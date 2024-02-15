#pragma once
#ifndef GROUP4_H
#define GROUP4_H
#include <iostream>
#include "GROUP3.h"
#include "sqlConn.h" 
using namespace std;

class User final : private OrderProduct, private OrderProject, private Customer {
	int Customer_ID;
	int Product_ID;
	int Project_ID;
	double amount_paid;

public:
	void Services(sql::Connection* con);

};
       // class Admin 
class Admin final : private HumanResources, private Jobposition, private Employee, private SalaryManagement, private Product, private Project, private Customer,
	private Vendor, private OrderProduct, private OrderProject, private WorkOn, private FinancialManagement, private Logs, private Quality, private ProductsToOrder, private AddingEmployeesToWork {
public:
	void opreation(sql::Connection* con);
};
  // class EMP
class EMP final : private HumanResources, private Jobposition, private Employee, private Product, private Project, private Customer,
	private Vendor, private OrderProduct, private OrderProject, private WorkOn, private FinancialManagement, private Quality, private ProductsToOrder {
public:
	void Control(sql::Connection* con);
};


#endif // GROUP4_H

