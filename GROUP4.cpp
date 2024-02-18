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

     // class Admin
void Admin :: opreation(sql::Connection* con) {
	bool exit1 = true;
	bool exit2 = true;
	int r1;
	int r2;
	do {
		exit1 = true;
		exit2 = true;
		cout << "Welcome to Admin dashboard ..\n\n";
		cout << "choose : \n";
		cout << "1. Employees Management \n";
		cout << "2. Employees Accounts\n";
		cout << "3. Salary Management  \n";
		cout << "4. Product Management \n";
		cout << "5. Project Management \n";
		cout << "6. Customer Management  \n";
		cout << "7. Vendor Management  \n";
		cout << "8. Order Management   \n";
		cout << "9. Employee and Project Management \n";
		cout << "10. Fianacial Management \n";
		cout << "11. Warehouse Management \n";
		cout << "12. Logs Management\n";
		cout << "13. Quality Management \n";
		cout << "14. Exit \n";
		cout << "[  ]\b\b\b";
		cin >> r1;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid input. Please enter a number.\n";
			continue;
		}
		switch (r1) {
		case 1: {
			while (exit2 == true) {
				exit2 = true;
				cout << "\nchoose :\n";
				cout << "1. Display All Employees \n";
				cout << "2. Add New Employee \n";
				cout << "3. Remove Employee \n";
				cout << "4. Display Employee Position\n";
				cout << "5. Change Employee Position\n";
				cout << "6. Exit\n";
				cout << "7. Home \n";
				cout << "[ ]\b\b";
				cin >> r2;
				if (cin.fail()) {
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "Invalid input. Please enter a number.\n";
					continue;
				}
				switch (r2) {
				case 1:HumanResources::DisplayAllEmp(con);
					break;
				case 2: EmployeeBudgetStatues(con);
					HumanResources::AddEmployee(con);
					break;
				case 3:RemoveEmployee(con);
					break;
				case 4:DisplayEmpPosition(con);
					break;
				case 5:ChangeEmpPosition(con);
					break;
				case 6:exit2 = false;
					break;
				case 7:exit1 = false;
					exit2 = false;
					break;
				default:
					cout << "Wrong input , Try again .\n";
				}
			}

		}
			  break;
		case 2: {
			while (exit2 == true) {
				exit2 = true;
				cout << "\nchoose :\n";
				cout << "1. Assign Password \n";
				cout << "2. Display Employees With Credentials\n";
				cout << "3. Exit\n";
				cout << "4. Home \n";
				cout << "[ ]\b\b";
				cin >> r2;
				if (cin.fail()) {
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "Invalid input. Please enter a number.\n";
					continue;
				}
				switch (r2) {
				case 1: assignPassword(con);
				break;
                                case 2:displayEmployeesWithCredentials(con);
				break;
				case 3:exit2 = false;
					break;
				case 4:exit1 = false;
					exit2 = false;
					break;
				default:
					cout << "Wrong input , Try again .\n";
				}
			}

		}
			  break;
		case 3: {
			while (exit2 == true) {
				cout << "\nchoose :\n";
				cout << "1. Salary Deducation \n";
				cout << "2. Salary Bouns \n";
				cout << "3. Display Total Salaries \n";
				cout << "4. Change Salary For employee \n";
				cout << "5. Exit\n";
				cout << "6. Home \n";
				cout << "[ ]\b\b";
				cin >> r2;
				if (cin.fail()) {
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "Invalid input. Please enter a number.\n";
					continue;
				}
				switch (r2) {
				case 1:SalaryManagement::SalaryDeduction(con);
					break;
				case 2:SalaryManagement::SalaryBonus(con);
					break;
				case 3:SalaryManagement::TotalSalaries(con);
					break;
				case 4:SalaryManagement::ChangeSalary(con);
					break;
				case 5:exit2 = false;
					break;
				case 6: exit1 = false;
					exit2 = false;
					break;
				default:
					cout << "Wrong Input ." << endl;
				}
			}
		}
			  break;
		case 4:
		{
			while (exit2 == true) {
				cout << "\nchoose :\n";
				cout << "1. Display All Products \n";
				cout << "2. Add Product\n";
				cout << "3. Update Product \n";
				cout << "4. Delete Product \n";
				cout << "5. Exit\n";
				cout << "6. Home \n";
				cout << "[ ]\b\b";
				cin >> r2;
				if (cin.fail()) {
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "Invalid input. Please enter a number.\n";
					continue;
				}
				switch (r2) {
				case 1: Product::DisplayAllProduct(con);
					break;
				case 2:Product::AddProduct(con);
					break;
				case 3:Product::UpdateProduct(con);
					break;
				case 4:Product::DeleteProduct(con);
					break;
				case 5:exit2 = false;
					break;
				case 6: exit1 = false;
					exit2 = false;
					break;
				default:
					cout << "Wrong Input ." << endl;
				}
			}
		}
		break;
		case 5:
		{
			while (exit2 == true) {
				cout << "\nchoose :\n";
				cout << "1. Display All Projects \n";
				cout << "2. Add Project\n";
				cout << "3. Update Project \n";
				cout << "4. Delete Project \n";
				cout << "5. Exit\n";
				cout << "6. Home \n";
				cout << "[ ]\b\b";
				cin >> r2;
				if (cin.fail()) {
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "Invalid input. Please enter a number.\n";
					continue;
				}
				switch (r2) {
				case 1: Project::DisplayAllProjects(con);
					break;
				case 2: Project::InsertProject(con);
					break;
				case 3:Project::UpdateProject(con);
					break;
				case 4: Project::DeleteProject(con);
					break;
				case 5:exit2 = false;
					break;
				case 6: exit1 = false;
					exit2 = false;
					break;
				default:
					cout << "Wrong Input ." << endl;
				}
			}
		}
		break;
		case 6: {
			while (exit2 == true) {
				cout << "\nchoose :\n";
				cout << "1. Display All Customers \n";
				cout << "2. Display a Speceific Customer\n";
				cout << "3. Add Customer\n";
				cout << "4. Delete Customer \n";
				cout << "5. Exit\n";
				cout << "6. Home \n";
				cout << "[ ]\b\b";
				cin >> r2;
				if (cin.fail()) {
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "Invalid input. Please enter a number.\n";
					continue;
				}
				switch (r2) {
				case 1: displayAllCustomers(con);
					break;
				case 2:displayCustomerById(con);
					break;
				case 3:insertCustomer(con);
					break;
				case 4:deleteCustomer(con);
					break;
				case 5:exit2 = false;
					break;
				case 6: exit1 = false;
					exit2 = false;
					break;
				default:
					cout << "Wrong Input ." << endl;
				}
			}
		}
			  break;
		case 7: {
			while (exit2 == true) {
				cout << "\nchoose :\n";
				cout << "1. Display All Vendors \n";
				cout << "2. Display a Speceific Vendor\n";
				cout << "3. Add Vendor\n";
				cout << "4. Delete Vendor \n";
				cout << "5. Exit\n";
				cout << "6. Home \n";
				cout << "[ ]\b\b";
				cin >> r2;
				if (cin.fail()) {
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "Invalid input. Please enter a number.\n";
					continue;
				}
				switch (r2) {
				case 1: displayAllVendors(con);
					break;
				case 2:displayVendorById(con);
					break;
				case 3:insertVendor(con);
					break;
				case 4:deleteVendor(con);
					break;
				case 5:exit2 = false;
					break;
				case 6: exit1 = false;
					exit2 = false;
					break;
				default:
					cout << "Wrong Input ." << endl;
				}
			}
		}
			  break;
		case 8: { while (exit2 == true) {
			cout << "\nchoose :\n";
			cout << "1. Display All Product Orders \n";
			cout << "2. Display All Project Orders\n";
			cout << "3. Remove Order from Products Orders \n";
			cout << "4. Remove Order from Projects Orders \n";
			cout << "5. Exit\n";
			cout << "6. Home \n";
			cout << "[ ]\b\b";
			cin >> r2;
			if (cin.fail()) {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Invalid input. Please enter a number.\n";
				continue;
			}
			switch (r2) {
			case 1:DisplayAllProductOrders(con);
				break;
			case 2: displayAllOrders(con);
				break;
			case 3:RemoveProductOrder(con);
				break;
			case 4:removeOrder(con);
				break;
			case 5:exit2 = false;
				break;
			case 6: exit1 = false;
				exit2 = false;
				break;
			default:
				cout << "Wrong Input ." << endl;
			}
		}
		}
			  break;
		case 9: {
			while (exit2 == true) {
				cout << "\nchoose :\n";
				cout << "1. Display Employees And Thier Projects \n";
				cout << "2. Insert Employee To Project \n";
				cout << "3. Delete Employee From Project\n";
				cout << "4. Update Employee Projects \n";
				cout << "5. Exit\n";
				cout << "6. Home \n";
				cout << "[ ]\b\b";
				cin >> r2;
				if (cin.fail()) {
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "Invalid input. Please enter a number.\n";
					continue;
				}
				switch (r2) {
				case 1: DisplayProjectEmployees(con);
					break;
				case 2: insertEmployeeToProject(con);
					break;
				case 3:deleteEmployeeFromProject(con);
					break;
				case 4:updateProjectEmployees(con);
					break;
				case 5:exit2 = false;
					break;
				case 6: exit1 = false;
					exit2 = false;
					break;
				default:
					cout << "Wrong Input ." << endl;
				}
			}
		}
			  break;
		case 10: {
			while (exit2 == true) {
				exit2 = true;
				cout << "\nchoose :\n";
				cout << "1. Display Budget Table \n";
				cout << "2. Change Budgets \n";
				cout << "3. Edit Product Price \n";
				cout << "4. Display Products To Buy\n";
				cout << "5. Add Product To Buy\n";
				cout << "6. Approve Product\n";
				cout << "7. Exit\n";
				cout << "8. Home \n";
				cout << "[ ]\b\b";
				cin >> r2;
				if (cin.fail()) {
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "Invalid input. Please enter a number.\n";
					continue;
				}
				switch (r2) {
				case 1:Display_Budget_table(con);
					break;
				case 2: ChangeBudgets(con);
					break;
				case 3:editProductPrice(con);
					break;
				case 4:displayProductsToBuy(con);
					break;
				case 5:ProductBudgetStatues(con);
					insertProductToBuy(con);
					break;
				case 6:approveProduct(con);
					break;
				case 7:exit2 = false;
					break;
				case 8:exit1 = false;
					exit2 = false;
					break;
				default:
					cout << "Wrong input , Try again .\n";
				}
			}

		}
			   break;
		case 11: {
			while (exit2 == true) {
				exit2 = true;
				cout << "\nchoose :\n";
				cout << "1. View Products to be ordered \n";
				cout << "2. Display Approved Products \n";
				cout << "3. Insert Approved Products \n";
				cout << "4. Exit\n";
				cout << "5. Home \n";
				cout << "[ ]\b\b";
				cin >> r2;
				if (cin.fail()) {
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "Invalid input. Please enter a number.\n";
					continue;
				}
				switch (r2) {
				case 1:productsToOrder(con);
					break;
				case 2:displayApprovedProducts(con);
					break;
				case 3:insertApprovedProducts(con);
					break;
				case 4:exit2 = false;
					break;
				case 5:exit1 = false;
					exit2 = false;
					break;
				default:
					cout << "Wrong input , Try again .\n";
				}
			}

		}
			   break;
		case 12: {
			while (exit2 == true) {
				exit2 = true;
				cout << "\nchoose :\n";
				cout << "1. View Logs \n";
				cout << "2. Exit\n";
				cout << "3. Home \n";
				cout << "[ ]\b\b";
				cin >> r2;
				if (cin.fail()) {
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "Invalid input. Please enter a number.\n";
					continue;
				}
				switch (r2) {
				case 1:view_logs(con);
					break;
				case 2:exit2 = false;
					break;
				case 3:exit1 = false;
					exit2 = false;
					break;
				default:
					cout << "Wrong input , Try again .\n";
				}
			}

		}
			   break;
		case 13: {
			while (exit2 == true) {
				cout << "\nchoose :\n";
				cout << "1. Display Most Requsted Product\n";
				cout << "2. Display Most Requsted Project\n";
				cout << "3. Display The Profit or Loss Precentage of Products\n";
				cout << "4. Exit\n";
				cout << "5. Home \n";
				cout << "[ ]\b\b";
				cin >> r2;
				if (cin.fail()) {
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "Invalid input. Please enter a number.\n";
					continue;
				}
				switch (r2) {
				case 1: Most_Requested_Product(con);
					break;
				case 2:Most_Requested_Project(con);
					break;
				case 3:profit_and_loss(con);
					break;
					break;
				case 4:exit2 = false;
					break;
				case 5: exit1 = false;
					exit2 = false;
					break;
				default:
					cout << "Wrong Input ." << endl;
				}
			}
		}
			   break;
		case 14: exit1 = false;
			break;
		default:
			cout << "Wrong Input .";
		}
		system("cls");
	} while (exit1 == true);

}

