#ifndef TASKLIST_H
#define	TASKLIST_H
#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <cstring>
#include "Functions.h"
using namespace std;

const int ASCENDING = 0;
const int DESCENDING = 1;

template <class T>
class Node {
protected:
    T data; // to hold generic data of type T
    Node<T>* next; // to hold pointer to next item
    //Node<T>* prev; // to hold pointer for previous item
public:

    Node() {
        next = NULL;
    }

    Node(T dataItem, Node<T>* nextPtr = NULL) {
        data = dataItem;
        next = nextPtr;
    }

    Node<T>* getNext() {
        return next;
    }

    void setNext(Node<T>* ptr) {
        next = ptr;
    }

    T getData() {
        return data;
    }

    void setData(T dataItem) {
        data = dataItem;
    }

    friend ostream& operator<<(ostream& out, Node<T>* n) {
        if (n == NULL) {
            exit(0);
        }
        cout << n->data << endl;
        return out;
    }
};

template< class T>
class FCISLL {
private:
    Node<T> *head;
    Node<T> *tail;
    int size;
    Node<T>* mergeSort(Node<T>* first, int len, bool (*comp)(T& item1, T& item2));
    Node<T>* merging(Node<T>* left, int leftlen, Node<T>* right, int rightlen, bool (*comp)(T& item1, T& item2));
    void reverseList();
public:
    FCISLL();
    void addToHead(T item);
    void addToTail(T item);
    void addInOrder(T item);
    void writeIntoFile(ofstream & outfile);
    void readFromFile(ifstream & infile);
    void write(ofstream & outfile, Task & data);
    void sort(bool (*comp)(T& item1, T& item2), int order);
    void Merge(FCISLL<T>* anotherList, bool (*comp)(T& item1, T& item2), int order);
    int search(T item);
    int length();
    Node<T>* getHead();
    T removeHead();
    T removeTail();
    T removeFromIndex(int i);
    T removeItem(T item);
    bool isEmpty();
    bool removeWithPredicate(bool (*predicate)(T& item));
    ~FCISLL();
    template <class TT>
    friend ostream& operator<<(ostream&, FCISLL< TT > &);
};

template <class T>
FCISLL<T>::FCISLL() {
    head = NULL;
    tail = NULL;
    size = 0;
}

template <class T>
Node<T>* FCISLL<T>::getHead() {
    return this->head;
}

template <class T>
void FCISLL<T>::sort(bool (*comp)(T& item1, T& item2), int order) {
    head = mergeSort(head, size, comp);
    if (order == DESCENDING) {
        reverseList();
    }
}

template <class T>
Node<T>* FCISLL<T>::mergeSort(Node<T>* first, int len, bool (*comp)(T& item1, T& item2)) {
    if (len < 1) {
        return first;
    }
    if (len < 2) {
        first->setNext(NULL);
        return first;
    }
    Node<T>* middle = first;
    int mid = 0;
    while (mid < len / 2) {
        middle = middle->getNext();
        mid++;
    }
    mid = len / 2;
    int end = len - mid;
    first = mergeSort(first, mid, comp);
    middle = mergeSort(middle, len - mid, comp);
    return merging(first, mid, middle, end, comp);
}

template <class T>
Node<T>* FCISLL<T>::merging(Node<T>* left, int leftlen, Node<T>* right, int rightlen, bool (*comp)(T& item1, T& item2)) {
    Node<T>* newHead = new Node<T>();
    newHead->setNext(NULL);
    Node<T>* temp = newHead;
    while (leftlen > 0 && rightlen > 0) {
        T data1 = left->getData();
        T data2 = right->getData();
        if (comp(data1, data2)) {
            temp->setNext(left);
            temp = temp->getNext();
            left = left->getNext();
            leftlen--;
        } else {
            temp->setNext(right);
            temp = temp->getNext();
            right = right->getNext();
            rightlen--;
        }
    }
    while (leftlen > 0) {
        temp->setNext(left);
        temp = temp->getNext();
        left = left->getNext();
        leftlen--;
    }
    while (rightlen > 0) {
        temp->setNext(right);
        temp = temp->getNext();
        right = right->getNext();
        rightlen--;
    }
    temp = newHead;
    newHead = newHead->getNext();
    delete temp;
    return newHead;
}

template <class T>
void FCISLL<T>::reverseList() {
    Node<T>* tmp = head;
    Node<T>* prev = head;
    Node<T>* save = NULL;
    while (tmp) {
        save = tmp->getNext();
        tmp->setNext(prev);
        prev = tmp;
        tmp = save;
    }
    head->setNext(NULL);
    head = prev;
}

template <class T>
void FCISLL< T >::addToHead(T item) {
    Node<T>* ptr = new Node<T>(item, head);
    if (head == NULL) {
        head = ptr;
        tail = ptr;
    } else {
        head = ptr;
    }
}

template <class T>
void FCISLL<T>::addToTail(T item) {
    Node<T>* ptr = new Node<T>(item, NULL);
    tail->setNext(ptr);
    tail = ptr;
}

