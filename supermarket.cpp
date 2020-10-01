#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <fstream>
#include <ncurses.h>
#include <math.h>
#include <string>
using namespace std;
int h,dd,mm,yy;

void main_menu();
void admin_menu();
void menu();
void gotoxy(int ,int );
void setcolor(string );
class product
   {
       int pno;
       char chk[100];
       string name;
       float price, qty, dis;
       public:
       
    
           void create_product()
       {
               cout << "\n\n\nPlease Enter The Product No.: ";
               cin >>chk;
               cout << "\nPlease Enter The Name of The Product: ";
           cin>>name;
           
           
           
               cout << "\nPlease Enter The Price of The Product: ";
               cin >> price;
               cout << "\nPlease Enter The Discount (%): ";
               cin >> dis;
           
           for( h=0;h<strlen(chk);h++)
                     {
                         if((chk[h]>=97&&chk[h]<=122)||(chk[h]>=65&&chk[h]<=90))
                             break;
                     }
                     if(h!=strlen(chk))
                     {
                         cout<<"\n\nINVALID product no.";
                         create_product();
                     }
                     else
                     {pno=0;
                         for(h=0;h<strlen(chk);h++)
                         {pno+=pow(10, strlen(chk)-1-h)*(chk[h]-48);
                             
                         }
                     }
           
           
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

       string retname()
       {
           return name;
       }

       int retdis()
       {
           return dis;
       }

   }; //class ends here


void gotoxy(int x, int y)
{
    printf("\033[%d;%dH",y,x);
}

//black,red,green,yellow,blue,magenta,cyan,white from 30 to 37

void setcolor(string s ){
   if(s=="black")
         printf("\x1b[30m");
       else if(s=="red")
            printf("\x1b[31m");
       else if(s=="green")
          printf("\x1b[32m");
    else if(s=="yellow")
         printf("\x1b[33m");
        else if(s=="blue")
             printf("\x1b[34m");
            else if(s=="magenta")
                 printf("\x1b[35m");
                else if(s=="cyan")
                     printf("\x1b[36m");
                    else if(s=="white")
                        printf("\x1b[37m");
    else if(s=="re")
     printf("\x1b[0m");
    
}


fstream fp;
product pr;

void title(){

    cout << "\n\n=============================================================================\n";
        cout<<left<<setw(20)<<"Product no."<<left<<setw(20)<<"NAME"<<left<<setw(15)<<"Price";
        cout<<"Discount";
        
    cout << "\n=============================================================================\n";
}

void place_order()
{
    int order_arr[50], quan[50], c = 0;
    float amt, damt, total = 0;
    char ch = 'Y';
    menu();
    cout << "\n\t\t============================";
    setcolor("magenta");
    cout << "\n\t\t      PLACE YOUR ORDER";
    setcolor("re");
    cout << "\n\t\t============================\n";
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
    system("clear");
    gotoxy(84, 6);
    setcolor("magenta");
    cout << "Thank You For Placing The Order";
    setcolor("re");
    gotoxy(43, 8);
    cout<<"*******************";
cout << " INVOICE ";
    cout<<"*******************\n";
    gotoxy(143, 9);
    cout<<"Date :"<<dd<<"/"<<mm<<"/"<<yy;
    gotoxy(80, 12);
         cout<<"======================================\n";
       gotoxy(80, 13);
       setcolor("magenta");
         cout<<"             SUPER  MARKET\n";
       setcolor("re");
       gotoxy(80, 14);
         cout<<"======================================\n";
    gotoxy(43, 18);
cout<<"=====================================================================================";
    cout<<"==============================\n";
    gotoxy(43, 19);
    cout<<left<<setw(20)<<"Product no."<<left<<setw(20)<<"NAME"<<left<<setw(20)<<"Quantity";
    cout<<left<<setw(15)<<"Price"<<left<<setw(15)<<"Amount"<<"Amount after Discount\n";
    gotoxy(43, 20);
cout<<"=====================================================================================";
    cout<<"==============================\n";
    
    
    int x;
    
    for ( x = 0; x <= c; x++)
    {
        fp.open("Shop.dat", ios:: in );
        fp.read((char * ) & pr, sizeof(product));
        while (!fp.eof())
        {
            if (pr.retpno() == order_arr[x])
            {
                amt = pr.retprice() * quan[x];
                damt = amt - (amt * pr.retdis() / 100);
                gotoxy(43, 21+x);
            cout<<left<<setw(20)<<order_arr[x]<<left<<setw(21)<<pr.retname()<<left<<setw(21)
        << quan[x] <<left<<setw(16)<<pr.retprice()<<left<<setw(16) <<amt<<damt<<"\n";
                total += damt;
            }
            fp.read((char * ) & pr, sizeof(product));
        }

        fp.close();
    }
    gotoxy(43, 22+x);
    cout << "TOTAL = " << total;
    
    gotoxy(43, 23+x); cout<<"-------------------------------------------------------------------------------------------------------------------\n";
    gotoxy(89, 26+x);
    cout<<" THANKYOU, VISIT AGAIN!";
    gotoxy(43, 30+x);
    cout<<"Press any key to go back:";
    char cy;
    cin>>cy;
    system("clear");
    main_menu();
   
}








void write_product()
{
    fp.open("Shop.dat", ios::out | ios::app);
    pr.create_product();
    fp.write((char * ) & pr, sizeof(product));
    fp.close();
   
    setcolor("red");
    cout << "\n\n\n\t\tThe product has been added ";
    setcolor("re");
   
    cout<<"\n\n\nPress 1 :To add more product\n\n";
   
    cout<<"Press any other key to go back  :  ";
    char choice;
    cin>>choice;    //check
    if(choice=='1'){
        system("clear");
    write_product();
    }
else{
    system("clear");
        admin_menu();
}
        
   
}



void modify_product()
{
   
    
    int no, found = 0;
    setcolor("magenta");
    cout << "\n\n\t\t\t\tModify Product Details\n\n";
    setcolor("re");
    menu();
    cout << "\n\nPlease enter product no. of the product you want to modify:";
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
        cout << "\n\t\t\t\t Record Not Found ";
        modify_product();
    }
    
    else{system("clear");
       
        gotoxy(92, 6);
        setcolor("red");
        cout << "Record Updated";
        setcolor("re");
       
    }
    
    admin_menu();
        
    
  
}

