#include <stdio.h>

long int factorial(int n){
    long  f=1;
    int i;
    

    for ( i = 1; i <=n ; i++)
    {
        
        f= f*i;
    }
    return f;
}

long int recursion_factorial(int n){
    if(n <= 1){
        return 1;
    }else{
        return(recursion_factorial(n-1)*n);
    }
}


int main(void){
    int how_many = 0;
    printf("I want table of factorial upto : ");
    scanf("%d",&how_many);
    printf("\n factorials \n");
    for (int i = 1; i <= how_many; i++)
    printf("\n %d\t %ld \n", i , factorial(i));

    printf("\n\n");

    for (int i = 1; i <= how_many; i++)
    printf("\n %d\t %ld \n", i , recursion_factorial(i));




}