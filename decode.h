#ifndef DECODE_H_INCLUDED
#define DECODE_H_INCLUDED

/** Beolvassa a kódtáblát dekodláshoz.
 * @param f a beolvasandó fájl
 * @param t a kódtábla mutatója ahova beolvasunk
 * @param ti ti karakter
 * @param ta tá karakter
 * @return void
 */
void ct_d_read(FILE* f, codet* t,char ti,char ta);

/** Dekódólja a bemenetet és kiírja kimenetre egy adott kódtábla segítségével.
 * @param f a bemeneti fájl
 * @param o a kimeneti fájl
 * @param t a kódtábla mutatója ahova beolvasunk
 * @param ti ti karakter
 * @param ta tá karakter
 * @param sep elválasztó karakter
 * @return void
 */
void decode(FILE *f,FILE *o, codet* t, char ti,char ta,char sep);
#endif // DECODE_H_INCLUDED
