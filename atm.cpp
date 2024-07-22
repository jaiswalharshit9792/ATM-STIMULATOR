#include <iostream>
#include <string>
#include <vector>
#include <ctime>

using namespace std;

struct Account {
    string accountNumber;
    string pin;
    double balance;
    vector<string> transactionHistory;
};

bool validatePin(const string& pin, const string& enteredPin) {
    return pin == enteredPin;
}

// Function to check account balance
void checkBalance(const Account& account) {
    cout << "Account Balance: $" << account.balance << endl;
}

void withdrawFunds(Account& account, double amount) {
    if (amount > account.balance) {
        cout << "Insufficient funds!" << endl;
    } else {
        account.balance -= amount;
        account.transactionHistory.push_back("Withdrawal: -$" + to_string(amount));
        cout << "Withdrawal successful!" << endl;
    }
}
void depositFunds(Account& account, double amount) {
    account.balance += amount;
    account.transactionHistory.push_back("Deposit: +$" + to_string(amount));
    cout << "Deposit successful!" << endl;
}
void transferFunds(Account& sender, Account& receiver, double amount) {
    if (amount > sender.balance) {
        cout << "Insufficient funds!" << endl;
    } else {
        sender.balance -= amount;
        receiver.balance += amount;
        sender.transactionHistory.push_back("Transfer: -$" + to_string(amount) + " to " + receiver.accountNumber);
        receiver.transactionHistory.push_back("Transfer: +$" + to_string(amount) + " from " + sender.accountNumber);
        cout << "Transfer successful!" << endl;
    }
}
void displayTransactionHistory(const Account& account) {
    cout << "Transaction History:" << endl;
    for (const string& transaction : account.transactionHistory) {
        cout << transaction << endl;
    }
}

int main() {
    
    Account accounts[] = {
        {"9792058291", "9792", 10000.0, {}},
        {"9670341482", "9670", 115020.0, {}}
    };
    int numAccounts = sizeof(accounts) / sizeof(Account);

    
    int currentAccountIndex = -1;

    
    while (true) {
       
        cout << "Enter account number: ";
        string accountNumber;
        cin >> accountNumber;
        cout << "Enter PIN: ";
        string pin;
        cin >> pin;

       
        bool isValid = false;
        for (int i = 0; i < numAccounts; i++) {
            if (accounts[i].accountNumber == accountNumber && validatePin(accounts[i].pin, pin)) {
                currentAccountIndex = i;
                isValid = true;
                break;
            }
        }

        if (!isValid) {
            cout << "Invalid account number or PIN!" << endl;
            continue;
        }

       
        while (true) {
            cout << "Main Menu:" << endl;
            cout << "1. Check Balance" << endl;
            cout << "2. Withdraw Funds" << endl;
            cout << "3. Deposit Funds" << endl;
            cout << "4. Transfer Funds" << endl;
            cout << "5. Transaction History" << endl;
            cout << "6. Logout" << endl;
            cout << "Enter choice: ";
            int choice;
            cin >> choice;

            switch (choice) {
                case 1:
                    checkBalance(accounts[currentAccountIndex]);
                    break;
                case 2: {
                    cout << "Enter amount to withdraw: ";
                    double amount;
                    cin >> amount;
                    withdrawFunds(accounts[currentAccountIndex], amount);
                    break;
                }
                case 3: {
                    cout << "Enter amount to deposit: ";
                    double amount;
                    cin >> amount;
                    depositFunds(accounts[currentAccountIndex], amount);
                    break;
                }
                case 4: {
                    cout << "Enter recipient account number: ";
                    string recipientAccountNumber;
                    cin >> recipientAccountNumber;
                    cout << "Enter amount to transfer: ";
                    double amount;
                    cin >> amount;

                    int recipientAccountIndex = -1;
                    for (int i = 0; i < numAccounts; i++) {
                        if (accounts[i].accountNumber == recipientAccountNumber) {
                            recipientAccountIndex = i;
                            break;
                        }
                    }

                    if (recipientAccountIndex == -1) {
                        cout << "Recipient account not found!" << endl;
                    } else {
                        transferFunds(accounts[currentAccountIndex], accounts[recipientAccountIndex], amount);
                    }
                    break;
                }
            }
        }
    }           
}               