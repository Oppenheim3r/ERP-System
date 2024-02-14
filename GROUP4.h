#pragma once
#ifndef GROUP4_H
#define GROUP4_H
#include <iostream>
#include "sqlConn.h" 
using namespace std;

class User : private OrderProduct, private OrderProject, private Customer {
	int Customer_ID;
	int Product_ID;
	int Project_ID;
	double amount_paid;

public:
	void Services(sql::Connection* con);

};


#endif // GROUP4_H

