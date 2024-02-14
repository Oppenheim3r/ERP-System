#include "GROUP1.h"
#include "GROUP2.h"
#include "GROUP4.h"
#include <iostream>
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/prepared_statement.h>
#include "sqlConn.h"
using namespace std;

// User
void User:: Services(sql::Connection* con) {
	int c;
	char order;
	bool check;
	bool exit1 = true;
	bool exit2 = true;

	int qun, Total;
	do {
		exit2 = true;
		cout << "Welome ..\n\n";
		cout << "choose : " << endl;
		cout << "1. Hradware \n";
		cout << "2. Software \n";
		cout << "3. View previoud orders \n";
		cout << "4. Exit \n";
		cout << "[ ]\b\b";
		cin >> c;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid input. Please enter a number.\n";
			continue;
		}
		switch (c) {
		case 1: {
			while (exit2 == true) {
				DisplayAllProduct(con);
				cout << endl;
				cout << "Do You Want To Order ? (Y/N): ";
				cin >> order;
				order = toupper(order);
				if (order == 'N') {
					exit2 = false;
					cout << "Thank You .\n\n";

				}
				else if (order == 'Y') {
					cout << "Enter Product ID : ";
					cin >> Product_ID;
					if (!ProductExists(con, Product_ID)) {
						cout << "Product With ID " << Product_ID << " Does Not Exists .\n";
					}
					else {
						cout << "Enter Your Information Befor Ordering ..\n";
						int log;
						cout << "1. Log in \n";
						cout << "2. Sign Up \n";
						cout << "choose [ ]\b\b";
						cin >> log;
						switch (log) {
						case 1:
						{
							if (!Login(Customer_ID, con)) {
								cout << "You have not an account , You need to sign up .\n";
								Customer_ID = insertCustomer(check, con);
								if (check == true) {
									displayProductById(Product_ID, con);
									cout << "Enter the quantity you want :";
									cin >> qun;
									while (!CheckTheQuantity(Product_ID, qun, con)) {
										exit2 == false;
										cout << "Try Again .";
										cin >> qun;
									}
									Total = CalculationTheAmount(Product_ID, qun, con);
									cin >> amount_paid;
									AddOrderProduct(Product_ID, Customer_ID, qun, amount_paid, Total, con);

								}
								else {
									cout << "There is a problem entring your information .";

								}
							}
							else {
								displayProductById(Product_ID, con);
								cout << "Enter the quantity you want :";
								cin >> qun;
								while (!CheckTheQuantity(Product_ID, qun, con)) {
									exit2 == false;
									cout << "Try Again .";
									cin >> qun;
								}
								Total = CalculationTheAmount(Product_ID, qun, con);
								cin >> amount_paid;
								AddOrderProduct(Product_ID, Customer_ID, qun, amount_paid, Total, con);
							}

						}
						break;
						case 2: {
							Customer_ID = insertCustomer(check, con);
							if (check == true) {
								displayProductById(Product_ID, con);
								cout << "Enter the quantity you want :";
								cin >> qun;
								while (!CheckTheQuantity(Product_ID, qun, con)) {
									exit2 == false;
									cout << "Try Again .";
									cin >> qun;
								}
								Total = CalculationTheAmount(Product_ID, qun, con);
								cin >> amount_paid;
								AddOrderProduct(Product_ID, Customer_ID, qun, amount_paid, Total, con);

							}
							else {
								cout << "There is a problem entring your information .";

							}
						}
							  break;
						default:
							cout << "Wrong Input .\n";
						}

					}
				}
				else {
					exit2 = false;
					cout << "Invalid input. Please enter 'Y' for Yes or 'N' for No.\n";

				}


			}
		}

			  break;
		case 2: {
			while (exit2 == true) {
				DisplayAllProjects(con);
				cout << endl;
				cout << "Do You Want To Order ? (Y/N): ";
				cin >> order;
				order = toupper(order);
				if (order == 'N') {
					exit2 = false;
					cout << "Thank You .\n\n";

				}
				else if (order == 'Y') {
					cout << "Enter Project ID : ";
					cin >> Project_ID;
					if (!ProjectExists(con, Project_ID)) {
						cout << "Project With ID " << Project_ID << " Does Not Exists .\n";
					}
					else {
						cout << "Enter Your Information Befor Ordering ..\n";
						int log;
						cout << "1. Log in \n";
						cout << "2. Sign Up \n";
						cout << "choose [ ]\b\b";
						cin >> log;
						switch (log) {
						case 1:
						{
							if (!Login(Customer_ID, con)) {
								cout << "You have not an account , You need to sign up .\n";
								Customer_ID = insertCustomer(check, con);
								if (check == true) {
									displayProjectById(Project_ID, con);
									cout << "Enter the project price : \n";
									cin >> amount_paid;
									addOrder(Project_ID, Customer_ID, amount_paid, con);
								}
								else {
									cout << "There is a problem entring your information .";
								}
							}
							else {
								displayProjectById(Project_ID, con);
								cout << "Enter the project price : \n";
								cin >> amount_paid;
								addOrder(Project_ID, Customer_ID, amount_paid, con);
							} }
						break;
						case 2: {
							Customer_ID = insertCustomer(check, con);
							if (check == true) {
								displayProjectById(Project_ID, con);
								cout << "Enter the project price : \n";
								cin >> amount_paid;
								addOrder(Project_ID, Customer_ID, amount_paid, con);
							}
							else {
								cout << "There is a problem entring your information .";
							}
						}
							  break;
						default:
							cout << "Wrong Input .\n";
						}
					}
				}
				else {
					exit2 = false;
					cout << "Invalid input. Please enter 'Y' for Yes or 'N' for No.\n";

				}
			}
		}
			  break;
		case 3: {
			while (exit2 == true) {

				if (!Login(Customer_ID, con)) {
					cout << "You have no previous orders .\n";
				}
				else {
					int Rows = 0;
					try {
						sql::PreparedStatement* Stmt = con->prepareStatement("SELECT COUNT(*) AS 'Rows' FROM orderproduct WHERE customer_id =? ");
						Stmt->setInt(1, Customer_ID);
						sql::ResultSet* result = Stmt->executeQuery();

						if (result->next()) {
							Rows = result->getInt("Rows");
						}
						delete result;
						delete Stmt;
						/////////
						sql::PreparedStatement* prst = con->prepareStatement("SELECT * FROM orderproduct WHERE customer_id =? ");
						prst->setInt(1, Customer_ID);
						sql::ResultSet* res = prst->executeQuery();
						cout << "Product order : \n";
						if (Rows == 1) {
							cout << "ID | Product ID | Customer ID| Quantity | Amount Paid | Order Date | \n";
							if (res->next()) {
								cout << res->getInt("order_id") << " | "
									<< res->getInt("product_id") << " | "
									<< res->getInt("customer_id") << " | "
									<< res->getInt("quantity_ordered") << " | "
									<< res->getDouble("amount_paid") << " | "
									<< res->getString("order_date") << " | "
									<< endl;
							}
						}
						else if (Rows > 1) {
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
						}
						else if (Rows == 0) {
							cout << "There are no product orders .\n";
						}
						delete res;
						delete prst;

					}
					catch (sql::SQLException& e) {

						cerr << "MySQL Exception: " << e.what() << endl;

					}

					try {
						sql::PreparedStatement* Stmt = con->prepareStatement("SELECT COUNT(*) AS 'Rows' FROM orderproject WHERE customer_id =? ");
						Stmt->setInt(1, Customer_ID);
						sql::ResultSet* result = Stmt->executeQuery();

						if (result->next()) {
							Rows = result->getInt("Rows");
						}
						delete result;
						delete Stmt;
						////////
						sql::PreparedStatement* prst = con->prepareStatement("SELECT * FROM orderproject WHERE customer_id =? ");
						prst->setInt(1, Customer_ID);
						sql::ResultSet* res = prst->executeQuery();

						cout << "Project order : \n";
						if (Rows == 1) {
							cout << "ID | Project ID | Customer ID | Amount Paid | Order Date | Date to be Ready\n";
							if (res->next()) {
								cout << res->getInt("order_id") << " | "
									<< res->getInt("project_id") << " | "
									<< res->getInt("customer_id") << " | "
									<< res->getDouble("amount_paid") << " | "
									<< res->getString("order_date") << " | "
									<< res->getString("date_to_be_ready") << endl;
							}
						}
						else if (Rows > 1) {
							cout << "ID | Project ID | Customer ID | Amount Paid | Order Date | Date to be Ready\n";
							while (res->next()) {
								cout << res->getInt("order_id") << " | "
									<< res->getInt("project_id") << " | "
									<< res->getInt("customer_id") << " | "
									<< res->getDouble("amount_paid") << " | "
									<< res->getString("order_date") << " | "
									<< res->getString("date_to_be_ready") << endl;
							}
						}
						else if (Rows == 0) {
							cout << "There are no project orders .\n";
						}

						delete res;
						delete prst;

					}
					catch (sql::SQLException& e) {

						cerr << "MySQL Exception: " << e.what() << endl;

					}

				}
				cout << "Press 1 to exit : ";
				int l;
				cin >> l;
				if (l == 1) { exit2 = false; }
			}
		}
			  break;
		case 4:
			exit1 = false;
			break;
		default:
			cout << "Wrong Input .";
		}

		system("cls");
	} while (exit1 == true);

}
