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
		
	protected:
		virtual ~Resource();
		unsigned int uses;
		virtual void Delete() = 0;

};

#endif