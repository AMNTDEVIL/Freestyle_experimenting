#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

int main(){
    char buffer[2*1024*2048];
    while (1)
    {
    printf("Address of stack allocated buffer: %p\n", (void*)buffer);
    }
    
    memcpy(buffer, "Hello, Stack Pointer!", 22);
    sleep(60);
    return 123;
    exit(5);
    abort();
}