#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
#include "encode.h"
#include "decode.h"

/*typedef struct codet
{
    char *code;
    struct codet *right, *left;
} codet;
*/
/**
 * Ellenőrzi, hogy nem üres-e (csak egy sortörést tartalmaz, vagy azt se) a megadott sor és eltávolítja a végéről a sortörést.
 * @param char *l string mutatója
 * @return logikai IGAZ, ha a sor nem üres különben logikai HAMIS
 */
int line_check(char *l)
{
    if(strcmp(l,"\n") == 0 || strcmp(l," ") == 0)
        return 0;
    char * temp;
    // sortörés keresése
    temp = (char*)strstr(l,"\n");
    if(temp != NULL)
    	*temp = '\0';
    return 1;
}

/**
 * A program paraméterezését adja meg, ha -h vagy --help kapcsolóval lett meghívva.
 */
void help()
{
    printf("Morze Dekodóló \n -h vagy --help kapcsoló ezt az üzenetet adja vissza.\n -c vagy --code-table A kódólási tábla fájl neve adható meg a paraméterrel\n -o vagy --output kimeneti fájl helye adható meg a paraméterrel\n -i vagy --input bementi fájl helye adható meg a paraméterrel \n -b vagy --builtin programba épített kódtába használata ekkor kódtábla paraméter nem lesz figyelembe véve\n -co vagy --console-output ezzel a kimenet a consolra történik kiírásra  egy fájl helyett \n -ci vagy --console-input ezzel a kimenet a consolról történik beolvasás egy fájl helyett \n -e vagy --encode kódólás végzése \n -d vagy --decode dekódólás végzése \n -ti ti karakter adható meg(alapértelmezetten a . karakter) \n -ta tá karakter adható meg(alapértelmezetten a - karakter) \n -sep elválasztó karakter adható meg(alapértelmezetten a space karakter) \n");
}
/**
 * Ellenőrzi, hogy nem üres-e (csak egy sortörést tartalmaz, vagy azt se) a megadott sor és eltávolítja a végéről a sortörést.
 * @param codet *root kódtábla(bináris fa) mutatója
 */
void freet(codet *root)
{
    if (root == NULL)   // leállási feltétel
        return;
    free(root->code);
    freet(root->left);
    freet(root->right);
    free(root);
}

