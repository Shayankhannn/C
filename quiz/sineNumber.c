#include<stdio.h>

int main(void)
{ 
int sign ,power;
double x ,term  ;

printf("please enter number between 0 and 1 eg. 0.1 , 0.2 etc");

scanf("%lf", &x);

term = x;
sign = 1;
power = 1;

for (int i = 1 ; i <=7 ; i+=2) // 4 times
{

power*=i;


}



return 0;
}