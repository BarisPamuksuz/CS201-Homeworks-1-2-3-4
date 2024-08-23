#ifndef __CUSTOMER_H
#define __CUSTOMER_H
#include <string>
#include "DVD.h"
using namespace std;

class Customer{
public:
    Customer(const int ID, const string name);
    Customer();
    void changeRent(int amount);
    int getRent() const;
    int getID() const;
    string getName() const;
    Customer& operator=( const Customer&);
    DVD* cusRentals;
    
private:
    int ID;
    string name;
    int numRent;
    

};
#endif 
