#pragma once
#include <map>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
class Timer
{
private:
	int defaultMinutes;
	int defaultSeconds;
	int minutes;
	int seconds;

	float timer;

	bool stopFlag;
	bool endFlag;

	std::map<char, std::string> digits;


public:
	static Timer *Instance;

	Timer();

	void loadDigits();

	std::string getImage();

	void set(int dmin, int dsec);
	void reset();

	void stop();
	void start();

	void update(float dTime);
	
	bool isStopped();
	bool isEnded();
	friend std::ostream& operator<<(std::ostream& os, Timer& dt);
};

