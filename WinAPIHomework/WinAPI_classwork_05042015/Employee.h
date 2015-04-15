#pragma once

#include <string>

using std::string;

class Employee
{
private:

	string name;

	double fee;

public:

	Employee();

	~Employee();

	Employee(const string &name, const double &fee);

	Employee(const Employee&worker);

	Employee& operator = (const Employee &worker)
	{
		if (this != &worker)
		{ 
		name = worker.name;

		fee = worker.fee;
		}
		return *this;

	}// Employee& operator = (const Employee &worker)

	bool operator < (const Employee &worker)//const
	{
		return this->name < worker.name;

	}// bool operator < (const Employee &worker)

	//friend bool operator == (const Employee &worker1, const Employee &worker2);

	bool operator == (const Employee &worker2)
		{
			return this->name == worker2.name;
		
		}// bool operator < (const Employee &worker)


	//Getters

	string GetInfoInStr();

	string GetName() const;

	//char* GetInfoInChar();

	double GetFee()const;

};


