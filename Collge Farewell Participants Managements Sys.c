#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_PARTICIPANTS 100
#define MAX_NAME_LENGTH 50
#define PHONE_NUMBER_LENGTH 11 // 10 digits + null terminator

// Structure to hold participant information
typedef struct {
    char name[MAX_NAME_LENGTH];
    char phoneNumber[PHONE_NUMBER_LENGTH]; // Phone number as a string
    int hasPaid; // 1 for paid, 0 for not paid
} Participant;

// Function prototypes
void inputParticipants(Participant participants[], int *count);
void displayParticipants(Participant participants[], int count);
void deleteParticipant(Participant participants[], int *count);
void updatePaymentStatus(Participant participants[], int count);
void displayPaymentStatus(Participant participants[], int count);
int isValidPhoneNumber(const char *phoneNumber); // Function to validate phone number

int main() {
    Participant participants[MAX_PARTICIPANTS]; // Array to store participants
    int count = 0; // Number of participants
    int choice;

    do {
        printf("\nCollege Farewell Participants Management System\n");
        printf("1. Add Participants\n");
        printf("2. Display All Participants\n");
        printf("3. Delete a Participant\n");
        printf("4. Update Payment Status\n");
        printf("5. Display Participants by Payment Status\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                inputParticipants(participants, &count);
                break;
            case 2:
                displayParticipants(participants, count);
                break;
            case 3:
                deleteParticipant(participants, &count);
                break;
            case 4:
                updatePaymentStatus(participants, count);
                break;
            case 5:
                displayPaymentStatus(participants, count);
                break;
            case 6:
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 6);

    return 0;
}

// Function to input participant information from the user
void inputParticipants(Participant participants[], int *count) {
    printf("Enter the number of participants to add (max %d): ", MAX_PARTICIPANTS);
    scanf("%d", count);

    // Validate the number of entries
    if (*count <= 0 || *count > MAX_PARTICIPANTS) {
        printf("Invalid number of participants. Please enter a number between 1 and %d.\n", MAX_PARTICIPANTS);
        *count = 0;
        return;
    }

    // Input each participant's name, phone number, and payment status
    for (int i = 0; i < *count; i++) {
        printf("Enter name for participant %d: ", i + 1);
        scanf(" %[^\n]", participants[i].name); // Read name with spaces
        
        do {
            printf("Enter phone number for '%s' (10 digits): ", participants[i].name);
            scanf("%s", participants[i].phoneNumber); // Read phone number
            
            if (!isValidPhoneNumber(participants[i].phoneNumber)) {
                printf("Invalid phone number! Please enter a valid 10-digit phone number.\n");
            }
        } while (!isValidPhoneNumber(participants[i].phoneNumber)); // Loop until valid

        do {
            printf("Has '%s' paid the fees? (1 for Yes, 0 for No): ", participants[i].name);
            scanf("%d", &participants[i].hasPaid); // Read payment status

            if (participants[i].hasPaid != 0 && participants[i].hasPaid != 1) {
                printf("Invalid input! Please enter either 1 or 0.\n");
            }
        } while (participants[i].hasPaid != 0 && participants[i].hasPaid != 1); // Loop until valid
    }
}

// Function to validate phone number format
int isValidPhoneNumber(const char *phoneNumber) {
    if (strlen(phoneNumber) != 10) return 0; // Must be exactly 10 digits

    for (int i = 0; i < 10; i++) {
        if (!isdigit(phoneNumber[i])) return 0; // Must be all digits
    }

    return 1; // Valid phone number
}

// Function to display all participants in the system
void displayParticipants(Participant participants[], int count) {
    if (count == 0) {
        printf("No participants available in the system.\n");
        return;
    }

    printf("\nList of Participants:\n");
    for (int i = 0; i < count; i++) {
        printf("%d. '%s' - Phone: %s - Payment Status: %s\n", 
               i + 1, 
               participants[i].name, 
               participants[i].phoneNumber,
               participants[i].hasPaid ? "Paid" : "Not Paid");
    }
}

// Function to delete a participant by name
void deleteParticipant(Participant participants[], int *count) {
    char query[MAX_NAME_LENGTH];
    
    if (*count == 0) {
        printf("No participants available to delete.\n");
        return;
    }

    printf("Enter the name of the participant you want to delete: ");
    scanf(" %[^\n]", query); // Read name with spaces

    for (int i = 0; i < *count; i++) {
        if (strcmp(participants[i].name, query) == 0) {
            // Shift remaining elements left
            for (int j = i; j < *count - 1; j++) {
                participants[j] = participants[j + 1];
            }
            (*count)--; // Decrease the count of participants
            printf("Participant '%s' has been deleted.\n", query);
            return;
        }
    }

    printf("The participant '%s' was not found in the system.\n", query);
}

// Function to update payment status of a participant by name
void updatePaymentStatus(Participant participants[], int count) {
    char query[MAX_NAME_LENGTH];
    
    if (count == 0) {
        printf("No participants available to update.\n");
        return;
    }

    printf("Enter the name of the participant whose payment status you want to update: ");
    scanf(" %[^\n]", query); // Read name with spaces

    for (int i = 0; i < count; i++) {
        if (strcmp(participants[i].name, query) == 0) {
            printf("Updating payment status for '%s'.\n", query);
            
            do {
                printf("Has '%s' paid the fees? (1 for Yes, 0 for No): ", query);
                scanf("%d", &participants[i].hasPaid); // Update payment status

                if (participants[i].hasPaid != 0 && participants[i].hasPaid != 1) {
                    printf("Invalid input! Please enter either 1 or 0.\n");
                }
            } while (participants[i].hasPaid != 0 && participants[i].hasPaid != 1); // Loop until valid
            
            printf("Payment status updated successfully.\n");
            return;
        }
    }

    printf("The participant '%s' was not found in the system.\n", query);
}

// Function to display participants based on payment status
void displayPaymentStatus(Participant participants[], int count) {
    if (count == 0) {
        printf("No participants available in the system.\n");
        return;
    }

    int choice;
    printf("\nDisplay Participants by Payment Status:\n");
    printf("1. Show Paid Participants\n");
    printf("2. Show Not Paid Participants\n");
    
    scanf("%d", &choice);

    if (choice == 1) {
        printf("\nList of Paid Participants:\n");
        for (int i = 0; i < count; i++) {
            if (participants[i].hasPaid) {
                printf("%d. '%s' - Phone: %s\n", 
                       i + 1, 
                       participants[i].name, 
                       participants[i].phoneNumber);
            }
        }
    } else if (choice == 2) {
        printf("\nList of Not Paid Participants:\n");
        for (int i = 0; i < count; i++) {
            if (!participants[i].hasPaid) {
                printf("%d. '%s' - Phone: %s\n", 
                       i + 1, 
                       participants[i].name, 
                       participants[i].phoneNumber);
            }
        }
    } else {
        printf("Invalid choice!\n");
    }
}