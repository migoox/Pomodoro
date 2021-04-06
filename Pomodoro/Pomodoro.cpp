#include "Pomodoro.h"

Pomodoro* Pomodoro::Instance;

void Pomodoro::createQueue(int s, int r)
{
	queue.clear();

	for (int i = 0; i < s; i++)
	{
		queue.push_back(longBreak);
		queue.push_back(focus);
		for (int j = 0; j < r - 1; j++)
		{
			queue.push_back(shortBreak);
			queue.push_back(focus);
		}
	}
}

Pomodoro::Pomodoro()
{
	Instance = this;
	loadTitles();

	endFlag = false;

	// defaut
	rounds = 4;
	sessions = 3;

	longBreak.seconds = 5;
	longBreak.minutes = 0;
	longBreak.name = "LongBrake";

	shortBreak.seconds = 4;
	shortBreak.minutes = 0;
	shortBreak.name = "ShortBrake";

	focus.seconds = 3;
	focus.minutes = 0;
	focus.name = "Focus";

	createQueue(sessions, rounds);
	loadSettings();

	//default
	currentRound = 1;

	Timer::Instance->set(queue.back().minutes, queue.back().seconds);
	Timer::Instance->start();
	loadState();
}

std::string Pomodoro::getImage()
{
	std::string image = queue.back().title + "\n" + "Round: " + std::to_string(currentRound) + " / " + std::to_string(rounds) + " Session: " + std::to_string(int(currentRound/sessions + 1)) + " / " + std::to_string(sessions) + "\n" + "Press \'Space\' to pause and access commands mode.";
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
		nextPeriod();
		Timer::Instance->set(queue.back().minutes, queue.back().seconds);
		Timer::Instance->start();
	}
}

void Pomodoro::nextPeriod()
{
	queue.pop_back();
	if (queue.size() % 2 == 0)
		currentRound = rounds * sessions - int(queue.size() / 2) + 1;
	else
		currentRound = rounds * sessions - int(queue.size() / 2);
}

void Pomodoro::set(int sessions, int rounds)
{
	this->sessions = sessions;
	this->rounds = rounds;
	reset();
}

void Pomodoro::setFocusTimer(int minutes, int seconds)
{
	this->focus.minutes = minutes;
	this->focus.seconds = seconds;
}

void Pomodoro::setShortBreakTimer(int minutes, int seconds)
{
	this->shortBreak.minutes = minutes;
	this->shortBreak.seconds = seconds;
}

void Pomodoro::setLongBreakTimer(int minutes, int seconds)
{
	this->longBreak.minutes = minutes;
	this->longBreak.seconds = seconds;
}

void Pomodoro::reset()
{
	endFlag = false;
	createQueue(rounds, sessions);
	if (queue.size() % 2 == 0)
		currentRound = rounds * sessions - int(queue.size() / 2) + 1;
	else
		currentRound = rounds * sessions - int(queue.size() / 2);
}

std::ostream& operator<<(std::ostream& os, Pomodoro& dt)
{
	os << dt.getImage();
	return os;
}
