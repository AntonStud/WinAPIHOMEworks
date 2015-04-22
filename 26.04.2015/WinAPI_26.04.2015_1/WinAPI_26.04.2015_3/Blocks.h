#pragma once

#include <string>

using std::string;


class Blocks
{
private:

	string name;

	int strength;

public:
	Blocks();
	Blocks(const string &name, const int &strength);
	~Blocks();

	string GetName()const;
	/*void SetName(const char *name);
	void SetName(const string &name);*/

	int GetStrength()const;
	//void SetStrength(const int &strength);


};

