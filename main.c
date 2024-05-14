#include "index.h"


int main(){
   
    my_printf("Large number: %f\n", 0.6);
    my_printf("Large number: %f\n", 0.123456);

    my_printf("Large number: %0.2f\n", 2.123434);

    my_printf("Large number: %0.2f\n", 0.123456);
    my_printf("integer number %d %0.2f %2345 %0.2f obama \n", 10,5.3223,  10.567);

   
    long int num = 1234234890;
    my_printf("long value %ld",num);
    return 0;

}