/*
 * Software Systems - HW 03
 *
 * Implement Oracle of Bacon with BFS
 *
 * Author:
 *  Brendan Caporaletti <Brendan.Caporaletti@students.olin.edu>
 *  SeongHyeok Im (Steven) <SeongHyeok.Im@students.olin.edu>
 *
 * Note:
 *  Ingesting data was successfully done by 'insert.py' in the same directory.
 *  The original code had been mainly developed by Brendan, and SeongHyeok supported debugging.
 *  (Original code--> https://github.com/bren525/SoftwareSystems/blob/master/hw03/OracleofBacon.c)
 *  This new code is basically from original one and mainly developed by SeongHyeok.
 *  Currently, development of this code was stopped because original code is working!
 *
 * Style:
 *  Camel case for function and class.
 *  Under scodre for variable.
 *  Capital for #define.
 *  Add prefix 'g_' for global variable.
 */

/*****************************************************************************/
/* Include Headers */
/*****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql.h>

/*****************************************************************************/
/* Global Variables & Definitions */
/*****************************************************************************/
#define DB_HOST "localhost"
#define DB_USER "root"
#define DB_PASS "sim"
#define DB_NAME "softsys"

#define SQL_SELECT_ALL_WHERE_MOVIE    \
    "SELECT * FROM `actor_tbl` WHERE movie_name ='%s'"
#define SQL_SELECT_ACTOR_WHERE_MOVIE    \
    "SELECT actor_name FROM `actor_tbl` WHERE movie_name ='%s'"
#define SQL_SELECT_ALL_WHERE_ACTOR    \
    "SELECT * FROM `actor_tbl` WHERE actor_name ='%s'"
#define SQL_SELECT_MOVIE_WHERE_ACTOR    \
    "SELECT movie_name FROM `actor_tbl` WHERE actor_name ='%s'"

#define NUM_FIELDS  (4)

MYSQL *g_conn = NULL;

/*****************************************************************************/
/* Time Functions */
/*****************************************************************************/

//

/*****************************************************************************/
/* MySQL Functions */
/*****************************************************************************/
void exit_with_db_error()
{
    fprintf(stderr, "%s\n", mysql_error(g_conn));
    mysql_close(g_conn);
    exit(1);
}

void initDB()
{
    g_conn = mysql_init(NULL);
    if (g_conn == NULL) {
        fprintf(stderr, "[ERROR] mysql_init() failed\n");
        exit(1);
    }

    if (mysql_real_connect(g_conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0) == NULL) {
        exit_with_db_error();
    }
}

void uninitDB()
{
    mysql_close(g_conn);
}

void sendQuery(char *sql)
{
    if (mysql_query(g_conn, sql)) {
        exit_with_db_error();
    }
}

MYSQL_RES* getQueryResult()
{
    MYSQL_RES *result = NULL;

    result = mysql_store_result(g_conn);
    if (result == NULL) {
        exit_with_db_error();
    }

    return result;
}

void freeQueryResult(MYSQL_RES *res)
{
    mysql_free_result(res);
}

void testDB()
{
    char q[128] = {0, };
    char movie[65] = {0, };
    char actor[65] = {0, };
    MYSQL_RES *result = NULL;
    MYSQL_ROW row;
    int i;
    int num_fields;

    // 1
    mysql_real_escape_string(g_conn, movie, "Oblivion", strlen("Oblivion"));
    sprintf(q, SQL_SELECT_ACTOR_WHERE_MOVIE, movie);
    printf("Query: [%s]\n", q);

    sendQuery(q);
    result = getQueryResult();
    num_fields = mysql_num_fields(result);
    printf("num_fields: %d\n", num_fields);
    while (row = mysql_fetch_row(result)) {
        for (i = 0; i < num_fields; ++i) {
            printf("%s /", row[i]? row[i]: "NULL");
        }
        printf("\n");
    }
    freeQueryResult(result);

    // 2
    mysql_real_escape_string(g_conn, actor, "Cruise, Tom", strlen("Cruise, Tom"));
    sprintf(q, SQL_SELECT_ALL_WHERE_ACTOR, actor);
    printf("Query: [%s]\n", q);

    sendQuery(q);
    result = getQueryResult();
    num_fields = mysql_num_fields(result);
    printf("num_fields: %d\n", num_fields);
    while (row = mysql_fetch_row(result)) {
        for (i = 0; i < num_fields; ++i) {
            printf("%s /", row[i]? row[i]: "NULL");
        }
        printf("\n");
    }
    freeQueryResult(result);
}

/*****************************************************************************/
/*  */
/*****************************************************************************/

void searchPath(char *actor_start, char *actor_target)
{
    printf("Start: %s / Target: %s\n", actor_start, actor_target);

    // Add actor_start to the queue
    // Run while loop until the queue is empty
        // Dequeue one actor
        // Fetch all movies of the actor
        // For a movie in movies
            // Fetch all actors of the movie
            // For an actor in actors
                // Check actor is actor_target
                    // if then, found, break or return!
                    // if not, add to the queue
}

/*****************************************************************************/
/* Main */
/*****************************************************************************/

int main(void)
{
    initDB();

    //testDB();

    // Bacon, Kevin (I)
    // Cruise, Tom
    //  A Few Good Men
    searchPath("Bacon, Kevin (I)", "Cruise, Tom");

    uninitDB();
    return 0;
}
