void saveTransactionHistoryToCSV() {
    FILE *fp;
    fp = fopen("transaction_history.csv", "w"); // Open file in write mode

    if (fp == NULL) {
        printf("Error opening file.\n");
        return;
    }

    // Write transaction history to file
    for (int i = 0; i < numTransactions; i++) {
        fprintf(fp, "%d,%d,%s,%.2f,%ld\n", transactions[i].transactionID, transactions[i].accountNumber,
                transactions[i].type, transactions[i].amount, transactions[i].timestamp);
    }

    fclose(fp);
}

// Function to load transaction history from CSV file
void loadTransactionHistoryFromCSV() {
    FILE *fp;
    fp = fopen("transaction_history.csv", "r"); // Open file in read mode

    if (fp == NULL) {
        printf("Error opening file.\n");
        return;
    }

    // Read transaction history from file
    while (!feof(fp)) {
        struct Transaction newTransaction;
        fscanf(fp, "%d,%d,%[^,],%f,%ld\n", &newTransaction.transactionID, &newTransaction.accountNumber,
               newTransaction.type, &newTransaction.amount, &newTransaction.timestamp);

        // Add new transaction to the transactions array
        transactions[numTransactions++] = newTransaction;
    }

    fclose(fp);
}
// Function to load account data from CSV file
// Function to load account data from CSV file
void loadAccountDataFromCSV() {
    FILE *fp;
    char line[256]; // Assuming the maximum length of a line in the CSV file is 256 characters

    fp = fopen("account_data.csv", "r"); // Open file in read mode

    if (fp == NULL) {
        printf("Error opening file.\n");
        return;
    }

    // Read each line from the file
    while (fgets(line, sizeof(line), fp) != NULL) {
        // Tokenize the line based on comma (,) delimiter
        char *token = strtok(line, ",");
        if (token == NULL) {
            printf("Error reading file.\n");
            break;
        }

        // Extract account details from tokens
        struct Account* newAccount = (struct Account*)malloc(sizeof(struct Account));
        newAccount->accountNumber = atoi(token);

        token = strtok(NULL, ",");
        strcpy(newAccount->customer.name, token);

        token = strtok(NULL, ",");
        strcpy(newAccount->customer.address, token);

        token = strtok(NULL, ",");
        strcpy(newAccount->customer.contact, token);

        token = strtok(NULL, ",");
        newAccount->balance = atof(token);

        token = strtok(NULL, ",");
        newAccount->pin = atoi(token);

        // Add new account to the binary search tree
        insertAccount(&root, newAccount);
        numAccounts++;
    }

    fclose(fp);
}
void writeAccountDataToCSV(struct Account* node, FILE *fp) {
    if (node == NULL) {
        return;
    }

    // Write account data to CSV file
    fprintf(fp, "%d,%s,%s,%s,%.2f,%d\n", node->accountNumber, node->customer.name, node->customer.address,
            node->customer.contact, node->balance, node->pin);

    
    writeAccountDataToCSV(node->left, fp);
    writeAccountDataToCSV(node->right, fp);
}



void saveAccountDataToCSV() {
    FILE *fp;

    fp = fopen("account_data.csv", "w"); 

    if (fp == NULL) {
        fprintf(stderr, "Error opening file: %s\n", strerror(errno)); 
        return;
    }

    
    fprintf(fp, "AccountNumber,Name,Address,Contact,Balance,PIN\n");

    writeAccountDataToCSV(root, fp);

    fclose(fp);
}