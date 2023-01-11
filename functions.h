#include "prototype.h"
// 2147483647
void nullifier()
{
    customer = NULL;
    id = NULL;
    accNumChk = NULL;
    n = NULL;
    delete id;
    delete accNumChk;
    delete n;
    delete[] customer;
}
//----------------------------------------------------------------
// Database Functions Start
// ----------------------------------------------------------------
void accSizChk(unsigned int *n = n)
{
    int count = 0;
    string garbage;
    fin.open(database, ios::in);

    if (fin.is_open())
    {
        while (!fin.eof())
        {
            getline(fin, garbage);
            count++;
        }
    }
    else
    {
        databaseFailure();
    }
    fin.close();
    count--;
    *n = count;
}
void Customer::addAccountNode(Account *newAcc)
{
    if (isEmpty())
    {
        head = newAcc;
        tail = newAcc;
    }
    else
    {
        tail->next = newAcc;
        newAcc->prev = tail;
        tail = newAcc;
    }
}
void Customer::deleteAccountNode(unsigned int pos)
{
    if (isEmpty())
    {
        accountFailure();
    }
    else
    {
        trav = head;
        while (trav != NULL)
        {
            if (trav->accId == pos + 1)
            {
                if (trav == head)
                {
                    head = head->next;
                    head->prev = NULL;
                    trav = NULL;
                    delete trav;
                    break;
                }
                else if (trav == tail)
                {
                    tail = tail->prev;
                    tail->next = NULL;
                    trav = NULL;
                    delete trav;
                    break;
                }
                else
                {
                    trav->prev->next = trav->next;
                    trav->next->prev = trav->prev;
                    trav = NULL;
                    delete trav;
                    break;
                }
            }
            else
            {
                trav = trav->next;
            }
        }
    }
}
Account *Customer::searchAccountNode(unsigned int tempId)
{

    if (isEmpty())
    {
        accountFailure();
    }
    else
    {
        trav = head;
        while (trav != NULL)
        {
            if (trav->accId == tempId)
            {
                return trav;
            }
            else
            {
                trav = trav->next;
            }
        }
    }
    return NULL;
}
void Customer ::loadSalary()
{
    int salaryAmt;
    fin.open(salaryDB, ios::in);
    if (fin.is_open())
    {
        while (!fin.eof())
        {
            fin >> salaryAmt;
            salaryQue.push(salaryAmt);
        }
    }
    else
    {
        databaseFailure();
    }
    fin.close();
}
void Customer::readDatabase(unsigned int *n = n, unsigned int *accNumChk = accNumChk)
{

    accSizChk(n);
    Account *fetchedAcc = new Account;
    fin.open(database, ios::in);
    if (fin.is_open())
    {
        head = tail = NULL;
        for (int i = 0; i < *n; i++)
        {
            fin >> fetchedAcc;
            addAccountNode(fetchedAcc);
            fetchedAcc = new Account;
        }
    }
    else
    {
        databaseFailure();
    }
    fin.close();
    *accNumChk = tail->accId + 1;
    delete fetchedAcc;
}
void Customer ::updateDatabase(unsigned int *n = n)
{

    fout.open(database, ios::out | ios::trunc);
    if (fout.is_open())
    {
        trav = head;
        for (trav = head; trav != NULL; trav = trav->next)
        {
            fout << trav;
        }
    }
    else
    {
        databaseFailure();
    }
    fout.close();
    readDatabase();
}
//----------------------------------------------------------------
// Database Functions End
// ----------------------------------------------------------------
//----------------------------------------------------------------
// Management Functions Start
//----------------------------------------------------------------

void Customer::paySalary(unsigned int *n = n)
{
    long int salaryAmt;
    if (salaryQue.empty())
    {
        statementFailure();
    }
    else
    {
        trav = head;
        for (trav = head; trav != NULL; trav = trav->next)
        {
            salaryAmt = salaryQue.front();
            salaryQue.pop();
            trav->accBalance += salaryAmt;
            string statFile = Statement(trav->accId);
            fout.open(statFile, ios::out | ios::app);
            if (fout.is_open())
            {
                fout << "Salary Credited - " << salaryAmt << endl;
            }
            else
            {
                statementFailure();
            }
            fout.close();
        }
        updateDatabase();
        transactionSuccess();
    }
}

