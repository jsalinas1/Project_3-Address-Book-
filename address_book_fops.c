#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>
#include <ctype.h>

#include "address_book.h"

Status load_file(AddressBook *address_book)
{
	int ret;

	/* 
	 * Check for file existance
	 */

	address_book->list = (ContactInfo*)malloc(sizeof(ContactInfo)*100);
	address_book->count = 0;
    /// access fp file, then store it in list, then list++;
	if(address_book->fp = fopen(DEFAULT_FILE, "r")){
		fclose(address_book->fp);
		ret = 0;
	}

	if (ret == 0)
	{
		/* 
		 * Do the neccessary step to open the file
		 * Do error handling
		 */ 
		address_book->fp = fopen(DEFAULT_FILE, "a+");
		fscanf(address_book->fp, "%*[^0-9]%d", &address_book->count);
		
		//for(int i = 0; i < address_book->count; i++){
		
		char c;

		c = getc(address_book->fp);

		for(int i = 0; i < address_book->count; i++){
			fscanf(address_book->fp, "%d,%32[^,],%32[^,],%32[^,],%32[^,],%32[^,],%32[^,],%32[^,],%32[^,],%32[^,],%32[^,],%32[^,]", 
			&address_book->list[i].si_no,
			address_book->list[i].name[0], address_book->list[i].phone_numbers[0], address_book->list[i].phone_numbers[1], 
			address_book->list[i].phone_numbers[2], 
			address_book->list[i].phone_numbers[3], address_book->list[i].phone_numbers[4], address_book->list[i].email_addresses[0], 
			address_book->list[i].email_addresses[1], address_book->list[i].email_addresses[2], address_book->list[i].email_addresses[3], 
			address_book->list[i].email_addresses[4]);

		for (c = getc(address_book->fp); c != EOF; c = getc(address_book->fp))
        	if (c == '\n') break;
		}

		fclose(address_book->fp);
		//}

	}
	else
	{
		/* Create a file for adding entries */
		address_book->fp = fopen(DEFAULT_FILE, "w");
		fclose(address_book->fp);
	}

	return e_success;
}

Status save_file(AddressBook *address_book)
{
	/*
	 * Write contacts back to file.
	 * Re write the complete file currently
	 */ 

	

	address_book->fp = fopen(DEFAULT_FILE, "w");

	if (address_book->fp == NULL)
	{
		return e_fail;
	}

	fprintf(address_book->fp, "count=%d\n", address_book->count);

	for (int listIndex = 0; listIndex < address_book ->count; listIndex++)
	{
		// serial number
		fprintf(address_book ->fp, "%d,", address_book->list[listIndex].si_no);

		// name
		fprintf(address_book->fp, "%s,", address_book->list[listIndex].name);

		// phone number
		for (int i = 0; i < PHONE_NUMBER_COUNT; i++)
		{
			fprintf(address_book->fp, "%s,", address_book->list[listIndex].phone_numbers[i]);
		}

		// email address
		for (int i = 0; i < EMAIL_ID_COUNT; i++)
		{
			fprintf(address_book->fp, "%s,", address_book->list[listIndex].email_addresses[i]);
		}

		fputs("\n", address_book->fp);
	}
	/* 
	 * Add the logic to save the file
	 * Make sure to do error handling
	 */ 

	fclose(address_book->fp);

	return e_success;
}

/*
void main(){ /// Test function

	AddressBook test;
	test.list = (ContactInfo*)malloc(sizeof(ContactInfo)*100);
	load_file(&test);
	printf("List size: %d\n", test.count);
	for(int i = 0; i < test.count; i++)
		printf("%d %s\n", test.list[i].si_no, test.list[i].name[0]);
	

}*/