#include<stdio.h>
int main(){
    int a = 10,b=5;
    // __asm__(
    //     "subl %%eax,%%ebx;"
    //     :"=b"(b)
    //     :"a"(a),"0"(b)
    // );
    // __asm__("add %%rax, %%rbx;"
    //         :"=b"(b)
    //         :"a"(a),"0"(b)
    // );
    __asm__(
        "shl $3, %%eax;"
        :"=b"(b)
        :"a"(a),"0"(b)
    );
    printf("Result of Assembly Addition: %d\n",b);
    return 0;
}