void Account::inputData()
{
    cout << "Enter First Name : ";
    getline(cin, firstName);
    cout << "Enter Last Name : ";
    getline(cin, lastName);
    do
    {
        cout << "Enter " << firstName << " " << lastName << "'s Account Type : ";
        getline(cin, accType);
    } while ((stricmp("platinum", (accType).c_str()) != 0) && (stricmp("gold", (accType).c_str()) != 0) && (stricmp("bronze", (accType).c_str()) != 0) && (stricmp("silver", (accType).c_str()) != 0));

    if (accId == 0)
    {
        accId = *accNumChk;
        *accNumChk += 1;
    }
}
void Account::outputData() const
{
    cout << "First Name : " << firstName << endl;
    cout << "Last Name : " << lastName << endl;
    cout << "Account ID : " << accId << endl;
    cout << "Account Type : " << accType << endl;
    cout << "Balance : " << accBalance << endl;
    cout << "Loan : " << accLoan << endl;
}
void Account::outputInfo() const
{
    cout << setw(17) << left << firstName << setw(16) << left << lastName << setw(16) << left << accId << setw(16) << left << accType << setw(16) << left << accBalance << accLoan << endl;
}

void Customer::addAccount(unsigned int *n = n)
{
    Account *newAcc = new Account;
    newAcc->inputData();
    addAccountNode(newAcc);
    updateDatabase(n);
}

void Customer::modifyAccount(unsigned int *n = n)
{
    int tempId;
    cout << "Enter account ID to modify : ";
    cin >> tempId;
    trav = searchAccountNode(tempId);
    if (!trav)
    {
        accountFailure();
    }
    return;
    cin.ignore();
    trav->inputData();
    updateDatabase(n);
}
void Customer::deleteAccount(unsigned int *n = n)
{
    int tempId;
    cout << "Enter account ID to delete : ";
    cin >> tempId;
    trav = searchAccountNode(tempId);
    if (!trav)
    {
        accountFailure();
        return;
    }
    if (!trav)
    {
        accountFailure();
        return;
    }
    if (trav->accBalance != 0)
    {
        color(12);
        cout << "Please withdraw all the cash before deleting!" << endl;
        color(15);
        return;
    }
    if (trav->accLoan != 0)
    {
        color(12);
        cout << "Please pay all the loan before deleting!" << endl;
        color(15);
        return;
    }
    if (trav)
    {
        deleteAccountNode(tempId);
    }
    else
    {
        databaseFailure();
    }
    fout.close();
    updateDatabase(n);
}
void Customer::alotCash(unsigned int *n = n)
{
    unsigned int amount = 0;
    unsigned int tempId = 0;
    cout << "Enter the ID of the account : ";
    cin >> tempId;
    trav = searchAccountNode(tempId);
    if (!trav)
    {
        accountFailure();
        return;
    }
    cout << "ACCOUNT DETAILS" << endl;
    trav->outputInfo();
    cout << endl;
    cout << "Enter amount to alot : ";
    cin >> amount;
    if (amount > 0)
    {
        trav->receiveCash(amount);
        transactionSuccess();
        string statFile = Statement(trav->accId);
        fout.open(statFile, ios::app | ios::out);
        if (fout.is_open())
        {
            fout << "Received +" << amount << " from Bank " << endl;
        }
        else
        {
            statementFailure();
        }
        fout.close();
        updateDatabase();
    }
    else if (amount <= 0)
    {
        invalidAmountFailure();
    }
    else
    {
        technicalFailure();
    }
}
void Customer::alotLoan(unsigned int *n = n)
{
    unsigned int amount = 0;
    unsigned int tempId = 0;
    cout << "Enter the ID of the account : ";
    cin >> tempId;
    trav = searchAccountNode(tempId);
    if (!trav)
    {
        accountFailure();
        return;
    }
    cout << "ACCOUNT DETAILS" << endl;
    trav->outputInfo();
    cout << endl;
    cout << "Enter amount to alot : ";
    cin >> amount;
    if (amount > 0)
    {
        trav->receiveCash(amount);
        trav->addLoan(amount);
        transactionSuccess();
        string statFile = Statement(trav->accId);
        fout.open(statFile, ios::app | ios::out);
        if (fout.is_open())
        {
            fout << "Loan Added +" << amount << endl;
        }
        else
        {
            statementFailure();
        }
        fout.close();
        updateDatabase();
    }
    else if (amount <= 0)
    {
        invalidAmountFailure();
    }
    else
    {
        technicalFailure();
    }
}

