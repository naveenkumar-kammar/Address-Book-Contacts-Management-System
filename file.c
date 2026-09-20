#include <stdio.h>
#include "file.h"


/* Save all contacts to contacts.txt */
void saveContactsToFile(AddressBook *addressBook)
{
    /* Define the logic to create a saveContactsToFile */
    
    int i;

    /* Open file in write mode */
    FILE *fp;
    fp = fopen("contacts.txt", "w");

    /* Check file opening */
    if (fp == NULL)
    {
        printf("Unable to open file\n");
        return;
    }

    /* Save contact count */
    fprintf(fp, "Contacts stored: %d\n", addressBook->contactCount);

    /* Save all contacts */
    for (i = 0; i < addressBook->contactCount; i++)
    {
        fprintf(fp, "%d) %s, %s, %s\n", i + 1, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
    }

    /* Close the file */
    fclose(fp);
}


/* Load contacts from contacts.txt */
void loadContactsFromFile(AddressBook *addressBook)
{
    /* Define the logic to create a loadContactsFromFile */

    int i;

    /* Open file in read mode */
    FILE *fp;
    fp = fopen("contacts.txt", "r");

    /* Check file opening */
    if (fp == NULL)
    {
        return;
    }

    /* Read contact count */
    fscanf(fp, "Contacts stored: %d", &addressBook->contactCount);

    /* Validate contact count */
    if (addressBook->contactCount < 0 || addressBook->contactCount > MAX_CONTACTS)
    {
        addressBook->contactCount = 0;
        fclose(fp);
        return;
    }

    /* Load all contacts */
    for (i = 0; i < addressBook->contactCount; i++)
    {
        fscanf(fp, "%*d) %49[^,], %14[^,], %39[^\n]", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
    }

    /* Close the file */
    fclose(fp);
}