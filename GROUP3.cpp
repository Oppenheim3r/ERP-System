#include "GROUP3.h"
#include "sqlConn.h"
#include <iostream>
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/prepared_statement.h>

using namespace std;

void FinancialManagement::Display_Budget_table(sql::Connection* con) {
    double ProjectBudget = 0;

    try {
        sql::Statement* stmt = con->createStatement();
        sql::ResultSet* res = stmt->executeQuery("SELECT * FROM budget_table");
        cout << "Product_budget | Project_budget | Employee_budget | Product_costs | Project_costs | Product_profit | Project_profit \n ";
        if (res->next()) {
            ProjectBudget = res->getDouble("product_budget");
            cout << ProjectBudget << " | " <<
                res->getDouble("project_budget") << " | " <<
                res->getDouble("employee_budget") << " | " <<
                res->getDouble("product_costs") << " | " <<
                res->getDouble("project_costs") << " | " <<
                res->getDouble("product_profit") << " | " <<
                res->getDouble("project_profit") << " | " << endl;
        }
        delete res;
        delete stmt;

    }
    catch (sql::SQLException& e) {
        cerr << "MySQL Exception: " << e.what() << endl;
    }
}

void FinancialManagement::ChangeBudgets(sql::Connection* con) {
    double NewProductBudget, NewProjectBudget, NewEmployeeBudet;
    int choose;
    cout << "Which budget you want to change ?\n";
    cout << "1. Employee Budget \n";
    cout << "2. Product Budget\n";
    cout << "3. Project Budget \n";
    cin >> choose;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter a number.\n";
        return;
    }
    switch (choose) {
    case 1: {
        cout << "Enter the New Employee Budget :\n";
        cin >> NewEmployeeBudet;
        try {

            sql::PreparedStatement* updateBudet = con->prepareStatement("UPDATE budget_table SET employee_budget  = ? WHERE id = 1");
            updateBudet->setDouble(1, NewEmployeeBudet);
            updateBudet->execute();
            delete updateBudet;
            cout << "Done !\n";

        }
        catch (sql::SQLException& e) {
            cerr << "MySQL Exception: " << e.what() << endl;
        }

    }
          break;
    case 2: {
        cout << "Enter the New Product Budget :\n";
        cin >> NewProductBudget;
        try {

            sql::PreparedStatement* updateBudet = con->prepareStatement("UPDATE budget_table SET product_budget   = ? WHERE id = 1");
            updateBudet->setDouble(1, NewProductBudget);
            updateBudet->execute();
            delete updateBudet;

            cout << "Done !\n";
        }
        catch (sql::SQLException& e) {
            cerr << "MySQL Exception: " << e.what() << endl;
        }

    }
          break;
    case 3: {
        cout << "Enter the New Project Budget :\n";
        cin >> NewProjectBudget;
        try {

            sql::PreparedStatement* updateBudet = con->prepareStatement("UPDATE budget_table SET project_budget   = ? WHERE id = 1");
            updateBudet->setDouble(1, NewProjectBudget);
            updateBudet->execute();
            delete updateBudet;
            cout << "Done !\n";
        }
        catch (sql::SQLException& e) {
            cerr << "MySQL Exception: " << e.what() << endl;
        }

    }
          break;
    default:
        cout << "Wrong Input .\n";
    }
}

void FinancialManagement::EmployeeBudgetStatues(sql::Connection* con) {
    double EmployeeBudget;
    cout << "\nNote : " << endl;
    double Total = TotalSalaries(con);

    try {
        sql::Statement* stmt = con->createStatement();
        sql::ResultSet* res = stmt->executeQuery("SELECT employee_budget FROM budget_table where id=1");


        if (res->next()) {

            EmployeeBudget = res->getDouble("employee_budget");

            cout << "Employee Budget: " << EmployeeBudget << endl;
        }
        else {
            cout << "No budget information found." << endl;
        }

        delete res;
        delete stmt;
    }
    catch (sql::SQLException& e) {
        cerr << "MySQL Exception: " << e.what() << endl;
        return;
    }


    if (Total >= EmployeeBudget) {
        cout << "The Total employee salaries are greater than the salary budget, Action must be taken urgently!\n";
    }
    else if (Total + 50000 >= EmployeeBudget) {
        cout << "Total salaries are almost up to the salary budget, it is better to take action.\n";
    }
    else {
        cout << "Total employee salaries are adequate, there is still a budget to add employees.\n";
    }
    cout << "________________________________________\n\n";
}

