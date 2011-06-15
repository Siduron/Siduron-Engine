#ifndef RESOURCE_H
#define RESOURCE_H
#include <iostream>

class Resource
{
	public:
		Resource();
		virtual void AddUse();
		virtual void SubtractUse();
		virtual int GetUses();
		virtual void Reload() = 0;
		
	protected:
		unsigned int uses;
		std::string path;
		virtual void Delete() = 0;

};

#endif