#include "stdafx.h"
#include "CBase4618.h"

#include <iostream>

#define DIGITAL 0


using namespace std;

void CBase4618::run() {

	do {
		
		update();
		draw();
		cv::imshow("PONG", _canvas);

	} while (cv::waitKey(1) != 'q');
}