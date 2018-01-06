//g++ -Wall -o "%e" "%f" -I/usr/include/postgresql -lpq
#include "psql.h"

int main(int argc, char* argv[])
{
	//Start connection
	PGconn *conn = NULL;
  
	conn = ConnectDB();
  
	if (conn != NULL)
	{    
		//InsertRec(conn, "Indoor scene", "shot 003", "3D render","path to sequence 003");
		//RemoveRec(conn, "Indoor scene");		
		FetchRec(conn);
		CloseConn(conn);
	}
	
	return 0;
}
