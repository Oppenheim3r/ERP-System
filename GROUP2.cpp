#include "GROUP1.h"
#include "GROUP2.h"
#include <iostream>
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/prepared_statement.h>
#include "sqlConn.h"
using namespace std;

   // class products
void Product::DisplayAllProduct(sql::Connection* con) {
    try {
        sql::Statement* stmt = con->createStatement();
        sql::ResultSet* res = stmt->executeQuery("SELECT * FROM products");

        while (res->next()) {
            cout << "Product ID : " << res->getInt("product_id") << "   " << "Product Name : " << res->getString("product_name") << "   " <<
                "Product Price : " << res->getDouble("price") << "    " << "remaining number of product : " << res->getInt("quantity") << "   "
                << "Number of orders :" << res->getInt("TimePurchased") << endl;
        }
        delete res;
        delete stmt;
    }
    catch (sql::SQLException& e) {
        cerr << "MySQL Exception: " << e.what() << endl;
    }

}
void Product::AddProduct(sql::Connection* con) {
    string proname;
    double proprice;
    int quantity;
    cout << "Enter the product's Name : ";
    cin >> proname;
    cout << "Enter the product's price : ";
    cin >> proprice;
    cout << "Enter the Number of product quantity : ";
    cin >> quantity;

    try {
        sql::PreparedStatement* pstmt = con->prepareStatement("INSERT INTO products (product_name,price,quantity,TimePurchased) VALUES (?,?,?,?)");
        pstmt->setString(1, proname);
        pstmt->setDouble(2, proprice);
        pstmt->setInt(3, quantity);
        pstmt->setInt(4, 0);
        pstmt->execute();
        delete pstmt;
        cout << "Product added successfully." << endl;
    }
    catch (sql::SQLException& e) {
        cerr << "MySQL Exception: " << e.what() << endl;
    }

}
bool Product::ProductExists(sql::Connection* con, int productId) {
    sql::PreparedStatement* pstmt = con->prepareStatement("SELECT * FROM products WHERE product_id = ?");
    pstmt->setInt(1, productId);

    sql::ResultSet* res = pstmt->executeQuery();

    bool exists = res->next();

    delete res;
    delete pstmt;

    return exists;
}
void Product::UpdateProduct(sql::Connection* con) {
    int productId;
    string newName;

    cout << "Enter product ID to update: ";
    cin >> productId;

    if (!ProductExists(con, productId)) {
        cout << "product with ID " << productId << " does not exist!\n";
        return;
    }

    sql::PreparedStatement* pstmtSelect = con->prepareStatement("SELECT * FROM products WHERE product_id = ?");
    pstmtSelect->setInt(1, productId);

    sql::ResultSet* res = pstmtSelect->executeQuery();

    cout << "Updating product with ID " << productId << ":\n";

    while (res->next()) {
        cout << "product Name: " << res->getString("product_name") << ", Price: "
            << res->getDouble("price") << endl;
    }

    delete res;
    delete pstmtSelect;

    cout << "Enter new product name: ";
    cin >> newName;


    sql::PreparedStatement* pstmtUpdate = con->prepareStatement("UPDATE products SET product_name = ? WHERE product_id = ?");
    pstmtUpdate->setString(1, newName);
    pstmtUpdate->setInt(2, productId);

    pstmtUpdate->executeUpdate();

    delete pstmtUpdate;

    cout << "product updated successfully!\n";

}
void Product::DeleteProduct(sql::Connection* con) {
    int productId;

    cout << "Enter product ID to delete: ";
    cin >> productId;

    if (!ProductExists(con, productId)) {
        cout << "product with ID " << productId << " does not exist!\n";
        return;
    }

    sql::PreparedStatement* pstmtSelect = con->prepareStatement("SELECT * FROM products WHERE product_id = ?");
    pstmtSelect->setInt(1, productId);

    sql::ResultSet* res = pstmtSelect->executeQuery();

    cout << "Deleting product with ID " << productId << ":\n";

    while (res->next()) {
        cout << "product Name: " << res->getString("product_name") << ", Price: "
            << res->getDouble("price") << endl;
    }

    delete res;
    delete pstmtSelect;

    sql::PreparedStatement* pstmtDelete = con->prepareStatement("DELETE FROM products WHERE product_id = ?");
    pstmtDelete->setInt(1, productId);

    pstmtDelete->executeUpdate();

    delete pstmtDelete;

    cout << "Product deleted successfully!\n";

}
       // class projects 
