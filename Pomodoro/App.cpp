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
		cls();
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
			Sleep(70);

		t2 = clock();
	}
}

void App::cls()
{
	// Get the Win32 handle representing standard output.
	// This generally only has to be done once, so we make it static.
	static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	COORD topLeft = { 0, 0 };

	// std::cout uses a buffer to batch writes to the underlying console.
	// We need to flush that to the console because we're circumventing
	// std::cout entirely; after we clear the console, we don't want
	// stale buffered text to randomly be written out.
	std::cout.flush();

	// Figure out the current width and height of the console window
	if (!GetConsoleScreenBufferInfo(hOut, &csbi)) {
		// TODO: Handle failure!
		abort();
	}
	DWORD length = csbi.dwSize.X * csbi.dwSize.Y;

	DWORD written;

	// Flood-fill the console with spaces to clear it
	FillConsoleOutputCharacter(hOut, TEXT(' '), length, topLeft, &written);

	// Reset the attributes of every character to the default.
	// This clears all background colour formatting, if any.
	FillConsoleOutputAttribute(hOut, csbi.wAttributes, length, topLeft, &written);

	// Move the cursor back to the top left for the next sequence of writes
	SetConsoleCursorPosition(hOut, topLeft);
}
