# include "opencv2/opencv.hpp"
# include "opencv2/imgcodecs.hpp"
# include "opencv2/imgproc.hpp"
# include "opencv2/highgui.hpp"
# include "opencv2/aruco.hpp"
# include "opencv2/calib3d.hpp"
# include "opencv2/video.hpp"
# include "opencv2/dnn.hpp"
# include "opencv2/videoio.hpp"
# include "GameState.h"
# include "MunchkinCards.h"
# include "CardTypeActions.h"
# include "common.h"
# include "Button.h"
# include "ArucoGenerator.h"
# include "CameraCalibration.h"
# include "DetectionVariants.h"
# include "YOLODataGenerator.h"

# include <sstream>
# include <iostream>
# include <fstream>
# include <string>
# include <stdexcept>
# include <unordered_map>
# include <functional>
# include <random>
# include <map>
# include <iomanip>
# include <cmath>
# include <type_traits>

using namespace cv;
using namespace std;
using namespace munch_tut;

const float calbirationSquareDimension = 0.025f; //meters
const float arucoSquareDimension = 0.02f; //meters
const Size chessboardDimensions = Size(6, 9);
float confThreshold = 0.7;
float nmsThreshold = 0.4;
int modus = 2;
int debugSingleOutput = 5;
bool multipleTests = false;
string YoloName = "40-20k";
string MunchkinClassesNum = "40";
string testNum = "3";
vector<String> classes;

vector<MunchkinCard> cards;
std::unordered_map<CardType, CardTypeFunc> functMap;

GameState gamestate;


// button callbacks
void button_exit(const Button& b);
void button_continue(const Button& b);
void button_end_turn(const Button& b);

void logic()
{
	//Rect rect(corners[1].x, corners[1].y, corners[0].y - corners[1].y, corners[0].y - corners[1].y);
	if (gamestate.mouseparams.event == MouseEvent::lclick)
	{
		gamestate.mouseparams.event = MouseEvent::none;

		// process button events
		for (const Button& b : gamestate.buttons)
		{
			if (b.poll_click(gamestate.mouseparams.clickP, gamestate.canvas_size))
			{
				// do stuff
			}
		}

		int iterator = 0;

		for (NNresult result : gamestate.nnResults)
		{
			if ((gamestate.nnResults[iterator].nnBBox.contains(gamestate.mouseparams.clickP)) || (gamestate.should_continue == true))
			{
				MunchkinCard singleCard = cards.at(gamestate.nnResults[iterator].id);
				std::cout << "Left button of mouse is clicked _ position (" << gamestate.mouseparams.clickP.x << "," << gamestate.mouseparams.clickP.y << ")" << endl;
				std::cout << "markerId: " << gamestate.nnResults[iterator].id << endl;
				std::cout << "Name: " << cards.at(gamestate.nnResults[iterator].id).cardName << endl;
				std::cout << "type: " << (int)cards.at(gamestate.nnResults[iterator].id).type << endl;
				auto cardtype = cards.at(gamestate.nnResults[iterator].id).type;

				if (functMap.find(cardtype) != functMap.end())
				{
					functMap[cardtype](gamestate, singleCard);
				}
			}

			iterator++;

		}

		//if ((gamestate.mouseparams.poly.size() > 2 && pointPolygonTest(gamestate.mouseparams.poly, gamestate.mouseparams.clickP, false) == 1/*rect.contains(clickP)*/) || (gamestate.should_continue == true))
		//{
		//	MunchkinCard singleCard = cards.at(gamestate.mouseparams.markerId);
		//	std::cout << "Left button of mouse is clicked _ position (" << gamestate.mouseparams.clickP.x << "," << gamestate.mouseparams.clickP.y << ")" << endl;
		//	std::cout << "markerId: " << gamestate.mouseparams.markerId << endl;
		//	std::cout << "Name: " << cards.at(gamestate.mouseparams.markerId).cardName << endl;
		//	std::cout << "type: " << (int)cards.at(gamestate.mouseparams.markerId).type << endl;
		//	auto cardtype = cards.at(gamestate.mouseparams.markerId).type;
		//
		//	if (functMap.find(cardtype) != functMap.end())
		//	{
		//		functMap[cardtype](gamestate, singleCard);
		//	}
		//}

	}
	if (gamestate.mouseparams.event == MouseEvent::rclick)
	{
		gamestate.mouseparams.event = MouseEvent::none;

		if ((gamestate.mouseparams.poly.size() > 2 && pointPolygonTest(gamestate.mouseparams.poly, gamestate.mouseparams.clickP, false) == 1))
		{
			MunchkinCard singleCard = cards.at(gamestate.mouseparams.markerId);
			auto cardtype = cards.at(gamestate.mouseparams.markerId).type;
			gamestate.remove_card = true;

			if (functMap.find(cardtype) != functMap.end())
			{
				functMap[cardtype](gamestate, singleCard);
			}
		}
	}

	if (gamestate.end_turn == true)
	{

		gamestate.buttons.at(1).visible = true;
		gamestate.buttons.at(1).callback = button_end_turn;
	}

}

