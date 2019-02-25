#pragma once

#include "stdafx.h"
#include "CControl.h"

// OpenCV Include
#include "opencv.hpp"

// OpenCV Library
#pragma comment(lib,".\\opencv\\lib\\opencv_world310d.lib")

/**
*
* @brief Base class for all ELEX4618 labs 4 - 9
*
* This class is the parent class for CSketch and allows the Etch-a-sketch to run
*
* @author Max Horie
*
*/
class CBase4618 {
protected:
	CControl ctrl;///< CControl object to allow access to its functions
	cv::Mat _canvas;///< OpenCV Mat object to create an image
	float x, y;///< coordinates for the image

public:

	/**
	*
	* @brief Virtual function update to allow CSketch to overload and use
	*
	* @param none
	* @return none
	*
	*/
	virtual void update() = 0;

	/**
	*
	* @brief Virtual function draw to allow CSketch to overload and use
	*
	* @param none
	* @return none
	*
	*/
	virtual void draw() = 0;

	/**
	*
	* @brief Allows the etch-a-sketch program to run
	*
	* @param none
	* @return none
	*
	*/
	void run();

};