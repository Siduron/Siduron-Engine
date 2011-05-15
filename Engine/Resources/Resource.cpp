#include "Resource.h"

Resource::Resource()
{
	this->uses = 1;
	this->path = "";
}

void Resource::AddUse()
{
	this->uses += 1;
}

void Resource::SubtractUse()
{
	this->uses -= 1;
}

int Resource::GetUses()
{
	return this->uses;
}

Resource::~Resource()
{

}
