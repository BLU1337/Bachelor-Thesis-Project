# include <PostProcessFunctions.h>
#include <algorithm>
#include <vector>
#include <cmath>

Color chooseCardColor(int markerId, vector<MunchkinCard> cards)
{
	Color color;
	CardType type;
	try
	{
		type = cards.at(markerId).type;

		switch (type)
		{
		case CardType::curse:
			color[0] = 102;
			color[1] = 0;
			color[2] = 255;
			break;
		case CardType::munchClass:
			color[0] = 0;
			color[1] = 0;
			color[2] = 255;
			break;
		case CardType::joker:
			color[0] = 255;
			color[1] = 255;
			color[2] = 255;
			break;
		case CardType::lvlUp:
			color[0] = 255;
			color[1] = 153;
			color[2] = 51;
			break;
		case CardType::itemBuff:
			color[0] = 0;
			color[1] = 255;
			color[2] = 255;
			break;
		case CardType::monster:
			color[0] = 255;
			color[1] = 0;
			color[2] = 0;
			break;
		case CardType::race:
			color[0] = 255;
			color[1] = 255;
			color[2] = 0;
			break;
		case CardType::item:
			color[0] = 0;
			color[1] = 255;
			color[2] = 0;
			break;
		}

		return color;

	}
	catch (const std::out_of_range& ex)
	{
		std::cerr << "Invalid marker ID" << std::endl;
		color[0] = 255;
		color[1] = 255;
		color[2] = 255;
		return color;
		//throw ex;
	}

}

vector<String> getOutputsNames(const cv::dnn::Net& net)
{
	static vector<String> names;
	if (names.empty())
	{
		vector<int> outLayers = net.getUnconnectedOutLayers();

		vector<String> layersName = net.getLayerNames();

		names.resize(outLayers.size());
		for (size_t i = 0; i < outLayers.size(); ++i)
		{
			names[i] = layersName[outLayers[i] - 1];
		}

	}
	return names;
}

void drawPred(int classId, float conf, int left, int top, int right, int bottom, Mat& frame, vector<String> classes, vector<MunchkinCard> cards, int modus)
{
	Color bbColor = chooseCardColor(classId, cards);

	//Draw a rectangle displaying the bounding box
	//rectangle(frame, Point(left, top), Point(right, bottom), Scalar(255, 178, 50), 3);
	rectangle(frame, Point(left, top), Point(right, bottom), Scalar(bbColor[0], bbColor[1], bbColor[2]), 3);

	//Get the label for the class name and its confidence
	string label = format("%.2f", conf);
	if (!classes.empty())
	{
		CV_Assert(classId < (int)classes.size());
		label = classes[classId] + ":" + label;
	}

	if (modus != 4)
	{
		//Display the label at the top of the bounding box
		int baseLine;
		Size labelSize = getTextSize(label, FONT_HERSHEY_SIMPLEX, 0.5, 1, &baseLine);
		top = max(top, labelSize.height);
		rectangle(frame, Point(left, top - round(1.5 * labelSize.height)), Point(left + round(1.5 * labelSize.width), top + baseLine), Scalar(255, 255, 255), FILLED);
		putText(frame, label, Point(left, top), FONT_HERSHEY_SIMPLEX, 0.75, Scalar(0, 0, 0), 1);
	}

}

