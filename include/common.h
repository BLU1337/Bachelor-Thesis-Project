/** \file common.h
*	\author Benjamin Lueben
* 
*	\brief class for common used tools, objects, etc
* 
*	In this class helpfull things like own namespaces or custom structs are defined that can be used throughout the whole classes.
*/

#pragma once
#include <array>
#include <sstream>

/**
* \brief namespace for munchkin tutorial
*/
namespace munch_tut {
	using Color = std::array<int, 3>;
}

/**
* \brief struct for object that is used for the YOLO tests.
*/
struct testOutput
{
	vector<stringstream> singleFile;	///< vector of stringstreams for single test output files
	vector<stringstream> csvSingleFile; ///< vector of stringstreams for single test output csv files
	stringstream fileString;			///< stringstream for the whole test output file
	stringstream csvFileString;			///< stringstream for the whole test output csv file
	int fileCounter;					///< counter for how many files are already written
	int debugTick;						///< current tick (seconds) for test
	int debugSingleOutput;				///< tick value for when a single output file should be generated
	double allClasses;					///< adds up the munchkin classes found in a single frame to calculate the average class count
	double inferenceTime;				///< adds up the inference time for each frame to calculate the average inferance time
	double allPropability;				///< double value to add up all class propabilities to calculate the average class propability
	string YoloName;					///< name of yolo net that is tested
	string MunchkinClassesNum;			///< Number of munchkin classes (cards) that are used in the test.
};