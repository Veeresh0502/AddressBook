#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "contact.h"
#include "file.h"
#include "populate.h"

void listContacts(AddressBook *addressBook, int sortCriteria) 
{
    if (addressBook->contactCount == 0) {
        printf("===================================================================\n");
        printf("|   No contacts available to display.                            |\n");
        printf("===================================================================\n");
        return;
    }

    char choice;
    printf("===================================================================\n");
    printf("|   Do you want to sort the contacts? (y/n): ");
    scanf(" %c", &choice);
    printf("===================================================================\n");

    if (choice == 'y' || choice == 'Y') {
        printf("|   Choose sorting criteria:                                     |\n");
        printf("| 1. Name                                                        |\n");
        printf("| 2. Phone Number                                                |\n");
        printf("| 3. Email ID                                                    |\n");
        printf("-------------------------------------------------------------------\n");
        printf("| Enter your choice: ");
        scanf("%d", &sortCriteria);
        printf("===================================================================\n");

        // Simple bubble sort (since contact list will be small)
        for (int i = 0; i < addressBook->contactCount - 1; i++) {
            for (int j = i + 1; j < addressBook->contactCount; j++) {
                int cmp = 0;
                switch (sortCriteria) {
                    case 1:
                        cmp = strcmp(addressBook->contacts[i].name, addressBook->contacts[j].name);
                        break;
                    case 2:
                        cmp = strcmp(addressBook->contacts[i].phone, addressBook->contacts[j].phone);
                        break;
                    case 3:
                        cmp = strcmp(addressBook->contacts[i].email, addressBook->contacts[j].email);
                        break;
                    default:
                        printf("|   Invalid sorting choice. Showing unsorted list.              |\n");
                        cmp = 0;
                        break;
                }
                if (cmp > 0) {
                    Contact temp = addressBook->contacts[i];
                    addressBook->contacts[i] = addressBook->contacts[j];
                    addressBook->contacts[j] = temp;
                }
            }
        }

        printf("|   Contacts sorted successfully!                              |\n");
        printf("===================================================================\n");
    }

    printf("\n===========================================================================\n");
    printf("                          CONTACT LIST MENU                      \n");
    printf("===========================================================================\n");
    printf("| %-4s | %-20s | %-12s | %-25s |\n", "No.", "Name", "Phone", "Email");
    printf("---------------------------------------------------------------------------\n");

    for (int i = 0; i < addressBook->contactCount; i++) {
        printf("| %-4d | %-20s | %-12s | %-25s |\n",
               i + 1,
               addressBook->contacts[i].name,
               addressBook->contacts[i].phone,
               addressBook->contacts[i].email);
    }

    printf("===========================================================================\n\n");
}


void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
    loadContactsFromFile(addressBook);

    printf("\n================================================================\n");
    printf("                        INITIALIZING DATABASE                   \n");
    printf("================================================================\n");

    if (addressBook->contactCount > 0) {
        printf("|   Loaded %-3d contact(s) from test.csv                     |\n", addressBook->contactCount);
    } else {
        printf("|    No contacts found in test.csv. Starting fresh.             |\n");
        populateAddressBook(addressBook);
        saveContactsToFile(addressBook);
    }

    printf("================================================================\n\n");
}

void saveAndExit(AddressBook *addressBook) {
    printf("\n================================================================\n");
    printf("|   Saving contacts and exiting program...                    |\n");
    printf("================================================================\n");
    saveContactsToFile(addressBook);
    exit(EXIT_SUCCESS);
}

// -------------------- Validation --------------------

int isValidName(const char *name) {
    for (int i = 0; name[i] != '\0'; i++) {
        if (!((name[i] >= 'A' && name[i] <= 'Z') || (name[i] >= 'a' && name[i] <= 'z')))
            return 0;
    }
    return 1;
}

int isValidPhone(AddressBook *addressBook, const char *phone, int ignoreIndex) {
    if (strlen(phone) != 10) return 0;
    for (int i = 0; i < 10; i++) {
        if (phone[i] < '0' || phone[i] > '9') return 0;
    }
    for (int i = 0; i < addressBook->contactCount; i++) {
        if (i != ignoreIndex && strcmp(addressBook->contacts[i].phone, phone) == 0) return 0;
    }
    return 1;
}

int isValidEmail(AddressBook *addressBook, const char *email, int ignoreIndex) {
    char *at = strchr(email, '@');
    char *dot = strstr(email, ".com");
    if (at == NULL || dot == NULL || at == email || *(at + 1) == '\0' || at > dot || dot == at + 1)
        return 0;
    for (int i = 0; i < addressBook->contactCount; i++) {
        if (i != ignoreIndex && strcmp(addressBook->contacts[i].email, email) == 0)
            return 0;
    }
    return 1;
}

// -------------------- Search --------------------

