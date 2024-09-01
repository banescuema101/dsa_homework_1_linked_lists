/* Bănescu Ema-Ioana grupa 311 CB */
#include "operatii.h"
#include <stdlib.h>

TLista AlocCelula(char elem) {
    TLista aux = (TLista) malloc(sizeof(TCelula));  /* alocare celula*/
    if (!aux) {
        return NULL;
    }                  /* aux != NULL */
    aux->info = elem;
    aux->urm = NULL;
    aux->pre = NULL;
    return aux;        /* returnare adresa sau NULL */
}
Tren* InitTren(void) {  // creez lista doar cu santinela.
    Tren* tren = (Tren *)malloc(sizeof(Tren));
    if (!tren) {
        return NULL;
    }
    TLista santinela = AlocCelula(' ');
    // aloc prima celula, adica santinela, primul vagon din tren.
    if (!santinela) {
        if (!tren) {
        free(tren);
        }
        return NULL;
    }
    TLista vagon1 = AlocCelula('#');
    if (!vagon1) {
        free(santinela);
        free(tren);
        return NULL;
    }
    tren->santinela = santinela;
    tren->santinela->urm = vagon1;
    // leg santinela de primul vagon.
    tren->santinela->pre = vagon1;
    // leg santinela la stanga tot de primul
    // vagon(ca e si primul si ultimul, la inittren).
    vagon1->pre = tren->santinela;
    // leg la stanga vagonul de santinela(locomotiva).
    vagon1->urm = tren->santinela;
    // leg la dreapta vagonul de santinela.
    tren->m = vagon1;
    // mecanicul este pus in primul vagon de imediat de dupa santinela.
    return tren;
}
void show(Tren* tren, FILE *output) {
    TLista curr = tren->santinela->urm;
    while (curr != tren->santinela) {
        if (curr == tren->m) {
            fprintf(output, "|%c|", curr->info);
        } else {
        fprintf(output, "%c", curr->info);
        }
        curr = curr->urm;
    }
    fprintf(output, "\n");
}
void show_current(Tren *tren, FILE *output) {
    if (!tren) {
        return;
    } else {
        fprintf(output, "%c", tren->m->info);
    }
    fprintf(output, "\n");
}
void move_left(Tren *tren) {
    // daca mecanicul se afla in primul vagon, fac urmatorul lucru:
    if (tren->m == tren->santinela->urm) {
        tren->m = tren->santinela->pre;
        // mecanicul va fi ultimul vagon.
    } else {
        TLista aux;
        aux = tren->m;
        // am memorat mecanicul spre a-l modifica in randul urmator.
        tren->m = aux->pre;
        // am mutat in ,,vagonul" precedent.
    }
}
void insert_end(Tren* tren, char informatie) {
    // trebuie sa aflu unde este mecanicul.
    TLista new = AlocCelula(informatie);
    // aloc o noua celula, new.
    if (tren->m == tren->santinela->pre) {
    // daca mecanicul e pe ultima pozitie;
    new->urm = tren->santinela;
    // legatura urmatoare indica spre santinela.
    new->pre = tren->santinela->pre;
    /* legatura anterioara indica spre ultimul vagon 
    ce se afla in tren in momentul actual */
    tren->santinela->pre->urm = new;
    // legatura urmatoare a ultimului vagon indica spre celula new.
    tren->santinela->pre = new;
    // in momentul de fata, vreau ca ultimul vagon sa fie new.
    tren->m = new;
    // setez mecanicul la new.
    }
}
void move_right(Tren *tren) {
    // daca mecanicul se afla in ultimul vagon, fac urmatorul lucru:
    if (tren->m == tren->santinela->pre) {
        insert_end(tren, '#');
        tren->m = tren->santinela->pre;
    } else {
        tren->m = tren->m->urm;
    }
}
void write_c(Tren *tren, char informatie) {
    tren->m->info = informatie;
    // informatia din mecanic va fi noua informatie.
}
void clear_cell(Tren *tren) {
    TLista aux = tren->m;
    TLista vagon_aux;
    if (tren->m == tren->santinela->urm && tren->m != tren->santinela->pre) {
        vagon_aux = tren->santinela->urm->urm;
        /* memorez in vagon_aux, al doilea vagon,
         pentru a face legaturile cu santinela. */
        vagon_aux->pre = tren->santinela;
        // legatura dintre al doilea vagon si santinela.
        tren->santinela->urm = vagon_aux;
        // legatura dintre santinela si vagon_aux
        tren->m = tren->santinela->pre;
        // acum actualizez mecanicul pe ultimul vagon.
        free(aux);
        // eliberez memoria pentru aux.
    } else if (tren->m == tren->santinela->urm
    && tren->m == tren->santinela->pre) {
        write_c(tren, '#');
    } else if (tren->m == tren->santinela->pre) {
        // daca e ultimul vagon din tren
        vagon_aux = tren->santinela->pre->pre;
        // memorez penultimul vagon in pointerul vagon_aux;
        vagon_aux->urm = tren->santinela;
        // leg penultimul de primul.
        tren->santinela->pre = vagon_aux;
        // ultimul vagon va fi vagonul vagon_tren.
        free(aux);
        tren->m = tren->santinela->pre;
        // actualizez mecanicul.
    } else {
        vagon_aux = tren->m->pre;
        // memorez vagonul precedent celui in care se afla mecanicul.
        vagon_aux->urm = tren->m->urm;
        // fac legatura dintre vagon_aux si cel de dupa mecanic. ->
        tren->m->urm->pre = vagon_aux;
        // fac legatura intre cel de dupa mecanic si vagon_aux <-
        free(aux);
        tren->m = vagon_aux;
        // setez mecanicul.
    }
}
void clear_all(Tren *tren) {
    tren->m = tren->santinela->pre;
    // setez mecanicul la final de tot.
    while (tren->m != tren->santinela->urm) {
        // cat timp mecanicul nu se afla pe vagonul 1
        clear_cell(tren);
        // sterg celula si mut mecanicul la stanga.
    }
    tren->m->info = '#';
    // initializez mecanicul.
}
void insert_left(Tren *tren, char valoare, FILE*output) {
    if (tren->m == tren->santinela->urm) {
        fprintf(output, "ERROR\n");
    } else {
        TLista aux = AlocCelula(valoare);
        if (!aux) {
            return;
        }
        TLista vagon_aux;
        vagon_aux = tren->m->pre;
        // salvez vagonul precedent mecanicului.
        vagon_aux->urm = aux;
        // acel vagon il leg de noul vagon aux
        aux->urm = tren->m;
        // leg aux la dreapta de vagonul in care se afla mecanicul.
        aux->pre = vagon_aux;
        // leg aux la stanga de vagonul precedent mecanicului.
        tren->m->pre = aux;
        // leg vagonul in care se afla mecanicul de aux.
        tren->m = vagon_aux->urm;
        // mecanicul va fi urmatorul dupa vagon_aux
    }
}
void insert_right(Tren *tren, char valoare) {
    TLista aux = AlocCelula(valoare);
    if (!aux) {
        return;
    }
    if (tren->m == tren->santinela->pre) {
        // daca mecanicul se afla in ultimul vagon.
        tren->m->urm = aux;  // leg mecanicul de aux, noul nod adica
        aux->pre = tren->m;
        // leg noul nod la stanga de mecanic(adica ultimul vagon)
        aux->urm = tren->santinela;  // leg noul nod la dreapta de santinela.
        tren->santinela->pre = aux;  // leg santinela de noul nod.
        tren->m = aux;              // setez mecanicul la noul nod, aux.
    } else {
        TLista vagon_aux;
        vagon_aux = tren->m->urm;
        // memorez in vagon_aux, celula  de dupa mecanic.
        vagon_aux->pre = aux;
        // leg acea celula la stanga de noul nod pe care trebuie sa il inserez.
        aux->urm = vagon_aux;
        // leg noul nod la dreapta de celula de dupa mecanic.
        aux->pre = tren->m;
        // leg noul nod la stanga de mecanic.
        tren->m->urm = aux;
        // leg mecanicul la dreapta de celula de inserat.
        tren->m = vagon_aux->pre;
        // mecanicul il setez ca fiind vagonul de dinainte de vagon_aux.
    }
}
void search(Tren *tren, char* s, FILE *output) {
    TLista curr = tren->m;
    TLista poz_initiala_mecanic = tren->m;
    TLista poz_prim1 = NULL;
    TLista poz_prim = NULL;
    int n_sir = strlen(s);
    int ct = 0;
    // lungime partiala, de tipul problemelor din liceu.
    if (curr == tren->santinela->pre && tren->santinela->urm == tren->santinela->pre) {
        if (!(n_sir == 1 && curr->info == s[0]))
        fprintf(output, "ERROR\n");
        return;
        /* am gasit, daca trenul are doar un vagon
         si caracterul din acel vagon formeaza sirul
          (de un caracter ar fi sirul) */
    } else {
        do {  /* cat timp nu am ajuns la sfarsitul
        potentialei secvente si mai am elemente de parcurs */
            if (curr == tren->santinela) {
                /* daca ajung la santinela,
                unde nu am ,,acces la info" avansam spre
                dreapta si continuam bucla. */
                if (ct != 0 && curr->urm->info != s[ct])
                ct = 0;
                /* insa a trebuit ca, ct sa se faca 0
                doar in cazul in care elementul de dupa
                santinela ar fi diferit de elementul
                de pe pozitia ct sin sirul s. */
                curr = curr->urm;  // sar peste santinela.
            }
            if (curr->info == s[ct]) {
                    if (ct == 0) {
                        poz_prim = curr;
    /* poz_prim memoreaza potentialul vagon
    unde se afla primul caracter din sirul gasit. */
                    }
                    ct++;
                    if (ct == n_sir) {
                        poz_prim1 = poz_prim;
    /* atunci poz_prim este bun si va ramane
     si il voi memora in poz_prim1. */
                        break;  // ne oprim.
                    }
                } else {
                    ct = 0;
                // incercam sa cautam alte secvente.
                    poz_prim = NULL;
                // poz_prim va puncta spre NULL.
                }
            curr = curr->urm;  // avansam in lista.
    }  while (ct < n_sir && curr != poz_initiala_mecanic);
    /* cat timp nu am ajuns din nou la pozitia
    initiala mecanicului si nu s-a ajuns
    la lungimea secventei de cauta */
    if (poz_prim1 != NULL) {
        tren->m = poz_prim1;
    } else {
        fprintf(output, "ERROR\n");
        }
    }
}
// aici de revenit ca da o eroare
// de segmentare pentru cazul in care e in primul vagon
void search_right(Tren *tren, char *s, FILE *output) {
    // s este un sir de caractere
    // de dimensiune nesetata in final.
    TLista curr = tren->m;
    TLista poz_ult = NULL;
    /* pointer la ultima pozitie unde sirul
    se potriveste cu potentiala insiruire
    de caractere din tren si din sir. */
    int n_sir = strlen(s);
    int ct = 0;
    // lungime partiala.
    if (tren->m == tren->santinela->pre) {
        if (n_sir == 1 && tren->m->info != s[0])
            fprintf(output, "ERROR\n");
        /* daca lungimea sirului de cautat este 1
         si informatia din singurul vagon nu
         va coincide cu sirul, intorc eroare */
        else if (n_sir == 1 && tren->m->info == s[0])
        return;
        // altfel, inseamna ca am gasit.
    } else {
    while (ct < n_sir && curr != tren->santinela) {
        // cat timp nu am ajuns la sfarsitul
        // potentialei secvente si mai am elemente de parcurs
        if (curr->info == s[ct]) {
            // daca un caracter coincide.
            // incepe potentiala secventa de caractere.
            ct++;
            if (ct == n_sir) {
                poz_ult = curr;
                break;
                // inseamna ca am gasit cel putin o data
                // cele exact n_sir litere care corespund
                // in aceeasi ordine si una dupa alta in tren,
                // exact ca in sir.
            }
        } else {  // sunt deja in potentiala secventa de caractere.
            ct = 0;
        }
        curr = curr->urm;  // avansez.
    }
    if (poz_ult != NULL) {
        tren->m = poz_ult;
    } else {
        fprintf(output, "ERROR\n");
    }
    }
}
void search_left(Tren *tren, char *s, FILE *output) {
    // s este un sir de caractere de dimensiune nesetata in final.
    TLista curr = tren->m;
    TLista poz_ult = NULL;
    // pointer la ultima pozitie unde sirul
    // se potriveste cu potentiala insiruire de
    // caractere din tren si din sir.
    int n_sir = strlen(s);
    int ct = 0;
    // lungime partiala, de tipul problemelor din liceu.
    if (tren->m == tren->santinela->urm) {
        if (n_sir != 1)
        fprintf(output, "ERROR\n");
        // am gasit.
    } else {
    while ( (ct < n_sir) && (curr!= NULL) && (curr != tren->santinela) ) {
        // cat timp nu am ajuns la sfarsitul
        // potentialei secvente si mai am elemente de parcurs
        if (curr->info == s[ct]) {
            // daca un caracter coincide.
            // incepe potentiala secventa de caractere.
            ct++;
            if (ct == n_sir) {
                poz_ult = curr;
        // actualizez pozitia ultimului element
        // din sir sa stiu unde voi pune la final mecanicul.
                break;
            }
        } else {
            ct = 0;
        }
        curr = curr->pre;
    }
    if (poz_ult != NULL) {
        // inseamna ca am gasit cel putin o data
        // cele exact n_sir litere care corespund
        // in aceeasi ordine si una dupa alta in tren, exact ca in sir.
        tren->m = poz_ult;
    } else {
        fprintf(output, "ERROR\n");
        }
    }
}
coada_com* InitQ() { /* creeaza coada vida */
  coada_com* c;
  /* spatiu pentru descriptor coada */
  c = (coada_com*)malloc(sizeof(coada_com));
  if (!c) return NULL;
  /* nu exista spatiu -> "esec" */
  c->sf = NULL;
  c->inc = NULL;
  return c;
  /* intoarce adresa descriptorului cozii */
}
void IntrQ(coada_com *c, char x[]) {
     /* adauga element la sfarsitul cozii */
  // lista_com cel_aux;
  if (!c) {
    return;
  }
  lista_com aux = (lista_com)malloc(sizeof(cel_com));
  if (!aux) {
    return;
  }
  strcpy(aux->info, x);
  aux->urm = NULL;
  // adaugand o noua celula (la sfarsit),
  // spre dreapta va indica spre NULL.
  if (c->sf) {
    aux->pre = c->sf;
    // leg noul nod de sfarsitul cozii.
    c->sf->urm = aux;
    // leg sfarsitul de celula nou creata.
    c->sf = aux;
    // sfarsitul va puncta spre celula nou creata.
  } else {
    // daca nu am niciun element momentan in coada.
    c->inc = aux;
    // inceputul va puncta catre celula noua.
    c->sf = aux;
    // sfarsitul va puncta catre noua celula nou creata.
    aux->pre = NULL;
    // la stanga noua celula va indica spre NULL.
  }
}
char* ExtrQ(coada_com *c) {
    if (!c || !c->inc) {
        return NULL;
    }
    cel_com *aux = c->inc;
    // memorez pointerul aux care va indica catre inceputul cozii.
    char* val_aux = (char *)malloc(sizeof(aux->info));
    if (!val_aux) {
        free(aux);
        return NULL;
    }
    strcpy(val_aux, aux->info);
    if (c->inc == c->sf) {
        c->inc = NULL;
        // daca este doar o celula in lista din coada,
        // atunci si sfarsitul si inceputul vor indica catre NULL.
        c->sf = NULL;
    } else {
        c->inc = c->inc->urm;
        // Altfel, inceputul il voi muta la celula din
        // lista de dupa celula la care puncteaza intial inceputul.
    }
    free(aux);
    return val_aux;
}
void switch_c(coada_com *c) {
    if (c->inc == c->sf) {
        /* daca nu exista sau exista doar o
         celula in lista din coada nu avem ce sa mai inversam. */
        return;
    } else {
        lista_com poz_inc, poz_sf;
        // mi am luat acesti doi pointeri pentru a schimba inc si sf.
        poz_inc = c->inc;
        poz_sf = c->sf;
        // intial, ii atribui lui poz_inc, inceputul cozii.
        // inceputul cozii si lui poz_sf, sfarsitul cozii.
        lista_com p, aux;
        lista_com al = c->inc;
        p = al->urm;
        al->urm = NULL;
        /* in liniile ce urmeaza am inversat practic lista
        care apartine cozii noastre, conform pasilor din curs. */
        while (p) {
            aux = p;
            p = p->urm;
            aux->urm = al;
            al = aux;
        }
    c->inc = poz_sf;
    c->sf = poz_inc;
    }
}
void DistrQ(coada_com **c) {
/* distruge coada */
  if (c == NULL) {
    printf("Eroare, nu avem ce sa mai dezalocam");
    return;
  }
    while ((*c)->inc != (*c)->sf) {
        char* p = ExtrQ(*c);
        // in functia extragere mi se si elibereaza memoria, cu free;
        free(p);
    }
    free((*c)->inc);
    free(*c);
    *c = NULL;
}
void Distruge_tren(Tren* tren) {
    TLista curr = tren->santinela->urm, aux;
    // curr va puncta catre primul vagonas.
    while (curr != tren->santinela) {
        // daca nu am ajuns inca la santinela,
        // atunci continui cu procesul de eliberare.
        aux = curr;
        curr = curr->urm;
        free(aux);
    }
    free(tren->santinela);
    // free si valorii de la pointerul la care puncta pointerul tren->santinela
    free(tren);
}
