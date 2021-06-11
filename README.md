# CHIP-8 Emulator
 CHIP-8 was created by RCA engineer Joe Weisbecker in 1977 for the COSMAC VIP microcomputer. It was intended as a simpler way to make small programs and games for the computer.
 CHIP-8 programs are run on a CHIP-8 virtual machine. It was made to allow video games to be more easily programmed for these computers.
 
 # Knowledges
- Programming languages
  - C Language
  - Assembly Language
  
- Computer Architecture

- Binary and hexadecinal number system

- C File Handling

- Computer Graphics
  - OpenGL
  
 # Note
  - This project is currently in progress. This repository is updating in real-time.
  - Using Code::Blocks IDE
  - You can use Code:Blocks to open the project.
  
  # Example code
  
  ```c
  #include <stdio.h>
#include <stdlib.h>

//spec CPU
unsigned char memory[4096]; //RAM
unsigned char v[0xf]; //Register
int pc=0; //program counter (how many times)

void dis(unsigned char b1, unsigned char b2, int *i){ //machine code to Assembly

    unsigned int bc = (b1<<8) | b2;

    switch(bc){

        case 0x00E0:
            printf("disp_clear()");
            break;

        case 0x00EE:
            printf("return;");
            break;

        default:

            switch(b1 >> 4){
                case 0x0:
                    printf("Call %.3x", bc&0x0FFF);
                    break;

                case 0x1:
                    printf("goto %.3x", bc&0x0FFF);
                    *i = (bc&0x0FFF)-2;
                    break;

                case 0x2:
                    printf("*(%.3x)()", bc&0x0FFF);
                    dis(memory[bc&0x0FFF], memory[(bc&0xFFF)+1], i);
                    break;

                case 0x3:
                    printf("if(V%.1x == %.2x)", (bc>>8)&0x0F, bc&0x00FF);

                    if(v[(bc>>8)&0x0F] == bc&0x00FF){
                        i+=2;
                    }
                    break;

                 case 0x4:
                    printf("if(V%.1x != %.2x)", (bc>>8)&0x0F, bc&0x00FF);
                    if(v[(bc>>8)&0x0F] != bc&0x00FF){
                        i+=2;
                    }
                    break;

                 case 0x5:
                    printf("if(V%.1x == V%.1x)", (bc>>8)&0x0F, (bc>>4)&0x00F);
                    if(v[(bc>>8)&0x0F] == v[(bc>>4)&0x00F]){
                        i+=2;
                    }
                    break;

                 case 0x6:
                    printf("V%.1x = %.2x", (bc>>8) & 0x0F, bc& 0x00FF);
                    v[(bc>>8) & 0x0F] = bc& 0x00FF;
                    break;

                 case 0x7:
                    printf("V%.1x += %.2x", (bc>>8) & 0x0F, bc& 0x00FF);
                    v[(bc>>8) & 0x0F] += bc& 0x00FF;
                    break;

                case 0x8:

                    switch(b2 & 0x0F) {
                        case 0x0:
                            printf("V%.1x = V%.1x", (bc>>8)&0x0F, (bc>>4)&0x00F);
                            v[(bc>>8)&0x0F] = v[(bc>>4)&0x00F];
                            break;

                        case 0x1:
                            printf("V%.1x = V%.1x | V%.1x", (bc>>8)&0x0F, (bc>>8)&0x0F,(bc>>4)&0x00F);
                            v[(bc>>8)&0x0F] = v[(bc>>8)&0x0F] | v[(bc>>4)&0x00F];
                            break;

                        case 0x2:
                            printf("V%.1x = V%.1x & V%.1x", (bc>>8)&0x0F, (bc>>8)&0x0F,(bc>>4)&0x00F);
                            v[(bc>>8)&0x0F] = v[(bc>>8)&0x0F] & v[(bc>>4)&0x00F];

                            break;

                        case 0x3:
                            printf("V%.1x = V%.1x ^ V%.1x", (bc>>8)&0x0F, (bc>>8)&0x0F,(bc>>4)&0x00F);
                            v[(bc>>8)&0x0F] = v[(bc>>8)&0x0F] ^ v[(bc>>4)&0x00F];
                            break;

                        case 0x4:
                            printf("V%.1x += V%.1x",  (bc>>8)&0x0F, (bc>>4)&0x00F);
                            break;

                        case 0x5:
                            printf("V%.1x -= V%.1x",  (bc>>8)&0x0F, (bc>>4)&0x00F);
                            break;

                        case 0x6:
                            printf("V%.1x >> 1", (bc>>8)&0x0F);
                            break;

                        case 0x7:
                            printf("V%.1x = V%.1x - V%.1x", (bc>>8)&0x0F, (bc>>4)&0x00F, (bc>>8)&0x0F );
                            break;

                        case 0xE:
                            printf("V%.1x << 1", (bc>>8)&0x0F);
                            break;

                        }

                    break;

                    case 0x9:
                        printf("if(%V.1x != %V.1x", (bc>>8)&0x0F,(bc>>4)&0x00F);
                        break;

                    case 0xA:
                        printf("1 = %.3x", bc&0x0FFF);
                        break;

                    case 0xB:
                        printf("PC = V0+ %.3x", bc&0xFFF);
                        break;

                    case 0xC:
                        printf("V%.1x = rand()&.2x", b1&0x0F, b2);
                        break;

                    case 0xD:
                        printf("draw(V%.1x,V%.1x,V%.1x)",b1&0x0F, b2>>4, b2&0xF);
                        break;

                    case 0xE:
                        if(b2== 0x9E){
                            printf("if(key() == %.1x)");
                        }

                        else if(b2 == 0xA1){
                            printf("if(key() != %.1x)");
                        }

                        break;

                    case 0xF:

                        switch(b2){

                            case(0x07):
                                printf("%.1x = get_delay()", b1&0x0F);
                                break;

                            case(0x0A):
                                printf("%.1x = get_key()", b1&0x0F);
                                break;

                            case(0x15):
                                printf("delay_timer(%.1x)", b1&0x0F);
                                break;

                            case(0x18):
                                printf("sound_timer(%.1x)", b1&0x0F);
                                break;

                            case(0x1E):
                                printf("I += %.1x", b1&0x0F);
                                break;

                            case(0x29):
                                printf("I = sprite_addr[%.1x]", b1&0x0F);
                                break;

                            case(0x33):
                                printf("set_BCD(%.1x)",b1&0x0F);
                                break;

                            case(0x55):
                                printf("reg_dump(%.1x,&I)", bc&0x0F);
                                break;

                            case(0x65):
                                printf("reg_load(%.1x,&I)", bc&0x0F);
                                break;

                        }


                }


        }
}

int main()
{

    FILE *f = fopen("testrom.ch8","rb");

    for(int i = 512; i<1301+512; i++){
        memory[i] = fgetc(f);
    }

    for(int i = 512; i<1301+512; i=i+2){ //1 instruction = 2byte
        printf("%.4x ", (memory[i] << 8) | memory[i+1]);
        dis(memory[i], memory[i+1], &i); //&i is address of i

        printf("\n");
        for(int i = 0; i<16; i++){
            printf("%x ", v[i]);
        }

        printf("\n");
    }

    getch(); //hold the program not to close
    return 0;
}
```
