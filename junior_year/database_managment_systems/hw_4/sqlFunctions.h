#include <iostream>
#include <stdio.h>
#include <mysql/mysql.h>
#include <cstdlib>

using namespace std;

void die(const char* str) {
  fprintf(stderr, "Error: %s\n", str);
  exit(1);
}

void die(const char* str, const char* msg) {
  fprintf(stderr, "Error: %s (%s)\n", str, msg);
  exit(1);
}

MYSQL* connect() {
  MYSQL *conn = mysql_init(NULL);

  if(!mysql_real_connect(conn, "127.0.0.1", "richjed", "richjed", "richjed", 0, NULL, 0) ) {
    die("Failed to connect to database", mysql_error(conn));
  }

  return conn;
}

int select(const string attr, const string table) {
  
  MYSQL *conn = connect();

  //if (mysql_query(conn, "SELECT * FROM events;"))
  const string query = "SELECT " + attr + " FROM " + table + ";";

  if (mysql_query(conn, query.c_str()))
    die("Failed to execute query", mysql_error(conn));

  MYSQL_RES *res = mysql_store_result(conn);

  int numRows = mysql_num_rows(res);
  int numColumns = mysql_num_fields( res );

  cout << "---------------------------------------------------------" << endl;

  for(int i=0; i < numRows; i++) {
    MYSQL_ROW row = mysql_fetch_row(res);

    for(int j=0; j < numColumns; j++) {
      if (row[j] == NULL) {
        cout << "[NULL] ";
      }
      else {
        cout << "[" << row[j] << "] ";
      }
    }
    cout << endl;
  }

  cout << "---------------------------------------------------------" << endl;

  mysql_free_result(res);

  return 0;
}

int select1() {
  
  MYSQL *conn = connect();

  //if (mysql_query(conn, "SELECT * FROM events;"))
  const string query = "SELECT teamName, count(teamID) FROM teams NATURAL JOIN robots GROUP BY teamName;";

  if (mysql_query(conn, query.c_str()))
    die("Failed to execute query", mysql_error(conn));

  MYSQL_RES *res = mysql_store_result(conn);

  int numRows = mysql_num_rows(res);
  int numColumns = mysql_num_fields( res );

  cout << "---------------------------------------------------------" << endl;

  for(int i=0; i < numRows; i++) {
    MYSQL_ROW row = mysql_fetch_row(res);

    for(int j=0; j < numColumns; j++) {
      if (row[j] == NULL) {
        cout << "[NULL] ";
      }
      else {
        cout << "[" << row[j] << "] ";
      }
    }
    cout << endl;
  }

  cout << "---------------------------------------------------------" << endl;

  mysql_free_result(res);

  return 0;
}

int select2() {
  
  MYSQL *conn = connect();

  const string query = "SELECT teamName, memberName FROM teams NATURAL JOIN members ORDER BY teamName;";

  if (mysql_query(conn, query.c_str()))
    die("Failed to execute query", mysql_error(conn));

  MYSQL_RES *res = mysql_store_result(conn);

  int numRows = mysql_num_rows(res);
  int numColumns = mysql_num_fields( res );

  cout << "---------------------------------------------------------" << endl;

  for(int i=0; i < numRows; i++) {
    MYSQL_ROW row = mysql_fetch_row(res);

    for(int j=0; j < numColumns; j++) {
      if (row[j] == NULL) {
        cout << "[NULL] ";
      }
      else {
        cout << "[" << row[j] << "] ";
      }
    }
    cout << endl;
  }

  cout << "---------------------------------------------------------" << endl;

  mysql_free_result(res);

  return 0;
}

int insert(const string table, const string value) {
  
  MYSQL *conn = connect();

  const string query = "INSERT INTO " + table + " VALUES (" + value + ");";

  if (mysql_query(conn, query.c_str()))
    die("Failed to execute query", mysql_error(conn));

  return 0;
}

int update(const string table, const string attr, const string oldValue, const string newValue) {
  
  MYSQL *conn = connect();

  const string query = "UPDATE " + table + " SET " + attr + " = '" +  newValue + "' WHERE " + attr + " = '" + oldValue + "';";

  if (mysql_query(conn, query.c_str()))
    die("Failed to execute query", mysql_error(conn));

  return 0;
}

int delete_(const string table, const string attr, const string value) {
  
  MYSQL *conn = connect();

  const string query = "DELETE FROM " + table + " WHERE " + attr + " = '" +  value + "';";

  if (mysql_query(conn, query.c_str()))
    die("Failed to execute query", mysql_error(conn));

  return 0;
}