void callBackFunction(int event, int x, int y, int flags, void* userdata)
{
	gamestate.mouseparams.clickP.x = x;
	gamestate.mouseparams.clickP.y = y;
	if (event == EVENT_LBUTTONDOWN)
	{
		//logic();
		gamestate.mouseparams.event = MouseEvent::lclick;
	}
	else if (event == EVENT_RBUTTONDOWN)
	{
		gamestate.mouseparams.event = MouseEvent::rclick;
	}
	else
	{
		gamestate.mouseparams.event = MouseEvent::none;
	}
}

int TestYOLOMatching()
{
	testOutput fileContent;
	fileContent.fileCounter = 0;
	fileContent.debugTick = 0;
	fileContent.inferenceTime = 0;
	fileContent.allPropability = 0.00;
	fileContent.debugSingleOutput = debugSingleOutput;
	fileContent.allClasses = 0;
	fileContent.MunchkinClassesNum = MunchkinClassesNum;
	fileContent.YoloName = YoloName;

	std::stringstream testVidFile;
	std::stringstream testOutputVidFile;
	testVidFile << "TestVideos/Testvideo-" << fileContent.MunchkinClassesNum << "-" << testNum << ".mp4";
	testOutputVidFile << "TestOutput/thresh" << confThreshold << "/test" << testNum << "/yolov3-tiny-" << YoloName << "/test" << testNum << "Output_" << YoloName << ".avi";
	VideoCapture testVid(testVidFile.str());

	VideoWriter video(testOutputVidFile.str(), CV_FOURCC('M', 'J', 'P', 'G'), testVid.get(CAP_PROP_FPS), Size(testVid.get(cv::CAP_PROP_FRAME_WIDTH), testVid.get(cv::CAP_PROP_FRAME_HEIGHT)));
	int frameCounter = 0;
	int fullFrameCounter = 0;
	int tick = 0;
	double fps = 0.00;
	std::time_t timeBegin = std::time(0);

	if (!testVid.isOpened()) {
		std::cout << "Error opening file stream!" << endl;
		return -1;
	}

	while (1) {

		Mat frame;
		Mat rawFrame;

		testVid >> frame;

		if (frame.empty())
			break;

		frameCounter++;
		std::time_t timeNow = std::time(0) - timeBegin;

		if (timeNow - tick >= 1)
		{
			tick++;
			fps = static_cast<float>(frameCounter);
			frameCounter = 0;
			fileContent.debugTick++;
			frame.copyTo(rawFrame);
		}

		YOLOMatching(frame, classes, confThreshold, nmsThreshold, gamestate, cards, modus, fileContent);

		string label = format("Average frames per second: %.2f FPS", fps);
		cv::putText(frame, label, Point(0, 30), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 255));

		if (fileContent.debugTick >= fileContent.debugSingleOutput)
		{
			
			stringstream fileName;
			stringstream txtFileName;
			stringstream rawFileName;
			fileName << "TestOutput/thresh" << confThreshold << "/test" << testNum << "/yolov3-tiny-" << YoloName << "/test" << testNum << "Output_" << YoloName << "-" << std::to_string(fileContent.fileCounter);
			txtFileName << fileName.str() << ".txt";
			rawFileName << fileName.str() << "_raw.jpg";
			fileName << ".jpg";
			imwrite(fileName.str(), frame);
			imwrite(rawFileName.str(), rawFrame);
			std::ofstream testFile(txtFileName.str(), std::ios::binary | std::ios::trunc);
			testFile << fileContent.singleFile.at(fileContent.fileCounter).str() << endl;
			testFile.close();
			fileContent.fileCounter++;
			fileContent.debugTick = 0;
		}

		fullFrameCounter++;
		imshow("testFrame", frame);
		video.write(frame);
		if (waitKey(5) == 27) break;

	}
	std::time_t totalTime = std::time(0) - timeBegin;
	double avgFPS = (static_cast<double>(fullFrameCounter) / totalTime);
	double avgInferenceTime = fileContent.inferenceTime / fullFrameCounter;
	double avgClasses = fileContent.allClasses / fullFrameCounter;
	double avgClassProp = fileContent.allPropability / fileContent.allClasses;
	fileContent.fileString << endl << format("Average FPS in Testvideo: %.2f", avgFPS) << endl;
	fileContent.fileString << endl << format("Average inference time per frame in Testvideo: %.2f", avgInferenceTime);
	fileContent.fileString << endl << format("Average classes found per frame: %.2f", avgClasses);
	fileContent.fileString << endl << format("Average class propability in video: %.2f", avgClassProp);
	std::stringstream testOutputFile;
	testOutputFile<< "TestOutput/thresh" << confThreshold << "/test" << testNum << "/yolov3-tiny-" << YoloName << "/test" << testNum << "Output_" << fileContent.YoloName << ".txt";
	std::ofstream testOutput(testOutputFile.str(), std::ios::binary | std::ios::trunc);
	testOutput << fileContent.fileString.str() << endl;
	testOutput.close();

	std::stringstream testOutputCSVFile;
	testOutputCSVFile << "TestOutput/thresh" << confThreshold << "/test" << testNum << "/yolov3-tiny-" << YoloName << "/test" << testNum << "Output_" << fileContent.YoloName << ".csv";
	std::ofstream testOutputCSV(testOutputCSVFile.str(), std::ios::binary | std::ios::trunc);
	testOutputCSV << fileContent.csvFileString.str() << endl;
	testOutputCSV.close();

	testVid.release();
	video.release();

	return 1;

}

