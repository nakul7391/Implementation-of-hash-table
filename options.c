#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "database.h"
#include "options.h"

char backup[] = "backup.txt";

/*prototype for hash table of size 26*/
struct hashtable
{
    word_list_t *head;
    word_list_t *tail;
}hashtable[26];


/*read each file and store in database*/
status create_database(int argc, char *argv[])
{
      int i;
      FILE *fp;

      for ( i = 1; i < argc; i++ )
      {
          fp = fopen(argv[i],"r");    //open file in read mode
          /*read the words one by one and store*/
          read_characters(fp, argv[i]);
          fclose(fp);   //close the file
      }

      printf("Database creation successfull\n");
}

/*search database for word*/
status search_database(char *word)
{
    int key = hash_function(word);

    find_word(&hashtable[key].head, word);

}

/*read words from file*/
void read_characters(FILE *fp, char *file_name)
{
      int c, i = 0, key;
      char word[MAX_WORD_SIZE];

      while ( (c = fgetc(fp)) != EOF )
      {
          if ( c == '\n' || c == '\t' || c == ' ')
          {
              word[i] = '\0';
              /*get key for hash table*/
              key = hash_function(word);
              insert_word(&hashtable[key].head, &hashtable[key].tail, word, file_name); //insert into linked list
              i = 0;
          }
          else
            word[i++] = c;
      }
}

/*simple function to check first char of word and generate key*/
int hash_function(const char *word)
{
			int c;
			if( word[0] >= 65 && word[0] <= 90 )
			c = word[0] - 'A';
			else if( word[0] >= 97 && word[0] <= 122 )
			c = word[0] - 'a';
			return c;
}

/*show the database if exists*/
void display_database()
{
    int i;
    printf("----------Database-----------\n");
    for( i = 0; i < 26; i++ )
    print_word_list(&hashtable[i].head);
    printf("-----------------------------\n");
}

status save_database()
{
      int i;
      /*open back up file */
      FILE *fp = fopen(backup,"w");

      for ( i = 0; i < 26; i++ )
      {
            if( hashtable[i].head != NULL )
            {
                /*store key*/
                fprintf(fp,"%d#\n",i);
                /*store the database*/
                store_database(&hashtable[i].head, fp);
            }
      }

      fclose(fp);
      return Success;
}


/*get database from temp file*/
status get_database()
{
      FILE *fp = fopen(backup,"r");
      int c, key;


      /*if there is no file return failure*/
      if( fp == NULL )
      return Failure;

      /*get each char from file*/
      while( ( c = fgetc(fp)) != EOF )
      {
          if( c >= 48 && c <= 57 )
          key = get_store_index(c, fp);

          if( c >= 65 && c<= 90 || c >= 97 && c <= 122 )
          get_line_parse_line(c,fp, key);

      }

}

int get_store_index(char c, FILE *fp)
{
      char buff[100], *ptr;
      int i = 0;

      /*get index*/
      do{
         buff[i++] = c;
      } while( (c = fgetc(fp)) != '\n' );
      buff[i] = '\0';

      ptr = strtok(buff,"#");

      return atoi(ptr);
}

/*get whole line from the file*/
void get_line_parse_line(char c, FILE *fp, int key)
{
      char buff[1000], *word, *file_name, *ptr;
      int i = 0, wc, fc, file_word_count;

      do{
         buff[i++] = c;
      } while( (c = fgetc(fp)) != '\n' );
      buff[i] = '\0';

      /*get word*/
      word = strtok(buff,";");
      /*get word count*/
      wc = atoi (strtok(NULL,";"));
      /*get file count*/
      fc = atoi (strtok(NULL,";"));

      /*store the word wordcount and file count*/
      update_word (&hashtable[key].head, &hashtable[key].tail, word, wc, fc );

      /*store file names and count in database*/
      ptr = strtok( NULL,";");
      while( ptr )
      {
          file_word_count = atoi (strtok(NULL,";"));
          update_file( &hashtable[key].head, ptr, file_word_count, word);
          ptr = strtok( NULL,";");
      }
}
