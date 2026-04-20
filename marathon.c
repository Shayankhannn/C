#include <stdio.h>
int main (void){
int miles = 26 , yards = 385;
double kilometer ;

kilometer = 1.609 * (miles+yards/1760.0);

printf("marathon is %lf kilometers  " , kilometer);


    return 0;
}