int searchByName(AddressBook *addressBook, const char *name) {
    for (int i = 0; i < addressBook->contactCount; i++) {
        if (strcasestr(addressBook->contacts[i].name, name) != NULL)
            return i;
    }
    return -1;
}

int searchName(AddressBook *addressBook, const char *name) {
    for (int i = 0; i < addressBook->contactCount; i++) {
        if (strcasecmp(addressBook->contacts[i].name, name) == 0)
            return i;
    }
    return -1;
}

int searchByPhone(AddressBook *addressBook, const char *phone) {
    for (int i = 0; i < addressBook->contactCount; i++) {
        if (strcmp(addressBook->contacts[i].phone, phone) == 0)
            return i;
    }
    return -1;
}

int searchByEmail(AddressBook *addressBook, const char *email) {
    for (int i = 0; i < addressBook->contactCount; i++) {
        if (strcmp(addressBook->contacts[i].email, email) == 0)
            return i;
    }
    return -1;
}

// -------------------- Create Contact --------------------

void createContact(AddressBook *addressBook) {
    printf("\n================================================================\n");
    printf("                       CREATE NEW CONTACT                       \n");
    printf("================================================================\n");

    int i = addressBook->contactCount;
    char input[50];

L0:
    printf("| Enter Name          : ");
    scanf("%s", input);
    if (!isValidName(input)) {
        printf("|   Invalid name! Only alphabets allowed.\n");
        goto L0;
    }
    strcpy(addressBook->contacts[i].name, input);

    char ph_no[20];
L1:
    printf("| Enter Phone Number  : ");
    scanf("%s", ph_no);
    if (!isValidPhone(addressBook, ph_no, -1)) {
        printf("|   Invalid phone number! Must be 10 digits and unique.\n");
        goto L1;
    }
    strcpy(addressBook->contacts[i].phone, ph_no);

    char email[50];
L2:
    printf("| Enter Email ID      : ");
    scanf("%s", email);
    if (!isValidEmail(addressBook, email, -1)) {
        printf("|   Invalid email format or duplicate! Example: name@gmail.com\n");
        goto L2;
    }
    strcpy(addressBook->contacts[i].email, email);

    addressBook->contactCount++;
    printf("----------------------------------------------------------------\n");
    printf("|   Contact added successfully!                              |\n");
    printf("================================================================\n\n");
}

// -------------------- Search Contact --------------------

void searchContact(AddressBook *addressBook) {
    printf("\n================================================================\n");
    printf("                       SEARCH CONTACT MENU                      \n");
    printf("================================================================\n");
    printf("| 1. Name                                                  |\n");
    printf("| 2. Phone no                                              |\n");
    printf("| 3. Email                                                 |\n");
    printf("----------------------------------------------------------------\n");

    int choice;
    printf("| Enter your choice : ");
    if (scanf("%d", &choice) != 1) {
        printf("|   Invalid input!                                     |\n");
        while (getchar() != '\n');
        return;
    }

    while (getchar() != '\n');

    char input[50];
    int ret = 0;

    switch (choice) {
        case 1:
            printf("| Enter Name : ");
            fgets(input, sizeof(input), stdin);
            input[strcspn(input, "\n")] = 0;
            break;
        case 2:
            printf("| Enter Phone : ");
            fgets(input, sizeof(input), stdin);
            input[strcspn(input, "\n")] = 0;
            break;
        case 3:
            printf("| Enter Email : ");
            fgets(input, sizeof(input), stdin);
            input[strcspn(input, "\n")] = 0;
            break;
        default:
            printf("|   Invalid option!                                     |\n");
            return;
    }

    printf("----------------------------------------------------------------------\n");
    printf("| %-20s | %-15s | %-25s |\n", "Name", "Phone", "Email");
    printf("----------------------------------------------------------------------\n");

    for (int i = 0; i < addressBook->contactCount; i++) {
        if (strcasestr(addressBook->contacts[i].name, input) != NULL ||
            strcasestr(addressBook->contacts[i].phone, input) != NULL ||
            strcasestr(addressBook->contacts[i].email, input) != NULL) {

            printf("| %-20s | %-15s | %-25s |\n",
                   addressBook->contacts[i].name,
                   addressBook->contacts[i].phone,
                   addressBook->contacts[i].email);
            ret = 1;
        }
    }

    if (!ret)
        printf("|   No contacts found.                                   |\n");

    printf("======================================================================\n\n");
}

// -------------------- Edit Contact --------------------

