
#include<iostream> //for input output
#include<windows.h> //
#include<conio.h> // for getch and clearcscreen
#include<fstream> // for file handelling
#include<cstring> // managing string
#include<cstdio> //
#include<cstdlib> //
#include<iomanip> // screen manuplation

using namespace std;
          void SetColor(int value) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), value);
}

void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
int dd,mm,yy,p=0,k=7,n_o_t=0;
void main_menu();
void admin_menu();
void clean();
void menu();
class product
   {
       int pno;
       char name[50];
       float price, qty, dis;
       public:


           void create_product()
           {
               cout << "\nPlease Enter The Product No.:  ";
               cin >> pno;
               cout << "\n\nPlease Enter The Name of The Product: ";
               scanf("%s",name);
               cout << "\nPlease Enter The Price of The Product: ";
               cin >> price;
               cout << "\nPlease Enter The Discount (%): ";
               cin >> dis;
           }


       void show_product()
       {
           cout <<left<<setw(20)<< pno;

           cout<<left<<setw(21);
           cout<<name;

           cout <<left<< setw(16);
           cout<<price;
           cout << dis<<"%";
       }

       int retpno()
       {
           return pno;
       }

       float retprice()
       {
           return price;
       }

       char * retname()
       {
           return name;
       }

       int retdis()
       {
           return dis;
       }

   }; //class ends here
fstream fp;
product pr;

void title(){
SetColor(8);
    cout << "\n\n=============================================================================\n";
       SetColor(13); cout<<left<<setw(20)<<"Product no."<<left<<setw(20)<<"NAME"<<left<<setw(15)<<"Price";
        cout<<"Discount";
SetColor(8);
    cout << "\n=============================================================================\n";
}

void place_order()
{
    int order_arr[50], quan[50], c = 0;
    float amt, damt, total = 0;
    char ch = 'Y';
    menu();
    cout << "\n============================";
    cout << "\n PLACE YOUR ORDER";
    cout << "\n============================\n";
    do
    {
        cout << "\n\nEnter the product no. of the product : ";
        cin >> order_arr[c];
        cout << "\nQuantity in number : ";
        cin >> quan[c];
        c++;
        cout << "\nDo You Want To Order Another Product ? (y/n)";
        cin >> ch;
    } while (ch == 'y' || ch == 'Y');
    clean();
    cout << "\n\nThank You For Placing The Order";
    int x=1;
cout << "\n\n************ INVOICE ***********\n\n";
    cout<<left<<setw(80)<<"Invoice Number"<<"Date\n";
    cout<<left<<setw(80)<<x;cout<<dd<<"-"<<mm<<"-"<<yy;
    cout<<"\n\n#######################################\n";
    cout<<"          SUPER MARKET\n";
    cout<<"#######################################\n\n";
cout<<"=====================================================================================";
    cout<<"===================================\n";
    cout<<left<<setw(20)<<"Product no."<<left<<setw(20)<<"NAME"<<left<<setw(20)<<"Quantity";
    cout<<left<<setw(15)<<"Price"<<left<<setw(15)<<"Amount"<<"Amount after Discount\n";
cout<<"=====================================================================================";
    cout<<"===================================\n";




    for (int x = 0; x <= c; x++)
    {
        fp.open("Shop.dat", ios:: in );
        fp.read((char * ) & pr, sizeof(product));
        while (!fp.eof())
        {
            if (pr.retpno() == order_arr[x])
            {
                amt = pr.retprice() * quan[x];
                damt = amt - (amt * pr.retdis() / 100);
            cout<<left<<setw(20)<<order_arr[x]<<left<<setw(21)<<pr.retname()<<left<<setw(21)
        << quan[x] <<left<<setw(16)<<pr.retprice()<<left<<setw(16) <<amt<<damt<<"\n";
                total += damt;
            }


            fp.read((char * ) & pr, sizeof(product));
        }

        fp.close();
    }
    cout << "\nTOTAL = " << total;

    cout<<"\n------------------------------------------------------------------------------------------------------------------------";
    cout<<"\n\n THANKYOU, VISIT AGAIN!";
    cout<<"Press any character to go back:";
    char b;
    cin>>b;
    clean();
    main_menu();

}








void write_product()
{
    fp.open("Shop.dat", ios::out | ios::app);
    pr.create_product();
    fp.write((char * ) & pr, sizeof(product));
    fp.close();SetColor(13);
    cout << "\n\nThe Product Has Been Created \n";SetColor(8);
    cout<<"\t\tPress 1 :To create more product\n";
    cout<<"\t\tPress any other no.: To go back ";
    int choice;
    cin>>choice;
    if(choice==1){
        system("cls");
    write_product();
    }
else{
    system("cls");
        admin_menu();
}


}

void modify_product()
{
    menu();

    int no, found = 0;
    cout << "\n\n\tTo Modify ";
    cout << "\n\n\tPlease Enter The Product No.:";
    cin >> no;
    fp.open("Shop.dat", ios:: in | ios::out);
    while (fp.read((char * ) & pr, sizeof(product)) && found == 0)
    {
        if (pr.retpno() == no)
        {
            cout << "\n\nPlease Enter The New Details of Product" << endl;
            pr.create_product();
            unsigned long int pos = -1 * sizeof(pr);
            fp.seekp(pos, ios::cur);
            fp.write((char * ) & pr, sizeof(product));

            found = 1;
        }
    }
    fp.close();



    if (found == 0)
    {system("clear");
        cout << "\n\n Record Not Found ";
        modify_product();
    }

    else{system("clear");

        menu();
        cout << "\n\n\t Record Updated";

    }

    admin_menu();



}



