// OOP STL Struct Data Input Output

#include "vxbase_stl.h"

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
		void set_db(string set_name, string set_user,
					string set_type, string set_data)
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
				cout << i->name << " * "<< i->user << " * "<< i->type << " * "<< i->data <<endl;	
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
		void read_db (const char *fname)
		{
			string line;			
			ifstream bfile (fname);			
			vector<string> out_str;
			//vector<string>::iterator i;
			
			if (bfile.is_open())
			{
				while ( getline (bfile,line) )
				{									
					out_str=split(line, '|');
					ex.name=out_str[0];
					ex.user=out_str[1];
					ex.type=out_str[2];
					ex.data=out_str[3];
					var_list.push_back(ex);		
				}				
			}
			bfile.close();
		}
};

int main()
{	
	Base base;
	
	//base.set_db ("variale 01", "user", "string", "text 01");
	//base.set_db ("variale 02", "root", "string", "text 02");
	//base.set_db ("variale 03", "user", "string", "text 03");
	base.read_db("test.db");	
	base.get_db();
	
	string test("abc abc abd abc");
	cout << test[1] << endl;

	//base.write_db("test.db");	
	//test = split ("aaaa|bbbbb");
	
	return 0;
}
