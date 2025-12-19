#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
int main(){
    char *p;
    p=(char*)malloc(sizeof(char)*1024*1024*1024*3);
    if(!p){
        printf("Memory allocation failed\n");
        return -1;
    }
        memcpy(p, "Hello, Pointer Practice!", 24);

    while (1)
    {
    printf("Address of allocated memory: %p\n", (void*)p);
    printf("Experiment");
fflush(stdout);
sleep(50);
    }
    
    free(p);
    // sleep(60);
    return 0;
}