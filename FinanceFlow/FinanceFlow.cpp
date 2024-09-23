#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

struct Transaction {
    string date;
    string category;
    double amount;
};

// Function to add a transaction (income or expense)
void addTransaction() {
    Transaction t;
    cout << "Enter date (YYYY-MM-DD): ";
    cin >> t.date;
    cout << "Enter category: ";
    cin >> t.category;
    cout << "Enter amount (positive for income, negative for expense): ";
    cin >> t.amount;

    // Append the transaction to the file
    ofstream file("transactions.txt", ios::app);
    if (file.is_open()) {
        file << t.date << "," << t.category << "," << t.amount << endl;
        file.close();
        cout << "Transaction added successfully!\n";
    }
    else {
        cout << "Unable to open file.\n";
    }
}

// Function to view all transactions and return them as a vector
vector<Transaction> viewTransactions(bool showIndex = false) {
    ifstream file("transactions.txt");
    string line;
    vector<Transaction> transactions;

    cout << "\nDate       | Category     | Amount\n";
    cout << "-----------------------------------\n";

    if (file.is_open()) {
        int index = 1;
        while (getline(file, line)) {
            stringstream ss(line);
            Transaction t;
            string amountStr;
            getline(ss, t.date, ',');
            getline(ss, t.category, ',');
            getline(ss, amountStr, ',');
            t.amount = stod(amountStr);

            transactions.push_back(t);
            if (showIndex) {
                cout << index++ << ". " << t.date << " | " << t.category << " | " << t.amount << endl;
            }
            else {
                cout << t.date << " | " << t.category << " | " << t.amount << endl;
            }
        }
        file.close();
    }
    else {
        cout << "Unable to open file.\n";
    }

    return transactions;
}

// Function to delete a transaction by its index
void deleteTransaction() {
    vector<Transaction> transactions = viewTransactions(true); // Show transactions with index
    int deleteIndex;
    cout << "\nEnter the number of the transaction to delete (or 0 to cancel): ";
    cin >> deleteIndex;

    if (deleteIndex == 0) {
        cout << "No transaction deleted.\n";
        return;
    }

    if (deleteIndex < 1 || deleteIndex > transactions.size()) {
        cout << "Invalid selection!\n";
        return;
    }

    // Remove the selected transaction
    transactions.erase(transactions.begin() + deleteIndex - 1);

    // Rewrite the file with remaining transactions
    ofstream file("transactions.txt");
    if (file.is_open()) {
        for (const auto& t : transactions) {
            file << t.date << "," << t.category << "," << t.amount << endl;
        }
        file.close();
        cout << "Transaction deleted successfully!\n";
    }
    else {
        cout << "Unable to open file.\n";
    }
}

int main() {
    int choice;

    do {
        // Display menu
        cout << "\n====== FinanceFlow ======\n";
        cout << "1. Add Transaction\n";
        cout << "2. View Transactions\n";
        cout << "3. Delete Transaction\n";
        cout << "4. Exit\n";
        cout << "=========================\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            addTransaction();  // Add new transaction
            break;
        case 2:
            viewTransactions(); // View all transactions
            break;
        case 3:
            deleteTransaction(); // Delete a specific transaction
            break;
        case 4:
            cout << "Exiting the program. Goodbye!\n";
            break;
        default:
            cout << "Invalid choice, please try again.\n";
            break;
        }
    } while (choice != 4);

    return 0;
}