#include "Blocks.h"


Blocks::Blocks()
{
	name = "";

	strength = 0;
}

Blocks::~Blocks()
{
}

Blocks::Blocks(const string &name, const int &strength)
{

	this->name = name;

	this->strength = strength;

}// Blocks::Blocks(const string &name, const int &strength)

string Blocks::GetName()const
{
	return this->name;
}
//void Blocks::SetName(const char *name)
//{
//	this->name = name;
//}
//void Blocks::SetName(const string &name)
//{
//	this->name = name;
//}

int Blocks::GetStrength()const
{
	return this->strength;
}
//void Blocks::SetStrength(const int &strength)
//{
//	this->strength = strength;
//}