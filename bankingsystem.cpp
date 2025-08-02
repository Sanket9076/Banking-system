#include <iostream>
#include <vector>
#include <string>
#include <ctime>
using namespace std;

// Transaction class
class Transaction {
public:
    string type;
    double amount;
    string timestamp;

    Transaction(string t, double a) {
        type = t;
        amount = a;
        time_t now = time(0);
        timestamp = ctime(&now);
    }

    void display() {
        cout << type << " of Rs." << amount << " at " << timestamp;
    }
};

// Account class
class Account {
private:
    int accountNumber;
    double balance;
    vector<Transaction> transactions;

public:
    Account(int accNo) {
        accountNumber = accNo;
        balance = 0.0;
    }

    void deposit(double amount) {
        balance += amount;
        transactions.emplace_back("Deposit", amount);
        cout << "Deposit successful.\n";
    }

    void withdraw(double amount) {
        if (amount <= balance) {
            balance -= amount;
            transactions.emplace_back("Withdrawal", amount);
            cout << "Withdrawal successful.\n";
        } else {
            cout << "Insufficient balance!\n";
        }
    }

    void transfer(Account &toAccount, double amount) {
        if (amount <= balance) {
            balance -= amount;
            toAccount.balance += amount;
            transactions.emplace_back("Transfer to Acc " + to_string(toAccount.accountNumber), amount);
            toAccount.transactions.emplace_back("Transfer from Acc " + to_string(accountNumber), amount);
            cout << "Transfer successful.\n";
        } else {
            cout << "Insufficient balance!\n";
        }
    }

    void showBalance() {
        cout << "Account Number: " << accountNumber << "\nBalance: Rs." << balance << endl;
    }

    void showTransactions() {
        cout << "Transaction History for Acc " << accountNumber << ":\n";
        for (auto &t : transactions) {
            t.display();
        }
    }

    int getAccountNumber() {
        return accountNumber;
    }
};

// Customer class
class Customer {
private:
    string name;
    int customerId;
    Account account;

public:
    Customer(string n, int id) : name(n), customerId(id), account(id + 1000) {}

    void displayInfo() {
        cout << "Customer ID: " << customerId << "\nName: " << name << endl;
        account.showBalance();
    }

    Account& getAccount() {
        return account;
    }
};

int main() {
    Customer c1("Sanket", 1);
    Customer c2("Ravi", 2);

    c1.getAccount().deposit(1000);
    c1.getAccount().withdraw(300);
    c1.getAccount().transfer(c2.getAccount(), 200);

    cout << "\n--- Customer Info ---\n";
    c1.displayInfo();
    c2.displayInfo();

    cout << "\n--- Transactions ---\n";
    c1.getAccount().showTransactions();
    c2.getAccount().showTransactions();

    return 0;
}