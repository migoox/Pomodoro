#pragma once
#include "Timer.h"

struct Period
{
	std::string name;

	int seconds;
	int minutes;
	std::string title;
};

class Pomodoro
{
private:
	int sessions;
	int currentSession;

	int rounds;
	int currentRound;
	
	Period longBreak;
	Period shortBreak;
	Period focus;

	std::vector<Period> queue;

	bool endFlag;

	void createQueue(int s, int r);

public:
	Pomodoro();
	static Pomodoro* Instance;

	std::string getImage();

	void saveCurrentState();
	void loadState();
	void loadSettings();

	void loadTitles();

	void update();

	Period & getPeriod(std::string name);
	Period & getCurrentPeriod();

	void nextPeriod();
	void reset();
	friend std::ostream& operator<<(std::ostream& os, Pomodoro& dt);
};

