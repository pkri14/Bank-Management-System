#include <iostream>
#include <vector>
#include <string>
#include <limits>

class Account
{
public:
  Account(int id, std::string name, double balance)
      : id(id), name(name), balance(balance) {}

  int getId() const { return id; }
  std::string getName() const { return name; }
  double getBalance() const { return balance; }

  void deposit(double amount)
  {
    if (amount > 0)
    {
      balance += amount;
      std::cout << "Deposited $" << amount << ". New balance: $" << balance << "\n";
    }
    else
    {
      std::cout << "Invalid deposit amount.\n";
    }
  }

  void withdraw(double amount)
  {
    if (amount > 0 && amount <= balance)
    {
      balance -= amount;
      std::cout << "Withdrew $" << amount << ". New balance: $" << balance << "\n";
    }
    else
    {
      std::cout << "Invalid withdrawal amount.\n";
    }
  }

private:
  int id;
  std::string name;
  double balance;
};

class Bank
{
public:
  void createAccount(const std::string &name, double initialBalance)
  {
    int id = accounts.size() + 1;
    accounts.emplace_back(id, name, initialBalance);
    std::cout << "Account created successfully. Account ID: " << id << "\n";
  }

  void deposit(int id, double amount)
  {
    Account *account = findAccount(id);
    if (account)
    {
      account->deposit(amount);
    }
    else
    {
      std::cout << "Account not found.\n";
    }
  }

  void withdraw(int id, double amount)
  {
    Account *account = findAccount(id);
    if (account)
    {
      account->withdraw(amount);
    }
    else
    {
      std::cout << "Account not found.\n";
    }
  }

  void checkBalance(int id) const
  {
    const Account *account = findAccount(id);
    if (account)
    {
      std::cout << "Account balance for " << account->getName() << ": $" << account->getBalance() << "\n";
    }
    else
    {
      std::cout << "Account not found.\n";
    }
  }

private:
  std::vector<Account> accounts;

  Account *findAccount(int id)
  {
    for (auto &account : accounts)
    {
      if (account.getId() == id)
      {
        return &account;
      }
    }
    return nullptr;
  }

  const Account *findAccount(int id) const
  {
    for (const auto &account : accounts)
    {
      if (account.getId() == id)
      {
        return &account;
      }
    }
    return nullptr;
  }
};

void showMenu()
{
  std::cout << "\nBank Account Management System\n";
  std::cout << "1. Create Account\n";
  std::cout << "2. Deposit\n";
  std::cout << "3. Withdraw\n";
  std::cout << "4. Check Balance\n";
  std::cout << "5. Exit\n";
  std::cout << "Enter your choice: ";
}

int main()
{
  Bank bank;
  int choice;

  do
  {
    showMenu();
    std::cin >> choice;

    switch (choice)
    {
    case 1:
    {
      std::string name;
      double initialBalance;
      std::cout << "Enter name: ";
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::getline(std::cin, name);
      std::cout << "Enter initial balance: ";
      std::cin >> initialBalance;
      bank.createAccount(name, initialBalance);
      break;
    }
    case 2:
    {
      int id;
      double amount;
      std::cout << "Enter account ID: ";
      std::cin >> id;
      std::cout << "Enter deposit amount: ";
      std::cin >> amount;
      bank.deposit(id, amount);
      break;
    }
    case 3:
    {
      int id;
      double amount;
      std::cout << "Enter account ID: ";
      std::cin >> id;
      std::cout << "Enter withdrawal amount: ";
      std::cin >> amount;
      bank.withdraw(id, amount);
      break;
    }
    case 4:
    {
      int id;
      std::cout << "Enter account ID: ";
      std::cin >> id;
      bank.checkBalance(id);
      break;
    }
    case 5:
      std::cout << "Exiting...\n";
      break;
    default:
      std::cout << "Invalid choice. Please try again.\n";
    }
  } while (choice != 5);

  return 0;
}
