/*Documentation

Name        : Naveenkumar Kammar
Student id  : 26018_039
Batch id    : 26018D
Start Date  : 07/09/2026
End date    : 19/09/2026

Description:
The following functions are implemented in the Address Book project to manage contacts. 

createContact()         :-> Adds a new contact by taking name, phone number and email ID from the user.
                         -> Validates every input before storing it to address book and allows the user to create another contact.

searchContact()         :-> Searches for contacts by name, phone number or email ID as selected by the user.
                         -> Displays all matching records.

editContact()           :-> Allows the user to modify the name, phone number, email ID or all fields of an existing contact as they want.
                         -> Validates the updated values using the same validation rules as creating a contact.

deleteContact()         :-> Deletes a selected contact by searching using name, phone number or email ID.
                         -> Asks for confirmation before deleting the selected contact.

listContacts()          :-> Displays all stored contacts in a formatted table.
                         -> Also displays the address book status such as maximum contacts allowed, total contacts stored and available slots.

saveContactsToFile()    :-> Writes the contact count and all contact details from memory into contacts.txt. 
                         -> Ensures that the contacts are preserved for future program executions. 

loadContactsFromFile()  :-> Reads the saved contact details from contacts.txt back into memory when the program starts. 
                         -> Ensures that the contacts are ready for further program operations.

validatename()          :-> Checks whether the name contains at least 3 characters and only alphabets and spaces.
                         -> Spaces are allowed, but numbers and symbols are not allowed.

validatephone()         :-> Checks whether the phone number contains exactly 10 digits, starts with a digit between 6 and 9, contains only digits.
                         -> Also checks that the phone number is unique.

validateemail()         :-> Checks whether the email ID contains only lowercase letters and digits, exactly one '@' symbol and exactly one '.' after '@', and no extra characters are allowed after '.com'.
                         -> Also checks that the email ID is unique.

saveAndExit()           :-> Calls saveContactsToFile() to write the contact count and all contact details from memory into contacts.txt.
                         -> Ensures the contacts are preserved for future executions and exits the program after saving the contacts.

*/


/*
Sample input:
+===============================+
|       ADDRESS BOOK MENU       |
+===============================+
|  1. Create contact            |
|  2. Search contact            |
|  3. Edit contact              |
|  4. Delete contact            |
|  5. List all contacts         |
|  6. Save and Exit             |
+===============================+
Enter your choice: 1

sample output:
------Create New contact------

-----Enter Contact Details----

Enter name: Naveenkumar Kammar
Enter phone: 8495965878
Enter email: naveenkumarkammar978@gmail.com

Saving...[######################] 100%
Contact added successfully...
Total contacts stored: 1

Do you want to create another contact? [Yes (Y/y) or No (N/n)]: n

Returning to main menu...

*/


#include <stdio.h>
#include "contact.h"

/* Main function */
int main()
{
    int choice, sortChoice;
    AddressBook addressBook;
    initialize(&addressBook); // Initialize the address book

    do
    {
        /* Display address book menu */
        printf(ORANGE "\n+===============================+\n" RESET);
        printf(BLUE "|     📖 ADDRESS BOOK MENU      |\n" RESET);
        printf(ORANGE "+===============================+\n" RESET);
        printf(YELLOW "|  1. ➕  Create contact        |\n" RESET);
        printf(YELLOW "|  2. 🔍  Search contact        |\n" RESET);
        printf(YELLOW "|  3. ✏️   Edit contact          |\n" RESET);
        printf(YELLOW "|  4. 🗑️   Delete contact        |\n" RESET);
        printf(YELLOW "|  5. 📋  List all contacts     |\n" RESET);
        printf(YELLOW "|  6. 💾  Save and Exit         |\n" RESET);
        printf(ORANGE "+===============================+\n" RESET);

        printf(GRAY "Enter your choice: " RESET);
        if (scanf("%d", &choice) != 1)
        {
            printf(RED "Invalid choice, Please enter a number.\n" RESET);
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n');

        switch (choice)
        {

            /* Create a new contact */
            case 1:
                printf(YELLOW "\n------Create New contact------\n" RESET);
                createContact(&addressBook);
                break;

            /* Search for contacts */
            case 2:
                printf(YELLOW "\n------Search for contacts-----\n" RESET);
                searchContact(&addressBook, 0);
                break;

            /* Edit an existing contact */
            case 3:
                printf(YELLOW "\n---------Edit contact---------\n" RESET);
                editContact(&addressBook);
                break;

            /* Delete a contact */
            case 4:
                printf(YELLOW "\n---------Delete contact--------\n" RESET);
                deleteContact(&addressBook);
                break;

            /* List all contacts */
            case 5:
                /* Display sorting menu */
                printf(YELLOW "\n---------List contacts--------\n" RESET);
                printf(ORANGE "\n+------------------------------+\n" RESET);
                printf(GRAY "|   📋 Select sort criteria    |\n" RESET);
                printf(ORANGE "+------------------------------+\n" RESET);
                printf(MAGENTA "|  1. ↕ 🔤 Sort by name        |\n" RESET);
                printf(MAGENTA "|  2. ↕ 📱 Sort by phone       |\n" RESET);
                printf(MAGENTA "|  3. ↕ 📧 Sort by email       |\n" RESET);
                printf(MAGENTA "|  4.🚪 Exit                   |\n" RESET);
                printf(ORANGE "+------------------------------+\n");

                printf(GRAY "Enter your choice: " RESET);
                if (scanf("%d", &sortChoice) != 1)
                {
                    printf(RED "Invalid choice, Please enter a number.\n" RESET);
                    while (getchar() != '\n');
                    break;
                }
                while (getchar() != '\n');

                listContacts(&addressBook, sortChoice);
                break;

            /* Save contacts and exit the program */
            case 6:
                /* Save contacts and exit */
                saveAndExit(&addressBook);
                break;

            default:
                printf(RED "Invalid choice, Please try again.\n" RESET);
        }
    } while (choice != 6);

    return 0;
}
