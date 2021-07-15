CREATE TABLE customer (customer_name char(20),
  customer_street  char(30),
  customer_city char(30),
  primary key (customer_name));
CREATE TABLE branch
  (branch_name char(15),
  branch_city  char(30),
  assets  integer,
  primary key (branch_name),
  CHECK (assets>=0));
CREATE TABLE account
  (account_number char(10),
  branch_name char(15),
  balance integer,
  primary key (account_number), 
  foreign key (branch_name) references branch,
  CHECK(balance>=0));
CREATE TABLE depositor
  (customer_name  char(20),
  account_number  char(10),
  primary key (customer_name, account_number),
  foreign key (account_number) references account,
  foreign key (customer_name) references customer);

  INSERT customer
  VALUES('Henry','Tianmushan','Hangzhou')
INSERT customer
  VALUES('Rock','Nanjing','Hangzhou')
之后再执行
INSERT customer
  VALUES('Henry','Nanjing','Shanghai')

INSERT INTO account
  VALUES('006','Pudong',‐10)

create  table book
(book_id char(10),
category varchar(10),
title varchar(20),
press varchar(20),
year int,
author varchar(10),
price decimal(7,2),
total int,
stock int,
primary key(book_id));

create table card
(card_id char(7),
name varchar(10),
department varchar(40),
type char(1),
primary key(card_id),
check(type in('T','S'))
);

create table borrow
(card_id char(7),
book_id  char(8),
borrow_date int,
return_date int,
primary key(card_id,book_id),
foreign key (card_id) references card(card_id),
foreign key (book_id) references book(book_id));