void delete_product()
{
    int no;
    setcolor("magenta");
    cout << "\n\n\t\t\t\tDelete Record\n\n";
    setcolor("re");
    menu();
    
    cout << "\n\nPlease Enter the product no. of the product you want to delete:";
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
    
    system("clear");
    gotoxy(93, 6);
    setcolor("red");
    cout << "Record Deleted ..\n";
    setcolor("re");
    
    
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
    setcolor("magenta");
    cout << "\n\n\n\t\tDISPLAY ALL RECORD !!!\n\n";
    setcolor("re");
    title();
    fp.open("Shop.dat", ios:: in );
    while (fp.read((char * ) & pr, sizeof(product)))
    {
        pr.show_product();
        
        cout<<"\n";
    }
    fp.close();
    
    
    cout<<"\n\nEnter any key to go back";
    char cx;
    cin>>cx;;

    system("clear");
    admin_menu();
    
}



void login(){
    gotoxy(80, 10);
      cout<<"======================================\n";
    gotoxy(80, 11);
    setcolor("magenta");
      cout<<"             SUPER  MARKET\n";
    setcolor("re");
    gotoxy(80, 12);
      cout<<"======================================\n";
    
    gotoxy(94, 15);
    cout<<"===========\n";
    gotoxy(94, 16);
    setcolor("magenta");
    cout<<"|  LOGIN  |\n";
    setcolor("re");
    gotoxy(94, 17);
    cout<<"===========\n";
    gotoxy(80, 21);
    cout<<"login id: ";
    char na[30];
    cin>>na;
    gotoxy(80, 23);
    cout<<"Password: ";
    char pass[30];
    cin>>pass;
    
    if((strcmp(na,"Sameer")==0||strcmp(na,"Suryakant")==0||strcmp(na, "Nimit")==0)&&strcmp(pass,"password")==0)
    {system("clear");
        gotoxy(91, 6);
        setcolor("red");
            cout<<"**Welcome**\n";
        setcolor("re");
        gotoxy(80, 8);
        cout<<"Enter today's date:";
        cin>>dd>>mm>>yy;

    }
            else
            {system("clear");
                gotoxy(88, 6);
                setcolor("red");
        cout<<"**Access Denied**\n";
                setcolor("re");
        login();
    }
    
    system("clear");
    
}






