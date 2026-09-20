#include "Task.h"

#include <chrono>
#include <iostream>
#include <random>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

extern mutex m;
extern condition_variable cv;

void Task::execute() const
{
    switch (type)
    {
        case TaskType::Fast:
            std::cout << "Task " << id << ": FAST started\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            std::cout << "Task " << id << ": FAST finished\n";
            break;

        case TaskType::Medium:
            std::cout << "Task " << id << ": MEDIUM started\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(1500));
            std::cout << "Task " << id << ": MEDIUM finished\n";
            break;

        case TaskType::Slow:
            std::cout << "Task " << id << ": SLOW started\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(3000));
            std::cout << "Task " << id << ": SLOW finished\n";
            break;
    }
}

void fillTaskStack(std::stack<Task>* tasks, int periodMs)
{
    std::mt19937 generator(std::random_device{}());
    std::uniform_int_distribution<int> typeDistribution(0, 2);

    int nextId = 1;

    while (true)
    {
        Task task;

        task.id = nextId++;
        task.type = static_cast<TaskType>(typeDistribution(generator));

        {
            lock_guard<mutex> lock(m);
            tasks->push(task);
        }
        cv.notify_one();

        std::cout << "Added task " << task.id << '\n';

        std::this_thread::sleep_for(
            std::chrono::milliseconds(periodMs)
        );
    }
}
