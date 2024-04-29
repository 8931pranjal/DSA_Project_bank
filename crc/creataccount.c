#include "header.h"

void insertAccount(struct Account** root, struct Account* newAccount) {
    if (*root == NULL) {
        *root = newAccount;
    } else {
        if (newAccount->accountNumber < (*root)->accountNumber) {
            insertAccount(&(*root)->left, newAccount);
        } else {
            insertAccount(&(*root)->right, newAccount);
        }
    }
}
// Function to search for an account in the BST
struct Account* searchAccount(struct Account* root, int accountNumber) {
    if (root == NULL || root->accountNumber == accountNumber) {
        return root;
    }

    if (accountNumber < root->accountNumber) {
        return searchAccount(root->left, accountNumber);
    }

    return searchAccount(root->right, accountNumber);
}




void createAccount() {
    if (numAccounts >= MAX_ACCOUNTS) {
        printf("Maximum number of accounts reached.\n");
        return;
    }

    struct Account* newAccount = (struct Account*)malloc(sizeof(struct Account));
    struct Customer newCustomer;

    // Get customer information
    printf("Enter customer name: ");
    scanf(" %[^\n]", newCustomer.name); 

    // Validate customer name (alphabetic characters and spaces only)
    for (int i = 0; newCustomer.name[i] != '\0'; i++) {
        if (!isalpha(newCustomer.name[i]) && newCustomer.name[i] != ' ') {
            printf("Invalid name! Please enter alphabetic characters and spaces only.\n");
            free(newAccount); // Free allocated memory
            return;
        }
    }

    printf("Enter customer address: ");
    scanf(" %[^\n]", newCustomer.address);

    printf("Enter customer contact number: ");
    scanf("%s", newCustomer.contact);

    // Validate contact number (must be numeric with 10 digits)
    if (strlen(newCustomer.contact) != 10) {
        printf("Invalid contact number! Please enter exactly 10 digits.\n");
        free(newAccount); // Free allocated memory
        return;
    }
    for (int i = 0; i < 10; ++i) {
        if (!isdigit(newCustomer.contact[i])) {
            printf("Invalid contact number! Please enter numeric digits only.\n");
            free(newAccount); // Free allocated memory
            return;
        }
    }

    // Set up PIN
    printf("Set up PIN (4 digits): ");
    scanf("%d", &newAccount->pin);

    // Validate PIN (exactly 4 digits)
    if (newAccount->pin < 1000 || newAccount->pin > 9999) {
        printf("Invalid PIN! Please enter a 4-digit PIN.\n");
        free(newAccount); // Free allocated memory
        return;
    }

    // Generate a unique account number
    newAccount->accountNumber = 1000 + numAccounts;

    // Set initial balance to 0
    newAccount->balance = 0;

    // Set account type (for simplicity, we'll assume all accounts are savings accounts)
    strcpy(newAccount->type, "Savings");

    // Store customer information
    newAccount->customer = newCustomer;

    // Add account to the BST
    insertAccount(&root, newAccount);

    ++numAccounts;
    printf("Account created successfully. Account number: %d\n", newAccount->accountNumber);
    
}