void FinancialManagement::ProductBudgetStatues(sql::Connection* con) {
    double ProductBudget;
    double ProductCost;
    cout << "\nNote : " << endl;

    try {
        sql::Statement* stmt = con->createStatement();
        sql::ResultSet* res = stmt->executeQuery("SELECT product_budget ,product_costs  FROM budget_table where id=1");


        if (res->next()) {

            ProductBudget = res->getDouble("product_budget");
            ProductCost = res->getDouble("product_costs");
        }
        else {
            cout << "No budget information found." << endl;
        }

        delete res;
        delete stmt;
    }
    catch (sql::SQLException& e) {
        cerr << "MySQL Exception: " << e.what() << endl;
        return;
    }


    if (ProductCost >= ProductBudget) {
        cout << "The products costs is greater than the products budget, Action must be taken urgently!\n";
    }
    else if (ProductCost + 50000 >= ProductBudget) {
        cout << "Total Products costs are almost up to the products budget , it is better to take action.\n";
    }
    else {
        cout << "Total Products costs are adequate, there is still a budget to buy products.\n";
    }
    cout << "________________________________________\n\n";
}

void FinancialManagement::displayProductsToBuy(sql::Connection* con) {
    try {
        sql::Statement* stmt = con->createStatement();
        sql::ResultSet* res = stmt->executeQuery("SELECT * FROM productsToBuy");

        cout << "ProductsToBuy Details:\n";
        cout << "Product ID | Product Name | Vendor Name | Price | Quantity | Approved\n";
        while (res->next()) {
            cout << res->getInt("id") << " | "
                << res->getString("product_name") << " | "
                << res->getString("vendor_name") << " | "
                << res->getDouble("price") << " | "
                << res->getInt("quantity") << " | "
                << res->getBoolean("approve") << "\n";
        }

        delete res;
        delete stmt;
    }
    catch (sql::SQLException& e) {
        cerr << "SQL Error: " << e.what() << endl;
    }
}

void FinancialManagement::insertProductToBuy(sql::Connection* con) {
    string productName, vendorName;
    double price;
    int quantity;

    cout << "Enter product name: ";
    cin >> productName;

    cout << "Enter vendor name: ";
    cin >> vendorName;

    cout << "Enter price: ";
    cin >> price;

    cout << "Enter quantity: ";
    cin >> quantity;

    try {

        sql::PreparedStatement* pstmt = con->prepareStatement("INSERT INTO productsToBuy (product_name, vendor_name, price, quantity, approve) VALUES (?, ?, ?, ?, false)");
        pstmt->setString(1, productName);
        pstmt->setString(2, vendorName);
        pstmt->setDouble(3, price);
        pstmt->setInt(4, quantity);
        pstmt->execute();
        delete pstmt;


        sql::PreparedStatement* budgetStmt = con->prepareStatement("UPDATE budget_table SET product_costs = product_costs + (?*?) WHERE id = 1");
        budgetStmt->setDouble(1, price);
        budgetStmt->setInt(2, quantity);
        budgetStmt->execute();
        delete budgetStmt;

        cout << "Product inserted into productsToBuy successfully!\n";
    }
    catch (sql::SQLException& e) {
        cerr << "SQL Error: " << e.what() << endl;
    }
}

void FinancialManagement::approveProduct(sql::Connection* con) {
    try {
        sql::Statement* stmt = con->createStatement();
        sql::ResultSet* res = stmt->executeQuery("SELECT * FROM productsToBuy WHERE approve = false");

        cout << "Products To Approve:\n";
        cout << "Product ID | Product Name | Vendor Name | Price | Quantity | Approved\n";
        while (res->next()) {
            cout << res->getInt("id") << " | "
                << res->getString("product_name") << " | "
                << res->getString("vendor_name") << " | "
                << res->getDouble("price") << " | "
                << res->getInt("quantity") << " | "
                << res->getBoolean("approve") << "\n";
        }

        delete res;
        delete stmt;

        int productId;
        cout << "Enter the ID of the product to approve: ";
        cin >> productId;

        double percentage;
        cout << "Enter the percentage to add to the product price: ";
        cin >> percentage;

        char confirm;
        cout << "Are you sure about these changes? (Y/N): ";
        cin >> confirm;

        if (toupper(confirm) == 'Y') {
            try {
                sql::PreparedStatement* pstmt = con->prepareStatement("UPDATE productsToBuy SET approve = true, price = price + (price * ? / 100) WHERE id = ?");
                pstmt->setDouble(1, percentage);
                pstmt->setInt(2, productId);
                pstmt->execute();
                delete pstmt;

                cout << "Product with ID " << productId << " approved successfully!\n";
            }
            catch (sql::SQLException& e) {
                cerr << "SQL Error: " << e.what() << endl;
            }
        }
        else {
            cout << "Changes not confirmed. Product approval cancelled.\n";
        }
    }
    catch (sql::SQLException& e) {
        cerr << "SQL Error: " << e.what() << endl;
    }
}
void FinancialManagement::editProductPrice(sql::Connection* con) {
    int productId;
    double NewPrice;

    DisplayAllProduct(con);
    cout << "Enter the ID of the product you want to edit: ";
    cin >> productId;
    if (!ProductExists(con, productId)) {
        cout << "product with ID " << productId << " does not exist!\n";
        return;
    }
    cout << "\nCurrent Product Details:\n";
    displayProductById(productId, con);
    cout << "\nEnter the New Price : ";
    cin >> NewPrice;
    try {
        sql::PreparedStatement* updateStmt = con->prepareStatement("UPDATE products SET price = ? WHERE product_id = ?");
        updateStmt->setDouble(1, NewPrice);
        updateStmt->setInt(2, productId);
        updateStmt->execute();
        cout << "product price updated successfully!\n";
        delete updateStmt;
    }
    catch (sql::SQLException& e) {
        cerr << "MySQL Exception: " << e.what() << endl;
    }

   
}
/////////////////
//logs



