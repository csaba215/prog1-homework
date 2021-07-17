#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

/** Beolvassa a kódtáblát dekodláshoz.
 * @param f a beolvasandó fájl
 * @param t a kódtábla mutatója ahova beolvasunk
 * @param ti ti karakter
 * @param ta tá karakter
 * @return void
 */
void ct_d_read(FILE* f, codet* t,char ti,char ta)
{
    int i;
    codet* temp;
    ssize_t read;
    size_t len = 0;
    char * line = NULL;

    while ((read = getline(&line, &len, f)) != -1)
    {
        temp = t;
        if(line_check(line))
        {
            for(i=2; line[i]!='\0'; i++)
            {
                if(line[i] == ti)
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
                else if(line[i] == ta)
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


            temp->code = (char*)malloc(2*sizeof(char));
            temp->code[0] = line[0];
            temp->code[1] = '\0';
        }
    }
    if (line)
        free(line);
}


/** Dekódólja a bemenetet és kiírja kimenetre egy adott kódtábla segítségével.
 * @param f a bemeneti fájl
 * @param o a kimeneti fájl
 * @param t a kódtábla mutatója ahova beolvasunk
 * @param ti ti karakter
 * @param ta tá karakter
 * @param sep elválasztó karakter
 * @return void
 */

void decode(FILE *f,FILE *o, codet* t, char ti,char ta,char sep)
{
    codet* temp=t;
    int c;
    while( (c = getc(f)) != EOF)
    {
        if(c == ti)
        {
            if(temp->right != NULL)
                temp = temp->right;
        }
        else if(c == ta)
        {
            if(temp->left != NULL)
                temp = temp->left;
        }
        else if(c == sep)
        {
            fprintf(o,"%s",temp->code);
            temp=t;
        }

    }
    fprintf(o,"%s\n",temp->code);
}
