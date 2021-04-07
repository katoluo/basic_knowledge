#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>


static int callback(void *data, int argc, char **argv, char **azColName)
{
  int i;
  for (i = 0; i != argc; ++i)
    fprintf(stdout, "%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
  fprintf(stdout, "\n");
  return 0;
}


int main(int argc, char *argv[])
{
  sqlite3 *db;
  char *zErrMsg = 0;
  int rc;
  char *sql;

  rc = sqlite3_open("database.db", &db);
  if (rc != SQLITE_OK) {
    fprintf(stdout, "Cannot open database: %s\n",
        sqlite3_errmsg(db));
    exit(EXIT_FAILURE);
  } else {
    fprintf(stdout, "Opened database successfully\n");
  }

  sql = "CREATE TABLE COMPANY("  \
         "ID INT PRIMARY KEY     NOT NULL," \
         "NAME           TEXT    NOT NULL," \
         "AGE            INT     NOT NULL," \
         "ADDRESS        CHAR(50)," \
         "SALARY         REAL );";

  rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
  if (rc != SQLITE_OK) {
    fprintf(stderr, "SQL error: %s\n", zErrMsg);
    sqlite3_free(zErrMsg);
  } else {
    fprintf(stdout, "Table created successfully\n");
  }

  sqlite3_close(db);
  return EXIT_SUCCESS;
}
