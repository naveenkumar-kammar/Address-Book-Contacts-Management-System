#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "contact.h"
#include "file.h"

/* Store Sl.No positions found during search */
static int searchedPositions[MAX_CONTACTS];
static int searchedCount = 0;


/* List contacts in sorted order */
void listContacts(AddressBook *addressBook, int sortCriteria)
{
    /* Define the logic to listContacts */

    Contact temp[MAX_CONTACTS];
    Contact swap;
    int i, j;
    int progress, delay;

    /* Copy contacts to temporary array */
    for (i = 0; i < addressBook->contactCount; i++)
    {
        temp[i] = addressBook->contacts[i];
    }

    /* Check if address book is empty */
    if (addressBook->contactCount == 0)
    {
        printf(RED "\nAddress Book is empty, There are no contacts to list.\n" RESET);
        return;
    }

    /* Check for exit option */
    if (sortCriteria == 4)
    {
        printf(DARK_PURPLE "\n-------------Exit-------------\n" RESET);
        printf(ORANGE "\nReturning to main menu...\n" RESET);
        return;
    }

    /* Validate sorting choice */
    if (sortCriteria < 1 || sortCriteria > 4)
    {
        printf(RED "Invalid choice, Please try again...\n" RESET);
        return;
    }

    /* Sort contacts using bubble sort */
    for (i = 0; i < addressBook->contactCount - 1; i++)
    {
        for (j = 0; j < addressBook->contactCount - 1 - i; j++)
        {

            /* Sort contacts by name */
            if (sortCriteria == 1)
            {
                if (strcmp(temp[j].name, temp[j + 1].name) > 0)
                {
                    swap = temp[j];
                    temp[j] = temp[j + 1];
                    temp[j + 1] = swap;
                }
            }

            /* Sort contacts by phone */
            else if (sortCriteria == 2)
            {
                if (strcmp(temp[j].phone, temp[j + 1].phone) > 0)
                {
                    swap = temp[j];
                    temp[j] = temp[j + 1];
                    temp[j + 1] = swap;
                }
            }

            /* Sort contacts by email */
            else if (sortCriteria == 3)
            {
                if (strcmp(temp[j].email, temp[j + 1].email) > 0)
                {
                    swap = temp[j];
                    temp[j] = temp[j + 1];
                    temp[j + 1] = swap;
                }
            }
        }
    }

    /* Display exit progress */
    printf("\n");
    for (progress = 1; progress <= 100; progress++)
    {
        printf(DARK_PURPLE "\rLoading...[" RESET);
        for (j = 1; j <= 21; j++)
        {
            j <= progress * 21 / 100 ? printf(DARK_PURPLE "#" RESET) : printf(DARK_PURPLE " " RESET);
        }
        printf(DARK_PURPLE "] %i%%" RESET, progress);
        fflush(stdout);
        for (delay = 0xffffff; delay--;);
    }
    printf("\n");

    /* Display contact table */
    printf(CYAN "\n================================= ADDRESS BOOK CONTACTS LIST ==================================\n" RESET);
    printf(GREEN "\n+-------+--------------------------+----------------+-----------------------------------------+\n" RESET);
    printf(BLUE "| %-5s | %-25s| %-15s| %-40s|\n" RESET, "Sl.No", "NAME", "PHONE", "EMAIL");
    printf(GREEN "+-------+--------------------------+----------------+-----------------------------------------+\n" RESET);

    /* Display all sorted contacts */
    for (i = 0; i < addressBook->contactCount; i++)
    {
        printf(GREEN "| %-5d | %-25s| %-15s| %-40s|\n" RESET, i + 1, temp[i].name, temp[i].phone, temp[i].email);
    }
    printf(GREEN "+-------+--------------------------+----------------+-----------------------------------------+\n" RESET);

    /* Display address book status */
    printf(CYAN "\n======ADDRESS BOOK STATUS======\n" RESET);
    printf(ORANGE "Maximum contacts allowed: " BLUE "%d\n" RESET, MAX_CONTACTS);
    printf(ORANGE "Contacts stored: " BLUE "%d\n" RESET, addressBook->contactCount);
    printf(ORANGE "Available slots: " BLUE "%d\n" RESET, MAX_CONTACTS - addressBook->contactCount);
    printf(CYAN "===============================\n" RESET);
}


/* Initialize address book */
void initialize(AddressBook *addressBook)
{
    /* Define the logic to initialize */

    addressBook->contactCount = 0;

    /* Load contacts from file during initialization (After files) */
    loadContactsFromFile(addressBook);
}


