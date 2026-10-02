#include <iostream>
#include <mpi.h>
using namespace std;

int main(int arc, char** argv) {
    MPI_Init(&arc, &argv);
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    //cout << rank << ' ' << size << '\n';
    
    if (size < 2) {
        if (rank == 0)
            cout << "2+ POTOKA ZDELAY DOWN";
        MPI_Finalize();
        return 0;
    }

    long long value = 0;
    if (rank == 0) {
        long long ans = 0;
        for (int i = 1; i < size; ++i) {
            MPI_Recv(&value, 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            //cout << "0 get from " << i << ": " << value << '\n';
            ans += value;
        }
        cout << '\n' << ans << '\n';
    }
    else {
        int n = 1000;
        int st = ((n * (rank-1)) / (size-1));
        if (st == 0) st++;
        int en = ((n * rank) / (size-1));
        //cout << rank << ' ' << st << ' ' << en << '\n';
        //value = 100;
        for (int i = st; i < en; ++i) {
            value += i;
        }

        MPI_Send(&value, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
        cout << rank << " send to 0: " << value << '\n';
    }

    MPI_Finalize();
    return 0;
}

