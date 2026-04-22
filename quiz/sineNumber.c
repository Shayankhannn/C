#include<stdio.h>

int main(void)
{ 

    /*

we had to find sine of value given by user  wich will be between 0 and 1 
for tthat first wwe have to know the formula 
sine = x - x^3/3! + x^5/5! - x^7/7!

so now we have to figure how to do that 
so first we will take value from user 
x -- value taken from user will be is double 
we have to check if num is between 0 and 1
now we will have to find how to power it up so each time the power increase by 2 first 
one is 1 then 3 then 5 then 7 so a loop will work by +2
now the factorial part - its same number which is power we will use loop inner 

and sign change in farmula -+-+-+ like that 


*/
double x , power ,sine = 0 , term;
int fac , sign ; 


printf("please enter value between 0 and 1 \n ");

scanf("%lf", &x);

if (x >= 1 || x <= 0 ) 
{
    printf("please enter number between 0 and 1 ");
    return 0;
}


sign = 1; 
for(int i =1; i<=7; i+=2){

    power = 1 ;
    for (int j =1 ; j <= i ; j++)
    {
        power *= x ;

    }
    fac= 1 ;
    for (int k = i;k>0;k--){
        fac *= k ; 
    }
    
    term =  power/fac ;
    sine += sign * term ;
    sign = -sign ;


    
    

    
}

printf("sine of value : %.2lf is %.6lf\n" , x, sine);

return 0;
}