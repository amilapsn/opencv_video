/*
Branch : PID_method
> This brach used Simple PID to maintain framerate
> This may be an overkill, but this is done to get a feel about PID
*/
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <windows.h>

using namespace cv;
using namespace std;

double PCFreq = 0.0;
__int64 CounterStart = 0;

// variables for PID controller
double pid[3] = { 1, 0, 0 };	// this will hold K_p, K_i and K_d values (shud be tuned)
double p, i, d;					// proportional, integral and differential values
double e[2];					// saving error
int toggle = 0;						// to jump between e[0] and e[1]

void StartCounter()
{
	LARGE_INTEGER li;
	if (!QueryPerformanceFrequency(&li))
		cout << "QueryPerformanceFrequency failed!\n";

	PCFreq = double(li.QuadPart) / 1000.0;

	QueryPerformanceCounter(&li);
	CounterStart = li.QuadPart;
}
double GetCounter()
{
	LARGE_INTEGER li;
	QueryPerformanceCounter(&li);
	return double(li.QuadPart - CounterStart) / PCFreq;
}

int main(int argc, char* argv[])
{
	CommandLineParser parser(argc, argv, "{@input||}");
	string arg = parser.get<string>("@input");
	if (arg.empty()) {
		//help(av);
		return 1;
	}
	VideoCapture cap(arg);		// open the video file for reading
	if (!cap.isOpened())		// if not success, exit program
	{
		cout << "Cannot open the video file" << endl;
		return -1;
	}
	cap.set(CV_CAP_PROP_POS_MSEC, 300);			//start the video at 300ms

	double fps = cap.get(CV_CAP_PROP_FPS);		//get the frames per seconds of the video
	double delay = 1000 / fps;					//this is the delay that sould be between 2 frames to keep framerate

	cout << "Frame per seconds : " << fps << endl;

	namedWindow("MyVideo", CV_WINDOW_AUTOSIZE);	//create a window called "MyVideo"
	Mat frame;
	for (;;)
	{
		StartCounter();
		bool bSuccess = cap.read(frame);		// read a new frame from video
		if (!bSuccess)							//if not success, break loop
		{
			cout << "Cannot read the frame from video file" << endl;
			break;
		}
		imshow("MyVideo", frame);				//show the frame in "MyVideo" window
		if (waitKey(delay - GetCounter()) == 27)//wait for 'esc' key press for 30 ms. If 'esc' key is pressed, break loop
		{
			cout << "esc key is pressed by user" << endl;
			break;
		}

	}
	return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////