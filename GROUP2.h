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
 void displayProductById(int proId, sql::Connection* con);
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
    void displayProjectById(int proId, sql::Connection* con);
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
    int insertCustomer(bool& check, sql::Connection* con);
    bool Login(int& customer_id, sql::Connection* con);
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
class OrderProject : protected Project {
public:
    void displayAllOrders(sql::Connection* con);
    bool orderExistsById(int orderId, sql::Connection* con);
    void displayOrderById(int orderId, sql::Connection* con);
    void editOrder(sql::Connection* con);
    void removeOrder(sql::Connection* con);
    void addOrder(sql::Connection* con);
};
// class OrederProduct
class OrderProduct : public Product {
private:
    int productID;

protected:
    void DisplayAllProduct(sql::Connection* con);
    bool CheckTheQuantity(int proId, int quantity, sql::Connection* con);
    double CalculationTheAmount(int proId, int quantity, sql::Connection* con);
    void AddOrderProduct(int proId, int cumtomerId, int quantity, double amount_paid, double Total, sql::Connection* con);
    void DisplayAllProductOrders(sql::Connection* con);
    bool ProductOrderExistsById(int orderId, sql::Connection* con);
    void DisplayProductOrderById(int orderId, sql::Connection* con);
    void RemoveProductOrder(sql::Connection* con);
    void EditProductOrder(sql::Connection* con);
};
class WorkOn : public Project, public HumanResources {
//Has to be changed to proteced after verifying 
public:
    void insertEmployeeToProject(sql::Connection* con);
    void DisplayProjectEmployees(sql::Connection* con);
    void deleteEmployeeFromProject(sql::Connection* con);
    void updateProjectEmployees(sql::Connection* con);
};

class ProductsToOrder {
public:
	void productsToOrder(sql::Connection* con);
	void displayApprovedProducts(sql::Connection* con);
	void insertApprovedProducts(sql::Connection* con);
};


#endif // GROUP2_H
