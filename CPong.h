#pragma once
#include "stdafx.h"
#include "CBase4618.h"
#include <string>

/**
*
* @brief Enables PONG gameplay
*
* This class, inheriting from CBASE4628, simulates PONG and draws it to the screen
*
* @author Max Horie
*
*/
class CPong: public CBase4618 {
private:
	
	int angle;///< the initial angle at which the ball moves
	int start = 0;///< a variable to hold start conditions for the game
	
	int player1score = 0;///< the player's score
	int computerscore = 0;///< the computer's score
	
	float ball_x;///< the ball's x-coordinate
	float ball_y;///< the ball's y-coordinate
	int velocity_x = 200;///< speed of the ball
	int velocity_y = 200;

	int computer_paddle;///< the computer paddle's location
	int prev_computer_paddle;///< the computer paddle's previous location
	int prev_y;///< the previous location of the joystick value

	double start_tic;///< start time for calculating ball movement and fps
	double elapsed;///< elapsed time for calculating ball movement and fps
	double freq = cv::getTickFrequency();///< frequency of the computer, for timing calculations
	float threads_p_s;///< variable to hold the number of threads per second
	string threadstring = "";///< a string to hold the threads per second

public:

	/**
	*
	* @brief Constructor
	*
	* @param comport The comport to be initialized
	* @param size The size of the screen to play in
	* 
	* @return none
	*
	*/
	CPong(string comport, cv::Size size);

	/**
	*
	* @brief Updates analog joystick position and checks for button presses, also maps the joystick to the canvas size
	*
	* @param none
	* @return none
	*
	*/
	void update();

	/**
	*
	* @brief Draws the paddles, ball, and text on screen, and calculates ball movement and collisions
	*
	* @param none
	* @return none
	*
	*/
	void draw();
};