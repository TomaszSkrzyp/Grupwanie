#ifndef INB2WIN_H
#define INB2WIN_H
#include <iostream>
#include <string>
#include<vector>
#include<random>

void create_data(int ile_pkt, int d,std::string input_file);
void k_means(std::vector<Point>* Points, int powt, int ilosc_k, int ile_pkt,int d);


#endif
