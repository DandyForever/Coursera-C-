#include <map>
#include <iostream>

using namespace std;

// Перечислимый тип для статуса задачи
enum class TaskStatus {
    NEW,          // новая
    IN_PROGRESS,  // в разработке
    TESTING,      // на тестировании
    DONE          // завершена
};

// Объявляем тип-синоним для map<TaskStatus, int>,
// позволяющего хранить количество задач каждого статуса
using TasksInfo = map<TaskStatus, int>;

class TeamTasks {
public:
    // Получить статистику по статусам задач конкретного разработчика
    const TasksInfo& GetPersonTasksInfo(const string& person) const {
        return data.at(person);
    }

    // Добавить новую задачу (в статусе NEW) для конкретного разработчитка
    void AddNewTask(const string& person) {
        data[person][TaskStatus::NEW]++;
    }

    // Обновить статусы по данному количеству задач конкретного разработчика,
    // подробности см. ниже
    tuple<TasksInfo, TasksInfo> PerformPersonTasks(
            const string& person, int task_count) {
        auto& user_tasks = data[person];
        TasksInfo updated_tasks;
        for (auto& [status, count] : user_tasks) {
            if (status == TaskStatus::NEW) {
                if (count > task_count) {
                    updated_tasks[TaskStatus::IN_PROGRESS] = task_count;
                    task_count -= task_count;
                    break;
                } else {
                    updated_tasks[TaskStatus::IN_PROGRESS] = count;
                    task_count -= count;
                }
            } else if (status == TaskStatus::IN_PROGRESS) {
                if (count > task_count) {
                    updated_tasks[TaskStatus::TESTING] = task_count;
                    task_count -= task_count;
                    break;
                } else {
                    updated_tasks[TaskStatus::TESTING] = count;
                    task_count -= count;
                }
            } else if (status == TaskStatus::TESTING) {
                if (count > task_count) {
                    updated_tasks[TaskStatus::DONE] = task_count;
                    task_count -= task_count;
                    break;
                } else {
                    updated_tasks[TaskStatus::DONE] = count;
                    task_count -= count;
                }
            }
        }
        for (auto& [status, count] : updated_tasks) {
            if (status == TaskStatus::IN_PROGRESS) {
                user_tasks[TaskStatus::NEW] -= count;
                if (!user_tasks[TaskStatus::NEW])
                    user_tasks.erase(TaskStatus::NEW);
            } else if (status == TaskStatus::TESTING) {
                user_tasks[TaskStatus::IN_PROGRESS] -= count;
                if (!user_tasks[TaskStatus::IN_PROGRESS])
                    user_tasks.erase(TaskStatus::IN_PROGRESS);
            } else if (status == TaskStatus::DONE) {
                user_tasks[TaskStatus::TESTING] -= count;
                if (!user_tasks[TaskStatus::TESTING])
                    user_tasks.erase(TaskStatus::TESTING);
            }
        }
        if (!updated_tasks[TaskStatus::IN_PROGRESS])
            updated_tasks.erase(TaskStatus::IN_PROGRESS);
        if (!updated_tasks[TaskStatus::TESTING])
            updated_tasks.erase(TaskStatus::TESTING);
        if (!updated_tasks[TaskStatus::DONE])
            updated_tasks.erase(TaskStatus::DONE);
        TasksInfo untouched_tasks = user_tasks;
        untouched_tasks.erase(TaskStatus::DONE);
        for (auto& [status, count] : updated_tasks) {
            if (status == TaskStatus::IN_PROGRESS) {
                user_tasks[TaskStatus::IN_PROGRESS] += count;
            } else if (status == TaskStatus::TESTING) {
                user_tasks[TaskStatus::TESTING] += count;
            } else if (status == TaskStatus::DONE) {
                user_tasks[TaskStatus::DONE] += count;
            }
        }
        return {updated_tasks, untouched_tasks};
    }

private:
    map<string, TasksInfo> data;
};

// Принимаем словарь по значению, чтобы иметь возможность
// обращаться к отсутствующим ключам с помощью [] и получать 0,
// не меняя при этом исходный словарь
void PrintTasksInfo(TasksInfo tasks_info) {
  cout << tasks_info[TaskStatus::NEW] << " new tasks" <<
      ", " << tasks_info[TaskStatus::IN_PROGRESS] << " tasks in progress" <<
      ", " << tasks_info[TaskStatus::TESTING] << " tasks are being tested" <<
      ", " << tasks_info[TaskStatus::DONE] << " tasks are done" << endl;
}

int main() {
  TeamTasks tasks;
  tasks.AddNewTask("Alice");
  for (int i = 0; i < 4; ++i) {
    tasks.AddNewTask("Alice");
  }
  PrintTasksInfo(tasks.GetPersonTasksInfo("Alice"));
    {auto [updated_tasks, untouched_tasks] = tasks.PerformPersonTasks("Alice", 5);
    PrintTasksInfo(updated_tasks);
    PrintTasksInfo(untouched_tasks);}
  PrintTasksInfo(tasks.GetPersonTasksInfo("Alice"));
    std::cout << std::endl;
    {auto [updated_tasks, untouched_tasks] = tasks.PerformPersonTasks("Alice", 5);
        PrintTasksInfo(updated_tasks);
        PrintTasksInfo(untouched_tasks);}
    std::cout << std::endl;
    {auto [updated_tasks, untouched_tasks] = tasks.PerformPersonTasks("Alice", 1);
        PrintTasksInfo(updated_tasks);
        PrintTasksInfo(untouched_tasks);}
    PrintTasksInfo(tasks.GetPersonTasksInfo("Alice"));
    std::cout << std::endl;
    for (int i = 0; i < 5; ++i) {
        tasks.AddNewTask("Alice");
    }
    PrintTasksInfo(tasks.GetPersonTasksInfo("Alice"));
    {auto [updated_tasks, untouched_tasks] = tasks.PerformPersonTasks("Alice", 2);
        PrintTasksInfo(updated_tasks);
        PrintTasksInfo(untouched_tasks);}
    PrintTasksInfo(tasks.GetPersonTasksInfo("Alice"));


    return 0;
}