
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "address_book_fops.h"
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

	
	
	switch(mode){
		case e_list:{ 
			///This is a mode where it shows all of the list
			
				int myIndex = 0;
				char choice;
				do{
					menu_header(title);
					printf("=======================================================================================================\n");
					printf(": S.No : Name                        : Phone No                        : Email ID                     :\n");
	 				printf("=======================================================================================================\n");
					if(myIndex + 1 < address_book->count && choice == 'n'){
						myIndex++;
					}
					else if(myIndex > 0 && choice == 'p'){
						myIndex--;
					}
					printf(":  %-4d: %-28s: %-32s: %-29s:\n",address_book->list[myIndex].si_no, address_book->list[myIndex].name[0],
					address_book->list[myIndex].phone_numbers[0],
					address_book->list[myIndex].email_addresses[0]);
					for(int i = 1; i < 5; i++)	
					printf(":%-6c:%-29c: %-32s: %-29s:\n",' ',' ',
					address_book->list[myIndex].phone_numbers[i],
					address_book->list[myIndex].email_addresses[i]);
					printf("=======================================================================================================\n");
					choice = get_option(CHAR, msg);
				

				}while(choice != 'q');

			break;
		}
		case e_search:{
			char c = 'q';
			int myIndex = *index;
			do{
				if(strcmp("S", msg) == 0){
					c = get_option(CHAR, "Press Q to cancel: ");
					break;
				}
				printf(":  %-4d: %-28s: %-32s: %-29s:\n",address_book->list[myIndex].si_no, address_book->list[myIndex].name[0],
				address_book->list[myIndex].phone_numbers[0],
				address_book->list[myIndex].email_addresses[0]);
				for(int i = 1; i < 5; i++){
					printf(":%-6c:%-29c: %-32s: %-29s:\n",' ',' ',
					address_book->list[myIndex].phone_numbers[i],
					address_book->list[myIndex].email_addresses[i]);
				}
				printf("=======================================================================================================\n");
				
			}while(c != 'q' && c != 'Q');
			
			break;
		}

		case e_add:{ ///This is a mode where it shows the addressbook result after adding
			char c;
			int myIndex = *index;
			do{
				menu_header(title);
				
				printf("=======================================================================================================\n");
				printf(": S.No : Name                        : Phone No                        : Email ID                     :\n");
	 			printf("=======================================================================================================\n");
				printf(":  %-4d: %-28s: %-32s: %-29s:\n",address_book->list[myIndex].si_no, address_book->list[myIndex].name[0],
				address_book->list[myIndex].phone_numbers[0],
				address_book->list[myIndex].email_addresses[0]);
				for(int i = 1; i < 5; i++)	
					printf(":%-6c:%-29c: %-32s: %-29s:\n",' ',' ',
					address_book->list[myIndex].phone_numbers[i],
					address_book->list[myIndex].email_addresses[i]);
				printf("=======================================================================================================\n");
				c = get_option(CHAR, msg);
				
			}while(c != 'q' && c != 'Q');
			break;
		}

		case e_edit:{
			char c;
			int choice;
			do{
				c = get_option(CHAR, "Press s to select | q to cancel : ");
				if(c == 's'){
					do{
						choice = get_option(NUM, "Please select a number: ");
						if(choice < 0 || choice > address_book->count)
							printf("Invalid input\n");
						
					}while(choice < 0 || choice > address_book->count);
					break;
				}
			}while(c != 'q');
			if(c == 's') *index = choice;
			else *index = -1;
			break;
		}

		case e_delete:{
			int choice;
			char c;
			char deleteOption;
			do{
				c = get_option(CHAR, "Press s to select | q to cancel : ");
				if(c == 's'){
					do{
						choice = get_option(NUM, "Please select a number: ");
						if(choice < 0 || choice > address_book->count)
							printf("Invalid input\n");
						
					}while(choice < 0 || choice > address_book->count);
					break;
				}
			}while(c != 'q');

			if(c == 's')
			{

				strcpy(address_book->list[choice-1].name[0], address_book->list[address_book->count - 1].name[0]);
				for(int i = 0; i < 5; i++)
				{
					strcpy(address_book->list[choice-1].phone_numbers[i], address_book->list[address_book->count - 1].phone_numbers[i]);
					strcpy(address_book->list[choice-1].email_addresses[i],address_book->list[address_book->count - 1].email_addresses[i]);
				}
				address_book->count = address_book->count - 1;
			}
			break;
		}
	}

	return e_success;
}


