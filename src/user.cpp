#include "classes.h"
#include "main.h"
#include "user.h"
#include <iostream>
#include <string>
#include <vector>

void createUser() {             //Create a new user account
    cout<<"User account creation.\nEnter username:";
    string username;
    cin>>username;
    cout<<"Enter password:";
    string password;
    cin>>password;
    user tmp(username, password);
    userArray.push_back(tmp);
    cout<<"Account created with username "<<tmp.getUser()<<" and password "<<tmp.getPass()<<".\n";
}

bool userLogin() {              //Login as user
    cout<<"User login.\nEnter username:";
    string username;
    cin>>username;
    cout<<"Enter password:";
    string password;
    cin>>password;
    for(unsigned i=0; i<userArray.size(); i++){
        user &tmp=userArray[i];
        if(tmp.getUser()==username){
            if (tmp.getPass()==password){
                userPanel(tmp);
                return 1;
            }
        }
    }
    return 0;
}

void userPanel(user& client) {  //User panel with user options
    cout<<"\nWelcome to the User Panel.\n1. Make a reservation.\n2. Check reservations.\n"
        <<"3. Account balance.\n4. Log out.\n";
    char choice;
	cin>>choice;
	switch(choice){
		case '1':
			makeRsv(client);
			break;
		case '2':
			checkRsv(client);
			break;
		case '3':
			accWallet(client);
			break;
        case '4':
			return;
			break;
		default:
			cout<<"Invalid. Try again.\n";
			break;
	}
	userPanel(client);
};

void makeRsv(user& client) {    //Make a reservation
    cout<<"You have chosen to make a reservation. Please choose which:";
    for(unsigned i=0; i<trackArray.size(); i++){
        cout<<"\n"<<i+1<<". ";
        trackArray[i].print_track();
    }
    cout<<endl;
    unsigned choice;
	cin>>choice;
	int aNr=0;
	if(!(choice>0 && choice<=trackArray.size())) {
        cout<<"Invalid choice.\n";
        return;
	} else {
        cout<<"Available seats:";
        for(int i=0; i<10; i++){
            if(trackArray[choice-1].seat_status(i)){
                cout<<i+1<<" ";
            aNr++;
            }
        }
	}
	int nr, pick;
	cout<<"\nHow many seats would you like to reserve?\n";
	cin>>nr;
	if (nr>aNr || nr<1){
        cout<<"Invalid choice.\n";
        return;
	}
	vector<int> orderedSeats;
    for(int i=0; i<nr; i++){
        cout<<"Pick a seat:";
        cin>>pick;
        if(!(trackArray[choice-1].seat_status(pick+1))) {
            cout<<"Invalid choice.";
            i--;
        } else {
            orderedSeats.push_back(pick-1);
        }
    }
    double price=nr*trackArray[choice-1].mMovie->get_price();
    cout<<"Total cost for "<<nr<<" seats is "<<price<<"PLN. Purchase?";
    cout<<"\nPress 1 to cancel order, or anything else to continue.\n";
    cin>>pick;
    if(pick==1) return;
    if(client.getWallet()<price){
        cout<<"Insufficient funds in user account.\n";
        return;
    }
    order tmp(&trackArray[choice-1], orderedSeats);
    client.makeOrder(tmp, price);
    for(unsigned i=0; i<orderedSeats.size(); i++){
        tmp.get_track()->set_seat(orderedSeats[i]);
    }
};

void checkRsv(user& client) {   //Check your reservations
    cout<<"My reservations:\n";
    client.print_orders();
}

void accWallet(user& client) {  //Account balance/deposit to account wallet
    cout<<"Current account balance for user "<<client.getUser()<<" is "<<client.getWallet()<<"PLN.\n";
    cout<<"How much would you like to deposit?\n";
    double money;
    cin>>money;
    client.deposit(money);
    cout<<"New balance is "<<client.getWallet()<<"PLN.\n";
}