/* Save contacts and exit */
void saveAndExit(AddressBook *addressBook)
{
    /* Define the logic to saveAndExit */

    int j, progress, delay;

    /* Save contacts to file */
    saveContactsToFile(addressBook);

    /* Display exit progress */
    printf("\n");
    for (progress = 1; progress <= 100; progress++)
    {
        printf(DARK_PURPLE "\rSaving and Exiting...[" RESET);
        for (j = 1; j <= 22; j++)
        {
            j <= progress * 22 / 100 ? printf(DARK_PURPLE "#" RESET) : printf(DARK_PURPLE " " RESET);
        }
        printf(DARK_PURPLE "] %i%%" RESET, progress);
        fflush(stdout);
        for (delay = 0xffffff; delay--;);
    }
    printf(DARK_GREEN "\nAddress book saved and exit successfully...\n\n" RESET);
    printf(BLUE "\r✨✨✨   THANK YOU!   ✨✨✨\n\n" RESET);

    /* Exit the program */
    exit(EXIT_SUCCESS);
}


/* Create a new contact */
void createContact(AddressBook *addressBook)
{
    /* Define the logic to createContact */

    int j, delay, progress;
    char confirmchoice;
    char tempName[50];
    char tempPhone[15];
    char tempEmail[40];

    /* Repeat contact creation until user chooses No */
    do
    {
        /* Check if address book is full */
        if (addressBook->contactCount >= MAX_CONTACTS)
        {
            printf(RED "\nThe Address Book is already full...\n" RESET);
            return;
        }

        printf(CYAN "\n-----Enter Contact Details----\n" RESET);

        /* Validate contact name */
        while (1)
        {
            printf(GRAY "\nEnter name: " RESET);
            if (scanf("%49[^\n]", tempName) != 1)
            {
                printf(ORANGE "The name should not be empty,\nTry again...\n" RESET);
                while (getchar() != '\n');
                continue;
            }
            getchar();

            if (validatename(tempName))
            {
                break;
            }
        }

        /* Validate contact phone number */
        while (1)
        {
            printf(GRAY "\nEnter phone: " RESET);
            if (scanf("%14[^\n]", tempPhone) != 1)
            {
                printf(ORANGE "The phone number should not be empty,\nTry again...\n" RESET);
                while (getchar() != '\n');
                continue;
            }
            while (getchar() != '\n');

            if (validatephone(tempPhone, addressBook, -1))
            {
                break;
            }
        }

        /* Validate contact email */
        while (1)
        {
            printf(GRAY "\nEnter email: " RESET);
            if (scanf("%39[^\n]", tempEmail) != 1)
            {
                printf(ORANGE "The email should not be empty,\nTry again...\n" RESET);
                while (getchar() != '\n');
                continue;
            }
            while (getchar() != '\n');

            if (validateemail(tempEmail, addressBook, -1))
            {
                break;
            }
        }

        /* Store contact details */
        strcpy(addressBook->contacts[addressBook->contactCount].name, tempName);
        strcpy(addressBook->contacts[addressBook->contactCount].phone, tempPhone);
        strcpy(addressBook->contacts[addressBook->contactCount].email, tempEmail);

        /* Increment contact count */
        addressBook->contactCount++;

        /* Display save progress */
        printf("\n");
        for (progress = 1; progress <= 100; progress++)
        {
            printf(DARK_PURPLE "\rSaving...[" RESET);
            for (j = 1; j <= 21; j++)
            {
                j <= progress * 21 / 100 ? printf(DARK_PURPLE "#" RESET) : printf(DARK_PURPLE " " RESET);
            }
            printf(DARK_PURPLE "] %i%%" RESET, progress);
            fflush(stdout);
            for (delay = 0xffffff; delay--;);
        }
        printf(DARK_GREEN "\nContact added successfully...\n" RESET);
        printf(CYAN "Total contacts stored: " BLUE "%d\n" RESET, addressBook->contactCount);

        /* Ask whether to create another contact */
        while(1)
        {
            printf(YELLOW "\nDo you want to create another contact? " RESET);
            printf(RED "[Yes (Y/y) or No (N/n)]: " RESET);
            scanf(" %c", &confirmchoice);
            while(getchar() != '\n');

            /* Exit choice validation loop and create another contact */
            if(confirmchoice == 'Y' || confirmchoice == 'y')
            {
                printf(YELLOW "\nCreating another contact...\n" RESET);
                break;
            }

            /* Exit contact creation and return to main menu */
            else if(confirmchoice == 'N' || confirmchoice == 'n')
            {
                printf(ORANGE "\nReturning to main menu...\n" RESET);
                return;
            }

            /* Handle invalid choice */
            else
            {
                printf(RED "Invalid choice! Please enter Y/y or N/n.\n" RESET);
            }
        }
    } while(1);
}


