#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED


typedef struct codet
{
    char *code;
    struct codet *right, *left;
} codet;
/** Ellenőrzi, hogy nem üres-e (csak egy sortörést tartalmaz, vagy azt se) a megadott sor és eltávolítja a végéről a sortörést.
 * @param char *l string mutatója
 * @return logikai IGAZ, ha a sor nem üres különben logikai HAMIS
 */
int line_check(char *l);

#endif // MAIN_H_INCLUDED
