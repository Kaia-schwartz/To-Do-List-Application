#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <limits>

using namespace std;

struct Task {
    string description;
    string dueDate;
    int priority;
};

class ToDoList {
private:
    vector<Task> tasks;

public:
    void addTask(const Task& task) {
        tasks.push_back(task);
    }

    void viewTasks() const {
        if (tasks.empty()) {
            cout << "No tasks available.\n";
            return;
        }

        for (size_t i = 0; i < tasks.size(); ++i) {
            cout << "Task " << i + 1 << ":\n";
            cout << "Description: " << tasks[i].description << "\n";
            cout << "Due Date: " << tasks[i].dueDate << "\n";
            cout << "Priority: " << tasks[i].priority << "\n\n";
        }
    }

    void removeTask(size_t index) {
        if (index < 0 || index >= tasks.size()) {
            throw out_of_range("Invalid task index");
        }
        tasks.erase(tasks.begin() + index);
    }
};

void showMenu() {
    cout << "1. Add Task\n";
    cout << "2. View Tasks\n";
    cout << "3. Remove Task\n";
    cout << "4. Exit\n";
}

int main() {
    ToDoList todoList;
    int choice = 0;

    while (choice != 4) {
        showMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
            cout << "Invalid input, please enter a number.\n";
            continue;
        }

        switch (choice) {
            case 1: {
                Task task;
                cin.ignore();

                cout << "Enter description: ";
                getline(std::cin, task.description);
                cout << "Enter due date: ";
                getline(std::cin, task.dueDate);
                cout << "Enter priority: ";
                cin >> task.priority;

                try {
                    if (task.priority < 1 || task.priority > 5 ) {
                        throw invalid_argument("Priority has to be between 1 to 5");
                    }
                    todoList.addTask(task);
                } catch (const exception& e) {
                    cout << "Error: " << e.what() << "\n";
                }
                break;
            }
            case 2:
                todoList.viewTasks();
                break;
            case 3: {
                size_t index;
                cout << "Enter task index to remove: ";
                cin >> index;

                try {
                    todoList.removeTask(index);
                } catch (const exception& e) {
                    cout << "Error: " << e.what() << "\n";
                }
                break;
            }
            case 4:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}


