#pragma once

#include <string>

using std::string;

class Arms
{
private:

	string name;

	int strength;

public:
	Arms();
	Arms(const string &name, const int &strength);

	~Arms();


	string GetName()const;
	//void SetName(const char *name);
	//void SetName(const string &name);

	int GetStrength()const;
	//void SetStrength(const int &strength);

};

