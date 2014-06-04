#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

char xbmfile[999][16];

char intermediate[529][5];
char interbytes[529][9];
char backasswards[529][9];
char final [529][6];

char xbmbinary[48][89];

char mrgfile[999][16];

char file_name[20];
char name[20];
char file_ext[5];

int x;
int y;
int z;
int i;

char a;
char b;
char c;
char d;



void binaryToHex(const char *inStr, char *outStr) {
    // outStr must be at least strlen(inStr)/4 + 1 bytes.
    static char hex[] = "0123456789ABCDEF";
    int len = strlen(inStr) / 4;
    int i = strlen(inStr) % 4;
    char current = 0;
    if(i) { // handle not multiple of 4
        while(i--) {
            current = (current << 1) + (*inStr - '0');
            inStr++;
        }
        *outStr = hex[current];
        ++outStr;
    }
    while(len--) {
        current = 0;
        for(i = 0; i < 4; ++i) {
            current = (current << 1) + (*inStr - '0');
            inStr++;
        }
        *outStr = hex[current];
        ++outStr;
    }
    *outStr = 0; // null byte
}



char* hex2bin(char hex1, char hex2)//converts hex to binary
{
    char byte[9];
    char halfbyte1[5] = {'\0','\0','\0','\0','\0'};
    char halfbyte2[5] = {'\0','\0','\0','\0','\0'};
    int x;

    for (x=0;x<9;x++)
    {
        byte[x]='\0';
    }

    if (hex1 == '0')
    {
        halfbyte1[0] = '0';
        halfbyte1[1] = '0';
        halfbyte1[2] = '0';
        halfbyte1[3] = '0';
    }
    else if(hex1 == '1')
    {
        halfbyte1[0] = '0';
        halfbyte1[1] = '0';
        halfbyte1[2] = '0';
        halfbyte1[3] = '1';
    }
    else if(hex1 == '2')
    {
        halfbyte1[0] = '0';
        halfbyte1[1] = '0';
        halfbyte1[2] = '1';
        halfbyte1[3] = '0';
    }
    else if(hex1 == '3')
    {
        halfbyte1[0] = '0';
        halfbyte1[1] = '0';
        halfbyte1[2] = '1';
        halfbyte1[3] = '1';
    }
    else if(hex1 == '4')
    {
        halfbyte1[0] = '0';
        halfbyte1[1] = '1';
        halfbyte1[2] = '0';
        halfbyte1[3] = '0';
    }
    else if(hex1 == '5')
    {
        halfbyte1[0] = '0';
        halfbyte1[1] = '1';
        halfbyte1[2] = '0';
        halfbyte1[3] = '1';
    }
    else if(hex1 == '6')
    {
        halfbyte1[0] = '0';
        halfbyte1[1] = '1';
        halfbyte1[2] = '1';
        halfbyte1[3] = '0';
    }
    else if(hex1 == '7')
    {
        halfbyte1[0] = '0';
        halfbyte1[1] = '1';
        halfbyte1[2] = '1';
        halfbyte1[3] = '1';
    }
    else if(hex1 == '8')
    {
        halfbyte1[0] = '1';
        halfbyte1[1] = '0';
        halfbyte1[2] = '0';
        halfbyte1[3] = '0';
    }
    else if(hex1 == '9')
    {
        halfbyte1[0] = '1';
        halfbyte1[1] = '0';
        halfbyte1[2] = '0';
        halfbyte1[3] = '1';
    }
    else if(hex1 == 'a')
    {
        halfbyte1[0] = '1';
        halfbyte1[1] = '0';
        halfbyte1[2] = '1';
        halfbyte1[3] = '0';
    }
    else if(hex1 == 'b')
    {
        halfbyte1[0] = '1';
        halfbyte1[1] = '0';
        halfbyte1[2] = '1';
        halfbyte1[3] = '1';
    }
    else if(hex1 == 'c')
    {
        halfbyte1[0] = '1';
        halfbyte1[1] = '1';
        halfbyte1[2] = '0';
        halfbyte1[3] = '0';
    }
    else if(hex1 == 'd')
    {
        halfbyte1[0] = '1';
        halfbyte1[1] = '1';
        halfbyte1[2] = '0';
        halfbyte1[3] = '1';
    }
    else if(hex1 == 'e')
    {
        halfbyte1[0] = '1';
        halfbyte1[1] = '1';
        halfbyte1[2] = '1';
        halfbyte1[3] = '0';
    }
    else
    {
        halfbyte1[0] = '1';
        halfbyte1[1] = '1';
        halfbyte1[2] = '1';
        halfbyte1[3] = '1';
    }


    if (hex2 == '0')
    {
        halfbyte2[0] = '0';
        halfbyte2[1] = '0';
        halfbyte2[2] = '0';
        halfbyte2[3] = '0';
    }
    else if(hex2 == '1')
    {
        halfbyte2[0] = '0';
        halfbyte2[1] = '0';
        halfbyte2[2] = '0';
        halfbyte2[3] = '1';
    }
    else if(hex2 == '2')
    {
        halfbyte2[0] = '0';
        halfbyte2[1] = '0';
        halfbyte2[2] = '1';
        halfbyte2[3] = '0';
    }
    else if(hex2 == '3')
    {
        halfbyte2[0] = '0';
        halfbyte2[1] = '0';
        halfbyte2[2] = '1';
        halfbyte2[3] = '1';
    }
    else if(hex2 == '4')
    {
        halfbyte2[0] = '0';
        halfbyte2[1] = '1';
        halfbyte2[2] = '0';
        halfbyte2[3] = '0';
    }
    else if(hex2 == '5')
    {
        halfbyte2[0] = '0';
        halfbyte2[1] = '1';
        halfbyte2[2] = '0';
        halfbyte2[3] = '1';
    }
    else if(hex2 == '6')
    {
        halfbyte2[0] = '0';
        halfbyte2[1] = '1';
        halfbyte2[2] = '1';
        halfbyte2[3] = '0';
    }
    else if(hex2 == '7')
    {
        halfbyte2[0] = '0';
        halfbyte2[1] = '1';
        halfbyte2[2] = '1';
        halfbyte2[3] = '1';
    }
    else if(hex2 == '8')
    {
        halfbyte2[0] = '1';
        halfbyte2[1] = '0';
        halfbyte2[2] = '0';
        halfbyte2[3] = '0';
    }
    else if(hex2 == '9')
    {
        halfbyte2[0] = '1';
        halfbyte2[1] = '0';
        halfbyte2[2] = '0';
        halfbyte2[3] = '1';
    }
    else if(hex2 == 'a')
    {
        halfbyte2[0] = '1';
        halfbyte2[1] = '0';
        halfbyte2[2] = '1';
        halfbyte2[3] = '0';
    }
    else if(hex2 == 'b')
    {
        halfbyte2[0] = '1';
        halfbyte2[1] = '0';
        halfbyte2[2] = '1';
        halfbyte2[3] = '1';
    }
    else if(hex2 == 'c')
    {
        halfbyte2[0] = '1';
        halfbyte2[1] = '1';
        halfbyte2[2] = '0';
        halfbyte2[3] = '0';
    }
    else if(hex2 == 'd')
    {
        halfbyte2[0] = '1';
        halfbyte2[1] = '1';
        halfbyte2[2] = '0';
        halfbyte2[3] = '1';
    }
    else if(hex2 == 'e')
    {
        halfbyte2[0] = '1';
        halfbyte2[1] = '1';
        halfbyte2[2] = '1';
        halfbyte2[3] = '0';
    }
    else
    {
        halfbyte2[0] = '1';
        halfbyte2[1] = '1';
        halfbyte2[2] = '1';
        halfbyte2[3] = '1';
    }



         strcat(halfbyte1, halfbyte2);
         strcpy(byte,halfbyte1);

         /*
         for(x=0;x<8;x++)
         {
             if (byte[x] == '0')
             {
                 byte[x] = '1';
             }
             else
             {
                 byte[x] = '0';
             }
         }*/

    //printf("%s" ,byte);
    //getchar();


    char *return_byte =(char *) malloc(sizeof(char)*9);
    strcpy(return_byte, byte);
    return return_byte;

}

