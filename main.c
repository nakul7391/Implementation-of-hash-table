/*This program is to */
#include <stdio.h>
#include <stdlib.h>
#include <stdio_ext.h>
#include "database.h"
#include "options.h"

/*function to call option functions*/
int call_options(int option, int argc, char *argv[]);
/*function to show menu*/
int show_menu();

/*variable to hold creation of database*/
int database_created;

extern char backup[];

int main(int argc, char *argv[] )
{
		/*show option*/

		while(1)
		{
				if (call_options(show_menu(), argc, argv) == Failure)
				return 0;
		}



		return 0;
}

/*show option table and return choice*/
int show_menu()
{
		int option;
		printf("1.Create DB\n");
		printf("2.Search\n");
		printf("3.Display DB\n");
		printf("4.Save\n");
		printf("5.Update\n");
		printf("6.Exit\n");
		scanf("%d", &option);
		return option;
}

/*call function depends on option*/
int call_options(int option, int argc, char *argv[])
{
			char word[100], ch;

			switch (option)
			{
					case 1: if (argc == 1) //if there is no file in input
									{
											printf("Invalid arguments\n");
											return Failure;
									}
									//call create db function
									create_database(argc, argv);
									database_created = 1;
									break;
					case 2:	if ( database_created == 0 )
									{
										printf("No database......\n");
										return Success;
									}

									printf("Enter the word: ");
									scanf("%s", word);
									__fpurge(stdin);
									if (search_database(word) == Failure)
									printf("Not found\n");
									break;
					case 3:	if ( database_created == 0 )
									{
										printf("No database......\n");
										return Success;
									}

									display_database();
									break;
					case 4: if ( database_created == 0 )
									{
										printf("No database......\n");
										return Success;
									}

									save_database();
									printf("Database saved\n");
									break;
					case 5: if( database_created == 0 )
									{
											if ( get_database() == Failure )
											printf("No database.....\n");
											else
											{
												printf("Databse updation successfull\n");
												database_created = 1;
												printf("Do you want to delete backup (y/n): ");
												__fpurge(stdin);
												scanf("%c", &ch);
												if( ch == 'y' || ch == 'Y')
												{
												remove(backup);
												printf("Backup file deleted successfully\n");
												}
											}
									}
									else
									printf("Database already exists\n");
									break;
					case 6: exit(0);
									break;
					default: printf("Invalid option\n");
									break;
			}
}
