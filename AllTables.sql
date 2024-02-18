CREATE TABLE employees (
    id INT AUTO_INCREMENT PRIMARY KEY,
    name VARCHAR(255),
    email VARCHAR(255) UNIQUE,
    password VARCHAR(255) DEFAULT NULL,
    position VARCHAR(255),
    salary DOUBLE(9,2)
);

CREATE TABLE projects (
    project_id INT AUTO_INCREMENT PRIMARY KEY,
    project_name VARCHAR(255) NOT NULL,
    price DECIMAL(10, 2) NOT NULL,
    time_needed VARCHAR(255) NOT NULL,
    TimePurchased INT DEFAULT 0 NOT NULL
);

CREATE TABLE products (
    product_id INT AUTO_INCREMENT PRIMARY KEY,
    product_name VARCHAR(255) NOT NULL,
    price DECIMAL(10, 2) NOT NULL,
    quantity INT NOT NULL,
    TimePurchased INT DEFAULT 0 NOT NULL
);

CREATE TABLE customers (
    customer_id INT AUTO_INCREMENT PRIMARY KEY,
    customer_name VARCHAR(255) NOT NULL,
    address VARCHAR(255) NOT NULL,
    phone_number VARCHAR(20) NOT NULL UNIQUE
);

CREATE TABLE orderProduct (
    order_id INT AUTO_INCREMENT PRIMARY KEY,
    product_id INT,
    customer_id INT,
    quantity_ordered INT NOT NULL,
    amount_paid DECIMAL(10, 2) NOT NULL,
    order_date TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (product_id) REFERENCES products(product_id),
    FOREIGN KEY (customer_id) REFERENCES customers(customer_id)
);

CREATE TABLE workon (
    project_id INT,
    employee_id INT,
    PRIMARY KEY (project_id, employee_id),
    FOREIGN KEY (project_id) REFERENCES projects(project_id),
    FOREIGN KEY (employee_id) REFERENCES employees(id)
);

CREATE TABLE orderProject (
    order_id INT AUTO_INCREMENT PRIMARY KEY,
    project_id INT NOT NULL,
    customer_id INT NOT NULL,
    amount_paid DECIMAL(10, 2) NOT NULL,
    order_date TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    date_to_be_ready TIMESTAMP,
    FOREIGN KEY (project_id) REFERENCES projects (project_id),
    FOREIGN KEY (customer_id) REFERENCES customers (customer_id),
    CONSTRAINT fk_orderproject_project FOREIGN KEY (project_id) REFERENCES projects (project_id)
);

CREATE TABLE vendors (
    vendor_id INT AUTO_INCREMENT PRIMARY KEY,
    vendor_name VARCHAR(255) NOT NULL,
    address VARCHAR(255) NOT NULL,
    phone_number VARCHAR(20) NOT NULL UNIQUE
);

CREATE TABLE ProductsToBuy (
    id INT AUTO_INCREMENT PRIMARY KEY,
    product_name VARCHAR(255) NOT NULL,
    vendor_name VARCHAR(255) NOT NULL,
    price DECIMAL(10, 2) NOT NULL,
    quantity INT NOT NULL,
    approve BOOLEAN DEFAULT FALSE
);

CREATE TABLE budget_table (
    id INT AUTO_INCREMENT PRIMARY KEY,
    product_budget DOUBLE DEFAULT 100000.00,
    project_budget DOUBLE DEFAULT 0.00,
    employee_budget DOUBLE DEFAULT 2000000.00,
    product_costs DOUBLE DEFAULT 0.00,
    project_costs DOUBLE DEFAULT 0.00,
    product_profit DOUBLE DEFAULT 0.00,
    project_profit DOUBLE DEFAULT 0.00
);

CREATE TABLE change_log (
    id INT AUTO_INCREMENT PRIMARY KEY,
    table_name VARCHAR(255),
    action VARCHAR(10),
    timestamp TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);
