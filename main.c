/*
 *  EZDB main.c
 *  Author: Gagondeep Srai
 *  E-Mail: humourless.conch@gmail.com
 *  Address: srai.io
 *
 *  For additional information go to:
 *  github.com/humourless/EZDB
 *  
 */

#include "main.h"

int main(int argc, const char * argv[])
{
	if (argc < 3) die("USAGE: ezdb <dbfile> <action> [action params]");

	char * filename = argv[1];
	char action = argv[2][0]; // the mode
	Connection * connection = openDatabase(filename, action);
	int id = 0;

	if (argc > 3) id = atoi(argv[3]);
	if (id >= MAX_ROWS) die("There's not that many records.");

	switch (action)
	{
		case 'c':
			createDatabase(connection);
			writeDatabase(connection);
			break;

		case 'g':
			if (argc != 4) die("Need an id to get");
			getDatabase(connection, id);
			break;

		case 's':
			if (argc != 6) die("Need id, name and email to set");
			setDatabase(connection, id, argv[4], argv[5]);
			writeDatabase(connection);
			break;

		case 'd':
			if (argc != 4) die("Need id to delete");
			deleteDatabase(connection, id);
			writeDatabase(connection);
			break;

		case 'l':
			listDatabase(connection);
			break;

		default:
			die("Invalid action, only: c = create, g = get, s = set, d = delete, l = list");
	}

	closeDatabase(connection);

	return EXIT_SUCCESS;
}
