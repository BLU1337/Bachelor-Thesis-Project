# Bachelor-Thesis-Project

## Build Instructions
OpenCV 3 with contrib modules needs to be installed via CMake.
Add a environment variable "OpenCV_DIR" to the path of the corresponding install root directory.
Then build the project itself as usual.

After building finished download all Files from https://th-koeln.sciebo.de/s/9oSsSW6dSUsiHBE.
Add files from "obj names Dateien" Folder to the Project directory.
Unzip other Folders and add them to the Project directory as well.

## PPMunchkinTut Functions

A Documentation for all functions from the previous project can be found under: [PPMunchkinTut](https://github.com/BLU1337/PPMunchkinTut/)

## Data Generator

To generate all data used for YOLO training add "-gdnn" Commandline Option.
To change the number of images that should be generated change variable num_images from generateDataSetNN function in [YOLODataGenerator.cpp](https://github.com/BLU1337/Bachelor-Thesis-Project/blob/2cba473dc29c4f76d1e17f173ee454b47ae8b677/src/YOLODataGenerator.cpp) File.
To change the number of different cards in the training pictures change variable num_inputPictures from generateDataSetNN function in [YOLODataGenerator.cpp](https://github.com/BLU1337/Bachelor-Thesis-Project/blob/2cba473dc29c4f76d1e17f173ee454b47ae8b677/src/YOLODataGenerator.cpp) File.

## Run Tests

To run different Tests that are added for this project add "-tnn" Commandline Option.
To change YOLO Net to be tested alter variable YoloName in [main.cpp](https://github.com/BLU1337/Bachelor-Thesis-Project/blob/2cba473dc29c4f76d1e17f173ee454b47ae8b677/src/main.cpp) File.
Available YOLO Nets are:
- 10-1k
- 10-5k
- 10-10k
- 10-20k
- 20-1k
- 20-5k
- 20-10k
- 20-20k
- 30-1k
- 30-5k
- 30-10k
- 30-20k
- 40-1k
- 40-5k
- 40-10k
- 40-20k

If you test single Nets you need to change variable MunchkinClassesNum appropriate to Numbers of Classes in Net (first 2 digits of Net Name) in [main.cpp](https://github.com/BLU1337/Bachelor-Thesis-Project/blob/2cba473dc29c4f76d1e17f173ee454b47ae8b677/src/main.cpp) File.

To run a Test for all YOLO Nets simply set multipleTests variable to true in [main.cpp](https://github.com/BLU1337/Bachelor-Thesis-Project/blob/2cba473dc29c4f76d1e17f173ee454b47ae8b677/src/main.cpp) File.

To run a different Test for YOLO Nets alter variable testNum in [main.cpp](https://github.com/BLU1337/Bachelor-Thesis-Project/blob/2cba473dc29c4f76d1e17f173ee454b47ae8b677/src/main.cpp) File.


## Tutorial Functions

To start the normal Tutorial yoe need to remove all Commandline Options.
After that you can change the YOLO Net you want to run the Tutorial with just like you would change a single Net for testing.

Corresponding Munchkincards can be found in [MunchkinCards.cpp](https://github.com/BLU1337/Bachelor-Thesis-Project/blob/2cba473dc29c4f76d1e17f173ee454b47ae8b677/src/MunchkinCards.cpp).

There are some bugs left since this is only a Proof of Concept.
Sometimes Button have to be pressed multiple Times to work.
