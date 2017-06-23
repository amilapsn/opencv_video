/*
Branch: Master
This is currently the stable one
> Fixed time given in waitKey (32 ms)
> Not adaptable for videos with different frame rates  (Only for 25 fps)
*/
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "opencv2/highgui/highgui.hpp"
#include <iostream>

using namespace cv;
using namespace std;


int main(int argc, char* argv[])
{
	CommandLineParser parser(argc, argv, "{@input||}");
	string arg = parser.get<string>("@input");
	if (arg.empty()) {
		return 1;
	}
	VideoCapture cap(arg); // open the video file for reading
	if (!cap.isOpened()) // if not success, exit program
	{
		cout << "Cannot open the video file" << endl;
		return -1;
	}

	double fps = cap.get(CV_CAP_PROP_FPS); //get the frames per seconds of the video
	double delay = 1000 / fps;

	cout << "Frame per seconds : " << fps << endl;

	namedWindow("MyVideo", CV_WINDOW_AUTOSIZE); //create a window called "MyVideo"
	for (;;)
	{
		Mat frame;
		bool bSuccess = cap.read(frame);// read a new frame from video
		if (!bSuccess) //if not success, break loop
		{
			cout << "Cannot read the frame from video file" << endl;
			break;
		}
		imshow("MyVideo", frame); //show the frame in "MyVideo" window
		if (waitKey(32) == 27) //wait for 'esc' key press for 30 ms. If 'esc' key is pressed, break loop
		{
			cout << "esc key is pressed by user" << endl;
			break;
		}
	}
	return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////