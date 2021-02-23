/* @Author
Student Name: Ahmet Polat
Student ID : 150170109
Date: 09/01/2021 
*/
#ifndef DATA_STRUCTS_H
#define DATA_STRUCTS_H

#include <iostream>

using namespace std;

struct Subtask{
    string name;
    int duration;
    Subtask* next;
};

struct Stack{
    Subtask* head;
    void init();
    void close();
    void push(Subtask* in);
    Subtask* pop();
    bool isEmpty();
    //void print();//
};

struct Process{
    string name;
    int arrival_time;
    int deadline;
    int task_count;
    int priority;
    Stack task_stack;
    Process* next;
    //void print();//

};

struct Queue{
    Process* head;
    Process* tail;
    void init();
    void close();
    void queue(Process* in);
    Process* dequeue(int &cpu_time);
    bool isEmpty();
    Process* front();
    //void print();//
};

struct MultiQueue{
    Queue queues[3];
    void init();
    void close();
    void queue(Process* in);
    Process* dequeue(int priority, int &cpu_time);
    bool isEmpty();
    Process* front(int priority);
    //void print();//
};

#endif