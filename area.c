#include <stdio.h>
#define PI 3.14159
int main (){
    double radius = 0.0 , area = 0.0;
    printf("enter radius of the area \n");
    scanf("%lf" , &radius);
    area = PI * radius*radius;
    printf("the radius of %lf meters; area is %lf sq meters \n", radius,area);
    return 0;
}