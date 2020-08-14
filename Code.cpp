#include<iostream>
#include<iomanip>
#include<algorithm>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#include<bits/stdc++.h>
#include<cstdio>
#include<ctype.h>
#include<windows.h>
#include<fstream>
#include<sstream>
#define num 100
int p;
using namespace std;
COORD coord={0,0}; // this is global variable .center of axis is set to the top left cornor of the screen

//CLASSES DECLARATION.
class User{
   private:
      string name;
      string phoneNo;

   public:
      void get_name();     // A FUNCTION TO GET NAME.
      void get_phoneNo();  //A FUNCTION TO GET PHONE NO.

}user;

//A CLASS CUSTOMER INHERITED FROM CLASS USER.
class Customer: public User{
  public:
      void bill();        //A FUNCTION TO CALCULATE BILL.
	  void exit();        //A FUNCTION TO EXIT.
      void selectSlot();  //A FUNCTION TO SELECT SLOT.
}customer;

//A CLASS VENDOR INHERITED FROM CLASS USER
class Vendor: public User{
  public:
      void add();  //A FUNCTION TO ADD ITEMS.
  	  void edit(); //A FUNCTION TO EDIT ITEM DETAILS.
}vendor;

class product{
	public:
           string name;
           int code;
           float rate;
           int quantity;
}item;

class Display{
	public:
		    void d_mainmenuForCustomer(); //A FUNCTION TO DISPLAY MAINMENU FOR CUSTOMER.
		    void d_mainmenuForVendor();   //A FUNCTION TO DISPLAY MAINMENU FOR VENDOR.
            void window(int,int,int,int); //A FUNCTION TO DISPLAY A BOX.
            void display_all();           //A FUNCTION TO DISPLAY ALL ITEMS.
}display;

void check_code(int);
int check_code2(int x);
int check_code1();
void d_search();
void gotoxy(int ,int);  //A FUNCTION TO GO TO SPECIFIC POINT.
int qsearch(string s,string password1);
void dedit(string s,string newname);

void User :: get_name(){

     cout<<"Enter your name :";
     gotoxy(28,25);
	 cin>>name;
}

void User :: get_phoneNo(){

     cout<<"Enter your phone number :";
     gotoxy(28,27);
	 cin>>phoneNo;
}


