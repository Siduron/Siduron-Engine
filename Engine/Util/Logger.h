#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <iostream>

enum Messagetype
{
	Warning,
	Info,
	Error
};

class Logger
{
	public:
		static Logger* Instance();
		static void Log(std::string message, Messagetype type);
		static void Progress();
		~Logger();
	private:
		Logger();
		static Logger* pInstance;
};
#endif