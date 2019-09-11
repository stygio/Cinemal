#include "classes.h"
#include "main.h"
#include "admin.h"
#include "user.h"
#include <iostream>
#include <string>
#include <vector>

void createAdmin() {            //Create a new admin account
	string key;
	cout<<"Administrator account creation.\nEnter admin account creation key:";
	cin>>key;
	if(!admin::checkKey(key)) {
		cout<<"Invalid key.\n";
		return;
	} else {
		cout<<"Enter username:";
		string username;
		cin>>username;
		cout<<"Enter password:";
		string password;
		cin>>password;
		admin tmp(username, password);
		adminArray.push_back(tmp);
		cout<<"Account created with username "<<tmp.getUser()<<" and password "<<tmp.getPass()<<".\n";
	}
}

bool adminLogin() {             //Login as admin
    cout<<"Administrator login.\nEnter username:";
    string username;
    cin>>username;
    cout<<"Enter password:";
    string password;
    cin>>password;
    for(unsigned i=0; i<adminArray.size(); i++){
        admin &tmp=adminArray[i];
        if(tmp.getUser()==username){
            if (tmp.getPass()==password){
                adminPanel();
                return 1;
            }
        }
    }
    return 0;
}

void adminPanel() {             //Admin terminal with admin options
    cout<<"\nWelcome to the Admin Panel.\n1. Add movie.\n2. Adjust movie price.\n"
        <<"3. Add track.\n4. Remove track.\n5. Check orders.\n6. Log out.\n";
    char choice;
	cin>>choice;
	switch(choice){
		case '1':
			addMovie();
			break;
		case '2':
			changePrice();
			break;
		case '3':
			addTrack();
			break;
        case '4':
			removeTrack();
			break;
        case '5':
			checkOrders();
			break;
		case '6':
			return;
			break;
		default:
			cout<<"Invalid. Try again.\n";
			break;
	}
	adminPanel();
};

unsigned chooseMovie() {        //Utility function for listing available movies
    cout<<"\nPlease choose a movie:\n";
    for(unsigned i=0; i<movieArray.size(); i++){
        cout<<i+1<<". "<<movieArray[i].get_title()<<"\n";
    }
    unsigned choice;
	cin>>choice;
	return choice-1;
}

void addMovie() {               //Add a movie
    char input[100];
    int length;
    double price;
    cout<<"You have chosen to add a movie.\nEnter movie title:";
    cin.ignore();
    cin.getline(input,sizeof(input));
    string title(input);
    cout<<"Enter movie price:";
    cin>>price;
    cout<<"Enter movie length (minutes):";
    cin>>length;
    movie tmp(title, price, length);
    movieArray.push_back(tmp);
    cout<<"You added a movie. ";
    movieArray.back().print_movie();
}

void changePrice(){             //Change an existing movie's price
    unsigned choice=chooseMovie();
    cout<<"Current price of "<<movieArray[choice].get_title()<<" is "<<movieArray[choice].get_price()<<". Enter new price:";
	double price;
	cin>>price;
	movieArray[choice].change_price(price);
}

void addTrack() {               //Add a track
    int hour, minute, day, month, year, roomNr;
    cout<<"You have chosen to add a track.";
    unsigned choice=chooseMovie();
    cout<<"Choose a time.\nHour:";
    cin>>hour;
    cout<<"Minute:";
    cin>>minute;
    cout<<"Choose a date.\nDay:";
    cin>>day;
    cout<<"Month:";
    cin>>month;
    cout<<"Year:";
    cin>>year;
    cout<<"Choose a room (1-20):";
    cin>>roomNr;
    track tmp(&movieArray[choice], roomNr, hour, minute, day, month, year);
    trackArray.push_back(tmp);
    trackArray.back().print_track();
    cout<<endl;
}

void removeTrack() {            //Remove a track
    cout<<"You have chosen to remove a track. Please choose which:";
    for(unsigned i=0; i<trackArray.size(); i++){
        cout<<"\n"<<i+1<<". ";
        trackArray[i].print_track();
    }
    cout<<endl;
    unsigned choice;
	cin>>choice;
	if(choice>0 && choice<=trackArray.size())  trackArray.erase(trackArray.begin()+choice-1);
	else cout<<"Invalid choice.\n";
}

void checkOrders() {            //Check all user's orders
    cout<<"User orders:\n";
    for(unsigned i=0; i<userArray.size(); i++){
        cout<<"User "<<userArray[i].getUser()<<" has the following orders:";
        userArray[i].print_orders();
    }
}
