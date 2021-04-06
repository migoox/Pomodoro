#pragma once
#include <string>
#include "App.h"
static class CommandInterpreter
{
private:
	static std::vector<std::string> Separate(std::string input);

public:
	static void Interpret(std::string input);

	static void CResume();
	static void CReset(std::string in);
	static void CSet(std::vector<std::string> command);
	static void CHelp();
};

