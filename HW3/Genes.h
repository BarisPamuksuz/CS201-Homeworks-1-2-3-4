/**
 * @author Barış Pamuksuz 22202238
 * CS201 HW3
 */

#ifndef __GENES_H
#define __GENES_H
#include <iostream>
#include "Node.h"
using namespace std;

class Genes{
public:
    Genes(int ID, string name);
    void setName(string newName);
    string getName() const;
    void setID(int newID);
    int getID() const; 

private:

    int geneID;
    string geneName;

};
#endif