#include "index.h"


int main(){
    // my_printf("less go s%dasdf &&&%% %f", 10, 10.567);
    
    my_printf("Large number: %f\n", 0.6);
    my_printf("Large number: %f\n", 0.123456);
    //print the %0.2f with float value 0.67
    my_printf("Large number: %0.2f\n", 2.123434);

    my_printf("Large number: %0.2f\n", 0.123456);
    my_printf("integer number %d %0.2f %2345 %2f", 10,5.3223,  10.567);
    return 0;

}