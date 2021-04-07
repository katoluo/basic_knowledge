#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

int main(int argc, char *argv[])
{
  sqlite3 *db;
  char *zErrMsg = 0;
  int rc;

  rc = sqlite3_open("database.db", &db);
  if (rc != SQLITE_OK) {
    fprintf(stderr, "Cannot open database: %s\n",
        sqlite3_errmsg(db));
    sqlite3_close(db);
    exit(EXIT_FAILURE);
  }

  fprintf(stdout, "Opened database successfully\n");

  sqlite3_close(db);
  return 0;
}
