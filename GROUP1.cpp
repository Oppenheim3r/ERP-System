#include "GROUP1.h"
#include <iostream>
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/prepared_statement.h>
#include "sqlConn.h"
using namespace std;
info::info() {
    try {
        sql::Connection* con = SQLConn::setupMySQL();
        sql::Statement* stmt = con->createStatement();
        sql::ResultSet* result = stmt->executeQuery("SELECT COUNT(*) AS EmployeeCount FROM Employees");

        if (result->next()) {
            EmployeeCount = result->getInt("EmployeeCount");
        }

        delete result;
        delete stmt;
    }
    catch (sql::SQLException& e) {
        std::cerr << "MySQL Exception: " << e.what() << std::endl;
    }
}
int info::EmployeeCount = 0;
        // class Employees
Employee::Employee() {
}

Employee::Employee(std::string name, int ID, std::string email, std::string position) {
    this->name = name;
    EmployeeID = ID;
    this->email = email;
    this->position = position;
}




// class jobpsition
Jobposition::Jobposition() {
}

void Jobposition::DisplayEmpPosition(sql::Connection* con) {
    try {
        string name;
        cout << "Enter Employee Name: ";
        cin >> name;

        sql::PreparedStatement* selectStmt = con->prepareStatement("SELECT name, position FROM Employees WHERE name = ?");
        selectStmt->setString(1, name);
        sql::ResultSet* result = selectStmt->executeQuery();

        while (result->next()) {
            cout << "Employee: " << result->getString("name") << ", Position: " << result->getString("position") << endl;
        }


        delete result;
        delete selectStmt;
    }
    catch (sql::SQLException& e) {
        cerr << "MySQL Exception: " << e.what() << endl;
    }

}

void Jobposition::ChangeEmpPosition(sql::Connection* con) {
    string name;
    string pos;

    cout << "Enter the employee's Name: ";
    cin >> name;

    try {
        sql::PreparedStatement* selectStmt = con->prepareStatement("SELECT id FROM Employees WHERE name = ?");
        selectStmt->setString(1, name);


        sql::ResultSet* result = selectStmt->executeQuery();

        if (result->next()) {
            cout << "Enter the new position: ";
            cin >> pos;

            int employeeId = result->getInt("id");

            delete result;

            sql::PreparedStatement* updateStmt = con->prepareStatement("UPDATE Employees SET position = ? WHERE name = ?");
            updateStmt->setString(1, pos);
            updateStmt->setString(2, name);

            updateStmt->executeUpdate();
            cout << "Employee position updated successfully." << endl;
            delete updateStmt;
        }
        else {
            cout << "Employee not found." << endl;
        }


        delete selectStmt;
    }
    catch (sql::SQLException& e) {
        cerr << "MySQL Exception: " << e.what() << endl;
    }
}

void Jobposition::RemoveEmployee(sql::Connection* con) {
    if (EmployeeCount == 0) {
        cout << "There are No Employees to remove." << endl;
    }
    else {
        
        string name;
        cout << "Enter the Name of the Employee: ";
        cin >> name;
        

        try {
            sql::PreparedStatement* selectStmt = con->prepareStatement("SELECT id, name FROM Employees WHERE name = ?");
            selectStmt->setString(1, name);
            sql::ResultSet* result = selectStmt->executeQuery();

            cout << "Matching Employees:\n";
            while (result->next()) {
                cout << "ID: " << result->getInt("id") << " - " << result->getString("name") << endl;
            }

            delete result;
            delete selectStmt;
            bool sure = false;
            int x;
            int idToDelete;
            cout << "Enter the ID of the employee you want to delete: ";
            cin >> idToDelete;
            cout << "\nAre you sure you want to delete this employee ?";
            cout << "\n1. Yes";
            cout << "\n2. No";
            cin >> x;
            switch (x) {
            case 1:
                sure = true;
                break;
            case 2:
                sure = false;
                break;
            default:
                cout << "Try again , must be 1 or 2 ";
            }
            if (sure == true) {
                try {
                    sql::PreparedStatement* deleteStmt = con->prepareStatement("DELETE FROM Employees WHERE id = ?");
                    deleteStmt->setInt(1, idToDelete);
                    deleteStmt->execute();
                    delete deleteStmt;


                    EmployeeCount--;

                    cout << "Employee with ID " << idToDelete << " removed successfully." << endl;
                }
                catch (sql::SQLException& e) {
                    cerr << "MySQL Exception: " << e.what() << endl;
                }
            }
            else
                cout << "\nThe process has been stopped . ";
           
            
        }
        catch (sql::SQLException& e) {
            cerr << "MySQL Exception: " << e.what() << endl;
        }
    }
}
       // class HR
HumanResources::HumanResources() {
    max_emp = 100;
}

