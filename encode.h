#ifndef ENCODE_H_INCLUDED
#define ENCODE_H_INCLUDED
/** Beolvassa a kódtáblát enkódoláshoz.
 * @param f a beolvasandó fájl
 * @param t a kódtábla mutatója ahova beolvasunk
 * @param ti ti karakter
 * @param ta tá karakter
 * @return void
 */
void ct_e_read(FILE* f, codet* t,char ti,char ta);

/** Enkódólja a bemenetet és kiírja kimenetre egy adott kódtábla segítségével.
 * @param f a bemeneti fájl
 * @param o a kimeneti fájl
 * @param t a kódtábla mutatója ahova beolvasunk
 * @param ti ti karakter
 * @param ta tá karakter
 * @param sep elválasztó karakter
 * @return void
 */
void encode(FILE *f,FILE *o, codet* t,char sep);

#endif // ENCODE_H_INCLUDED
