#include <stdio.h>
#include <stdlib.h>
#include <libpq-fe.h>
#include <iostream>
#include <string.h>

using namespace std;

void CloseConn(PGconn *conn)
{
  PQfinish(conn);
  getchar();
}

PGconn *ConnectDB()
{
	PGconn *conn = NULL;

	// Make a connection to the database
	conn = PQconnectdb("host=localhost dbname=vxbase sslmode=require user=postgres password=qwerty");

	// Check to see that the backend connection was successfully made 
    if (PQstatus(conn) != CONNECTION_OK)
    {
        printf("Connection to database failed");
        CloseConn(conn);
    }

	printf("Connection to database - OK\n");

	return conn;
}

void CreateTable(PGconn *conn)
{
	// Execute with sql statement
    PGresult *res = PQexec(conn, "CREATE TABLE test01 (v_scene char(255), v_shot char(255), v_type char(255), v_data char(255))");
    
	if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        printf("Create employee table failed");
        PQclear(res);
        CloseConn(conn);
    }

	printf("Create employee table - OK\n");

	// Clear result
	PQclear(res);
}

/* Append SQL statement and insert record into employee table */
void InsertRec(PGconn *conn, const char *vscene, const char *vshot, const char *vtype, const char *vdata)
{
  // Append the SQL statment
  std::string sSQL;
  sSQL.append("INSERT INTO test01 VALUES ('");
  sSQL.append(vscene);
  sSQL.append("', '");
  sSQL.append(vshot);
  sSQL.append("', '");
  sSQL.append(vtype);
  sSQL.append("', '");
  sSQL.append(vdata);
  sSQL.append("')");
 
  // Execute with sql statement
  PGresult *res = PQexec(conn, sSQL.c_str());

  if (PQresultStatus(res) != PGRES_COMMAND_OK)
  {
    cout << "Insert employee record failed\n";
    PQclear(res);
    CloseConn(conn);
  }

  cout << "Insert employee record - OK\n";

  // Clear result
  PQclear(res);
}

void FetchRec(PGconn *conn)
{
	// Will hold the number of field in employee table
	int nFields;

	// Start a transaction block
	PGresult *res  = PQexec(conn, "BEGIN");

    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        printf("BEGIN command failed");
        PQclear(res);
        CloseConn(conn);
    }

   // Clear result
    PQclear(res);

    // Fetch rows from employee table
    res = PQexec(conn, "DECLARE emprec CURSOR FOR select * from test01");
    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        printf("DECLARE CURSOR failed");
        PQclear(res);
        CloseConn(conn);
    }

	// Clear result
    PQclear(res);

    res = PQexec(conn, "FETCH ALL in emprec");

    if (PQresultStatus(res) != PGRES_TUPLES_OK)
    {
        printf("FETCH ALL failed");
        PQclear(res);
        CloseConn(conn);
    }

    // Get the field name
    nFields = PQnfields(res);

	// Prepare the header with employee table field name
	printf("\nFetch scene record:");
	printf("\n--------------------------------------------------------------------------------\n");
    for (int i = 0; i < nFields; i++)
        printf("%-20s", PQfname(res, i));
    printf("\n--------------------------------------------------------------------------------\n");

    // Next, print out the employee record for each row
    
    for (int i = 0; i < PQntuples(res); i++)
    {
        for (int j = 0; j < nFields; j++)
        {			
			printf("%.20s", PQgetvalue(res, i, j));

        }
        printf("\n");
    }
	
    PQclear(res);

    // Close the emprec
    res = PQexec(conn, "CLOSE emprec");
    PQclear(res);

    // End the transaction
    res = PQexec(conn, "END");

	// Clear result
    PQclear(res);
}

/* Erase record in employee table */
void RemoveRec(PGconn *conn, const char *key)
{
	
	std::string sSQL;
	sSQL.append("DELETE FROM test01 WHERE v_scene='");
	sSQL.append(key);
	sSQL.append("';");
	
	// Execute with sql statement  DELETE FROM test01 WHERE v_scene='Indoor scene';
	
    PGresult *res = PQexec(conn, sSQL.c_str());

    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        printf("Delete employees record failed.");
        PQclear(res);
        CloseConn(conn);
    }

	printf("\nDelete employees record - OK\n");

	// Clear result
	PQclear(res);
}
