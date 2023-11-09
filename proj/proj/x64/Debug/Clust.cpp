#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include"C:\Users\Dell\source\repos\Grupwanie\proj\create.h"

/// @brief ta funkcja jest g
struct Point {///@brief struktura punktu 
    std::vector<double> coordinates;
    int cluster;
    double minDist;
    Point() :
        coordinates(),
        cluster(-1),
        minDist(20000.0) {}

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



};

void k_means(std::vector<Point>* Points, int powt, int ilosc_k,int ile_pkt) {
    std::vector<Point> Centroidy;
    std::vector<Point>::iterator it;
    

    int licznik=0;
    for (int i = 0; i < ilosc_k; ++i) {
        
        Centroidy.push_back(Points->at(rand() % ile_pkt));
    }
        
       
    
    for (it = Centroidy.begin(); it != Centroidy.end(); ++it) {
        

        int numer_clustera = licznik;
        
        
        for (std::vector<Point>::iterator p_it = Points->begin(); p_it != Points->end(); ++p_it) {
            Point iterowany_punkt = *p_it;
            double odleglosc_od_clustra = Centroidy[licznik].distance(iterowany_punkt);
            if (odleglosc_od_clustra < iterowany_punkt.minDist) {
                iterowany_punkt.minDist = odleglosc_od_clustra;
                iterowany_punkt.cluster = licznik;
            }
            *p_it = iterowany_punkt;
            
        }
        licznik += 1;
        
    }
    for (int i = 0; i < ilosc_k; i++) {
        for (int l = 0; l < 2; l++) {
            std::cout << Centroidy[i].coordinates[l]<<" ";
        }
        std::cout << "\n";
    }
    for (std::vector<Point>::iterator p_it = Points->begin(); p_it != Points->end(); ++p_it) {
        Point p = *p_it;
        std::cout << p.cluster << ", ";
    }
    

}


std::vector<Point> create_vector(std::string input_file) {
    std::vector<Point> vv;
    std::string line;
    std::ifstream input(input_file);
    while (std::getline(input, line))
    {
        std::stringstream ss(line);
        double i;
        std::vector<double> v;
        while (ss >> i) {
            std::cout << i << "\n";
            v.push_back(i);
        }
        vv.push_back(Point(v));
    }
    return vv;
}
///problem z przekazaniem

//C++\Projekt\Clust.exe -i dataset.txt -o liczby.txt -k 10 -d 3
int main(int argc, char* argv[]) {
    if (argc < 4) {
        std::cout << "za malo argumentow";
        return 1;
    }
    std::string input_file; std::string output_file; int k; int d;

    for (int i = 0; i < argc; ++i) {
        std::string a = argv[i];
        if (a == "-i") {
            input_file = argv[i + 1];
            i++;
        }
        else if (a == "-o") {
            output_file = argv[i + 1];
            i++;
        }
        else   if (a == "-k") {
            std::istringstream iss(argv[i + 1]);
            if ((iss >> k) && iss.eof()) {
                ///the number is right
            } i++;
        }
        else if (a == "-d") {
            std::istringstream iss(argv[i + 1]);
            if ((iss >> d) && iss.eof()) {
                ///the number is right
            }
            i++;
        }
    }
    std::cout << input_file;
    std::cout << output_file;
    std::cout << k;
    std::cout << d;
    create_data(100, d, input_file);

    ///document entity
    /// i love doxygen
    std::vector<Point> Points;
    Points = create_vector(input_file);

    Point p0 = Point({ 1.0,2.0,3.0 });
    Point p1 = Point({ 4.0,2.0,7.0 });
    
    k_means(&Points, 100, k,100);

    return 0;
}
///.\x64\Debug\proj.exe -i dataset.txt -o liczby.txt -k 3 -d 3