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
     //class customer
class Customer {
private:
    int customer_id;

protected:
    void displayAllCustomers(sql::Connection* con);
    void displayCustomerById(sql::Connection* con);
    bool customerExists(sql::Connection* con);
    int insertCustomer(sql::Connection* con);
    void deleteCustomer(sql::Connection* con);
};
      // class Vendor
class Vendor {
private:
    int vendor_id;

protected:
    void displayAllVendors(sql::Connection* con);
    void displayVendorById(sql::Connection* con);
    bool vendorExists(sql::Connection* con);
    int insertVendor(sql::Connection* con);
    void deleteVendor(sql::Connection* con);

};




#endif // GROUP2_H
