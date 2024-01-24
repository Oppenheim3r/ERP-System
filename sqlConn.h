#pragma once
#ifndef SQLCONN_H
#define SQLCONN_H

#include <mysql_driver.h>
#include <mysql_connection.h>

class Employee;
class JobPosition;
class SalaryManagement;
class Admin;
class HumanResources;

namespace SQLConn {
    sql::Connection* setupMySQL();
    void closeConnection(sql::Connection* con);
}

#endif 