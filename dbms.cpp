#include<stdlib.h>
#include<stdio.h>
#include<iostream>
#include<string>
#include<vector>
#include "dbms.h"

database* main_db= new database;

//prints table
void print()
{
	database *db=main_db;
	table_schema *tab=db->dhead;
	cout<<db->database_name<<endl;
	while(tab!=NULL)
	{
		cout<<tab->table_name<<endl;
		t_attributes *attr=tab->thead;
		cell *c=attr->chead;
		while(attr!=NULL)
		{
			cout<<attr->attribute_name<<" ";
			attr=attr->anext;
		}
		cout<<endl;
		while(c!=NULL)
		{
			cell*d=c;
			while(d!=NULL)
			{
				cout<<d->cell_value<<" ";
				d=d->right;
			}
			cout<<endl;
			c=c->down;
		}
		tab=tab->tnext;
		cout<<endl;

	}
}


/*result_t* myexec(char *query) {
	result_t* const res = (result_t*)malloc(sizeof(result_t));
	//your code runs here
	printf("inside myexec query=%s\n",query);
	return res;
}

handle_t* get_handle() {
	handle_t* const myhandle = (handle_t*)malloc(sizeof(handle_t));
	myhandle->exec = &myexec;
	printf("inside get_handle\n");
	return myhandle;
}*/

//creates database with given name and initialises the values
database* create_database(string db_name)
{
   main_db = new database;
   main_db->database_name=db_name;
   table_schema* tmp= new table_schema; //dummy head for table_schema
   //initialising dummy node
   t_attributes* ta = new t_attributes; //dummy attribute;
  cell* ct=new cell;	//dummy cell in dummy attribute
	//The attributes are initialised to their dummy values
  ct->right=NULL;
  ct->down=NULL;
  ct->cell_value="*";
  ta->chead=ct;
  ta->value_type="var_char";
  ta->attribute_name="$";
  ta->anext=NULL;
  ta->p_key=false;
   tmp->thead=ta;
   tmp->tnext=NULL;
   tmp->table_name="#";
   main_db->dhead= tmp;
   return main_db;
}

table_schema* create_table(string tb_name)
{
 	//"in create table"
 	database*dptr=main_db;
 	table_schema * dumm=main_db->dhead;
 	while(dumm->tnext!=NULL)
 	{
 		if((dumm->table_name).compare(tb_name)==0)
 		{
 			cout<<"This table name already exist"<<endl;
 			return dumm;
 		}
 		dumm=dumm->tnext;
 	}
  	table_schema* ts= new table_schema;
  	ts->table_name=tb_name;
  	ts->tnext=NULL;

		//create table and initialise the fields to dummy values
  	t_attributes* ta = new t_attributes; //dummy attribute;
  	cell* ct=new cell;	//dummy cell in dummy attribute
  	ct->right=NULL;
  	ct->down=NULL;
  	ct->cell_value="*";
  	ta->chead=ct;
  	ta->value_type="var_char";
  	ta->attribute_name="$";
  	ta->anext=NULL;
  	ta->p_key=false;
  	//dptr->dhead->thead=ta;
  	//ta->keys_list=NULL;
  	//
  	ts->thead=ta;	//attribute head ta to table ts
  	dumm->tnext=ts;
  	return ts;
}

//returns pointer to the table schema of given name
table_schema *findTable(string tname)
{
	database* dptr= main_db;
  	table_schema* table= dptr->dhead;

  	while(table->table_name!=tname && table!=NULL)
  	{
  		table=table->tnext;
  		//cout<<table->table_name<<endl;

  	}
  	return table;
}


//adds attribute and initialises other fields in the table
void add_attribute(table_schema* table,string attr_name,string dtype,bool is_pk)
{

  	t_attributes* atr = new t_attributes; //new attr_node
  	cell* ct=new cell;

  	ct->down=NULL;
  	ct->right=NULL;
  	ct->cell_value="*";

  	atr->value_type=dtype;
  	atr->attribute_name=attr_name;
  	atr->anext=NULL;
  	atr->p_key=is_pk;
  	//atr->keys_list=NULL;

  	t_attributes* at = new t_attributes;
  	at=table->thead;
  	while(at->anext!=NULL)
  	{
  		at=at->anext;
  	}
  	cell* ct1=at->chead;
  	ct1->right=ct;
  	atr->chead=ct;

  	at->anext=atr;


}

