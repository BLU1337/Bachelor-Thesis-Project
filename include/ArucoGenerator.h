/** \file ArucoGenerator.h
*	\author Benjamin Lueben
*
*	\brief class to generate new Aruco Markers

	In this class the Aruco Markers can be generated. By now 50 4x4 Aruco Markers are generated.

*/

#pragma once

# include <vector>
# include "opencv2/opencv.hpp"
# include "opencv2/aruco.hpp"
# include <string>
# include <sstream>
# include <iostream>
# include <fstream>

/// function to generate Aruco Markers. Dictionary for Aruco Markers are choosen inside this function.
void createArucoMarkers();