//----------------------------------------------------------------
// Management Functions End
//----------------------------------------------------------------

int Account::accTypeChk()
{
    unsigned int maxAmount;
    if ((strcmpi(accType.c_str(), "platinum")) == 0)
    {
        maxAmount = 100000;
    }
    else if ((strcmpi(accType.c_str(), "gold")) == 0)
    {
        maxAmount = 75000;
    }
    else if ((strcmpi(accType.c_str(), "silver")) == 0)
    {
        maxAmount = 50000;
    }
    else if ((strcmpi(accType.c_str(), "bronze")) == 0)
    {
        maxAmount = 25000;
    }
    else
    {
        maxAmount = 0;
    }
    return maxAmount;
}
//----------------------------------------------------------------
// Faliures Start
//----------------------------------------------------------------
void databaseFailure()
{
    color(12);
    cout << endl;
    cout << "Database access failed !" << endl;
    cout << endl;
    color(15);
}
void statementFailure()
{
    color(12);
    cout << endl;
    cout << "Statement InAccessible !" << endl;
    cout << endl;
    color(15);
}
void accountFailure()
{
    color(12);
    cout << endl;
    cout << "The account does not exist ! " << endl;
    cout << endl;
    color(15);
}
void fundFailure()
{
    color(12);
    cout << endl;
    transactionFailure();
    cout << "You do not have enough funds available ! " << endl;
    cout << endl;
    color(15);
}
void limitFailure(unsigned int limit)
{
    color(12);
    cout << endl;
    transactionFailure();
    cout << "Your maximum limit is " << limit << endl;
    cout << endl;
    color(15);
}
void technicalFailure()
{
    color(12);
    cout << endl;
    transactionFailure();
    cout << "Technical Error ! " << endl;
    cout << endl;
    color(15);
}
void invalidAmountFailure()
{
    color(12);
    cout << endl;
    transactionFailure();
    cout << "Invalid Amount ! " << endl;
    cout << endl;
    color(15);
}
void transactionSuccess()
{
    color(10);
    cout << endl;
    cout << "Transaction Successful ! " << endl;
    cout << endl;
    color(15);
}
void transactionFailure()
{
    cout << "Transaction Failed ! " << endl;
}
//----------------------------------------------------------------
// Faliures End
//----------------------------------------------------------------
//----------------------------------------------------------------
// Customer Functions Start
//----------------------------------------------------------------
void Account::withdrawCash()
{
    unsigned int amount = 0;
    unsigned int limit = 0;
    cout << "Enter amount to withdraw : ";
    cin >> amount;
    limit = accTypeChk();
    if (amount <= accBalance && amount > 0 && amount <= limit)
    {
        accBalance -= amount;
        transactionSuccess();
        cout << "Remaining Balance : " << accBalance << endl;
        string statFile = Statement(accId);
        fout.open(statFile, ios::out | ios::app);
        if (fout.is_open())
        {
            fout << "Withdrew -" << amount << endl;
        }
        else
        {
            statementFailure();
        }
        fout.close();
        customer->updateDatabase();
    }
    else if (amount <= 0)
    {
        invalidAmountFailure();
    }
    else if (amount > limit)
    {
        limitFailure(limit);
    }
    else if (amount > accBalance)
    {
        fundFailure();
    }
    else
    {
        technicalFailure();
    }
}
void Account::transferCash()
{
    unsigned int receiverId = 0;
    unsigned int amount = 0;
    unsigned int limit = 0;
    cout << "Enter account ID of the reciever : ";
    cin >> receiverId;
    Account *trav = customer->searchAccountNode(receiverId);
    if (!trav)
    {
        accountFailure();
        return;
    }
    if (trav->accId == accId)
    {
        color(12);
        cout << "You cannot send to yourself !" << endl;
        color(15);
        return;
    }
    cout << "Enter amount to sent to " << trav->firstName << " " << trav->lastName << " : ";
    cin >> amount;
    limit = accTypeChk();
    if (amount <= accBalance && amount > 0 && amount <= limit)
    {

        transactionSuccess();
        cout << "Sent " << amount << " to " << trav->firstName << " " << trav->lastName << " " << trav->accId << endl;
        accBalance -= amount;
        trav->receiveCash(amount);
        cout << "Remaining Balance : " << accBalance << endl;
        customer->updateDatabase();
        string statFile = Statement(accId);
        fout.open(statFile, ios::app | ios::out);
        if (fout.is_open())
        {
            fout << "Sent - " << amount << " to " << trav->firstName << " " << trav->lastName << " " << trav->accId << endl;
        }
        else
        {
            statementFailure();
        }
        fout.close();
        statFile = Statement(trav->accId);
        fout.open(statFile, ios::app | ios::out);
        if (fout.is_open())
        {
            fout << "Received + " << amount << " from " << firstName << " " << lastName << " " << accId << endl;
        }
        else
        {
            statementFailure();
        }
        fout.close();
    }
    else if (amount <= 0)
    {
        invalidAmountFailure();
    }
    else if (amount > limit)
    {
        limitFailure(limit);
    }
    else if (amount > accBalance)
    {
        fundFailure();
    }
    else
    {
        technicalFailure();
    }
}
void Account::takeLoan()
{
    unsigned int amount = 0;
    unsigned int limit = 0;
    cout << "Enter amount to take loan : ";
    cin >> amount;
    limit = accTypeChk();
    if (amount > 0 && amount <= limit)
    {
        accBalance += amount;
        accLoan += amount;
        transactionSuccess();
        cout << "You recieved a loan of " << amount << endl;
        cout << "Remaining Balance : " << accBalance << endl;
        cout << "Account Loan : " << accLoan << endl;
        string statFile = Statement(accId);
        fout.open(statFile, ios::out | ios::app);
        if (fout.is_open())
        {
            fout << "Loan Added + " << amount << endl;
        }
        else
        {
            statementFailure();
        }
        fout.close();
        customer->updateDatabase();
    }
    else if (amount <= 0)
    {
        invalidAmountFailure();
    }
    else if (amount > limit)
    {
        limitFailure(limit);
    }
    else
    {
        technicalFailure();
    }
}
void Account::payLoan()
{
    unsigned int amount = 0;
    cout << "Enter amount to pay back : ";
    cin >> amount;
    if (amount > 0 && amount <= accLoan && amount <= accBalance)
    {
        accBalance -= amount;
        accLoan -= amount;
        transactionSuccess();
        cout << "You payed back " << amount << endl;
        cout << "Remaining Balance : " << accBalance << endl;
        cout << "Account Loan : " << accLoan << endl;
        string statFile = Statement(accId);
        fout.open(statFile, ios::out | ios::app);
        if (fout.is_open())
        {
            fout << "Loan Payed - " << amount << endl;
        }
        else
        {
            statementFailure();
        }
        fout.close();
        customer->updateDatabase();
    }
    else if (amount <= 0)
    {
        invalidAmountFailure();
    }
    else if (amount > accLoan)
    {
        color(12);
        cout << "You are trying to pay back more then than you owe !" << endl;
        color(15);
    }
    else if (amount > accBalance)
    {
        fundFailure();
    }
    else
    {
        technicalFailure();
    }
}
void Account::changePin()
{
    unsigned int tempPin = 0;
    unsigned int tempPin2 = 0;
    cout << "Enter last pin : ";
    cin >> tempPin;
    if (tempPin == accPin)
    {
        cout << "Enter new pin : ";
        cin >> tempPin;
        cout << "Enter new pin again : ";
        cin >> tempPin2;
        if (tempPin == tempPin2)
        {
            color(10);
            cout << "Pin changed successfully !" << endl;
            accPin = tempPin;
            customer->updateDatabase();
        }
        else
        {
            color(12);
            cout << "Pin change failed !" << endl;
        }
    }
    else
    {
        color(12);
        cout << "Invalid Pin !" << endl;
    }
    color(15);
}
void Account::printStatement()
{
    string statFile = "";
    string line = "";
    statFile = Statement(accId);
    fin.open(statFile, ios::in);
    if (fin.is_open())
    {
        while (!fin.eof())
        {
            getline(fin, line);
            cout << line << endl;
        }
    }
    else
    {
        statementFailure();
    }
    fin.close();
}
//----------------------------------------------------------------
// Customer Functions End
//----------------------------------------------------------------
//----------------------------------------------------------------
// UI and Misc Start
//----------------------------------------------------------------
void color(int n)
{
    SetConsoleTextAttribute(console, n);
}
void g_xy(int x, int y)
{
    COORD cp;
    cp.X = x;
    cp.Y = y;
    SetConsoleCursorPosition(console, cp);
}
void line(int num)
{
    for (int i = 0; i <= num; i++)
    {
        cout << "=";
    }
    cout << endl;
}
void loading()
{
    cin.sync();
    for (int i = 0; i < 5; i++)
    {
        g_xy(58 + i, 25);
        cout << "*";
        Sleep(300);
    }
    cin.sync();
}
string Statement(unsigned int id)
{
    string statFile = "statement-";
    statFile = statFile.append(to_string(id));
    statFile += ".txt";
    return statFile;
}

