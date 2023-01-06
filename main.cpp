#include "functionsT.h"
int main()
{

    customer->readDatabase();
    customer->outputDatabase();
    int opt, mainOpt;
    char yn;
    bool chk;
    bool loop_control = true;
    // do
    // {
    //     system("CLS");
    //     mainOpt = mainMenu();
    //     system("CLS");
    //     switch (mainOpt)
    //     {
    //     default:
    //         break;
    //     case 2:
    //         loop_control = true;
    //         chk = customerLogin();
    //         cin.sync();

    //         if (chk == true)
    //         {
    //             do
    //             {
    //                 opt = customerMenu();
    //                 cout << endl
    //                      << endl;

    //                 switch (opt)
    //                 {
    //                 default:
    //                     break;
    //                 case 2:
    //                     // acc->withdrawCash();
    //                     cout << "Withdraw Cash" << endl;
    //                     system("pause>nul");
    //                     system("CLS");
    //                     break;
    //                 case 3:
    //                     // acc->transferCash();
    //                     cout << "Transfer Cash" << endl;
    //                     system("pause>nul");
    //                     system("CLS");
    //                     break;
    //                 case 4:
    //                     // acc->changePin();
    //                     cout << "Change Pin" << endl;
    //                     system("pause>nul");
    //                     system("CLS");
    //                     break;
    //                 case 5:
    //                     // acc->takeLoan();
    //                     cout << "Take Loan" << endl;
    //                     system("pause>nul");
    //                     system("CLS");
    //                     break;
    //                 case 6:
    //                     // acc->payLoan();
    //                     cout << "Pay Loan" << endl;
    //                     system("pause>nul");
    //                     system("CLS");
    //                     break;
    //                 case 7:
    //                     // acc->printStatement();
    //                     cout << "Print Statement" << endl;
    //                     system("pause>nul");
    //                     system("CLS");
    //                     break;
    //                 case 8:
    //                     loop_control = false;
    //                     cin.clear();
    //                     system("CLS");
    //                     break;
    //                 }

    //             } while (loop_control == true);
    //         }
    //         loop_control = true;
    //         break;

    //     case 3:
    //         loop_control = true;
    //         chk = adminLogin();
    //         if (chk == true)
    //         {
    //             do
    //             {
    //                 opt = managementMenu();
    //                 cout << endl
    //                      << endl;

    //                 switch (opt)
    //                 {
    //                 default:
    //                     system("CLS");
    //                     break;
    //                 case 2:
    //                     // addAccount();
    //                     cout << "Add Account" << endl;
    //                     system("pause");
    //                     system("CLS");
    //                     break;
    //                 case 3:
    //                     // modifyAccount();
    //                     cout << "Modify Account" << endl;
    //                     system("pause");
    //                     system("CLS");
    //                     break;
    //                 case 4:
    //                     // deleteAccount();
    //                     cout << "Delete Account" << endl;
    //                     system("pause");
    //                     system("CLS");
    //                     break;
    //                 case 5:
    //                     // alotCash();
    //                     cout << "Alot Cash" << endl;
    //                     system("pause");
    //                     system("CLS");
    //                     break;
    //                 case 6:
    //                     // alotLoan();
    //                     cout << "Alot Loan" << endl;
    //                     system("pause");
    //                     system("CLS");
    //                     break;
    //                 case 7:
    //                     // outputDatabase();
    //                     cout << "Output Database" << endl;
    //                     system("pause");
    //                     system("CLS");
    //                     break;
    //                 case 8:
    //                     loop_control = false;
    //                     cin.clear();
    //                     system("CLS");
    //                     break;
    //                 }

    //             } while (loop_control == true);
    //         }
    //         loop_control = true;
    //         break;
    //     case 4:
    //         cout << "Are you sure you want to QUIT![y|Y] :: ";
    //         cin >> yn;
    //         if (yn == 'y' || yn == 'Y')
    //         {
    //             exit(0);
    //         }
    //         break;
    //     }

    // } while (true);

    nullifier();
    system("pause");
    return 0;
}
