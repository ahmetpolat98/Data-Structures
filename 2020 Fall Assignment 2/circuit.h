/* @Author
Student Name: Ahmet Polat
Student ID : 150170109
Date: 26/11/2020 
*/
#ifndef CIRCUIT_H
#define CIRCUIT_H

#include <iostream>
#include "resistor.h"

using namespace std;


struct circuit{
    resistor *head;

    void create();
    void add_resistor(char, double);
    int remove_resistor(char, double);
    void delete_resistor(char);
    void circuit_info();
    void clear();
};

void circuit::create(){
    this->head = NULL;
}

void circuit::add_resistor(char group, double value){

    //Adding first node
    if(head == NULL){
        head = new resistor;
        head->group = group;
        head->value = value;
        head->quantity = 1;
        head->next = NULL;
    }
    //adding before head, head is changing
    else if(head->group > group){
        resistor *temp = new resistor;
        temp->group = group;
        temp->value = value;
        temp->quantity = 1;
        temp->next = head;
        head = temp;
    }
    //
    else{
        resistor *iter = head;
        while(iter->next != NULL && iter->next->group <= group){
            iter = iter->next;
        }
        //adding same size
        if(iter->group == group){    
            if(iter->value == value){
                iter->quantity += 1; 
            }   
            else
            {
                return;
                //cout << "Resistor must be same" << endl;
            }         
        }
        //adding between or last
        else
        {
            resistor *res_to_add = new resistor;
            res_to_add->group = group;
            res_to_add->value = value;
            res_to_add->quantity = 1;
            res_to_add->next = iter->next;
            iter->next = res_to_add;
        }
    }
}

int circuit::remove_resistor(char group, double value){
    resistor *iter = head;
    //stop the node we want to remove
    while (iter->next != NULL && iter->group != group){
        iter = iter->next;
    }
    if(iter->group == group && iter->value == -(value)){
        iter->quantity -= 1;
        if(iter->quantity == 0){
            delete_resistor(iter->group);
        }
    }
    else
    {
        cout << "NO_RESISTOR" << endl;
    }
    return 0;
}

void circuit::delete_resistor(char group){
    //delete head
    if(head->group == group){
        resistor *temp = head;
        head = head->next;
        delete temp;
    }
    //delete others
    else{
        resistor *iter = head;
        //stop before the node we want to delete
        while (iter->next != NULL && iter->next->group != group){
            iter = iter->next;
        }
        resistor *temp_del = iter->next;
        iter->next = iter->next->next;
        temp_del->next = NULL;
        delete temp_del;
    }
}

void circuit::circuit_info(){
    resistor *iter = head;
    resistor_info *resistor_info_head = NULL;
    double total_resistor = 0;

    while (iter)
    {
        total_resistor += (iter->value / iter->quantity);

        if(resistor_info_head == NULL){
            resistor_info_head = new resistor_info;
            resistor_info_head->next = NULL;
            resistor_info_head->value = iter->value;
            resistor_info_head->quantity = iter->quantity;
        }
        else if(resistor_info_head->value > iter->value){
            resistor_info *temp = new resistor_info;
            temp->value = iter->value;
            temp->quantity = iter->quantity;
            temp->next = resistor_info_head;
            resistor_info_head = temp;
        }
        else
        {
            resistor_info *iter_resistor_info = resistor_info_head;
            while(iter_resistor_info->next != NULL && iter_resistor_info->next->value <= iter->value){
                iter_resistor_info = iter_resistor_info->next;
            }
            //adding same value
            if(iter_resistor_info->value == iter->value){
                iter_resistor_info->quantity += iter->quantity;
            }
            //adding between or last
            else
            {
                resistor_info *resistor_info_add = new resistor_info;
                resistor_info_add->value = iter->value;
                resistor_info_add->quantity = iter->quantity;
                resistor_info_add->next = iter_resistor_info->next;
                iter_resistor_info->next = resistor_info_add;
            }
        }
        

        iter = iter->next;
    }  

    resistor_info *iter_info = resistor_info_head;
    while (iter_info)
    {
        cout << iter_info->value << ":" << iter_info->quantity << endl;
        iter_info = iter_info->next;
    }
    

    cout << "Total resistance=" << total_resistor << " ohm" << endl;
}

void circuit::clear(){

    while (head){
        resistor *iter = head;
        head = head->next;
        delete iter;
    }

}

#endif