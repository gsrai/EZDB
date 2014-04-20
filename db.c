/*
 *  EZDB db.c
 *  Author: Gagondeep Srai
 *  E-Mail: humourless.conch@gmail.com
 *  Address: srai.io
 *
 *  For additional information go to:
 *  github.com/humourless/EZDB
 *  
 */

#include "main.h"

void die(const char * message)
{
	if (errno)
	{
		perror(message);
	}
	else
	{
		printf("ERROR: %s\n", message);
	}
	exit(1);
}

void printRecord(Record * r)
{
	printf("%d %s %s\n", r->id, r->name, r->email);
}

void loadDatabase(Connection * connection)
{
	int rc = fread(connection->db, sizeof(Database), 1, connection->file);
	if (rc != 1) die("Failed to load database.");
}

Connection * openDatabase(const char * filename, char mode)
{
	Connection * conn = malloc(sizeof(Connection));
	if (!conn) die("Connection memory allocation error");

	conn->db = malloc(sizeof(Database));
	if (!conn->db) die("Database memory allocation error");

	if (mode == 'c')
	{	
		conn->file = fopen(filename, "w");
	}
	else
	{
		conn->file = fopen(filename, "r+");
		if (conn->file) loadDatabase(conn);
	}

	if (!conn->file) die("Failed to open the database file");

	return conn;
}

void closeDatabase(Connection * connection)
{
	if (connection)
	{
		if (connection->file) fclose(connection->file);
		if (connection->db) free(connection->db);
		free(connection);	
	}
} 

void writeDatabase(Connection * connection)
{
	rewind(connection->file);

	int rc = fwrite(connection->db, sizeof(Database), 1, connection->file);
	if (rc != 1) die("Failed to write database.");

	rc = fflush(connection->file); // clear the buffer after a write (output).
	if (rc == -1) die("Cannot flush database.");
}

void createDatabase(Connection * connection)
{
    int i = 0;

    for (i = 0; i < MAX_ROWS; ++i)
    {
    	// create a prototype and initialize it then assign it.
    	Record r = {.id = i, .set = 0}; // r is not a pointer so use . instead of ->
    	connection->db->rows[i] = r;
    }
}

void setDatabase(Connection * connection, int id, const char * name, const char * email)
{
	Record * r = &connection->db->rows[id];
	if (r->set) die("Already set, delete Record first");

	r->set = 1;
	
	char * result = strncpy(r->name, name, MAX_DATA); // copy name into r.name
	if (!result) die("Name copy failed"); // strncpy returns false if copy failed.
	
	result = strncpy(r->email, email, MAX_DATA);
	if (!result) die("Email copy failed");
}

void getDatabase(Connection * connection, int id)
{
	Record * r = &connection->db->rows[id];

	if (r->set)
	{
		printRecord(r);
	}
	else
	{
		die("ID is not set");
	}
}

void deleteDatabase(Connection * connection, int id)
{
	Record r = {.id = id, .set = 0};
	connection->db->rows[id] = r;
}

void listDatabase(Connection * connection)
{
	int i = 0;
	Database * db = connection->db;

	for (; i < MAX_ROWS; ++i)
	{
		Record * current = &db->rows[i];
		if (current->set) printRecord(current);
	}
}