void HumanResources::AddEmployee(sql::Connection* con) {
    string name;
    string email;
    string position;
    double salary;
    if (EmployeeCount >= max_emp)
        cout << "The number of Employees has reached its maximum , You cannot add a new employee" << endl;
    else {
        cout << "Enter Employee Name: " << endl;
        getline(cin, name);
        cout << "Enter Employee Email: " << endl;
        cin >> email;
        cout << "Enter Employee Position: " << endl;
        cin >> position;
        cout << "Enter Employee Salary: " << endl;
        cin >> salary;

        try {
            sql::PreparedStatement* pstmt = con->prepareStatement("INSERT INTO employees (name, email, position,salary) VALUES (?, ?, ?,?)");
            pstmt->setString(1, name);
            pstmt->setString(2, email);
            pstmt->setString(3, position);
            pstmt->setDouble(4, salary);
            pstmt->execute();
            delete pstmt;

            cout << "Employee added successfully." << endl;
        }
        catch (sql::SQLException& e) {
            cerr << "MySQL Exception: " << e.what() << endl;
        }


    }
}

void HumanResources::DisplayAllEmp(sql::Connection* con) {
    try {
        sql::Statement* stmt = con->createStatement();
        sql::ResultSet* res = stmt->executeQuery("SELECT * FROM employees");

        while (res->next()) {
            cout << "ID: " << res->getInt("id") << ", Name: " << res->getString("name") << ", Email:  " << res->getString("email")
                << ",Position :" << res->getString("position") << ", Salary :" << res->getDouble("salary") << endl;
        }
        delete res;
        delete stmt;

    }
    catch (sql::SQLException& e) {
        cerr << "MySQL Exception: " << e.what() << endl;
    }

}
       // class SM
void SalaryManagement::SalaryDeduction(sql::Connection* con) {
    double salaryy;
    cout << "Choose:\n";
    cout << "1. All Employees\n";
    cout << "2. Specific Employee\n";
    cin >> c1;

    if (c1 == 1) {
        cout << "Choose:\n";
        cout << "1. Amount\n";
        cout << "2. Percentage\n";
        cin >> c2;

        if (c2 == 1) {
            cout << "Enter the amount:\n";
            cin >> amount;

            try {

                sql::PreparedStatement* updateStmt = con->prepareStatement("UPDATE Employees SET salary = salary - ?");
                updateStmt->setDouble(1, amount);
                updateStmt->executeUpdate();
                delete updateStmt;

                cout << "Salary deduction for all employees successful.\n";
            }
            catch (sql::SQLException& e) {
                cerr << "MySQL Exception: " << e.what() << endl;
            }
        }
        else if (c2 == 2) {
            cout << "Enter the percentage:\n";
            cin >> percentage;

            try {

                sql::PreparedStatement* updateStmt = con->prepareStatement("UPDATE Employees SET salary = salary - (salary * ? / 100)");
                updateStmt->setDouble(1, percentage);
                updateStmt->executeUpdate();
                delete updateStmt;

                cout << "Salary deduction for all employees successful.\n";
            }
            catch (sql::SQLException& e) {
                cerr << "MySQL Exception: " << e.what() << endl;
            }
        }
        else {
            cout << "Wrong choice.\n";
        }
    }
    else if (c1 == 2) {
        string name;
        cout << "Enter the name of the Employee: ";
        cin >> name;

        cout << "Choose:\n";
        cout << "1. Amount\n";
        cout << "2. Percentage\n";
        cin >> c2;

        if (c2 == 1) {
            cout << "Enter the amount:\n";
            cin >> amount;

            try {

                sql::PreparedStatement* updateStmt = con->prepareStatement("UPDATE Employees SET salary = salary - ? WHERE name = ?");
                updateStmt->setDouble(1, amount);
                updateStmt->setString(2, name);
                updateStmt->executeUpdate();
                delete updateStmt;

                cout << "Salary deduction for employee  " << name << " successful.\n";
            }
            catch (sql::SQLException& e) {
                cerr << "MySQL Exception: " << e.what() << endl;
            }
        }
        else if (c2 == 2) {
            cout << "Enter the percentage:\n";
            cin >> percentage;

            try {

                sql::PreparedStatement* updateStmt = con->prepareStatement("UPDATE Employees SET salary = salary - (salary * ? / 100) WHERE name = ?");
                updateStmt->setDouble(1, percentage);
                updateStmt->setString(2, name);
                updateStmt->executeUpdate();
                delete updateStmt;

                cout << "Salary deduction for employee  " << name << " successful.\n";
            }
            catch (sql::SQLException& e) {
                cerr << "MySQL Exception: " << e.what() << endl;
            }
        }
        else {
            cout << "Wrong choice.\n";
        }
    }
}

