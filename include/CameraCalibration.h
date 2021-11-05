/** \file CameraCalibration.h
*	\author Benjamin Lueben
*
*	\brief Camera Calibration with OpenCV Chessboard

	In this class the Webcam gets calibrated for use of Aruco Markers. 
	Calibration is done with OpenCV and Chessboard pattern.
	This Class is based on a series of youtube tutorials from George Lecakes regarding OpenCV Camera Calibration
	and Aruco Markers (pt1 of Camera Calibration: https://www.youtube.com/watch?v=HNfPbw-1e_w)

*/

#pragma once
# include "opencv2/opencv.hpp"
# include "opencv2/imgcodecs.hpp"
# include "opencv2/imgproc.hpp"
# include "opencv2/highgui.hpp"
# include "opencv2/aruco.hpp"
# include "opencv2/calib3d.hpp"
# include "opencv2/video.hpp"
# include "opencv2/videoio.hpp"


using namespace cv;
using namespace std;

/// <summary>
/// creates known boards position for chessboard used to calibrate camera.
/// </summary>
/// <param name="boardSize">
/// size of the calibration chess board. e.g 9x6
/// </param>
/// <param name="squareEdgeLength">
/// Square edge length of single calibration board tile. Needs to be meassured from printed chess board.
/// </param>
/// <param name="corners">
/// reference of chessboard corners that are returned.
/// </param>
void createKnownBoardPositions(Size boardSize, float squareEdgeLength, vector<Point3f>& corners);

/// <summary>
/// function to get chessboard corners from given images.
/// </summary>
/// <param name="images">
/// Vector of Mat objects with calibration pictures of chessboard.
/// </param>
/// <param name="allFoundCorners">
/// vector with vector of Points that return all found corners of tiles inside the chessboard pictures.
/// </param>
/// <param name="showResult">
/// bool of wether or not the results should be shown on the output image.
/// </param>
void getChessboardCorners(vector<Mat> images, vector<vector<Point2f>>& allFoundCorners, bool showResult = false);

/// <summary>
/// function to save camera calibration to calibration file.
/// </summary>
/// <param name="name">
/// name for the filepath to store camera matrix in
/// </param>
/// <param name="cameraMatrix">
/// calculated camera matrix mat object to store inside calibration file
/// </param>
/// <param name="distanceCoefficients">
/// distance coefficients that are also stored within the camera calibration file
/// </param>
/// <returns>
/// true => file was saved successfully; false => file could not be created;
/// </returns>
bool saveCameraCalibration(string name, Mat cameraMatrix, Mat distanceCoefficients);

/// <summary>
/// function so load camera calibration from file
/// </summary>
/// <param name="name">
/// filepath for camera calibration file
/// </param>
/// <param name="cameraMatrix">
/// reference to mat object to store camera matrix in and return camera matrix.
/// </param>
/// <param name="distanceCoefficients">
/// reference to mat object to store distance coefficients in and return them.
/// </param>
/// <returns>
/// true => file could be opened and camera matrix was loaded; false => file could not be opened.
/// </returns>
bool loadCameraCalibration(string name, Mat& cameraMatrix, Mat& distanceCoefficients);

/// <summary>
/// camera calibration function to process the actual camera calibration.
/// </summary>
/// <param name="calibrationImages">
/// vector of mat objects that store the calibration images.
/// </param>
/// <param name="boardSize">
/// size of chess board used to calibrate camera e.g 9x6
/// </param>
/// <param name="squareEdgeLength">
/// edge length of single square tile on calibration board
/// </param>
/// <param name="cameraMatrix">
/// reference of mat object for camera matrix to be stored in
/// </param>
/// <param name="distanceCoefficients">
/// reference of mat object for distance coefficients to be stored in
/// </param>
void cameraCalibration(vector<Mat> calibrationImages, Size boardSize, float squareEdgeLength, Mat& cameraMatrix, Mat& distanceCoefficients);

/// <summary>
/// function to guide through the camera calibration process. Can take Pictures of chess board to calibrate camera with
/// </summary>
/// <param name="cameraMatrix">
/// reference of mat object to store camera matrix in after calibration.
/// </param>
/// <param name="distanceCoefficients">
/// reference of mat object to store distance coefficients in after calibration.
/// </param>
/// <param name="chessboardDimensions">
/// size of chessboard dimensions e.g 9x6
/// </param>
/// <param name="calibrationSquareDimensions">
/// edge length of single square tile on calibration board
/// </param>
void cameraCalibrationProcess(Mat& cameraMatrix, Mat& distanceCoefficients, Size chessboardDimensions, float calbirationSquareDimension);