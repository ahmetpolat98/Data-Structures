/*
YOU HAVE TO WRITE THE REQUIRED  FUNCTIONS. YOU CAN ADD NEW FUNCTIONS IF YOU NEED.
*/
#include <iostream>
#include <stdlib.h>
#include <string.h>

#include "counter.h"

using namespace std;

/* @Author
Student Name: Ahmet Polat
Student ID : 150170109
Date: 02/11/2020 */

	
int Counter::findindex(Token *arr,char elem[]){
	int i;
	for(i = 0; i <= token_count; i++){
		if(strcmp(arr[i].token ,elem) == 0){
        	return i;
    	}
	}
	return -1;	
} 

bool Counter::contains(char *token, char target){


	for(int i = 0; i < 2; i++){
		if(token[i] == '.'){
			return false;
		}
	}
	return true;
	
}

void Counter::read_and_count(){

    FILE *filePointer;
    char ch[3];
	int x;

    filePointer = fopen("pi_approximate", "r");

    if (filePointer == NULL)
    {
        printf("File is not available \n");
    }
    else
    { 
        while (ch[1] != EOF)
        {
            ch[0] = fgetc(filePointer);           
            ch[1] = fgetc(filePointer);
			ch[2] = '\0';

            fseek(filePointer, -1, SEEK_CUR);

			if(contains(ch, '.')){
				if(ch[1] != EOF && (ch[1] > 47 || ch[1] < 58)){
                
					if((x = findindex(token_array, ch)) != -1){
						token_array[x].count += 1;

					}
					else
					{
						token_array[token_count].token[0] = ch[0];
						token_array[token_count].token[1] = ch[1];
						token_array[token_count].token[2] = '\0';
						token_array[token_count].count = 1;

						token_count += 1;
					}		
            	}  
			}     
        }
    }
    fclose(filePointer);
}


Token *Counter::get_most_common_three(){

	Token *x= new Token[3];

	int i;

	//initialize
	x[0].token[0] = 'a';
	x[0].token[1] = 'b';
	x[0].token[2] = '\0';
	x[0].count = 0;

	x[1].token[0] = 'a';
	x[1].token[1] = 'b';
	x[1].token[2] = '\0';
	x[1].count = 0;

	x[2].token[0] = 'a';
	x[2].token[1] = 'b';
	x[2].token[2] = '\0';
	x[2].count = 0;

	for(i = 0; i < token_count; i++){
		
		if(token_array[i].count >= x[0].count){

			x[2].token[0] = x[1].token[0];
			x[2].token[1] = x[1].token[1];
			x[2].token[3] = '\0';
			x[2].count = x[1].count;

			x[1].token[0] = x[0].token[0];
			x[1].token[1] = x[0].token[1];
			x[1].token[3] = '\0';
			x[1].count = x[0].count;

			x[0].token[0] = token_array[i].token[0];
			x[0].token[1] = token_array[i].token[1];
			x[0].token[3] = '\0';
			x[0].count = token_array[i].count;
			
		}
		else if (token_array[i].count >= x[1].count)
		{
			x[2].token[0] = x[1].token[0];
			x[2].token[1] = x[1].token[1];
			x[2].token[3] = '\0';
			x[2].count = x[1].count;

			x[1].token[0] = token_array[i].token[0];
			x[1].token[1] = token_array[i].token[1];
			x[1].token[3] = '\0';
			x[1].count = token_array[i].count;
			
		}
		else if (token_array[i].count >= x[2].count)
		{
			x[2].token[0] = token_array[i].token[0];
			x[2].token[1] = token_array[i].token[1];
			x[2].token[3] = '\0';
			x[2].count = token_array[i].count;
		}		
	}
	return x;
}
