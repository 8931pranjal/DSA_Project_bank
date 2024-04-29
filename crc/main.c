#include "header.h"

int main() {
    loadAccountDataFromCSV();
    loadTransactionHistoryFromCSV();
    int choice;
    do {
        printf("\nBanking Management System\n");
        printf("1. Create Account\n");
        printf("2. Deposit\n");
        
        printf("3. checkBalance\n");
        printf("4. transactionHistory\n");
        printf("5. withdraw\n");
        printf("6. closeAccount\n");
        printf("7. resetPIN\n");
        printf("8. resetContactNumber\n");
        printf("9. undoLastTransaction\n");
        printf("10. approveLoan\n ");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                createAccount();
                break;
            case 2:
                deposit();
                break;
            case 3:
                checkBalance();
                break;
            case 4:
                transactionHistory();
                break;
            case 5:
                withdraw();
                break;
            case 6:
                closeAccount();
                break;
            case 7:
                resetPIN();
                break;
            case 8:
                resetContactNumber();
                break;
            case 9:
                undoLastTransaction();
                break;
            case 10:
                approveLoan();
                break;
            case 11:
                transfer();
                break;
            case 0:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice!\n");
        }
    } while(choice != 0);
    saveAccountDataToCSV();
    saveTransactionHistoryToCSV();
    return 0;
}
