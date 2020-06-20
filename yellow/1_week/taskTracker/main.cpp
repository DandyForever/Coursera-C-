#include <iostream>
#include <tuple>
#include <map>

using namespace std;

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
    tuple<TasksInfo, TasksInfo> PerformPersonTasks(const string& person, int task_count) {
        TasksInfo updated, tmp = data[person];
        for (const auto& item : data[person]) {
            for (int i = 0; i < item.second; i++) {
                if (!task_count) break;
                switch (item.first) {
                    case TaskStatus::NEW: {
                        updated[TaskStatus::IN_PROGRESS]++;
                        tmp[TaskStatus::NEW]--;
                        tmp[TaskStatus::IN_PROGRESS]++;
                        break;
                    }
                    case TaskStatus::IN_PROGRESS: {
                        updated[TaskStatus::TESTING]++;
                        tmp[TaskStatus::IN_PROGRESS]--;
                        tmp[TaskStatus::TESTING]++;
                        break;
                    }
                    case TaskStatus::TESTING: {
                        updated[TaskStatus::DONE]++;
                        tmp[TaskStatus::TESTING]--;
                        tmp[TaskStatus::DONE]++;
                        break;
                    }
                    default:
                        break;
                }
                task_count--;
            }
        }
        TasksInfo untouched;
        for (const auto& item : tmp) {
            if (item.first != TaskStatus::DONE) {
                if (updated.count(item.first))
                    untouched[item.first] = item.second - updated.at(item.first);
                else
                    untouched[item.first] = item.second;
                if (!untouched[item.first])
                    untouched.erase(item.first);
            }
        }
        data[person] = tmp;
        return tie (updated, untouched);
    }

private:
    map <string, TasksInfo> data;
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
