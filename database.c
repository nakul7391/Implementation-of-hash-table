#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "database.h"

/*create node for word list*/
word_list_t *create_word_node(char *word)
{
    word_list_t *new = malloc(sizeof(word_list_t));

    /*if no memory is there*/
    if( new == NULL )
    return NULL;

    /*else insert data*/
    new->word = strdup(word);
    new->word_count = 1;
    new->word_next = NULL;
    new->file_count = 1;
    new->file_head = NULL;
    return new;
}

/*create node for file list*/
file_list_t *create_file_node(char *file_name)
{
      //allocate memory for the new node
      file_list_t *new = malloc(sizeof(file_list_t));

      if( new == NULL )
      return NULL;

      /*else insert data*/
      new->file_name = strdup(file_name);
      new->word_count = 1;
      new->file_next = NULL;
      return new;
}


/*insert data at the last of the link list*/
status insert_word(word_list_t **head, word_list_t **tail,char *word, char *file_name)
{
    word_list_t *new;
    /*if there was no list*/
    if( *head == NULL )
    {
        if ( (new = create_word_node(word)) == NULL )
        return Failure;   //if head is null no need to search..
        insert_file(&new->file_head, file_name,&new->file_count);
        *head = new;      // create new node and link it to head and tail
        *tail = new;
        return Success;
    }

    /*check if word exists in list*/
    word_list_t *ptr = *head;

    while ( ptr->word_next != NULL && strcmp(ptr->word,word) != 0 ) //search for word
    ptr = ptr->word_next;

    /*if word is not found insert new node*/
    if ( strcmp(ptr->word, word) != 0 )
    {
        if ( (new = create_word_node(word)) == NULL )
        return Failure;
        insert_file(&new->file_head, file_name,&new->file_count);
        ptr->word_next = new;   //make link
        *tail = new;      // update tail
        return Success;
    }

    /*if word is found*/
    if( strcmp(ptr->word, word) == 0)
    {
        ptr->word_count++;  //increment word count
        insert_file(&ptr->file_head, file_name,&ptr->file_count);
    }

    return Success;
}

/*function to insert file in the list and compare if it exists or not*/
status insert_file(file_list_t **head, char *file_name, int *file_count)
{
      file_list_t *new;
  //    printf("%s ",file_name);
      /*IF THERE IS NOT LIST CREATE LIST*/
      if ( *head == NULL )
      {
          if ( (new = create_file_node(file_name)) == NULL )
          return Failure;
          *file_count = 1;
          *head = new;
          return Success;
      }

      /*find file name*/
      file_list_t *ptr = *head;

      while( ptr->file_next != NULL && strcmp(ptr->file_name,file_name) != 0 )
      ptr = ptr->file_next;

      /*if file name is not found insert new node*/
      if ( strcmp(ptr->file_name, file_name) != 0 )
      {
          if ( (new = create_file_node(file_name)) == NULL )
          return Failure;
          ptr->file_next = new;   //make link
          ++*file_count;
          return Success;
      }

      /*if file is found*/
      if( strcmp(ptr->file_name, file_name) == 0)
      ptr->word_count++;  //increment word count in file
      return Success;
}


/*function to print list*/
void print_word_list(word_list_t ** head)
{
    word_list_t *ptr = *head;
    while(ptr)
    {
        printf("%s| words %d|file %d|->\n",ptr->word, ptr->word_count, ptr->file_count);

        file_list_t *ptr_file = ptr->file_head;
        while (ptr_file)
        {
            printf("%s| words %d|->", ptr_file->file_name, ptr_file->word_count);
            ptr_file = ptr_file->file_next;
        }
        printf("\n");
        ptr = ptr->word_next;
    }
}

status find_word(word_list_t **head, char *word)
{
      /*if no list is there*/
      if( *head == NULL )
      return Failure;

      word_list_t *ptr = *head;

      /*find the word*/
      while ( ptr->word_next != NULL && strcmp(ptr->word,word) != 0)
      ptr = ptr->word_next;

      /*if word is found*/
      if ( strcmp(ptr->word, word) == 0 )
      {
          printf("---------------------------\n");
          printf("found word %s\n", ptr->word);
          printf("Word count %d\n", ptr->word_count);
          printf("present in files %d\n",ptr->file_count);
          file_list_t *ptr_file = ptr->file_head;

          while( ptr_file )
          {
              printf("in file %s %d times\n",ptr_file->file_name,ptr_file->word_count);
              ptr_file = ptr_file->file_next;
          }
          printf("---------------------------\n");
          return Success;
      }

      /*not found*/
      return Failure;
}


status store_database(word_list_t **head, FILE *fp)
{
    word_list_t *ptr = *head;

    while( ptr )
    {
        fprintf(fp,"%s;%d;%d;",ptr->word,ptr->word_count,ptr->file_count);

        file_list_t *ptr_file = ptr->file_head;

        while(ptr_file)
        {
            fprintf(fp,"%s;%d;",ptr_file->file_name,ptr_file->word_count);
            ptr_file = ptr_file->file_next;
        }
        fprintf(fp,"\n");
        ptr = ptr->word_next;
    }
}

status update_word(word_list_t **head, word_list_t **tail,char *word, int wc, int fc)
{
    word_list_t *new = malloc(sizeof(word_list_t));

    if( new == NULL )
    return Failure;

    /*create a node and insert a word*/
    new->word = strdup(word);
    new->word_count = wc;
    new->file_count = fc;
    new->file_head = NULL;
    /*if there is no list create list*/
    if( *head == NULL )
    {
        *head = new;
        *tail = new;
        return Success;
    }

    /*else find NULL then insert*/
    word_list_t *ptr = *head;

    while( ptr->word_next != NULL )
    ptr = ptr->word_next;

    ptr->word_next = new;
    *tail = new;
    return Success;
}

status update_file(word_list_t **head, char *file_name, int file_word_count, char *word)
{
    /*file word then find file head*/
    word_list_t *ptr = *head;

    while( strcmp(ptr->word, word) != 0 )
    ptr = ptr->word_next;

    /*create node for file list*/
    file_list_t *new = malloc(sizeof(file_list_t));

    if( new == NULL )
    return Failure;

    new->file_name = strdup(file_name);
    new->word_count = file_word_count;

    /*if it is the first node*/
    if( ptr->file_head == NULL )
    {
        ptr->file_head = new;
        return Success;
    }

    file_list_t *ptr_file = ptr->file_head;

    while( ptr_file->file_next != NULL )
    ptr_file = ptr_file->file_next;

    ptr_file->file_next = new;
    return Success;
}
