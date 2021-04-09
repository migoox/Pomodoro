#include "App.h"

bool App::commandsState;
float App::dTime;

App::App()
{
	t1 = 0;
	t2 = 0;
	dTime = 0;
	commandsState = false;
}

void App::onClose()
{

}

void App::updateInput()
{
	char button;
	if (_kbhit())
	{
		button = _getch();
		if (button == ' ')
		{
			SwitchToCommandsState();
		}
	}
}

void App::update()
{
	if (commandsState)
	{
		std::string input;
		std::cout << "\n>";
		getline(std::cin, input);

		CommandInterpreter::Interpret(input);

		t1 = 0;
		t2 = 0;
		dTime = 0;
	}
	else
	{
		timer.update(dTime);
		pomodoro.update();
	}
}
void App::SwitchToCommandsState()
{
	if (!commandsState)
	{
		commandsState = true;
		Timer::Instance->stop();
	}
}
void App::SwitchToPomodoroState()
{
	if (commandsState)
	{
		commandsState = false;
		dTime = 0;
		Timer::Instance->start();
	}
}
bool App::CommandsState()
{
	return commandsState;
}
void App::RefreshScreen()
{
	if (commandsState)
	{
		system("cls");
		std::cout << *Timer::Instance;
		std::cout << *Pomodoro::Instance;
	}
}
float App::DeltaTime()
{
	return dTime;
}
void App::render()
{
	if (commandsState)
	{

	}
	else
	{
		system("cls");
		std::cout << timer;
		std::cout << pomodoro;
	}
}
void App::run()
{
	while (true)
	{
		if (t1 == 0 || t2 == 0)
			dTime = 0;
		else
			dTime = (t2 - t1) / 1000.f;

		t1 = clock();

		updateInput();
		update();
		render();

		if(!commandsState)
			Sleep(50);

		t2 = clock();
	}
}
