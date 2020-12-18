#include <stdio.h>
#include <stdlib.h>

int main()
{
    int memory[4096];
    FILE *f = fopen("Hello.txt","rb");

    for(int i = 0; i<5; i++){
        memory[i] = fgetc(f);
        printf("%x",memory[i]);
    }

    getch(); //hold the program to not close
    return 0;
}
