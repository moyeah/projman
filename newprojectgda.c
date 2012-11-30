#include <libgda/libgda.h>
#include <sql-parser/gda-sql-parser.h>

#include "newprojectgda.h"

void
run_sql_non_select (GdaConnection *connection, const gchar *sql)
{
  GdaStatement *stmt;
  GError *error = NULL;
  gint nrows;
  const gchar *remain;
  GdaSqlParser *parser;

  parser = g_object_get_data (G_OBJECT (connection), "parser");
  stmt = gda_sql_parser_parse_string (parser, sql, &remain, &error);
  if (remain)
    g_print ("REMAINS: %s\n", remain);

  nrows = gda_connection_statement_execute_non_select (connection, stmt,
                                                       NULL, NULL, &error);
  if (nrows == -1)
    g_error ("NON SELECT error: %s\n",
             error && error->message ? error->message : "No detail");
  g_object_unref (stmt);
}

static GdaConnection *
open_connection ()
{
  GdaConnection *connection;
  GError *error = NULL;
  GdaSqlParser *parser;

  connection = gda_connection_open_from_string ("SQLite",
                                                "DB_DIR=./data;DB_NAME=test_db",
                                                NULL,
                                                GDA_CONNECTION_OPTIONS_NONE,
                                                &error);
  if (!connection)
  {
    g_print ("Could not open connection to SQLite database.\n File: %s\n",
             error && error->message ? error->message : "No detail");

  }

  parser = gda_connection_create_parser (connection);
  if (!parser)
    parser = gda_sql_parser_new ();
  g_object_set_data_full (G_OBJECT (connection), "parser",
                          parser, g_object_unref);

  return connection;
}

void
create_table (GdaConnection *connection)
{
  run_sql_non_select (connection,
                      "DROP table IF EXISTS projects");

  run_sql_non_select (connection,
                      "CREATE table projects ("
                        "name string not null primary key, "
                        "description string, "
                        "customer string)");
}

void
insert_data (GdaConnection *connection, ProjectInfo *project_info)
{
  gboolean res;
  GError *error = NULL;
  GValue *v1, *v2, *v3;

  v1 = gda_value_new_from_string (project_info->name, G_TYPE_STRING);
  v2 = gda_value_new_from_string (project_info->description, G_TYPE_STRING);
  v3 = gda_value_new_from_string (project_info->customer, G_TYPE_STRING);

  res = gda_connection_insert_row_into_table (connection, "projects", &error,
                                              "name", v1,
                                              "description", v2,
                                              "customer", v3,
                                              NULL);

  if (!res) {
    g_error ("Could not INSERT data into the 'projects' table: %s\n",
             error && error->message ? error->message : "No detail");
  }

  gda_value_free (v1);
  gda_value_free (v2);
  gda_value_free (v3);
}

void
display_data (GdaConnection *connection)
{
  GdaDataModel *data_model;
  GdaSqlParser *parser;
  GdaStatement *stmt;
  gchar *sql = "SELECT * FROM projects";
  GError *error = NULL;

  parser = g_object_get_data (G_OBJECT (connection), "parser");
  stmt = gda_sql_parser_parse_string (parser, sql, NULL, NULL);
  data_model = gda_connection_statement_execute_select (connection, stmt,
                                                        NULL, &error);
  g_object_unref (stmt);
  if (!data_model)
    g_error ("Could not get the contents of the 'projects' table: %s\n",
             error && error->message ? error->message : "No detail");
  gda_data_model_dump (data_model, stdout);
  g_object_unref (data_model);
}

int
create_project (ProjectInfo *project_info)
{
  gda_init ();

  GdaConnection *connection;

  connection = open_connection ();

  create_table (connection);

  insert_data (connection, project_info);

  display_data (connection);

  gda_connection_close (connection);

  return 0;
}

int
create_client ()
{
  gda_init ();
}
