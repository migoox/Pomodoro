#include "CommandInterpreter.h"

std::vector<std::string> CommandInterpreter::Separate(std::string input)
{
	std::vector<std::string> vec;
	while (input.find(" ") != std::string::npos)
	{
		int pos = input.find(" ");
		vec.push_back(input.substr(0, pos));
		input = input.substr(pos + 1);
	}
	vec.push_back(input);
	return vec;
}

void CommandInterpreter::Interpret(std::string input)
{
	std::vector<std::string> command = Separate(input);
	
	if (command.size() == 0)
		return;

	if (command[0] == "resume" || command[0] == "r")
	{
		CResume();
	}
	else if (command[0] == "reset" || command[0] == "rs")
	{
		if (command.size() == 1)
			CReset("timer");
		else
			CReset(command[1]);
	}
	else if (command[0] == "help" || command[0] == "h")
	{
		CHelp();
	}
	else if (command[0] == "set" || command[0] == "s")
	{
		CSet(command);
	}
	else if (command[0] == "skip" || command[0] == "sk")
	{
		CSkip();
	}
	else
	{
		std::cout << "uknown command, try \"help\"\n";
	}
}

void CommandInterpreter::CResume()
{
	App::SwitchToPomodoroState();
}

void CommandInterpreter::CReset(std::string in)
{
	if (in == "pomodoro")
	{
		Pomodoro::Instance->reset();
	}
	else
	{
		Pomodoro::Instance->resetTimer();
	}
	App::RefreshScreen();
}

void CommandInterpreter::CSet(std::vector<std::string> command)
{
	auto fail = []() { return "set command failed"; };

	if (command.size() == 4)
	{
		int minutes, seconds;
		bool failStatus = false;
		try
		{
			minutes = std::stoi(command[2]);
			seconds = std::stoi(command[3]);
		}
		catch (...)
		{
			fail();
			failStatus = true;
		}
		if (!failStatus)
		{
			if (command[1] == "short_break")
			{
				Pomodoro::Instance->setShortBreakTimer(minutes, seconds);
			}
			else if (command[1] == "long_break")
			{
				Pomodoro::Instance->setLongBreakTimer(minutes, seconds);
			}
			else if (command[1] == "focus")
			{
				Pomodoro::Instance->setFocusTimer(minutes, seconds);
			}
			else
			{
				std::cout << fail();
			}
		}
		else
		{
			std::cout << fail();
		}
	}
	else if (command.size() == 3)
	{
		int amount;
		bool failStatus = false;
		try
		{
			amount = std::stoi(command[2]);
		}
		catch (...)
		{
			fail();
			failStatus = true;
		}

		if (command[1] == "rounds")
		{
			Pomodoro::Instance->setAmountOfRounds(amount);
		}
		else if (command[1] == "sessions")
		{
			Pomodoro::Instance->setAmountOfSessions(amount);
		}
		else
		{
			std::cout << fail();

		}

	}
	else
	{
		std::cout<< fail();
	}
	App::RefreshScreen();
}

void CommandInterpreter::CSkip()
{
	Pomodoro::Instance->nextPeriod();
	App::RefreshScreen();

}

void CommandInterpreter::CHelp()
{
	std::cout << "COMMAND LIST: \n resume(r) - programm returns to pomodoro.\n";
	std::cout << "\n reset(rs) timer - resets timer.\n";
	std::cout << "\n reset(rs) pomodoro - resets pomodoro\n";
	std::cout << "\n set(s) [period_type] [minutes] [seconds] - sets timers on chosen period.\n";
	std::cout << "\n set(s) rounds [amount_of_rounds] - sets amount of rounds. WARNING: COMMAND RESETS YOUR PROGRESS\n";
	std::cout << "\n set(s) sessions [amount_of_sessions] - sets timers on chosen period. WARNING: COMMAND RESETS YOUR PROGRESS\n";
	std::cout << "\n skip(sk) - skips current period\n";
}


