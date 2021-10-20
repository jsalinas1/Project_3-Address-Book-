#include <stdio.h>
#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "address_book_fops.h"
//#include "abk_log.h"
#include "address_book_menu.h"
#include "address_book.h"

int get_option(int type, const char *msg)
{
	/*
	 * Mutilfuction user intractions like
	 * Just an enter key detection
	 * Read an number
	 * Read a charcter
	 */ 

	/* Fill the code to add above functionality */
}

Status save_prompt(AddressBook *address_book)
{
	char option;

	do
	{
		main_menu();

		option = get_option(CHAR, "\rEnter 'N' to Ignore and 'Y' to Save: ");

		if (option == 'Y')
		{
			save_file(address_book);
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

	return e_success;
}

void menu_header(const char *str)
{
	fflush(stdout);

	system("clear");

	printf("#######  Address Book  #######\n");
	if (str != '\0')
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
				add_contacts(address_book);
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
				save_file(address_book);
				break;
			case e_exit:
				break;
		}
	} while (option != e_exit);

	return e_success;
}

Status add_contacts(AddressBook *address_book)
{
ContactInfo newPerson;
	int phoneCount = 0; //total number of phone numbers added
	int emailCount = 0; //total number of emails added
	int user_choice;

	strcpy(newPerson.name, " ");
	strcpy(newPerson.phone_numbers[0], " ");
	strcpy(newPerson.email_addresses[0], " ");

	do{
		//Displaying the menu
	 	menu_header("Add Contact:\n\n");
		printf("0. Back\n");
		printf("1. Name: %s\n", newPerson.name);
		printf("2. Phone No 1: %s\n", newPerson.phone_numbers[0]);

		if(phoneCount > 1){		//If there are more than one phone numbers added it will loop to display
			for(int i = 0; i < phoneCount-1; i++){
				printf("\t    %d: %s\n", i+2, newPerson.phone_numbers[i+1]);
			}
		}
	
		printf("3. Email ID 1: %s\n", newPerson.email_addresses);

		if(emailCount > 1){		//If there are more than one emails added it will loop to display
			for(int i = 0; i < emailCount-1; i++){
				printf("\t    %d: %s\n", i+1, newPerson.email_addresses[i+1]);
			}
		}

		//Prompting the user to select a menu option 0-3
		do{
			user_choice = get_option(NUM, "Please enter an option 0-3: ");
			if(user_choice < 0 || user_choice > 3){
				printf("Invalid input!\n");
			}

		} while(user_choice < 0 || user_choice > 3);

		//Switch for the user choices
		switch(user_choice) {
			case 0:
				break;
			case 1:	//Option to enter a name for contact
				printf("Enter the name: ");
				scanf("%s", &newPerson.name);
				break;
			case 2: //Option to enter a phone number for contact
				if(phoneCount < 5){
					printf("Enter Phone Number %d: [Please reenter the same option for alternate Phone Number]: ", phoneCount+1);
					scanf("%s", &newPerson.phone_numbers[phoneCount]);
					phoneCount++;
				} else{
					printf("Already at max phone numbers for contact.\n");
				}
				break;
			case 3: //Option to enter a email for contact
				if(emailCount < 5){
					printf("Enter Email ID %d: [Please reenter the same option for alternate Email ID]: ", emailCount+1);
					scanf("%s", &newPerson.email_addresses[emailCount]);
					emailCount++;
				} else {
					printf("Already at the max emails for contact.\n");
				}
				break;
		}
	} while(user_choice != 0);

	//Increment count and assign SI_NO to count
	address_book->count++;
	newPerson.si_no = address_book->count;

	/*
	Print contact info to .csv file
	Each 11 possible fields for the contact are separated by a comma.
	Unused fields for phone and email are set to a space.
	Adds a new line to the .csv at the end of the contact info.
	*/
	fprintf(address_book->fp, "%d", newPerson.si_no);
	fprintf(address_book->fp, "%c",FIELD_DELIMITER);
	fprintf(address_book->fp, "%s", newPerson.name);
	fprintf(address_book->fp, "%c",FIELD_DELIMITER);

	for(int i = 0; i < 5; i++){
		if(i < phoneCount){
			fprintf(address_book->fp, newPerson.phone_numbers[i]);
			fprintf(address_book->fp, "%c", FIELD_DELIMITER);
		} else {
			fprintf(address_book->fp, " ");
			fprintf(address_book->fp, "%c", FIELD_DELIMITER);
		}
	}

	for(int i = 0; i < 5; i++){
		if(i < emailCount){
			fprintf(address_book->fp, newPerson.email_addresses[i]);
			fprintf(address_book->fp, "%c", FIELD_DELIMITER);
		} else {
			fprintf(address_book->fp, " ");			
			fprintf(address_book->fp, "%c", FIELD_DELIMITER);
		}
	}
	fprintf(address_book->fp, "%c", NEXT_ENTRY);
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
