#include "Employee.h"

Employee::Employee()
{
	name = "";
	fee = 0.0;
}// Employee::Employee()

Employee::Employee(const string &name, const double &fee)
{
	this->name = name;
	this->fee = fee;
}// Employee::Employee(const string &name, const double &fee)

Employee::~Employee()
{
}// Employee::~Employee()

// copy constr
Employee::Employee(const Employee&worker)
{
	this->name = worker.name;

	this->fee = worker.fee;

}// Employee::Employee(const Employee&worker)




//string Employee::GetInfoInStr()
//{
//	string info = name + " | ";
//
//	info += std::to_string(fee);
//
//	return info;
//}// string Employee::EmployeeGetInfoInStr()


string Employee::GetInfoInStr()
{
	string info = name + " | ";

	int BUFF = std::to_string(fee).size();
	// нужна проверка на выделение памяти
	char* buff = new char[BUFF];
	sprintf(buff, "%.2f", fee);

	info += buff;
	delete buff;
	return info;

}// string Employee::GetInfoInChar()



double Employee::GetFee()const
{
	return fee;

}//double& Employee::GetFee()const 

string Employee::GetName()const
{

	return name;

}// string  Employee::GetName()

//bool operator == (const Employee &worker1, const Employee &worker2)
//{
//	return worker1.name == worker2.name;
//
//}// bool operator < (const Employee &worker)