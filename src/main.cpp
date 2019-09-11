#include "classes.h"
#include "main.h"
#include "admin.h"
#include "user.h"
#include <iostream>
#include <vector>

using namespace std;

vector<admin> adminArray;
vector<user> userArray;
vector<movie> movieArray;
vector<track> trackArray;

void terminal(){                //Initial terminal
	cout<<"Welcome to the Cinema!\n";
	cout<<"1. Create account\n2. Administrator login\n3. User login\n";
	chooseLogin();
	cout<<"\n";
}

void chooseLogin(){             //Choose what to login as/create a new account
	char choice;
	cin>>choice;
	switch(choice){
		case '1':
			createAccount();
			break;
		case '2':
			if(!adminLogin()) cout<<"Invalid username or password.\n";
			break;
		case '3':
			if(!userLogin()) cout<<"Invalid username or password.\n";
			break;
		default:
			cout<<"Invalid. Try again.\n";
			chooseLogin();
			break;
	}
}

void createAccount() {          //Create account panel
	cout<<"Account creation. Press 1 for administrator, 2 for user, 3 to exit.\n";
	char one;
	cin>>one;
	switch(one){
		case '1':
			createAdmin();
			break;
		case '2':
			createUser();
			break;
		case '3':
			return;
			break;
		default:
			cout<<"Invalid. Try again.\n";
			createAccount();
			break;
	}
}

int main(){
	while(1) terminal();
	return 0;
}
