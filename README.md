# Relational-DBMS
A RAM based Relational Database Management System built in C++ that implements a few operations of RDMS.
## File descriptions:
  * **dbms.h**: Header file, contains all function declarations.
  
  * **dbms.cpp**: Contains function definitions of all the functions.
  
  * **main.cpp**: Main file that parses as well as executes the queries.
  
  * **text.txt**: INPUT FILE
  
  * **dump.txt**: File where *select*, *from*, *where* queries are dumped. These are the parsed version of the mentioned queries which are used by functions for processing.
  
  * **tmp.txt**: A temporary file created to hold a formatted query being processed.
  
## Available functionalities
The following queries can be performed on the RDBMS:
1. **CREATE DATABASE**: Creates a database.
2. **CREATE TABLE**: Creates a table.
3. **PRINT**: Prints the table.
4. **SELECT**: Selects the mentioned column in the table.
5. **FROM**: Selects concerned data from the mentioned table.
6. **WHERE**: Filters records(rows) that match a certain condition.
7. **ALTER(ROW)**: Adds attribute to a table and initialises other fields in the table.
8. **INSERT INTO**: Inserts a row in the table with the given values.
9. **CROSS JOIN**: Performs the cross operation on rows of two tables.

*The queries SELECT, FROM and WHERE currently operate on a single condition of type *<attr_name = value>.**

## TO-DO:
1. Implementation of Foreign Key while creation of tables.
2. Implementation of nested queries with complex **AND**/**OR** conditions.
3. Parse the **MIN**, **MAX**, **DROP TABLE**, **DROP ROW** and **DROP COLUMN** functions.
