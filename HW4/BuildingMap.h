/**
 * 17.05.2024
 * @author Barış Pamuksuz
 * ID: 22202238
 * CS201-HW4
 */
#include <string>
using namespace std;
#include "Cubicle.h"
#include "LinkedStack.h"
#include "Node.h"

class BuildingMap {
    public:
        BuildingMap(const string buildingMapFile);
        ~BuildingMap();

        void displayAllCubicles() const;
        void displayAdjacentCubicles(const int row, const int col) const;
        void displayBuildingMap() const;
        void findPaths(const int startRow, const int startCol, const int endRow, const int endCol);
        void findPaths(const int startRow, const int startCol, const int endRow, const int endCol,
        const int avoidRow, const int avoidCol);
        int IndexofCubicleByCoordinate(int row, int column) const;
        Cubicle* getAnAdjacentCubicle(Cubicle* sourceCubicle);
        void unVisitAll();
        
    private:
        Cubicle* allCubicles;
        int rows;
        int columns;
};
