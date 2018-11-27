# Relational-DBMS
Files:
  dbms.h: Header File
  dbms.cpp: Function definitions of all the functions
  main.cpp: Main file that parses as well as executes the queries
  text.txt: INPUT FILE
  dump.txt: File where select from where queries are dumped
  tmp.txt: A temporary file created to hold a formatted query being processed.
  TODO.txt: Contains features to be implemented in the second version of this RAM-based dbms.

Features:
  This RAM-based dbms implememts the following queries:
    1. Create table (Foreign key is not yet implemented)
    2. Insert into...values
    3. Select....from....where query with a single condition of type <attr_name = value>
    (Nested queries as well as queries with complex and/or conditions are yet to be implemented)

implementatio:
    There is dummy node kept for table head, attribute head and cell head which points to the main table, attribute and cells     respectively.

The main functions implemented are:

void parse(): Parses the queries
void print(): Prints table
database* create_database(string db_name): Creates a database_name
table_schema* create_table(string tb_name): creates table
table_schema *findTable(string tname): returns pointer to the table schema of given name
void add_attribute(table_schema* table,string attr_name,string dtype,bool is_pk):
adds attribute and initialises other fields in the table

insert_row(table_schema* table ,vector<pair<string, string> >&input_list):
inserts a row in the table with the given values.
If the value inserted for specific attribute does not match with it's value type then it throws error.

table_schema* cross(table_schema*t1, table_schema*t2):
A cross function creates new dummy table, crosses two tables in the database and put the values in the dummy node. 
And returns the pointer to the new created node.

void sigma(table_schema* tmp, string attrname, string val , vector<string> list):
Sigma functions

void pi(cell *ct, t_attributes* t, vector<string> list):
Project function
  
void min 
  written the function but not parsed
  
 void max
   written the function but not parsed
   
 drop table , drop column and drop row
    parsing is not done
  
print():
  In first line it prints database name.
  As it has dummy nodes, at first it prints dummy table. 
  In next it prints actual table. In that first it prints table name. In next line it prints dummy attribute follwed by attributes of the table. And in next line it prints dummy cell head nodes of each attribute.
  From next line onwards it prints fist dummy cell followed by cell values in a row.