int main(int argc, char *argv[])
{	

    if (argc < 1)
            return 0;

        int i;
        int strsize = 0;
        for (i=1; i<argc; i++)
        {
            strsize += strlen(argv[i]);
            if (argc > i+1)
                strsize++;
        }

        //printf("strsize: %d\n", strsize);

        char *cmdstring;
        cmdstring = malloc(strsize);
        cmdstring[0] = '\0';

        for (i=1; i<argc; i++)
        {
            strcat(cmdstring, argv[i]);
            if (argc > i+1)
                strcat(cmdstring, " ");
        }

        file_ext[0] = '.';
        file_ext[1] = 'm';
        file_ext[2] = 'r';
        file_ext[3] = 'g';
        file_ext[4] = '\0';

        for (x=0;x<529;x++)
        {
            final[x][0] = '0';
            final[x][1] = 'x';
        }


        for(x=0;x<999;x++)
		{
            for(y=0;y<16;y++)
			{
                xbmfile[x][y] = '\0';
			}
		}
	
		
		for(x=0;x<20;x++)
		{
            file_name[x] = '\0';
		}

        strcat(file_name, cmdstring);

        //printf("Please Enter the name of the file you would like to convert:");
        //scanf("%s" ,&file_name);
        //fpurge(stdin);

        //read the file

             FILE *xbmRead;

             xbmRead=fopen(file_name ,"r");
             if(xbmRead==NULL)
             {
               printf("Error opening file");
               return(1);
             }

             for(x=0;x<999;x++)
             {
               fscanf(xbmRead, "%s" ,&xbmfile[x]);
             }
             fclose(xbmRead);

             //for(x=0;x<999;x++)
             //{
             //    printf("%s" ,xbmfile[x]);
             //    getchar();
             //    fpurge(stdin);
             //}

             // filter out the hexidecimals from the crap

             i = 0;

             for(x=0;x<999;x++)
             {
                 for(y=0;y<16;y++)
                 {
                     if ((16-y)>=4)
                     {
                        a = xbmfile[x][y];
                        b = xbmfile[x][y+1];
                        c = xbmfile[x][y+2];
                        d = xbmfile[x][y+3];
                     }
                     else if((16-y)==3)
                     {
                        a = xbmfile[x][y];
                        b = xbmfile[x][y+1];
                        c = xbmfile[x][y+2];
                        d = xbmfile[x+1][0];
                     }
                     else if((16-y)==2)
                     {
                         a = xbmfile[x][y];
                         b = xbmfile[x][y+1];
                         c = xbmfile[x+1][0];
                         d = xbmfile[x+1][1];
                     }
                     else if ((16-y)==1)
                     {
                         a = xbmfile[x][y];
                         b = xbmfile[x+1][0];
                         c = xbmfile[x+1][1];
                         d = xbmfile[x+1][2];
                     }
                     else
                     {
                         printf("ERROR READING 2D ARRAY");
                     }

                     if (a == '0' && b == 'x')
                     {
                         intermediate[i][0] = a;
                         intermediate[i][1] = b;
                         intermediate[i][2] = c;
                         intermediate[i][3] = d;
                         intermediate[i][4] = '\0';
                         i++;
                     }
                 }
             }

             /*print for debuging
             for (x=0;x<529;x++)
             {
                printf("%s\n" ,intermediate[x]);
                getchar();
             }
             */

             /*----------------Reformat File-------------*/
             char *getbin;

             for (x=0;x<529;x++)//converts hexes to binary bytes
             {
                    getbin = hex2bin(intermediate[x][2],intermediate[x][3]);
                    for (i=0;i<9;i++)
                    {
                        interbytes[x][i]=*getbin;
                        getbin++;
                    }
             }

             for(x=0;x<529;x++)
             {
                for(i=0;i<8;i++)
                {
                 backasswards[x][i]=interbytes[x][7-i];
                }
             }


             /*
             for (x=0;x<529;x++)
             {
                 printf("%s\n" ,interbytes[x]);
                 getchar();
             }
             */

             y=0;

             for (x=0;x<48;x++)//puts binary in proper xbm squares
             {
                 for(i=0;i<11;i++)
                 {
                     strcat(xbmbinary[x],backasswards[i+(x*11)]);
                 }

             }
             /*---------------------------------------------------------------PRINT DEBUG HERE---------------------------------*/
             for (x=0;x<48;x++)
             {
                 printf("%s\n" ,xbmbinary[x]);
             }

             z=0;
             for(y=0;y<6;y++)//converts binary to correct order
             {
                for (x=0;x<84;x++)
                {
                    for(i=0;i<8;i++)
                    {
                        interbytes[z][i]=xbmbinary[i+(8*y)][x];
                    }
                    z++;
                }
             }

             for(x=0;x<529;x++)
             {
                for(i=0;i<8;i++)
                {
                 backasswards[x][i]=interbytes[x][7-i];
                }
             }

             for(x=0;x<529;x++)
             {
                 printf("%s\n" ,backasswards[x]);
             }

             for (x=0;x<529;x++)//converts binary back to hex
             {
                 binaryToHex(backasswards[x],intermediate[x]);
             }

             //for (x=0;x<529;x++)
             //{
             //    printf("%s\n" ,interbytes[x]);
             //    getchar();
             //    fpurge(stdin);
             //}

             for (x=0;x<529;x++)
             {
                 final[x][2] = intermediate[x][0];
                 final[x][3] = intermediate[x][1];
             }

             //printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++\n");

             for (x=0;x<529;x++)
             {
                 final[x][4] = ',';
                 final[x][5] = '\0';
             }

             //for(x=0;x<529;x++)
             //{
             //    printf("%s\n" ,final[x]);
             //    getchar();
             //    fpurge(stdin);
             //}




             /*----------------Write File----------------*/

		 for(x=0;x<20;x++)//this loop cuts .xbm off of the file name
		 {
            a = file_name[x];
            b = file_name[x+1];
            c = file_name[x+2];
            d = file_name[x+3];
            if (a == '.' && b == 'x')
			{
                file_name[x] = '\0';
                file_name[x+1] = '\0';
                file_name[x+2] = '\0';
                file_name[x+3] = '\0';
			}
		 }
		
         strcpy(name, file_name);
         strcat(file_name, file_ext);

         //Write the file
		
             FILE *xbmWrite;

             xbmWrite=fopen(file_name , "w");
             if(xbmWrite==NULL)
             	{
               		printf("Error opening file");
               		return(1);
             	}

             fprintf(xbmWrite, "const static unsigned char %s[] ={\n" ,name);
                for(x=0;x<504;x++)
             	{
                    fprintf(xbmWrite, "%s\n" ,final[x]);
            	}
                fprintf(xbmWrite, "};");

             	fclose(xbmWrite);


return 0;
}//Bracket for main 

