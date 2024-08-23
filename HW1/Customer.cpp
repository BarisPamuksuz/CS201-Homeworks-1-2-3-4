#include <iostream>
using namespace std;
#include "Customer.h"

Customer::Customer(const int iD, const string nAme){
    ID = iD;
    name = nAme;
    numRent = 0;
    cusRentals = nullptr;
}
Customer::Customer(){
    ID = 0;
    name = "";
    numRent = 0;
    cusRentals = nullptr;
}
void Customer::changeRent(int amount){
    numRent += amount;
}
int Customer::getID() const{
    return ID;
}
string Customer::getName() const{
    return name;
}
int Customer::getRent() const{
    return numRent;
}
Customer& Customer::operator=(const Customer& RCustomer){
    this->ID = RCustomer.getID();
    this->name = RCustomer.getName();
    this->numRent = RCustomer.getRent();
    delete[] cusRentals;
    if(RCustomer.getRent()>0){
        cusRentals = new DVD[numRent];
        for(int i = 0; i < numRent; i++){
            cusRentals[i] = RCustomer.cusRentals[i];
        }
    }else{
        cusRentals = nullptr;
    }
    return *this;
}

