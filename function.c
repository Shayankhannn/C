#include <stdio.h>
int write_vary(int count){
    printf("I love her\n");
    while (count>0)
    {
        printf("very \n");
        --count;
    }
    printf("much \n");
    
}

int main(void){
    int repeat ;

    printf("how much do you love her ?? ");
    scanf("%d",&repeat);
    
    write_vary(repeat);
}