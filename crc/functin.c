#include "header.h"

void deposit() {
    int accountNumber, enteredPIN;
    float amount;

    printf("Enter account number: ");
    scanf("%d", &accountNumber);

    struct Account* account = searchAccount(root, accountNumber);
    if (account == NULL) {
        printf("Account not found.\n");
        return;
    }

    // Verify PIN
    printf("Enter PIN: ");
    scanf("%d", &enteredPIN);

    if (enteredPIN != account->pin) {
        printf("Incorrect PIN. Deposit failed.\n");
        return;
    }

    printf("Enter deposit amount: ");
    scanf("%f", &amount);

    if (amount <= 0) {
        printf("Invalid deposit amount. Amount must be positive.\n");
        return;
    }

    account->balance += amount;

    
    struct Transaction newTransaction;
    newTransaction.transactionID = 1000 + numTransactions;
    newTransaction.accountNumber = accountNumber;
    strcpy(newTransaction.type, "Deposit");
    newTransaction.amount = amount;
    newTransaction.timestamp = time(NULL); 
    transactions[numTransactions++] = newTransaction;

    printf("Deposit successful. New balance: %.2f\n", account->balance);
}
void checkBalance() {
    int accountNumber;
    int pin;

    printf("Enter account number: ");
    scanf("%d", &accountNumber);

    struct Account* account = searchAccount(root, accountNumber);
    if (account == NULL) {
        printf("Account not found.\n");
        return;
    }

    printf("Enter PIN: ");
    scanf("%d", &pin);

    
    if (pin != account->pin) {
        printf("Incorrect PIN. Unable to check balance.\n");
        return;
    }

    printf("Account balance: %.2f\n", account->balance);
}
void transactionHistory() {
    int accountNumber;
    int pin;

    printf("Enter account number: ");
    scanf("%d", &accountNumber);

    struct Account* account = searchAccount(root, accountNumber);
    if (account == NULL) {
        printf("Account not found.\n");
        return;
    }

    printf("Enter PIN: ");
    scanf("%d", &pin);

    // Verify PIN
    if (pin != account->pin) {
        printf("Incorrect PIN. Unable to show transaction history.\n");
        return;
    }

    printf("Transaction History for Account %d:\n", accountNumber);
    printf("Transaction ID\tAccount Number\tType\tAmount\tTimestamp\n");
    for (int i = numTransactions - 1; i >= 0; i--) {
        if (transactions[i].accountNumber == accountNumber) {
            printf("%d\t%d\t%s\t%.2f\t%s", transactions[i].transactionID, transactions[i].accountNumber,
                   transactions[i].type, transactions[i].amount, ctime(&transactions[i].timestamp));
        }
    }
}
void closeAccount() {
    int accountNumber, pin;
    char name[50], address[100];

    printf("Enter account number: ");
    scanf("%d", &accountNumber);

    struct Account* account = searchAccount(root, accountNumber);
    if (account == NULL) {
        printf("Account not found.\n");
        return;
    }

    printf("Enter customer name: ");
    scanf(" %[^\n]", name);

    printf("Enter customer address: ");
    scanf(" %[^\n]", address);

    
    if (strcmp(account->customer.name, name) != 0 || strcmp(account->customer.address, address) != 0) {
        printf("Invalid customer information. Account closure failed.\n");
        return;
    }

    printf("Enter PIN: ");
    scanf("%d", &pin);


    if (pin != account->pin) {
        printf("Incorrect PIN. Unable to close account.\n");
        return;
    }

    
    account->accountNumber = -1; 

    printf("Account closed successfully.\n");
}

void withdraw() {
    int accountNumber, enteredPIN;
    float amount;

    printf("Enter account number: ");
    scanf("%d", &accountNumber);

    struct Account* account = searchAccount(root, accountNumber); 
    if (account == NULL) {
        printf("Account not found.\n");
        return;
    }

    // Verify PIN
    printf("Enter PIN: ");
    scanf("%d", &enteredPIN);

    if (enteredPIN != account->pin) {
        printf("Incorrect PIN. Withdrawal failed.\n");
        return;
    }

    printf("Enter withdrawal amount: ");
    scanf("%f", &amount);

    if (amount <= 0 || amount > account->balance) {
        printf("Invalid withdrawal amount. Amount must be positive and less than or equal to account balance.\n");
        return;
    }

    account->balance -= amount;

    
    struct Transaction newTransaction;
    newTransaction.transactionID = 1000 + numTransactions;
    newTransaction.accountNumber = accountNumber;
    strcpy(newTransaction.type, "Withdrawal");
    newTransaction.amount = amount;
    newTransaction.timestamp = time(NULL); // Current time
    transactions[numTransactions++] = newTransaction;

    printf("Withdrawal successful. New balance: %.2f\n", account->balance);
}
