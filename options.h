#ifndef OPTIONS_H
#define OPTIONS_H

#define MAX_WORD_SIZE 100

/*function to create database from the files given in commnad line arguments*/
status create_database(int argc, char *argv[]);

/*function to get characters from file*/
void read_characters(FILE *fp, char *file_name);

int hash_function(const char *name); /*function to calculate key*/

/*search the database for word*/
status search_database(char *word);

/*display the database*/
void display_database();

/*save database */
status save_database();

/*get database from file*/
status get_database();

/*get index from file and store the index*/
int get_store_index(char c, FILE *fp);

void get_line_parse_line(char c, FILE *fp, int key);
#endif
