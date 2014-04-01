use test;
drop table if exists branch;
drop table if exists customer;
drop table if exists loan;
drop table if exists borrower;
drop table if exists account;
drop table if exists depositor;

create table branch(
	branch_name varchar(32),
	branch_city varchar(128),
	assets integer,
	primary key(branch_name)
);

insert into branch(branch_name,branch_city,assets)values("TianTongYuan zhihang","Beijing",200000);
insert into branch(branch_name,branch_city,assets)values("HaidianHuangzhuang zhihang","Beijing",300000);
insert into branch(branch_name,branch_city,assets)values("XuJiaHui zhihang","ShangHai",6000000);

create table customer(
	customer_name varchar(32) ,
	customer_street varchar(128),
	customer_city varchar(64),
	primary key(customer_name)
);

insert into customer(customer_name,customer_street,customer_city) values("kevin","huilongguan","beijing");
insert into customer(customer_name,customer_street,customer_city) values("david","jiulong","hongkong");
insert into customer(customer_name,customer_street,customer_city) values("andy","qingping","shandong");
insert into customer(customer_name,customer_street,customer_city) values("Jesica","chengde","hebei");

create table loan(
	loan_number integer,
	branch_name varchar(32),
	amount integer,
	primary key(loan_number)
);

insert into loan(loan_number,branch_name,amount) values(1,"TianTongYuan zhihang",1200);
insert into loan(loan_number,branch_name,amount) values(2,"HaidianHuangzhuang zhihang",2600);
insert into loan(loan_number,branch_name,amount) values(3,"XuJiaHui zhihang",2800);

create table borrower(
	customer_name varchar(32),
	loan_number integer,
	primary key(customer_name)
);

insert into borrower(customer_name,loan_number) values("kevin",1);
insert into borrower(customer_name,loan_number) values("david",2);
insert into borrower(customer_name,loan_number) values("andy",3);

create table account(
	account_number integer,
	branch_name varchar(32),
	balance integer,
	primary key(account_number)
);

insert into account(account_number,branch_name,balance) values(1,"TianTongYuan zhihang",1000);
insert into account(account_number,branch_name,balance) values(2,"HaidianHuangzhuang zhihang",2000);
insert into account(account_number,branch_name,balance) values(3,"XuJiaHui zhihang",3000);
insert into account(account_number,branch_name,balance) values(4,"XuJiaHui zhihang",2500);

create table depositor(
	customer_name varchar(32),
	account_number integer,
	primary key(customer_name,account_number)
);

insert into depositor(customer_name,account_number) values("kevin",1);
insert into depositor(customer_name,account_number) values("david",2);
insert into depositor(customer_name,account_number) values("andy",3);
insert into depositor(customer_name,account_number) values("Jesica",4);

(select distinct customer_name from depositor) union (select customer_name from borrower);

create view all_customer as
(
	select branch_name,customer_name from depositor,account where depositor.account_number = account.account_number
)