// class EMP
void EMP::Control(sql::Connection* con) {
	bool exit1 = true;
	bool exit2 = true;
	int r1;
	int r2;
	do {
		exit1 = true;
		exit2 = true;
		cout << "Welcome to Employee dashboard ..\n\n";
		cout << "choose : \n";
		cout << "1. Employees Control \n";
		cout << "2. Product Control \n";
		cout << "3. Project Control \n";
		cout << "4. Customer Control  \n";
		cout << "5. Vendor Control  \n";
		cout << "6. Order Control   \n";
		cout << "7. Employee and Project Control \n";
		cout << "8. Fianacial Control \n";
		cout << "9. Warehouse Control \n";
		cout << "10. Quality Control \n";
		cout << "11. Exit \n";
		cout << "[  ]\b\b\b";
		cin >> r1;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid input. Please enter a number.\n";
			continue;
		}
		switch (r1) {
		case 1: {
			while (exit2 == true) {
				exit2 = true;
				cout << "\nchoose :\n";
				cout << "1. Display All Employees \n";
				cout << "2. Display Employee Position\n";
				cout << "3. Exit\n";
				cout << "4. Home \n";
				cout << "[ ]\b\b";
				cin >> r2;
				if (cin.fail()) {
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "Invalid input. Please enter a number.\n";
					continue;
				}
				switch (r2) {
				case 1:HumanResources::DisplayAllEmp(con);
					break;
				case 2:DisplayEmpPosition(con);
					break;
				case 3:exit2 = false;
					break;
				case 4:exit1 = false;
					exit2 = false;
					break;
				default:
					cout << "Wrong input , Try again .\n";
				}
			}

		}
			  break;
		case 2:
		{
			while (exit2 == true) {
				cout << "\nchoose :\n";
				cout << "1. Display All Products \n";
				cout << "2. Add Product\n";
				cout << "3. Update Product \n";
				cout << "4. Delete Product \n";
				cout << "5. Exit\n";
				cout << "6. Home \n";
				cout << "[ ]\b\b";
				cin >> r2;
				if (cin.fail()) {
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "Invalid input. Please enter a number.\n";
					continue;
				}
				switch (r2) {
				case 1: Product::DisplayAllProduct(con);
					break;
				case 2:Product::AddProduct(con);
					break;
				case 3:Product::UpdateProduct(con);
					break;
				case 4:Product::DeleteProduct(con);
					break;
				case 5:exit2 = false;
					break;
				case 6: exit1 = false;
					exit2 = false;
					break;
				default:
					cout << "Wrong Input ." << endl;
				}
			}
		}
		break;
		case 3:
		{
			while (exit2 == true) {
				cout << "\nchoose :\n";
				cout << "1. Display All Projects \n";
				cout << "2. Add Project\n";
				cout << "3. Update Project \n";
				cout << "4. Delete Project \n";
				cout << "5. Exit\n";
				cout << "6. Home \n";
				cout << "[ ]\b\b";
				cin >> r2;
				if (cin.fail()) {
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "Invalid input. Please enter a number.\n";
					continue;
				}
				switch (r2) {
				case 1: Project::DisplayAllProjects(con);
					break;
				case 2: Project::InsertProject(con);
					break;
				case 3:Project::UpdateProject(con);
					break;
				case 4: Project::DeleteProject(con);
					break;
				case 5:exit2 = false;
					break;
				case 6: exit1 = false;
					exit2 = false;
					break;
				default:
					cout << "Wrong Input ." << endl;
				}
			}
		}
		break;
		case 4: {
			while (exit2 == true) {
				cout << "\nchoose :\n";
				cout << "1. Display All Customers \n";
				cout << "2. Display a Speceific Customer\n";
				cout << "3. Exit\n";
				cout << "4. Home \n";
				cout << "[ ]\b\b";
				cin >> r2;
				if (cin.fail()) {
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "Invalid input. Please enter a number.\n";
					continue;
				}
				switch (r2) {
				case 1: displayAllCustomers(con);
					break;
				case 2:displayCustomerById(con);
					break;
				case 3:exit2 = false;
					break;
				case 4: exit1 = false;
					exit2 = false;
					break;
				default:
					cout << "Wrong Input ." << endl;
				}
			}
		}
			  break;
		case 5: {
			while (exit2 == true) {
				cout << "\nchoose :\n";
				cout << "1. Display All Vendors \n";
				cout << "2. Display a Speceific Vendor\n";
				cout << "3. Exit\n";
				cout << "4. Home \n";
				cout << "[ ]\b\b";
				cin >> r2;
				if (cin.fail()) {
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "Invalid input. Please enter a number.\n";
					continue;
				}
				switch (r2) {
				case 1: displayAllVendors(con);
					break;
				case 2:displayVendorById(con);
					break;
				case 3:exit2 = false;
					break;
				case 4: exit1 = false;
					exit2 = false;
					break;
				default:
					cout << "Wrong Input ." << endl;
				}
			}
		}
			  break;
		case 6: { while (exit2 == true) {
			cout << "\nchoose :\n";
			cout << "1. Display All Product Orders \n";
			cout << "2. Display All Project Orders\n";
			cout << "3. Remove Order from Products Orders \n";
			cout << "4. Remove Order from Projects Orders \n";
			cout << "5. Exit\n";
			cout << "6. Home \n";
			cout << "[ ]\b\b";
			cin >> r2;
			if (cin.fail()) {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Invalid input. Please enter a number.\n";
				continue;
			}
			switch (r2) {
			case 1:DisplayAllProductOrders(con);
				break;
			case 2: displayAllOrders(con);
				break;
			case 3:RemoveProductOrder(con);
				break;
			case 4:removeOrder(con);
				break;
			case 5:exit2 = false;
				break;
			case 6: exit1 = false;
				exit2 = false;
				break;
			default:
				cout << "Wrong Input ." << endl;
			}
		}
		}
			  break;
		case 7: {
			while (exit2 == true) {
				cout << "\nchoose :\n";
				cout << "1. Display Employees And Thier Projects \n";
				cout << "2. Exit\n";
				cout << "3. Home \n";
				cout << "[ ]\b\b";
				cin >> r2;
				if (cin.fail()) {
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "Invalid input. Please enter a number.\n";
					continue;
				}
				switch (r2) {
				case 1: DisplayProjectEmployees(con);
					break;
				case 2:exit2 = false;
					break;
				case 3: exit1 = false;
					exit2 = false;
					break;
				default:
					cout << "Wrong Input ." << endl;
				}
			}
		}
			  break;
		case 8: {
			while (exit2 == true) {
				exit2 = true;
				cout << "\nchoose :\n";
				cout << "1. Display Budget Table \n";
				cout << "2. Display Products To Buy\n";
				cout << "3. Exit\n";
				cout << "4. Home \n";
				cout << "[ ]\b\b";
				cin >> r2;
				if (cin.fail()) {
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "Invalid input. Please enter a number.\n";
					continue;
				}
				switch (r2) {
				case 1:Display_Budget_table(con);
					break;
				case 2:displayProductsToBuy(con);
					break;
				case 3:exit2 = false;
					break;
				case 4:exit1 = false;
					exit2 = false;
					break;
				default:
					cout << "Wrong input , Try again .\n";
				}
			}

		}
			  break;
		case 9: {
			while (exit2 == true) {
				exit2 = true;
				cout << "\nchoose :\n";
				cout << "1. View Products to be ordered \n";
				cout << "2. Display Approved Products \n";
				cout << "3. Insert Approved Products \n";
				cout << "4. Exit\n";
				cout << "5. Home \n";
				cout << "[ ]\b\b";
				cin >> r2;
				if (cin.fail()) {
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "Invalid input. Please enter a number.\n";
					continue;
				}
				switch (r2) {
				case 1:productsToOrder(con);
					break;
				case 2:displayApprovedProducts(con);
					break;
				case 3:insertApprovedProducts(con);
					break;
				case 4:exit2 = false;
					break;
				case 5:exit1 = false;
					exit2 = false;
					break;
				default:
					cout << "Wrong input , Try again .\n";
				}
			}

		}
			  break;
		case 10: {
			while (exit2 == true) {
				cout << "\nchoose :\n";
				cout << "1. Display Most Requsted Product\n";
				cout << "2. Display Most Requsted Project\n";
				cout << "3. Display The Profit or Loss Precentage of Products\n";
				cout << "4. Exit\n";
				cout << "5. Home \n";
				cout << "[ ]\b\b";
				cin >> r2;
				if (cin.fail()) {
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "Invalid input. Please enter a number.\n";
					continue;
				}
				switch (r2) {
				case 1: Most_Requested_Product(con);
					break;
				case 2:Most_Requested_Project(con);
					break;
				case 3:profit_and_loss(con);
					break;
					break;
				case 4:exit2 = false;
					break;
				case 5: exit1 = false;
					exit2 = false;
					break;
				default:
					cout << "Wrong Input ." << endl;
				}
			}
		}
			   break;
		case 11: exit1 = false;
			break;
		default:
			cout << "Wrong Input .";
		}
		system("cls");
	} while (exit1 == true);

}
