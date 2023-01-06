#include "prototype.h"
void nullifier()
{
    id = NULL;
    accNumChk = NULL;
    n = NULL;
    delete id;
    delete accNumChk;
    delete n;
}
// NEW

// NEW END
//----------------------------------------------------------------
//  Database Functions Start
//  ----------------------------------------------------------------

account *Customer::getAccount(int id)
{
    account *temp = head;
    while (temp)
    {
        if (temp->accId == id)
        {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}
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
// NEW ADD FUNCTION
void Customer ::addAccount(account *node)
{
    account *temp = new account;
    temp = node;
    if (isEmpty())
    {
        head = temp;
        tail = temp;
        return;
    }
    else
    {
        tail->next = temp;
        node->prev = temp;
        tail = node;
    }
}
// NEW ADD FUNCTION END

void Customer::readDatabase(unsigned int *n = n, unsigned int *accNumChk = accNumChk)
{
    accSizChk(n);
    account *fetchedAccount = new account;
    fin.open(database, ios::in);
    if (fin.is_open())
    {

        for (int i = 0; i < *n; i++)
        {
            fin >> fetchedAccount;
            if (isEmpty())
            {
                head = fetchedAccount;
                tail = fetchedAccount;
                fetchedAccount = new account;
            }
            else
            {
                tail->next = fetchedAccount;
                fetchedAccount->prev = tail;
                tail = fetchedAccount;
                fetchedAccount = new account;
            }
        }
    }
    else
    {
        databaseFailure();
        return;
    }
    
    fin.close();
    *accNumChk = (tail->accId) + 1;
    delete fetchedAccount;
}

void Customer::updateDatabase()
{
    fout.open(database, ios::out | ios::trunc);
    if (fout.is_open())
    {
        account *temp = head;
        while (temp)
        {
            fout << temp;
            temp = temp->next;
        }
    }
    else
    {
        databaseFailure();
    }
    fout.close();
    readDatabase();
}
void account ::outputInfo() const
{

    cout << "First Name: " << firstName << endl;
    cout << "Last Name: " << lastName << endl;
    cout << "Account Number: " << accId << endl;
    cout << "Account Type: " << accType << endl;
    cout << "Account Balance: " << accBalance << endl;
    cout << "Account Loan: " << accLoan << endl;
    cout << endl;
}
//----------------------------------------------------------------
// Database Functions End
// ----------------------------------------------------------------
//----------------------------------------------------------------
// Management Functions Start
//----------------------------------------------------------------

//----------------------------------------------------------------
// Management Functions End
//----------------------------------------------------------------

int Customer ::idChk(unsigned int *n, int tempId)
{
    int pos = 0;
    account *trav = head;
    while (trav)
    {
        if (trav->accId == tempId)
        {
            return pos;
        }
        pos++;
        trav = trav->next;
    }
    return -1;
}
// int account::accTypeChk()
// {
//     unsigned int maxAmount;
//     if ((strcmpi(accType.c_str(), "platinum")) == 0)
//     {
//         maxAmount = 100000;
//     }
//     else if ((strcmpi(accType.c_str(), "gold")) == 0)
//     {
//         maxAmount = 75000;
//     }
//     else if ((strcmpi(accType.c_str(), "silver")) == 0)
//     {
//         maxAmount = 50000;
//     }
//     else if ((strcmpi(accType.c_str(), "bronze")) == 0)
//     {
//         maxAmount = 25000;
//     }
//     else
//     {
//         maxAmount = 0;
//     }
//     return maxAmount;
// }
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

bool customerLogin(unsigned int *n = n, account *acc = acc)
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
    acc = customer->getAccount(tempId);
    if (!tempId)
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

    if (intPass == acc->accPin)
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
int mainMenu(unsigned int *n = n)
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
int customerMenu(unsigned int *n = n, unsigned int *id = id)
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
    cout << setw(20) << left << "|" << setw(15) << left
         << acc->firstName
         << setw(15) << left
         << acc->lastName
         << setw(15) << left
         << acc->accId
         << setw(15) << left
         << acc->accType
         << setw(15) << left
         << acc->accBalance
         << setw(24) << left
         << acc->accLoan << "|" << endl;
    line(119);
    if (opt == -1 && flip == 0)
    {
        opt = arrowSelection(8);
        goto label1;
    }
    return opt;
}
int managementMenu(unsigned int *n = n)
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