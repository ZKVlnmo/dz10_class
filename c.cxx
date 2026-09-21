#include "myaso.hpp"
using namespace std;
mutex mtx;
void mission(int id, int k)
{
    while (true)
    {
        mtx.lock();
        ofstream out("data.txt", ios::app);
        out << id << endl;
        out.close();
        ifstream in("data.txt");
        int sum = 0;
        int num;
        while (in >> num)
        {
            sum += num;
        }
        in.close();
        cout << "Поток " << id << ": сумма = " << sum << endl;
        if (sum >= id * k)
        {
            cout << "Поток " << id << ": моя миссия выполнена, я спать" << endl;
            mtx.unlock();
            break;
        } 
        int delay = rand() % 400 + 100;
        mtx.unlock();
        this_thread::sleep_for(chrono::milliseconds(delay));
    }
}
int main()
{
    srand(time(0));
    int n, k;
    cin >> n >> k;
    ofstream file("data.txt");
    file.close();
    vector<thread> threads;
    for (int i = 1; i <= n; i++)
    {
        threads.push_back(thread(mission, i, k));
    }
    for (int i = 0; i < n; i++)
    {
        threads[i].join();
    }
}