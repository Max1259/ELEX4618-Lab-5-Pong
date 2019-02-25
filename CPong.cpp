#include "stdafx.h"
#include "CPong.h"

#include <time.h>
#include <chrono>
#include <thread>
#include <sstream>
#include <iomanip>
#include <math.h>

// OpenCV Include
#include "opencv.hpp"

// OpenCV Library
#pragma comment(lib,".\\opencv\\lib\\opencv_world310d.lib")

#define PADDLE_EXTENSION	40
#define COMPUTER_PADDLE_EXT 40
#define DIGITAL				0
#define FPS					32
#define PI					3.1415926
#define BALL_RADIUS			10
#define PLAYER_DISTANCE		3
#define COMPUTER_DISTANCE	4
#define PADDLE_WIDTH		4

CPong::CPong(string comport, cv::Size size) {

	ctrl.init_com(comport);

	_canvas = cv::Mat::zeros(size, CV_8UC3);
}

void CPong::update() {

	//check button state, if active reset the game
	if (ctrl.get_button(32) == 0) {
		start = 0;
		computerscore = 0;
		player1score = 0;
	}

	//set previous value to current
	prev_y = y;
	prev_computer_paddle = computer_paddle;

	//return x and y joystick values
	tie(x, y) = ctrl.get_analog();

	//fit joystick value to canvas height
	y = y * _canvas.size().height;

	//don't let paddle go beyond upper and lower canvas limits
	if ((y - PADDLE_EXTENSION) < PADDLE_EXTENSION) {
		y = PADDLE_EXTENSION + 1; 
	}
	if ((y + PADDLE_EXTENSION) > _canvas.size().height - PADDLE_EXTENSION) { 
		y = _canvas.size().height - (PADDLE_EXTENSION + 1); 
	}
	computer_paddle = ball_y;

	//don't let computer paddle go beyond upper and lower limits
	if (computer_paddle < COMPUTER_PADDLE_EXT) {
		computer_paddle = COMPUTER_PADDLE_EXT + 1;
	}
	if (computer_paddle + COMPUTER_PADDLE_EXT > _canvas.size().height) {
		computer_paddle = _canvas.size().height - (COMPUTER_PADDLE_EXT + 1);
	}

	//choose random direction for computer paddle to move
	//srand(time(NULL));
	//int dir = rand() % 2 + 1;

	//if (dir == 1) {
	//	computer_paddle += 10;
	//}
	//else {
	//	computer_paddle -= 10;
	//}
}

void CPong::draw() {

	_canvas = cv::Mat::zeros(cv::Size(800,500), CV_8UC3);

	//set thread time to 33 ms
	auto end_time = chrono::system_clock::now() + chrono::milliseconds(FPS);

	//get ticks to calculate x and y ball values
	start_tic = cv::getTickCount();

	//redraw paddles in new locations
	cv::line(_canvas, cv::Point(PLAYER_DISTANCE, y - PADDLE_EXTENSION), cv::Point(PLAYER_DISTANCE, y + PADDLE_EXTENSION), cv::Scalar::all(255), PADDLE_WIDTH, CV_AA);
	cv::line(_canvas, cv::Point(_canvas.size().width - COMPUTER_DISTANCE, computer_paddle - COMPUTER_PADDLE_EXT), cv::Point(_canvas.size().width - COMPUTER_DISTANCE, computer_paddle + COMPUTER_PADDLE_EXT), cv::Scalar::all(255), PADDLE_WIDTH, CV_AA);

	cv::putText(_canvas, "P O N G", cv::Point(317, 30), cv::FONT_HERSHEY_DUPLEX, 1, cv::Scalar::all(255), 1, CV_AA);

	//set current score strings
	string playerscore = "Player 1: " + to_string(player1score);
	string computer = "Computer: " + to_string(computerscore);

	//draw score
	cv::putText(_canvas, playerscore, cv::Point(100, 50), cv::FONT_HERSHEY_DUPLEX, 0.4, cv::Scalar::all(255), 1, CV_AA);
	cv::putText(_canvas, computer, cv::Point(580, 50), cv::FONT_HERSHEY_DUPLEX, 0.4, cv::Scalar::all(255), 1, CV_AA);

	//first time through, or after reset/game win
	if (start == 0) {

		ball_x = _canvas.size().width / 2;
		ball_y = _canvas.size().height / 2;

		cv::circle(_canvas, cv::Point(ball_x, ball_y), BALL_RADIUS, cv::Scalar::all(255), -1, CV_AA);

		//srand(time(NULL));
		//angle = rand() % 30 + 25;
		start++;
	}

	ball_x += elapsed * velocity_x;// abs(cos(angle * PI / 180));
	ball_y += elapsed * velocity_y;// abs(sin(angle * PI / 180));

	//collisions 
	if (ball_y > _canvas.size().height - 14) {
		
		velocity_y = -velocity_y;
	}
	if (ball_y < 14) {

		velocity_y = -velocity_y;
	}
	if (ball_x < 20) {
		if ((ball_y < y + 45) && (ball_y > y - 45)) {

			velocity_x = -velocity_x;
			
		}
		else if (ball_x < -10) {

			if (computerscore < 4) {

				computerscore++;
			}
			else {
				computerscore = 0;
				player1score = 0;
			}

			start = 0;
		}
	}

	if (ball_x > _canvas.size().width - 18) {

		if ((ball_y < computer_paddle + 45) && (ball_y > computer_paddle - 45)) {

			velocity_x = -velocity_x;
		}
		else if (ball_x - 10 > _canvas.size().width) {

			if (player1score < 4) {

				player1score++;
			}
			else {

				computerscore = 0;
				player1score = 0;
			}

			start = 0;
		}
	}

	//draw ball
	cv::circle(_canvas, cv::Point(ball_x, ball_y), BALL_RADIUS, cv::Scalar::all(255), -1, CV_AA);

	//sleep until set end time
	this_thread::sleep_until(end_time);

	//find new FPS, print to canvas
	elapsed = (cv::getTickCount() - start_tic) / freq;
	threads_p_s = 1 / elapsed;
	stringstream s;
	s << fixed << setprecision(2) << threads_p_s;
	threadstring = s.str() + " FPS";
	cv::putText(_canvas, threadstring, cv::Point(350, 50), cv::FONT_HERSHEY_DUPLEX, 0.4, cv::Scalar::all(255), 1, CV_AA);

}