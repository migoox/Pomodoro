#include "Timer.h"
#include <iostream>
Timer* Timer::Instance;

std::string Timer::getImage()
{
	int min = minutes;
	int sec = seconds;
	char a;
	char b;
	char c;
	char d;
	if (min / 10 < 1)
	{
		a = '0';
		b = min + '0';
	}
	else
	{
		int l1 = min / 10;
		int l2 = min % 10;
		a = l1 + '0';
		b = l2 + '0';
	}
	if (sec / 10 < 1)
	{
		c = '0';
		d = sec + '0';
	}
	else
	{
		int l1 = sec / 10;
		int l2 = sec % 10;
		c = l1 + '0';
		d = l2 + '0';
	}
	std::istringstream as(this->digits[a]);
	std::istringstream bs(this->digits[b]);
	std::istringstream cs(this->digits[c]);
	std::istringstream ds(this->digits[d]);
	std::istringstream ms(this->digits[':']);
	std::string al = "";
	std::string bl = "";
	std::string cl = "";
	std::string dl = "";
	std::string ml = "";
	std::string result = "";
	while (getline(as, al))
	{
		getline(bs, bl);
		getline(cs, cl);
		getline(ds, dl);
		getline(ms, ml);
		result += al + bl + ml + cl + dl + "\n";
	}
	return result;
}

Timer::Timer()
{
	minutes = 0;
	seconds = 0;
	defaultMinutes = 5;
	defaultSeconds = 0;
	stopFlag = true;
	endFlag = false;
	Instance = this;

	loadDigits();

	timer = 0;

}

void Timer::loadDigits()
{
	std::fstream file;
	file.open("digits.txt", std::ios::in);
	if (file.is_open())
	{
		for (int i = 0; i <= 10; i++)
		{
			std::string digit = "";
			std::string line = "";
			do
			{
				if (line != "")
					digit += "\n" + line;
				line = "";
				getline(file, line);
			} while (line[0] != '*');
			
			if(i == 10)
				this->digits[':'] = digit;
			else
				this->digits[i + '0'] = digit;
		}
	}
	else
	{
		for (int i = 0; i <= 9; i++)
		{
			std::string digit = "" + char(i + '0');
			this->digits[i + '0'] = digit;
		}
		this->digits[':'] = ":";
	}
	file.close();
}


void Timer::set(int dmin, int dsec)
{
	defaultMinutes = dmin;
	defaultSeconds = dsec;
	timer = 0;
	reset();
}

void Timer::reset()
{
	minutes = defaultMinutes;
	seconds = defaultSeconds;
	timer = 0;
	endFlag = false;
}

void Timer::stop()
{
	stopFlag = true;
}

void Timer::start()
{
	stopFlag = false;
}

void Timer::update(float dTime)
{
	if (!stopFlag && !endFlag)
	{
		timer += dTime;
		if (timer >= 1.f)
		{
			timer = timer - 1.f;
			if (seconds > 0)
				seconds--;
			else if (seconds == 0)
			{
				if (minutes == 0)
				{
					endFlag = true;
					stopFlag = true;
				}
				else
				{
					minutes--;
					seconds = 59;
				}
			}
		}
	}

}
bool Timer::isStopped()
{
	return stopFlag;
}

bool Timer::isEnded()
{
	return endFlag;
}

std::ostream& operator<<(std::ostream& os, Timer& obj)
{
	os << obj.getImage();
	return os;
}
