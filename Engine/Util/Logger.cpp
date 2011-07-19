#include "Logger.h"

Logger* Logger::pInstance = NULL;
 
Logger* Logger::Instance()
{
	if(pInstance == NULL)
	{
		pInstance = new Logger();
	}
	return pInstance;
}

Logger::Logger()
{

}

void Logger::Log(std::string message, Messagetype type)
{
	if(type == Info)std::cout << "}"+ message + "\n";
	if(type == Warning)std::cout << "*WARNING* "+ message + "\n";
	if(type == Error)std::cout << "**ERROR** "+ message + "\n";
}

void Logger::Progress()
{
	std::cout << ".";
}

Logger::~Logger()
{
  if(pInstance != 0)delete pInstance;
}