int startWebcamMonitoring(/*const Mat& cameraMatrix, const Mat& distanceCoefficients, float arucoSquareDimensions*/)
{
	Mat frame;
	gamestate.mouseparams.tutText = { "Um zu beginnen lege eine ", "Karte nach der anderen vor ", "die Kamera und klicke mit der ", "linken Maustaste auf ", "das farbige Quadrat!" };
	int offset = 25;
	int frameCounter = 0;
	int tick = 0;
	double fps;
	testOutput fileContent;
	fileContent.MunchkinClassesNum = MunchkinClassesNum;
	fileContent.YoloName = YoloName;
	std::time_t timeBegin = std::time(0);

	vector<int> markerIds;
	Moments m;
	Color cardColor;
	vector<Point2f> corners;
	vector<Point> poly;
	vector<vector<Point2f>> markerCorners, rejectedCandidates;
	aruco::DetectorParameters parameters;

	Ptr<aruco::Dictionary> markerDictionary = aruco::getPredefinedDictionary(aruco::PREDEFINED_DICTIONARY_NAME::DICT_4X4_50);

	VideoCapture vid(0);

	if (!vid.isOpened())
	{
		return -1;
	}

	vid.set(cv::CAP_PROP_FRAME_WIDTH, 1280);
	vid.set(cv::CAP_PROP_FRAME_HEIGHT, 720);

	namedWindow("Webcam", CV_WINDOW_AUTOSIZE);

	vector<Vec3d> rotationVectors, translationVectors;

	while (!gamestate.should_exit)
	{
		if (!vid.read(frame))
			break;

		frameCounter++;
		std::time_t timeNow = std::time(0) - timeBegin;

		if (timeNow - tick >= 1)
		{
			tick++;
			fps = static_cast<float>(frameCounter);
			frameCounter = 0;
		}

		double vidFPS = vid.get(CAP_PROP_FPS);

		YOLOMatching(frame, classes, confThreshold, nmsThreshold, gamestate, cards, 1, fileContent);

		for (int i = 0; i < gamestate.mouseparams.tutText.size(); i++)
		{
			cv::putText(frame, gamestate.mouseparams.tutText.at(i), Point(50, 60 + i * offset), FONT_HERSHEY_COMPLEX, 1.0, Scalar(0, 0, 0), 4);
			cv::putText(frame, gamestate.mouseparams.tutText.at(i), Point(50, 60 + i * offset), FONT_HERSHEY_COMPLEX, 1.0, Scalar(0, 204, 0), 2);
		}

		
		string label = format("Average frames per second: %.2f FPS", fps);
		cv::putText(frame, label, Point(0, 30), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 255));

		cv::setMouseCallback("Webcam", callBackFunction);
		// draw buttons
		for (const Button& b : gamestate.buttons)
		{
			b.draw(frame);
		}
		// show frame
		gamestate.canvas_size = cv::Size(frame.cols, frame.rows);
		imshow("Webcam", frame);
		if (waitKey(5) == 27) break;

		// poll game logic
		logic();
		gamestate.nnResults.clear();
	}

	return 1;
}

