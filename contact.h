#ifndef CONTACT_H
#define CONTACT_H

/* Define maximum number of contacts */
#define MAX_CONTACTS 100

/* Define terminal text colors */
#define RESET "\033[0m"
#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define YELLOW "\033[0;33m"
#define BLUE "\033[0;34m"
#define MAGENTA "\033[0;35m"
#define CYAN "\033[0;36m"
#define WHITE "\033[0;37m"
#define DARK_GREEN "\033[0;32m"
#define DARK_BLUE "\033[0;34m"
#define DARK_PURPLE "\033[0;35m"
#define GRAY "\033[0;90m"
#define ORANGE "\033[38;5;208m"

/* Define contact structure */
typedef struct
{
    char name[50];
    char phone[15];
    char email[40];
} Contact;

/* Define address book structure */
typedef struct
{
    Contact contacts[MAX_CONTACTS];
    int contactCount;
} AddressBook;

/* Declare contact management functions */
void createContact(AddressBook *addressBook);
int searchContact(AddressBook *addressBook, int mode);
void editContact(AddressBook *addressBook);
void deleteContact(AddressBook *addressBook);
void listContacts(AddressBook *addressBook, int sortCriteria);
void initialize(AddressBook *addressBook);
void saveAndExit(AddressBook *addressBook);

/* Declare validation functions */
int validatename(char *name);
int validatephone(char *phone, AddressBook *addressBook, int currentIndex);
int validateemail(char *email, AddressBook *addressBook, int currentIndex);

#endif