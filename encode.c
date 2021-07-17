#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

/** Beolvassa a kódtáblát enkódoláshoz.
 * @param f a beolvasandó fájl
 * @param t a kódtábla mutatója ahova beolvasunk
 * @param ti ti karakter
 * @param ta tá karakter
 */

void ct_e_read(FILE* f, codet* t,char ti,char ta)
{
    int i;
    codet* temp;
    ssize_t read;
    size_t len = 0;
    char * line = NULL;


    while ((read = getline(&line, &len, f)) != -1)
    {
        if(line_check(line))
        {
            temp = t;
            for(i=0; i<8; i++)
            {
                if(line[0] >> i & 1)
                {
                    if(temp->right == NULL)
                        temp->right = calloc(1,sizeof(codet));
                    if(temp->right == NULL)
                    {
                        fprintf(stderr,"Nem sikerült memóriát foglalnom!");
                        exit(EXIT_FAILURE);
                    }
                    temp = temp->right;
                }
                else
                {
                    if(temp->left == NULL)
                        temp->left = calloc(1,sizeof(codet));
                    if(temp->left == NULL)
                    {
                        fprintf(stderr,"Nem sikerült memóriát foglalnom!");
                        exit(EXIT_FAILURE);
                    }
                    temp = temp->left;
                }
            }
            int strl = (strlen(line));
            temp->code = (char*)calloc(strl,sizeof(char));

            if(temp->code == NULL)
            {
                fprintf(stderr,"Nem sikerült memóriát foglalnom!");
                exit(EXIT_FAILURE);
            }
            memcpy(temp->code, line+2, strl+1);
            for(int i=0; i<strl; i++)
            {
                if(temp->code[i] == '.')
                    temp->code[i] = ti;
                else if(temp->code[i] == '-')
                    temp->code[i] = ta;
            }
        }
    }
    if (line)
        free(line);
}

/** Enkódólja a bemenetet és kiírja kimenetre egy adott kódtábla segítségével.
 * @param f a bemeneti fájl
 * @param o a kimeneti fájl
 * @param t a kódtábla mutatója ahova beolvasunk
 * @param ti ti karakter
 * @param ta tá karakter
 * @return void
 */
void encode(FILE *f,FILE *o, codet* t,char sep)
{
    int i;
    codet* temp=t;
    int c;
    while( (c = getc(f)) != EOF)
    {
        c = toupper(c);
        if(c != sep)
        {
            for(i=0; i<8; i++)
            {
                if(c >> i & 1)
                {
                    if(temp->right != NULL)
                        temp = temp->right;
                }
                else
                {
                    if(temp->left != NULL)
                        temp = temp->left;
                }
            }
            if(temp->code != '\0')
                fprintf(o,"%s%c",temp->code,sep);
            temp=t;
        }
        else
        {
            fprintf(o,"%c%c",sep,sep);
        }
    }
    fprintf(o,"\n");
}
