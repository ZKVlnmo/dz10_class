#pragma once

#include <stack>

// Тип задания
enum class TaskType
{
    Fast,
    Medium,
    Slow
};

// Пользовательская структура задания
struct Task
{
    int id;
    TaskType type;

    // Выполнить задание.
    // Время выполнения зависит от type.
    void execute() const;
};

// Периодически добавляет в стек случайные задания.
// periodMs — пауза между добавлениями заданий в миллисекундах.
void fillTaskStack(std::stack<Task>* tasks, int periodMs);
