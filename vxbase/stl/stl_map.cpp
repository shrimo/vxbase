// OOP STL MAP Data Input Output

#include <iostream>
#include <list>
#include <string.h>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <sstream>
#include <map>

using namespace std;
#include "split.h"

class Base 
{
	public:
		struct Variable_st
		{
			string name;
			string user;
			string type;
			string data;
		};
		
		list<Variable_st> var_list;
		Variable_st ex;
		list<Variable_st>::iterator i;
		
		//get data
		void set_db(string set_name,
					string set_user,
					string set_type,
					string set_data)
        {
            ex.name=set_name;
			ex.user=set_user;
			ex.type=set_type;
			ex.data=set_data;
			var_list.push_back(ex);
        }
        
        //print data
        void get_db()
        {
			for(i=var_list.begin(); i != var_list.end(); ++i)
			{
				cout << i->name << " | "<< i->user << " | "<< i->type << " | "<< i->data <<endl;	
			}
		}
		
		//write data to file
		void write_db(const char *fname)
		{
			ofstream bfile;
			bfile.open (fname);
			for(i=var_list.begin(); i != var_list.end(); ++i)
			{
				bfile << i->name << "|"<< i->user << "|"<< i->type << "|"<< i->data <<endl;
			}
			bfile.close();
		}
		
		//read data from file
		map<int,string> read_db (const char *fname)
		{
			string line;			
			ifstream bfile (fname);
			map<int,string> out_str;
			vector<string> _str;
			vector<string>::iterator i;			
			
			if (bfile.is_open())
			{
				int j=1;
				while ( getline (bfile,line) )
				{
					_str=split(line, '|');
					
					for(i=_str.begin(); i != _str.end(); ++i)
					{
						//cout << *i <<' '<< j << '\n';
						out_str.insert(std::make_pair(j,*i));
						j++;
					}
					j++;
					//out_str.push_back(_str[0]);
					
					//cout << line << '\n';
				}	
				}
			bfile.close();
			return out_str;
		}
};

int main()
{	
	Base base;
	map<int,string>_list;
	map<int,string>::iterator i;
	char end_str[255];
	//base.set_db ("variable 01", "user", "string", "text 01");
	//base.set_db ("variable 02", "root", "string", "text 02");
	//base.set_db ("variable 03", "user", "string", "text 03");
	
	_list=base.read_db("test.db");

	for(i=_list.begin(); i != _list.end(); ++i)
	{		
		cout<<i->second<<' ';
		strcpy(end_str,i->second.c_str());
		if(strstr(end_str, "@") != NULL) 
		{
			cout<<endl;
		}

	}
	//base.get_db();
	//base.write_db("test.db");	
	//test = split ("aaaa|bbbbb");	

	return 0;
}
