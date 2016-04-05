#include <iostream>
#include <fstream>
#include <string>
#include "Task.h"
#include "FCISLL.h"
#include "Functions.h"
using namespace std;

FCISLL<Task>* list = new FCISLL<Task>();

bool isPassed(Task & data) {
    string date = "11\12\2015";
    if (compareDate(data.getDate(), date)) {
        return true;
    } else {
        return true;
    }
}

int main() {
    ifstream infile;
    infile.open("MyTasks.txt", ios::in);
    if (!infile.fail()) {
        list->readFromFile(infile);
        infile.close();
    }
    ofstream outfile("SortedList.txt");
    if (!outfile.fail()) {
        list->writeIntoFile(outfile);
        outfile.close();
    }
    char choice;
    while (true) {
        cout << "are you want to enter the data of a new task?" << endl;
        cout << "if yes enter (Y) else enter (N)." << endl;
        cin >> choice;
        if (choice == 'Y' || choice == 'y') {
            string name, desc, date;
            int prio, num;
            cout << "Enter The Name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter The Description: ";
            getline(cin, desc);
            cout << "Enter The priority: ";
            while (true) {
                cin >> prio;
                if (prio >= 1 && prio <= 5) {
                    break;
                } else {
                    cout << "Enter a priority again: ";
                }
            }
            cout << "Enter The Date: ";
            cin >> date;
            cout << "The Number Of Taken Days: ";
            cin >> num;
            Task task(name, desc, prio, date, num);
            list->addInOrder(task);
        } else if (choice == 'N' || choice == 'n') {
            break;
        } else {
            cout << "you should enter either Y or N." << endl;
            continue;
        }
    }
    cout << *list << endl;
    list->sort(orderByDueDate, 0);
    list->Merge(list, orderByDueDate, 0);
    cout << *list << endl;
    list->removeWithPredicate(isPassed);
    if (list->isEmpty()) {
        cout << "The List is empty.\n";
    } else {
        cout << "the List is not empty.\n";
    }
    return 0;
}
