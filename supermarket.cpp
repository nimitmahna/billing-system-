#include<iostream> //for input output
#include<windows.h> // 
#include<conio.h> // for getch and clearcscreen
#include<fstream> // for file handelling
#include<cstring> // managing string
#include<cstdio> //
#include<cstdlib> //
#include<iomanip> // screen manuplation

using namespace std;
//global variable declaration
int k = 7, r = 0, flag = 0;
COORD coord = { 0, 0 };
//for textcolour (copied from stack overflow)
void SetColor(int value) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), value);
}
 //for manipulating coordinates on output screen
void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
 //footer for program
void footer()
{
    cout<<"\n\n\n";
    cout<<"             *   *   \n";
    cout<<"MADE With   *  *  *    By: SK, NM, MS\n";
    cout<<"             *   *        \n";
    cout<<"               * \n";

}
struct date
{
    int mm, dd, yy;
};

ofstream fout;
ifstream fin;

class item
{
    int itemno;
    char name[25];
    date d;
public:
    void add() // add function
    {
        SetColor(11);
        cout << "\n\n\tItem No: ";
        cin >> itemno;
        cout << "\n\n\tName of the item: ";
        cin >> name;
        //gets(name);
        cout << "\n\n\tManufacturing Date(dd-mm-yy): ";
        cin >> d.mm >> d.dd >> d.yy;
    }
    void show() // show function
    {
        SetColor(11);
        cout << "\n\tItem No: ";
        cout << itemno;
        cout << "\n\n\tName of the item: ";
        cout << name;
        cout << "\n\n\tDate : ";
        cout << d.mm << "-" << d.dd << "-" << d.yy;
    }
    void report()                                      // shows  bill 
    {
        SetColor(11);
        gotoxy(3, k);
        cout << itemno;
        gotoxy(13, k);
        puts(name);
    }
    int retno() 
    {
        return(itemno);

    }

};

class amount : public item
{
    float price, qty, tax, gross, dis, net_amt;
public:
    void add();
    void show();
    void report();
    void calculate();
    void pay();
    float retnetamt()
    {
        return(net_amt);
    }
} amt;

void amount::add()
{
    item::add();
    SetColor(11);
    cout << "\n\n\tPrice: ";
    cin >> price;
    cout << "\n\n\tQuantity: ";
    cin >> qty;
    cout << "\n\n\tTax percent: ";
    cin >> tax;
    cout << "\n\n\tDiscount percent: ";
    cin >> dis;
    calculate();
    fout.write((char*)&amt, sizeof(amt));
    fout.close();
}
void amount::calculate()                          // calculates gross amount and net amount
{
    gross = price + (price * (tax / 100));
    net_amt = qty * (gross - (gross * (dis / 100)));
}
void amount::show() //  reads the file and the prints net amount
{
    fin.open("itemstore.dat", ios::binary);
    SetColor(11);
    fin.read((char*)&amt, sizeof(amt));
    item::show();
    cout << "\n\n\tNet amount: ";
    cout << net_amt;
    fin.close();
}

void amount::report()                                 // prints item detail line wise
{
    item::report();
    gotoxy(23, k);
    cout << price;
    gotoxy(33, k);
    cout << qty;
    gotoxy(44, k);
    cout << tax;
    gotoxy(52, k);
    cout << dis;
    gotoxy(64, k);
    cout << net_amt;
    k = k + 1;
    if (k == 50)
    {
        gotoxy(25, 50);
        SetColor(11);
        cout << "PRESS ANY KEY TO CONTINUE...";
        getch();
        k = 7;
        system("cls");
        gotoxy(30, 3);
        cout << " ITEM DETAILS ";
        gotoxy(3, 5);
        cout << "NUMBER";
        gotoxy(13, 5);
        cout << "NAME";
        gotoxy(23, 5);
        cout << "PRICE";
        gotoxy(33, 5);
        cout << "QUANTITY";
        gotoxy(44, 5);
        cout << "TAX";
        gotoxy(52, 5);
        cout << "DEDUCTION";
        gotoxy(64, 5);
        cout << "NET AMOUNT";
    }
}

void amount::pay()                                      // shows bill
{
    show();
    SetColor(11);
    cout << "\n\n\n\t\t*********************************************";
    cout << "\n\t\t                 DETAILS                  ";
    cout << "\n\t\t*********************************************";
    cout << "\n\n\t\tPRICE                     :" << price;
    cout << "\n\n\t\tQUANTITY                  :" << qty;
    cout << "\n\t\tTAX PERCENTAGE              :" << tax;
    cout << "\n\t\tDISCOUNT PERCENTAGE         :" << dis;
    cout << "\n\n\n\t\tNET AMOUNT              :Rs." << net_amt;
    cout << "\n\t\t*********************************************";
}