void postprocess(
	Mat& frame, 
	const vector<Mat>& outs, 
	float confThreshold, 
	float nmsThreshold, 
	GameState& gamestate, 
	const vector<String>& classes, 
	const vector<MunchkinCard>& cards,
	int modus,
	testOutput& fileContent)
{
	constexpr auto num_cells = constants::yolo_grid_size * constants::yolo_grid_size;
	const int cell_width = frame.cols / constants::yolo_grid_size;
	const int cell_height = frame.rows / constants::yolo_grid_size;

	struct BoundingBox
	{
		int centerX;
		int centerY;
		int width;
		int height;
		int left;
		int top;
		double confidence;
	};

	struct GridCell
	{
		std::vector<BoundingBox> boundingBoxes;
		cv::Mat classProbabilities;
		cv::Rect cellCoords;
	};

	vector<int> classIds;
	vector<float> confidences;
	vector<Rect> boxes;

	// create empty grid cells
	vector<GridCell> grid;
	std::fill_n(std::back_inserter(grid), num_cells, GridCell{});
	int boxCount = 0;
	stringstream singleFileString;

	for (size_t i = 0; i < outs.size(); ++i)
	{
		// Scan through all the bounding boxes output from the network and keep only the
		// ones with high confidence scores. Assign the box's class label as the class
		// with the highest score for the box.
		float* data = (float*)outs[i].data;
		for (int j = 0; j < outs[i].rows; ++j, data += outs[i].cols)
		{
			//std::vector<float> fuckthis(data, data + outs[i].cols);
			Mat scores = outs[i].row(j).colRange(5, outs[i].cols);
			//std::cout << scores << endl;
			Point classIdPoint;
			double confidence;
			// Get the value and location of the maximum score
			minMaxLoc(scores, 0, &confidence, 0, &classIdPoint);
			if (confidence > confThreshold)
			{
				BoundingBox bb{};

				bb.centerX = (int)(data[0] * frame.cols);
				bb.centerY = (int)(data[1] * frame.rows);
				bb.width = (int)(data[2] * frame.cols);
				bb.height = (int)(data[3] * frame.rows);
				bb.left = bb.centerX - bb.width / 2;
				bb.top = bb.centerY - bb.height / 2;
				bb.confidence = confidence;


				if (modus == 2)
				{
					// put box into grid cell
					int grid_x = bb.centerX / (frame.cols / constants::yolo_grid_size);
					int grid_y = bb.centerY / (frame.rows / constants::yolo_grid_size);
					grid[grid_y * constants::yolo_grid_size + grid_x].boundingBoxes.push_back(bb);

					drawPred(classIdPoint.x, (float)confidence, grid_x * cell_width, grid_y * cell_height,
						(grid_x + 1) * cell_width, (grid_y + 1) * cell_height, frame, classes, cards, 4);
				}

				classIds.push_back(classIdPoint.x);
				confidences.push_back((float)confidence);
				boxes.push_back(Rect(bb.left, bb.top, bb.width, bb.height));
				boxCount++;
			}
		}
	}

	// Perform non maximum suppression to eliminate redundant overlapping boxes with
	// lower confidences
	vector<int> indices;
	cv::dnn::NMSBoxes(boxes, confidences, confThreshold, nmsThreshold, indices);
	std::vector<double> classConfidences(classes.size(), -1.0);
	for (size_t i = 0; i < indices.size(); ++i)
	{
		int idx = indices[i];
		Rect box = boxes[idx];
		NNresult nnResult = { classIds[idx], box };
		gamestate.nnResults.push_back(nnResult);

		drawPred(classIds[idx], confidences[idx], box.x, box.y,
			box.x + box.width, box.y + box.height, frame, classes, cards, modus);

		if (modus == 2)
		{
			fileContent.fileString << "Found Class: " << cards.at(classIds[idx]).cardName << " with confidence: " << confidences[idx] << endl;
			classConfidences[classIds[idx]] = confidences[idx];
			fileContent.allClasses++;
			fileContent.allPropability += confidences[idx];

			if (fileContent.debugTick >= fileContent.debugSingleOutput)
			{
				singleFileString << "Found Class: " << cards.at(classIds[idx]).cardName << " with confidence: " << confidences[idx] << endl;

			}
		}
	}

	if (modus == 2)
	{
		if (fileContent.debugTick >= fileContent.debugSingleOutput && modus == 2)
		{
			singleFileString << endl << "Classes found in Frame: " << indices.size() << endl;

			fileContent.singleFile.push_back(std::move(singleFileString));
		}

		fileContent.fileString << endl << "Classes found in Frame: " << indices.size() << endl << endl;
		for (int c = 0; c < classConfidences.size(); ++c)
			fileContent.csvFileString << classConfidences[c] << (c < classConfidences.size() - 1 ? "," : "\n");
	}

}