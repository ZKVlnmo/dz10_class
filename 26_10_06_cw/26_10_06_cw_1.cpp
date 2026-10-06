#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <mpi.h>
using namespace std;

int main(int arc, char** argv) {
    MPI_Init(&arc, &argv);
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if (size != 10) {
        if (rank == 0) cout << "10 POTOKOV SDELAI DEBIL\n";
        MPI_Finalize();
        return 0;
    }
    
    string file_name = to_string(rank+1);
    if (file_name.size() == 1) file_name = '0'+file_name;
    file_name = "/home/mika/Documents/GitHub/dz10_class/26_10_06_cw/files/sales_"+file_name+".csv";
    //cout << file_name << '\n';
    std::ifstream file(file_name);
    map<string, int> schet;
    
    // продукт | дата продажи | изначальная цена | скидка в рублях
    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string cell;
        vector<string> row(4);
        
        for (int i = 0; i < 4; ++i) {
            std::getline(ss, cell, ',');
            row[i] = cell;
        }
        
        if (schet.find(row[0]) == schet.end())
            schet.insert({row[0], 1});
        else
            schet[row[0]]++;
    }

    string max_key = schet.begin()->first;
    for (const auto& pair : schet) {
        if (pair.second > schet[max_key]) max_key =  pair.first;
        //std::cout << rank << ' ' << pair.first << " : " << pair.second << std::endl;
    }
    //cout << "\n\n";
    cout << rank+1 << " | " << max_key << " | " << schet[max_key] << '\n';

    MPI_Finalize();
    return 0;
}

