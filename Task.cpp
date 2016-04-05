#include "Task.h"

Task::Task() {
    this->NumberOfDays = 0;
    this->Priority = 0;
    this->Date = "";
    this->Description = "";
    this->Name = "";
}

Task::Task(string name, string desc, int prio, string date, int num) {
    this->Name = name;
    this->Date = date;
    this->Description = desc;
    this->NumberOfDays = num;
    this->Priority = prio;
}

void Task::setDate(string date) {
    this->Date = date;
}

void Task::setName(string name) {
    this->Name = name;
}

void Task::setDescription(string desc) {
    this->Description = desc;
}

void Task::setPriority(int priority) {
    this->Priority = priority;
}

void Task::setNumberOfDays(int num) {
    this->NumberOfDays = num;
}

const string Task::getDate() {
    return Date;
}

const string Task::getName() {
    return Name;
}

const string Task::getDescription() {
    return Description;
}

const int Task::getPriority() {
    return Priority;
}

const int Task::getNumberOfDays() {
    return NumberOfDays;
}

ostream& operator<<(ostream & out, const Task & task) {
    cout << "Name: ";
    out << task.Name;
    cout << endl;
    cout << "Description: ";
    out << task.Description;
    cout << endl;
    cout << "Priority: ";
    out << task.Priority;
    cout << endl;
    cout << "Date: ";
    out << task.Date;
    cout << endl;
    cout << "Number of Days: ";
    out << task.NumberOfDays;
    cout << endl;
    return out;
}

bool Task::operator<=(Task other) {
    return (Priority <= other.getPriority());
}
Task & Task::operator=(const Task & rhs) {
    if (this == &rhs)
        return *this;
    Date = rhs.Date;
    Name = rhs.Name;
    Description = rhs.Description;
    NumberOfDays = rhs.NumberOfDays;
    Priority = rhs.Priority;
    return *this;
}

bool Task::operator==(const Task & rhs) {
    if (Date == rhs.Date && Name == rhs.Name && Description == rhs.Description &&
            NumberOfDays == rhs.NumberOfDays && Priority == rhs.Priority) {
        return true;
    }
    return false;
}