/*
PLEASE, DO NOT CHANGE void display(bool verbose, bool testing), int getUsableDay() and int getUsableTime() FUNCTIONS.
YOU HAVE TO WRITE THE REQUIRED  FUNCTIONS THAT IS MENTIONED ABOVE. YOU CAN ADD NEW FUNCTIONS IF YOU NEED.
*/

#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <iomanip>

#include "task_management_tool.h"

using namespace std; 


void WorkPlan::display(bool verbose,bool testing)
{
	string inone="***";
	if (head!=NULL)
	{
		Task *pivot =new Task;
		Task *compeer =new Task;
			
		pivot=head;
		do
		{
			if(testing)
				inone+=" ";
			else
				cout << pivot->day <<". DAY"<< endl;
			compeer=pivot;
			while(compeer!=NULL)
			{
				string PREV= compeer->previous!=NULL?compeer->previous->name:"NULL";
				string NEXT=compeer->next!=NULL?compeer->next->name:"NULL";
				string CONT=compeer->counterpart!=NULL?compeer->counterpart->name:"NULL";
				if (testing)
					inone+=compeer->name;
				else
					if(verbose)
						cout<<"\t"<<setw(2)<< compeer->time <<":00\t"<< PREV<<"\t<- "<< compeer->name <<"("<< compeer->priority <<")->\t"<<NEXT <<"\t |_"<<CONT<<endl;
					else
						cout<<"\t"<<setw(2)<< compeer->time <<":00\t"<< compeer->name <<"("<< compeer->priority <<")"<<endl;				
				compeer=compeer->counterpart;
			}
			pivot=pivot->next;
		}while(pivot!=head);
		if(testing)
		{
			cout<<inone<<endl;
			cout<<"(checking cycled list:";
			if (checkCycledList())
				cout<<" PASS)"<<endl;
			else
				cout<<" FAIL)"<<endl;
		}
	}
	else
		cout<<"There is no task yet!"<<endl;
}

int WorkPlan::getUsableDay()
{
	return usable_day;
}

int WorkPlan::getUsableTime()
{
	return usable_time;
}


void WorkPlan::create()
{	
	head = NULL;
}

void WorkPlan::close()
{
	delete head;
}

void WorkPlan::add(Task *task)
{

	Task *iter = head;

	bool check_day = false; //For same day hours, was day created before(true)? or first time(false)? 


	if(head == NULL){


		head = new Task;
		head->name = task->name;


		head->day = task->day;
		head->time = task->time;
		head->priority = task->priority;

		head ->next = head;
		head ->previous = head;

		head ->counterpart = NULL;

	}

	else
	{
		//check_day control
		while (iter->next != head)
		{
			if (iter->day == task->day)
			{
				check_day = true; //same day was created before
				break;
			}
			iter = iter->next;
		}

		if(task->day == head->day){
			check_day = true;
			iter = head;
		}
		
		//if day adding first time
		if(!check_day){
			

			iter = head;
			//adding first day

			//adding smaller day than head
			if(head->day > task->day){

				task->next = head;
				task->previous = head->previous;

				task->counterpart = NULL;

				head ->previous = task;

				while (iter ->next != head)
				{
					iter = iter->next;
				}
				iter ->next = task;
				
				head = task;
			}

			//adding other days
			else{ 
				while (iter->next != head && iter->next->day < task->day){
					iter = iter->next;
				}
				task->next = iter->next;
				iter->next->previous= task;
				iter->next = task;
				task->previous = iter;

				task->counterpart = NULL;				
			}
		}

		//if day was created before and adding same day's other hours
		else{
			//earlier than first hour
			if(task->time < iter->time){
				
				task->next = iter->next;
				task->previous = iter->previous;

				iter->next->previous = task;
				iter->previous->next = task;

				task->counterpart = iter;

				iter->next = NULL;
				iter->previous = NULL;
			}
			//same hour first hour
			else if(task->time == iter->time){  
				if(task->priority > iter->priority){
					iter->previous->next = task;
					iter->next->previous = task;
					task->next = iter->next;
					task->previous = iter->previous;
					task->counterpart = iter->counterpart;

					checkAvailableNextTimesFor(iter);
					iter->day = usable_day;
					iter->time = usable_time;

					iter->next = NULL;
					iter->previous = NULL;

					add(iter);				
				}
				else
				{
					checkAvailableNextTimesFor(task);
					task->day = usable_day;
					task->time = usable_time;
					add(task);
				}
				
			}

			else{
				while(iter->counterpart != NULL && iter->counterpart->time < task->time){
					iter = iter->counterpart;
				}
				if(iter->counterpart != NULL && iter->counterpart->time == task->time){	//if times are same
					if(task->priority > iter->counterpart->priority){
						Task *temp = iter->counterpart;

						iter->counterpart = task;
						task->counterpart = temp->counterpart;

						checkAvailableNextTimesFor(temp);
						temp->day = usable_day;
						temp->time = usable_time;

						temp->counterpart = NULL;

						add(temp);
					}
					else
					{
						checkAvailableNextTimesFor(task);
						task->day = usable_day;
						task->time = usable_time;
						add(task);
					}
					
				}
				else{	//other times
					task->counterpart = iter->counterpart;
					task->next = NULL; // 
					task->previous = NULL; //
					iter->counterpart = task;					
				}
			}
		}	
	}
} 