void Project::DisplayAllProjects(sql::Connection* con) {
    sql::PreparedStatement* pstmt = con->prepareStatement("SELECT * FROM projects");
    sql::ResultSet* res = pstmt->executeQuery();

    cout << "Displaying all projects:\n";
    cout << "ID | Project Name | Price | Time Needed\n";

    while (res->next()) {
        cout << res->getInt("project_id") << " | "
            << res->getString("project_name") << " | "
            << res->getDouble("price") << " | "
            << res->getString("time_needed") << endl;
    }

    delete res;
    delete pstmt;

    cout << "------------------------------------------\n";
}

bool Project::ProjectExists(sql::Connection* con, int projectId) {
    sql::PreparedStatement* pstmt = con->prepareStatement("SELECT * FROM projects WHERE project_id = ?");
    pstmt->setInt(1, projectId);

    sql::ResultSet* res = pstmt->executeQuery();

    bool exists = res->next();

    delete res;
    delete pstmt;

    return exists;
}

void Project::InsertProject(sql::Connection* con) {
    string projectName;
    double price;
    string timeNeeded;

    cout << "Enter project details:\n";


    cout << "Project Name: ";
    getline(cin, projectName);

    cout << "Price: ";
    cin >> price;

    cout << "Time Needed: ";
    cin >> timeNeeded;

    sql::PreparedStatement* pstmt = con->prepareStatement("INSERT INTO projects (project_name, price, time_needed) VALUES (?, ?, ?)");
    pstmt->setString(1, projectName);
    pstmt->setDouble(2, price);
    pstmt->setString(3, timeNeeded);

    pstmt->executeUpdate();

    delete pstmt;

    cout << "Project inserted successfully!\n";
}

void Project::UpdateProject(sql::Connection* con) {
    int projectId;
    string newName;
    string newTimeNeeded;

    cout << "Enter project ID to update: ";
    cin >> projectId;

    if (!ProjectExists(con, projectId)) {
        cout << "Project with ID " << projectId << " does not exist!\n";
        return;
    }

    sql::PreparedStatement* pstmtSelect = con->prepareStatement("SELECT * FROM projects WHERE project_id = ?");
    pstmtSelect->setInt(1, projectId);

    sql::ResultSet* res = pstmtSelect->executeQuery();

    cout << "Updating project with ID " << projectId << ":\n";

    while (res->next()) {
        cout << "Project Name: " << res->getString("project_name") << ", Price: "
            << res->getDouble("price") << ", Time Needed: " << res->getString("time_needed") << endl;
    }

    delete res;
    delete pstmtSelect;

    cout << "Enter new project name: ";
    cin >> newName;
    cout << "Enter new time needed: ";
    cin >> newTimeNeeded;

    sql::PreparedStatement* pstmtUpdate = con->prepareStatement("UPDATE projects SET project_name = ?, time_needed = ? WHERE project_id = ?");
    pstmtUpdate->setString(1, newName);
    pstmtUpdate->setString(2, newTimeNeeded);
    pstmtUpdate->setInt(3, projectId);

    pstmtUpdate->executeUpdate();

    delete pstmtUpdate;

    cout << "Project updated successfully!\n";
}

void Project::DeleteProject(sql::Connection* con) {
    int projectId;

    cout << "Enter project ID to delete: ";
    cin >> projectId;

    if (!ProjectExists(con, projectId)) {
        cout << "Project with ID " << projectId << " does not exist!\n";
        return;
    }

    sql::PreparedStatement* pstmtSelect = con->prepareStatement("SELECT * FROM projects WHERE project_id = ?");
    pstmtSelect->setInt(1, projectId);

    sql::ResultSet* res = pstmtSelect->executeQuery();

    cout << "Deleting project with ID " << projectId << ":\n";

    while (res->next()) {
        cout << "Project Name: " << res->getString("project_name") << ", Price: "
            << res->getDouble("price") << ", Time Needed: " << res->getString("time_needed") << endl;
    }

    delete res;
    delete pstmtSelect;

    sql::PreparedStatement* pstmtDelete = con->prepareStatement("DELETE FROM projects WHERE project_id = ?");
    pstmtDelete->setInt(1, projectId);

    pstmtDelete->executeUpdate();

    delete pstmtDelete;

    cout << "Project deleted successfully!\n";

}
     //class customer
