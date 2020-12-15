/* @Author
Student Name: Ahmet Polat
Student ID : 150170109
Date: 26/11/2020 
*/
#ifndef RESISTOR_H
#define RESISTOR_H


struct resistor{
    char group;
    double value;
    int quantity;
    resistor *next;
};

struct resistor_info{
    double value;
    int quantity;
    resistor_info *next;
};
#endif