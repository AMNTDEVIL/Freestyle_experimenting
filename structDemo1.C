#include<stdio.h>
#include<string.h>
struct Student{
    int id;
    char name[50];
    float marks;
};
void main(){
    for (int i = 0; i < 10; i++)
    {
        struct Student s;
        s.id++;
        scanf("%s",s.name);
        scanf("%f",&s.marks);
        printf("ID: %d\n",s.id);
        printf("Name: %s\n",s.name);
        printf("Marks: %.2f\n",s.marks);
    }
    
}