template <class T>
void FCISLL<T>::Merge(FCISLL<T>* anotherList, bool (*comp)(T& item1, T& item2), int order) {
    this->sort(comp, order);
    FCISLL<T>* newList = new FCISLL<T>();
    Node<T>* temp = anotherList->getHead();
    while (temp != NULL) {

        T data = temp->getData();
        newList->addInOrder(data);
        temp = temp->getNext();
    }
    newList->sort(comp, order);
    temp = newList->getHead();
    head = merging(head, size, temp, newList->length(), comp);
}

template <class T>
void FCISLL<T>::addInOrder(T item) {
    if (head == NULL) {
        size++;
        addToHead(item);
        return;
    }
    Node<T>* pPtr = head;
    Node<T>* prev = NULL;
    while (pPtr->getNext() != NULL) {
        if (pPtr->getData() <= item) {
            break;
        }
        prev = pPtr;
        pPtr = pPtr->getNext();
    }
    if (pPtr == head) {
        addToHead(item);
    } else if (pPtr == tail) {
        addToTail(item);
    } else {
        Node<T>* nPtr = new Node<T>();
        nPtr->setData(item);
        nPtr->setNext(pPtr);
        prev->setNext(nPtr);
    }
    size++;
}

template <class T>
int FCISLL<T>::length() {
    return this->size;
}

template <class T>
ostream& operator<<(ostream& out, FCISLL<T> & list) {
    Node<T>* temp = list.head;
    if (list.head == NULL) {
        return out;
    }
    while (temp) {
        out << temp;
        temp = temp->getNext();
    }
    return out;
}

template <class T>
void FCISLL<T>::readFromFile(ifstream & infile) {
    while (true) {
        string desc, name, date;
        int num, prio;
        getline(infile, name);
        getline(infile, desc);
        infile >> prio;
        infile.ignore();
        getline(infile, date);
        infile >> num;
        infile.ignore();
        if (infile.eof()) {
            break;
        }
        while (true) {
            if (prio >= 1 && prio <= 5) {
                break;
            } else {
                cout << "Enter a priority again <= 5 and >= 1: ";
                cin >> prio;
            }
        }
        Task node(name, desc, prio, date, num);
        addInOrder(node);
    }
}

template <class T>
void FCISLL<T>::writeIntoFile(ofstream & outfile) {
    Node<T>* temp = head;
    while (temp) {
        T data = temp->getData();
        write(outfile, data);
        temp = temp->getNext();
    }
}

template <class T>
void FCISLL<T>::write(ofstream & outfile, Task & data) {
    outfile << data.getName() << endl;
    outfile << data.getDescription() << endl;
    outfile << data.getPriority() << endl;
    outfile << data.getDate() << endl;
    outfile << data.getNumberOfDays() << endl;
}

template <class T>
FCISLL<T>::~FCISLL() {
    Node<T> * temp = head;
    Node<T> * del = head;
    while (temp) {
        del = temp;
        temp = temp->getNext();
        delete del;
    }
}

template <class T>
int FCISLL<T>::search(T item) {
    int count = 0;
    Node<T> * temp = head;
    while (temp) {
        if (temp->getData() == item) {
            return count;
        }
        temp = temp->getNext();
    }
    return -1;
}

template <class T>
T FCISLL<T>::removeHead() {
    size--;
    if (head == NULL) {
        exit(0);
    } else if (head == tail) {
        T data = head->getData();
        delete head;
        head = tail = NULL;
        return data;
    }
    Node<T>* temp = head;
    T data = head->getData();
    delete temp;
    head = head->getNext();
    return data;
}

template <class T>
T FCISLL<T>::removeTail() {
    size--;
    if (head == NULL) {
        exit(0);
    } else if (head == tail) {
        Node<T>* temp = head;
        T data = head->getData();
        delete temp;
        head = tail = NULL;
        return data;
    }
    Node<T>* temp = head;
    Node<T>* del = tail;
    int c = 0;
    while (temp->getNext() != tail) {
        c++;
        temp = temp->getNext();
    }
    T data = tail->getData();
    delete del;
    temp->setNext(NULL);
    tail = temp;
    return data;
}

template<class T>
T FCISLL<T>::removeFromIndex(int i) {
    size--;
    if (i >= size || i < 0) {
        exit(0);
    } else if (i == 0) {
        return removeHead();
    } else if (i == size - 1) {
        return removeTail();
    } else {
        Node<T> * temp = head;
        int count = 0;
        while (count < i) {
            temp = temp->getNext();
        }
        Node<T>* del = temp->getNext();
        T data = del->getData();
        temp->setNext(del->getNext());
        delete del;
        return data;
    }
}

template <class T>
T FCISLL<T>::removeItem(T item) {
    if (head->getData() == item) {
        return removeHead();
    } else if (tail->getData() == item) {
        return removeTail();
    } else {
        int index = search(item);
        if (index >= 0) {
            return removeFromIndex(index);
        }
    }
}

template <class T>
bool FCISLL<T>::removeWithPredicate(bool (*predicate)(T& item)) {
    Node<T> * temp = head;
    while (temp) {
        T data = temp->getData();
        bool t = (*predicate)(data);
        if(t){
            this->removeItem(data);
        }
        temp = temp->getNext();
    }
    return true;
}

template <class T>
bool FCISLL<T>::isEmpty() {
    if (head == NULL) {
        return true;
    } else {
        return false;
    }
}

#endif	/* TASKLIST_H */
