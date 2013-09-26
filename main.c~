#if defined _WIN32 || defined _WIN64
#include <conio.h>    
#else
#include <curses.h>
#endif

#include <stdio.h>
#include <stdlib.h>


int bytesToInt(unsigned char* b, unsigned length)
{
    int val = 0;
    int j = 0;
    for (int i = length-1; i >= 0; --i)
    {
        val += (b[i] & 0xFF) << (8*j);
        ++j;
    }
    return val;
}


int main(int argc, char *argv[])
{
    unsigned long fileLen;
    unsigned long loop_list[1000];
    unsigned long loop_ind =0;

    unsigned char tape[30000] = {0};
    unsigned long pointer = 0;

    char *buffer;
    int Register;

    int ignore = 0;

    if ( argc != 2 )
    {
        printf( "usage: %s filename", argv[0] );
    }
    else
    {
        FILE *file = fopen( argv[1], "rb" );

        if ( file )
        {
            int x, instr;

            fseek(file,0,SEEK_END);
            fileLen=ftell(file);
            fseek(file,0,SEEK_SET);

            buffer = (char *)malloc(fileLen+1);

            while  ( ( x = fgetc( file ) ) != EOF )
            {
                fread( buffer, fileLen, 1, file );
            }
            fclose( file );
            for(instr=0;instr<fileLen;instr++){
                Register = (int)buffer[instr];
                switch(Register){
                case 7:
                    if(ignore == 1){
                        ignore = 0;
                        break;
                    }
                    else if (ignore == 0){
                        instr = (loop_list[loop_ind]);
                        break;
                    }
                case 0:
                    if(ignore == 0){
                        pointer += 1;
                        if (pointer >= 30000){
                            pointer = 29999;
                        }
                        break;
                    }else{
                        break;}
                case 1:
                    if(ignore == 0){
                        pointer -= 1;
                        if (pointer < 0){
                            pointer = 0;
                        }
                        break;
                    }else{
                        break;}
                case 2:
                    if(ignore == 0){
                        tape[pointer] += 1;
                        break;
                    }else{
                        break;}
                case 3:
                    if(ignore == 0){
                        tape[pointer] -= 1;
                        break;
                    }else{
                        break;}
                case 4:
                    if(ignore == 0){
                        putchar(tape[pointer]);
                        break;
                    }else{break;}
                case 5:
                    if(ignore == 0){
                        tape[pointer]=getch();
                        putchar(tape[pointer]);
                        break;
                    }else{break;}
                case 6:
                    if (tape[pointer] == 0){
                        ignore = 1;
                        loop_list[loop_ind] =0;
                        loop_ind--;
                    }
                    else{
                        ignore = 0;
                        loop_ind++;

                        loop_list[loop_ind]=instr-1;
                    }
                }
            }
        }
        else
        {
            printf( "Could not open file\n" );
        }
    }
    return 0;
}
