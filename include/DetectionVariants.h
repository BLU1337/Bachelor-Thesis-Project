/** \file DetectionVariants.h
*	\author Benjamin Lueben
*
*	\brief multiple Detection Variants for Munchkin Tutorial

	In this class multiple Detection Variants are implemented to detect Munchkin Cards.
	Detection Variants contain Aruco Markers, Template Matching and neuronal net matching with YOLO.

*/

#pragma once

# include "opencv2/aruco.hpp"
# include "opencv2/dnn.hpp"
# include "GameState.h"
# include "MunchkinCards.h"
# include <PostProcessFunctions.h>
# include <GameState.h>
# include <common.h>

using namespace cv;
using namespace std;
using namespace munch_tut;

/// <summary>
/// Function to match Munchkincards via YOLO Neuronal Network. This function is based on online Tutorial by Sunita Nayak (https://learnopencv.com/deep-learning-based-object-detection-using-yolov3-with-opencv-python-c)
/// </summary>
/// <param name="frame">
/// current frame of webcam input
/// </param>
/// <param name="classes">
/// vector of class names that can be found by YOLO net
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
/// <param name="modus">
/// modus for yolo matching (1 => live tutorial; 2 => testing with class name and confidence displayed; 4 => testing withour class name and confidence displayed)
/// </param>
/// <param name="fileContent">
/// object of testOutput to store all data needed for testing
/// </param>
/// <returns> 1 if nothing failed.</returns>
int YOLOMatching(Mat& frame, const vector<String>& classes, float confThreshold, float nmsThreshold, GameState& gamestate, const vector<MunchkinCard>& cards, int modus, testOutput& fileContent);

/// <summary>
/// function to use Aruco Markers as workaround for matching method. Part of practical project.
/// </summary>
/// <param name="frame">
/// current frame of webcam input
/// </param>
/// <param name="gamestate">
/// gamestate object which stores all necessary data for tutorial
/// </param>
/// <param name="markerDictionary">
/// aruco dictionary object of what aruco dictionary is used and needs to be detected
/// </param>
/// <param name="arucoSquareDimensions">
/// dimension of aruco square that is printed onto the cards. Needs to be meassured.
/// </param>
/// <param name="cameraMatrix">
/// mat object of camera matrix which stores camera calibration needed for aruco markers to function
/// </param>
/// <param name="distanceCoefficients">
/// mat object of camera matrix which stores distance coefficients needed for aruco markers to function
/// </param>
/// <param name="cards">
/// vector of munchkin cards object in which all cards are stored that can be detected with the tutorial.
/// </param>
/// <returns> 1 if nothing failed.</returns>
int ArucoMatching(Mat& frame, GameState& gamestate, Ptr<aruco::Dictionary> markerDictionary, float arucoSquareDimensions, Mat cameraMatrix, Mat distanceCoefficients, vector<MunchkinCard> cards);