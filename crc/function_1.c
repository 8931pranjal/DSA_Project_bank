void resetPIN() {
    int accountNumber, enteredPIN, newPIN;
    char name[50], address[100], contact[15];

    
    printf("Enter your account number: ");
    scanf("%d", &accountNumber);

    
    struct Account* account = searchAccount(root, accountNumber);
    if (account == NULL) {
        printf("Account not found.\n");
        return;
    }

    
    printf("Enter your name: ");
    scanf(" %[^\n]", name);

    
    if (strcmp(account->customer.name, name) != 0) {
        printf("Name does not match. Reset failed.\n");
        return;
    }

    
    printf("Enter your address: ");
    scanf(" %[^\n]", address);

    
    if (strcmp(account->customer.address, address) != 0) {
        printf("Address does not match. Reset failed.\n");
        return;
    }

    
    printf("Enter your contact number: ");
    scanf("%s", contact);

    
    if (strcmp(account->customer.contact, contact) != 0) {
        printf("Contact number does not match. Reset failed.\n");
        return;
    }

    
    printf("Enter your current PIN: ");
    scanf("%d", &enteredPIN);

    
    if (enteredPIN != account->pin) {
        printf("Incorrect PIN. Reset failed.\n");
        return;
    }

    // Input new PIN
    printf("Enter your new PIN: ");
    scanf("%d", &newPIN);

    // Update PIN
    account->pin = newPIN;

    printf("PIN reset successful.\n");
}
bool isNumeric(const char* str) {
    while (*str) {
        if (!isdigit(*str)) {
            return false;
        }
        str++;
    }
    return true;
}
void resetContactNumber() {
    int accountNumber, enteredPIN;
    char newContact[15];

    printf("Enter account number: ");
    scanf("%d", &accountNumber);

    struct Account* account = searchAccount(root, accountNumber);
    if (account == NULL) {
        printf("Account not found.\n");
        return;
    }

    
    printf("Enter PIN: ");
    scanf("%d", &enteredPIN);

    if (enteredPIN != account->pin) {
        printf("Incorrect PIN. Unable to reset contact number.\n");
        return;
    }

    
    printf("Enter new contact number (exactly 10 digits): ");
    scanf("%s", newContact);

    
    if (strlen(newContact) != 10 || !isNumeric(newContact)) {
        printf("Invalid contact number! Please enter exactly 10 digits.\n");
        return;
    }


    strcpy(account->customer.contact, newContact);

    printf("Contact number updated successfully.\n");
}
void undoLastTransaction() {
    if (numTransactions == 0) {
        printf("No transactions to undo.\n");
        return;
    }

    
    struct Transaction lastTransaction = transactions[numTransactions - 1];

    
    struct Account* account = searchAccount(root, lastTransaction.accountNumber);
    
    if (account == NULL) {
        printf("Associated account not found.\n");
        return;
    }

    
    if (strcmp(lastTransaction.type, "Deposit") == 0) {
        account->balance -= lastTransaction.amount;
    } else if (strcmp(lastTransaction.type, "Withdrawal") == 0) {
        account->balance += lastTransaction.amount;
    }

    
    numTransactions--;

    printf("Last transaction undone successfully.\n");
}
void approveLoan() {
    int accountNumber, enteredPIN;
    float loanAmount;

    printf("Enter account number: ");
    scanf("%d", &accountNumber);

    struct Account* account = searchAccount(root, accountNumber);
    if (account == NULL) {
        printf("Account not found.\n");
        return;
    }


    printf("Enter PIN: ");
    scanf("%d", &enteredPIN);

    if (enteredPIN != account->pin) {
        printf("Incorrect PIN. Unable to approve loan.\n");
        return;
    }

    
    if (account->balance < 0) {
        printf("Account balance is negative. Unable to approve loan.\n");
        return;
    }

    
    printf("Enter loan amount: ");
    scanf("%f", &loanAmount);

    
    if (loanAmount <= 0) {
        printf("Invalid loan amount. Loan amount must be positive.\n");
        return;
    }


    account->balance += loanAmount;

    printf("Loan approved. New balance: %.2f\n", account->balance);
}
void transfer() {
    int senderAccountNumber, receiverAccountNumber, enteredPIN;
    float amount;

    printf("Enter sender account number: ");
    scanf("%d", &senderAccountNumber);

    struct Account* senderAccount = searchAccount(root, senderAccountNumber);
    if (senderAccount == NULL) {
        printf("Sender account not found.\n");
        return;
    }

    // Verify sender's PIN
    printf("Enter sender's PIN: ");
    scanf("%d", &enteredPIN);

    if (enteredPIN != senderAccount->pin) {
        printf("Incorrect PIN for sender account. Transfer failed.\n");
        return;
    }

    printf("Enter receiver account number: ");
    scanf("%d", &receiverAccountNumber);

    struct Account* receiverAccount = searchAccount(root, receiverAccountNumber);
    if (receiverAccount == NULL) {
        printf("Receiver account not found.\n");
        return;
    }

    printf("Enter transfer amount: ");
    scanf("%f", &amount);

    if (amount <= 0 || amount > senderAccount->balance) {
        printf("Invalid transfer amount. Amount must be positive and less than or equal to sender's balance.\n");
        return;
    }

    // Perform transfer
    senderAccount->balance -= amount;
    receiverAccount->balance += amount;

    // Record transactions
    struct Transaction senderTransaction;
    senderTransaction.transactionID = 1000 + numTransactions;
    senderTransaction.accountNumber = senderAccountNumber;
    strcpy(senderTransaction.type, "Transfer (Sent)");
    senderTransaction.amount = amount;
    senderTransaction.timestamp = time(NULL);
    transactions[numTransactions++] = senderTransaction;

    struct Transaction receiverTransaction;
    receiverTransaction.transactionID = 1000 + numTransactions;
    receiverTransaction.accountNumber = receiverAccountNumber;
    strcpy(receiverTransaction.type, "Transfer (Received)");
    receiverTransaction.amount = amount;
    receiverTransaction.timestamp = time(NULL);
    transactions[numTransactions++] = receiverTransaction;

    printf("Transfer successful. New balance for sender: %.2f, New balance for receiver: %.2f\n", senderAccount->balance, receiverAccount->balance);
}
