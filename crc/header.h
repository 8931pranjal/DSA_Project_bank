#ifndef HEADER_H   
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#include <errno.h>

#define MAX_ACCOUNTS 100
#define MAX_TRANSACTIONS 1000
#define HASH_SIZE 1000
// Define structures
struct Customer {
    char name[50];
    char address[100];
    char contact[15];
};

struct Account {
    int accountNumber;
    struct Customer customer;
    char type[20];
    float balance;
    int pin; // PIN for account access
    struct Account* left;
    struct Account* right;
};

struct Transaction {
    int transactionID;
    int accountNumber;
    char type[20]; // "deposit", "withdrawal", or "transfer"
    float amount;
    time_t timestamp;
    
};


// Global variables
struct Account* root = NULL;
int numAccounts = 0;
struct Transaction transactions[MAX_TRANSACTIONS];
int numTransactions = 0;


// Function prototypes
void createAccount();
void deposit();
void checkBalance();
void transactionHistory();
void  closeAccount();
void resetPIN();
void resetContactNumber();
void undoLastTransaction();
void approveLoan();
void transfer();
// Function to search for an account in the BST
struct Account* searchAccount(struct Account* root, int accountNumber);
void withdraw();
void saveAccountDataToCSV();
void loadAccountDataFromCSV();
void saveTransactionHistoryToCSV();
void loadTransactionHistoryFromCSV();

#endif  /