void SalaryManagement::SalaryBonus(sql::Connection* con) {
    double salaryy;
    cout << "Choose:\n";
    cout << "1. All Employees\n";
    cout << "2. Specific Employee\n";
    cin >> c1;

    if (c1 == 1) {
        cout << "Choose:\n";
        cout << "1. Amount\n";
        cout << "2. Percentage\n";
        cin >> c2;

        if (c2 == 1) {
            cout << "Enter the amount:\n";
            cin >> amount;

            try {

                sql::PreparedStatement* updateStmt = con->prepareStatement("UPDATE Employees SET salary = salary + ?");
                updateStmt->setDouble(1, amount);
                updateStmt->executeUpdate();
                delete updateStmt;

                cout << "Salary bonus for all employees successful.\n";
            }
            catch (sql::SQLException& e) {
                cerr << "MySQL Exception: " << e.what() << endl;
            }
        }
        else if (c2 == 2) {
            cout << "Enter the percentage:\n";
            cin >> percentage;

            try {

                sql::PreparedStatement* updateStmt = con->prepareStatement("UPDATE Employees SET salary = salary + (salary * ? / 100)");
                updateStmt->setDouble(1, percentage);
                updateStmt->executeUpdate();
                delete updateStmt;

                cout << "Salary bonus for all employees successful.\n";
            }
            catch (sql::SQLException& e) {
                cerr << "MySQL Exception: " << e.what() << endl;
            }
        }
        else {
            cout << "Wrong choice.\n";
        }
    }
    else if (c1 == 2) {
        int employeeId;
        cout << "Enter the ID of the Employee: ";
        cin >> employeeId;

        cout << "Choose:\n";
        cout << "1. Amount\n";
        cout << "2. Percentage\n";
        cin >> c2;

        if (c2 == 1) {
            cout << "Enter the amount:\n";
            cin >> amount;

            try {

                sql::PreparedStatement* updateStmt = con->prepareStatement("UPDATE Employees SET salary = salary + ? WHERE id = ?");
                updateStmt->setDouble(1, amount);
                updateStmt->setInt(2, employeeId);
                updateStmt->executeUpdate();
                delete updateStmt;

                cout << "Salary bonus for employee ID " << employeeId << " successful.\n";
            }
            catch (sql::SQLException& e) {
                cerr << "MySQL Exception: " << e.what() << endl;
            }
        }
        else if (c2 == 2) {
            cout << "Enter the percentage:\n";
            cin >> percentage;

            try {

                sql::PreparedStatement* updateStmt = con->prepareStatement("UPDATE Employees SET salary = salary + (salary * ? / 100) WHERE id = ?");
                updateStmt->setDouble(1, percentage);
                updateStmt->setInt(2, employeeId);
                updateStmt->executeUpdate();
                delete updateStmt;

                cout << "Salary bonus for employee ID " << employeeId << " successful.\n";
            }
            catch (sql::SQLException& e) {
                cerr << "MySQL Exception: " << e.what() << endl;
            }
        }
        else {
            cout << "Wrong choice.\n";
        }
    }
}

double SalaryManagement::TotalSalaries(sql::Connection* con) {
    double Total = 0;

    try {

        sql::Statement* stmt = con->createStatement();
        sql::ResultSet* result = stmt->executeQuery("SELECT SUM(salary) AS TotalSalaries FROM Employees");

        if (result->next()) {
            Total = result->getDouble("TotalSalaries");
        }


        delete result;
        delete stmt;
    }
    catch (sql::SQLException& e) {
        cerr << "MySQL Exception: " << e.what() << endl;
    }

    return Total;
}

void SalaryManagement::ChangeSalary(sql::Connection* con) {
    string namee;
    cout << "Enter the name of Employee:\n";
    cin.ignore();
    getline(cin, namee);

    try {

        sql::PreparedStatement* selectStmt = con->prepareStatement("SELECT id, name, salary FROM Employees WHERE name = ?");
        selectStmt->setString(1, namee);
        sql::ResultSet* result = selectStmt->executeQuery();

        cout << "Matching Employees:\n";
        while (result->next()) {
            cout << "ID: " << result->getInt("id") << ", Name: " << result->getString("name") << ", Salary: " << result->getDouble("salary") << endl;
        }


        delete result;
        delete selectStmt;


        double newSalary;
        cout << "Enter the New Salary:\n";
        cin >> newSalary;


        sql::PreparedStatement* updateStmt = con->prepareStatement("UPDATE Employees SET salary = ? WHERE name = ?");
        updateStmt->setDouble(1, newSalary);
        updateStmt->setString(2, namee);
        updateStmt->executeUpdate();


        delete updateStmt;

        cout << "Salary change for employee " << namee << " successful.\n";
    }
    catch (sql::SQLException& e) {
        cerr << "MySQL Exception: " << e.what() << endl;
    }
}


