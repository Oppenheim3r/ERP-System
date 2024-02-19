--Trigger for calculating how many days the project to be implmented in the customers systme
DELIMITER //
CREATE TRIGGER calculate_date_to_be_ready
BEFORE INSERT ON orderProject
FOR EACH ROW
BEGIN
    DECLARE time_needed_days INT;

    SELECT time_needed INTO time_needed_days
    FROM projects
    WHERE project_id = NEW.project_id;

    SET NEW.date_to_be_ready = DATE_ADD(CURRENT_TIMESTAMP, INTERVAL time_needed_days DAY);
END;
//
DELIMITER ;
--------------------------------------------------------------------------

--All these triggers beneath this comment ,are for stroing logs for the operations that happen in the database 

-- Employees Table
DELIMITER //
CREATE TRIGGER log_before_insert_employees BEFORE INSERT ON employees
FOR EACH ROW
BEGIN
    INSERT INTO change_log (table_name, action) VALUES ('employees', 'INSERT');
END;
//
CREATE TRIGGER log_before_update_employees BEFORE UPDATE ON employees
FOR EACH ROW
BEGIN
    INSERT INTO change_log (table_name, action) VALUES ('employees', 'UPDATE');
END;
//
DELIMITER //
CREATE TRIGGER log_before_delete_employees BEFORE DELETE ON employees
FOR EACH ROW
BEGIN
    INSERT INTO change_log (table_name, action) VALUES ('employees', 'DELETE');
END;
//
DELIMITER ;

-- Orderproduct Table
DELIMITER //
CREATE TRIGGER log_before_insert_orderproduct BEFORE INSERT ON orderproduct
FOR EACH ROW
BEGIN
    INSERT INTO change_log (table_name, action) VALUES ('orderproduct', 'INSERT');
END;
//
CREATE TRIGGER log_before_update_orderproduct BEFORE UPDATE ON orderproduct
FOR EACH ROW
BEGIN
    INSERT INTO change_log (table_name, action) VALUES ('orderproduct', 'UPDATE');
END;
//
CREATE TRIGGER log_before_delete_orderproduct BEFORE DELETE ON orderproduct
FOR EACH ROW
BEGIN
    INSERT INTO change_log (table_name, action) VALUES ('orderproduct', 'DELETE');
END;
//
DELIMITER ;
-- Budget Table
DELIMITER //
CREATE TRIGGER log_before_insert_budget_table BEFORE INSERT ON budget_table
FOR EACH ROW
BEGIN
    INSERT INTO change_log (table_name, action) VALUES ('budget_table', 'INSERT');
END;
//
CREATE TRIGGER log_before_update_budget_table BEFORE UPDATE ON budget_table
FOR EACH ROW
BEGIN
    INSERT INTO change_log (table_name, action) VALUES ('budget_table', 'UPDATE');
END;
//
CREATE TRIGGER log_before_delete_budget_table BEFORE DELETE ON budget_table
FOR EACH ROW
BEGIN
    INSERT INTO change_log (table_name, action) VALUES ('budget_table', 'DELETE');
END;
//
DELIMITER ;

-- Customers Table
DELIMITER //
CREATE TRIGGER log_before_insert_customers BEFORE INSERT ON customers
FOR EACH ROW
BEGIN
    INSERT INTO change_log (table_name, action) VALUES ('customers', 'INSERT');
END;
//
CREATE TRIGGER log_before_update_customers BEFORE UPDATE ON customers
FOR EACH ROW
BEGIN
    INSERT INTO change_log (table_name, action) VALUES ('customers', 'UPDATE');
END;
//
CREATE TRIGGER log_before_delete_customers BEFORE DELETE ON customers
FOR EACH ROW
BEGIN
    INSERT INTO change_log (table_name, action) VALUES ('customers', 'DELETE');
END;
//
DELIMITER ;
-- Orderproject Table
DELIMITER //
CREATE TRIGGER log_before_insert_orderproject BEFORE INSERT ON orderproject
FOR EACH ROW
BEGIN
    INSERT INTO change_log (table_name, action) VALUES ('orderproject', 'INSERT');
