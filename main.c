#include <stdio.h>
#include "contact.h"

int main() {
    int choice;
    int sortChoice = 0;
    AddressBook addressBook;
    initialize(&addressBook); // Initialize the address book

    do {
        printf("\n================================================================\n");
        printf("                       ADDRESS BOOK MENU                       \n");
        printf("================================================================\n");
        printf("|  1.  Create Contact                                         |\n");
        printf("|  2.  Search Contact                                         |\n");
        printf("|  3.  Edit Contact                                           |\n");
        printf("|  4.  Delete Contact                                         |\n");
        printf("|  5.  List All Contacts                                      |\n");
        printf("|  6.  Save Contacts                                          |\n");
        printf("|  7.  Exit                                                   |\n");
        printf("----------------------------------------------------------------\n");
        printf("| Enter your choice -->> ");
        scanf("%d", &choice);
        printf("----------------------------------------------------------------\n");

        switch (choice) {
            case 1:
                printf("|   Creating a new contact...                                |\n");
                createContact(&addressBook);
                break;

            case 2:
                printf("|   Searching contacts...                                   |\n");
                searchContact(&addressBook);
                break;

            case 3:
                printf("|    Editing contact details...                              |\n");
                editContact(&addressBook);
                break;

            case 4:
                printf("|    Deleting contact...                                    |\n");
                deleteContact(&addressBook);
                break;

            case 5:
                printf("|   Listing all contacts...                                 |\n");
                listContacts(&addressBook, sortChoice);
                break;

            case 6:
                printf("|   Saving contacts to file...                              |\n");
                saveContactsToFile(&addressBook);
                printf("|   Contacts saved successfully!                            |\n");
                break;

            case 7:
                printf("|   Exiting program...                                      |\n");
                printf("|   Saving contacts before exit...                          |\n");
                saveContactsToFile(&addressBook);
                printf("|   All data saved. Goodbye!                                |\n");
                printf("================================================================\n");
                break;

            default:
                printf("|   Invalid choice! Please try again.                       |\n");
                printf("----------------------------------------------------------------\n");
                break;
        }

    } while (choice != 7);

    return 0;
}