//inserts a row in the table with the given values
void insert_row(table_schema* table ,vector<pair<string, string> >&input_list)
{
  	t_attributes* at = new t_attributes;
  	at=table->thead;
  	cell* ct1=at->chead;
  	cout<<ct1->cell_value<<endl;
  	at=at->anext;
  	for(int i=0;i<input_list.size();i++)
  	{
  		if((at->value_type).compare(input_list[i].second)!=0)
  		{
  			cout<<at->attribute_name<<" is "<<at->value_type<<" you passed "<<input_list[i].second<<" "<<input_list[i].first<<endl;
  			return;
  		}
  		if(at==NULL)
  		{
  			cout<<"error : input is more than number of attributes in table"<<endl;
  			return;
  		}
  		at=at->anext;
  	}

  	cout<<"what"<<endl;
  	//number of attributes in the table
  	int n=input_list.size();
  	cell* ct=new cell;
  	ct->cell_value="*";
  	ct->down=ct1->down;
  	ct1->down=ct;
  	ct1=ct1->right;
  	cout<<ct->cell_value<<" "<<ct1->cell_value<<" yes"<<endl;
  	for(int i=0;i<n;i++)
  	{
  			cout<<"ok"<<endl;
  			cell* ct2=new cell;
  			ct2->cell_value=input_list[i].first;
  			//cout<<ct2->cell_value<<" ";
  			ct2->right=NULL;
  			ct2->down=ct1->down;
  			ct1->down=ct2;
  			ct->right=ct2;
  			ct=ct->right;
  			ct1=ct1->right;
  			cout<<ct->cell_value<<" "<<ct1->cell_value<<" yes"<<endl;

  	}
  	//cout<<endl<<"out of insert row"<<endl;
}

/*void drop_row(string tabname , string attrname, union data_type* prikey)
{
	table_schema* tmp=main_db->dhead;
	while(tmp->table_name.comapre(tabname)!=0)
	{
		if(tmp->tnext==NULL)
		{
			cout<<tabname<<" does not exist"<<endl;
			return;
		}
		tmp=tmp->tnext;
	}

	t_attributes *tab=tmp->thead;
	while(tab->attribute_name.compare(attrname)!=0)
	{
		if(tab->anext==NULL)
		{
			cout<<attrname<<" does not exist"<<endl;
			return;
		}
		tab=tab->anext;
	}
	cell* c=tab->chead;
	int flag=0;					//flag==0 if data type is int else 1
	int count=0;
	if(tab->value_type.compare("string")==0)
		flag=1;
	while(1)					//first count the number of cells upto the required cell
	{
		if(c->down==NULL)
		{
			cout<<prikey<<" does not exist"<<endl;
			return;
		}
		if((flag==1 && c->cell_value.compare(prikey)==0) || (flag==0 && c->cell_value==prikey))
		{
			break;
		}
		c=c->down;
		count++;
	}
	tmp=main_db->dhead;
	dhead->tnext;
	tab=tmp->thead;
	tab->anext;
	c=tab->chead;
	for(int i=0;i<count-1;i++)		//traverse through the cells till we get prev of required cell
	{
		c=c->down;
	}
	while(c!=NULL)				//delete the cell and goto right and continue till we get end
	{
		c->down=c->down->down;
		c=c->right;
	}
}

void drop_attribute(string tabname , string attrname)
{
	table_schema* tmp=main_db->dhead;
	while(tmp->table_name.comapre(tabname)!=0)
	{
		if(tmp->tnext==NULL)
		{
			cout<<tabname<<" does not exist"<<endl;
			return;
		}
		tmp=tmp->tnext;
	}

	t_attributes *tab=tmp->thead;
	t_attributes *prev=tab;
	while(tab->attribute_name.compare(attrname)!=0)
	{
		if(tab->anext==NULL)
		{
			cout<<attrname<<" does not exist"<<endl;
			return;
		}
		prev=tab;
		tab=tab->anext;
	}
	cell*c=prev->chead;
	prev->anext=prev->anext->anext;
	while(c!=NULL)				//delete the cell and goto down and continue till we get end
	{
		c->right=c->right->right;
		c=c->down;
	}
}

void drop_table(string tabname)
{
	table_schema* tmp=main_db->dhead;
	table_schema* prev=tmp;
	while(tmp->table_name.comapre(tabname)!=0)
	{
		if(tmp->tnext==NULL)
		{
			cout<<tabname<<" does not exist"<<endl;
			return;
		}
		prev=tmp;
		tmp=tmp->tnext;
	}
	prev->tnext=prev->tnext->next;
}


union data_type* max_attr(string tb, string atr)
{
	database* dptr=new database;
  	dptr=main_db;
  	table_schema* table=new table_schema;
  	table=dptr->dhead;
  	while(table->table_name!=tb)
  	{
  		table=table->tnext;

  	}
  	t_attributes* at = new t_attributes;
  	at=table->thead;
  	while(at->attribute_name != atr)
  	{
  		at=at->anext;
  	}
  	cell* c1=new cell;
  	c1=at->chead;
  	c1=c1->down;
  	if(at->value_type == "int" && c1 != NULL)
  	{
  		int ma;
  		ma=c1->cell_value;
  		c1=c1->down;
  		while(c1!=NULL)
  		{
  			if(ma < c1->cell_value)
  			{
  				ma=c1->cell_value;
  			}
  			c1=c1->down;
  		}
  	}
  	else if(at->value_type == "string" && c1 != NULL)
  	{
  		string ma;
  		ma=c1->cell_value;
  		c1=c1->down;
  		while(c1!=NULL)
  		{
  			if(ma.compare(c1->cell_value)<0)
  			{
  				ma=c1->cell_value;
  			}
  			c1=c1->down;
  		}
  	}
}*/