Task * WorkPlan::getTask(int day, int time)
{

	Task *iter = head;

	while(iter->next != head && iter->day < day){
		iter = iter->next;
	}
	if(iter->day == day){
		while(iter->counterpart != NULL && iter->time < time){
			iter = iter->counterpart;
		}
		if(iter->time == time){
			return iter;
		}
	}	
	return NULL;
}

void WorkPlan::checkAvailableNextTimesFor(Task *delayed)	
{	

	Task *iter = delayed;
	Task *iter_day = head;

	bool check = false;

	//iter_day indicate delayed day's first hour
	while (iter_day->day != delayed->day){
		iter_day = iter_day->next;
		if(delayed->day > iter_day->day){
			cout << "day not found" << endl;
			break;
			
		}
	}
	
	while(!check){ 
		while(iter->counterpart != NULL){
			if((iter->counterpart->time - iter->time) >=2 ){
				usable_day = iter_day->day;
				usable_time = iter->time + 1;
				check = true;
				break;
			}
			iter = iter->counterpart;
		}
		iter_day = iter_day->next;
		iter = iter_day;
		if(iter_day == head && check == false){
			cout << "not available time" << endl;
			usable_day = 99; //
			usable_time = 99; //
			break;
		}
	}	
}

void WorkPlan::delayAllTasksOfDay(int day)
{
	Task *iter = head;
	Task *temp = new Task;

	bool day_found = true;

	while (iter->day != day)
	{
		iter = iter->next;
		if(day > iter->day)
		{
			cout << "day not found" << endl;
			day_found = false;
			break;
		}
	}

	if(day_found){
		Task *newone = new Task;

		while (iter->counterpart != NULL)
		{
			newone->name=new char [strlen(iter->name)];
			newone->name = iter->name;
			newone->priority = iter->priority;

			checkAvailableNextTimesFor(iter);

			cout<<getUsableDay()<<".day and "<<std::setw(2)<<getUsableTime()<<":00 is the first available day and hour for delaying the task "<<iter->name<<" that is on "<<iter->day<<".day at "<<std::setw(2)<< iter->time <<":00"<<endl;
		
			newone->day = getUsableDay();
			newone->time = getUsableTime();

			temp = iter;
			iter = iter->counterpart;

			add(newone);
			remove(temp);

		}
	}	
}

void WorkPlan::remove(Task *target)
{
	Task *iter = head;

	while (iter->next != head && iter->day != target->day)
	{
		iter = iter->next;
	}
	if(iter->day == target->day)
	{
		if (iter->time == target->time)  //if target is first hour in day
		{
			iter = iter->previous;
			if(target->counterpart != NULL){  //if target is not alone time in day
				target->previous->next = target->counterpart;
				target->counterpart->next = target->next;
				target->next->previous = target->counterpart;
				target->counterpart->previous = target->previous;

			}
			else  //if target is alone time in day
			{
				target->previous->next = target->next;
				target->next->previous = target->previous;
				delete target;
			}			
		}
		else  //if target is not first hour in day
		{
			while (iter->counterpart != NULL && iter->counterpart != target)
			{
				iter = iter->counterpart;
			}
			if(iter->counterpart->time == target->time){
				iter->next = target->next;
				delete target;
			}
			else
			{
				cout << "target not found" << endl;
			}
		}		
	}
	else
	{
		cout << "target not found" << endl;
	}	
}

bool WorkPlan::checkCycledList()
{				
	Task *pivot=new Task();
	pivot=head;
	int patient=100;
	bool r=false;
	while (pivot!=NULL&&patient>0)
	{		
		patient--;
		pivot=pivot->previous;
		if(pivot==head)
		{
			r=true;
			break;
		}
	}
	cout<<"("<<100-patient<<")";
	patient=100;
	bool l=false;
	while (pivot!=NULL&&patient>0)
	{		
		patient--;
		pivot=pivot->next;
		if(pivot==head)
		{
			l=true;
			break;
		}
	}
	return r&l;
}
