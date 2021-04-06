#include "Pomodoro.h"

Pomodoro* Pomodoro::Instance;

Pomodoro::Pomodoro()
{
	Instance = this;
	loadTitles();

	endFlag = false;

	// defaut
	rounds = 4;
	sessions = 3;
	currentSession = 1;

	longBreak.seconds = 0;
	longBreak.minutes = 25;
	longBreak.name = "LongBrake";

	shortBreak.seconds = 0;
	shortBreak.minutes = 4;
	shortBreak.name = "ShortBrake";

	focus.seconds = 30;
	focus.minutes = 27;
	focus.name = "Focus";
	loadSettings();

	//default
	currentPeriod = focus;
	currentRound = 1;
	currentSession = 1;

	Timer::Instance->set(currentPeriod.minutes, currentPeriod.seconds);
	Timer::Instance->start();
	loadState();
}

std::string Pomodoro::getImage()
{
	std::string image = currentPeriod.title + "\n" + "Round: " + std::to_string(currentRound) + " / " + std::to_string(rounds) + " Session: " + std::to_string(currentSession) + " / " + std::to_string(sessions) + "\n" + "Press \'Space\' to pause and access commands mode.";
	return image;
}

void Pomodoro::loadState()
{
	;
}

void Pomodoro::loadSettings()
{
	;
}

void Pomodoro::loadTitles()
{
	std::fstream file;
	file.open("titles.txt", std::ios::in);
	if (file.is_open())
	{
		std::string title = "";
		std::string line = "";
		do
		{
			if (line != "")
				title += "\n" + line;
			line = "";
			getline(file, line);
		} while (line[0] != '*');
		focus.title = title;
		title = "";
		line = "";
		do
		{
			if (line != "")
				title += "\n" + line;
			line = "";
			getline(file, line);
		} while (line[0] != '*');
		longBreak.title = title;
		shortBreak.title = title;
	}
	else
	{
		longBreak.title = "Long Break";
		shortBreak.title = "Short Break";
		focus.title = "Focus";
	}
	file.close();
}

void Pomodoro::update()
{
	if (Timer::Instance->isEnded())
	{
		if (currentPeriod.name == focus.name) // FOCUS	
		{
			if (currentRound == rounds)
			{
				currentPeriod = longBreak;
			}
			else
			{
				currentPeriod = shortBreak;
			}
		}
		else if (currentPeriod.name == shortBreak.name) // SHORT BRAKE
		{
			currentRound++;
			currentPeriod = focus;
		}
		else // LONG BRAKE
		{
			currentRound = 1;
			if (currentSession == sessions)
			{
				endFlag = true;
			}
			else
			{
				currentSession++;
				currentPeriod = focus;
			}
		}
		if (!endFlag)
		{
			Timer::Instance->set(currentPeriod.minutes, currentPeriod.seconds);
			Timer::Instance->start();
		}
	}
}

Period & Pomodoro::getPeriod(std::string name)
{
	if (name == "Focus")
	{
		return focus;
	}
	else if (name == "LongBreak")
	{
		return longBreak;
	}
	else if ("ShortBreak")
	{
		return shortBreak;
	}
	else
	{
		return currentPeriod;
	}
}

Period& Pomodoro::getCurrentPeriod()
{
	return currentPeriod;
}

void Pomodoro::reset()
{
	endFlag = false;
	currentRound = 0;
	currentSession = 0;
	currentPeriod = focus;
}

std::ostream& operator<<(std::ostream& os, Pomodoro& dt)
{
	os << dt.getImage();
	return os;
}
