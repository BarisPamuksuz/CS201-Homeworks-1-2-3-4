#ifndef __DVD_H
#define __DVD_H
#include <string>
using namespace std;

class DVD {

public:
    DVD(const string serialNum, const string tiTle, const string diRector);
    DVD();
    string getSerialNum() const;
    string getTitle() const;
    string getDirector() const;
    string getStatus() const;
    string setStatus(string newStatus);
private:
    string serialNo;
    string title;
    string director;
    string status;
};
#endif
