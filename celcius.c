#include <stdio.h> 

int main(void){

int fahrenheit,celsius;

printf("enter fahrenheit  in integar\n");

scanf("%d", &fahrenheit);

celsius = (fahrenheit-32)/1.8;

printf("fahrenheit to celcius is %d" , celsius);


    return 0;
}