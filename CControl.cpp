#include "stdafx.h"
#include <string>
#include <iostream>
#include <iomanip>
#include "CControl.h"
#include "opencv.hpp"
#include <sstream>
#include <tuple>

#define MAX_X 1015.0
#define MIN_X 10.0
#define MAX_Y 1024.0
#define MIN_Y 20.0

using namespace std; 

enum { DIGITAL = 0, ANALOG, SERVO };

void CControl::init_com(string s) {

	_com.open(s);
	_com.flush();
}

bool CControl::get_data(int type, int channel, int &value) {

	string tx_str, rx_str;
	stringstream s;

	s << "G " << type << " " << channel << "\n";
	tx_str = s.str();

	_com.write(tx_str.c_str(), tx_str.length());

	// temporary storage
	char buff[2];
	// Send TX string
	//_com.write(tx_str.c_str(), tx_str.length());
	Sleep(10); // not needed?

	rx_str = "";
	// start timeout count
	double start_time = GetTickCount();

	buff[0] = 0;
	// If 1 byte was read then print to screen, timeout after 1 second
	while (buff[0] != '\n' && (GetTickCount() - start_time) / cv::getTickFrequency() < 1.0) {

		if (_com.read(buff, 1) > 0) {

			rx_str = rx_str + buff[0];
		}
	}

	rx_str.erase(0, rx_str.find(" ") + 1);
	rx_str.erase(0, rx_str.find(" ") + 1);
	rx_str.erase(0, rx_str.find(" ") + 1);
	value = stoi(rx_str);

	cv::waitKey(1);
	return TRUE;
}

bool CControl::set_data(int type, int channel, int value) {

	std::string tx_str;
	stringstream s;

	s << "S " << type << " " << channel << " " << value << "\n";
	tx_str = s.str();
	_com.write(tx_str.c_str(), tx_str.length());
	_com.flush();
	
	cv::waitKey(1);
	return TRUE;
}

int CControl::get_button(int channel) {

	int value;

	get_data(DIGITAL, channel, value);

	if (value == 0) {

		float start_time = GetTickCount();

		get_data(DIGITAL, channel, value);

		if (value == 0 && (GetTickCount() - start_time > 300)) {

			return value;
		}
		else { return value; }
	}
	else { return value; }
}

tuple<float, float> CControl::get_analog() {
	
	float analog_percent_x, analog_percent_y;
	int value;

	get_data(ANALOG, 9, value);
	analog_percent_y = ((MAX_Y - value + MIN_Y) / (MAX_Y - MIN_Y));
	cout << setprecision(2) << fixed << "ANALOG TEST : CH: " << 9 << "= " << value << " (" << analog_percent_y << "%)  ";

	get_data(ANALOG, 15, value);
	analog_percent_x = ((value - MIN_X) / (MAX_X - MIN_X));
	cout << setprecision(2) << fixed << setw(20) << "ANALOG TEST : CH: " << 15 << "= " << value << "(" << analog_percent_x << "%)" << endl;

	return make_tuple(analog_percent_x, analog_percent_y);
}

void CControl::set_digital() {

	int digital1, digital2, value, val;

	cout << "Enter button pin number: ";
	cin >> digital1;

	cout << "Enter LED pin number: ";
	cin >> digital2;

	while (1) {

		get_data(DIGITAL, digital1, value);
		if (value == 1)
		{
			val = 0;
			set_data(DIGITAL, digital2, val);
			
		}
		else if (value == 0)
		{
			val = 1;
			set_data(DIGITAL, digital2, val);
			
		}
		cout << "DIGITAL TEST: CH" << digital1 << " = " << value << endl;

		_com.flush();
	}
}
