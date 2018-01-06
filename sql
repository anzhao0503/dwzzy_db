CREATE TABLE CUSTOMER (C_CUSTKEY INTEGER, C_NAME VARCHAR(20));
INSERT INTO CUSTOMER VALUES (1,'WANG');
SELECT C_NAME FROM CUSTOMER;
DELETE FROM CUSTOMER WHERE C_CUSTKEY > 0;
UPDATE CUSTOMER SET C_CUSTKEY = 2 WHERE C_CUSTKEY > 0 ;

SELECT N_NAME FROM nation;
SELECT nation.N_NAME, region.R_NAME FROM nation, region WHERE nation.N_REGIONKEY=region.R_REGIONKEY;

CREATE TABLE SUPPLIER (S_SUPPKEY INTEGER, S_NAME CHAR(25), S_ADDRESS VARCHAR(40), S_PHONE CHAR(15), S_ACCTBAL FLOAT(1), S_COMMENT VARCHAR(101));
create table nation (n_nationkey integer, n_name char(25), n_regionkey integer, n_comment varchar(152));

INSERT INTO Persons VALUES ('Gates', 'Bill', 'Xuanwumen 10', 'Beijing');

DELETE FROM table_name where a >10 and b<100;

SELECT LastName,FirstName FROM Persons;

SELECT DISTINCT Company FROM Orders;

SELECT * FROM tb1 where Persons.Id_P = Orders.Id_P AND Persons.Id_P > 10 AND Persons.name = Orders.name AND IP > 100;

SELECT Persons.LastName, Persons.FirstName, Orders.OrderNo FROM Persons, Orders WHERE Persons.Id_P = Orders.Id_P AND Persons.Id_P > 10 AND Persons.name = Orders.name ORDER BY FirstName;


gcc -o test bison.tab.c lex.yy.c -lfl -ly
