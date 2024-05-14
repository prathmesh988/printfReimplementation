# Printf Scratch implementation

First of all this is just striclty for windows !


```
"index.h" contains the my_printf function  
 main.c  is the main  file which execute that 

but i directly generated the bin of main.c which is main.exe 
u just directly run that 
```

First we take and  reimplement the behavior normal  printf function by taking it's n argument 
and printing them ,
so i found a article on how to take n function they used stdarg lib 
first they store the argument in va_list type varible 
by va_start method we append the argumuments inside the va_list type var it's the va_start is a macro 
and va_end is used to clean up the args before we end's the execution of our function 

```
void my_printf(char *val ,...){

   va_list args;
   va_start(args, format);


}
```


by calling  the va_arg method and specifying the type to access it will increment the aargument 
so u next time u call with the type u wann access it will get that arg in a sequential order 

so i have  a basic example of the printf function takes argument and  how it go through that

```
void my_printf(char *val ,...){

   va_list args;
   va_start(args, format);


   while (*val != '\0')
        {
                res += va_arg(ap, int);
                //increasing the pointer to jump to next address
                val++;
        }

}
```
here's the docs link :- 
https://medium.com/@scarletskynned/variadic-functions-in-c-stdarg-h-f466101f1d47


## Accessing the Console API

To access the console api 

```bash
 #include <windows.h>
 HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
 DWORD written;

```
this is the boilor plate to access the console api , this is just to handle the current instance of our console 
this is because we need to write in same console not to popup or use other console that's why!

now we can directly access the same console using the 
```
 WriteConsole(hStdout, str, strlen(str), &written, NULL);
```
again it is just a boiler plate that's how they made it ,  the main thing is to use is the "str" argument in the WriteConsole  method which we pass character there and print the characters by character 


# Test Cases :-

    my_printf("Large number: %f\n", 0.6);
    my_printf("Large number: %f\n", 0.123456);

    my_printf("Large number: %0.2f\n", 2.123434);

    my_printf("Large number: %0.2f\n", 0.123456);
    my_printf("integer number %d %0.2f %2345 %0.2f obama \n", 10,5.3223,  10.567);

   
    long int num = 1234234890;
    my_printf("long value %ld",num);


Output in terminal :- 
  ![image](https://github.com/prathmesh988/printfReimplementation/assets/86892561/8f317235-b352-4bfc-881c-8356ee8d1c93)


so mistakes i did which is using too much if statement , we can make that dynamic to handle less if  statement  i've hardcoded there too much but it was just a example reimplementaion 
