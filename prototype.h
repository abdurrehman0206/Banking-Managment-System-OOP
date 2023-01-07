#include "class.h"

void nullifier();

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
bool adminLogin();
int mainMenu(Customer *, unsigned int *);
int customerMenu(Customer *, unsigned int *, unsigned int *);
int managementMenu(Customer *, unsigned int *);
int arrowSelection(int);