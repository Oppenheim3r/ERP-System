#include "GROUP1.h"
#include "GROUP2.h"
#include "GROUP3.h"
#include "GROUP4.h"
#include <iostream>
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/prepared_statement.h>
#include "sqlConn.h"
using namespace std;

bool authenticate(sql::Connection* con, const string& email, const string& password, string& position) {
    try {
        sql::PreparedStatement* pstmt = con->prepareStatement("SELECT * FROM employees WHERE email = ? AND password = ?");
        pstmt->setString(1, email);
        pstmt->setString(2, password);

        sql::ResultSet* res = pstmt->executeQuery();

        if (res->next()) {
            position = res->getString("position");
            delete res;
            delete pstmt;
            return true;
        }

        delete res;
        delete pstmt;
    }
    catch (sql::SQLException& e) {
        cerr << "SQL Error: " << e.what() << endl;
    }

    return false;
}


int main() {
    sql::Connection* con = SQLConn::setupMySQL();
    int option;
    int attempts;
    bool home = true;
    do {
        for (attempts = 3; attempts > 0; attempts--) {
            cout << "Choose an option to login:" << endl;
            cout << "1. Admin" << endl;
            cout << "2. Employee" << endl;
            cout << "3. User" << endl;
            cout << "Enter your choice: ";

            if (!(cin >> option)) {
                cout << "Invalid input. Please enter a number." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }

            if (option == 1) {
                cout << "Login as Admin" << endl;
            }
            else if (option == 2) {
                cout << "Login as Employee" << endl;
            }
            else if (option == 3) {
                cout << "Logged in as User" << endl;
                User obj;
                obj.Services(con);
                break;
            }
            else {
                cout << "Invalid option. Please try again." << endl;
                continue;
            }

            if (option == 3) {
                break;
            }

            string email, password;
            cout << "Enter email: ";
            cin >> email;

            cout << "Enter password: ";
            cin >> password;

            string position;
            if (authenticate(con, email, password, position)) {
                if (position == "Manager") {
                    cout << "Logged in as Admin" << endl;

                    Admin obj;
                    obj.opreation(con);
                }
                else {
                    cout << "Logged in as Employee" << endl;
                    EMP obj;
                    obj.Control(con);
                }
                break;
            }
            else {
                cout << "Invalid credentials. Please try again." << endl;
            }
        }

        if (attempts == 0) {
            cout << "Maximum login attempts reached. Exiting..." << endl;
            home = false;
        }
    } while (home == true);


    delete con;

    return 0;
}
