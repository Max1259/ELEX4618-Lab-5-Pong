#pragma once

#include "Serial.h"

#include <string>
#include <tuple>

using namespace std;

/**
*
* @brief Controls Serial IO functions on the MSP432
*
* This class initializes the com port that it's passed, verifies that data has been sent or received, 
* and has functions to get analog and digital data
*
* @author Max Horie
*
*/
class CControl {

private:
	Serial _com;///< Serial object to access Serial Class functions

public: 

	/** @brief Initializes a com port
	*
	* @param s String of comport to initialize
	* @return nothing to return
	*/
	void init_com(string s);

	/** @brief Function to verify that data has been received and returns the value
	*
	* @param type Digital, Analog or Servo
	* @param channel The channel to be read from
	* @param value The memory location of the value received
	* 
	* @return bool Returns true if data is received
	*/
	bool get_data(int type, int channel, int &value);

	/** @brief Function to verify that data has been transmitted
	*
	* @param type Digital, Analog or Servo
	* @param channel The channel to be read from
	* @param value The data value sent to the channel
	*
	* @return bool Returns true if data is transmitted 
	*/
	bool set_data(int type, int channel, int value);

	/** @brief Function to debounce digital input
	*
	* @param channel The desired channel of the pushbutton
	* @return int the value of the button
	*/
	int get_button(int channel);

	/** @brief Function to receive analog data and interpret it as a percent
	*
	* @param no parameters
	* @return tuple<float, float> decimal value between 0 and 1 denoting positions of x and y
	*/
	tuple<float, float> get_analog();

	/** @brief Function to test digital input state
	*
	* @param no parameters
	* @return nothing to return
	*/
	void set_digital();

};
