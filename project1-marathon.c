#include <stdio.h>
int main (void){

    int miles , yards ;
    double kilometer;

    printf("enter the values of miles and yards as int\n");
    scanf("%d %d", &miles, &yards);

    kilometer = 1.609 * (miles+yards/1760.0);
    printf("a marathon is of %.2lf km \n", kilometer);

    return 0;
}