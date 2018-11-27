#include<stdlib.h>
#include<cstdio>
#include<iostream>
#include<string>
#include<fstream>
#include "dbms.cpp"
using namespace std;


/*

select * from table;

insert into table();
*/
void parse()
{

	/* Function to parse all queries based on the first word */

	string word;

	string condition;
	vector<string> select;
	vector<string> tables;

	vector<pair<string, string> > attr_list;
	string primary_attr= "NULL";
	pair<string, string> referred_key= make_pair("NULL", "NULL");
	string fk= "NULL";

	//Read query from the file
	ifstream tmp("tmp.txt");
	if (tmp.is_open())
	{

		while(tmp>>word)
		{
	////select statement
	//cout<<"word="<<word<<endl;
		if(word.compare("select")==0)
		{
			//Select from where query is parsed here
			do
			{
				tmp>>word;
				if(word.compare(",")!=0 && word.compare("from")!=0)
				{
					select.push_back(word);
				}
			}
			while(word.compare( "from")!=0);

			do
			{
				tmp>>word;
				if(word.compare(",")!=0 && word.compare(";")!=0 && word.compare("where")!=0)
				{
					tables.push_back(word);
				}
			}
			while(word.compare(";")!=0 && word.compare("where")!=0);

			char c;

			if(word.compare("where")==0)
			{
				//condition.append(word);
				do
				{
					tmp>>noskipws>>c;
					if(c!=';' && c!='\'')
					{
						condition.append(1, c);
					}
				}
				while(c!=';');
			}

			tmp.close();

			//writing temporarily to dump.txt
			ofstream t("dump.txt");
			int i=1, j;

			//handling cross function
			for( j=0; j<tables.size(); j++)
			{
				t<<tables[j]<<" ";
			}
			//cout<<" ; "<<endl;

			//handling sigma functions - condition
			t<<"sigma ( "<<condition<<" ) ; "<<endl;

			//handling attribute list selection
			t<<"pi ( ";
			for(j=0; j<select.size(); j++)
			{
				t<<select[j]<<" ";
			}
			t<<" ) ;"<<endl;
			t.close();

			/*-----------------*/
			ifstream in("dump.txt");

			/* Reading functions to be called from dump.txt and
			making those function calls */

			if(in.is_open())
			{
				vector<string> tab_list;
				in>>word;
				while(word.compare("sigma")!=0)
				{
					//cout<<word<<endl;;
					tab_list.push_back(word);
					in>>word;
				}
				table_schema*t1 =findTable(tab_list[0]);
				for(int i=1;i<tab_list.size();i++)
				{
					table_schema*t2 =findTable(tab_list[i]);
					cout<<t1->table_name<<" "<<t2->table_name<<endl;
					t1=cross(t1,t2);
				}
				/*------*/
				table_schema *tab=t1;
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
				/*-------*/

				cout<<t1->table_name<<endl;
				in>>word; //"("
				in>>word; //attribute_name
				string attr=word;
				in>>word; //=
				in>>word;
				string val=word;
				in>>word; //")"
				in>>word; //";"
				vector<string> attr_list;
				if(in>>word)
				{
					in>>word; //"("
					in>>word;
					while(word.compare(")")!=0)
					{
						cout<<word<<" ";
						attr_list.push_back(word);
						in>>word;
					}
					in>>word;//";"
				}
				cout<<endl;
				/*cout<<attr<<" "<<val<<" ";
				for(int i=0;i<attr_list.size();i++)
				{
					cout<<attr_list[i]<<" ";
				}
				cout<<endl;*/
				sigma(t1,attr,val,attr_list);
			}


			/*------------------*/

		}
		else if(word.compare("create")==0)
		{
			//Create query
			string t_name;

			tmp>>word;	//word has 'table'
			tmp>>word;	//word has table name
			t_name= word;

			//function call to create the table with the given name
			create_table(t_name);

			tmp>>word;	//word has '('
			tmp>>word;	//tmp has the next word

			while(word.compare("primary")!=0 && word.compare("foreign")!=0 && word.compare(")")!=0 && word.compare(";")!=0 )
			{

				string attr;
				string type;
				attr= word;
				tmp>>word;
				type= word;
				tmp>>word; //","

				//attr_list has list of attributes names
				//it is a vector pf pairs <attr_name, attr_type>
				attr_list.push_back(make_pair(attr, type));
				tmp>>word;
			}

			if(word.compare("primary")==0)
			{
				tmp>>word; 	//word has 'key'
				tmp>>word;	//word has '('
				tmp>>word;
				primary_attr= word;
				tmp>>word;	//word has ')'
				tmp>>word;  //word has ','
			}
			for(int i=0; i<attr_list.size(); i++)
			{
				if(primary_attr.compare(attr_list[i].first)==0)
				{
					table_schema* t=findTable(t_name);
					add_attribute(t, attr_list[i].first, attr_list[i].second, true );
				}
				else
				{
					table_schema* t=findTable(t_name);
					add_attribute( t, attr_list[i].first, attr_list[i].second, false );
				}
			}/*
			else if( word.compare("foreign")!=0	)
			{
				tmp>>word; 	//word has 'key'
				tmp>>word;	//word has '('
				tmp>>word;
				fk= word;
				tmp>>word;	//word has ')'
				tmp>>word;  //word has 'references'
				tmp>>word;	//word has 'table_name'
				referred_key.first= word;
				tmp>>word;	//word has 'pk referred'
				referred_key.second= word;
			}*/
			while(word.compare(";")!=0)
			{
				tmp>>word;
			}

			//writin to the file


		}
		else if(word.compare("insert")==0)
		{
			//insert query
			string t_name;
			tmp>>word;
			tmp>>word;	//table_name
			t_name= word;
			tmp>>word;	//values
			tmp>>word;	//'('
			vector<pair<string, string> > values;

			while(word.compare(")")!=0)
			{
				tmp>>word;	//new value
				if(word.compare("'")==0)
				{
					tmp>>word;
					pair<string, string> str= make_pair(word, "varchar");
					values.push_back(str);
					//cout<<word<<endl;
					tmp>>word;
					//cout<<word<<" ";
				}
				else
				{
					pair<string, string> str= make_pair(word, "int");
					values.push_back(str);
				}
				tmp>>word;	//','
				//cout<<word<<" ";

			}
			/*cout<<values.size()<<endl;
			for(int z=0;z<values.size();z++)
			{
				cout<<values[z].first<<" "<<values[z].second<<endl;
			}
			cout<<endl;*/
			table_schema* t=findTable(t_name);
			insert_row( t, values);
			tmp>>word;	//word has ';'
		}
		//cout<<"what to do"<<endl;
		}
	}
}


int main()
{

	 create_database("main_db");
	//formatting query input
	char c;
	ifstream myfile ("text.txt");

	//Each query is read separately from text.txt and
	//the formatted query is written back in tmp.txt
	//which is further used for processing
	if (myfile.is_open())
	{
		ofstream z("tmp.txt");
		int i=0;
		myfile>>c;

		//while loop runs till all the queries are exhausted
		while(!myfile.eof())
		{
			ofstream z("tmp.txt");
			string input;
			if(c==EOF)
				break;
			while (1)
			{

			 	if(c==';')
			 		break;
			 	if(c==',')
			 	input.append(" , ");
			 	else if(c=='(')
			 	input.append(" ( ");
			 	else if(c==')')
			 	input.append(" ) ");
			 	else if(c=='\'')
			 	input.append(" \' ");
			 	else if(c=='=')
			 	input.append(" = ");
			 	else
			 	input.append(1, c);
			 	myfile.get(c);

			}
			input.append(" ; ");
			z<<input<<endl;

			//function call to parse the query
			parse();
			z.close();
			if(c==EOF)
				break;
			myfile>>c;

		}

		myfile.close();
	}
	else cout << "Unable to open file";

	print();



	return 0;
}
