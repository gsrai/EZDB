/*
 *  EZDB main.h
 *  Author: Gagondeep Srai
 *  E-Mail: humourless.conch@gmail.com
 *  Address: srai.io
 *
 *  For additional information go to:
 *  github.com/humourless/EZDB
 *  
 */

#ifndef EZDB_main_h
#define EZDB_main_h

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define MAX_DATA 512  // maximum field or data size.
#define MAX_ROWS 100

struct Record
{
    int id;  
    int set; // boolean, is record set (invoke setDatabase)
    char name[MAX_DATA];
    char email[MAX_DATA];
};

typedef struct Record Record;

struct Database
{
    Record rows[MAX_ROWS];
};

typedef struct Database Database;

struct Connection
{
    FILE * file;
    Database * db;
};

typedef struct Connection Connection;

// Beginning of function declaration:

void die(const char * message);
void printRecord(Record * r);
void loadDatabase(Connection * connection); 
Connection * openDatabase(const char * filename, char mode); 
void closeDatabase(Connection * connection); 
void writeDatabase(Connection * connection);
void createDatabase(Connection * connection);
void setDatabase(Connection * connection, int id, const char * name, const char * email);
void getDatabase(Connection * connection, int id);
void deleteDatabase(Connection * connection, int id);
void listDatabase(Connection * connection);

// End of function declaration.

#endif