void footer()
{system("clear");
    cout<<"\n\n\n";
    cout<<"             *   *   \n";
    cout<<"MADE With   ***    By: SK, NM, MS\n";
    cout<<"             ***        \n";
    cout<<"               * \n";

}

void admin_menu()
{
    
    int ch2;
    
    gotoxy(94, 11);
    setcolor("magenta");
    cout << "ADMIN MENU\n";
    setcolor("re");
    gotoxy(80, 15);
    cout << "1.ADD PRODUCT\n";
    gotoxy(80, 17);
    cout << "2.SHOW STOCK\n";
    gotoxy(80, 19);
    cout << "3.MODIFY PRODUCT\n";
    gotoxy(80, 21);
    cout << "4.DELETE PRODUCT\n";
    gotoxy(80, 23);
    cout << "5.BACK TO MAIN MENU\n";
    gotoxy(80, 25);
    cout << "Please Enter Your Choice (1-5): ";
    cin>>ch2;
    switch (ch2)
    {
    case 1:
            system("clear");
            setcolor("magenta");
            cout<<"\n\n\t\t\t\tAdding Product";
            setcolor("re");
            write_product();
        
        break;
    case 2:
            system("clear");
            display_all();
            
       
        break;
   
    case 3:
            system("clear");
            modify_product();
       
        break;
    case 4:
            system("clear");
            delete_product();
       
        break;
   
       
       
    case 5:
            system("clear");
            main_menu();
        break;
    default:
            system("clear");
        cout << "Invalid choice";
        admin_menu();
    }
}






void main_menu(){
   int ch;
    
    gotoxy(80, 10);
      cout<<"======================================\n";
    gotoxy(80, 11);
    setcolor("magenta");
      cout<<"             SUPER  MARKET\n";
    setcolor("re");
    gotoxy(80, 12);
      cout<<"======================================\n";
    gotoxy(95, 16);
    setcolor("magenta");
    cout << "MAIN MENU\n";
    setcolor("re");
    gotoxy(80, 20);
    cout << "01. CUSTOMER\n";
    gotoxy(80, 22);
    cout << "02. ADMINISTRATOR\n";
    gotoxy(80, 24);
    cout << "03. EXIT\n";
    gotoxy(80, 26);
    cout << "Please Select Your Option (1-3): ";
    cin>>ch;
    switch (ch)
    {
    case 1:
            system("clear");
            place_order();
        
        break;
    case 2:
            system("clear");
            admin_menu();
        
        break;
    case 3:
            gotoxy(80, 30);
            cout << "ARE YOU SURE, YOU WANT TO EXIT (Y/N)?";
            char yn;
            cin >> yn;
            if ((yn == 'Y') || (yn == 'y'))
            {footer();
                exit(0);
            }
            else
            { system("clear");
                main_menu();}
            break;
                   
    default:
            system("clear");
            gotoxy(80, 30);
        cout << "Invalid choice";
           
            main_menu();
            break;
    }
    
}


int main()
{
    cout<<"Press 1 to start program";
    
    char st;
    st=getchar();
    if(st=='1')
    {system("clear");
    login();
    
        main_menu();
        
    }
    
    else
    {
        system("clear");
        main();
    
    }
   
    
    
}
