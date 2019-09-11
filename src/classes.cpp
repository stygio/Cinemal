#include <iostream>
#include <string>
#include <stdio.h>
#include <sstream>
#include <vector>
#include "classes.h"

using namespace std;

void user::pay(double money) { wallet-=money; };
void user::deposit(double money) { wallet+=money; };
void user::makeOrder(order& tmpOrder, double price){
    pay(price);
    orders.push_back(tmpOrder);
}
void user::print_orders() {
    if(orders.size()==0) cout<<"No reservations on this account.";
    for(unsigned i=0; i<orders.size(); i++){
        cout<<i+1<<". ";
        orders[i].get_track()->print_track();
        cout<<"\nReserved seats:";
        orders[i].print_seats();
        cout<<endl;
    }
}

const string date::print_date() const{
    stringstream ss;
    ss<<day<<"/"<<month<<"/"<<year;
    const string out = ss.str();
    return out;
}

const string time::print_length() const{
    stringstream ss;
    ss<<hour; ss<<"h"; ss<<minute; ss<<"min";
    const string out = ss.str();
    return out;
}
const string time::print_time() const{
    stringstream ss;
    ss<<hour; ss<<":"; ss<<minute;
    const string out = ss.str();
    return out;
}

void movie::print_movie(){
    cout<<title<<" has a runtime of "<<print_length()<<" and costs "<<price<<"PLN."<<endl;
}
void movie::change_price(double new_price){ price=new_price; }

void track::print_track(){
    mMovie->print_movie();
    cout<<"The screening is at "<<print_time()<<" on "<<print_date()<<" in room "<<get_room()<<".";
}

void order::print_seats(){
    for(unsigned i=0; i<orderedSeats.size(); i++){
        cout<<orderedSeats[i]+1<<" ";
    }
}
