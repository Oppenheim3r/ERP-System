
#include "sqlConn.h"

using namespace std;

namespace SQLConn {
    sql::Connection* setupMySQL() {
        sql::mysql::MySQL_Driver* driver;
        sql::Connection* con;

        driver = sql::mysql::get_mysql_driver_instance();

        try {

            const string url = "tcp://127.0.0.1:3306";
            const string user = "husam";
            const string password = "123";
            const string database = "erppro";

            con = driver->connect(url, user, password);


            con->setSchema(database);


            sql::Statement* stmt = con->createStatement();

            delete stmt;
        }
        catch (sql::SQLException& e) {
            cerr << "MySQL Exception: " << e.what() << endl;
            return nullptr;
        }

        return con;
    }




    void closeConnection(sql::Connection* con) {
        if (con) {
            delete con;
        }
    }
}