END;
//
CREATE TRIGGER log_before_update_orderproject BEFORE UPDATE ON orderproject
FOR EACH ROW
BEGIN
    INSERT INTO change_log (table_name, action) VALUES ('orderproject', 'UPDATE');
END;
//
CREATE TRIGGER log_before_delete_orderproject BEFORE DELETE ON orderproject
FOR EACH ROW
BEGIN
    INSERT INTO change_log (table_name, action) VALUES ('orderproject', 'DELETE');
END;
//
DELIMITER ;

-- Products Table
DELIMITER //
CREATE TRIGGER log_before_insert_products BEFORE INSERT ON products
FOR EACH ROW
BEGIN
    INSERT INTO change_log (table_name, action) VALUES ('products', 'INSERT');
END;
//
CREATE TRIGGER log_before_update_products BEFORE UPDATE ON products
FOR EACH ROW
BEGIN
    INSERT INTO change_log (table_name, action) VALUES ('products', 'UPDATE');
END;
//
CREATE TRIGGER log_before_delete_products BEFORE DELETE ON products
FOR EACH ROW
BEGIN
    INSERT INTO change_log (table_name, action) VALUES ('products', 'DELETE');
END;
//
DELIMITER ;


-- Productstobuy Table
DELIMITER //
CREATE TRIGGER log_before_insert_productstobuy BEFORE INSERT ON productstobuy
FOR EACH ROW
BEGIN
    INSERT INTO change_log (table_name, action) VALUES ('productstobuy', 'INSERT');
END;
//
CREATE TRIGGER log_before_update_productstobuy BEFORE UPDATE ON productstobuy
FOR EACH ROW
BEGIN
    INSERT INTO change_log (table_name, action) VALUES ('productstobuy', 'UPDATE');
END;
//
CREATE TRIGGER log_before_delete_productstobuy BEFORE DELETE ON productstobuy
FOR EACH ROW
BEGIN
    INSERT INTO change_log (table_name, action) VALUES ('productstobuy', 'DELETE');
END;
//
DELIMITER ;

-- Projects Table
DELIMITER //
CREATE TRIGGER log_before_insert_projects BEFORE INSERT ON projects
FOR EACH ROW
BEGIN
    INSERT INTO change_log (table_name, action) VALUES ('projects', 'INSERT');
END;
//
CREATE TRIGGER log_before_update_projects BEFORE UPDATE ON projects
FOR EACH ROW
BEGIN
    INSERT INTO change_log (table_name, action) VALUES ('projects', 'UPDATE');
END;
//
CREATE TRIGGER log_before_delete_projects BEFORE DELETE ON projects
FOR EACH ROW
BEGIN
    INSERT INTO change_log (table_name, action) VALUES ('projects', 'DELETE');
END;
//
DELIMITER ;

-- Vendors Table
DELIMITER //
CREATE TRIGGER log_before_insert_vendors BEFORE INSERT ON vendors
FOR EACH ROW
BEGIN
    INSERT INTO change_log (table_name, action) VALUES ('vendors', 'INSERT');
END;
//
CREATE TRIGGER log_before_update_vendors BEFORE UPDATE ON vendors
FOR EACH ROW
BEGIN
    INSERT INTO change_log (table_name, action) VALUES ('vendors', 'UPDATE');
END;
//


CREATE TRIGGER log_before_delete_vendors BEFORE DELETE ON vendors
FOR EACH ROW
BEGIN
    INSERT INTO change_log (table_name, action) VALUES ('vendors', 'DELETE');
END;
//
DELIMITER ;

-- Workon Table
DELIMITER //
CREATE TRIGGER log_before_insert_workon BEFORE INSERT ON workon
FOR EACH ROW
BEGIN
    INSERT INTO change_log (table_name, action) VALUES ('workon', 'INSERT');
END;
//
CREATE TRIGGER log_before_update_workon BEFORE UPDATE ON workon
FOR EACH ROW
BEGIN
    INSERT INTO change_log (table_name, action) VALUES ('workon', 'UPDATE');
END;
//
CREATE TRIGGER log_before_delete_workon BEFORE DELETE ON workon
FOR EACH ROW
BEGIN
    INSERT INTO change_log (table_name, action) VALUES ('workon', 'DELETE');
END;
//
DELIMITER ;
