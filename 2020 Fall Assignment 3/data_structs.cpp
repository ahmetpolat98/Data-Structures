/* @Author
Student Name: Ahmet Polat
Student ID : 150170109
Date: 09/01/2021 
*/
#include <iostream>
#include <fstream>
#include "data_structs.h"

using namespace std;

void Stack::init(){
    head = NULL;
}
void Stack::close(){
    Subtask *iter;
    while (head)
    {
        iter = head;
        head = head->next;
        delete iter;      
    }
}
void Stack::push(Subtask *new_data){
    Subtask *add_data = new Subtask;
    *add_data = *new_data;
    add_data->next = head;
    head = add_data;
}
Subtask* Stack::pop(){
    Subtask* top_node = head;
    Subtask* temp_node = new Subtask;
    head = head->next;
    top_node->next = NULL;
    *temp_node = *top_node;
    delete top_node;
    return temp_node;
}
bool Stack::isEmpty(){
    return head == NULL;
}


void Queue::init(){
    head = NULL;
    tail = NULL;
}
void Queue::close(){
    Process *iter;
    while (head)
    {
        iter = head;
        head = head->next;
        iter->task_stack.close();
        delete iter;
    }   
}
void Queue::queue(Process *new_data){
    Process *add_data = new Process;
    *add_data = *new_data;
    add_data->next = NULL;

    if (isEmpty())
    {
        tail = add_data;
        head = tail;
    }
    else
    {
        tail->next = add_data;
        tail = add_data;
    }   
}
Process* Queue::dequeue(int &cpu_time){
    Subtask* pop_data = head->task_stack.pop();
    Process* top_node = head;
    Process* temp_node = new Process;
    cpu_time += pop_data->duration;
    
    cout << top_node->name << " " << pop_data->name << endl;
    if (head->task_stack.isEmpty())
    {

        head = head->next;
        top_node->next = NULL;
        *temp_node = *top_node;
        delete top_node;
        return temp_node;
    }
    return NULL;  
}
bool Queue::isEmpty(){
    return head == NULL;
}
Process* Queue::front(){
    return head;
}


void MultiQueue::init(){
    for (int i = 0; i < 3; i++)
    {
        queues[i].init();
    }
}
void MultiQueue::close(){
    for (int i = 0; i < 3; i++)
    {
        queues[i].close();
    }
}
void MultiQueue::queue(Process *new_data){
    int priority = new_data->priority - 1;
    if (priority >= 0 || priority < 3)
    {
        queues[priority].queue(new_data);
    }
    else
    {
        cout << "invalid priority" << endl;
    }
}
Process* MultiQueue::dequeue(int priority, int &cpu_time){
    return queues[priority-1].dequeue(cpu_time);
}
bool MultiQueue::isEmpty(){
    bool flag = true;
    for (int i = 0; i < 3; i++)
    {
        if (!queues[i].isEmpty())
        {
            flag = false;
            return flag;
        }
    }
    return flag;
}
Process* MultiQueue::front(int priority){
    return queues[priority-1].front();
}

/*
void Stack::print(){
    Subtask *iter = head;
    while (iter)
    {
        cout << "subtask: " << iter->name << " " << iter->duration << endl;
        iter = iter->next;
    }
}
void Process::print(){
    cout << "process: " << name << " " << priority << " " << endl << arrival_time << " " << task_count << endl;
    task_stack.print();
}
void Queue::print(){
    Process *iter_process = head;
    while (iter_process)
    {
        iter_process->print();
        iter_process = iter_process->next;
        if (head == tail)
        {
            break;
        }
    }
}
void MultiQueue::print(){
    cout << "----1.queue:---- " << endl;
    queues[0].print();
    cout << "----2.queue:---- " << endl;
    queues[1].print();
    cout << "----3.queue:---- " << endl;
    queues[2].print();
}
*/
