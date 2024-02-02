#pragma once
#ifndef GROUP1_H
#define GROUP1_H
#include <iostream>
#include <string>
#include "sqlConn.h"  // Include any necessary headers for SQLConn
using namespace std;
     // class info
class info {
protected:
    int EmployeeID;
    static int EmployeeCount;
    double salary;
    string position;
    string name;
bool EmployeeExists(sql::Connection* con, int);
public:
    info();
};
      //  class Employees
class Employee : protected info {
private:
    string email;

public:
    Employee();
    Employee(string name, int ID, string email, string position);

   
 
};
      // class jobposition
class Jobposition : protected info {
public:
    Jobposition();
protected:
    void DisplayEmpPosition(sql::Connection* con);
    void ChangeEmpPosition(sql::Connection* con);
    void RemoveEmployee(sql::Connection* con);
};

     // class Human Resources
class HumanResources : protected info {
private:
    std::string employee;
    int max_emp;

public:
    HumanResources();
    // Add other public member functions if needed

protected:
    // Only the Admin can access
    void AddEmployee(sql::Connection* con);
    void DisplayAllEmp(sql::Connection* con);
};
     // class Salary Managment
class SalaryManagement : protected Employee {
private:
    int c1;
    int c2;
    int amount;
    float percentage;
    std::string namee;

protected:
    void SalaryDeduction(sql::Connection* con);
    void SalaryBonus(sql::Connection* con);
    double TotalSalaries(sql::Connection* con);
    void ChangeSalary(sql::Connection* con);
};








#endif // GROUP1_H
