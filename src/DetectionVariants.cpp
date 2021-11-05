# include <DetectionVariants.h>


int YOLOMatching(Mat& frame, const vector<String>& classes, float confThreshold, float nmsThreshold, GameState& gamestate, const vector<MunchkinCard>& cards, int modus, testOutput& fileContent)
{

	std::stringstream model;
	std::stringstream config;
	model << "YOLOs/yolov3-tiny-" << fileContent.YoloName << "/results/yolov3-tiny-" << fileContent.MunchkinClassesNum << "_best.weights";
	config << "YOLOs/yolov3-tiny-" << fileContent.MunchkinClassesNum << ".cfg";

	//cv::dnn::Net network = cv::dnn::readNet(model, config, "Darknet");
	cv::dnn::Net network = cv::dnn::readNetFromDarknet(config.str(), model.str());
	network.setPreferableBackend(cv::dnn::DNN_BACKEND_OPENCV);
	network.setPreferableTarget(cv::dnn::DNN_TARGET_CPU);

	cv::Mat blobFromImg;
	bool swapRB = true;
	cv::dnn::blobFromImage(frame, blobFromImg, 1 / 255.0, Size(416, 416), Scalar(), swapRB, false);
	//cv::Size blob = blobFromImg.size();

	//cout << blob << endl;

	float scale = static_cast<float>(1.0) / 255.0;
	Scalar mean = 0;
	network.setInput(blobFromImg/*, "", scale, mean*/);

	vector<Mat> outs;
	auto on = getOutputsNames(network);
	network.forward(outs, on);

	postprocess(frame, outs, confThreshold, nmsThreshold, gamestate, classes, cards, modus, fileContent);

	vector<double> layersTimes;
	double freq = getTickFrequency() / 1000;
	double t = network.getPerfProfile(layersTimes) / freq;
	fileContent.inferenceTime += t;
	string label = format("Inference time for a frame: %.2f ms", t);
	cv::putText(frame, label, Point(0, 15), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 255));


	return 1;
}

int ArucoMatching(Mat& frame, GameState& gamestate, Ptr<aruco::Dictionary> markerDictionary, float arucoSquareDimensions, Mat cameraMatrix, Mat distanceCoefficients, vector<MunchkinCard> cards)
{
	vector<int> markerIds;
	Moments m;
	Color cardColor;
	vector<vector<Point2f>> markerCorners, rejectedCandidates;
	vector<Point2f> corners;
	vector<Point> poly;
	vector<Vec3d> rotationVectors, translationVectors;
	Rect box;

	aruco::detectMarkers(frame, markerDictionary, markerCorners, markerIds);

	if (markerIds.size() > 0)
	{
		aruco::drawDetectedMarkers(frame, markerCorners, markerIds);
		aruco::estimatePoseSingleMarkers(markerCorners, arucoSquareDimensions, cameraMatrix, distanceCoefficients, rotationVectors, translationVectors);
	
		for (int i = 0; i < markerIds.size(); i++)
		{
			//aruco::drawAxis(frame, cameraMatrix, distanceCoeffiecients, rotationVectors[i], translationVectors[i], 0.1);
			gamestate.mouseparams.markerId = markerIds.at(i);
			for (int j = markerCorners[i].size() - 4; j < markerCorners[i].size(); j++)
			{
				corners.push_back(markerCorners[i][j]);
			}
			/*for (int j = 0; j < 4; j++)
			{
				params.markerCorner.push_back(markerCorners[i][j]);
				//corners.push_back(markerCorners[i][j]);
			}*/
			cv::approxPolyDP(corners, poly, 0, true);
			gamestate.mouseparams.poly = poly;
			box = Rect(corners[0].x, corners[0].y, (corners[1].x - corners[0].x), (corners[2].y - corners[0].y));
			NNresult nnResult = { markerIds.at(i), box };
			gamestate.nnResults.push_back(nnResult);
			
			try
			{
				cardColor = chooseCardColor(markerIds.at(i), cards);
				//cv::fillPoly(frame, poly, cv::Scalar(cardColor[2], cardColor[1], cardColor[0]));

				cv::rectangle(frame, Point(box.x, box.y), Point(box.x + box.width, box.y + box.height), Scalar(cardColor[0], cardColor[1], cardColor[2]), FILLED);
				//cv::rectangle(frame, Point(markerCorners[i][1].x, markerCorners[i][1].y), Point(markerCorners[i][3].x, markerCorners[i][3].y), Scalar(cardColor[0], cardColor[1], cardColor[2]), FILLED);
				m = moments(poly);
				Point center(m.m10 / m.m00, m.m01 / m.m00);
				cv::putText(frame, cards.at(markerIds[i]).cardName, center, FONT_HERSHEY_COMPLEX_SMALL, 1.0, Scalar(255,255,255));
			}
			catch (const std::out_of_range& ex)
			{
				std::cerr << "Invalid marker ID thingy" << std::endl;
				continue;
				//throw ex;
			}
			corners.clear();
		}
	}

	return 1;

}