#include "Arms.h"


Arms::Arms()
{
	name = "";

	strength = 0;
}

Arms::Arms(const string &name, const int &strength)
{
	this->name = name;

	this->strength = strength;
}


Arms::~Arms()
{
}


string Arms::GetName()const
{
	return this->name;
}
//void Arms::SetName(const char *name)
//{
//	this->name = name;
//}
//void Arms::SetName(const string &name)
//{
//	this->name = name;
//}

int Arms::GetStrength()const
{
	return this->strength;
}
//void Arms::SetStrength(const int &strength)
//{
//	this->strength = strength;
//}