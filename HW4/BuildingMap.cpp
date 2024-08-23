/**
 * 17.05.2024
 * @author Barış Pamuksuz
 * ID: 22202238
 * CS201-HW4
 */
#include <iostream>
#include <fstream>
#include "BuildingMap.h"

using namespace std;

BuildingMap::BuildingMap(const string buildingMapFile){
    ifstream inputFile(buildingMapFile);
    int currentRow = 0;
    string line;
    bool firstTime = true;
    getline(inputFile,line);
    rows = line[0] - '0';
    columns = line[2] - '0';
    allCubicles = new Cubicle[rows*columns];
    while(currentRow < rows){
        getline(inputFile, line);
        for(int currentCol = 0; currentCol < columns; currentCol++){
            int currentIndex = currentRow*columns+currentCol;
            int type = line[currentCol]-'0';
            allCubicles[currentIndex] = Cubicle(currentRow, currentCol, type);
        }
        currentRow++;    
    }

    for(int k = 0; k < rows*columns;k++){
        int currentRow = k / columns;
        int currentCol = k % columns;
        if(allCubicles[k].typeNum == 0){
            if(currentCol == 0 && currentRow != rows-1){
                allCubicles[k].addAdjacentCubicle(allCubicles[k+columns]);
                allCubicles[k+columns].addAdjacentCubicle(allCubicles[k]);
            }else if(currentCol != 0 && currentRow != rows-1){
                allCubicles[k].addAdjacentCubicle(allCubicles[k+columns]);
                allCubicles[k].addAdjacentCubicle(allCubicles[k-1]);
                allCubicles[k+columns].addAdjacentCubicle(allCubicles[k]);
                allCubicles[k-1].addAdjacentCubicle(allCubicles[k]);
            }else if(currentCol != 0 && currentRow == rows-1){
                allCubicles[k].addAdjacentCubicle(allCubicles[k-1]);
                allCubicles[k-1].addAdjacentCubicle(allCubicles[k]);
            }
        }else if(allCubicles[k].typeNum == 1){
            if(currentRow != rows-1){
                allCubicles[k].addAdjacentCubicle(allCubicles[k+columns]);
                allCubicles[k+columns].addAdjacentCubicle(allCubicles[k]);
            }
        }else if(allCubicles[k].typeNum == 2){
            if(currentCol != 0){
                allCubicles[k].addAdjacentCubicle(allCubicles[k-1]);
                allCubicles[k-1].addAdjacentCubicle(allCubicles[k]);
            }
        }else if(allCubicles[k].typeNum == 3){
            // do nothing, not possible to add any adjacent cubicle.
        }
    }
    cout<<rows<<" rows and "<<columns<<" columns have been read."<<endl;
}
BuildingMap::~BuildingMap(){
    for(int i = 0; i < rows*columns; i++){
        Node<Cubicle*>* adjacentListHead = allCubicles[i].adjacentCubicleList;
        while(adjacentListHead != nullptr){
            Node<Cubicle*>* nextPtr = adjacentListHead->getNext();
            delete adjacentListHead;
            adjacentListHead = nextPtr;
        }
        allCubicles[i].clearVisitedCubicles();
    }
    delete[] allCubicles;
}
void BuildingMap::displayAdjacentCubicles(const int row, const int col) const {
    int indexOfTarget = IndexofCubicleByCoordinate(row, col);
    cout<<"The cubicles adjacent to "<<"("<<allCubicles[indexOfTarget].rowNum<<","<<allCubicles[indexOfTarget].columnNum<<")"<<" are:"<<endl;
    cout << "("<<allCubicles[indexOfTarget].rowNum<<","<<allCubicles[indexOfTarget].columnNum<<")" <<" -> ";
    Node<Cubicle*>* headptr = allCubicles[indexOfTarget].adjacentCubicleList;
    while(headptr != nullptr){
        if(headptr->getNext() != nullptr){
            cout<<"("<<headptr->getItem()->rowNum<<","<<headptr->getItem()->columnNum<<"),";
        }else{
            cout<<"("<<headptr->getItem()->rowNum<<","<<headptr->getItem()->columnNum<<")";  
        }
        headptr = headptr->getNext();
    }
    cout<<endl;

}
int BuildingMap::IndexofCubicleByCoordinate(const int row, const int col) const{
    for(int k = 0; k < rows*columns; k++){
        if(row == allCubicles[k].rowNum && col == allCubicles[k].columnNum){
            return k;
        }
    }
    return -1;
}
void BuildingMap::displayBuildingMap() const {
    cout<<"The building map is as follows: "<<endl;
    for(int k = 0; k <rows*columns; k++){
        cout << "("<<allCubicles[k].rowNum<<","<<allCubicles[k].columnNum<<")" <<" -> ";
        Node<Cubicle*>* headptr = allCubicles[k].adjacentCubicleList;
        while(headptr != nullptr){
            if(headptr->getNext() != nullptr){
                cout<<"("<<headptr->getItem()->rowNum<<","<<headptr->getItem()->columnNum<<"),";
            }else{
                cout<<"("<<headptr->getItem()->rowNum<<","<<headptr->getItem()->columnNum<<")";  
            }
            headptr = headptr->getNext();
        }
        cout<<endl;
    }
}
void BuildingMap::unVisitAll(){
    for(int k = 0; k < rows*columns; k++){
        allCubicles[k].isVisited = false;
    }
}
LinkedStack<Cubicle*> deepCopyStack(LinkedStack<Cubicle*>& original) {
    LinkedStack<Cubicle*> newStack;
    LinkedStack<Cubicle*> temp;
    while (!original.isEmpty()) {
        temp.push(original.peek());
        original.pop();
    }
    while (!temp.isEmpty()) {
        Cubicle* item = temp.peek();
        temp.pop();
        original.push(item);
        newStack.push(item);
    }
    return newStack;
}
//Logic: First find a path, pop one by one until finding another or stack's empty. Each popping makes that cubicle sets to notVisited but departed cubicle has no access popped one for that time, so that another path can be found from indirect access if there is.
// The popped cubicle has been freed by deleting visited cubicle list to ensure that far cubicle can access same cubicle if there is at least one gap(far cubicle), so that different paths still holds same parts of previous paths but not all. i.e. assuming path 1->3->5->7 
// if 3->9->5 possible and when 5 pops, 3->5 is not possible due to 3's visitedList but 5 is available since popped set to isVisited = false, stack finds 3->9->5 path and since 5's visitedList is released, 5->7 possible. New path is found: 1->3->9->5->7. I use DFS.
void BuildingMap::findPaths(const int startRow, const int startCol, const int endRow, const int endCol) {
    cout << "Paths from (" << startRow << "," << startCol << ") to (" << endRow << "," << endCol << ") are: " << endl;
    LinkedStack<Cubicle*> stackToDisplay;
    unVisitAll();
    int starterIndex = IndexofCubicleByCoordinate(startRow, startCol);
    int endIndex = IndexofCubicleByCoordinate(endRow, endCol);
    bool isDone = false;
    Cubicle* starterCubicle = &allCubicles[starterIndex];
    Cubicle* endCubicle = &allCubicles[endIndex];

    LinkedStack<Cubicle*>* allStacks = nullptr;
    LinkedStack<Cubicle*> stack;
    int allStacksSize = 0;
    stack.push(starterCubicle);
    starterCubicle->isVisited = true;
    Cubicle* topCubicle = stack.peek();
    while (!stack.isEmpty() && &*topCubicle != &*endCubicle) {
        //cout<<topCubicle->rowNum<<" "<<topCubicle->columnNum<<endl;--DEBUG STATEMENT--
        //cout<<"I was here: "<<"("<<stack.peek()->rowNum<<","<<stack.peek()->columnNum<<") ";
        Cubicle* anAdjacent = getAnAdjacentCubicle(topCubicle);
        
        if (anAdjacent == nullptr) {
            //cout<<"I dont have adjacent cubicle"<<endl;
            topCubicle->isVisited = false;
            topCubicle->clearVisitedCubicles();
            stack.pop();
        } else {
            //cout<<"My adjacent cubicle is "<<"("<<anAdjacent->rowNum<<","<<anAdjacent->columnNum<<")"<<endl;
            topCubicle->addVisitedCubicle(*anAdjacent);
            stack.push(anAdjacent);
            //cout<<"I travelled there: "<<"("<<anAdjacent->rowNum<<","<<anAdjacent->columnNum<<")"<<endl;
            anAdjacent->isVisited = true;
        }
        if(!stack.isEmpty()){
            topCubicle = stack.peek();
        }
        if(&*topCubicle == &*endCubicle) {\
            isDone = true;
            while (!stack.isEmpty()) {
                Cubicle* curCubicle = stack.topPtr->getItem();
                stack.pop();
                stackToDisplay.push(curCubicle);
            }
            while (!stackToDisplay.isEmpty()) {
                Cubicle* curCubicle = stackToDisplay.topPtr->getItem();
                stackToDisplay.pop();
                stack.push(curCubicle);
                cout << "(" << curCubicle->rowNum << "," << curCubicle->columnNum << ")";
                if (!stackToDisplay.isEmpty()) {
                    cout << " -> ";
                }else{
                    cout<<endl;
                }
            }
            stack.peek()->isVisited = false;
            stack.peek()->clearVisitedCubicles();
            stack.pop();
            topCubicle = stack.peek();
        }
    }
    if(isDone == false){
        cout<<"None"<<endl;
    }
}
bool isExist(Cubicle* searched, Node<Cubicle*>* list){
    while(list != nullptr){
        if(list->getItem() == searched){
            return true;
        }
        list = list->getNext();
    }
    return false;
}

