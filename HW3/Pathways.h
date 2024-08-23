/**
 * @author Barış Pamuksuz 22202238
 * CS201 HW3
 */

#ifndef __PATHWAYS_H
#define __PATHWAYS_H
#include <iostream>
#include "Proteins.h"
using namespace std;

class Pathways{
public:
    
    Pathways(int Id, string name);
    void setNameOfPath(string newName);
    string getNameofPath() const;
    void setIDofPath(int newID);
    int getIDofPath() const; 
    Node<Proteins>* ptrToProteinList;   

private:
    int IdPath;
    string namePath;
};


#endif