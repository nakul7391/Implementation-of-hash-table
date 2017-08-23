#ifndef DATABASE_H
#define DATABASE_H

/*prototype for file list*/
typedef struct FILE_LIST
{
    char *file_name;  //store file name
    int word_count;   //store word count in that file
    struct FILE_LIST *file_next; //store next address
} file_list_t;

/*prototype for word list*/
typedef struct WORD_LIST
{
    char *word;     //store word
    int file_count; //store file count
    int word_count; //store word count
    file_list_t *file_head;  //store address of head
    struct WORD_LIST *word_next; //store next address
} word_list_t;

/*return flags*/
typedef enum { Failure,Success } status;

/*ceate node in word list*/
word_list_t *create_word_node(char *word);

/*create new node in file list*/
file_list_t *create_file_node(char *file_name);

/*function to check word exists or not and insert if not exists*/
status insert_word(word_list_t **head, word_list_t **tail,char *word, char *file_name);

/*insert file name into file list*/
status insert_file(file_list_t **head, char *file_name, int *file_count);

/*find word from the database*/
status find_word(word_list_t **head, char *word);

/*store database in file*/
status store_database(word_list_t **head, FILE *fp);

void print_word_list(word_list_t ** head);

/*get word from backup and update in database*/
status update_word(word_list_t **head, word_list_t **tail,char *word, int wc, int fc);

/*insert file name into the database*/
status update_file(word_list_t **head, char *file_name, int file_word_count, char *word);
#endif
