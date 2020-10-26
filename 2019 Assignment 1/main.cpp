#include <iostream>
#include <fstream>

using namespace std;

struct node{
    int size;
    int quant;
    node *next;
};

struct stock{
    node *head;
    void create();
    void add_stock(int);
    void sell(int);
    void current_stock();
    void clear();
};

void stock::create(){
    head = NULL;
}

void stock::add_stock(int shoes_number){

    node *iter;
    iter = head;

    //adding first element
    if(head == NULL){
        head = new node;
        head -> size = shoes_number;
        head -> quant = 1;
        head -> next = NULL;
    }

    //adding smaller than first element, head is changing
    else if(head -> size > shoes_number){
        node *temp = new node;
        node *temp1 = head;
        temp -> size = shoes_number;
        temp -> quant = 1;
        temp -> next = temp1;
        head = temp;
    }

    else{
        while (iter -> next != NULL && iter -> next -> size <= shoes_number){
            iter = iter ->next;
        }
        if(iter ->size == shoes_number){   //adding same size
            iter ->quant += 1;
        }
        else{   //adding between or last
            node *temp2 = new node;
            temp2 ->next = iter ->next;
            iter ->next = temp2;
            temp2 ->size = shoes_number;
            temp2 ->quant = 1;
        }
    }
}

void stock::sell(int size_number){
    node *iter = head;

     //if selling size is head
    if(iter -> size == size_number){
        iter ->quant -= 1;

        //head is changing
        if(iter ->quant == 0){
            node *temp1 = head;
            head = head ->next;
            free(temp1);
        }
    }
    
    else{
        while(iter ->next != NULL && iter ->next ->size != size_number){
            iter = iter ->next;
        }
        if(iter ->next !=NULL && iter->next ->size == size_number){
            iter ->next ->quant -= 1;
            
            if(iter ->next ->quant == 0){
                node *temp = iter ->next;
                iter ->next = iter ->next ->next;
                delete temp;
            }
        }
        else
        {
            cout << "NO_STOCK" << endl;
           
        }
    }
}

void stock::current_stock(){
    node *iter = head;
    while(iter != NULL){
        cout << iter ->size << ":" << iter ->quant << endl;
        iter = iter ->next;
    }
}

void stock::clear(){
    delete head;
}

int main(int argc, char** argv){

    stock shop_manage;
    shop_manage.create();

    int input_size;

    std::fstream input_file(argv[1], std::ios_base::in);

     while (input_file >> input_size)
    {
        if(input_size > 0){
            shop_manage.add_stock(input_size);
        }
        else if(input_size < 0){
            shop_manage.sell(-input_size);
        }
        else if(input_size == 0){
            shop_manage.current_stock();
        }
    }

    shop_manage.clear();
    
    return 0;
}

    
    


    