int main ( int argc, char *argv[] )
{
    char *ct = 0; //kódtábla fájl neve
    char *out = 0;  //kimeneti fájl neve
    char *in = 0;  //bementi fájl neve
    int builtin = 0;    //beépített kód táblát használjunk-e (bool)
    int co=0,ci=0;	// konzol kimenet/bemenet (bool)
    int dir = 0;	//kódolás irány 1:dekódólás 2:enkódólás
    char ti=0,ta=0,sep =0;
    if ( argc == 1 ) /* Nincs semmi paraméter megadva*/
    {
        fprintf(stderr,"Nincs semmilyen paraméter megadva!\nSegítség elérhető %s -h vagy --help kapcsolóval\n", argv[0]);
        return EXIT_SUCCESS;
    }
    else
    {
	// Kapcsolók beolvasása a megfelelő változókba
	int i;
        for(i=1; i<argc; i++)
        {
            if((strcmp(argv[i],"-h") == 0) || (strcmp(argv[i],"--help") == 0))
            {
                help();
                return EXIT_SUCCESS;
            }
            else if( (strcmp(argv[i],"-ct") == 0)  ||  (strcmp(argv[i],"--code-table") == 0))
                ct = argv[++i];
            else if( (strcmp(argv[i],"-o") == 0)   ||  (strcmp(argv[i],"--output") == 0))
                out = argv[++i];
            else if( (strcmp(argv[i],"-i") == 0)   ||  (strcmp(argv[i],"--input") == 0))
                in = argv[++i];
            else if( (strcmp(argv[i],"-b") == 0)   ||  (strcmp(argv[i],"--builtin") == 0))
                builtin = 1;
            else if( (strcmp(argv[i],"-co") == 0)  ||  (strcmp(argv[i],"--console-output") == 0))
                co = 1;
            else if( (strcmp(argv[i],"-ci") == 0)  ||  (strcmp(argv[i],"--console-input") == 0))
                ci = 1;
            else if( (strcmp(argv[i],"-e") == 0)   ||  (strcmp(argv[i],"--encode") == 0))
                dir = 2;
            else if( (strcmp(argv[i],"-d") == 0)   ||  (strcmp(argv[i],"--decode") == 0))
                dir = 1;
            else if( (strcmp(argv[i],"-ti") == 0))
                ti = argv[++i]==NULL?0:argv[i][0];
            else if( (strcmp(argv[i],"-ta") == 0))
                ta = argv[++i]==NULL?0:argv[i][0];
            else if( (strcmp(argv[i],"-sep") == 0))
                sep = argv[++i]==NULL?0:argv[i][0];
        }

    }
    //Kapcsolók meglétének ellenőrzése
    if(dir==0 || (co==0 && out == 0) || (ci==0 && in == 0) || (builtin == 0 && ct == 0))
    {
        fprintf(stderr,"Hiányzó paraméterek");
        return EXIT_FAILURE;
    }

    // Kódtábla lefoglalása
    codet* codet = calloc(1,sizeof(codet));
    if(codet == NULL)
    {
        fprintf(stderr,"Nem sikerült memóriát foglalnom!");
        exit(EXIT_FAILURE);
    }

    if(ti == 0)
        ti = '.';
    if(ta == 0)
        ta = '-';
    if(sep == 0)
        sep = ' ';

    FILE *outf,*inf;
    FILE *codetf;
    if(builtin == 0)
    {
        codetf = fopen(ct,"r");
        if(codetf == NULL)
        {
            fprintf(stderr,"Nem sikerült a kódtáblát megnyitnom!\n");
            exit(EXIT_FAILURE);
        }

    }
    if(co == 1)
        outf = stdout;
    else
    {
        outf = fopen(out,"w");
        if(outf == NULL)
        {
            fprintf(stderr,"Nem sikerült a kimeneti fájlt megynyitnom!\n");
            exit(EXIT_FAILURE);
        }
    }
    if(ci == 1)
        inf = stdin;
    else
    {
        inf = fopen(in,"r");
        if(inf == NULL)
        {
            fprintf(stderr,"Nem sikerült a bemeneti fájlt megynyitnom!\n");
            exit(EXIT_FAILURE);
        }
    }

    if(dir == 1)
    {

        codet->code = malloc(2*sizeof(char));
        codet->code[0] = sep;
        codet->code[1] = '\0';
        if(builtin == 1)
        {
            //kiírjuk egy ideilenes fájlba és beolvassuk
            FILE * temp = fopen(".temp","w");
            fprintf(temp,"A .-\nB -...\nC -.-.\nD -..\nE .\nF ..-.\nG --.\nH ....\nI ..\nJ .---\nK -.-\nL .-..\nM --\nN -.\nO ---\nP .--.\nQ --.-\nR .-.\nS ...\nT -\nU ..-\nv ...-\nW .--\nX -..-\nY -.--\nZ --..\n0 -----\n1 .----\n2 ..---\n3 ...--\n4 ....-\n5 .....\n6 -....\n7 --...\n8 ---..\n9 ----.\n\n");
            fclose(temp);
            codetf = fopen(".temp","r");
        }
        ct_d_read(codetf,codet,ti,ta);
        decode(inf,outf,codet,ti,ta,sep);

    }
    else if(dir == 2)
    {
        if(builtin == 1)
        {
            FILE * temp = fopen(".temp","w+");
            fprintf(temp,"A .-\nB -...\nC -.-.\nD -..\nE .\nF ..-.\nG --.\nH ....\nI ..\nJ .---\nK -.-\nL .-..\nM --\nN -.\nO ---\nP .--.\nQ --.-\nR .-.\nS ...\nT -\nU ..-\nv ...-\nW .--\nX -..-\nY -.--\nZ --..\n0 -----\n1 .----\n2 ..---\n3 ...--\n4 ....-\n5 .....\n6 -....\n7 --...\n8 ---..\n9 ----.\n\n");
            fclose(temp);
            codetf = fopen(".temp","r");
            //remove("temp");
        }
        ct_e_read(codetf,codet,ti,ta);
        encode(inf,outf,codet,sep);
    }

    if(co == 0)
        fclose(outf);
    if(ci == 0)
        fclose(inf);
    if(builtin == 1)
        remove(".temp");
    fclose(codetf);
    freet(codet);

    return EXIT_SUCCESS;
}
