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
    double rank_otv=0, otv=0;
    
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
        if (row[2] != "изначальная цена") rank_otv += stod(row[2]) * (100 - stod(row[3])) / 100;
    }
    cout << rank+1 << " | " << (int)rank_otv << '\n';

    MPI_Reduce(&rank_otv, &otv, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        cout << (int)otv << '\n';
    }

    MPI_Finalize();
    return 0;
}

