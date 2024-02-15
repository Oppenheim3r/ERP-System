#pragma once
#ifndef GROUP3_H
#define GROUP3_H
#include <iostream>
#include "sqlConn.h" 
using namespace std;

#include "GROUP1.h"
#include "GROUP2.h"
#include <mysql_connection.h>

class FinancialManagement : public SalaryManagement {
protected:
    void Display_Budget_table(sql::Connection* con);
    void ChangeBudgets(sql::Connection* con);
    void EmployeeBudgetStatues(sql::Connection* con);
    void ProductBudgetStatues(sql::Connection* con);
    void displayProductsToBuy(sql::Connection* con);
    void insertProductToBuy(sql::Connection* con);
    void approveProduct(sql::Connection* con);
    void editProductPrice(sql::Connection* con);
};
class Logs {
protected:
    void view_logs(sql::Connection* con);
};
class Quality {
protected:
    void profit_and_loss(sql::Connection* con);
    void Most_Requested_Product(sql::Connection* con);
    void Most_Requested_Project(sql::Connection* con);
};
#endif //GROUP3_H


