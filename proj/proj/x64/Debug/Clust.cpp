#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include"C:\Users\Dell\source\repos\Grupwanie\proj\create.h"

/// @brief ta funkcja jest g
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



};

void k_means(std::vector<Point>* Points, int powt, int ilosc_k, int ile_pkt,int d) {///(adres wektora punktow,ilosc powtorzen algorytmu,ilosc clustrow,ilosc punktow)
    std::vector<Point> Centroidy;///wektor przechowujacy centroidy clustrow
    std::vector<Point>::iterator it;
    std::vector<Point>::iterator p_it;



    for (int i = 0; i < ilosc_k; ++i) {

        Centroidy.push_back(Points->at(rand() % ile_pkt));///wybieranie losowych punktow jako centroidy
    }


    for (int powtorzenia = 0; powtorzenia < powt; powtorzenia++) {
        int licznik = 0;
        std::vector<std::vector<double>> srednie_koordynatow;

        for (it = Centroidy.begin(); it != Centroidy.end(); ++it) {///iteracja przez centroidy


            int numer_clustera = licznik;


            for (p_it = Points->begin(); p_it != Points->end(); ++p_it) {///przydzielanie punktow do clustrow
                Point iterowany_punkt = *p_it;
                Point iterowany_centroid = *it;
                double odleglosc_od_clustra = iterowany_centroid.distance(iterowany_punkt);
                if (odleglosc_od_clustra < iterowany_punkt.minDist) {
                    iterowany_punkt.minDist = odleglosc_od_clustra;
                    iterowany_punkt.cluster = licznik;
                }
                *p_it = iterowany_punkt;
                *it = iterowany_centroid;

            }
            
            std::vector<double> srednie_koordynatow_clustra;
            for (int wymiar = 0; wymiar < d; wymiar++) {
                srednie_koordynatow_clustra.push_back(0.0);
                
            }
            
            srednie_koordynatow.push_back(srednie_koordynatow_clustra);
            licznik += 1;
            
        }
        //punkty przydzielone

        
        
        
        for (p_it = Points->begin(); p_it != Points->end(); ++p_it) {
            Point podany_punkt = *p_it;
            int numer_clustra = podany_punkt.cluster;
            std::vector<double>::iterator it_coord;///iterator koordyantow podanego punktu
            int numer_wspolrzednej = 0;
            for (it_coord = podany_punkt.coordinates.begin(); it_coord != podany_punkt.coordinates.end(); ++it_coord) {
                double wspolrzedna_podanego_punktu = *it_coord;
                srednie_koordynatow[numer_clustra][numer_wspolrzednej] += wspolrzedna_podanego_punktu;
                numer_wspolrzednej += 1;
                *it_coord = wspolrzedna_podanego_punktu;

            }
        }
        for (int i = 0; i < ilosc_k; i++) {
            for (int l = 0; l < d; l++) {
                std::cout << Centroidy[i].coordinates[l] << " ";
            }
            std::cout << "\n";
        }

            
            
            for (int i = 0; i < ilosc_k; i++) {
                for (int l = 0; l<d; l++) {
                    srednie_koordynatow[i][l] = srednie_koordynatow[i][l] /ile_pkt;
                    std::cout << srednie_koordynatow[i][l] << ", ";

                }
                std::cout << "\n";
                Centroidy[i] = Point(srednie_koordynatow[i]);
             }
        
            for (std::vector<Point>::iterator p_it = Points->begin(); p_it != Points->end(); ++p_it) {
                Point p = *p_it;
                std::cout << p.cluster << ", ";
            }

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
            
            v.push_back(i);
        }
        vv.push_back(Point(v));
    }
    return vv;
}
///problem z przekazaniem

//C++\Projekt\Clust.exe -i dataset.txt -o liczby.txt -k 10 -d 3
int main(int argc, char* argv[]) {
    if (argc < 5) {
        std::cout << "za malo argumentow";
        return 1;
    }
    std::string input_file; std::string output_file; int k; int d; int pkt;

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
        else   if (a == "-pkt") {
            std::istringstream iss(argv[i + 1]);
            if ((iss >> pkt) && iss.eof()) {
                ///the number is right
            } i++;
        }
    }
    std::cout << input_file;
    std::cout << output_file;
    std::cout << k;
    std::cout << d;
    create_data(pkt, d, input_file);

    ///document entity
    /// i love doxygen
    std::vector<Point> Points;
    Points = create_vector(input_file);

    Point p0 = Point({ 1.0,2.0,3.0 });
    Point p1 = Point({ 4.0,2.0,7.0 });
    
    k_means(&Points, 3, k,pkt,d);

    return 0;
}
///.\x64\Debug\proj.exe -i dataset.txt -o liczby.txt -k 3 -d 2 -pkt 15