#include <iostream>
using namespace std;
#include "DVDStoreManagementSystem.h"
#include "DVD.h"
#include "Customer.h"

DVDStoreManagementSystem::DVDStoreManagementSystem(){
    DVDArrSize = 0;
    DVDArr = nullptr;
    customerArrSize = 0;
    customerArr = nullptr;
    transActSize = 0;
    transactionHist = nullptr;
}
void DVDStoreManagementSystem::addDVD( const string serialNo, const string title, const string director ){
    bool isContain = false;
    DVD dvdNew(serialNo, title, director);
    if( DVDArr == nullptr){
        DVDArr = new DVD[1];
        DVDArr[0] = dvdNew;
        DVDArrSize+=1;
        cout << "DVD with serial number "<< serialNo << " successfully added."<< endl;
        return;
    }
    else{
        for(int i = 0; i < DVDArrSize; i++){
            if(DVDArr[i].getSerialNum() == serialNo){
                isContain = true;
            }
        }
    }
    if(isContain == true){
        cout << "Cannot add DVD. DVD with serial number " << serialNo << " already exists."<< endl;
    }
    else{
        DVD* newArr = new DVD[DVDArrSize+1];
        for(int k = 0; k < DVDArrSize; k++){
            newArr[k] = DVDArr[k];
        }
        newArr[DVDArrSize] = dvdNew;
        delete[] DVDArr;
        DVDArr = newArr;
        DVDArrSize+=1;
        cout << "DVD with serial number "<< serialNo << " successfully added."<< endl;
    }  
}
void DVDStoreManagementSystem::removeDVD(const string serialNo){
    bool isContain = false;
    int index = 0;
    string status = "";
    for(int i = 0; i < DVDArrSize; i++){
        if(DVDArr[i].getSerialNum() == serialNo){
            isContain = true;
            status = DVDArr[i].getStatus();
            index = i;
        }
    }
    if(isContain == true && status == "Available"){
        if(DVDArrSize>1){
            DVD* newArr = new DVD[DVDArrSize-1];
            for(int i = 0; i < index; i++){
                newArr[i] = DVDArr[i];
            }
            for(int i = index+1; i < DVDArrSize; i++){
                newArr[i-1] = DVDArr[i];
            }
            delete[] DVDArr;
            DVDArr = newArr;
            DVDArrSize+= -1;
            cout<<"DVD with serial number "<<serialNo<<" successfully removed."<<endl;
        }else{
            delete[] DVDArr;
            DVDArr = nullptr;
            DVDArrSize+=-1;
            cout<<"DVD with serial number "<<serialNo<<" successfully removed."<<endl;
        }
    }else{
        if(isContain == false){
            cout<<"Cannot remove DVD. DVD with serial number "<< serialNo <<" not found."<<endl;
        }
        if(status == "Rented"){
            cout<<"Cannot remove DVD. DVD with serial number "<< serialNo <<" is currently rented by a customer."<<endl;
        }
    }
}
void DVDStoreManagementSystem::addCustomer(const int customerID, const string name){
    bool isContain = false;
    Customer newCus(customerID, name);
    if(customerArr == nullptr){
        customerArr = new Customer[1];
        customerArrSize+=1;
        customerArr[0] = newCus;
        cout << "Customer with ID "<< customerID << " successfully added."<< endl;
        return;
    }
    else{
        for(int i = 0; i < customerArrSize; i++){
            if(customerArr[i].getID() == customerID){
                isContain = true;
            }
        }
    }
    if(isContain == true){
        cout << "Cannot add customer. Customer with ID " << customerID << " already exists."<< endl;
    }
    else{
        Customer* newArr = new Customer[customerArrSize+1];
        for(int k = 0; k < customerArrSize; k++){
            newArr[k] = customerArr[k];
        }
        newArr[customerArrSize] = newCus;
        for(int i = 0; i<customerArrSize;i++){
            delete[] customerArr[i].cusRentals;
        }
        delete[] customerArr;
        customerArr = newArr;
        customerArrSize+=1;
        cout << "Customer with ID "<< customerID << " successfully added."<< endl;
    }
    
}
void DVDStoreManagementSystem::removeCustomer(const int customerId){
    
    bool isContain = false;
    int targetIndex = 0;
    
    for(int i = 0; i < customerArrSize; i++){
        if(customerArr[i].getID() == customerId){
            isContain = true;
            targetIndex = i;
        }
    }
    if(isContain == false){
        cout << "Cannot remove customer. Customer with ID "<< customerId << " not found."<< endl;
    }
    else{
        if(customerArr[targetIndex].getRent() >= 1){
            cout << "Cannot remove customer. Customer with ID "<< customerId << " has rented DVDs." << endl;
        }
        else{
            if(customerArrSize > 1){
                Customer* newArr = new Customer[customerArrSize-1];
                for(int i = 0; i < targetIndex; i++){
                    newArr[i] = customerArr[i];
                }
                for(int i = targetIndex+1; i < customerArrSize; i++){
                    newArr[i-1] = customerArr[i];
                }
                for(int i = 0; i<customerArrSize;i++){
                    delete[] customerArr[i].cusRentals;
                }
                delete[] customerArr;
                customerArr = newArr;
                customerArrSize-=1;
                cout << "Customer with ID "<< customerId << " successfully removed."<<endl;
            }else{
                delete[] customerArr;
                customerArr = nullptr;
                customerArrSize-=1;
                cout << "Customer with ID "<< customerId << " successfully removed."<<endl;
            }
        }
    }
}
void DVDStoreManagementSystem::rentDVD(const int customerID, const string serialNo){
    bool isDvdThere = false;
    bool isCusThere = false;
    int dvdInd = 0;
    int cusInd = 0;

    for(int i = 0; i < DVDArrSize; i++){
        if(DVDArr[i].getSerialNum() == serialNo){
            isDvdThere = true;
            dvdInd = i;
        }
    }
    for(int k = 0; k < customerArrSize; k++){
        if(customerArr[k].getID() == customerID){
            isCusThere = true;
            cusInd = k;
        }
    }
    if(isDvdThere == false && isCusThere == false){
        cout << "Cannot rent DVD. Customer with ID " << customerID << " and DVD with serial number "
        << serialNo << " not found."<< endl;
    }else if(isDvdThere == false){
        cout<< "Cannot rent DVD. DVD with serial number "<< serialNo << " not found."<<endl;
    }else if(isCusThere == false){
        cout<<"Cannot rent DVD. Customer with ID "<< customerID << " not found."<<endl;
    }else{
        if(DVDArr[dvdInd].getStatus() == "Rented"){
            cout << "Cannot rent DVD. DVD with serial number "<< serialNo <<" is not available."<<endl;
        }else{
            DVD* rentalNew = new DVD[customerArr[cusInd].getRent()+1];
            for(int k = 0; k < customerArr[cusInd].getRent(); k++){
                rentalNew[k] = customerArr[cusInd].cusRentals[k];
            }
            rentalNew[customerArr[cusInd].getRent()] = DVD(serialNo,DVDArr[dvdInd].getTitle(),DVDArr[dvdInd].getDirector());
            delete[] customerArr[cusInd].cusRentals;
            customerArr[cusInd].cusRentals = rentalNew;
            cout << "DVD with serial number "<< serialNo <<" successfully rented by customer with ID "<<customerID<<"."<<endl;
            DVDArr[dvdInd].setStatus("Rented");
            this->fillTransactionArray(DVDArr[dvdInd].getStatus(),customerID,serialNo);
            customerArr[cusInd].changeRent(1);    
        }
    }
}
void DVDStoreManagementSystem::returnDVD(const int customerID, const string serialNo){
    bool isDvdThere = false;
    bool isCusThere = false;
    int dvdInd = 0;
    int cusInd = 0;

    for(int i = 0; i < DVDArrSize; i++){
        if(DVDArr[i].getSerialNum() == serialNo){
            isDvdThere = true;
            dvdInd = i;
        }
    }
    for(int k = 0; k < customerArrSize; k++){
        if(customerArr[k].getID() == customerID){
            isCusThere = true;
            cusInd = k;
        }
    }
    if(isDvdThere == false && isCusThere == false){
        cout<<"Cannot return DVD. Customer with ID "<< customerID<<" and DVD with serial number "<<serialNo
        <<" not found."<<endl;
    }else if(isDvdThere == false){
        cout<<"Cannot return DVD. DVD with serial number "<<serialNo<<" not found."<<endl;
    }else if(isCusThere == false){
        cout<<"Cannot return DVD. Customer with ID "<<customerID<<" not found."<<endl;
    }else{
        bool isRental = false;
        int targetInd = 0;
        for(int i =0; i<customerArr[cusInd].getRent();i++){
            if(customerArr[cusInd].cusRentals[i].getSerialNum() == serialNo){
                isRental = true;
                targetInd = i;
            }
        }
        if(isRental == true){
            if(customerArr[cusInd].getRent()>1){
                DVD* newRent = new DVD[customerArr[cusInd].getRent()-1];
                for(int k = 0; k < targetInd; k++){
                    newRent[k] = customerArr[cusInd].cusRentals[k];
                }
                for(int m = targetInd+1; m < customerArr[cusInd].getRent();m++){
                    newRent[m-1] = customerArr[cusInd].cusRentals[m];
                }
                delete[] customerArr[cusInd].cusRentals;
                customerArr[cusInd].cusRentals = newRent;
                customerArr[cusInd].changeRent(-1);    
                cout<<"DVD with serial number "<< serialNo<<" successfully returned by customer with ID "<<customerID<<"."<<endl;
                DVDArr[dvdInd].setStatus("Available");
                this->fillTransactionArray(DVDArr[dvdInd].getStatus(),customerID,serialNo);
            }
            else{
                cout<<"DVD with serial number "<< serialNo<<" successfully returned by customer with ID "<<customerID<<"."<<endl;
                customerArr[cusInd].changeRent(-1);
                delete[] customerArr[cusInd].cusRentals;
                customerArr[cusInd].cusRentals = nullptr;
                 DVDArr[dvdInd].setStatus("Available");
                this->fillTransactionArray(DVDArr[dvdInd].getStatus(),customerID,serialNo);
            }  
        }else{
            cout<<"Cannot return DVD. DVD with serial number "<<serialNo<<" not rented by customer with ID "<<customerID<<"."<<endl;
        }
        //THIS PART NEED FIX AS DETERMINING OF RETURN SHOULD BE IN REGARD OF CUSTOMER OBJECTS RENTAL DVD ATTRIBUTES. '=' OPERATOR NEED TO BE OVERRIDDEN IN THE WAY
        //THAT POINTERS POINTING RENTAL DVDS OF CUSTOMER OBJECTS SHOULD BE DEEP COPIED.
    }
}
void DVDStoreManagementSystem::showAllDVDs() const{
    cout<<"DVDs in the system:"<<endl;
    if(DVDArrSize==0){
        cout<<"None"<<endl;
    }else{
        for(int i=0; i < DVDArrSize;i++){
            cout<<"DVD: "<<DVDArr[i].getSerialNum()<<", Title: "<<DVDArr[i].getTitle()<<", Director: "
            <<DVDArr[i].getDirector()<<", "<<DVDArr[i].getStatus()<<endl;
        }
    }
}
void DVDStoreManagementSystem::showAllCustomers() const{
    cout<<"Customers in the system:"<<endl;
    if(customerArrSize==0){
        cout<<"None"<<endl;
    }else{
        for(int i=0; i < customerArrSize;i++){
            cout<<"Customer: "<<customerArr[i].getID()<<", Name: "<<customerArr[i].getName()<<", DVDs Rented: "<<customerArr[i].getRent()
            <<endl;
        }
        
    }
}
void DVDStoreManagementSystem::showDVD( const string serialNo ) const{
    for(int i = 0; i<DVDArrSize;i++){
        if(DVDArr[i].getSerialNum()==serialNo){
            cout<<"DVD: "<<DVDArr[i].getSerialNum()<<", Title: "<<DVDArr[i].getTitle()<<", Director: "
            <<DVDArr[i].getDirector()<<", "<<DVDArr[i].getStatus()<<endl;
            return;
        }
    }
    cout<<"DVD with serial number "<<serialNo<<" not found."<<endl;
}
void DVDStoreManagementSystem::showCustomer( const int customerID ) const{
    for(int i = 0; i<customerArrSize;i++){
        if(customerArr[i].getID() == customerID){
            cout<<"Customer: "<<customerArr[i].getID()<<", Name: "<<customerArr[i].getName()<<", DVDs Rented: "<<customerArr[i].getRent()
            <<endl;
            return;
        }
    }
    cout<<"Customer with ID "<<customerID<<" not found."<<endl;
}
void DVDStoreManagementSystem::fillTransactionArray(const string status, const int customerID, const string serialNo){
    string key;
    if(status == "Available"){
        key = "Return";
    }else{
        key = "Rental";
    }
    if(transactionHist==nullptr){
        transactionHist = new string[1];
        transactionHist[0] = "Transaction: " + key + ", Customer: " + to_string(customerID) + ", DVD: " + serialNo;
        transActSize+=1;
    }else{
        string* newArr = new string[transActSize+1];
        for(int k = 0; k< transActSize;k++){
            newArr[k] = transactionHist[k];
        }
        newArr[transActSize] = "Transaction: " + key + ", Customer: " + to_string(customerID) + ", DVD: " + serialNo;
        delete[] transactionHist;
        transactionHist = newArr;
        transActSize+=1;
    }
}
void DVDStoreManagementSystem::showTransactionHistory() const{
    cout<<"Transactions in the system:"<<endl;
    if(transActSize==0){
        cout<<"None"<<endl;
    }else{
        for(int i = 0; i<transActSize; i++){
            cout<< transactionHist[i]<<endl;
        }
    }
}
DVDStoreManagementSystem::~DVDStoreManagementSystem(){
    for(int i = 0; i<customerArrSize;i++){
        delete[] customerArr[i].cusRentals;
    }
    delete[] customerArr;
    delete[] transactionHist;
    delete[] DVDArr;
}