int testArucoMatching(const Mat& cameraMatrix, const Mat& distanceCoefficients, float arucoSquareDimensions)
{
	Mat frame;
	gamestate.mouseparams.tutText = { "Um zu beginnen lege eine ", "Karte nach der anderen vor ", "die Kamera und klicke mit der ", "linken Maustaste auf ", "das farbige Quadrat!" };
	int offset = 25;
	int frameCounter = 0;
	int tick = 0;
	double fps;
	testOutput fileContent;
	fileContent.MunchkinClassesNum = MunchkinClassesNum;
	fileContent.YoloName = YoloName;
	std::time_t timeBegin = std::time(0);

	vector<int> markerIds;
	Moments m;
	Color cardColor;
	vector<Point2f> corners;
	vector<Point> poly;
	vector<vector<Point2f>> markerCorners, rejectedCandidates;
	aruco::DetectorParameters parameters;

	Ptr<aruco::Dictionary> markerDictionary = aruco::getPredefinedDictionary(aruco::PREDEFINED_DICTIONARY_NAME::DICT_4X4_50);

	VideoCapture vid(0);

	if (!vid.isOpened())
	{
		return -1;
	}

	vid.set(cv::CAP_PROP_FRAME_WIDTH, 1280);
	vid.set(cv::CAP_PROP_FRAME_HEIGHT, 720);

	namedWindow("Webcam", CV_WINDOW_AUTOSIZE);

	vector<Vec3d> rotationVectors, translationVectors;

	while (!gamestate.should_exit)
	{
		if (!vid.read(frame))
			break;

		frameCounter++;
		std::time_t timeNow = std::time(0) - timeBegin;

		if (timeNow - tick >= 1)
		{
			tick++;
			fps = static_cast<float>(frameCounter);
			frameCounter = 0;
		}

		double vidFPS = vid.get(CAP_PROP_FPS);

		ArucoMatching(frame, gamestate, markerDictionary, arucoSquareDimensions, cameraMatrix, distanceCoefficients,cards);

		for (int i = 0; i < gamestate.mouseparams.tutText.size(); i++)
		{
			cv::putText(frame, gamestate.mouseparams.tutText.at(i), Point(50, 60 + i * offset), FONT_HERSHEY_COMPLEX, 1.0, Scalar(0, 0, 0), 4);
			cv::putText(frame, gamestate.mouseparams.tutText.at(i), Point(50, 60 + i * offset), FONT_HERSHEY_COMPLEX, 1.0, Scalar(0, 204, 0), 2);
		}


		string label = format("Average frames per second: %.2f FPS", fps);
		cv::putText(frame, label, Point(0, 30), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 255));

		cv::setMouseCallback("Webcam", callBackFunction);
		// draw buttons
		for (const Button& b : gamestate.buttons)
		{
			b.draw(frame);
		}
		// show frame
		gamestate.canvas_size = cv::Size(frame.cols, frame.rows);
		imshow("Webcam", frame);
		if (waitKey(5) == 27) break;

		// poll game logic
		logic();
		gamestate.nnResults.clear();
	}

	return 1;
}


