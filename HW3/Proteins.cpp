/**
 * @author Barış Pamuksuz 22202238
 * CS201 HW3
 */

#include <iostream>
using namespace std;
#include "Proteins.h"

Proteins::Proteins(int ID){
    this->setId(ID);
    this->ptrToGeneList = nullptr;
}
int Proteins::getId() const{
    return Id;
}
void Proteins::setId(int newId){
    this->Id = newId;
}
