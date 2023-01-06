#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <conio.h>
#include <windows.h>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>

using namespace std;

struct Account
{
    string firstName;
    string lastName;
    string accType;
    unsigned int accBalance, accId, accLoan;
    unsigned short accPin;
    Account *next = NULL;
    Account *prev = NULL;
    Account() : firstName(""), lastName(""), accType("bronze"), accBalance(0), accId(0), accLoan(0), accPin(1111), next(NULL), prev(NULL){};
    void inputData();
    void outputData() const;
    void outputInfo() const;
    int accTypeChk();
    // void receiveCash(unsigned int tempBalance) { accBalance += tempBalance; }
    // void addLoan(unsigned int tempLoan) { accLoan += tempLoan; }
    void withdrawCash();
    void transferCash();
    void takeLoan();
    void payLoan();
    void changePin();
    void printStatement();
    friend ofstream &operator<<(ofstream &, Account *);
    friend ifstream &operator>>(ifstream &, Account *);
};

class Customer
{
private:
    Account *head;
    Account *tail;
    Account *trav;

public:
    Customer() : head(NULL), tail(NULL), trav(NULL){};
    bool isEmpty() { return head == NULL ? true : false; }
    void addAccountNode(Account *newAcc);
    void deleteAccountNode(unsigned int);
    Account *searchAccountNode(unsigned int);
    void readDatabase(unsigned int *, unsigned int *);
    void updateDatabase(unsigned int *);
    int idChk(unsigned int *, int);
    void addAccount(unsigned int *);
    void modifyAccount(unsigned int *);
    void deleteAccount(unsigned int *);
    bool customerLogin(unsigned int *, Account *);
    void outputDatabase()
    {
        Account *temp = head;
        while (temp != NULL)
        {
            temp->outputInfo();
            temp = temp->next;
        }
    }

    // friend ofstream &operator<<(ofstream &, Customer *);
    // friend ifstream &operator>>(ifstream &, Customer *);
};

Customer *customer = new Customer;
Account *acc = new Account;
unsigned int *id = new unsigned int(0);
unsigned int *accNumChk = new unsigned int(0);
unsigned int *n = new unsigned int(0);
ifstream fin;
ofstream fout;
const string database = "accounts.dat";
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

ofstream &operator<<(ofstream &FOUT, Account *c)
{
    FOUT << c->firstName << " "
         << c->lastName << " "
         << c->accId << " "
         << c->accType << " "
         << c->accBalance << " "
         << c->accLoan << " "
         << c->accPin << " "
         << endl;
    return FOUT;
}
ifstream &operator>>(ifstream &FIN, Account *c)
{
    FIN >> c->firstName;
    FIN >> c->lastName;
    FIN >> c->accId;
    FIN >> c->accType;
    FIN >> c->accBalance;
    FIN >> c->accLoan;
    FIN >> c->accPin;
    return FIN;
}