CREATE TABLE customer (C_CUSTKEY INTEGER, C_NAME VARCHAR(25),C_ADDRESS VARCHAR(40),C_NATIONKEY INTEGER, C_PHONE CHAR(15),C_ACCTBAL FLOAT(8),C_MKTSEGMENT CHAR(10),C_COMMENT VARCHAR(117));

LOAD 'customer.tbl' INTO customer;

CREATE TABLE orders (O_ORDERKEY INTEGER, O_CUSTKEY INTEGER, O_ORDERSTATUS CHAR(1), O_TOTALPRICE FLOAT(8), O_ORDERDATE DATE, O_ORDERPRIORITY CHAR(15), O_CLERK CHAR(15), O_SHIPPIORITY INTEGER, O_COMMENT VARCHAR(79));

LOAD 'orders.tbl' INTO orders;

CREATE TABLE part (P_PARTKEY INTEGER,P_NAME VARCHAR(55),P_MFGR CHAR(25), P_BRAND CHAR(10), P_TYPE VARCHAR(25), P_SIZE INTEGER, P_CONTAINER CHAR(10), P_RETAILPRICE FLOAT(8), P_COMMENT VARCHAR(23));
LOAD 'part.tbl' INTO part;

CREATE TABLE nation (N_NATIONKEY INTEGER, N_NAME CHAR(25),N_REGIONKEY INTEGER,N_COMMENT VARCHAR(152));
LOAD 'nation.tbl' INTO nation;

CREATE TABLE region (R_REGIONKEY INTEGER, R_NAME CHAR(25),R_COMMENT VARCHAR(152));
LOAD 'region.tbl' INTO region;

CREATE TABLE supplier (S_SUPPKEY INTEGER, S_NAME CHAR(25), S_ADDRESS VARCHAR(40),S_NATIONKEY INTEGER, S_PHONE CHAR(15),S_ACCTBAL FLOAT(8),S_COMMENT VARCHAR(101));
LOAD 'supplier.tbl' INTO supplier;

CREATE TABLE partsupp ( PS_PARTKEY INTEGER, PS_SUPPKEY INTEGER, PS_AVAILQTY INTEGER, PS_SUPPLYCOST FLOAT(8),PS_COMMENT VARCHAR(199));
LOAD 'partsupp.tbl' INTO partsupp;

CREATE TABLE lineitem ( L_ORDERKEY INTEGER, L_PARTKEY INTEGER, L_SUPPKEY INTEGER, L_LINENUMBER INTEGER, L_QUANTITY FLOAT(8), L_EXTENDEDPRICE FLOAT(8), L_DISCOUNT FLOAT(8), L_TAX FLOAT(8), L_RETURNFLAG CHAR(1), L_LINESTATUS CHAR(1), L_SHIPDATE DATE, L_COMMITDATE DATE, L_RECEIPTDATE DATE, L_SHIPINSTRUCT CHAR(25), L_SHIPMODE CHAR(10), L_COMMENT VARCHAR(44));
LOAD 'lineitem.tbl' INTO lineitem;


select n_name from orders,nation,region where nation.n_regionkey = region.r_regionkey and orders.o_orderdate >= '1995-06-12';

SELECT n_name INTO OUTFILE '/var/lib/mysql-files/select_results' FIELDS TERMINATED BY '	' FROM orders, nation, region WHERE o_orderdate >= '1995-06-12' AND nation.n_regionkey = region.r_regionkey;

select * from orders where o_orderdate >= '1995-06-12';
select * from nation;

select count(distinct(O_ORDERKEY)),count(distinct(O_CUSTKEY)),count(distinct(O_ORDERSTATUS)),count(distinct(O_TOTALPRICE)),count(distinct(O_ORDERDATE)),count(distinct(O_ORDERPRIORITY)),count(distinct(O_CLERK)),count(distinct(O_SHIPPIORITY)),count(distinct(O_COMMENT)) from orders;

INSERT INTO Persons VALUES ('Gates', 'Bill', 'Xuanwumen 10', 'Beijing');
INSERT INTO nation VALUES ('25','UNKOWN','1','y final packages. slow foxes cajole quickly. quickly silent platelets breach ironic accounts. unusual pinto') ;

