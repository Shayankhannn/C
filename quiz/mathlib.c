#include<stdio.h>
#include<math.h> /* has  sin(), abs(), and fabs() */
int main(void)
{ 
double interval;
int i;
for(i = 0; i <30; i++)
{
 interval = i/10.0;
 printf("sin( %lf ) = %lf \t", interval, fabs( sin(interval)));
}

// fabs is for double float 
// abs is for int
// sin is a math func

printf("\n+++++++\n");
return 0;
}