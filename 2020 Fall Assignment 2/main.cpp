/* @Author
Student Name: Ahmet Polat
Student ID : 150170109
Date: 26/11/2020 
*/
#include <iostream>
#include <fstream>
#include "circuit.h"

using namespace std;

int main(int argc, char* argv[]){

    char input_char;
    double input_double;

    circuit devre;
    devre.create();

    fstream input_file(argv[1], ios_base::in);

    while (input_file >> input_char >> input_double){
        if(input_double == 0){           
            devre.circuit_info();
        }
        else if(input_double < 0){
            devre.remove_resistor(input_char, input_double);
        }
        else if(input_double > 0){
            devre.add_resistor(input_char, input_double);
        }
    }

    devre.clear();

    return 0;
}


