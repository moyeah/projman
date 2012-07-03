#include <libgda/libgda.h>
#include <sql-parser/gda-sql-parser.h>

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
insert_data (GdaConnection *connection)
{
}

int
create_project ()
{
  gda_init ();

  GdaConnection *connection;

  connection = open_connection ();

  insert_data (connection);

  gda_connection_close (connection);

  return 0;
}

int
create_client ()
{
  gda_init ();
}