void Customer::displayAllCustomers(sql::Connection* con) {
    sql::PreparedStatement* pstmt = con->prepareStatement("SELECT * FROM customers");
    sql::ResultSet* res = pstmt->executeQuery();

    cout << "Displaying all customers:\n";
    cout << "ID | Customer Name | Address | Phone Number\n";

    while (res->next()) {
        cout << res->getInt("customer_id") << " | "
            << res->getString("customer_name") << " | "
            << res->getString("address") << " | "
            << res->getString("phone_number") << endl;
    }

    delete res;
    delete pstmt;

    cout << "------------------------------------------\n";
}

void Customer::displayCustomerById(sql::Connection* con) {
    cout << "Enter customer id : ";
    cin >> customer_id;
    sql::PreparedStatement* pstmt = con->prepareStatement("SELECT * FROM customers WHERE customer_id = ?");
    pstmt->setInt(1, customer_id);

    sql::ResultSet* res = pstmt->executeQuery();

    cout << "Displaying customer information for ID " << customer_id << ":\n";
    cout << "ID | Customer Name | Address | Phone Number\n";

    while (res->next()) {
        cout << res->getInt("customer_id") << " | "
            << res->getString("customer_name") << " | "
            << res->getString("address") << " | "
            << res->getString("phone_number") << endl;
    }

    delete res;
    delete pstmt;

    cout << "------------------------------------------\n";
}

bool Customer::customerExists(sql::Connection* con) {
    sql::PreparedStatement* pstmt = con->prepareStatement("SELECT * FROM customers WHERE customer_id = ?");
    pstmt->setInt(1, customer_id);

    sql::ResultSet* res = pstmt->executeQuery();

    bool exists = res->next();

    delete res;
    delete pstmt;

    return exists;
}

int Customer::insertCustomer(sql::Connection* con) {
    string customerName;
    string address;
    string phoneNumber;

    cout << "Enter customer details:\n";

    cout << "Customer Name: ";
    getline(cin, customerName);

    cout << "Address: ";
    getline(cin, address);


    while (true) {
        cout << "Phone Number: ";
        cin >> phoneNumber;

        sql::PreparedStatement* pstmtCheck = con->prepareStatement("SELECT COUNT(*) FROM customers WHERE phone_number = ?");
        pstmtCheck->setString(1, phoneNumber);

        sql::ResultSet* resCheck = pstmtCheck->executeQuery();
        resCheck->next();
        int count = resCheck->getInt(1);

        delete resCheck;
        delete pstmtCheck;

        if (count == 0) {
            break;
        }
        else {
            cout << "Phone number already exists. Please enter a different phone number.\n";
        }
    }

    sql::PreparedStatement* pstmt = con->prepareStatement("INSERT INTO customers (customer_name, address, phone_number) VALUES (?, ?, ?)");
    pstmt->setString(1, customerName);
    pstmt->setString(2, address);
    pstmt->setString(3, phoneNumber);

    pstmt->executeUpdate();

    delete pstmt;

    cout << "Customer inserted successfully!\n";

    sql::PreparedStatement* pstmtSelect = con->prepareStatement("SELECT LAST_INSERT_ID()");
    sql::ResultSet* res = pstmtSelect->executeQuery();

    if (res->next()) {
        customer_id = res->getInt(1);
        cout << "Your assigned customer ID is: " << customer_id << endl;
    }

    delete res;
    delete pstmtSelect;

    return customer_id;
}

void Customer::deleteCustomer(sql::Connection* con) {
    cout << "Enter customer id : ";
    cin >> customer_id;
    if (!customerExists(con)) {
        cout << "Customer with ID " << customer_id << " does not exist!\n";
        return;
    }

    sql::PreparedStatement* pstmtSelect = con->prepareStatement("SELECT * FROM customers WHERE customer_id = ?");
    pstmtSelect->setInt(1, customer_id);

    sql::ResultSet* res = pstmtSelect->executeQuery();

    cout << "Deleting customer with ID " << customer_id << ":\n";
    cout << "ID | Customer Name | Address | Phone Number\n";

    while (res->next()) {
        cout << res->getInt("customer_id") << " | "
            << res->getString("customer_name") << " | "
            << res->getString("address") << " | "
            << res->getString("phone_number") << endl;
    }

    delete res;
    delete pstmtSelect;

    sql::PreparedStatement* pstmtDelete = con->prepareStatement("DELETE FROM customers WHERE customer_id = ?");
    pstmtDelete->setInt(1, customer_id);

    pstmtDelete->executeUpdate();

    delete pstmtDelete;

    cout << "Customer deleted successfully!\n";
}
        // class Vendor
