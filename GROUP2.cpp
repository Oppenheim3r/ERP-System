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

      cout << "Displaying all Products :\n";
cout << "ID | Product Name | Price | Quantity | Time Purchased\n";
while (res->next()) {
    cout << res->getInt("product_id") << " | "
        << res->getString("product_name") << " | "
        << res->getDouble("price") << " | "
        << res->getString("quantity") << "| "<<
        res->getInt("TimePurchased") << endl;
}
        delete res;
        delete stmt;
    }
    catch (sql::SQLException& e) {
        cerr << "MySQL Exception: " << e.what() << endl;
    }

}
void Product::displayProductById(int proId, sql::Connection* con) {
    try {
        if (!ProductExists(con, proId)) {
            cout << "Product with ID " << proId << " does not exist!\n";
            return;
        }

        sql::PreparedStatement* pstmtSelect = con->prepareStatement("SELECT * FROM products WHERE product_id = ?");
        pstmtSelect->setInt(1, proId);

        sql::ResultSet* res = pstmtSelect->executeQuery();

        cout << "Product details for ID " << proId << ":\n";
        cout << "Product ID |Product Name | Price \n";

        while (res->next()) {
            cout << res->getInt("product_id") << " | " << res->getString("product_name") << " | " << res->getDouble("price") << endl;
        }

        delete res;
        delete pstmtSelect;
    }
    catch (sql::SQLException& e) {
        cerr << "SQL Error: " << e.what() << endl;
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
int Customer::insertCustomer(bool &check,sql::Connection* con) {
    string customerName;
    string address;
    string phoneNumber;

    

    cout << "Name: ";
    cin >> customerName;

    cout << "Address: ";
    cin >> address;


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
    try {sql::PreparedStatement* pstmt = con->prepareStatement("INSERT INTO customers (customer_name, address, phone_number) VALUES (?, ?, ?)");
    pstmt->setString(1, customerName);
    pstmt->setString(2, address);
    pstmt->setString(3, phoneNumber);

    pstmt->executeUpdate();

    delete pstmt;

    cout << "Done !\n";
    check = true;

    sql::PreparedStatement* pstmtSelect = con->prepareStatement("SELECT LAST_INSERT_ID()");
    sql::ResultSet* res = pstmtSelect->executeQuery();

    if (res->next()) {
        customer_id = res->getInt(1);
        //cout << "Your assigned customer ID is: " << customer_id << endl;

    }

    delete res;
    delete pstmtSelect;

    return customer_id;
    }
    catch (sql::SQLException& e) {
        cerr << "MySQL Exception: " << e.what() << endl;
        check = false;
    }
    
}
bool Customer::Login(int& customer_id, sql::Connection* con) {
    string name;
    string phone_number;
    cout << "Enter your Name :";
    cin >> name;
    cout << "Enter your phone Number :";
    cin >> phone_number;
    try {
        sql::PreparedStatement* pstmt = con->prepareStatement("SELECT * FROM customers WHERE customer_name = ? and phone_number = ?");
        pstmt->setString(1, name);
        pstmt->setString(2, phone_number);

        sql::ResultSet* res = pstmt->executeQuery();

        bool exists = res->next();
        if (exists == true) {
            cout << "Welcom " << name<<endl;
            customer_id= res->getInt("customer_id");
          
        }
        delete res;
        delete pstmt;
        return exists;
    }
    catch (sql::SQLException& e) {
        cerr << "MySQL Exception: " << e.what() << endl;
    }
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
////////////////////////
//OrderProject
void OrderProject::displayAllOrders(sql::Connection* con) {
    try {
        sql::PreparedStatement* pstmt = con->prepareStatement("SELECT * FROM orderProject");
        sql::ResultSet* res = pstmt->executeQuery();

       cout << "Displaying all orders:\n";
        cout << "ID | Project ID | Customer ID | Amount Paid | Order Date | Date to be Ready\n";

        while (res->next()) {
            cout << res->getInt("order_id") << " | "
                << res->getInt("project_id") << " | "
                << res->getInt("customer_id") << " | "
                << res->getDouble("amount_paid") << " | "
                << res->getString("order_date") << " | "
                << res->getString("date_to_be_ready") << std::endl;
        }

        delete res;
        delete pstmt;

        cout << "------------------------------------------\n";
    }
    catch (sql::SQLException& e) {
        cerr << "SQL Error: " << e.what() << std::endl;
    }
}

bool OrderProject::orderExistsById(int orderId, sql::Connection* con) {
    try {
        sql::PreparedStatement* pstmtSelect = con->prepareStatement("SELECT * FROM orderProject WHERE order_id = ?");
        pstmtSelect->setInt(1, orderId);

        sql::ResultSet* res = pstmtSelect->executeQuery();
        bool exists = res->next();

        delete res;
        delete pstmtSelect;

        return exists;
    }
    catch (sql::SQLException& e) {
        cerr << "SQL Error: " << e.what() << endl;
        return false;
    }
}

void OrderProject::displayOrderById(int orderId, sql::Connection* con) {
    try {
        if (!orderExistsById(orderId, con)) {
            cout << "Order with ID " << orderId << " does not exist!\n";
            return;
        }

        sql::PreparedStatement* pstmtSelect = con->prepareStatement("SELECT * FROM orderProject WHERE order_id = ?");
        pstmtSelect->setInt(1, orderId);

        sql::ResultSet* res = pstmtSelect->executeQuery();

        cout << "Order details for ID " << orderId << ":\n";
        cout << "ID | Project ID | Customer ID | Amount Paid | Order Date | Date to be Ready\n";

        while (res->next()) {
            cout << res->getInt("order_id") << " | "
                << res->getInt("project_id") << " | "
                << res->getInt("customer_id") << " | "
                << res->getDouble("amount_paid") << " | "
                << res->getString("order_date") << " | "
                << res->getString("date_to_be_ready") <<endl;
        }

        delete res;
        delete pstmtSelect;
    }
    catch (sql::SQLException& e) {
        cerr << "SQL Error: " << e.what() << endl;
    }
}

void OrderProject::editOrder(sql::Connection* con) {
    int orderId;
    double newAmountPaid;

    cout << "Enter Order ID: ";
    cin >> orderId;

    if (!orderExistsById(orderId, con)) {
        cout << "Order with ID " << orderId << " does not exist!\n";
        return;
    }

    displayOrderById(orderId, con);

   cout << "Enter New Amount Paid: ";
    cin >> newAmountPaid;

    try {
        sql::PreparedStatement* pstmt = con->prepareStatement("UPDATE orderProject SET amount_paid = ? WHERE order_id = ?");
        pstmt->setDouble(1, newAmountPaid);
        pstmt->setInt(2, orderId);

        pstmt->executeUpdate();

        delete pstmt;

        cout << "Order edited successfully!\n";
    }
    catch (sql::SQLException& e) {
        cerr << "SQL Error: " << e.what() << std::endl;
    }
}

void OrderProject::removeOrder(sql::Connection* con) {
    int orderId;

    cout << "Enter Order ID to delete: ";
    cin >> orderId;

    if (!orderExistsById(orderId, con)) {
        cout << "Order with ID " << orderId << " does not exist!\n";
        return;
    }

    displayOrderById(orderId, con);

    char confirmation;
    do {
      cout << "Are you sure you want to delete this order? (Y/N): ";
        cin >> confirmation;
        confirmation = toupper(confirmation);

        if (confirmation == 'Y') {
            try {
                sql::PreparedStatement* pstmtDelete = con->prepareStatement("DELETE FROM orderProject WHERE order_id = ?");
                pstmtDelete->setInt(1, orderId);

                pstmtDelete->executeUpdate();

                delete pstmtDelete;

                cout << "Order deleted successfully!\n";
            }
            catch (sql::SQLException& e) {
               cerr << "SQL Error: " << e.what() << std::endl;
            }
        }
        else if (confirmation == 'N') {
            cout << "Deletion canceled.\n";
        }
        else {
           cout << "Invalid input. Please enter 'Y' for Yes or 'N' for No.\n";
        }
    } while (confirmation != 'Y' && confirmation != 'N');
}
void OrderProject::addOrder(sql::Connection* con) {
    try {
        int projectId, customerId;
        double amountPaid, price;

        cout << "Enter Project ID: ";
        cin >> projectId;

        cout << "Enter Customer ID: ";
        cin >> customerId;

        
        sql::PreparedStatement* pstmtSelect = con->prepareStatement("SELECT price FROM projects WHERE project_id = ?");
        pstmtSelect->setInt(1, projectId);
        sql::ResultSet* res = pstmtSelect->executeQuery();

        if (res->next()) {
             price = res->getDouble("price");
            cout << "Price of the selected project: " << price << endl;
        }
        else {
            cout << "Project with ID " << projectId << " does not exist!\n";
            return;
        }
        
        cout << "Enter Amount Paid: ";
        cin >> amountPaid;

        if (amountPaid >= price) {
            double change = amountPaid - price;
            cout << "Change: " << change << endl;

            
            sql::PreparedStatement* pstmt = con->prepareStatement("INSERT INTO orderProject (project_id, customer_id, amount_paid) VALUES (?, ?, ?)");
            pstmt->setInt(1, projectId);
            pstmt->setInt(2, customerId);
            pstmt->setDouble(3, price);

            pstmt->executeUpdate();

            delete pstmt;
        }
        else {
            cout << "Amount paid is less than the project price. Please insert the full amount.\n";
        }

        delete res;
        delete pstmtSelect;
    }
    catch (sql::SQLException& e) {
        cerr << "SQL Error: " << e.what() << endl;
    }
}
// class OrderProduct
void OrderProduct::DisplayAllProduct(sql::Connection* con) {
    try {
        sql::Statement* stmt = con->createStatement();
        sql::ResultSet* res = stmt->executeQuery("SELECT * FROM products");

        cout << "Displaying all products :\n";
        cout << "ID | Product Name | Price \n";
        while (res->next()) {
            cout << res->getInt("product_id") << " | " << res->getString("product_name") << " | " << res->getDouble("price") << endl;
        }
        delete res;
        delete stmt;
    }
    catch (sql::SQLException& e) {
        cerr << "MySQL Exception: " << e.what() << endl;
    }
}

bool OrderProduct::CheckTheQuantity(int proId, int quantity, sql::Connection* con) {
    int reQun;
    sql::PreparedStatement* pstmtSelect = con->prepareStatement("SELECT quantity FROM products WHERE product_id = ?");
    pstmtSelect->setInt(1, proId);
    sql::ResultSet* res = pstmtSelect->executeQuery();

    if (res->next()) {
        reQun = res->getInt("quantity");
    }
    delete res;
    delete pstmtSelect;
    if (reQun > quantity)
        return true;
    else {
        cout << "Sorry , The required quantity is not available in stock , The available quantity is less than : " << reQun << endl;
        return false;
    }

}
double OrderProduct::CalculationTheAmount(int proId, int quantity, sql::Connection* con) {
    double total_price, price;
    sql::PreparedStatement* pstmtSelect = con->prepareStatement("SELECT price FROM products WHERE product_id = ?");
    pstmtSelect->setInt(1, proId);
    sql::ResultSet* res = pstmtSelect->executeQuery();

    if (res->next()) {
        price = res->getDouble("price");
        cout << "Price of the selected product : " << price << endl;
        total_price = price * quantity;
        cout << "The toatl price is : " << total_price << endl;
        cout << "Enter the amount : " << endl;
        return total_price;
    }


    delete res;
    delete pstmtSelect;
}



void OrderProduct::AddOrderProduct(int proId, int cumtomerId, int quantity, double amount_paid, double Total, sql::Connection* con) {
    bool check;

    if (!CheckTheQuantity(proId, quantity, con))
    {

    }
    else {
        if (amount_paid >= Total) {
            double change = amount_paid - Total;
            cout << "Change : " << change << endl;
            try {
                sql::PreparedStatement* pstmt = con->prepareStatement("INSERT INTO orderProduct(product_id,customer_id,quantity_ordered,amount_paid) VALUES (?,?,?,?)");
                pstmt->setInt(1, proId);
                pstmt->setInt(2, cumtomerId);
                pstmt->setInt(3, quantity);
                pstmt->setDouble(4, amount_paid);
                pstmt->execute();
                delete pstmt;
                check = true;
                cout << "The order completed successfully" << endl;
            }
            catch (sql::SQLException& e) {
                cerr << "MySQL Exception: " << e.what() << endl;
                check = false;
            }
            if (check) {
                try {
                    sql::PreparedStatement* updateStmt = con->prepareStatement("UPDATE products SET quantity = quantity - ? , TimePurchased = TimePurchased + ?  WHERE product_id = ?");
                    updateStmt->setInt(1, quantity);
                    updateStmt->setInt(2, quantity);
                    updateStmt->setInt(3, proId);
                    updateStmt->execute();
                    delete updateStmt;
                }
                catch (sql::SQLException& e) {
                    cerr << "MySQL Exception: " << e.what() << endl;
                }

            }

        }
        else
            cout << "Amount paid is less than the project price. Please insert the full amount.\n";
    }

}

void OrderProduct::DisplayAllProductOrders(sql::Connection* con) {
    try {
        sql::Statement* stmt = con->createStatement();
        sql::ResultSet* res = stmt->executeQuery("SELECT * FROM orderProduct");
        cout << "Displaying all orders:\n";
        cout << "ID | Product ID | Customer ID| Quantity | Amount Paid | Order Date | \n";
        while (res->next()) {
            cout << res->getInt("order_id") << " | "
                << res->getInt("product_id") << " | "
                << res->getInt("customer_id") << " | "
                << res->getInt("quantity_ordered") << " | "
                << res->getDouble("amount_paid") << " | "
                << res->getString("order_date") << " | "
                << endl;
        }
        delete res;
        delete stmt;
    }
    catch (sql::SQLException& e) {
        cerr << "MySQL Exception: " << e.what() << endl;
    }
}

bool OrderProduct::ProductOrderExistsById(int orderId, sql::Connection* con) {
    try {
        sql::PreparedStatement* pstmtSelect = con->prepareStatement("SELECT * FROM orderProduct WHERE order_id = ?");
        pstmtSelect->setInt(1, orderId);

        sql::ResultSet* res = pstmtSelect->executeQuery();
        bool exists = res->next();

        delete res;
        delete pstmtSelect;

        return exists;
    }
    catch (sql::SQLException& e) {
        cerr << "SQL Error: " << e.what() << endl;
        return false;
    }
}

void OrderProduct::DisplayProductOrderById(int orderId, sql::Connection* con) {
    try {

        if (!ProductOrderExistsById(orderId, con)) {
            cout << "Order with ID " << orderId << " does not exist!\n";
        }

        sql::PreparedStatement* pstmtSelect = con->prepareStatement("SELECT * FROM orderProduct WHERE order_id = ?");
        pstmtSelect->setInt(1, orderId);

        sql::ResultSet* res = pstmtSelect->executeQuery();


        cout << "Order details for ID " << orderId << ":\n";
        cout << "ID | Product ID | Customer ID| Quantity | Amount Paid | Order Date | \n";

        while (res->next()) {
            cout << res->getInt("order_id") << " | "
                << res->getInt("product_id") << " | "
                << res->getInt("customer_id") << " | "
                << res->getInt("quantity_ordered") << " | "
                << res->getDouble("amount_paid") << " | "
                << res->getString("order_date") << " | "
                << endl;
        }

        delete res;
        delete pstmtSelect;

    }
    catch (sql::SQLException& e) {
        cerr << "SQL Error: " << e.what() << endl;

    }
}

void OrderProduct::RemoveProductOrder(sql::Connection* con) {
    int orderId;

    cout << "Enter Order ID to delete: ";
    cin >> orderId;

    if (!ProductOrderExistsById(orderId, con)) {
        cout << "Order with ID " << orderId << " does not exist!\n";
        return;
    }

    char confirmation;
    do {
        cout << "Are you sure you want to delete this order? (Y/N): ";
        cin >> confirmation;
        confirmation = toupper(confirmation);

        if (confirmation == 'Y') {
            try {
                sql::PreparedStatement* pstmtDelete = con->prepareStatement("DELETE FROM orderProduct WHERE order_id = ?");
                pstmtDelete->setInt(1, orderId);

                pstmtDelete->executeUpdate();

                delete pstmtDelete;

                cout << "Order deleted successfully!\n";
            }
            catch (sql::SQLException& e) {
                cerr << "SQL Error: " << e.what() << endl;
            }
        }
        else if (confirmation == 'N') {
            cout << "Deletion canceled.\n";
        }
        else {
            cout << "Invalid input. Please enter 'Y' for Yes or 'N' for No.\n";
        }
    } while (confirmation != 'Y' && confirmation != 'N');
}

void OrderProduct::EditProductOrder(sql::Connection* con) {
    int order_Id;
    double amount1;
    double amount2;
    int proId;
    int quantity;
    int customerId;
    cout << "Enter The order ID you want to change : \n ";
    cin >> order_Id;
    DisplayProductOrderById(order_Id, con);

    try {
        sql::PreparedStatement* pstmtSelect = con->prepareStatement("SELECT * FROM orderProduct WHERE order_id = ?");
        pstmtSelect->setInt(1, order_Id);
        sql::ResultSet* res = pstmtSelect->executeQuery();
        if (res->next()) {
            customerId = res->getInt("customer_id");
            amount1 = res->getDouble("amount_paid");
        }
        else {
            cout << "Oreder with ID " << order_Id << " does not exist";
        }

        delete res;
        delete pstmtSelect;
    }
    catch (sql::SQLException& e) {
        cerr << "MySQL Exception: " << e.what() << endl;
    }
    cout << "You have paid :" << amount1 << endl;
    RemoveProductOrder(con);
    cout << "Enter the Details of the new order : \n";
    DisplayAllProduct(con);
    cout << "\nEnter Product number : ";
    cin >> proId;
    cout << "\nEnter the quantity : ";
    cin >> quantity;
    double Total =CalculationTheAmount(proId, quantity, con);
    cin >> amount2;
    amount2 = amount1 + amount2;
    AddOrderProduct(proId, customerId, quantity, amount2, Total, con);

}

////////////////////////////////////
//WorkOn
// WorkOn.cpp



void WorkOn::insertEmployeeToProject(sql::Connection* con) {
    int project_id, Emp_id;
    cout << "Projects Details :\n ";
    DisplayAllProjects(con);
    cout << "\nEmployees Details :\n ";
    DisplayAllEmp(con);
    cout << "\nEnter The Employee ID and the ID of The Project he Works on : " << endl;
    cout << "Employee ID : ";
    cin >> Emp_id;
    if (!EmployeeExists(con, Emp_id)) {
        cout << "Employee with ID :" << Emp_id << " does not exist." << endl;
    }
    else {
        cout << "Project ID : ";
        cin >> project_id;
        if (!ProjectExists(con, project_id)) {
            cout << "Project with ID : " << project_id << " does not exist." << endl;
        }
        else {
            try {
                sql::PreparedStatement* pstmt = con->prepareStatement("INSERT INTO workon(project_id,employee_id) VALUES (?, ?)");
                pstmt->setInt(1, project_id);
                pstmt->setInt(2, Emp_id);
                pstmt->execute();
                delete pstmt;
                cout << "The operation was completed successfully! " << endl;
            }
            catch (sql::SQLException& e) {
                cerr << "MySQL Exception: " << e.what() << endl;
            }
        }
    }
}

void WorkOn::DisplayProjectEmployees(sql::Connection* con) {
    try {
        sql::Statement* stmt = con->createStatement();
        sql::ResultSet* res = stmt->executeQuery("SELECT projects.project_id, projects.project_name, employees.id, employees.name FROM workon JOIN projects ON workon.project_id = projects.project_id JOIN employees ON workon.employee_id = employees.id");
        cout << "Project ID  |  Project Name  |  Employee ID  | Employee Name " << endl;
        while (res->next()) {
            cout << res->getInt("project_id") << "  |  " << res->getString("project_name") << " | " << res->getInt("id") << "  |  " << res->getString("name") << endl;
        }
        delete res;
        delete stmt;
    }
    catch (sql::SQLException& e) {
        cerr << "MySQL Exception: " << e.what() << endl;
    }
}

void WorkOn::deleteEmployeeFromProject(sql::Connection* con) {
    DisplayProjectEmployees(con);
    int emp_id, project_id;
    cout << "Enter Employee ID : ";
    cin >> emp_id;
    if (!EmployeeExists(con, emp_id)) {
        cout << "Employee does not exist." << endl;
    }
    else {
        cout << "Enter Project ID : ";
        cin >> project_id;
        if (!ProjectExists(con, project_id)) {
            cout << "Project does not exist." << endl;
        }
        else {
            try {
                sql::PreparedStatement* deleteStmt = con->prepareStatement("DELETE FROM workon WHERE project_id = ? and employee_id=?");
                deleteStmt->setInt(1, emp_id);
                deleteStmt->setInt(2, project_id);
                deleteStmt->execute();
                delete deleteStmt;
                cout << "The operation was completed successfully! " << endl;
            }
            catch (sql::SQLException& e) {
                cerr << "MySQL Exception: " << e.what() << endl;
            }
        }
    }
}

void WorkOn::updateProjectEmployees(sql::Connection* con) {
    int c;
    int emp_id, project_id;
    cout << "1. Change Employee " << endl;
    cout << "2. Change Project " << endl;
    cout << "Choose: ";
    cin >> c;
    switch (c) {
    case 1: {
        cout << "Enter Project ID : ";
        cin >> project_id;
        if (!ProjectExists(con, project_id)) {
            cout << "Project with ID " << project_id << " does not exist." << endl;
        }
        else {
            cout << "Enter The New Employee ID : ";
            cin >> emp_id;
            if (!EmployeeExists(con, emp_id)) {
                cout << "Employee with ID " << emp_id << " does not exist." << endl;
            }
            else {
                sql::PreparedStatement* updateStmt = con->prepareStatement("UPDATE workon SET employee_id = ? WHERE project_id = ?");
                updateStmt->setInt(1, emp_id);
                updateStmt->setInt(2, project_id);
                updateStmt->execute();
                delete updateStmt;
            }
        }
    }
          break;
    case 2: {
        cout << "Enter Employee ID : ";
        cin >> emp_id;
        if (!EmployeeExists(con, emp_id)) {
            cout << "Employee with ID " << emp_id << " does not exist." << endl;
        }
        else {
            cout << "Enter The New Project ID : ";
            cin >> project_id;
            if (!ProjectExists(con, project_id)) {
                cout << "Project with ID " << project_id << " does not exist." << endl;
            }
            else {
                sql::PreparedStatement* updateStmt = con->prepareStatement("UPDATE workon SET project_id = ? WHERE employee_id = ?");
                updateStmt->setInt(1, project_id);
                updateStmt->setInt(2, emp_id);
                updateStmt->execute();
                delete updateStmt;
            }
        }
    }
          break;
    default:
        cout << "Wrong input." << endl;
    }
}
