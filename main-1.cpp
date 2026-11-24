#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

// Displays the banking menu.
void displayMenu()
{
    cout << "\n========== GCC BANK ==========" << endl;
    cout << "1. Deposit" << endl;
    cout << "2. Withdraw" << endl;
    cout << "3. Send Cash" << endl;
    cout << "4. Check Balance" << endl;
    cout << "5. Exit" << endl;
    cout << "Enter your choice: ";
}

// Finds a user by account number. Returns the user's array position or -1.
int findUser(int accountNumber, int accountNumbers[], int size)
{
    for (int i = 0; i < size; i++)
    {
        if (accountNumbers[i] == accountNumber)
        {
            return i;
        }
    }
    return -1;
}

// Allows a user to log in with an account number and PIN.
int login(int accountNumbers[], int pins[], int size)
{
    int accountNumber, enteredPin;

    cout << "========== GCC BANK LOGIN ==========" << endl;
    cout << "Enter account number: ";
    if (!(cin >> accountNumber))
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid account number. Please enter numbers only." << endl;
        return -1;
    }

    cout << "Enter PIN: ";
    if (!(cin >> enteredPin))
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid PIN. Please enter numbers only." << endl;
        return -1;
    }

    int userIndex = findUser(accountNumber, accountNumbers, size);

    if (userIndex == -1)
    {
        cout << "Account number not found." << endl;
        return -1;
    }

    if (pins[userIndex] != enteredPin)
    {
        cout << "Incorrect PIN. Access denied." << endl;
        return -1;
    }

    cout << "Login successful. Welcome to GCC Bank!" << endl;
    return userIndex;
}

// Deposits money into the selected user's account.
void deposit(int userIndex, double balances[])
{
    double amount;
    cout << "Enter amount to deposit: R";

    if (!(cin >> amount))
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid amount. Please enter a number." << endl;
    }
    else if (amount <= 0)
    {
        cout << "Deposit amount must be greater than zero." << endl;
    }
    else
    {
        balances[userIndex] = balances[userIndex] + amount;
        cout << fixed << setprecision(2);
        cout << "Deposit successful. New balance: R" << balances[userIndex] << endl;
    }
}

// Withdraws money if the amount is valid and the balance is sufficient.
void withdraw(int userIndex, double balances[])
{
    double amount;
    cout << "Enter amount to withdraw: R";

    if (!(cin >> amount))
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid amount. Please enter a number." << endl;
    }
    else if (amount <= 0)
    {
        cout << "Withdrawal amount must be greater than zero." << endl;
    }
    else if (amount > balances[userIndex])
    {
        cout << "Insufficient funds. You cannot withdraw more than your balance." << endl;
    }
    else
    {
        balances[userIndex] = balances[userIndex] - amount;
        cout << fixed << setprecision(2);
        cout << "Withdrawal successful. New balance: R" << balances[userIndex] << endl;
    }
}

// Transfers money to another registered account.
void sendCash(int senderIndex, int accountNumbers[], double balances[], int size)
{
    int recipientAccount;
    double amount;

    cout << "Enter recipient account number: ";
    if (!(cin >> recipientAccount))
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid account number. Please enter numbers only." << endl;
        return;
    }

    int recipientIndex = findUser(recipientAccount, accountNumbers, size);

    if (recipientIndex == -1)
    {
        cout << "Recipient account does not exist." << endl;
        return;
    }

    if (recipientIndex == senderIndex)
    {
        cout << "You cannot send cash to your own account." << endl;
        return;
    }

    cout << "Enter amount to send: R";
    if (!(cin >> amount))
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid amount. Please enter a number." << endl;
    }
    else if (amount <= 0)
    {
        cout << "Transfer amount must be greater than zero." << endl;
    }
    else if (amount > balances[senderIndex])
    {
        cout << "Insufficient funds. Transfer cannot be completed." << endl;
    }
    else
    {
        balances[senderIndex] = balances[senderIndex] - amount;
        balances[recipientIndex] = balances[recipientIndex] + amount;
        cout << fixed << setprecision(2);
        cout << "Cash sent successfully." << endl;
        cout << "Your new balance: R" << balances[senderIndex] << endl;
    }
}

// Displays the selected user's account details and balance.
void checkBalance(int userIndex, string names[], int accountNumbers[], double balances[])
{
    cout << "\n========== ACCOUNT DETAILS ==========" << endl;
    cout << "Account holder: " << names[userIndex] << endl;
    cout << "Account number: " << accountNumbers[userIndex] << endl;
    cout << fixed << setprecision(2);
    cout << "Available balance: R" << balances[userIndex] << endl;
}

int main()
{
    const int SIZE = 3;

    // Parallel arrays store the details of the three bank users.
    string names[SIZE] = {"Kabelo", "Zanele", "Sipho"};
    int accountNumbers[SIZE] = {1001, 1002, 1003};
    int pins[SIZE] = {1234, 2345, 3456};
    double balances[SIZE] = {3500.00, 4000.00, 2000.00};

    int userIndex = login(accountNumbers, pins, SIZE);

    if (userIndex == -1)
    {
        cout << "Please restart the program and try logging in again." << endl;
        return 0;
    }

    int choice;
    do
    {
        displayMenu();

        if (!(cin >> choice))
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Please enter a menu number from 1 to 5." << endl;
            choice = 0;
        }
        else
        {
            switch (choice)
            {
                case 1:
                    deposit(userIndex, balances);
                    break;
                case 2:
                    withdraw(userIndex, balances);
                    break;
                case 3:
                    sendCash(userIndex, accountNumbers, balances, SIZE);
                    break;
                case 4:
                    checkBalance(userIndex, names, accountNumbers, balances);
                    break;
                case 5:
                    cout << "Thank you for banking with GCC Bank. Goodbye!" << endl;
                    break;
                default:
                    cout << "Invalid menu choice. Please select a number from 1 to 5." << endl;
            }
        }
    }
    while (choice != 5);

    return 0;
}
