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
	int rounds;

	int currentRound;
	
	Period longBreak;
	Period shortBreak;
	Period focus;

	std::vector<Period*> queue;

	bool endFlag;

	void createQueue(int s, int r);

public:
	static Pomodoro* Instance;

	Pomodoro();

	std::string getImage();
	void set(int sessions, int rounds);
	void setAmountOfSessions(int amount);
	void setAmountOfRounds(int amount);
	void setFocusTimer(int minutes, int seconds);
	void setShortBreakTimer(int minutes, int seconds);
	void setLongBreakTimer(int minutes, int seconds);

	void saveCurrentState();
	void loadState();
	void loadSettings();
	void loadTitles();

	void update();

	void resetTimer();
	void nextPeriod();
	void reset();

	friend std::ostream& operator<<(std::ostream& os, Pomodoro& dt);
};