/* Search for contacts */
int searchContact(AddressBook *addressBook, int mode)
{
    /* Define the logic for searchContact */

    int searchChoice;
    int i, j, delay, progress;
    int found, contactFound;
    char search[50];

    /* Check if address book is empty */
    if (addressBook->contactCount == 0)
    {
        printf(RED "\nAddress Book is empty, There are no contacts to search.\n" RESET);
        return 0;
    }

    /* Repeat search until user chooses Exit */
    do
    {
        /* Display search menu */
        printf(ORANGE "\n+------------------------------+\n" RESET);
        printf(GRAY "|  🔍 Select search criteria   |\n" RESET);
        printf(ORANGE "+------------------------------+\n" RESET);
        printf(MAGENTA "|  1. 🔍 🔤 Search by name     |\n" RESET);
        printf(MAGENTA "|  2. 🔍 📱 Search by phone    |\n" RESET);
        printf(MAGENTA "|  3. 🔍 📧 Search by email    |\n" RESET);
        printf(MAGENTA "|  4. 🚪 Exit                  |\n" RESET);
        printf(ORANGE "+------------------------------+\n" RESET);

        printf(GRAY "Enter your choice: " RESET);
        if (scanf("%d", &searchChoice) != 1)
        {
            printf(RED "Invalid choice, Please enter a number.\n" RESET);
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n');

        switch (searchChoice)
        {
            /* Search by name */
            case 1:
                /* Reset previous search results */
                searchedCount = 0;

                /* Reset previous contact found results */
                contactFound = 0;

                printf(CYAN "\n--------Search by name--------\n" RESET);
                printf(GRAY "\nEnter name: " RESET);
                if (scanf("%49[^\n]", search) != 1)
                {
                    printf(ORANGE "The name should not be empty,\nTry again...\n" RESET);
                    while (getchar() != '\n');
                    continue;
                }
                getchar();

                found = 0;

                /* Display search progress */
                printf("\n");
                for (progress = 1; progress <= 100; progress++)
                {
                    printf(DARK_PURPLE "\rSearching...[" RESET);
                    for (j = 1; j <= 18; j++)
                    {
                        j <= progress * 18 / 100 ? printf(DARK_PURPLE "#" RESET) : printf(DARK_PURPLE " " RESET);
                    }
                    printf(DARK_PURPLE "] %i%%" RESET, progress);
                    fflush(stdout);
                    for (delay = 0xffffff; delay--;);
                }
                printf("\n");

                /* Find matching contacts */
                for (i = 0; i < addressBook->contactCount; i++)
                {
                    if (strncmp(search, addressBook->contacts[i].name, strlen(search)) == 0)
                    {
                        if (found == 0)
                        {
                            printf(GREEN "\n+-------+--------------------------+----------------+-----------------------------------------+\n" RESET);
                            printf(BLUE "| %-5s | %-25s| %-15s| %-40s|\n" RESET, "Sl.No", "NAME", "PHONE", "EMAIL");
                            printf(GREEN "+-------+--------------------------+----------------+-----------------------------------------+\n" RESET);
                        }

                        printf(GREEN "| %-5d | %-25s| %-15s| %-40s|\n" RESET, i + 1, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);

                        /* Store the actual contact position */
                        searchedPositions[searchedCount++] = i + 1;

                        found = 1;
                        contactFound = 1;
                    }
                }
                if (found)
                {
                    printf(GREEN "+-------+--------------------------+----------------+-----------------------------------------+\n" RESET);
                }

                /* Display search result status */
                if (found == 0)
                {
                    printf(RED "Contact not found,\nTry again...\n" RESET);
                }

                /* Return to edit/delete operation after successful search */
                else if (found && mode == 1)
                {
                    return 1;
                }

                break;

            /* Search by phone */
            case 2:
                /* Reset previous search results */
                searchedCount = 0;

                /* Reset previous contact found results */
                contactFound = 0;

                printf(CYAN "\n--------Search by phone-------\n" RESET);
                printf(GRAY "\nEnter phone number: " RESET);
                scanf("%14s", search);
                while (getchar() != '\n');

                found = 0;

                /* Display search progress */
                printf("\n");
                for (progress = 1; progress <= 100; progress++)
                {
                    printf(DARK_PURPLE "\rSearching...[" RESET);
                    for (j = 1; j <= 18; j++)
                    {
                        j <= progress * 18 / 100 ? printf(DARK_PURPLE "#" RESET) : printf(DARK_PURPLE " " RESET);
                    }
                    printf(DARK_PURPLE "] %i%%" RESET, progress);
                    fflush(stdout);
                    for (delay = 0xffffff; delay--;);
                }
                printf("\n");

                /* Find matching contacts */
                for (i = 0; i < addressBook->contactCount; i++)
                {
                    if (strncmp(search, addressBook->contacts[i].phone, strlen(search)) == 0)
                    {
                        if (found == 0)
                        {
                            printf(GREEN "\n+-------+--------------------------+----------------+-----------------------------------------+\n" RESET);
                            printf(BLUE "| %-5s | %-25s| %-15s| %-40s|\n" RESET, "Sl.No", "NAME", "PHONE", "EMAIL");
                            printf(GREEN "+-------+--------------------------+----------------+-----------------------------------------+\n" RESET);
                        }

                        printf(GREEN "| %-5d | %-25s| %-15s| %-40s|\n" RESET, i + 1, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);

                        /* Store the actual contact position */
                        searchedPositions[searchedCount++] = i + 1;

                        found = 1;
                        contactFound = 1;
                    }
                }
                if (found)
                {
                    printf(GREEN "+-------+--------------------------+----------------+-----------------------------------------+\n" RESET);
                }

                /* Display search result status */
                if (found == 0)
                {
                    printf(RED "Contact not found,\nTry again...\n" RESET);
                }

                /* Return to edit/delete operation after successful search */
                else if (found && mode == 1)
                {
                    return 1;
                }

                break;

            /* Search by email */
            case 3:
                /* Reset previous search results */
                searchedCount = 0;

                /* Reset previous contact found results */
                contactFound = 0;

                printf(CYAN "\n--------Search by email-------\n" RESET);
                printf(GRAY "\nEnter email: " RESET);
                scanf("%39s", search);
                while (getchar() != '\n');

                found = 0;

                /* Display search progress */
                printf("\n");
                for (progress = 1; progress <= 100; progress++)
                {
                    printf(DARK_PURPLE "\rSearching...[" RESET);
                    for (j = 1; j <= 18; j++)
                    {
                        j <= progress * 18 / 100 ? printf(DARK_PURPLE "#" RESET) : printf(DARK_PURPLE " " RESET);
                    }
                    printf(DARK_PURPLE "] %i%%" RESET, progress);
                    fflush(stdout);
                    for (delay = 0xffffff; delay--;);
                }
                printf("\n");

                /* Find matching contacts */
                for (i = 0; i < addressBook->contactCount; i++)
                {
                    if (strncmp(search, addressBook->contacts[i].email, strlen(search)) == 0)
                    {
                        if (found == 0)
                        {
                            printf(GREEN "\n+-------+--------------------------+----------------+-----------------------------------------+\n" RESET);
                            printf(BLUE "| %-5s | %-25s| %-15s| %-40s|\n" RESET, "Sl.No", "NAME", "PHONE", "EMAIL");
                            printf(GREEN "+-------+--------------------------+----------------+-----------------------------------------+\n" RESET);
                        }

                        printf(GREEN "| %-5d | %-25s| %-15s| %-40s|\n" RESET, i + 1, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);

                        /* Store the actual contact position */
                        searchedPositions[searchedCount++] = i + 1;

                        found = 1;
                        contactFound = 1;
                    }
                }
                if (found)
                {
                    printf(GREEN "+-------+--------------------------+----------------+-----------------------------------------+\n" RESET);
                }

                /* Display search result status */
                if (found == 0)
                {
                    printf(RED "Contact not found,\nTry again...\n" RESET);
                }

                /* Return to edit/delete operation after successful search */
                else if (found && mode == 1)
                {
                    return 1;
                }

                break;

            /* Exit search menu */
            case 4:
                printf(DARK_PURPLE "\n-------------Exit-------------\n" RESET);
                printf(ORANGE "\nReturning to main menu...\n" RESET);

                /* Return to edit/delete operation if a contact was found */
                if (mode == 1)
                {
                    if (contactFound)
                    {
                        return 1;
                    }
                    else
                    {
                        return 0;
                    }
                }
                else
                {
                    return 0;
                }

            default:
                printf(RED "Invalid choice, Please try again...\n" RESET);
        }
    } while (searchChoice != 4);
    return 0;
}


/* Edit a contact */
void editContact(AddressBook *addressBook)
{
    /* Define the logic for editContact */

    int i, j, position, delay, editChoice, progress;
    char tempName[50];
    char tempPhone[15];
    char tempEmail[40];

    /* Check if address book is empty */
    if (addressBook->contactCount == 0)
    {
        printf(RED "\nAddress Book is empty, There are no contacts to edit.\n" RESET);
        return;
    }

    /* Search for the contact to edit */
    printf(YELLOW "\n------Search for a contact------\n" RESET);
    if (searchContact(addressBook, 1) == 0)
    {
        return;
    }

    /* Get contact position */
    while (1)
    {
        printf(GRAY "\nEnter the Sl. No. of the contact to edit: " RESET);
        if (scanf("%d", &position) != 1)
        {
            printf(RED "Invalid position. Please enter a number.\n" RESET);
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n');

        /* Validate that position belongs to the search results */
        int validSearchPosition = 0;
        for (j = 0; j < searchedCount; j++)
        {
            if (position == searchedPositions[j])
            {
                validSearchPosition = 1;
                break;
            }
        }
        if (validSearchPosition)
        {
            break;
        }
        printf(RED "Invalid position. Please select a Sl. No. from the search results.\n" RESET);
    }

    /* Convert position to array index */
    i = position - 1;

    /* Display selected contact */
    printf(CYAN "\n-----Contact to be edited-----\n" RESET);
    printf(GREEN "+-------+--------------------------+----------------+-----------------------------------------+\n" RESET);
    printf(GREEN "| %-5d | %-25s| %-15s| %-40s|\n" RESET, position, addressBook->contacts[position - 1].name, addressBook->contacts[position - 1].phone, addressBook->contacts[position - 1].email);
    printf(GREEN "+-------+--------------------------+----------------+-----------------------------------------+\n" RESET);

    /* Repeat edit options until user chooses Exit */
    do
    {
        /* Display edit menu */
        printf(ORANGE "\n+------------------------------+\n" RESET);
        printf(GRAY "|   ✏️  Select edit criteria    |\n" RESET);
        printf(ORANGE "+------------------------------+\n" RESET);
        printf(MAGENTA "|  1. ✏️  🔤 Edit by name       |\n" RESET);
        printf(MAGENTA "|  2. ✏️  📱 Edit by phone      |\n" RESET);
        printf(MAGENTA "|  3. ✏️  📧 Edit by email      |\n" RESET);
        printf(MAGENTA "|  4. ✏️  📝 Edit by All        |\n" RESET);
        printf(MAGENTA "|  5. 🚪 Exit                  |\n" RESET);
        printf(ORANGE "+------------------------------+\n" RESET);

        printf(GRAY "Enter your choice: " RESET);
        if (scanf("%d", &editChoice) != 1)
        {
            printf(RED "Invalid choice, Please enter a number.\n" RESET);
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n');

        switch (editChoice)
        {
            /* Edit contact name */
            case 1:
                /* Validate and update name */
                printf(CYAN "\n---------Edit by name---------\n" RESET);
                while (1)
                {
                    printf(GRAY "\nEnter name: " RESET);
                    if (scanf("%49[^\n]", tempName) != 1)
                    {
                        printf(ORANGE "The name should not be empty,\nTry again...\n" RESET);
                        while (getchar() != '\n');
                        continue;
                    }
                    getchar();

                    if (validatename(tempName))
                    {
                        /* Update contact name */
                        strcpy(addressBook->contacts[i].name, tempName);

                        /* Display edit progress */
                        printf("\n");
                        for (progress = 1; progress <= 100; progress++)
                        {
                            printf(DARK_PURPLE "\rEditing...[" RESET);
                            for (j = 1; j <= 20; j++)
                            {
                                j <= progress * 20 / 100 ? printf(DARK_PURPLE "#" RESET) : printf(DARK_PURPLE " " RESET);
                            }
                            printf(DARK_PURPLE "] %i%%" RESET, progress);
                            fflush(stdout);
                            for (delay = 0xffffff; delay--;);
                        }
                        printf(DARK_GREEN "\nContact name updated successfully...\n" RESET);
                        break;
                    }
                }

                /* Display contact after update*/
                printf(CYAN "\n-----Contact after updated----\n" RESET);
                printf(GREEN "+-------+--------------------------+----------------+-----------------------------------------+\n" RESET);
                printf(GREEN "| %-5d | %-25s| %-15s| %-40s|\n" RESET, position, addressBook->contacts[position - 1].name, addressBook->contacts[position - 1].phone, addressBook->contacts[position - 1].email);
                printf(GREEN "+-------+--------------------------+----------------+-----------------------------------------+\n" RESET);
                break;

            /* Edit contact phone */
            case 2:
                /* Validate and update phone */
                printf(CYAN "\n---------Edit by phone--------\n" RESET);
                while (1)
                {
                    printf(GRAY "\nEnter phone: " RESET);
                    if (scanf("%14[^\n]", tempPhone) != 1)
                    {
                        printf(ORANGE "The phone number should not be empty,\nTry again...\n" RESET);
                        while (getchar() != '\n');
                        continue;
                    }
                    while (getchar() != '\n');

                    if (validatephone(tempPhone, addressBook, i))
                    {
                        /* Update contact phone */
                        strcpy(addressBook->contacts[i].phone, tempPhone);

                        /* Display edit progress */
                        printf("\n");
                        for (progress = 1; progress <= 100; progress++)
                        {
                            printf(DARK_PURPLE "\rEditing...[" RESET);
                            for (j = 1; j <= 20; j++)
                            {
                                j <= progress * 20 / 100 ? printf(DARK_PURPLE "#" RESET) : printf(DARK_PURPLE " " RESET);
                            }
                            printf(DARK_PURPLE "] %i%%" RESET, progress);
                            fflush(stdout);
                            for (delay = 0xffffff; delay--;);
                        }
                        printf(DARK_GREEN "\nContact phone updated successfully...\n" RESET);
                        break;
                    }
                }

                /* Display contact after update*/
                printf(CYAN "\n-----Contact after updated----\n" RESET);
                printf(GREEN "+-------+--------------------------+----------------+-----------------------------------------+\n" RESET);
                printf(GREEN "| %-5d | %-25s| %-15s| %-40s|\n" RESET, position, addressBook->contacts[position - 1].name, addressBook->contacts[position - 1].phone, addressBook->contacts[position - 1].email);
                printf(GREEN "+-------+--------------------------+----------------+-----------------------------------------+\n" RESET);
                break;

            /* Edit contact email */
            case 3:
                /* Validate and update email */
                printf(CYAN "\n---------Edit by email--------\n" RESET);
                while (1)
                {
                    printf(GRAY "\nEnter email: " RESET);
                    if (scanf("%39[^\n]", tempEmail) != 1)
                    {
                        printf(ORANGE "The email should not be empty,\nTry again...\n" RESET);
                        while (getchar() != '\n');
                        continue;
                    }
                    while (getchar() != '\n');

                    if (validateemail(tempEmail, addressBook, i))
                    {
                        /* Update contact email */
                        strcpy(addressBook->contacts[i].email, tempEmail);

                        /* Display edit progress */
                        printf("\n");
                        for (progress = 1; progress <= 100; progress++)
                        {
                            printf(DARK_PURPLE "\rEditing...[" RESET);
                            for (j = 1; j <= 20; j++)
                            {
                                j <= progress * 20 / 100 ? printf(DARK_PURPLE "#" RESET) : printf(DARK_PURPLE " " RESET);
                            }
                            printf(DARK_PURPLE "] %i%%" RESET, progress);
                            fflush(stdout);
                            for (delay = 0xffffff; delay--;);
                        }
                        printf(DARK_GREEN "\nContact email updated successfully...\n" RESET);
                        break;
                    }
                }

                /* Display contact after update*/
                printf(CYAN "\n-----Contact after updated----\n" RESET);
                printf(GREEN "+-------+--------------------------+----------------+-----------------------------------------+\n" RESET);
                printf(GREEN "| %-5d | %-25s| %-15s| %-40s|\n" RESET, position, addressBook->contacts[position - 1].name, addressBook->contacts[position - 1].phone, addressBook->contacts[position - 1].email);
                printf(GREEN "+-------+--------------------------+----------------+-----------------------------------------+\n" RESET);
                break;

            /* Edit all contact details */
            case 4:
                /* Validate new contact name */
                printf(CYAN "\n----------Edit by All---------\n" RESET);
                while (1)
                {
                    printf(GRAY "\nEnter name: " RESET);
                    if (scanf("%49[^\n]", tempName) != 1)
                    {
                        printf(ORANGE "The name should not be empty,\nTry again...\n" RESET);
                        while (getchar() != '\n');
                        continue;
                    }
                    getchar();

                    if (validatename(tempName))
                    {
                        break;
                    }
                }

                /* Validate new contact phone number */
                while (1)
                {
                    printf(GRAY "\nEnter phone: " RESET);
                    if (scanf("%14[^\n]", tempPhone) != 1)
                    {
                        printf(ORANGE "The phone number should not be empty,\nTry again...\n" RESET);
                        while (getchar() != '\n');
                        continue;
                    }
                    while (getchar() != '\n');
                    
                    if (validatephone(tempPhone, addressBook, i))
                    {
                        break;
                    }
                }

                /* Validate new contact email address */
                while (1)
                {
                    printf(GRAY "\nEnter email: " RESET);
                    if (scanf("%39[^\n]", tempEmail) != 1)
                    {
                        printf(ORANGE "The email should not be empty,\nTry again...\n" RESET);
                        while (getchar() != '\n');
                        continue;
                    }
                    while (getchar() != '\n');

                    if (validateemail(tempEmail, addressBook, i))
                    {
                        break;
                    }
                }

                /* Update all contact details */
                strcpy(addressBook->contacts[i].name, tempName);
                strcpy(addressBook->contacts[i].phone, tempPhone);
                strcpy(addressBook->contacts[i].email, tempEmail);

                /* Display edit progress */
                printf("\n");
                for (progress = 1; progress <= 100; progress++)
                {
                    printf(DARK_PURPLE "\rEditing...[" RESET);
                    for (j = 1; j <= 20; j++)
                    {
                        j <= progress * 20 / 100 ? printf(DARK_PURPLE "#" RESET) : printf(DARK_PURPLE " " RESET);
                    }
                    printf(DARK_PURPLE "] %i%%" RESET, progress);
                    fflush(stdout);
                    for (delay = 0xffffff; delay--;);
                }
                printf(DARK_GREEN "\nContact updated successfully...\n" RESET);

                /* Display contact after update*/
                printf(CYAN "\n-----Contact after updated----\n" RESET);
                printf(GREEN "+-------+--------------------------+----------------+-----------------------------------------+\n" RESET);
                printf(GREEN "| %-5d | %-25s| %-15s| %-40s|\n" RESET, position, addressBook->contacts[position - 1].name, addressBook->contacts[position - 1].phone, addressBook->contacts[position - 1].email);
                printf(GREEN "+-------+--------------------------+----------------+-----------------------------------------+\n" RESET);
                break;

            /* Exit edit menu */
            case 5:
                printf(DARK_PURPLE "\n-------------Exit-------------\n" RESET);
                printf(ORANGE "\nReturning to main menu...\n" RESET);
                break;

            default:
                printf(RED "Invalid choice, Please try again...\n" RESET);
        }
    } while (editChoice != 5);
}


/* Delete a contact */
void deleteContact(AddressBook *addressBook)
{
    /* Define the logic for deleteContact */

    int i, j, delay, progress;
    char confirm;
    int position;

    /* Check if address book is empty */
    if (addressBook->contactCount == 0)
    {
        printf(RED "\nAddress Book is empty, There are no contacts to delete.\n" RESET);
        return;
    }

    /* Search for the contact to delete */
    printf(YELLOW "\n------Search for a contact-------\n" RESET);
    if (searchContact(addressBook, 1) == 0)
    {
        return;
    }

    /* Get contact position */
    while (1)
    {
        printf(GRAY "\nEnter the Sl. No. of the contact to delete (Enter 0 to exit): " RESET);
        if (scanf("%d", &position) != 1)
        {
            printf(RED "Invalid position. Please enter a number.\n" RESET);
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n');

        /* Exit delete operation */
        if (position == 0)
        {
            printf(DARK_PURPLE "\n-------------Exit-------------\n" RESET);
            printf(ORANGE "\nReturning to main menu...\n" RESET);
            return;
        }

        /* Validate that position belongs to the search results */
        int validSearchPosition = 0;

        for (j = 0; j < searchedCount; j++)
        {
            if (position == searchedPositions[j])
            {
                validSearchPosition = 1;
                break;
            }
        }

        if (validSearchPosition)
        {
            break;
        }

        printf(RED "Invalid position. Please select a Sl. No. from the search results.\n" RESET);
    }

    /* Display selected contact */
    printf(CYAN "\n----Contact to be deleted-----\n" RESET);
    printf(GREEN "+-------+--------------------------+----------------+-----------------------------------------+\n" RESET);
    printf(GREEN "| %-5d | %-25s| %-15s| %-40s|\n" RESET, position, addressBook->contacts[position - 1].name, addressBook->contacts[position - 1].phone, addressBook->contacts[position - 1].email);
    printf(GREEN "+-------+--------------------------+----------------+-----------------------------------------+\n" RESET);

    /* Confirm contact deletion */
    while (1)
    {
        printf(YELLOW "\nAre you sure you want to delete this contact? " RESET);
        printf(RED "[Yes (Y/y) or No (N/n)]: " RESET);
        scanf(" %c", &confirm);

        /* Confirm deletion */
        if (confirm == 'Y' || confirm == 'y')
        {
            break;
        }

        /* Cancel deletion */
        else if (confirm == 'N' || confirm == 'n')
        {
            printf(ORANGE "Delete operation cancelled...\n" RESET);
            return;
        }

        /* Handle invalid confirmation */
        else
        {
            printf(RED "Invalid choice, Please enter (Y/y) or (N/n)\n" RESET);
        }
    }

    /* Shift contacts after deletion */
    for (i = position - 1; i < addressBook->contactCount - 1; i++)
    {
        addressBook->contacts[i] = addressBook->contacts[i + 1];
    }

    /* Decrease contact count */
    addressBook->contactCount--;

    /* Display deletion progress */
    printf("\n");
    for (progress = 1; progress <= 100; progress++)
    {
        printf(DARK_PURPLE "\rDeleting...[" RESET);
        for (j = 1; j <= 19; j++)
        {
            j <= progress * 19 / 100 ? printf(DARK_PURPLE "#" RESET) : printf(DARK_PURPLE " " RESET);
        }
        printf(DARK_PURPLE "] %i%%" RESET, progress);
        fflush(stdout);
        for (delay = 0xffffff; delay--;);
    }
    printf(RED "\nContact deleted successfully...\n" RESET);
}


/* Validate contact name */
int validatename(char *name)
{
    /* Define the logic for validatename */

    int i;

    /* Check for empty name */
    if ( name[0] == '\n')
    {
        printf(ORANGE "The name should not be empty,\nTry again...\n" RESET);
        return 0;
    }

    /* Check minimum name length */
    if (strlen(name) < 3)
    {
        printf(ORANGE "The name should contain minimum 3 characters,\nTry again...\n" RESET);
        return 0;
    }

    /* Check starting space */
    if (name[0] == ' ')
    {
        printf(ORANGE "The name should not start with space,\nTry again...\n" RESET);
        return 0;
    }

    /* Validate allowed characters */
    for (i = 0; name[i] != '\0'; i++)
    {
        /* Check for invalid characters */
        if (!isalpha(name[i]) && name[i] != ' ')
        {
            printf(ORANGE "The name should contain only alphabets and spaces,\nTry again...\n" RESET);
            return 0;
        }
    }

    /* Check spacing in name */
    for (i = 0; name[i] != '\0'; i++)
    {
        /* Check consecutive spaces */
        if (name[i] == ' ' && name[i + 1] == ' ')
        {
            printf(ORANGE "The name should not contain consecutive spaces,\nTry again...\n" RESET);
            return 0;
        }

        /* Check trailing space */
        if (name[i] == ' ' && name[i + 1] == '\0')
        {
            printf(ORANGE "The name should not contain trailing spaces,\nTry again...\n" RESET);
            return 0;
        }
    }
    return 1;
}


/* Validate phone number */
int validatephone(char *phone, AddressBook *addressBook, int currentIndex)
{
    /* Define the logic for validatephone */

    int i;

    /* Check for spaces */
    for (i = 0; phone[i] != '\0'; i++)
    {
        if (phone[i] == ' ')
        {
            printf(ORANGE "Space in phone number is not allowed,\nTry again...\n" RESET);
            return 0;
        }
    }

    /* Validate phone digits */
    for (i = 0; phone[i] != '\0'; i++)
    {
        /* Check for non-digit characters */
        if (!isdigit(phone[i]))
        {
            printf(ORANGE "The phone number should contain only digits,\nTry again...\n" RESET);
            return 0;
        }
    }

    /* Check phone number length */
    if (strlen(phone) != 10)
    {
        printf(ORANGE "The phone number should contain exactly 10 digits,\nTry again...\n" RESET);
        return 0;
    }

    /* Check starting digit */
    if (phone[0] < '6' || phone[0] > '9')
    {
        printf(ORANGE "The phone number should start with 6 to 9,\nTry again...\n" RESET);
        return 0;
    }

    /* Check for duplicate phone number */
    for (i = 0; i < addressBook->contactCount; i++)
    {
        /* Skip current contact */
        if (i != currentIndex)
        {
            /* Compare with existing phone numbers */
            if (strcmp(phone, addressBook->contacts[i].phone) == 0)
            {
                printf(ORANGE "The phone number already exists,\nTry again...\n" RESET);
                return 0;
            }
        }
    }

    return 1;
}


/* Validate email address */
int validateemail(char *email, AddressBook *addressBook, int currentIndex)
{
    /* Define the logic for validateemail */

    int i;
    int atcount = 0;
    int dotcount = 0;
    int atposition = -1;
    int dotposition = -1;

    /* Check for spaces */
    for (i = 0; email[i] != '\0'; i++)
    {
        if (email[i] == ' ')
        {
            printf(ORANGE "Space in email is not allowed,\nTry again...\n" RESET);
            return 0;
        }
    }

    /* Validate email characters */
    for (i = 0; email[i] != '\0'; i++)
    {
        /* Check for invalid email characters */
        if (email[i] != '@' && email[i] != '.' && !islower(email[i]) && !isdigit(email[i]))
        {
            printf(ORANGE "Email should contain lowercase letters, digits, '@' and '.' only,\nTry again...\n" RESET);
            return 0;
        }
    }

    /* Find email symbols */
    for (i = 0; email[i] != '\0'; i++)
    {
        /* Count @ and dot characters */
        if (email[i] == '@')
        {
            atcount++;
            atposition = i;
        }

        if (email[i] == '.')
        {
            dotcount++;
            dotposition = i;
        }
    }

    /* Validate @ symbol count */
    if (atcount > 1)
    {
        printf(ORANGE "Email should contain exactly one '@',\nTry again...\n" RESET);
        return 0;
    }

    /* Check for @ symbol */
    if (atcount == 0)
    {
        printf(ORANGE "Email should contain at least one '@',\nTry again...\n" RESET);
        return 0;
    }

    /* Check @ symbol position */
    if (atposition == 0)
    {
        printf(ORANGE "Email should not start with '@',\nTry again...\n" RESET);
        return 0;
    }

    /* Validate dot count */
    if (dotcount > 1)
    {
        printf(ORANGE "Email should contain exactly one '.',\nTry again...\n" RESET);
        return 0;
    }

    /* Check for dot symbol */
    if (dotcount == 0)
    {
        printf(ORANGE "Email should contain at least one '.',\nTry again...\n" RESET);
        return 0;
    }

    /* Check dot position */
    if (dotposition < atposition)
    {
        printf(ORANGE "'.' should be present after the '@',\nTry again...\n" RESET);
        return 0;
    }

    /* Check characters between @ and dot */
    if (dotposition == atposition + 1)
    {
        printf(ORANGE "At least one character should be present between '@' and '.',\nTry again...\n" RESET);
        return 0;
    }

    /* Check .com extension */
    if (strcmp(&email[dotposition], ".com") != 0)
    {
        printf(ORANGE "The email should end with '.com',\nTry again...\n" RESET);
        return 0;
    }

    /* Check for duplicate email */
    for (i = 0; i < addressBook->contactCount; i++)
    {
        /* Skip current contact */
        if (i != currentIndex)
        {
            /* Compare with existing emails */
            if (strcmp(email, addressBook->contacts[i].email) == 0)
            {
                printf(ORANGE "The email already exists,\nTry again...\n" RESET);
                return 0;
            }
        }
    }

    return 1;
}