int main(int argv, char** argc)
{
	Mat cameraMatrix = Mat::eye(3, 3, CV_64F);

	Mat distanceCoefficients;
	//try
	//{
		//createArucoMarkers();
	stringstream classesFile;
	classesFile << "obj" << MunchkinClassesNum << ".names";
	ifstream ifs(classesFile.str().c_str());
	string line;

	while (getline(ifs, line)) classes.push_back(line);
	if (argv == 2)
	{
		if (std::string(argc[1]) == "-c")
		{
			cameraCalibrationProcess(cameraMatrix, distanceCoefficients, chessboardDimensions, calbirationSquareDimension);
			return 0;
		}
		else if (std::string(argc[1]) == "-g")
		{
			createArucoMarkers();
			return 0;
		}
		else if (std::string(argc[1]) == "-amm")
		{

			cards = MunchkinCard::cardsConstr();
			gamestate.player01.sex = "male";
			gamestate.player01.lvl = 1;
			gamestate.player01.strength = 0;
			gamestate.player01.hands = 2;
			gamestate.player01.carriesLargeItems = false;
			gamestate.player01.hasArmor = false;
			gamestate.player01.hasHat = false;
			gamestate.player01.hasShoes = false;
			gamestate.player01.runStrength = 4;
			gamestate.player01.availableClasses = 1;
			gamestate.player01.availableRaces = 1;
			gamestate.should_exit = false;
			gamestate.should_continue = false;
			gamestate.run_away = false;
			gamestate.end_turn = false;
			gamestate.remove_card = false;
			gamestate.mouseparams.event = MouseEvent::none;

			// setup buttons
			// exit button
			gamestate.buttons.push_back(
				Button{
					0,
					cv::Rect(5, 5, 25, 25),
					cv::Scalar(255, 0, 0),
					true,
					ButtonOrigin::topright,
					button_exit
				}
			);

			// continue button
			gamestate.buttons.push_back(
				Button{
					1,
					cv::Rect(5, 5, 50, 50),
					cv::Scalar(0, 255, 0),
					false,
					ButtonOrigin::bottomright,
					button_continue
				}
			);

			functMap[CardType::curse] = cardtypeaction::curse;
			functMap[CardType::item] = cardtypeaction::item;
			functMap[CardType::monster] = cardtypeaction::monster;
			functMap[CardType::munchClass] = cardtypeaction::munchClass;
			functMap[CardType::race] = cardtypeaction::race;
			functMap[CardType::itemBuff] = cardtypeaction::itemBuff;
			functMap[CardType::joker] = cardtypeaction::joker;
			functMap[CardType::lvlUp] = cardtypeaction::lvlUp;

			loadCameraCalibration("CameraCalibration", cameraMatrix, distanceCoefficients);
			testArucoMatching(cameraMatrix, distanceCoefficients, 0.005f);


		}
		else if (std::string(argc[1]) == "-nn")
		{
			cards = MunchkinCard::cardsConstr();
			//testNNMatching(cameraMatrix, distanceCoefficients);
			return 0;
		}
		else if (std::string(argc[1]) == "-gdnn")
		{
			generateDatasetNN();
			return 0;
		}
		else if (std::string(argc[1]) == "-tnn")
		{
			cards = MunchkinCard::cardsConstr();

			if (!multipleTests)
			{
				TestYOLOMatching();
			}
			else
			{
				vector<string> yolos;
				vector<string> classesNum;
				yolos.push_back("10-5k");
				yolos.push_back("10-10k");
				yolos.push_back("10-20k");
				yolos.push_back("20-1k");
				yolos.push_back("10-1k");
				yolos.push_back("20-5k");
				yolos.push_back("20-10k");
				yolos.push_back("20-20k");
				yolos.push_back("30-1k");
				yolos.push_back("30-5k");
				yolos.push_back("30-10k");
				yolos.push_back("30-20k");
				yolos.push_back("40-1k");
				yolos.push_back("40-5k");
				yolos.push_back("40-10k");
				yolos.push_back("40-20k");
				yolos.push_back("40-20k-2");

				classesNum.push_back("10");
				classesNum.push_back("10");
				classesNum.push_back("10");
				classesNum.push_back("10");
				classesNum.push_back("20");
				classesNum.push_back("20");
				classesNum.push_back("20");
				classesNum.push_back("20");
				classesNum.push_back("30");
				classesNum.push_back("30");
				classesNum.push_back("30");
				classesNum.push_back("30");
				classesNum.push_back("40");
				classesNum.push_back("40");
				classesNum.push_back("40");
				classesNum.push_back("40");
				classesNum.push_back("40");

				for (size_t i = 0; i < yolos.size(); i++)
				{
					YoloName = yolos.at(i);
					MunchkinClassesNum = classesNum.at(i);
					TestYOLOMatching();
				}

			}
			return 0;
		}
		else
		{
			std::cerr << "Invalid command line option" << std::endl;
			return 1;
		}
	}
	else if(argv == 1)
	{

		cards = MunchkinCard::cardsConstr();
		gamestate.player01.sex = "male";
		gamestate.player01.lvl = 1;
		gamestate.player01.strength = 0;
		gamestate.player01.hands = 2;
		gamestate.player01.carriesLargeItems = false;
		gamestate.player01.hasArmor = false;
		gamestate.player01.hasHat = false;
		gamestate.player01.hasShoes = false;
		gamestate.player01.runStrength = 4;
		gamestate.player01.availableClasses = 1;
		gamestate.player01.availableRaces = 1;
		gamestate.should_exit = false;
		gamestate.should_continue = false;
		gamestate.run_away = false;
		gamestate.end_turn = false;
		gamestate.remove_card = false;
		gamestate.mouseparams.event = MouseEvent::none;

		// setup buttons
		// exit button
		gamestate.buttons.push_back(
			Button{
				0,
				cv::Rect(5, 5, 25, 25),
				cv::Scalar(255, 0, 0),
				true,
				ButtonOrigin::topright,
				button_exit
			}
		);

		// continue button
		gamestate.buttons.push_back(
			Button{
				1,
				cv::Rect(5, 5, 50, 50),
				cv::Scalar(0, 255, 0),
				false,
				ButtonOrigin::bottomright,
				button_continue
			}
		);

		functMap[CardType::curse] = cardtypeaction::curse;
		functMap[CardType::item] = cardtypeaction::item;
		functMap[CardType::monster] = cardtypeaction::monster;
		functMap[CardType::munchClass] = cardtypeaction::munchClass;
		functMap[CardType::race] = cardtypeaction::race;
		functMap[CardType::itemBuff] = cardtypeaction::itemBuff;
		functMap[CardType::joker] = cardtypeaction::joker;
		functMap[CardType::lvlUp] = cardtypeaction::lvlUp;

		//cameraCalibrationProcess(cameraMatrix, distanceCoefficients);
		//loadCameraCalibration("CameraCalibration", cameraMatrix, distanceCoefficients);
		//testNNMatching(cameraMatrix, distanceCoefficients);
		startWebcamMonitoring(/*cameraMatrix, distanceCoefficients, 0.005f*/);
		return 0;
	}
	else
	{
		std::cerr << "Invalid command line arguments" << std::endl;
		return 1;
	}
	//}
	//catch(std::exception& ex)
	//{
	//	std::cerr << ex.what() << std::endl;
	//	return 0;
	//}
	//catch(...)
	//{
	//	std::cerr << "unknown error" << std::endl;
	//	return 0;
	//}	
}

void button_exit(const Button & b)
{
	gamestate.should_exit = true;
	//std::cout << "Button " << b.id << std::endl;
}

void button_continue(const Button & b)
{
	gamestate.should_continue = true;
	gamestate.buttons.at(1).visible = false;

}

void button_end_turn(const Button & b)
{
	gamestate.end_turn = false;
	gamestate.buttons.at(1).visible = false;
	gamestate.mouseparams.tutText = { "Nachdem du deine Schaetze ", "durchgesehen und ggf ausgeruestet ", "hast kommt nun die milde Gabe!", "gebe so viele Karten an", "die Person mit niedrigstem level", ", oder lege sie ab wenn du", "das niedrigste level hast, ", "bis du nurnoch 5 Karten hast!" };
	gamestate.buttons.at(1).visible = false;
	gamestate.buttons.at(1).callback = button_continue;

}