int main()
{


    cout.setf(ios::fixed); // manage float in output 
    cout.setf(ios::showpoint);
    cout << setprecision(2); // fixes deciaml points
    fstream tmp("temp.dat", ios::binary | ios::out);      // temp file is created
menu:
    system("cls");
    gotoxy(25, 1);                                      // take cursor to the coordiantes
    SetColor(8);                                       // sets the colour of text
    cout << " ==============================\n\n";
    gotoxy(25, 2);
    SetColor(13);
    cout << "| Super Market Billing System  |";
    gotoxy(25, 3);
    SetColor(8);
    cout << " ==============================\n\n";
    SetColor(11);
    cout << "\n\t\t1.Bill Report\n\n";                // 1.Bill Report
    cout << "\t\t2.Add/Remove/Edit Item\n\n";         // 2.Add/Remove/Edit Item
    cout << "\t\t3.Show Item Details\n\n";            // 3.Show Item Details
    cout << "\t\t4.Exit\n\n";                         // 4.Exit
    cout << "\t\tPlease Enter Required Option: ";
    int ch, ff;                                        // ch for input number
    float gtotal;                                     // stores  the grand total
    cin >> ch;
    switch (ch)
    {
    case 1:                                          // case 1. bill report
    ss:
        system("cls");                               // clear screen
        gotoxy(25, 1);
        SetColor(8);
        cout << "==================\n\n";
        gotoxy(25, 2);
        SetColor(13);
        cout << " | Bill Details |";
        gotoxy(25, 3);
        SetColor(8);
        cout << "==================\n\n";
        SetColor(11);
        cout << "\n\t\t1.All Items\n\n";                //1.All Items
        cout << "\t\t2.Back to Main menu\n\n";          //2.Back to Main menu
        cout << "\t\tPlease Enter Required Option: ";
        int cho;
        cin >> cho;
        if (cho == 1)                                   // if entered one prints the bill with item details
        {
            system("cls");
            gotoxy(30, 3);
            cout << " BILL DETAILS ";
            gotoxy(3, 5);
            cout << "ITEM NO";
            gotoxy(13, 5);
            cout << "NAME";
            gotoxy(23, 5);
            cout << "PRICE";
            gotoxy(33, 5);
            cout << "QUANTITY";
            gotoxy(44, 5);
            cout << "TAX %";
            gotoxy(52, 5);
            cout << "DISCOUNT %";
            gotoxy(64, 5);
            cout << "NET AMOUNT";
            fin.open("itemstore.dat", ios::binary);                 // opens itmstore.dat file
            if (!fin)                                              // if unable to open will print file not found,takes back to menu
            {
                cout << "\n\nFile Not Found...";
                goto menu;
            }
            fin.seekg(0);                                         //
            gtotal = 0;                                           
            while (!fin.eof())                                   // loop will run until it gets to end of file
            {
                fin.read((char*)&amt, sizeof(amt));              // reads the file
                if (!fin.eof())                                  // if it is not end of file
                {
                    amt.report();
                    gtotal += amt.retnetamt();                   // adds the amount to gtotal which will be our grand total
                    ff = 0;                                      
                }
                if (ff != 0) gtotal = 0;                        // if somehow ff is not zero our grand total in 0
            }
            gotoxy(17, k);
            cout << "\n\n\n\t\t\tGrand Total=" << gtotal;       // prints grand total

            cout<<"\n\n\n";
            footer();                                           // prints the footer
            getch();                  
            fin.close();                                        // file is closed
        }
        if (cho == 2)                                           // back to main menu
        {
            goto menu;
        }
        goto ss;
    case 2:                                                     // 2.Add/Remove/Edit Item
    db:
        system("cls");
        gotoxy(25, 1);
        SetColor(8);
        cout << "=================\n\n";
        gotoxy(25, 2);
        SetColor(13);
        cout << "|  Bill Editor  |";
        gotoxy(25, 3);
        SetColor(8);
        cout << "=================\n\n";
        SetColor(11);
        cout << "\n\t\t1.Add Item Details\n\n";
        cout << "\t\t2.Edit Item Details\n\n";
        cout << "\t\t3.Delete Item Details\n\n";
        cout << "\t\t4.Back to Main Menu ";
        int apc;
        cin >> apc;
        switch (apc)
        {
        case 1:                                                         // used to add items
            fout.open("itemstore.dat", ios::binary | ios::app);         // opening itemstore.dat
            amt.add();                                                  // calling add function via objectof class amount
            cout << "\n\t\tItem Added Successfully!";
            getch();
            goto db;

        case 2:                                                         // edit item details
            int ino;
            flag = 0;
            cout << "\n\n\tEnter Item ID to be Edited :";
            cin >> ino;
            fin.open("itemstore.dat", ios::binary);                    // opens itemstore.dat
            fout.open("itemstore.dat", ios::binary | ios::app);
            if (!fin)                                                  //
            {
                cout << "\n\nFile Not Found...";
                goto menu;
            }
            fin.seekg(0);
            r = 0;
            while (!fin.eof())                                       // loop will run till end of file
            {
                fin.read((char*)&amt, sizeof(amt));                  // reading the file
                if (!fin.eof())                                      // loop till end of file
                {   
                   int x = amt.item::retno();                        // compares the input id with ids in the file
                    if (x == ino)                                    // if found we edit it
                    {
                        flag = 1;
                        fout.seekp(r * sizeof(amt));           
                        system("cls");
                        SetColor(11);
                        cout << "\n\t\tCurrent Details are\n";      
                        amt.show();
                        cout << "\n\n\t\tEnter New Details\n";
                        amt.add();
                        cout << "\n\t\tItem Details editted"; 

                    }
                }
                r++;                                                   // pointer is moved to next item for further queries
            }
            if (flag == 0)                                             // if not matched  prints file doesnt exit
            {
                SetColor(11);
                cout << "\n\t\tItem No does not exist...Please Retry!";
                getch();
                goto db;
            }
            fin.close();                                              // itemstore.dat is closed
            getch();
            goto db;

        case 3:                                                      // to remove an item
            flag = 0;
            SetColor(11);
            cout << "\n\n\tEnter Item ID to be Removed :";
            cin >> ino;
            fin.open("itemstore.dat", ios::binary);                // opens itemstor.dat file
            if (!fin)                                              // if unable to open
            {
                cout << "\n\nFile Not Found...";
                goto menu;
            }
            //fstream tmp("temp.dat",ios::binary|ios::out);       // temp is already created above
            fin.seekg(0);
            while (fin.read((char*)&amt, sizeof(amt)))            // reading itemstore.dat file
            {
                int x = amt.item::retno();                       // matching id
                if (x != ino)                                    // while id doesn't matches we write it on temp.dat file
                    tmp.write((char*)&amt, sizeof(amt));
                else
                {
                    flag = 1;                                    // if id matches we make flag 1
                } 
            }
            fin.close();                                          // itemstore.dat is closed
            tmp.close();                                          // temp file is closed
            fout.open("itemstore.dat", ios::trunc | ios::binary); // opening itemstore
            fout.seekp(0);
            tmp.open("temp.dat", ios::binary | ios::in);          // opening temp.dat
            if (!tmp)                                             // if unable to open prints error
            {
                cout << "Error in File";
                goto db;
            }
            while (tmp.read((char*)&amt, sizeof(amt)))            // writing from temp to itemstore
                fout.write((char*)&amt, sizeof(amt));
            tmp.close();                                         // both files are closed
            fout.close();
            if (flag == 1) {                                     // now item is removed 
                SetColor(11);
                cout << "\n\t\tItem Succesfully Removed";
            }
            else if (flag == 0) {                                // else item doesn't exit
                SetColor(12);
                cout << "\n\t\tItem does not Exist! Please Retry";
            }
            getch();
            goto db;
        case 4:                                               // goes back to menu
            goto menu;
        default:                                              // else wrong choice
            SetColor(12);
            cout << "\n\n\t\tWrong Choice!!! Retry";
            getch();
            goto db;
        }
    case 3:                                              // show particular item detalis
        system("cls");                                   //clear screen
        flag = 0;
        int ino;
        SetColor(11);
        cout << "\n\n\t\tEnter Item ID :";
        cin >> ino;
        fin.open("itemstore.dat", ios::binary);               // opening itemstore.dat file
        if (!fin)                                             // if unable to open error
        {
            SetColor(12);
            cout << "\n\nFile Not Found...\nProgram Terminated!";
            goto menu;
        }
        fin.seekg(0);
        while (fin.read((char*)&amt, sizeof(amt)))           // else read the file and prints the details if id is matched
        {
            int x = amt.item::retno();
            if (x == ino)
            {
                amt.pay();
                flag = 1;
                break;
            }
        }
        if (flag == 0)
            SetColor(12);
        cout << "\n\t\tItem does not exist....Please Retry!";          // else item doesn't exit
            
        getch();
        fin.close();                                                   // itemstore .dat is closed and went to menu
        goto menu;
    case 4:                                                            // exit 
        system("cls");
        gotoxy(20, 20);
        SetColor(11);
        cout << "ARE YOU SURE, YOU WANT TO EXIT (Y/N)?";
        char yn;
        cin >> yn;
        if ((yn == 'Y') || (yn == 'y'))
        {
            gotoxy(12, 20);
            system("cls");
            SetColor(10);
            cout << "************************** THANKS FOR SHOPPING WITH US **************************************\n\n";
            cout << "**************************     HAVE A GREAT DAY !      **************************************";
            cout<<"\n";
            footer();
            getch();
            exit(0);
        }
        else if ((yn == 'N') || (yn == 'n'))
            goto menu;
        else
        {
            goto menu;
        }
    default:                                                // else wrong choice
        SetColor(8);
        cout << "\n\n\t\tWrong Choice....Please Retry!";
        getch();
        goto menu;
    }
    return 0;
}
