#include "qick_radix_sort.h"
#include <stdlib.h>
#include <time.h>   
#include <iostream>
#include <chrono>
#include<string>
#include <array>
#include <math.h>
#include <bitset>

class data
{
public:
    data() {}
    data(size_t& A):m(A) {};
    size_t& get_size_t() { return m; };
    
    void operator = (data& A) { m = A.m; };
    void operator = (size_t& A) { m = A; };
    size_t m;
};
void object_version(const size_t pow10, const size_t pow2) {
    size_t size = pow(10, pow10);
    data* arr = new data[size];
    size_t mod = 1 << (2 + pow2);
    float mediana = 0.0;

    for (size_t i = 0; i < 100; i++)
    {
        for (size_t i = 0; i < size; i++) {

            arr[i].m = rand() % mod;
        }


        auto started = std::chrono::high_resolution_clock::now();
        leixor::qick_radix_sort(arr, size);
        auto done = std::chrono::high_resolution_clock::now();
        mediana += float(std::chrono::duration_cast<std::chrono::nanoseconds>(done - started).count()) / float(1000000);
    }
    std::cout << "|" << mediana /100;

    delete[] arr;

};
void pointer_object_version(const size_t pow10, const size_t pow2) {
    size_t size = pow(10, pow10);
    data** arr = new data * [size];
    size_t mod = 1 << (1+ pow2);
    float mediana = 0.0;
    for (size_t i = 0; i < size; i++) 
        arr[i] = new data();

    for (size_t i = 0; i < 100; i++)
    {

        for (size_t i = 0; i < size; i++) {
            arr[i]->m = rand() % mod;
        }


        auto started = std::chrono::high_resolution_clock::now();
        leixor::qick_radix_sort(arr, size);
        auto done = std::chrono::high_resolution_clock::now();

        std::cout << "|" << float(std::chrono::duration_cast<std::chrono::nanoseconds>(done - started).count()) / float(1000000);
        mediana += float(std::chrono::duration_cast<std::chrono::nanoseconds>(done - started).count()) / float(1000000);
    }
    std::cout << "|" << mediana / 100;

    for (size_t i = 0; i < size; i++) {
        delete arr[i];
    }

    delete[] arr;

};
int main() {
    std::cout << "starting...\n";
    std::array<std::string, 7> alfa = { "\nmax|1 ","\nnum|2 ","\npow|3 ","\n2  |4 ","\n   |5 " ,"\n   |6 " ,"\n   |7 " };


std::cout <<
        "\n      --------------------------------------------------" <<
        "\n      ----------------object oriented version-----------" <<
        "\n      --------------------------------------------------\n\n";
        std::cout <<
            "\n      ---------------------size pow 10------------------" <<
            "\n      --------------------------------------------------" <<
            "\n      |  1     |  2     |   3    |    4   |   5  |    6  |    7 |";

        for (size_t z = 0; z < 7; z++) {
            std::cout << "\n      --------------------------------------------------" <<
                alfa[z];

            for (size_t i = 1; i < 8; i++) {
                object_version(i, z);
            }
        }
        std::cout << "\n      --------------------------------------------------\n";

    std::cout <<
        "\n      --------------------------------------------------" <<
        "\n      ----------------pointer oriented version-----------" <<
        "\n      --------------------------------------------------\n\n";

        std::cout <<
            "\n      ---------------------size pow 10------------------" <<
            "\n      --------------------------------------------------" <<
            "\n      |  1   | 2    |    3 |    4 |    5 |    6 |    7 |";

        for (size_t z = 0; z < 7; z++) {
            std::cout << "\n      --------------------------------------------------" <<
                alfa[z];

            for (size_t i = 1; i < 8; i++) {
                pointer_object_version(i, z);
            }
        }
        std::cout << "\n      --------------------------------------------------\n";

}
/*#include <chrono>
#include <vector>
#include <map>

int main() {

	

	/*
	std::cout << "\nreading..\n";
	auto started = std::chrono::high_resolution_clock::now();

	text text_s("dummy_text.txt");
	text_s.write_dic("order_dummy.txt");
	auto done = std::chrono::high_resolution_clock::now();
	auto first_done=done-started;

	started = std::chrono::high_resolution_clock::now();

	map<string, size_t> read;
	string line;
	ifstream myfile("dummy_text.txt");
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			istringstream iss(line);
			for (string s; iss >> s; )
				read[s]++;

		}
		myfile.close();
	}
	else cout << "Unable to open file";

	ofstream betafile;
	betafile.open("order_dummy.txt");
	map<string, size_t>::iterator itr;
	for (itr = read.begin(); itr != read.end(); itr++) {
		betafile << itr->first<< ":" << itr->second << "\n";
	}


	betafile.close();
	done = std::chrono::high_resolution_clock::now();

	auto second_done = done - started;
	std::cout << "first read time in seconds: " << std::chrono::duration_cast<std::chrono::seconds>(first_done).count() << '\n';
	std::cout << "second read time in seconds: " << std::chrono::duration_cast<std::chrono::seconds>(second_done).count() << '\n';

	/*
	auto started = std::chrono::high_resolution_clock::now();
	leixor::radix_sort_ftl(text_s.dic.data(), text_s.dic.size(),8);
	auto done = std::chrono::high_resolution_clock::now();

	std::cout << " time in milisecons: " << (float(std::chrono::duration_cast<std::chrono::nanoseconds>(done - started).count()) / float(1000000))<<'\n';
	std::cout << "size of the vector: "<< text_s.dic.size()<<'\n';
	std::cout << "sizeof(size_t)/sizeof(char): " << sizeof(size_t) / sizeof(char) <<'\n';
	std::cout << "sizeof(size_t): " << sizeof(size_t)<< '\n';
	std::cout << "sizeof(char): " << sizeof(char) << '\n';
	text_s.write("order_dummy.txt");
	
}
*/