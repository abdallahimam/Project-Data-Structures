#ifndef FUNCTIONS_H
#define	FUNCTIONS_H
#include <iostream>
#include <string>
#include "Task.h"
#include "FCISLL.h"
#include <algorithm>

bool orderByDuration(Task & task1, Task & task2) {
    return (task1.getNumberOfDays() < task2.getNumberOfDays());
}

bool orderByDueDate(Task & task1, Task & task2) {
    string date = task1.getDate();
    int day1, month1, year1;
    day1 = (date[0] - '0');
    int cur = 1;
    if (isdigit(date.at(cur))) {
        day1 = day1 * 10 + (date.at(cur) - '0');
        cur++;
    }
    cur++;
    month1 = (date.at(cur++) - '0');
    if (isdigit(date.at(cur))) {
        month1 = month1 * 10 + (date.at(cur) - '0');
        cur++;
    }
    cur++;
    year1 = (date.at(cur) - '0')*1000 + (date.at(cur + 1) - '0')*100 + (date.at(cur + 2) - '0')*10 + (date.at(cur + 3) - '0');
    int day2, month2, year2;
    date = task2.getDate();
    day2 = (date[0] - '0');
    cur = 1;
    if (isdigit(date.at(cur))) {
        day2 = day2 * 10 + (date.at(cur) - '0');
        cur++;
    }
    cur++;
    month2 = (date.at(cur++) - '0');
    if (isdigit(date.at(cur))) {
        month2 = month2 * 10 + (date.at(cur) - '0');
        cur++;
    }
    cur++;
    year2 = (date.at(cur) - '0')*1000 + (date.at(cur + 1) - '0')*100 + (date.at(cur + 2) - '0')*10 + (date.at(cur + 3) - '0');
    if (year1 < year2) {
        return true;
    } else if (year1 == year2) {
        if (month1 < month2) {
            return true;
        } else if (month1 == month2) {
            if (day1 < day2) {
                return true;
            }
        }
    }
    return false;
}

bool compareDate(string date1, string date2) {
    string date = date1;
    int day1, month1, year1;
    day1 = (date[0] - '0');
    int cur = 1;
    if (isdigit(date.at(cur))) {
        day1 = day1 * 10 + (date.at(cur) - '0');
        cur++;
    }
    cur++;
    month1 = (date.at(cur++) - '0');
    if (isdigit(date.at(cur))) {
        month1 = month1 * 10 + (date.at(cur) - '0');
        cur++;
    }
    cur++;
    year1 = (date.at(cur) - '0')*1000 + (date.at(cur + 1) - '0')*100 + (date.at(cur + 2) - '0')*10 + (date.at(cur + 3) - '0');
    date = date2;
    int day2, month2, year2;
    day2 = (date[0] - '0');
    cur = 1;
    if (isdigit(date.at(cur))) {
        day2 = day2 * 10 + (date.at(cur) - '0');
        cur++;
    }
    cur++;
    month2 = (date.at(cur++) - '0');
    if (isdigit(date.at(cur))) {
        month2 = month2 * 10 + (date.at(cur) - '0');
        cur++;
    }
    cur++;
    year2 = (date.at(cur) - '0')*1000 + (date.at(cur + 1) - '0')*100 + (date.at(cur + 2) - '0')*10 + (date.at(cur + 3) - '0');
    if (year1 < year2) {
        return true;
    } else if (year1 == year2) {
        if (month1 < month2) {
            return true;
        } else if (month1 == month2) {
            if (day1 < day2) {
                return true;
            }
        }
    }
    return false;
}
#endif	/* FUNCTIONS_H */

