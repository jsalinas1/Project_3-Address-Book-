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
				search_contact(address_book, e_search); 
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
			case 0: //Option to go back
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

	//Add a space for each empty index of phone or email
	for (int i = phoneCount; i < 5; i++)
		strcpy(newPerson.phone_numbers[i-1], " ");
	for (int i = emailCount; i < 5; i++)
		strcpy(newPerson.email_addresses[i-1], " ");


	address_book->list[address_book->count-1] = newPerson;
	int k = 0;
	list_contacts(address_book, "Add Result",&k, "Press q to quit", e_add);

}

Status search(const char *str, AddressBook *address_book, int loop_count, int field, const char *msg, Modes mode)
{
	/* Add the functionality for adding contacts here */
}

Status search_contact(AddressBook *address_book, Modes mode)
{
	int user_choice;
	char str[32];

	do {
		menu_header("Search contact by: ");
		printf("0. Back\n");
		printf("1. Name\n");
		printf("2. Phone\n");
		printf("3. Email\n");
		printf("4. Serial No.\n\n");
		printf("Please select an option: ");

		//Prompting the user to select a menu option 0-3
		do{
			user_choice = get_option(NUM, "Please enter an option 0-4: ");
			if(user_choice < 0 || user_choice > 4){
				printf("Invalid input!\n");
			}
		} while(user_choice < 0 || user_choice > 4);

		//Switch for user choices
		switch(user_choice){
			case 0: //Option to go back
				break;
			case 1: //Option to search for name
				do{
					//User inputs name to search for
					printf("Enter the name: ");
					scanf("%s", &str);
					//If str length is greater than max name length possible prompt again
					if(strlen(str) > 32)
						printf("Invalid name length! Try Again.\n");
				}while(strlen(str) > 32);

				search(str, address_book, 0, user_choice, "", mode);
				break;
			case 2: //Option to search for phone number
				do{
					//User inputs phone to search for
					printf("Enter the phone number: ");
					scanf("%s", &str);
					//If str length is greater than max phone length possible prompt again
					if(strlen(str) > 32)
						printf("Invalid phone length! Try Again.\n");
				}while(strlen(str) > 32);

				search(str, address_book, 0, user_choice, "", mode);				
				break;
			case 3: //Option to search for email
				do{
					//User inputs email to search for
					printf("Enter the email: ");
					scanf("%s", &str);
					//If str length is greater than max email length possible prompt again
					if(strlen(str) > 32)
						printf("Invalid email length! Try Again.\n");
				}while(strlen(str) > 32);

				search(str, address_book, 0, user_choice, "", mode);				
				break;
			case 4: //Option to search for serial number
				printf("Enter the serial number: ");
				scanf("%s", &str);
				search(str, address_book, 0, user_choice, "", mode);				
				break;
		}
	} while(user_choice != 0);

	return e_back;
}

Status edit_contact(AddressBook *address_book)
{
	/* Add the functionality for edit contacts here */
}

Status delete_contact(AddressBook *address_book)
{
	/* Add the functionality for delete contacts here */
}