//Function to clear screen depending on OS
void clear_screen(){
	#ifdef linux
		system("clear");
	#else
		system("cls");
	#endif
}


void menu_header(const char *str)
{
	fflush(stdout);


	//system("cls");
	clear_screen();

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
	int k = 0;
	
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
				list_contacts(address_book, "Search Result",&k, "Press q to quit | n next page | p previous page: ", e_list);
				break;
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
	int nameCount = 0;
	int phoneCount = 0; //total number of phone numbers added
	int emailCount = 0; //total number of emails added
	int user_choice;
	char *p;

	strcpy(newPerson.name[0], " "); /// Reinitializing the strings with default space
	for(int i = 0; i < 5; i ++){
		strcpy(newPerson.phone_numbers[i], " ");
		strcpy(newPerson.email_addresses[i], " ");
	}

	do{
		//Displaying the menu
	 	menu_header("Add Contact:\n\n");
		printf("0. Back\n");
		printf("1. Name: %s\n", newPerson.name[0]);
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
				nameCount++;
				printf("Enter the name: ");
				getchar();
				scanf("%[^\n]s", &newPerson.name[0]);
				break;

			case 2: //Option to enter a phone number for contact
				if(phoneCount < 5){
					printf("Enter Phone Number %d: [Please reenter the same option for alternate Phone Number]: ", phoneCount+1);
					scanf("%s", &newPerson.phone_numbers[phoneCount]);
					phoneCount++;
				} 
				else{
					printf("Already at max phone numbers for contact.\n");
				}
				break;

			case 3: //Option to enter a email for contact
				if(emailCount < 5){
					printf("Enter Email ID %d: [Please reenter the same option for alternate Email ID]: ", emailCount+1);
					scanf("%s", &newPerson.email_addresses[emailCount]);
					emailCount++;
				} 
				else {
					printf("Already at the max emails for contact.\n");
				}
				break;
		}
	} while(user_choice != 0);

	if(nameCount > 0 || phoneCount > 0 || emailCount > 0){
	//Increment count and assign SI_NO to count
		address_book->count++;
		newPerson.si_no = address_book->count;
	
	//Assign new contact to list in AddressBook struct
		address_book->list[address_book->count - 1] = newPerson;
	


		int k = address_book->count - 1;
		list_contacts(address_book, "Add Result",&k, "Press q to quit", e_add);
	}
	return e_success;

}

