#include <iostream>
using namespace std;
#include "DVD.h"

DVD::DVD(const string serialNum, const string tiTle, const string diRector){
    serialNo = serialNum;
    title = tiTle;
    director = diRector;
    setStatus("Available");
}
DVD::DVD(){
    serialNo = "";
    title = "";
    director = "";
}
string DVD::getSerialNum() const{
    return serialNo;
}
string DVD::getTitle() const{
    return title;
}
string DVD::getDirector() const{
    return director;
}
string DVD::getStatus() const{
    return status;
}
string DVD::setStatus(string newStatus){
    status = newStatus;
    return status;
}
