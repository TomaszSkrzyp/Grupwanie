#include"create.h"
#include<vector>
struct Point {///@brief struktura punktu 
    std::vector<double> coordinates;
    int cluster;///numer przydzielonego clustera
    double minDist;
    

    Point(std::vector<double> coordinates) ://lista inicjalizujaca  punktu
        coordinates(coordinates),
        cluster(-1),
        minDist(20000.0) {}
    double distance(Point p) { ///metoda dystanu pomiedzy punktami 
        double sum = 0;
        for (int i = 0; i < coordinates.size(); ++i) {
            sum += (coordinates[i] - p.coordinates[i]) * (coordinates[i] - p.coordinates[i]);
        }
        return sum;
    }
