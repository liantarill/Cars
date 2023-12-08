#include<iostream>
#include<fstream>
#include<string.h>
using namespace std;


void login();
void registration();


void Login(){


	int input;
	cout << "                                                      " << endl;
	cout << "\t\t\t\t    db       .d88b.   d888b  d888888b d8b   db" << endl;
	cout << "\t\t\t\t    88      .8P  Y8. 88' Y8b   `88'   888o  88" << endl;
	cout << "\t\t\t\t    88      88    88 88         88    88V8o 88" << endl;
	cout << "\t\t\t\t    88      88    88 88  ooo    88    88 V8o88" << endl;
	cout << "\t\t\t\t    88booo. `8b  d8' 88. ~8~   .88.   88  V888" << endl;
	cout << "\t\t\t\t    Y88888P  `Y88P'   Y888P  Y888888P VP   V8P" << endl;
	cout << "\t\t\t\t        P         A         G          E      " << endl;
	cout << "\n\n\n\n                                              " << endl;

	
	cout << "\t\t\t\t\t\t    1. LOGIN           "<< endl;
	cout << "\t\t\t\t\t\t   2. REGISTER         "<< endl;
	cout << "\t\t\t\t\t\t     3. EXIT           "<< endl<<endl;
	
	cout << "\t\t\t\t\t Please Enter your choice :  ";
	cin >> input;

	switch(input){
		case 1:
			login();
			break;
			
		case 2:
			registration();
			break;
			
		case 3:
			system("cls");
			cout << "THANKYOU!! \n";
			exit(0);
			
		default:
			system("cls");
			cout << "     Wrong input, please input the option \n";
			Login();
	}
	
	
}



void login(){
	string userId, Password, id, pass;
	system("cls");
	
	cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n";
	cout << "\t\t\t\t\t   Enter Your Username And Password !" << endl;
	cout << "\t\t\t\t\t           USERNAME : ";
	cin >> userId;
	cout << "\t\t\t\t\t           PASSWORD : ";
	cin >> Password;
	
	ifstream data("UserGame.txt");
	
	while(data>>id>>pass){
		if(id==userId && pass==Password){
			system("cls");
		}
		else{
			system("cls");
			cout << "LOGIN ERROR \nPlease check your username and password \n";
			Login();
		}
	}
}

void registration(){
	string regId, regPassword, regid, regpass;
	system("cls");
	cout << "Enter Username : ";
	cin >> regId;
	cout << "Enter Password : ";
	cin >> regPassword;
	
	ofstream f1("UserGame.txt", ios::app);
	f1<<regId<<' '<<regPassword<<endl;
	system("cls");
	cout << "Registration succsessfull!!";
	Login();
}
