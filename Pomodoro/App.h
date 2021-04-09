#pragma once
#include "Pomodoro.h"
#include "CommandInterpreter.h"
#include <iostream>
#include <windows.h>
#include <conio.h>

class App
{
private:

	float t1, t2;
	
	Timer timer;
	Pomodoro pomodoro;

	static bool commandsState;
	static float dTime;
public:
	App();
	void onClose();
	void updateInput();
	void update();
	void render();
	void run();

	static void SwitchToCommandsState();
	static void SwitchToPomodoroState();
	static bool CommandsState();
	static void RefreshScreen();
	static float DeltaTime();
};