void delete_product()
{
    int no;
SetColor(13);
    cout << "\n\n\n\t\tDelete Record";SetColor(8);
    cout << "\n\n\tPlease Enter the product no. of the product you want to delete: ";
    cin >> no;
    fp.open("Shop.dat", ios:: in | ios::out);
    fstream fp2;
    fp2.open("Temp.dat", ios::out);
    fp.seekg(0, ios::beg);
    while (fp.read((char * ) & pr, sizeof(product)))
    {
        if (pr.retpno() != no)
        {
            fp2.write((char * ) & pr, sizeof(product));
        }
    }
    fp2.close();
    fp.close();
    remove("Shop.dat");
    rename("Temp.dat", "Shop.dat");

    clean();
    SetColor(13);
    cout << "\n\n\tRecord Deleted ..";
SetColor(8);

    admin_menu();

}
void menu(){
    title();
    fp.open("Shop.dat", ios:: in );
    while (fp.read((char * ) & pr, sizeof(product)))
    {
        pr.show_product();

        cout<<"\n";
    }
    fp.close();

}




void display_all()
{
SetColor(13);
    cout << "\n\n\n\t\tDISPLAY ALL RECORD !!!\n\n";
    title();
    fp.open("Shop.dat", ios:: in );
    while (fp.read((char * ) & pr, sizeof(product)))
    {
        pr.show_product();

        cout<<"\n";
    }
    fp.close();


    cout<<"\n\nEnter any character to go back ";
    char p;
    cin>>p;
    system("cls");
    admin_menu();

}

void login(){

     gotoxy(41,k-3);
    SetColor(8);
     cout<<"=========\n";
    gotoxy(41,k-2);
    SetColor(13);
     cout<<"| LOGIN |\n";
    gotoxy(41,k-1);
    SetColor(8);
     cout<<"=========\n";
    gotoxy(37,k+3);
     cout<<"Login ID : ";
    char na[30];
    cin.getline(na, 30);
    gotoxy(37,k+5);
    cout<<"Password : ";
    char pass[30];
    cin.getline(pass,30);

    if((strcmp(na,"Sameer")==0||strcmp(na,"Suryakant")==0||strcmp(na, "Nimit")==0)&&strcmp(pass,"password")==0)
    {

            gotoxy(37,k+7);
            cout<<"*Access Granted*\n";
              }


    else
    {
        gotoxy(37,k+7);
        cout<<"**Access Denied*\n";
        n_o_t++;
        getch();
        system("cls");

        if(n_o_t>3){
        gotoxy(30,k+9);
        SetColor(4);
        cout<<"Alert : More than 3 wrong attempt";
        getch();
        exit(0);}
        login();
    }
}
    void date_fun(){
    gotoxy(35,k+9);
    cout<<"Today's date : ";
    cin>>dd>>mm>>yy;
    gotoxy(35,k+11);
    cout<<"Press any key to proceed\n";
    getch();
    system("cls");

}





void clean(){
    system("cls");
}




void footer()
{clean();
    cout<<"\n\n\n";
    cout<<"             *   *   \n";
    cout<<"MADE With   *  *  *    By: SK, NM, MS\n";
    cout<<"             *   *        \n";
    cout<<"               * \n";

}

void admin_menu()
{

    int ch2;SetColor(8);
    cout<<"\n\n\n============================";SetColor(13);
    cout << "\n\tADMIN MENU\n";SetColor(8);cout<<"==============================";SetColor(8);
    cout << "\n\n\t1.CREATE PRODUCT";
    cout << "\n\n\t2.DISPLAY ALL PRODUCTS";
    cout << "\n\n\t3.MODIFY PRODUCT";
    cout << "\n\n\t4.DELETE PRODUCT";
    cout << "\n\n\t5.BACK TO MAIN MENU";
    cout << "\n\n\tPlease Enter Your Choice (1-5) ";
    cin>>ch2;
    switch (ch2)
    {
    case 1:
            write_product();

        break;
    case 2:
            system("cls");
            display_all();


        break;

    case 3:
            clean();
            modify_product();

        break;
    case 4:
            clean();
            delete_product();

        break;



    case 5:
            clean();
            main_menu();
        break;
    default:
            clean();SetColor(13);
        cout << "\n\n\t\tInvalid choice";
        admin_menu();
    }
}






void main_menu(){
   int ch;

    gotoxy(40,5);
    SetColor(8);
    cout<<"======================================";gotoxy(45,6);SetColor(13);
    cout<<"          SUPER MARKET";gotoxy(40,7);SetColor(8);
    cout<<"======================================";gotoxy(45,10);SetColor(13);
    cout << "MAIN MENU\n";gotoxy(45,12);SetColor(8);
    cout << "01. CUSTOMER";gotoxy(45,13);
    cout << "02. ADMINISTRATOR";gotoxy(45,14);
    cout << "03. EXIT";gotoxy(45,16);SetColor(13);
    cout << "Please Select Your Option (1-3) ";
    cin>>ch;
    switch (ch)
    {
    case 1:
            system("cls");
            place_order();

        break;
    case 2:
            system("cls");
            admin_menu();

        break;
    case 3:

            cout << "ARE YOU SURE, YOU WANT TO EXIT (Y/N)?";
            char yn;
            cin >> yn;
            if ((yn == 'Y') || (yn == 'y'))
                footer();
            else
            { clean();
                main_menu();}
            break;

    default:
            clean();
        cout << "Invalid choice";

            main_menu();
            break;
    }

}


int main()
{

    login();
    date_fun();
    clean();
    main_menu();



}
