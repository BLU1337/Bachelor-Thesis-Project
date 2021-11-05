/** \file YOLODataGenerator.h
*	\author Benjamin Lueben
*
*	\brief generates Data for YOLO training

	In this class the functions needed for generating Data for YOLO neural net are defined.

*/

#pragma once
# include <vector>;
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

template <typename T>
T unirand(T a, T b);

template <typename T>
T uninorm(T mean, T sdev);

/// <summary>
/// generates datasets which were used to train YOLO nets. creates pictures and txt files with coordinates of bounding boxes relativ to picture size.
/// values num_images and num_inputPictures are used for how many images and how many input pictures should be used.
/// num_inputPictures means how many of loaded munchkin cards should be used.
/// </summary>
/// <returns> 1 when finished</returns>
int generateDatasetNN();