void editContact(AddressBook *addressBook) {
    printf("\n================================================================\n");
    printf("                          EDIT CONTACT MENU                     \n");
    printf("================================================================\n");
    printf("| 1. Name                                                   |\n");
    printf("| 2. Phone no                                               |\n");
    printf("| 3. Email                                                  |\n");
    printf("----------------------------------------------------------------\n");

    int choice;
    printf("| Enter your choice to edit: ");
    scanf("%d", &choice);
    getchar();

    int ret = -1;
    char input[100];

    switch (choice) {
        case 1:
            printf("| Enter existing Name : ");
            fgets(input, sizeof(input), stdin);
            input[strcspn(input, "\n")] = '\0';
            ret = searchName(addressBook, input);

            if (ret != -1) {
                printf("| New Name : ");
                fgets(input, sizeof(input), stdin);
                input[strcspn(input, "\n")] = '\0';

                if (!isValidName(input))
                    printf("|   Invalid name! Only alphabets allowed.\n");
                else {
                    strcpy(addressBook->contacts[ret].name, input);
                    printf("|   Name updated successfully.\n");
                    saveContactsToFile(addressBook);
                }
            } else
                printf("|   Contact not found!\n");
            break;

        case 2:
            printf("| Enter existing Phone : ");
            scanf("%s", input);
            getchar();
            ret = searchByPhone(addressBook, input);

            if (ret != -1) {
            L1:
                printf("| New Phone : ");
                char ph_no[20];
                scanf("%s", ph_no);
                getchar();

                if (!isValidPhone(addressBook, ph_no, ret)) {
                    printf("|   Invalid phone number! Must be 10 digits and unique.\n");
                    goto L1;
                }

                strcpy(addressBook->contacts[ret].phone, ph_no);
                printf("|   Phone updated successfully.\n");
                saveContactsToFile(addressBook);
            } else
                printf("|   Contact not found!\n");
            break;

        case 3:
            printf("| Enter existing Email : ");
            scanf("%s", input);
            getchar();
            ret = searchByEmail(addressBook, input);

            if (ret != -1) {
            L2:
                printf("| New Email : ");
                char email[100];
                scanf("%s", email);
                getchar();

                if (!isValidEmail(addressBook, email, ret)) {
                    printf("|   Invalid email format or duplicate.\n");
                    goto L2;
                }

                strcpy(addressBook->contacts[ret].email, email);
                printf("|   Email updated successfully.\n");
                saveContactsToFile(addressBook);
            } else
                printf("|   Contact not found!\n");
            break;

        default:
            printf("|   Invalid option!                                      |\n");
            break;
    }

    printf("================================================================\n\n");
}

// -------------------- Delete Contact --------------------

void deleteContact(AddressBook *addressBook) {
    printf("\n================================================================\n");
    printf("                         DELETE CONTACT MENU                     \n");
    printf("================================================================\n");
    printf("| 1. Name                                                  |\n");
    printf("| 2. Phone no                                              |\n");
    printf("| 3. Mail                                                  |\n");
    printf("----------------------------------------------------------------\n");

    int choice;
    printf("| Enter your choice to delete: ");
    scanf("%d", &choice);
    getchar();

    char input[100];
    int foundIndex = -1;

    switch (choice) {
        case 1:
            printf("| Enter Name (exact match required): ");
            fgets(input, sizeof(input), stdin);
            input[strcspn(input, "\n")] = '\0';
            for (int i = 0; i < addressBook->contactCount; i++) {
                if (strcasecmp(addressBook->contacts[i].name, input) == 0) {
                    foundIndex = i;
                    break;
                }
            }
            break;

        case 2:
            printf("| Enter Phone (exact match required): ");
            scanf("%s", input);
            for (int i = 0; i < addressBook->contactCount; i++) {
                if (strcmp(addressBook->contacts[i].phone, input) == 0) {
                    foundIndex = i;
                    break;
                }
            }
            break;

        case 3:
            printf("| Enter Email (exact match required): ");
            scanf("%s", input);
            for (int i = 0; i < addressBook->contactCount; i++) {
                if (strcasecmp(addressBook->contacts[i].email, input) == 0) {
                    foundIndex = i;
                    break;
                }
            }
            break;

        default:
            printf("|   Invalid option.                                     |\n");
            return;
    }

    if (foundIndex != -1) {
        printf("----------------------------------------------------------------\n");
        printf("| Found : %-15s | %-12s | %-25s |\n",
               addressBook->contacts[foundIndex].name,
               addressBook->contacts[foundIndex].phone,
               addressBook->contacts[foundIndex].email);
        printf("----------------------------------------------------------------\n");

        char confirm;
        printf("| Are you sure you want to delete (y/n)? ");
        scanf(" %c", &confirm);

        if (confirm == 'y' || confirm == 'Y') {
            for (int i = foundIndex; i < addressBook->contactCount - 1; i++) {
                addressBook->contacts[i] = addressBook->contacts[i + 1];
            }
            addressBook->contactCount--;
            printf("----------------------------------------------------------------\n");
            printf("|   Contact deleted successfully.                        |\n");
            printf("================================================================\n\n");
            saveContactsToFile(addressBook);
        } else {
            printf("|   Deletion cancelled.                                  |\n");
            printf("================================================================\n\n");
        }
    } else {
        printf("----------------------------------------------------------------\n");
        printf("|   Contact not found!                                  |\n");
        printf("================================================================\n\n");
    }
}
