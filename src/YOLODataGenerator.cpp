#include <YOLODataGenerator.h>
# include "opencv2/opencv.hpp"
# include "opencv2/imgcodecs.hpp"
# include "opencv2/imgproc.hpp"
# include "opencv2/highgui.hpp"


using namespace cv;
using namespace std;


// generate uniform random values
template <typename T>
T unirand(T a, T b)
{
	// random engine for entropy
	thread_local std::random_device rdev;
	thread_local std::mt19937 reng(rdev());
	if constexpr (std::is_integral_v<T>)
	{
		std::uniform_int_distribution<T> dist(a, b);
		return dist(reng);
	}
	else if constexpr (std::is_floating_point_v<T>)
	{
		std::uniform_real_distribution<T> dist(a, b);
		return dist(reng);
	}
}

template <typename T>
T uninorm(T mean, T sdev)
{
	static_assert(std::is_floating_point_v<T>, "uninorm only accepts floating point parameters.");
	// random engine for entropy
	thread_local std::random_device rdev;
	thread_local std::mt19937 reng(rdev());
	std::normal_distribution<T> dist(mean, sdev);
	return dist(reng);
}


int generateDatasetNN()
{
	// constants
	constexpr int num_images = 24000;
	constexpr int num_inputPictures = 10;

	std::vector<cv::Mat> inputPictures;
	std::vector<cv::Mat> backgrounds;
	std::string pictureList;
	//Mat inputPicture = imread("templates/BermudashortsTrans.png", -1);
	//Mat background = imread("backgrounds/background_tech.jpg", -1);
	//cv::resize(inputPicture, inputPicture, cv::Size(), 0.4, 0.4);

	backgrounds.push_back(imread("backgrounds/background_tech.jpg", -1));
	backgrounds.push_back(imread("backgrounds/background_crystal.jpg", -1));
	backgrounds.push_back(imread("backgrounds/background_paper.jpg", -1));
	backgrounds.push_back(imread("backgrounds/background_rock.jpg", -1));
	backgrounds.push_back(imread("backgrounds/background_wall.jpg", -1));
	backgrounds.push_back(imread("backgrounds/background_wood.jpg", -1));

	inputPictures.push_back(imread("templates/Überlebe RagnarökTrans.png", -1));
	inputPictures.push_back(imread("templates/BermudashortsTrans.png", -1));
	inputPictures.push_back(imread("templates/Die Launen des SchicksalsTrans.png", -1));
	inputPictures.push_back(imread("templates/KriegerTrans.png", -1));
	inputPictures.push_back(imread("templates/Magisches FaggotTrans.png", -1));
	inputPictures.push_back(imread("templates/Morgan Le FayTrans.png", -1));
	inputPictures.push_back(imread("templates/PfeiluBogenTrans.png", -1));
	inputPictures.push_back(imread("templates/TrollkinTrans.png", -1));
	inputPictures.push_back(imread("templates/Fenriswolf.png", -1));
	inputPictures.push_back(imread("templates/Schummeln1.png", -1));

	inputPictures.push_back(imread("templates/Zwerg.png", -1));
	inputPictures.push_back(imread("templates/Wunschring1.png", -1));
	inputPictures.push_back(imread("templates/Von Gott Gegeben.png", -1));
	inputPictures.push_back(imread("templates/Aura der Alltäglichkeit.png", -1));
	inputPictures.push_back(imread("templates/Die Gans die goldene Eier legt.png", -1));
	inputPictures.push_back(imread("templates/Dieb1.png", -1));
	inputPictures.push_back(imread("templates/Dieb2.png", -1));
	inputPictures.push_back(imread("templates/Doppelt Gezinkter Würfel.png", -1));
	inputPictures.push_back(imread("templates/Doppelt Gezinkter Würfel2.png", -1));
	inputPictures.push_back(imread("templates/Dosenkeule.png", -1));

	inputPictures.push_back(imread("templates/Drachenhautrüstung.png", -1));
	inputPictures.push_back(imread("templates/Echt starker Bart.png", -1));
	inputPictures.push_back(imread("templates/Einherjer.png", -1));
	inputPictures.push_back(imread("templates/Elf.png", -1));
	inputPictures.push_back(imread("templates/Elf2.png", -1));
	inputPictures.push_back(imread("templates/Faun1.png", -1));
	inputPictures.push_back(imread("templates/Faun2.png", -1));
	inputPictures.push_back(imread("templates/Fauntastische Spiele.png", -1));
	inputPictures.push_back(imread("templates/Gezinkter Würfel1.png", -1));
	inputPictures.push_back(imread("templates/Gezinkter Würfel2.png", -1));

	inputPictures.push_back(imread("templates/Gezinkter Würfel3.png", -1));
	inputPictures.push_back(imread("templates/Gezinkter Würfel4.png", -1));
	inputPictures.push_back(imread("templates/Gladiator1.png", -1));
	inputPictures.push_back(imread("templates/Gladiator2.png", -1));
	inputPictures.push_back(imread("templates/Gladiator3.png", -1));
	inputPictures.push_back(imread("templates/Goldstandarte.png", -1));
	inputPictures.push_back(imread("templates/Grendel.png", -1));
	inputPictures.push_back(imread("templates/Herkules.png", -1));
	inputPictures.push_back(imread("templates/Höllentoupet.png", -1));
	inputPictures.push_back(imread("templates/Jack der Rapper.png", -1));

	inputPictures.push_back(imread("templates/mit rot glühenden Augen.png", -1));
	inputPictures.push_back(imread("templates/Olympisch für das Monster.png", -1));
	inputPictures.push_back(imread("templates/Reptoid.png", -1));
	inputPictures.push_back(imread("templates/Schummeln2.png", -1));
	inputPictures.push_back(imread("templates/Schummeln3.png", -1));
	inputPictures.push_back(imread("templates/Speer der Dichte.png", -1));
	inputPictures.push_back(imread("templates/Steine aus dem Styx.png", -1));
	inputPictures.push_back(imread("templates/Titanisch für das Monster.png", -1));
	inputPictures.push_back(imread("templates/Trugbild.png", -1));
	inputPictures.push_back(imread("templates/Unheiler Gral.png", -1));

	inputPictures.push_back(imread("templates/Untot für Monster.png", -1));
	inputPictures.push_back(imread("templates/Untot für Monster2.png", -1));
	inputPictures.push_back(imread("templates/Waldschrat.png", -1));
	inputPictures.push_back(imread("templates/Walhalla erreichen.png", -1));
	inputPictures.push_back(imread("templates/Wikingerente.png", -1));
	inputPictures.push_back(imread("templates/Wunschring4.png", -1));
	inputPictures.push_back(imread("templates/Wunschring3.png", -1));
	inputPictures.push_back(imread("templates/Wunschring2.png", -1));
	inputPictures.push_back(imread("templates/Wurfnetz.png", -1));
	inputPictures.push_back(imread("templates/Zahnkrone.png", -1));

	inputPictures.push_back(imread("templates/Bürste des Todes.png", -1));
	inputPictures.push_back(imread("templates/Das war doch genau hier.png", -1));
	inputPictures.push_back(imread("templates/Den Fährmann bezahlen.png", -1));
	inputPictures.push_back(imread("templates/Der grosse böse Wolf.png", -1));
	inputPictures.push_back(imread("templates/Die Schau stehlen.png", -1));
	inputPictures.push_back(imread("templates/Donnerkeil.png", -1));
	inputPictures.push_back(imread("templates/Du bist nicht würdig.png", -1));
	inputPictures.push_back(imread("templates/Heldensandwich.png", -1));
	inputPictures.push_back(imread("templates/Toto.png", -1));
	inputPictures.push_back(imread("templates/Zerberus.png", -1));

	std::cout << inputPictures.size() << std::endl;
	for (int p = 0; p < inputPictures.size(); p++)
	{
		if (inputPictures[p].empty())
			cout << "Can't read Template!" << endl;

		cv::resize(inputPictures[p], inputPictures[p], cv::Size(), 0.4, 0.4);
		//cout << "read inputPicture No: " << p << endl;

	}






	//inputPicture.copyTo(background(cv::Rect(0, 0, inputPicture.cols, inputPicture.rows)), mask);
	//imwrite("dataset pictures/aiaiaiai.png", background);
#pragma omp parallel for
	for (int i = 0; i < num_images; i++)
	{
		//int randomCCount = unirand<int>(1, num_inputPictures);//rng.uniform(1, 10);
		int randomCCount = static_cast<int>(std::round(std::max(0.0, std::min(uninorm<double>(10.0, 3.0), 20.0))));
		int randomBackground = unirand<int>(0, 5);
		int beta = unirand<int>(-25, 50);
		double alpha = unirand<double>(0.1, 2.0);
		Mat temp_background;
		string datasetText;
		backgrounds[randomBackground].copyTo(temp_background);
		Mat new_background = Mat::zeros(temp_background.size(), temp_background.type());

		for (int pp = 0; pp < randomCCount; pp++)
		{
			int randomCard = unirand<int>(0, num_inputPictures - 1);
			int randomAngle = unirand<int>(-180, 180);
			double randomSize = std::max(0.3, std::min(uninorm<double>(1.0, 0.1), 1.7));
			int j = 0;
			Mat temp_card;
			inputPictures[randomCard].copyTo(temp_card);

			//cout << randomAngle << endl;

			cv::resize(temp_card, temp_card, cv::Size(), randomSize, randomSize);
			cv::Point2f center((temp_card.cols - 1) / 2.0, (temp_card.rows - 1) / 2.0);
			cv::Mat rot = cv::getRotationMatrix2D(center, randomAngle, 1.0);
			cv::Rect2f bbox = cv::RotatedRect(cv::Point2f(), temp_card.size(), randomAngle).boundingRect2f();

			rot.at<double>(0, 2) += bbox.width / 2.0 - temp_card.cols / 2.0;
			rot.at<double>(1, 2) += bbox.height / 2.0 - temp_card.rows / 2.0;


			cv::Mat rotImage;
			cv::warpAffine(temp_card, rotImage, rot, bbox.size());

			//Mat insetImage(background, Rect(rng.uniform(0, background.cols), rng.uniform(0, background.rows), rng.uniform(inputPicture.rows * 0.10, (double)inputPicture.rows), rng.uniform(inputPicture.cols * 0.10, (double)inputPicture.cols)));

			//Mat insetImage(background, Rect(70, 70, inputPicture.rows, inputPicture.cols));

			vector<cv::Mat> rgbLayer;
			cv::Mat mask;
			split(rotImage, rgbLayer);
			if (rotImage.channels() == 4)
			{
				split(rotImage, rgbLayer);
				cv::Mat cs[3] = { rgbLayer[0], rgbLayer[1], rgbLayer[2] };
				merge(cs, 3, rotImage);
				mask = rgbLayer[3];
			}

			float insertX = unirand<float>(50, temp_background.cols - rotImage.cols);
			float insertY = unirand<float>(50, temp_background.rows - rotImage.rows);
			datasetText += std::to_string(randomCard) + " " + std::to_string((insertX + (rotImage.cols / 2)) / temp_background.cols) + " " + std::to_string((insertY + (rotImage.rows / 2)) / temp_background.rows) + " " + std::to_string(static_cast<float>(rotImage.cols) / temp_background.cols) + " " + std::to_string(static_cast<float>(rotImage.rows) / temp_background.rows) + "\n";

			rotImage.copyTo(temp_background(cv::Rect(insertX, insertY, rotImage.cols, rotImage.rows)), mask);

		}

		Mat mGaussian_noise = Mat(temp_background.size(), CV_8UC3);

		randn(mGaussian_noise, 0, unirand<int>(0, 150));
		temp_background += mGaussian_noise;
		normalize(temp_background, temp_background, 0, 255, CV_MINMAX, CV_8UC3);

		for (int y = 0; y < temp_background.rows; y++)
		{
			for (int x = 0; x < temp_background.cols; x++)
			{
				for (int c = 0; c < temp_background.channels(); c++)
				{
					new_background.at<Vec3b>(y, x)[c] =
						saturate_cast<uchar>(alpha * temp_background.at<Vec3b>(y, x)[c] + beta);
				}
			}
		}
		
		string fileName = "G:\dataset pictures/img";
		fileName += std::to_string(i);
		string fileNamePicture = fileName + ".jpg";
		string fileNameTXT = fileName + ".txt";
		cv::imwrite(fileNamePicture, new_background);

		std::ofstream inputFile(fileNameTXT);
		inputFile << datasetText << endl;
		inputFile.close();

		//pictureList += "data/obj/img" + std::to_string(i) + ".png\n";
		
	}

	for (int i = 0; i < num_images; ++i) pictureList += "data/obj/img" + std::to_string(i) + ".jpg\n";

	std::ofstream inputFile("pictureList.txt");
	inputFile << pictureList << endl;
	inputFile.close();

	/*for (int i = 0; i <= inputPictures.size(); i++)
	{

		if (inputPictures.at(i).empty())
			cout << "Can't read Template!" << i << endl;

		cv::Point2f center((inputPictures[i].cols - 1)/2.0, (inputPictures[i].rows - 1)/2.0);
		cv::RNG rng = theRNG();
		int randomAngle = rng.uniform(-180, 180);

		cout << randomAngle << endl;

		cv::Mat rot = cv::getRotationMatrix2D(center, randomAngle, 1.0);
		cv::Rect2f bbox = cv::RotatedRect(cv::Point2f(), inputPictures[i].size(), randomAngle).boundingRect2f();

		rot.at<double>(0, 2) += bbox.width / 2.0 - inputPictures[i].cols / 2.0;
		rot.at<double>(1, 2) += bbox.height / 2.0 - inputPictures[i].rows / 2.0;

		cv::Mat rotImage;
		cv::warpAffine(inputPictures[i], rotImage, rot, bbox.size());
		string fileName = "dataset pictures/rotated_im";
		fileName += std::to_string(i);
		fileName += ".png";
		cv::imwrite(fileName, rotImage);


	}*/

	return 1;

}