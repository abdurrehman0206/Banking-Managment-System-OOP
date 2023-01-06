#include "class.h"

// new
// new
void nullifier();
// database
// management
// void addAccount(Customer **, unsigned int *);
// void modifyAccount(Customer *, unsigned int *);
// void deleteAccount(Customer *, unsigned int *);
// void alotCash(Customer *, unsigned int *);
// void alotLoan(Customer *, unsigned int *);
// void outputDatabase(Customer *, unsigned int *);

// Failures
void databaseFailure();
void statementFailure();
void accountFailure();
void fundFailure();
void limitFailure(unsigned int);
void technicalFailure();
void invalidAmountFailure();
void transactionSuccess();
void transactionFailure();

// UI and Misc
string Statement(unsigned int);
void g_xy(int, int);
void line(int);
void color(int);
void loading();
bool customerLogin(Customer *, unsigned int *, Account *);
bool adminLogin();
int mainMenu(Customer *, unsigned int *);
int customerMenu(Customer *, unsigned int *, unsigned int *);
int managementMenu(Customer *, unsigned int *);
int arrowSelection(int);