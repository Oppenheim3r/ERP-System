#pragma once
#ifndef GROUP2_H
#define GROUP2_H
#include <iostream>
#include "sqlConn.h" 
using namespace std;
      // class products
class Product //: protected customer
{
public:
    Product() {}

protected:
    void DisplayAllProduct(sql::Connection* con);
    void AddProduct(sql::Connection* con);
    bool ProductExists(sql::Connection* con, int productId);
    void UpdateProduct(sql::Connection* con);
    void DeleteProduct(sql::Connection* con);
};

     //  class projects 
class Project {
protected:
    void DisplayAllProjects(sql::Connection* con);
    bool ProjectExists(sql::Connection* con, int projectId);
    void InsertProject(sql::Connection* con);
    void UpdateProject(sql::Connection* con);
    void DeleteProject(sql::Connection* con);
};




#endif // GROUP2_H
