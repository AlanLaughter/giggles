#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(int argc, char *argv[])
{
    unsigned long fileLen;
    unsigned long loop_list[1000];
    unsigned long loop_ind =0;

    unsigned long pointer =0;
    static char tape[30000];

    char *buffer;
    int Register;

    bool ignore = false;

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
                    if(ignore){
                        ignore = false;
                        break;
                    }else{
                        instr = loop_list[loop_ind]-1;
                        break;
                    }
                case 0:
                    if(!ignore){
                        pointer++;
                        if (pointer > 30000){
                            pointer = 0;
                        }
                        break;
                    }else{break;}
                case 1:
                    if(!ignore){
                        pointer--;
                        if (pointer < 0){
                            pointer = 0;
                        }
                        break;
                    }else{break;}
                case 2:
                    if(!ignore){
                        tape[pointer]++;
                        if (tape[pointer] > 255){
                            tape[pointer]=0;
                        }
                        break;
                    }else{break;}
                case 3:
                    if(!ignore){
                        tape[pointer]--;
                        if (tape[pointer]< 0){
                            tape[pointer]=0;
                        }
                        break;
                    }else{break;}
                case 4:
                    if(!ignore){
                        putchar(tape[pointer]);
                        break;
                    }else{break;}
                case 5:
                    if(!ignore){
                        tape[pointer] = getchar();
                        break;
                    }else{break;}
                case 6:
                    if (tape[pointer] == 0){
                        ignore = true;
                        loop_ind--;
                    }
                    else{
                        ignore = false;
                        loop_ind++;

                        loop_list[loop_ind]=instr;
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
