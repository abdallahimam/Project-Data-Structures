#ifndef TASK_H
#define	TASK_H
#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;
class Task {
public:
    Task();
    Task(string, string, int, string, int);
    void setDate(string);
    void setName(string);
    void setDescription(string);
    void setPriority(int);
    void setNumberOfDays(int);
    const string getDate();
    const string getName();
    const string getDescription();
    const int getPriority();
    const int getNumberOfDays();
    bool operator <= (const Task );
    Task & operator=(const Task & rhs);
    bool operator==(const Task & rhs);
    friend ostream& operator<<(ostream & out, const Task & task);
private:
    int NumberOfDays;
    int Priority;
    string Name;
    string Description;
    string Date;
};

#endif	