#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<vector>
#include<iostream>
using namespace std;

//A dummy node is kept for table head, attribute head and cell head which points to the main table, attribute and cells respectively.
//Also contains-void parse(): Parses the queries.
//If the value inserted for specific attribute does not match with it's value type then it throws error.



//typedef enum { STR, INT} attr_type;
//keep head as a dummy node , head->next is the first node
union data_type               // the types of attribute value types allowed by the table attributes
{
  int int_var;
  //float float_var;
  char var_char[20];    //specify the max allowed length
};

/* Struct of a cell has cell_value and a pointer right that points to the
cell to its right in the same row and another pointer down that points to the
cell below it in the same column */
struct cell
{
  cell* right;
  cell* down;
  string cell_value;
};

// structure  to hold the attributes
struct t_attributes
{
  cell* chead;              //address of the first cell in the current attribute column
  string value_type;
  string attribute_name;         //table schema stores the table attributes

  t_attributes* anext;   //next attribute
  bool p_key;                   //tells whether the attribute is a primary key or not
  //foreign_keys* keys_list;
};

struct table_schema
{
  string table_name;
  t_attributes* thead;
  table_schema* tnext;
  //int number_of_attributes;
  //string data_type;
};

struct database
{
  string database_name;
  table_schema* dhead;   //pointer to the head of corresponding table schema
  //database_schema* next;
};

struct foreign_keys
{
  //foreign_keys* head;
  //table_attributes* key;
  string referenced_key;
  foreign_keys* next;
};
/*struct n5
{
  table_elements* head;   //pointer to the first node of the table
}typedef table;*/


database* create_database(string);                            //type will be database_schema, in which the database_name will have the name of the database
table_schema* create_table(string  );                         //give the name of table to be added in table schemas inside the function but give the number of attributes required
void insert_row(table_schema*, vector<pair<string, string> > &values);                 //the name of table into which row has to be inserted, values of the attributes can be given inside the function after seeing the number of attibutes it has
void add_attribute(table_schema*, string, string, bool);      //table into which column has to be inserted, also pass the name of the attribute
void drop_row(string , string,union data_type*);              //pass the name of the table from which row has to be deleted, name of the attribute(s) which is/are primary key
void drop_attribute(string , string);                         //pass the name of the table from which row has to be deleted, name of the attribute which is to be deleted
void drop_table(string);                                      //name of the table that has to be deleted
table_schema* findTable(string);
union data_type* max_attr(string, string);
table_schema* cross(table_schema*t1, table_schema*t2);        /*A cross function creates new dummy table, crosses two tables                                                                  in the database and put the values in the dummy node. 
                                                               And returns the pointer to the new created node.*/
void pi(cell *ct, t_attributes* t, vector<string> list);
void sigma(table_schema* tmp, string attrname, string val , vector<string> list);
void print();                                                /* In first line it prints database name.
                                                                As it has dummy nodes, at first it prints dummy table. 
                                                                In next it prints actual table. In that first it prints table                                                                 name. In next line it prints dummy attribute follwed by                                                                       attributes of the table. And in next line it prints dummy cell                                                                 head nodes of each attribute.
                                                                From next line onwards it prints fist dummy cell followed by                                                                   cell values in a row.*/

//void select_from(string , string , );             //name of the tables from which to select
//void where();
// all these functions need to be in a str