void Logs::view_logs(sql::Connection* con) {
    try {
        sql::Statement* stmt = con->createStatement();
        sql::ResultSet* res = stmt->executeQuery("SELECT * FROM change_log");

        cout << "Change Logs:\n";
        cout << "ID | Table Name | Action | Timestamp\n";
        while (res->next()) {
            cout << res->getInt("id") << " | "
                << res->getString("table_name") << " | "
                << res->getString("action") << " | "
                << res->getString("timestamp") << "\n";
        }

        delete res;
        delete stmt;
    }
    catch (sql::SQLException& e) {
        cerr << "SQL Error: " << e.what() << endl;
    }
}

////////////////
//quality 
void Quality::profit_and_loss(sql::Connection* con) {
    double amount = 0, budget = 0;
    try {
        sql::Statement* stmt = con->createStatement();
        sql::ResultSet* res = stmt->executeQuery("SELECT product_budget, product_profit FROM budget_table;");
        if (res->next()) {
            budget = res->getDouble("product_budget");
            amount = res->getDouble("product_profit") - res->getDouble("product_budget");
        }
        delete res;
        delete stmt;

        if (amount > 0) {
            cout << "The Profit amount is : " << amount << endl;
            cout << "In Percentage : " << amount / budget * 100 << "%\n";
        }
        else {
            amount = amount * -1;
            cout << "The amount of loss is  : " << amount << endl;
            cout << "In Percentage : " << amount / budget * 100 << "%\n";
        }
    }
    catch (sql::SQLException& e) {
        cerr << "MySQL Exception: " << e.what() << endl;
    }
}

void Quality::Most_Requested_Product(sql::Connection* con) {
    cout << "The Most Requested Product is : \n";
    try {
        sql::Statement* stmt = con->createStatement();
        sql::ResultSet* res = stmt->executeQuery("SELECT * FROM products WHERE TimePurchased = (SELECT MAX(TimePurchased) FROM products)");

        cout << "Product ID | Product Name | Price | Quantity | Time Purchased\n";
        if (res->next()) {
            cout << res->getInt("product_id") << " | " << res->getString("product_name") << " | " << res->getDouble("price") << " | " <<
                res->getInt("quantity") << " | " << res->getInt("TimePurchased") << endl;
        }
        delete res;
        delete stmt;
    }
    catch (sql::SQLException& e) {
        cerr << "MySQL Exception: " << e.what() << endl;
    }
}

void Quality::Most_Requested_Project(sql::Connection* con) {
    cout << "The Most Requested Project is : \n";
    try {
        sql::Statement* stmt = con->createStatement();
        sql::ResultSet* res = stmt->executeQuery("SELECT * FROM projects WHERE TimePurchased = (SELECT MAX(TimePurchased) FROM projects)");

        cout << "Project ID | Project Name | Price | Time Needed | Time Purchased\n";
        if (res->next()) {
            cout << res->getInt("project_id") << " | " << res->getString("project_name") << " | " << res->getDouble("price") << " | " <<
                res->getInt("time_needed") << " | " << res->getInt("TimePurchased") << endl;
        }
        delete res;
        delete stmt;
    }
    catch (sql::SQLException& e) {
        cerr << "MySQL Exception: " << e.what() << endl;
    }
}