void Vendor::displayAllVendors(sql::Connection* con) {
    sql::PreparedStatement* pstmt = con->prepareStatement("SELECT * FROM vendors");
    sql::ResultSet* res = pstmt->executeQuery();

    cout << "Displaying all vendors:\n";
    cout << "ID | vendor Name | Address | Phone Number\n";

    while (res->next()) {
        cout << res->getInt("vendor_id") << " | "
            << res->getString("vendor_name") << " | "
            << res->getString("address") << " | "
            << res->getString("phone_number") << endl;
    }

    delete res;
    delete pstmt;

    cout << "------------------------------------------\n";
}

void Vendor::displayVendorById(sql::Connection* con) {
    cout << "Enter vendor Id : ";
    cin >> vendor_id;
    sql::PreparedStatement* pstmt = con->prepareStatement("SELECT * FROM vendors WHERE vendor_id = ?");
    pstmt->setInt(1, vendor_id);

    sql::ResultSet* res = pstmt->executeQuery();

    cout << "Displaying vendor information for ID " << vendor_id << ":\n";
    cout << "ID | vendor Name | Address | Phone Number\n";

    while (res->next()) {
        cout << res->getInt("vendor_id") << " | "
            << res->getString("vendor_name") << " | "
            << res->getString("address") << " | "
            << res->getString("phone_number") << endl;
    }

    delete res;
    delete pstmt;

    cout << "------------------------------------------\n";
}

bool Vendor::vendorExists(sql::Connection* con) {
    sql::PreparedStatement* pstmt = con->prepareStatement("SELECT * FROM vendors WHERE vendor_id = ?");
    pstmt->setInt(1, vendor_id);

    sql::ResultSet* res = pstmt->executeQuery();

    bool exists = res->next();

    delete res;
    delete pstmt;

    return exists;
}

int Vendor::insertVendor(sql::Connection* con) {
    string vendorName;
    string address;
    string phoneNumber;

    cout << "Enter vendor details:\n";

    cout << "vendor Name: ";
    getline(cin, vendorName);

    cout << "Address: ";
    getline(cin, address);

    while (true) {
        cout << "Phone Number: ";
        cin >> phoneNumber;

        sql::PreparedStatement* pstmtCheck = con->prepareStatement("SELECT COUNT(*) FROM vendors WHERE phone_number = ?");
        pstmtCheck->setString(1, phoneNumber);

        sql::ResultSet* resCheck = pstmtCheck->executeQuery();
        resCheck->next();
        int count = resCheck->getInt(1);

        delete resCheck;
        delete pstmtCheck;

        if (count == 0) {
            break;
        }
        else {
            cout << "Phone number already exists. Please enter a different phone number.\n";
        }
    }

    sql::PreparedStatement* pstmt = con->prepareStatement("INSERT INTO vendors (vendor_name, address, phone_number) VALUES (?, ?, ?)");
    pstmt->setString(1, vendorName);
    pstmt->setString(2, address);
    pstmt->setString(3, phoneNumber);

    pstmt->executeUpdate();

    delete pstmt;

    cout << "vendor inserted successfully!\n";

    sql::PreparedStatement* pstmtSelect = con->prepareStatement("SELECT LAST_INSERT_ID()");
    sql::ResultSet* res = pstmtSelect->executeQuery();

    if (res->next()) {
        vendor_id = res->getInt(1);
        cout << "Your assigned customer ID is: " << vendor_id << endl;
    }

    delete res;
    delete pstmtSelect;

    return vendor_id;
}

void Vendor::deleteVendor(sql::Connection* con) {
    cout << "Enter vendor Id : ";
    cin >> vendor_id;
    if (!vendorExists(con)) {
        cout << "vendor with ID " << vendor_id << " does not exist!\n";
        return;
    }

    sql::PreparedStatement* pstmtSelect = con->prepareStatement("SELECT * FROM vendors WHERE vendor_id = ?");
    pstmtSelect->setInt(1, vendor_id);

    sql::ResultSet* res = pstmtSelect->executeQuery();

    cout << "Deleting vendor with ID " << vendor_id << ":\n";
    cout << "ID | vendor Name | Address | Phone Number\n";

    while (res->next()) {
        cout << res->getInt("vendor_id") << " | "
            << res->getString("vendor_name") << " | "
            << res->getString("address") << " | "
            << res->getString("phone_number") << endl;
    }

    delete res;
    delete pstmtSelect;

    sql::PreparedStatement* pstmtDelete = con->prepareStatement("DELETE FROM vendors WHERE vendor_id = ?");
    pstmtDelete->setInt(1, vendor_id);

    pstmtDelete->executeUpdate();

    delete pstmtDelete;

    cout << "vendor deleted successfully!\n";
}
