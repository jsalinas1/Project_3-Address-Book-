#include <stdio.h>
//#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "address_book_menu.h"
#include "address_book_fops.h"

/*#include "abk_fileops.h"
#include "abk_log.h"
#include "abk_menus.h"
#include "abk.h"*/

void clearBuffer(){
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}

int get_option(int type, const char *msg)
{
	/*
	 * Mutilfuction user intractions like
	 * Just an enter key detection
	 * Read an number
	 * Read a charcter
	 */ 

	/* Fill the code to add above functionality */
	fflush(stdin);
	printf("%s ", msg);

	switch(type){
		case NONE:
			return 0;
		case NUM :{
			int n;
			scanf("%d", &n);
			return n;
		}
		case CHAR:{
			char choice;
			scanf("%c", &choice);
			return choice;
		}
	}

	

}

Status save_prompt(AddressBook *address_book)
{
	char option;

	do
	{
		main_menu();

		option = get_option(CHAR, "\rEnter 'N' to Ignore and 'Y' to Save: ");

		if(option != 'Y' && option != 'N'){
			printf("Invalid input.\n");
			continue;
		}

		if (option == 'Y')
		{
			//save_file(address_book);
			printf("Exiting. Data saved in %s\n", DEFAULT_FILE);

			break;
		}
	} while (option != 'N');

	free(address_book->list);

	return e_success;
}

Status list_contacts(AddressBook *address_book, const char *title, int *index, const char *msg, Modes mode)
{
	/* 
	 * Add code to list all the contacts availabe in address_book.csv file
	 * Should be menu based
	 * The menu provide navigation option if the entries increase the page size
	 */ 

	 /// list_contacts(address_book, "Search Result", Serial Number, "Press: [q] | Cancel: ", e_list)
	 /// 
	 /// *index is passed so we can passed in the choice(S. No) 
	 //address_book->fp = fopen(DEFAULT_FILE);
	 

	switch(mode){
		case e_list:{
			char c;
			do{
				menu_header(title);
				printf("=======================================================================================================\n");
				printf(": S.No : Name                        : Phone No                        : Email ID                     :\n");
	 			printf("=======================================================================================================\n");
				fscanf(address_book->fp, "%d,%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%s",
				address_book->list->si_no, address_book->list->name[0], address_book->list->phone_numbers[0],
				address_book->list->phone_numbers[1], address_book->list->phone_numbers[2],
				address_book->list->phone_numbers[3], address_book->list->phone_numbers[3],
				address_book->list->email_addresses[0], address_book->list->email_addresses[1],
				address_book->list->email_addresses[2], address_book->list->email_addresses[3],
				address_book->list->email_addresses[4]);

				printf(":  %-4d: %-28s: %-32s: %-29s:\n",address_book->list->si_no, address_book->list->name[0],
				address_book->list->phone_numbers[0][0] != ' ' ? address_book->list->phone_numbers[0] : " ",
				address_book->list->email_addresses[0][0] != ' ' ? address_book->list->email_addresses[0] : " ");
				for(int i = 1; i < 5; i++)	
					printf(":%-6c:%-29c: %-32s: %-29s:\n",' ',' ',
					address_book->list->phone_numbers[i],
					address_book->list->email_addresses[i]);
				printf("=======================================================================================================\n");
				c = get_option(CHAR, msg);
		}while(c != 'q' && c != 'Q');

		
		
		
		break;
		}
		case e_search:{
			
			break;
		}

	}

//	*index = get_option(NUM, msg);
	 
	/*
	e_search,
	e_edit,
	e_delete,
	e_list,*/

	 


	return e_success;
}

void menu_header(const char *str)
{
	fflush(stdout);


	system("cls");

	printf("#######  Address Book  #######\n");
	if (*str != '\0')
	{
		printf("#######  %s\n", str);
	}
}

void main_menu(void)
{
	menu_header("Features:\n");

	printf("0. Exit\n");
	printf("1. Add Contact\n");
	printf("2. Search Contact\n");
	printf("3. Edit Contact\n");
	printf("4. Delete Contact\n");
	printf("5. List Contacts\n");
	printf("6. Save\n");
	printf("\n");
	printf("Please select an option: ");
}

Status menu(AddressBook *address_book)
{
	ContactInfo backup;
	Status ret;
	int option;

	do
	{
		main_menu();

		option = get_option(NUM, "");

		if ((address_book-> count == 0) && (option != e_add_contact))
		{
			get_option(NONE, "No entries found!!. Would you like to add? Use Add Contacts");

			continue;
		}

		switch (option)
		{
			case e_add_contact:
				/* Add your implementation to call add_contacts function here */
				break;
			case e_search_contact:
				search_contact(address_book);
				break;
			case e_edit_contact:
				edit_contact(address_book);
				break;
			case e_delete_contact:
				delete_contact(address_book);
				break;
			case e_list_contacts:
				break;
				/* Add your implementation to call list_contacts function here */
			case e_save:
				//save_file(address_book);
				break;
			case e_exit:
				break;
		}
	} while (option != e_exit);

	return e_success;
}

Status add_contacts(AddressBook *address_book)
{
	/* Add the functionality for adding contacts here */
}

Status search(const char *str, AddressBook *address_book, int loop_count, int field, const char *msg, Modes mode)
{
	/* Add the functionality for adding contacts here */
}

Status search_contact(AddressBook *address_book)
{
	/* Add the functionality for search contacts here */
}

Status edit_contact(AddressBook *address_book)
{
	/* Add the functionality for edit contacts here */
}

Status delete_contact(AddressBook *address_book)
{
	/* Add the functionality for delete contacts here */
}


