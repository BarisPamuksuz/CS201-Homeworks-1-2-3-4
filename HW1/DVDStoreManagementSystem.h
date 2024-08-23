#ifndef __DVDSTOREMANAGEMENTSYSTEM_H
#define __DVDSTOREMANAGEMENTSYSTEM_H
#include <string>
#include "DVD.h"
#include "Customer.h"

class DVDStoreManagementSystem {
public:
    DVDStoreManagementSystem();
    ~DVDStoreManagementSystem();

    void addDVD( const string serialNo, const string title, const string director );
    void removeDVD( const string serialNo );
    void addCustomer( const int customerID, const string name );
    void removeCustomer( const int customerID );
    void rentDVD( const int customerID, const string serialNo);
    void returnDVD( const int customerID, const string serialNo);
    void showAllDVDs() const;
    void showAllCustomers() const;
    void showDVD( const string serialNo ) const;
    void showCustomer( const int customerID ) const;
    void showTransactionHistory() const;
    void fillTransactionArray(const string status, const int customerID, const string serialNo);

    DVD* DVDArr;
    int DVDArrSize;
    Customer* customerArr;
    int customerArrSize;
    string* transactionHist;
    int transActSize;
};
#endif
