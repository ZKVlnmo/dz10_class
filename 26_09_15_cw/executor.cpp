#include "Task.cpp"
#include <iostream>
#include <stack>
#include <vector>
#include <mutex>
#include <thread>
#include <condition_variable>
using namespace std;

struct TaskStat {
    int id;
    string status;

    TaskStat() { id = -1; status = ""; }
    TaskStat(int i) { id = i; status = ""; }
    TaskStat(int i, string s) { id = i; status = s; }

    string updateStatus(string newstatus) { status = newstatus; return newstatus; }
};

mutex m;
condition_variable cv;

void threadFunc(stack<Task> *tasks, vector<TaskStat> &tasksStats) {
    while (true) {
        unique_lock<mutex> lock(m);
        cv.wait(lock, [tasks]() { return !tasks->empty(); });

        Task nowTask = tasks->top();
        tasks->pop();
        tasksStats.push_back(TaskStat(nowTask.id, "work"));
        lock.unlock();
        
        nowTask.execute();
        tasksStats[nowTask.id - 1].updateStatus("FINISHED!");
    }
}

int main() {
    vector<TaskStat> tasksStats(0);
    stack<Task> tasks;
    vector<thread> threads;
    int treadsCount = 100;
    
    thread fillTaskThread(fillTaskStack, &tasks, 1000);
    
    for (int i = 0; i < treadsCount; ++i)
    threads.push_back(thread(threadFunc, &tasks, ref(tasksStats)));
    for (int i = 0; i < treadsCount; ++i)
        threads[i].join();
    fillTaskThread.join();

    return 0;
}

