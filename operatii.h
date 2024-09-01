/* Bănescu Ema-Ioana grupa 311 CB */
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct celula{
    char info;
    struct celula *urm, *pre;  //*m este mecanicul.
}TCelula, *TLista;

typedef struct tren {
    TLista santinela;
    TLista m; //mecanicul.
}Tren;

typedef struct cel_com { // celula a listei in care memorez comenzile.
    char info[200];  // presupunem ca e de maxim 20 infoul.
    struct cel_com *pre, *urm;
}cel_com, *lista_com;

typedef struct coada_com
{ 
  lista_com sf, inc;       /* adresa ultimei celule */
} coada_com;


TLista AlocCelula(char elem);
Tren* InitTren(void);
void show(Tren* tren, FILE *output);
void show_current(Tren* tren, FILE *output);
void move_left(Tren *tren);
void move_right(Tren *tren);
void insert_end(Tren* tren, char informatie);
void write_c(Tren *tren, char informatie);
void clear_cell(Tren *tren);
void clear_all(Tren *tren);
void insert_left(Tren *tren, char valoare, FILE *output);
void insert_right(Tren *tren, char valoare);
void search_right(Tren *tren, char *s, FILE* output);
void search_left(Tren *tren, char *s, FILE *output);
void search(Tren *tren, char* s, FILE *output);
coada_com* InitQ ();
void IntrQ(coada_com *c, char x[]);
char* ExtrQ (coada_com* c);
void switch_c(coada_com *c);
void DistrQ(coada_com **c);
void Distruge_tren(Tren* tren);