Cubicle* BuildingMap::getAnAdjacentCubicle(Cubicle* sourceCubicle) {
    for (Node<Cubicle*>* target = sourceCubicle->adjacentCubicleList; target != nullptr; target = target->getNext()) {
        Cubicle* candidate = target->getItem();
        if (!candidate->isVisited && !isExist(candidate, sourceCubicle->visitedCubicleList)) {
            return candidate;
        }
    }
    return nullptr;
}
void BuildingMap::findPaths(const int startRow, const int startCol, const int endRow, const int endCol,
    const int avoidRow, const int avoidCol) {
    int targetIndex = IndexofCubicleByCoordinate(avoidRow,avoidCol);
     cout << "Paths from (" << startRow << "," << startCol << ") to (" << endRow << "," << endCol << ") avoiding ("<<avoidRow<<","<<avoidCol<<") "<<" are:"<<endl;
    
    LinkedStack<Cubicle*> stackToDisplay;
    unVisitAll();
    allCubicles[targetIndex].isVisited = true;
    int starterIndex = IndexofCubicleByCoordinate(startRow, startCol);
    int endIndex = IndexofCubicleByCoordinate(endRow, endCol);
    bool isDone = false;
    Cubicle* starterCubicle = &allCubicles[starterIndex];
    Cubicle* endCubicle = &allCubicles[endIndex];

    LinkedStack<Cubicle*>* allStacks = nullptr;
    LinkedStack<Cubicle*> stack;
    int allStacksSize = 0;
    stack.push(starterCubicle);
    starterCubicle->isVisited = true;
    Cubicle* topCubicle = stack.peek();
    while (!stack.isEmpty() && &*topCubicle != &*endCubicle) {
        //cout<<topCubicle->rowNum<<" "<<topCubicle->columnNum<<endl;--DEBUG STATEMENT--
        //cout<<"I was here: "<<"("<<stack.peek()->rowNum<<","<<stack.peek()->columnNum<<") ";
        Cubicle* anAdjacent = getAnAdjacentCubicle(topCubicle);
        
        if (anAdjacent == nullptr) {
            //cout<<"I dont have adjacent cubicle"<<endl;
            topCubicle->isVisited = false;
            topCubicle->clearVisitedCubicles();
            stack.pop();
        } else {
            //cout<<"My adjacent cubicle is "<<"("<<anAdjacent->rowNum<<","<<anAdjacent->columnNum<<")"<<endl;
            topCubicle->addVisitedCubicle(*anAdjacent);
            stack.push(anAdjacent);
            //cout<<"I travelled there: "<<"("<<anAdjacent->rowNum<<","<<anAdjacent->columnNum<<")"<<endl;
            anAdjacent->isVisited = true;
        }
        if(!stack.isEmpty()){
            topCubicle = stack.peek();
        }
        if(&*topCubicle == &*endCubicle) {\
            isDone = true;
            while (!stack.isEmpty()) {
                Cubicle* curCubicle = stack.topPtr->getItem();
                stack.pop();
                stackToDisplay.push(curCubicle);
            }
            while (!stackToDisplay.isEmpty()) {
                Cubicle* curCubicle = stackToDisplay.topPtr->getItem();
                stackToDisplay.pop();
                stack.push(curCubicle);
                cout << "(" << curCubicle->rowNum << "," << curCubicle->columnNum << ")";
                if (!stackToDisplay.isEmpty()) {
                    cout << " -> ";
                }else{
                    cout<<endl;
                }
            }
            stack.peek()->isVisited = false;
            stack.peek()->clearVisitedCubicles();
            stack.pop();
            topCubicle = stack.peek();
        }
    }
    if(isDone == false){
        cout<<"None"<<endl;
    }
}
void BuildingMap::displayAllCubicles() const{
    cout<<"The cubicles in the building are:"<<endl;
    for(int i = 0; i < rows; i++){
        for(int k = 0; k < columns; k++){
            if(k==columns-1){
                cout<<"("<<allCubicles[i*columns+k].rowNum<<","<<allCubicles[i*columns+k].columnNum<<")"<<endl; 
            }else{
            cout<<"("<<allCubicles[i*columns+k].rowNum<<","<<allCubicles[i*columns+k].columnNum<<")"<<",";}
        }
    }
}
int main() {
BuildingMap bm("building.txt");
cout << endl;
bm.displayAllCubicles();
cout << endl;
bm.displayAdjacentCubicles(1,1);
cout << endl;
bm.displayAdjacentCubicles(2,2);
cout << endl;
bm.displayAdjacentCubicles(3,5);
cout << endl;
bm.displayBuildingMap();
cout << endl;
bm.findPaths(0,0,4,0);
cout << endl;
bm.findPaths(0,0,4,0,1,3);
cout << endl;
bm.findPaths(0,0,4,0,2,1);
cout << endl;
bm.findPaths(3,1,2,4);
return 0;
}