//A FUNCTION TO GO TO SPECIFIC POINT.
void gotoxy(int x,int y){
    coord.X=x;
    coord.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

//A FUNCTION TO DISPLAY BOX.
void Display::window(int a,int b,int c,int d){

  int i;
  system("cls");
  gotoxy(25,10);
  for (i=1;i<=10;i++) cout<<"-";
  cout<<"-CC-";
  for (i=1;i<=10;i++) cout<<"-";
  cout<<endl<<endl;
  gotoxy(30,11);cout<<"Departmental Store";
  for (i=a;i<=b;i++){

        gotoxy(i,17);cout<<"\xcd";  //TO PRINT VERTICAL LINE.
        gotoxy(i,19);cout<<"\xcd";
        gotoxy(i,c);cout<<"\xcd";
        gotoxy(i,d);cout<<"\xcd";
  }

  gotoxy(a,17);cout<<"\xc9";
  gotoxy(a,18);cout<<"\xba";
  gotoxy(a,19);cout<<"\xc8";
  gotoxy(b,17);cout<<"\xbb";
  gotoxy(b,18);cout<<"\xba";
  gotoxy(b,19);cout<<"\xbc";

  for(i=c;i<=d;i++){

   gotoxy(a,i);cout<<"\xba";  //TO PRINT HORIZONTAL LINE.
   gotoxy(b,i);cout<<"\xba";

  }

  gotoxy(a,c);cout<<"\xc9";
  gotoxy(a,d);cout<<"\xc8";
  gotoxy(b,c);cout<<"\xbb";
  gotoxy(b,d);cout<<"\xbc";
}

//A FUNCTION TO DISPLAY MAINMENU FOR VENDOR.
void Display::d_mainmenuForVendor(){

  int i,n;
  const char *menu[]={"   1.Add Goods","   2.Edit Goods","   3.display All ","   4.Search","   5.Exit"};
  system("cls");
  display.window(25,50,20,32);
  gotoxy(28,18);
  cout<<"MAIN MENU FOR VENDOR"<<endl;
  for (i=0;i<=4;i++){
  gotoxy(28,22+i+1);cout<<menu[i]<<endl;}
  gotoxy(28,30);
  cout<<"Select your choice: ";
  cin>>n;
  switch(n){
  	case 1:
  		vendor.add();
	    break;
	case 2:
		vendor.edit();
	    break;
	case 3:
	    display.display_all();
	    break;
	case 4:
	    d_search();
	    break;
	default:
	    exit(0);
  }
 }

//A FUNCTION TO DISPLAY MAINMENU FOR CUSTOMER.
void Display::d_mainmenuForCustomer(){

  int i,n;
  const char *menu[]={"   1.Calculate Bill","   2.display All ","   3.Search","   4.Exit"};
  system("cls");
  display.window(25,50,20,32);
  gotoxy(28,18);
  cout<<"MAIN MENU(CUSTOMER)"<<endl;
  for (i=0;i<=3;i++){
  gotoxy(28,22+i+1); cout<<menu[i]<<endl;}
  gotoxy(28,30); cout<<"Select your choice: ";
  cin>>n;
  switch(n){
  	case 1:
  		customer.bill();
  		break;
  	case 2:
  		display,display_all();
	    break;
	case 3:
		d_search();
   }
 }



 //A FUNCTION TO REGISTOR.
void registor(){
    string password1,password;
    string user_id;
    system("cls");
    display.window(25,50,20,32); //To display a Box.
	gotoxy(35,18); //To go to a specific point (x,y).
    cout<<"REGISTOR"<<endl;
	gotoxy(28,22);
	cout<<"enter user_id:";
    gotoxy(28,23);
	cin>>user_id;
    gotoxy(28,24);
    user.get_name();

    gotoxy(28,26);
    user.get_phoneNo();
    gotoxy(28,28);
	cout<<"enter password:";
	gotoxy(28,29);
	cin>>password;
	gotoxy(28,30);
	cout<<"re_enter password:";
    gotoxy(28,31);
	cin>>password1;

    if(password==password1){

        fstream file("rec0.txt",ios::in|ios::out|ios::app);
        file<<user_id<<endl<<password<<endl;
        gotoxy(28,26);  cout<<"registered "<<endl;
        file.close();
    }
    else{

        gotoxy(28,26);
        cout<<"wrong password,register again"<<endl;
        registor();
    }
}

//A FUNCTION TO SEARCH PASSWORD.
int qsearch(string s,string password1){
    string isearch ;
    isearch=s;
    int offset;
    string line,password;
    fstream file;
    file.open("rec0.txt",ios::in|ios::out);
    file.seekg(0,ios::beg);
    if(file.is_open()){
            while(!file.eof()){
                getline(file,line);
                if((offset=line.find(isearch,0))!=string::npos){
                    file>>password;
                    if(password==password1) {
					          return 1;}
                    else return 0;
    }}}
    file.close();
    return 0;
}

//A FUNCTION FOR LOGIN.
int login(){
    system("cls");
    string user_id,password;
    display.window(25,50,20,32);
	gotoxy(35,18);  cout<<"LOGIN";
	gotoxy(28,23);  cout<<"enter user_id:";
    cin>>user_id;
    gotoxy(28,24);  cout<<"enter password:";
	cin>>password;
	gotoxy(28,25);
	cout<<"Select your choice: ";

   if(qsearch(user_id,password)){
        gotoxy(28,26);  cout<<"logged in"<<endl;
        return 1;
   }
   else{
        gotoxy(28,27);  cout<<"login unsuccessful"<<endl;
        return 0;
    }
}


//A  FUNCTION TO CHECK VALIDITY OF CODE WHILE EDITING , ADDING.
int check_code2(int x){
    int flag=1;
    fstream file;
    file.open("record3.txt",ios::in|ios::out);
    system("cls");
    string temp;
    stringstream ss;
    ss<<x;
    string s;
    ss>>s;
    int offset;
    while(!file.eof()){
  	  getline(file,temp);
  	  if((offset=temp.find(s,0))!=string::npos){
  		flag=0;
   }   }
  return flag;
}

//A FUNCTION TO CHECK AVAILABILITY OF CODE.
void check_code(int x){
   int flag;
   fstream file;
   file.open("record3.txt",ios::in|ios::out);

   while(1){
      system("cls");
      display.window(20,58,23,36);
      gotoxy(32,18); cout<<" ADD ARTICLES ";
      flag=1;
      string temp;
      stringstream ss;
      gotoxy(22,25); cout<<"Enter new code of the article:";
      ss<<x;
      string s;
      ss>>s;
      int offset;
      while(!file.eof()){
  	     getline(file,temp);
  	  if((offset=temp.find(s,0))!=string::npos){
  		flag=0;
  		gotoxy(26,30); cout<<"Code aleady exits.";
  		gotoxy(29,32); cout<<"Enter again : ";
  		getch();
  		break;
	  }
  }
  if (flag==1)
   break;
 }
}

//A FUNCTION TO CHECK AVAILABILITY OF CODE.
int check_code1(){
   int flag;
   int x;
   fstream file;
   file.open("record3.txt",ios::in|ios::out);

   while(1){
      system("cls");
      display.window(20,58,23,36);
      gotoxy(32,18);  cout<<" ADD ARTICLES ";
      flag=1;
      string temp;
      stringstream ss;
      gotoxy(22,25);  cout<<"Enter new code of the article:";
      cin>>x;
      ss<<x;
      string s;
      ss>>s;
      int offset;
      while(!file.eof()){
  	     getline(file,temp);
  	  if((offset=temp.find(s,0))!=string::npos){
  		flag=0;
  		gotoxy(26,30); cout<<"code already exits";
  		gotoxy(29,32); cout<<"enter again";
  		getch();
  		break;
	  }
  }
  if (flag==1)
   break;
 }
 return x;
}

//A function to display all items.
void Display :: display_all()
{
  system("cls");
  int k;
  gotoxy(25,10);
  for (k=1;k<=10;k++) cout<<"-";
  cout<<"-CC-";
  for (k=1;k<=10;k++) cout<<"-";
  cout<<endl<<endl;
  gotoxy(30,11);cout<<"Departmental Store";
  gotoxy(32,15);cout<<"CUSTOMER'S BILL";
  gotoxy(22,16);cout<<"SN.";
  gotoxy(25,16);cout<<"Id";
  gotoxy(31,16);cout<<"Item Name";
  gotoxy(42,16);cout<<"Quantity";
  gotoxy(53,16);cout<< "Rate";
  cout<<endl;
  int i=17;
  fstream file("record3.txt",ios::in|ios::out|ios::app);
    	string isearch,line ,password;
    	int offset;
    	file.seekg(0,ios::beg);
    while(!file.eof()&&i<17+num){
  	string line1,line2,line3,line4;
    getline(file,line1);
    getline(file,line2);
    getline(file,line3);
    getline(file,line4);
    gotoxy(22,i);  cout<<i-16;
    gotoxy(25,i);  cout<<line1;
    gotoxy(31,i);  cout<<line2;
    gotoxy(42,i);  cout<<line3;
    gotoxy(53,i);  cout<<line4;
    cout<<endl;
    i++;
  }
getch();
if(p==1) display.d_mainmenuForCustomer();
else display.d_mainmenuForVendor();
}


//A FUNCTION TO SEARCH AN ITEM BY CODE.
void d_search(){
    int x;
    system("cls");
	gotoxy(25,23); cout<<"enter item code: ";
    cin>>x;
    int flag=check_code2(x);
    gotoxy(25,30);
    fstream file("record3.txt",ios::in|ios::out|ios::app);
    if(flag==0){
       item.code=x;
       stringstream ss;
       string s;
       ss<<item.code;
       ss>>s;
       int i=0;
       int offset;
       string isearch,line,password;
       file.seekg(0,ios::beg);{

    while(!file.eof()&&i<num){
        i++;
        getline(file,line);
        if(offset=line.find(s,0)!=string::npos){

            file>>item.name;
            file>>item.rate;
            file>>item.quantity;
           gotoxy(25,27);  cout<<"name       = "<<item.name;
           gotoxy(25,28);   cout<<"code       = "<<item.code;
           gotoxy(25,29);   cout<<"quantity      = "<<item.rate;
           gotoxy(25,30);   cout<<"rate   = "<<item.quantity;
            break;
        }
    }
}
}
getch();
if(p==1) display.d_mainmenuForCustomer();
else display.d_mainmenuForVendor();
}


void Customer :: bill()
{
  int x;
  int j=29,q=0,size=0,i=1;
  float total=0,gtotal=0;
  fstream file;
  file.open("record3.txt",ios::in|ios::out);
  system("cls");
  int k;
  gotoxy(25,10);
  for (k=1;k<=10;k++) cout<<"-";
  cout<<"-CC-";
  for (k=1;k<=10;k++) cout<<"-";
  cout<<endl<<endl;
  gotoxy(30,11);cout<<"Departmental Store";
  gotoxy(32,25);cout<<"CUSTOMER'S CART";
  gotoxy(13,27);cout<<"SN. ";
  gotoxy(16,27);cout<<"Item Name";
  gotoxy(28,27);cout<<"Quantity";
  gotoxy(39,27);cout<<"Rate";
  gotoxy(50,27);cout<<"Total";
  gotoxy(26,15);
  cout<<"enter 0 to finish input";
  while(1){
  gotoxy(25,18);
  cout<<"                    ";
  gotoxy(25,19);
  cout<<"                    ";
  gotoxy(25,18);
  cout<<"enter item code:";
  cin>>x;
  if(x==0)
   break;
  gotoxy(25,19);
  cout<<"enter quantity:";
  cin>>q;

    string line;
    int offset;
    stringstream ss;
    string s;
    ss<<x;
    ss>>s;
    int j;
    file.seekg(0,ios::beg);
    if(file.is_open()){

    while(!file.eof()){
 	  getline(file,line);
 	  if((offset=line.find(s,0))!=string::npos){
	      item.code=x;
 		file>>item.name;
 		file>>item.rate;
        file>>item.quantity;
 		 		break;
	 }}}


    total=item.rate*q;
    gotoxy(13,27+i);cout<<i;
    gotoxy(16,27+i);cout<<item.name;
    gotoxy(28,27+i);cout<<q;
    gotoxy(39,27+i);cout<<item.rate;
    gotoxy(50,27+i);cout<<total;
    cout<<endl;
    q=item.quantity-q;
    j=j+2;
    i++;
    if(q>=0)
    { gtotal=gtotal+total;

    file.seekg(0,ios::beg);
    stringstream q1,uu;
    string u,qq;
    uu<<item.quantity;
    uu>>u;
    q1<<q;
    q1>>qq;
    if(file.is_open()){

    while(!file.eof()){
 	string line;
 	getline(file,line);

 	if((offset=line.find(s,0))!=string::npos)
 	{   item.code=x;
 		file>>item.name;
     	break;
	 }}}
  }
  else
    cout<<"no stock"<<endl;
  }
 if(gtotal!=0){
  gotoxy(30,j+5);
  printf("TOTAL AMOUNT = Rs. ");
  printf("%6.2f",gtotal);
}
gotoxy(30,j+7);

cout<<"Select your payment mode";
gotoxy(30,j+8);
cout<<"1.Pay on Delivery";
gotoxy(30,j+9);
cout<<"2.Pay by Card.";
int z;
gotoxy(30,j+10);
cin>>z;
if(z==1)
    customer.selectSlot();
else if(z==2){
        string accNo,CVVno,expiryDate,OTP;
    gotoxy(30,j+10);
    cout<<"Please enter your Account No. : ";
    cin>>accNo;
    gotoxy(30,j+11);
    cout<<"Please enter Expiry Date : ";
    cin>>expiryDate;
    gotoxy(30,j+12);
    cout<<"Please enter CVVno : ";
    cin>>CVVno;
    gotoxy(30,j+13);
    cout<<"Please enter OTP : ";
    cin>>OTP;
    customer.selectSlot();
}
 file.close();
 getch();
 display.d_mainmenuForCustomer();
}


//A FUNCTION TO SELECT SLOT.
 void Customer :: selectSlot(){
  system("cls");
  gotoxy(30,23);
  cout<<"1. 12pm - 2pm";
  gotoxy(30,24);
  cout<<"2. 6pm - 8pm";
  gotoxy(30,25);
  cout<<"Please select a slot : ";
  int n;
  cin>>n;
  system("cls");
  gotoxy(30,23);
  cout<<"Slot selected.";
  gotoxy(30,25);
  cout<<"Your order will be delivered in selected slot.";
  gotoxy(30,27);
  cout<<"THANK YOU!!!";
 }


//A FUNCTION TO ADD RECORDS.
void Vendor::add (){
    string y;
    int x;
    system("cls");
    gotoxy(25,25); cout<<"Enter new record(Y/N)?";
    while(toupper(getche())=='Y'){
       system("cls");
       fstream file("record3.txt",ios::in|ios::out|ios::app);
       item.code=check_code1();
       gotoxy(22,27);
       gotoxy(22,28); cout<<"Enter rate of the item:";
       cin>>item.rate;
       gotoxy(22,30); cout<<"Enter quantity of the item:";
       cin>>item.quantity;
       gotoxy(22,32); cout<<"Enter name of the item:";
       cin>>item.name;

    file<<item.code<<endl<<item.name<<endl<<item.quantity<<endl<<item.rate<<endl;
    file.close();

    gotoxy(22,34); cout<<"Enter new record(Y/N)?";
 }
   display.d_mainmenuForVendor();
}

//A FUNCTION TO EDIT.
void dedit(string s,string newname){

 ostringstream text;
    ifstream in_file("record3.txt");

    text << in_file.rdbuf();
    string str = text.str();
    string str_found = s;
    string str_replace = newname;
    size_t pos = str.find(str_found);
    str.replace(pos, string(str_found).length(), str_replace);
    in_file.close();

    ofstream out_file("record3.txt");
    out_file << str;
}


//A FUNCTION TO EDIT DETAILS OF ITEMS.
void Vendor::edit(){
 int flag=0;
 int x,k,choice;
 string new1;
 fstream file("record3.txt",ios::in|ios::out|ios::app);
 int size;
 system("cls");
 display.window(20,63,20,46);
 gotoxy(35,18);
 cout<<"EDIT RECORDS";
 gotoxy(25,23);
 cout<<"enter item code: ";
 cin>>x;
 flag=check_code2(x);
 if(flag==0){
 item.code=x;

  stringstream ss;
   string s;
   ss<<item.code;
 ss>>s;

   int offset;
 string isearch,line,password;
 file.seekg(0,ios::beg);
 if(file.is_open())
{
 while(!file.eof()){
 	getline(file,line);
if((offset=line.find(s,0))!=string::npos)
 	{
 		file>>item.name;
 		file>>item.rate;
 		file>>item.quantity;
 		break;
	 }}}
 gotoxy(25,27);
 cout<<"name       = "<<item.name;
 gotoxy(25,28);
 cout<<"code       = "<<item.code;
 gotoxy(25,29);
 cout<<"rate       = "<<item.rate;
 gotoxy(25,30);
 cout<<"quantity   = "<<item.quantity;
 gotoxy(25,32);;
 cout<<"do you want to edit this record(y/n):";
 if(toupper(getch())=='Y'){
     gotoxy(25,34);
     cout<<"1- edit name ";
     gotoxy(25,35);
    cout<<"2- edit code ";
     gotoxy(25,36);
     cout<<"3- edit rate ";
     gotoxy(25,37);
     cout<<"4- edit quantity ";
     gotoxy(25,39);  ;
     cout<<" Enter your choice(1, 2, 3, 4) ";
     cin>>choice;
     switch(choice){
      case 1:
       {
           system("cls");
       display.window(23,48,20,40);
       gotoxy(35,18);
       cout<<"EDIT RECORDS";
       gotoxy(25,24);
       cout<<" enter new name: ";
       cin>>new1;
       gotoxy(27,30);
       cout<<"Item edited";
       file.seekg(0,ios::beg);
    k=1;

 if(file.is_open())
{
while((!file.eof())){
    getline(file,line);
 	if((offset=line.find(s,0))!=string::npos)
 	{file>>isearch;
        dedit(isearch,new1);
        break;
   }
	 }}break;
     case 2:
      {
 system("cls");
       display.window(23,65,20,40);
       gotoxy(35,18);
       cout<<"EDIT RECORDS";
       gotoxy(25,24);
       check_code(x);
       item.code=x;
      cout<<"enter newcode"<<endl;
       cin>>new1;
       gotoxy(27,30);
       cout<<"Item edited";
    if(file.is_open())
{file.seekg(0,ios::beg);

while(!file.eof()&&k){
 	getline(file,line);
 	if((offset=line.find(s,0))!=string::npos)
 	{
        dedit(s,new1);
        break;
 	}
	 }
       }break;
      case 3:
       {ss<<item.rate;
        ss>>s;
           system("cls");
       display.window(23,65,20,40);
       gotoxy(35,18);
       cout<<"EDIT RECORDS";
       gotoxy(25,24);
       cout<<" enter new rate: ";
       cin>>new1;
       gotoxy(27,30);
       cout<<"Item edited";
       if(file.is_open()){
       file.seekg(0,ios::beg);
       while(!file.eof()&&k){
    	getline(file,line);
 	   if((offset=line.find(s,0))!=string::npos){
		 file>>isearch;
 	     file>>isearch;

 	    dedit(isearch,new1);
 	    break;
 		 }}}}break;
       case 4:
       {
       system("cls");
       display.window(23,65,20,40);
       gotoxy(35,18);
       cout<<"EDIT RECORDS";
       gotoxy(25,24);
       cout<<" enter new quantity: ";
       cin>>new1;
       gotoxy(27,30);
       cout<<"Item edited";
    file.seekg(0,ios::beg);
    if(file.is_open()){
      while(!file.eof()&&k){
 	    getline(file,line);
 	    if((offset=line.find(s,0))!=string::npos){
        file>>isearch;
 	    file>>isearch;
 	    file>>isearch;
        dedit(isearch,new1);
        break;
        }}}}
        break;
      }
      gotoxy(27,30);
      cout<<"--- item edited---";
      break;
  }}}
  if (flag==1){
   gotoxy(32,30);
   cout<<"item does not exist";
   gotoxy(36,32);
   cout<<"TRY AGAIN";
  }
   getch();
   file.close();
   display.d_mainmenuForVendor();
  }
}


//START OF MAIN FUNCTION.
int main(){
    display.window(25,50,20,32); //To display a Box.
	gotoxy(35,18); //To go to a specific point (x,y).
    cout<<"WELCOME";
	gotoxy(28,23);  cout<<"Enter 1 for Customer.";
	gotoxy(28,24);  cout<<"Enter 2 for Vendor.";
	gotoxy(28,25);  cout<<"Select your choice: ";
	cin>>p;
	if(p==1){
          system("cls");
          display.window(25,50,20,32);
	gotoxy(30,18);
    cout<<"Signup /Login"<<endl;
    gotoxy(28,23);  cout<<"Enter 1 to register.";
	gotoxy(28,24);  cout<<"Enter 2 to Login";
	gotoxy(28,25);  cout<<"Select your choice: ";
	int m;
	cin>>m;

	if(m==1){
            registor();
	        int l=0;
	        while(!l){
	           l=login();
               gotoxy(28,28);
           }
	    }
	    else if(m==2){
	        int l=0;
	        while(!l)
            l=login();
            gotoxy(28,28);
        }
        display.d_mainmenuForCustomer();}

	else if(p==2){
	   int l=0;
       while(!l)
            l=login();
	display.d_mainmenuForVendor();
	}
	return 0;
}