bool Customer::customerLogin(unsigned int *n = n)
{
    cin.sync();
    string pass;
    char ch;
    int tempId = 0;
    g_xy(42, 13);
    cout << "ID" << endl;
    g_xy(48, 12);
    line(23);
    g_xy(48, 13);
    cout << setw(23) << left << "|"
         << "|" << endl;
    g_xy(48, 14);
    line(23);
    g_xy(42, 16);
    cout << "PIN" << endl;
    g_xy(48, 15);
    line(23);
    g_xy(48, 16);
    cout << setw(23) << left << "|"
         << "|" << endl;
    g_xy(48, 17);
    line(23);
    g_xy(58, 13);
    cin >> tempId;
    acc = searchAccountNode(tempId);
    if (!acc)
    {
        color(12);
        g_xy(49, 21);
        cout << "Account Does Not Exist" << endl;
        g_xy(55, 23);
        cout << "Going Back" << endl;
        loading();
        color(15);
        return false;
    }
    g_xy(58, 16);
    int saveX = 58;
    while (true)
    {
        ch = getch();
        if (ch == 13)
        {
            break;
        }
        else if (ch == '\b')
        {

            if (!pass.empty())
            {
                pass.pop_back();
                g_xy(--saveX, 16);
                cout << " ";
            }
        }
        else
        {
            pass.push_back(ch);
            g_xy(saveX++, 16);
            cout << "*";
        }
    }

    int intPass = 0;
    try
    {
        intPass = stoi(pass);
    }
    catch (...)
    {
        color(12);
        g_xy(51, 19);
        cout << "Invalid Pin Format" << endl;
    }
    if (acc != NULL && intPass == acc->accPin)
    {
        color(10);
        g_xy(52, 21);
        cout << "Login Successful" << endl;
        g_xy(55, 23);
        cout << "Please Wait" << endl;
        loading();
        color(15);
        return true;
    }
    else
    {
        color(12);

        g_xy(54, 21);
        cout << "Login Failed" << endl;
        g_xy(55, 23);
        cout << "Going Back" << endl;
        loading();
        color(15);
        return false;
    }
}
bool adminLogin()
{
    cin.sync();
    string pass = "";
    char ch = '\0';
    g_xy(42, 13);
    cout << "Pass" << endl;
    g_xy(48, 12);
    line(23);
    g_xy(48, 13);
    cout << setw(23) << left << "|"
         << "|" << endl;
    g_xy(48, 14);
    line(23);
    g_xy(57, 13);
    int saveX = 57;
    while (true)
    {
        ch = getch();
        if (ch == 13)
        {
            break;
        }
        else if (ch == '\b')
        {

            if (!pass.empty())
            {
                pass.pop_back();
                g_xy(--saveX, 13);
                cout << " ";
            }
        }
        else
        {
            pass.push_back(ch);
            g_xy(saveX++, 13);
            cout << "*";
        }
    }
    if (pass == "admin")
    {
        color(10);
        g_xy(52, 21);
        cout << "Login Successful" << endl;
        g_xy(55, 23);
        cout << "Please Wait" << endl;
        loading();
        color(15);
        return true;
    }
    else
    {
        color(12);
        g_xy(54, 21);
        cout << "Login Failed" << endl;
        g_xy(55, 23);
        cout << "Going Back" << endl;
        loading();
        color(15);
        return false;
    }
}
int mainMenu(Customer *customer = customer, unsigned int *n = n)
{
    cin.sync();
    cin.clear();
    int opt = -1;
    line(119);
    cout << setw(50) << left << "|" << setw(69) << left << ""
         << "|" << endl;
    cout << setw(50) << left << "|" << setw(69) << left << "  Customer Menu "
         << "|" << endl;
    cout << setw(50) << left << "|" << setw(69) << left << " Managments Menu "
         << "|" << endl;
    cout << setw(50) << left << "|" << setw(69) << left << "       QUIT "
         << "|" << endl;
    cout << setw(50) << left << "|" << setw(69) << left << ""
         << "|" << endl;
    line(119);
    opt = arrowSelection(4);
    return opt;
}
int customerMenu(Customer *customer = customer, unsigned int *n = n, unsigned int *id = id)
{

    cin.sync();
    cin.clear();
    bool flip = 0;
    int opt = -1;
label1:
    if (opt == -1)
    {
        flip = 0;
    }
    else
    {
        flip = 1;
    }
    system("CLS");

    line(119);
    cout << setw(50) << left << "|" << setw(69) << left << ""
         << "|" << endl;
    if (opt == 2)
    {
        color(10);
        cout << setw(50) << left << ">"
             << setw(69) << left << " Withdraw Money"
             << "<" << endl;
        color(15);
    }
    else
    {
        cout << setw(50) << left << "|"
             << setw(69) << left << " Withdraw Money"
             << "|" << endl;
    }

    if (opt == 3)
    {
        color(10);
        cout << setw(50) << left << ">"
             << setw(69) << left << "   Send Money"
             << "<" << endl;
        color(15);
    }
    else
    {
        cout << setw(50) << left << "|"
             << setw(69) << left << "   Send Money"
             << "|" << endl;
    }
    if (opt == 4)
    {
        color(10);
        cout << setw(50) << left << ">"
             << setw(69) << left << "   Change Pin"
             << "<" << endl;
        color(15);
    }
    else
    {
        cout << setw(50) << left << "|"
             << setw(69) << left << "   Change Pin"
             << "|" << endl;
    }

    if (opt == 5)
    {
        color(10);
        cout << setw(50) << left << ">"
             << setw(69) << left << "    Get Loan"
             << "<" << endl;
        color(15);
    }
    else
    {
        cout << setw(50) << left << "|"
             << setw(69) << left << "    Get Loan"
             << "|" << endl;
    }
    if (opt == 6)
    {
        color(10);
        cout << setw(50) << left << ">"
             << setw(69) << left << "    Pay Loan"
             << "<" << endl;
        color(15);
    }
    else
    {
        cout << setw(50) << left << "|"
             << setw(69) << left << "    Pay Loan"
             << "|" << endl;
    }
    if (opt == 7)
    {
        color(10);
        cout << setw(50) << left << ">"
             << setw(69) << left << " Show Statement"
             << "<" << endl;
        color(15);
    }
    else
    {
        cout << setw(50) << left << "|"
             << setw(69) << left << " Show Statement"
             << "|" << endl;
    }

    cout << setw(50) << left << "|"
         << setw(69) << left << "    Go Back"
         << "|" << endl;

    cout << setw(50) << left << "|" << setw(69) << left << ""
         << "|" << endl;
    line(119);
    color(15);
    cout << setw(20) << left << "|" << setw(15) << left << customer->acc->firstName << setw(15) << left << customer->acc->lastName << setw(15) << left << customer->acc->accId << setw(15) << left << customer->acc->accBalance << setw(15) << left << customer->acc->accLoan << setw(24) << left << customer->acc->accType << "|" << endl;
    line(119);
    if (opt == -1 && flip == 0)
    {
        opt = arrowSelection(8);
        goto label1;
    }
    return opt;
}
int managementMenu(Customer *customer = customer, unsigned int *n = n)
{
    cin.sync();
    cin.clear();
    bool flip = 0;
    int opt = -1;
label1:
    if (opt == -1)
    {
        flip = 0;
    }
    else
    {
        flip = 1;
    }
    system("CLS");

    line(119);
    cout << setw(50) << left << "|" << setw(69) << left << ""
         << "|" << endl;
    if (opt == 2)
    {
        color(10);
        cout << setw(50) << left << ">" << setw(69) << left << "  Add Accounts"
             << "<" << endl;
        color(15);
    }
    else
    {
        cout << setw(50) << left << "|" << setw(69) << left << "  Add Accounts"
             << "|" << endl;
    }

    if (opt == 3)
    {
        color(10);
        cout << setw(50) << left << ">" << setw(69) << left << " Modify Account"
             << "<" << endl;
        color(15);
    }
    else
    {
        cout << setw(50) << left << "|" << setw(69) << left << " Modify Account"
             << "|" << endl;
    }
    if (opt == 4)
    {
        color(10);
        cout << setw(50) << left << ">" << setw(69) << left << " Delete Account"
             << "<" << endl;
        color(15);
    }
    else
    {
        cout << setw(50) << left << "|" << setw(69) << left << " Delete Account"
             << "|" << endl;
    }
    if (opt == 5)
    {
        color(10);
        cout << setw(50) << left << ">" << setw(69) << left << "   Add Money"
             << "<" << endl;
        color(15);
    }
    else
    {
        cout << setw(50) << left << "|" << setw(69) << left << "   Add Money"
             << "|" << endl;
    }

    if (opt == 6)
    {
        color(10);
        cout << setw(50) << left << ">" << setw(69) << left << "   Alot Loan"
             << "<" << endl;
        color(15);
    }
    else
    {
        cout << setw(50) << left << "|" << setw(69) << left << "   Alot Loan"
             << "|" << endl;
    }
    if (opt == 7)
    {
        color(10);
        cout << setw(50) << left << ">" << setw(69) << left << "Account Database"
             << "<" << endl;
        color(15);
    }
    else
    {
        cout << setw(50) << left << "|" << setw(69) << left << "Account Database"
             << "|" << endl;
    }

    cout << setw(50) << left << "|" << setw(69) << left << "    Go Back"
         << "|" << endl;

    cout << setw(50) << left << "|" << setw(69) << left << ""
         << "|" << endl;
    line(119);
    color(15);
    if (opt == -1 && flip == 0)
    {
        opt = arrowSelection(8);
        goto label1;
    }
    return opt;
}
int arrowSelection(int yxis)
{
    cin.clear();
    cin.sync();
    unsigned int pos = 1, y = 1;
    g_xy(69, 1);
    char c;
    while (true)
    {
        color(12);
        system("pause>nul");

        if (GetAsyncKeyState(VK_DOWN) && y <= yxis)
        {
            g_xy(70, y);

            cout << "    ";
            g_xy(43, y);

            cout << "    ";
            y++;
            g_xy(70, y);
            cout << "<===";
            g_xy(43, y);
            cout << "===>";
            pos++;
            continue;
        }
        if (GetAsyncKeyState(VK_UP) && y > 1)
        {

            g_xy(70, y);
            cout << "    ";
            g_xy(43, y);
            cout << "    ";
            y--;
            g_xy(70, y);
            cout << "<===";
            g_xy(43, y);
            cout << "===>";
            pos--;
            continue;
        }

        if (GetAsyncKeyState(VK_RETURN))
        {
            color(15);
            return pos;
        }
    }
}
//----------------------------------------------------------------
// UI and Misc End
//----------------------------------------------------------------
