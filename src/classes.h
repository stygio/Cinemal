#ifndef CLASSES
#define CLASSES

#include <iostream>
#include <string>
#include <stdio.h>
#include <sstream>
#include <vector>

using namespace std;

static const string adminKey="sudo";

class order;        //Forward declaration for user class

class admin{        //Admin class for administrators. Includes key checking.
private:
	string username;
	string password;

public:
	admin(string u, string p): username(u), password(p) { }
    static bool checkKey(string key) { return adminKey==key; }
    string getUser() { return username; }
    string getPass() { return password; }

};

class user{         //User class for clients. Includes a wallet, order function and order history
private:
	string username;
	string password;
	double wallet;
	vector<order> orders;

	void pay(double money);

public:
	user(string u, string p): username(u), password(p) { wallet=0; }
	void deposit(double money);
	double const getWallet() const { return wallet; }
	string getUser() { return username; }
    string getPass() { return password; }
    void makeOrder(order& tmpOrder, double price);
    void print_orders();

};

class date{         //Date class
private:
	int day, month, year;

public:
	date(int d, int m, int y): day(d), month(m), year(y) { }
	const string print_date() const;

};

class time{         //Time class offers functionality for time of day/movie length
private:
	int hour, minute;

public:
	time(int h, int m): hour(h), minute(m) { }
	time(int m) {
        hour=m/60;
        minute=m-(hour*60);
	}
	const string print_length() const;
	const string print_time() const;

};

class seat{         //Stores status of seats
private:
    bool status;

public:
    seat() {status=0;}
    bool get_status() {return status;}
    void set_status() { status=1; }

};

class room{         //Room instance for particular track with room# and seats
private:
	int roomNr;
	seat seats[10];

public:
    room(int num): roomNr(num) {}
    int get_room() { return roomNr; }
    bool seat_status(unsigned seatNr) { return seats[seatNr].get_status()==0; }
    void set_seat(int s) { seats[s].set_status(); }
};

class movie: public time{       //Inheritance allows ease of storing movie length
private:
	string title;
	double price;

public:
	movie(string title, double price, int minutes): time(minutes), title(title), price(price) { }

	void print_movie();
	string get_title(){ return title; }
	double get_price(){ return price; }
    void change_price(double new_price);
};

class track: public time, public date, public room{     //Track stores information about an instance of a movie screening
public:
    movie* mMovie;

	track(movie* mM, int rNr, int h, int m, int d, int m2, int y):
	    time(h, m), date(d, m2, y), room(rNr), mMovie(mM) {}
    void print_track();

};

class order{        //Used for order processing
private:
	track* mTrack;
	vector<int> orderedSeats;
	int orderId;

	order(){}	//orders only available via parametrized order method

public:
    order(track* mT, vector<int> oS): mTrack(mT), orderedSeats(oS) {}
    track* get_track() { return mTrack; };
    void print_seats();
};

#endif // CLASSES
