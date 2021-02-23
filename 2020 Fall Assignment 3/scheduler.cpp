/* @Author
Student Name: Ahmet Polat
Student ID : 150170109
Date: 09/01/2021 
*/
#include <iostream>
#include <fstream>
#include "data_structs.h"

using namespace std;

struct CPU{
    MultiQueue processes_queue;
    int cpu_time;
    int special_condition;
    int lateness;
    void init();
    void close();
    void processing();
    bool isItTime(int priority);
    bool isThereProcess();
};

void CPU::init(){
    processes_queue.init();
    cpu_time = 0;
    special_condition = 0;
    lateness = 0;
}
void CPU::close(){
    processes_queue.close();
}
void CPU::processing(){
    
    while (isThereProcess())
    {
        Process* temp = new Process;
        if(isItTime(1))
        {
            temp = processes_queue.dequeue(1, cpu_time);
            if(temp){
                lateness += cpu_time - temp->deadline;
            }
        }
        else if (isItTime(2) && special_condition != 2)
        {
            temp = processes_queue.dequeue(2, cpu_time);
            if(temp){
                lateness += cpu_time - temp->deadline;
            }
            special_condition += 1;
        }
        else if (isItTime(3))
        {                        
            temp = processes_queue.dequeue(3, cpu_time);
            if(temp){
                lateness += cpu_time - temp->deadline;
            }           
            special_condition = 0;
        }
        else if (special_condition == 2)
        {
            special_condition = 0;
        }       
    }
    cout << "Cumulative Lateness: " << lateness << endl; 
}
bool CPU::isItTime(int priority){
    Process* temp = processes_queue.front(priority);
    if (temp)
    {
        int time = temp->arrival_time;
        if (cpu_time >= time) 
        {
            return true;
        }   
    }
    return false;
}
bool CPU::isThereProcess(){
    if(processes_queue.isEmpty()){
        return false;
    }
    else
    {
        bool flag = false;
        while (!flag)
        {
            for(int priority = 1; priority < 4; priority++)
            {
                if(isItTime(priority)){
                    flag = true;
                }
            }
            if(!flag){
                cpu_time += 1;
            }
        }   
        return flag;                     
    }     
}

int main(int argc, char* argv[]){

    CPU cpu;
    cpu.init();

    Process *add_process = new Process;
    
    fstream input_file(argv[1], ios_base::in);

    while(input_file >> add_process->name >> add_process->priority >> add_process->arrival_time >> add_process->task_count)
    {        
        add_process->deadline = 0;
        add_process->deadline += add_process->arrival_time;
        add_process->task_stack.init();

        for(int i = 0; i < add_process->task_count; i++)
        {
            Subtask *add_subtask = new Subtask;
            add_subtask->next = NULL;
            input_file >> add_subtask->name >> add_subtask->duration;
            add_process->deadline += add_subtask->duration;
            
            add_process->task_stack.push(add_subtask);
        }
        cpu.processes_queue.queue(add_process);
    }
    cpu.processing();

    cpu.close();

    return 0;
}