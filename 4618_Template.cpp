#include "stdafx.h"

#include <string>
#include <iostream>
#include <thread>

#include "Serial.h" // Must include Windows.h after Winsock2.h, so Serial must include after Client/Server
#include "CControl.h"
#include "CBase4618.h"
#include "CPong.h"

// OpenCV Include
#include "opencv.hpp"

// OpenCV Library
#pragma comment(lib,".\\opencv\\lib\\opencv_world310d.lib")

using namespace std;

int main() {

	string comstring = "COM5";

	cv::Size size(800, 500);
	CPong pong(comstring, size);
	pong.run();
	return 0;
}