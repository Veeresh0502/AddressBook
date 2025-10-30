#include <stdio.h>
#include <unistd.h>  
#include "contact.h"
#include "file.h"

void saveContactsToFile(AddressBook *addressBook) {
    FILE *fp;

    fp = fopen("test.csv", "w");  
    if (fp == NULL) {
        perror("Error opening test.csv");
        return;
    }

    // Write all contacts
    for (int i = 0; i < addressBook->contactCount; i++) {
        fprintf(fp, "%s,%s,%s\n",
                addressBook->contacts[i].name,
                addressBook->contacts[i].phone,
                addressBook->contacts[i].email);
    }

    fclose(fp);

    printf("================================================================\n");
    printf("   Contacts saved successfully to test.csv  \n");
    printf("================================================================\n");
}




void loadContactsFromFile(AddressBook *addressBook) {
    FILE *fp = fopen("test.csv", "r");
    if (fp == NULL) {
        perror("Error opening test.csv");
        return;
    }

    addressBook->contactCount = 0;
    while (fscanf(fp, "%[^,],%[^,],%[^\n]\n",
                  addressBook->contacts[addressBook->contactCount].name,
                  addressBook->contacts[addressBook->contactCount].phone,
                  addressBook->contacts[addressBook->contactCount].email) == 3)
    {
        addressBook->contactCount++;
    }

    fclose(fp);
}