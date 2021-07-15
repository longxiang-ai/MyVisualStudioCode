create table employee (
    employee_name varchar (10),
    street varchar (10),
    city varchar (10),
    primary key (employee_name),
);

create table works (
    employee_name varchar (10),
    company_name varchar (10),
    salary numeric (10, 2),
    primary key (employee_name),
    foreign key (employee_name) references employee (employee_name),
    foreign key (company_name) references company(company_name)
);

create table company (
    company_name varchar (10),
    city varchar (10),
    primary key (company_name)
);

create table manages (
    employee_name varchar (10),
    manager_name varchar (10),
    primary key (employee_name),
    foreign key (employee_name) references employee
);