//A cross function that crosses two tables in the database
table_schema* cross(table_schema*t1, table_schema*t2)
{

	/* Creating new table*/

	table_schema* t= new table_schema;
  	t->table_name="dummy";
  	t->tnext=NULL;


  	t_attributes* ta = new t_attributes; //dummy attribute;
  	cell* ct=new cell;	//dummy cell in dummy attribute
  	ct->right=NULL;
  	ct->down=NULL;
  	ct->cell_value="*";
  	ta->chead=ct;
  	ta->value_type="var_char";
  	ta->attribute_name="$";
  	ta->anext=NULL;
  	ta->p_key=false;
  	t->thead=ta;	//attribute head ta to table ts

  	/*--------*/

	t_attributes* nt=t->thead;
	t_attributes* t1_attr=t1->thead;
	t_attributes* t2_attr=t2->thead;
	t1_attr=t1_attr->anext;
	while(t1_attr!=NULL)
	{
		add_attribute(t,t1_attr->attribute_name,t1_attr->value_type,t1_attr->p_key);
		t1_attr=t1_attr->anext;
	}
	t2_attr=t2_attr->anext;
	while(t2_attr!=NULL)
	{
		add_attribute(t,t2_attr->attribute_name,t2_attr->value_type,t2_attr->p_key);
		t2_attr=t2_attr->anext;
	}
	t1_attr=t1->thead->anext;
	t2_attr=t2->thead->anext;
	//t1_attr=t1_attr->anext;
	//t2_attr=t2_attr->anext;
	cell* nc=nt->chead;
	cell* c1=t1_attr->chead;
	cell* c2=t2_attr->chead;
	c1=c1->down;
	c2=c2->down;
	cell*tmp1=c1;
	cell*tmp2=c2;

	while(c1!=NULL)
	{
		vector<pair<string,string> > l1;
		while(tmp1!=NULL)
		{
			pair<string,string> p=make_pair(tmp1->cell_value,t1_attr->value_type);
			cout<<p.first<<" "<<p.second<<endl;
			l1.push_back(p);
			tmp1=tmp1->right;
			t1_attr=t1_attr->anext;
		}
		while(c2!=NULL)
		{
			vector<pair<string,string> >l2;
			while(tmp2!=NULL)
			{
				pair<string,string> p=make_pair(tmp2->cell_value,t2_attr->value_type);
				cout<<p.first<<" "<<p.second<<endl;
				l2.push_back(p);
				tmp2=tmp2->right;
				t2_attr=t2_attr->anext;
			}
			cout<<"done"<<endl;
			vector<pair<string,string> >input_list;
			for(int i=0;i<l1.size();i++)
			{
				input_list.push_back(l1[i]);
			}
			for(int i=0;i<l2.size();i++)
			{
				input_list.push_back(l2[i]);
			}
			cout<<"insert"<<endl;
			insert_row(t ,input_list);
			c2=c2->down;
			tmp2=c2->right;
			t2_attr=t2->thead->anext;
		}
		c1=c1->down;
		tmp1=c1->right;
		t1_attr=t1->thead->anext;

	}
	return t;
}


//A function that projects the columns with the given attribute names
void pi(cell *ct, t_attributes* t, vector<string> list)
{
	cell* c=ct->right;
	t_attributes * tmp=t->anext;
	for(int i=0;i<list.size();i++)
	{
		//c=c->right;
		while(tmp!=NULL)
		{
			if((tmp->attribute_name).compare(list[i])==0)
				cout<<c->cell_value<<" ";
			tmp=tmp->anext;
			c=c->right;
		}

		c=ct->right;
		tmp=t->anext;
	}
	cout<<endl;
}


// Sigma function that selects rows that satisfy the given condition
//This function however implements only one basic condition
//that selects matching attribute value
void sigma(table_schema* tmp, string attrname, string val , vector<string> list)
{
	//cout<<"in sigma"<<endl;
	t_attributes *tab=tmp->thead;
	t_attributes *t=tmp->thead;
	while(tab->attribute_name.compare(attrname)!=0)
	{
		if(tab->anext==NULL)
		{
			cout<<attrname<<" does not exist"<<endl;
			return;
		}
		tab=tab->anext;
	}
	//cout<<tab->attribute_name<<endl;
	string type=tab->value_type;
	cell *c=tab->chead;
	cell *ct=t->chead;

	while(c!=NULL)
	{
		//cout<<c->cell_value<<" "<<ct->cell_value<<endl;
		if(c->cell_value.compare(val)==0)
		pi(ct,t,list);
		ct=ct->down;
		c=c->down;
	}
}


//write insert rows/columns
