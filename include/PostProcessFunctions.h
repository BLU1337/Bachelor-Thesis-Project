/** \file PostProcessFunctions.h
*	\author Benjamin Lueben
*
*	\brief all util/post process functions

	In this class all the needed util and post process functions for Detection Variants are defined.

*/

#pragma once
# include <MunchkinCards.h>
# include <GameState.h>
# include <common.h>

using namespace cv;
using namespace std;
using namespace munch_tut;

namespace constants
{
	inline constexpr int yolo_grid_size = 13;
}

/// <summary>
/// function to choose color e.g for boundingBoxes that is bound to type of single munchkin card.
/// </summary>
/// <param name="markerId">
/// id of munchkin card that was detected by tutorial. (former showed marker id which was referenced with munchkin card)
/// </param>
/// <param name="cards">
/// vector of munchkin card objects with all munchkin cards that are currently usable with the tutorial.
/// </param>
/// <returns> cv::Color object with color for card (BGR) </returns>
Color chooseCardColor(int markerId, vector<MunchkinCard> cards);

/// <summary>
/// function to get Outputs names from neuronal net. This function is based on online Tutorial by Sunita Nayak (https://learnopencv.com/deep-learning-based-object-detection-using-yolov3-with-opencv-python-c)
/// </summary>
/// <param name="net">
/// cv::dnn::Net reference of neuronal net that is used in tutorial.
/// </param>
/// <returns>
/// array of names that can be found by neuronal net.
/// </returns>
vector<String> getOutputsNames(const cv::dnn::Net& net);

/// <summary>
/// function to draw prediction boxes for YOLO matching. This function is based on online Tutorial by Sunita Nayak (https://learnopencv.com/deep-learning-based-object-detection-using-yolov3-with-opencv-python-c)
/// </summary>
/// <param name="classId">
/// class id of found class
/// </param>
/// <param name="conf">
/// confidence of class for predicted box
/// </param>
/// <param name="left">
/// x value of top-left corner of bounding box to be drawn
/// </param>
/// <param name="top">
/// width of bounding box to be drawn
/// </param>
/// <param name="right">
/// y value of top-left corner of bounding box to be drawn
/// </param>
/// <param name="bottom">
/// height of bounding box to be drawn
/// </param>
/// <param name="frame">
/// Mat obejct of current frame of webcam input
/// </param>
/// <param name="classes">
/// vector of classes name that can be found with YOLO net
/// </param>
/// <param name="cards">
/// vector ob MunchkinCards object which stores all current detectable munchkin cards
/// </param>
/// <param name="modus">
/// modus for yolo matching (1 => live tutorial; 2 => testing with class name and confidence displayed; 4 => testing withour class name and confidence displayed)
/// </param>
void drawPred(int classId, float conf, int left, int top, int right, int bottom, Mat& frame, vector<String> classes, vector<MunchkinCard> cards, int modus);

/// <summary>
/// function which handles the post processing of outputs of YOLO matching method. This function is based on online Tutorial by Sunita Nayak (https://learnopencv.com/deep-learning-based-object-detection-using-yolov3-with-opencv-python-c)
/// </summary>
/// <param name="frame">
/// Mat obejct of current frame of webcam input
/// </param>
/// <param name="outs">
/// vector of mat objects in which outputs from YOLO net are stored in.
/// </param>
/// <param name="confThreshold">
/// threshold for confidence with which matches should be declared as valid/correct.
/// </param>
/// <param name="nmsThreshold">
/// Threshold for non-maximum suppression method to remove overlapping bounding boxes
/// </param>
/// <param name="gamestate">
/// gamestate object which stores all necessary data for tutorial
/// </param>
/// <param name="cards">
/// vector of munchkin cards object in which all cards are stored that can be detected with the tutorial.
/// </param>
/// <param name="classes">
/// vector of classes name that can be found with YOLO net
/// </param>
/// <param name="modus">
/// modus for yolo matching (1 => live tutorial; 2 => testing with class name and confidence displayed; 4 => testing withour class name and confidence displayed)
/// </param>
/// <param name="fileContent">
/// object of testOutput to store all data needed for testing
/// </param>
void postprocess(Mat& frame, const vector<Mat>& outs, float confThreshold, float nmsThreshold, GameState& gamestate, const vector<String>& classes, const vector<MunchkinCard>& cards, int modus, testOutput& fileContent);
