#include <stdio.h>
long fibonacci(int n){
    int i;
    int f0 = 0 , f1 = 1;
    
    for ( i = 0; i < n; i++)
    {
       int f_old = f0 + f1;

    }
    
}

long recursion_fibb(int n){

    if (n <= 1)
    {
        return 1;
    }else{
        return(recursion_fibb(n-1) + recursion_fibb(n-2));
    }
    
}