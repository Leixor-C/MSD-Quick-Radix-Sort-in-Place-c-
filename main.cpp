
#include "qick_radix_sort.h"
#include <time.h>
#include <chrono>
#include <vector>
#include <iterator>
#include <algorithm>
#include <iostream>
#include <math.h>
#include <string>
int main() {
    srand(1<<32-1);

    std::vector<size_t> a;
    size_t size ,mod;
    float med;
    std::chrono::high_resolution_clock::time_point started, done;

    std::cout<<"starting..\n";
    for (size_t siz = 0; siz < 10; ++siz){
        a.push_back(rand()%10);
    }
    for (size_t siz = 0; siz < 10; ++siz){
        std::cout<<a[siz]<<" ";
    }
    std::cout<<'\n';
    leixor::qick_radix_sort<size_t,size_t>(a.data(), a.size());//<the class it self,type of value to compare>
    std::cout<<"Order arr: ";

   for (size_t siz = 0; siz < 10; ++siz){
        std::cout<<a[siz]<<" ";
    }
    std::cout<<'\n';
    a.clear();
    size_t w,alfa;
    std::vector<std::string> sizearr={"    4   |","    5   |","    6   |","    7   |","    8   |"};
    std::cout<<
    "  size  |----------------------------max num 10^i-----------------------------\n"<<
    "  10^i  |    1   |    2    |    3    |    4    |    5    |    6    |    7    |\n"<<
    "        |---------------------------------------------------------------------\n";
    for (size_t i = 4; i < 9; ++i){
 
        std::cout<<sizearr[i-4];
        for (size_t z = 1; z < 8; ++z){
            med=0.0;
            size=pow(10,i);
            mod=pow(10,z);
            alfa=(z>3?(pow(10,z-4)*3):1);
            for (w = 0; w < 100.0/pow(10,((i-3)/2)); ++w){
                
                for (size_t siz = 0; siz < size; ++siz){
                    a.push_back((alfa*rand()+rand() )% mod);
                }


                started = std::chrono::high_resolution_clock::now();
                leixor::qick_radix_sort(a.data(), a.size());
                done = std::chrono::high_resolution_clock::now();
                med+=float(std::chrono::duration_cast<std::chrono::microseconds>(done - started).count())/1000.0;
                a.clear();
            }
            std::cout<<med/float(w) <<" | ";
        }
        std::cout<<"\n";
    }
}