void edit_this_contact(AddressBook *address_book, int serial){
	int phoneCount = 0; //total number of phone numbers added
	int emailCount = 0; //total number of emails added
	int user_choice;
	int phone_choice;
	int email_choice;
	char *p;

	for(int i = 0; i < 5; i++){
		if(address_book->list[serial-1].phone_numbers[i][0] != ' ')
			phoneCount++;
		if(address_book->list[serial-1].email_addresses[i][0] != ' ')
			emailCount++;
	}

	do{
		//Displaying the menu
	 	menu_header("Edit Contact:\n\n");
		printf("0. Back\n");
		printf("1. Name: %s\n", address_book->list[serial-1].name[0]);
		printf("2. Phone No 1: %s\n", address_book->list[serial-1].phone_numbers[0]);

		if(phoneCount > 1){		//If there are more than one phone numbers added it will loop to display
			for(int i = 0; i < phoneCount-1; i++){
				printf("\t    %d: %s\n", i+2, address_book->list[serial-1].phone_numbers[i+1]);
			}
		}
	
		printf("3. Email ID 1: %s\n", address_book->list[serial-1].email_addresses[0]);

		if(emailCount > 1){		//If there are more than one emails added it will loop to display
			for(int i = 0; i < emailCount-1; i++){
				printf("\t    %d: %s\n", i+2, address_book->list[serial-1].email_addresses[i+1]);
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
		switch(user_choice) 
		{
			case 0:
				break;

			case 1:	//Option to enter a name for contact
				printf("Enter the name: ");
				getchar();
				scanf("%[^\n]s", &address_book->list[serial-1].name[0]);
				break;

			case 2: //Option to enter a phone number for contact
				do{
					phone_choice = get_option(NUM, "Please choose an existing phone number to edit, or select the the number of the next slot to add a phone [MAX 5 PHONE NUMBERS]: ");
					if(phone_choice < 1 || phone_choice > phoneCount+1 || phone_choice > 5){
						printf("Invalid input!\n");
					}
					if(phone_choice == phoneCount+1){
						phoneCount++;
					}
				} while(phone_choice < 1 || phone_choice > phoneCount+1 || phone_choice > 5);
				printf("Enter Phone Number %d: [Please reenter the same option for alternate Phone Number]: ", phone_choice);
				scanf("%s",address_book->list[serial-1].phone_numbers[phone_choice-1]);

				break;

			case 3: //Option to enter a email for contact
				do{
					email_choice = get_option(NUM, "Please choose an existing email to edit, or select the the number of the next slot to add a email [MAX 5 EMAILS]: ");
					if(email_choice < 1 || email_choice > emailCount+1 || email_choice > 5){
						printf("Invalid input!\n");
					}
					if(email_choice == emailCount+1){
						emailCount++;
					}					
				} while(email_choice < 1 || email_choice > emailCount+1 || email_choice > 5);

				printf("Enter Email ID %d: [Please reenter the same option for alternate Email ID]: ", email_choice);
				scanf("%s",address_book->list[serial-1].email_addresses[email_choice-1]);
				break;
		}
	} while(user_choice != 0);

}


Status search(const char *str, AddressBook *address_book, int loop_count, int field, const char *msg, Modes mode)
{
	/* Add the functionality for adding contacts here */

	int index = 0;
	switch(mode)
	{
		
		case e_search:
		{
			int result;
			printf("=======================================================================================================\n");
			printf(": S.No : Name                        : Phone No                        : Email ID                     :\n");
	 		printf("=======================================================================================================\n");
			switch(field)
			{
				case 1:
				{
					for(int i = 0; i < address_book->count; i++)
					{
						if(strcmp(str, address_book->list[i].name[0]) == 0)
						{
							result = i;
							list_contacts(address_book, "Search Result", &result ," ", e_search);
						}
					}
					break;
				}
				case 2:
				{
					
					for(int i = 0; i < address_book->count; i++)
					{
						for(int j = 0; j < 5; j++){
							if(strcmp(str, address_book->list[i].phone_numbers[j]) == 0)
							{
								result = i;
								list_contacts(address_book, "Search Result", &result ," ", e_search);
							}
						}
					}
					break;
				}
				case 3:
				{
					for(int i = 0; i < address_book->count; i++)
					{
						for(int j = 0; j < 5; j++)
						{
							if(strcmp(str, address_book->list[i].email_addresses[j]) == 0)
							{
								result = i;
								list_contacts(address_book, "Search Result", &result ," ", e_search);
							}
						}
					}
					break;
				}
				case 4:
				{
					for(int i = 0; i < address_book->count; i++){
						if(address_book->list[i].si_no == atoi(str))
						{	
							result = i;
							list_contacts(address_book, "Search Result", &result ," ", e_search);
						}
					}
					break;
				}
			}
			list_contacts(address_book, "Search Result", &result ,"S", mode);
			break;
		}
		case e_edit:
		{
			printf("=======================================================================================================\n");
			printf(": S.No : Name                        : Phone No                        : Email ID                     :\n");
	 		printf("=======================================================================================================\n");
			int result = -1;
			switch(field){
				case 1:{
					for(int i = 0; i < address_book->count; i++){
						if(strcmp(str, address_book->list[i].name[0]) == 0){
							result = i;
							list_contacts(address_book, "Search Result", &result ," ", e_search);
						}
					}
					break;
				}
				case 2:
				{
					
					for(int i = 0; i < address_book->count; i++)
					{
						for(int j = 0; j < 5; j++){
							if(strcmp(str, address_book->list[i].phone_numbers[j]) == 0)
							{
								result = i;
								list_contacts(address_book, "Search Result", &result ," ", e_search);
							}
						}
					}
					break;
				}
				case 3:
				{
					
					for(int i = 0; i < address_book->count; i++)
					{
						for(int j = 0; j < 5; j++){
							if(strcmp(str, address_book->list[i].email_addresses[j]) == 0)
							{
								result = i;
								list_contacts(address_book, "Search Result", &result ," ", e_search);
							}
						}						
					}
					break;
				}
				case 4:{
					for(int i = 0; i < address_book->count; i++){
						if(address_book->list[i].si_no == atoi(str)){
							result = i;
							list_contacts(address_book, "Search Result", &result ," ", e_search);
						}
					}
					break;
				}
			}
		    /// we get result, edit by 
			if(result != -1){
				list_contacts(address_book, "Search Result", &result, "Select a serial number: ", mode);
				edit_this_contact(address_book, result);
			}
			else
				list_contacts(address_book, "Search Result", &result ,"S", e_search);
			/// list_function in edit, int c = get_option(NUM, msg);

				

			break;
		}
		case e_delete:
		{ 
			printf("=======================================================================================================\n");
			printf(": S.No : Name                        : Phone No                        : Email ID                     :\n");
	 		printf("=======================================================================================================\n");
			int result = -1;
			switch(field)
			{
				case 1:
				{
					for(int i = 0; i < address_book->count; i++)
					{
						if(strcmp(str, address_book->list[i].name[0]) == 0)
						{
							result = i;
							list_contacts(address_book, "Search Result", &result ," ", e_search);
						}
					}
					break;
				}
				case 2:
				{
					
					for(int i = 0; i < address_book->count; i++)
					{
						for(int j = 0; j < 5; j++)
						{
							if(strcmp(str, address_book->list[i].phone_numbers[j]) == 0)
							{
								result = i;
								list_contacts(address_book, "Search Result", &result ," ", e_search);
							}
						}
						
					}
					break;
				}
				case 3:
				{
					for(int i = 0; i < address_book->count; i++)
					{
						for(int j = 0; j < 5; j++)
						{
							if(strcmp(str, address_book->list[i].email_addresses[j]) == 0)
							{
								result = i;
								list_contacts(address_book, "Search Result", &result ," ", e_search);
							}
						}
						
					}
					break;
				}
				case 4:
				{
					for(int i = 0; i < address_book->count; i++)
					{
						if(address_book->list[i].si_no == atoi(str))
						{
							result = i;
							list_contacts(address_book, "Search Result", &result ," ", e_search);
						}
					}
				}
				break;
			}
			if(result != -1)
				list_contacts(address_book, "Search Result", &result, "Press s to select SI_NO, q to quit:", mode);
			else
				list_contacts(address_book, "Search Result", &result ,"S", e_search);			
		}
	}
}

Status search_contact(AddressBook *address_book, Modes mode)
{
	/* Add the functionality for search contacts here */
	int user_choice;
	char str[32];
	char *p;

	do 
	{
		menu_header("Search contact by: ");
		printf("0. Back\n");
		printf("1. Name\n");
		printf("2. Phone\n");
		printf("3. Email\n");
		printf("4. Serial No.\n\n");
		printf("Please select an option: ");

		//Prompting the user to select a menu option 0-3
		do
		{
			user_choice = get_option(NUM, "Please enter an option 0-4: ");
			if(user_choice < 0 || user_choice > 4)
			{
				printf("Invalid input!\n");
			}
		} while(user_choice < 0 || user_choice > 4);

		//Switch for user choices
		switch(user_choice)
		{
			case 0: //Option to go back
				break;

			case 1: //Option to search for name
				do
				{
					//User inputs name to search for
					printf("Enter the name: ");
					getchar();
					scanf("%[^\n]s", &str);

					//If str length is greater than max name length possible
					if(strlen(str) > 32)
					{
						printf("Invalid name length! Try Again.\n");
					}
				} while(strlen(str) > 32);

				search(str, address_book, 0, user_choice, "", mode);
				break;

			case 2: //Option to search for phone number
				do
				{
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
				do
				{
					//User inputs email to search for
					printf("Enter the email: ");
					scanf("%s", &str);
					//If str length is greater than max email length possible prompt again
					if(strlen(str) > 32)
					{
						printf("Invalid email length! Try Again.\n");
					}
						
				}while(strlen(str) > 32);

				search(str, address_book, 0, user_choice, "", mode);				
				break;

			case 4: //Option to search for serial number
				printf("Enter the serial number: ");
				getchar();
				scanf("%[^\n]s", &str);
				search(str, address_book, 0, user_choice, "", mode);				
				break;

		}
	} while(user_choice != 0);

	return e_back;
}

Status edit_contact(AddressBook *address_book)
{ 	
	/* Add the functionality for edit contacts here */
	search_contact(address_book, e_edit);
}

Status delete_contact(AddressBook *address_book)
{	
	/* Add the functionality for delete contacts here */
	search_contact(address_book, e_delete);
}