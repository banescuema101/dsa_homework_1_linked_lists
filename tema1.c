/* Bănescu Ema-Ioana grupa 311 CB */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "operatii.h"

int main() {
    coada_com *c;
    c = InitQ();
    if (!c) {
        return 1;
    }
    Tren *tren = InitTren();  // initializam trenuletul
    if (!tren) {
        return 1;
    }
    FILE *fisier, *output;
    char sir[200];
    fisier = fopen("tema1.in", "r");
    output = fopen("tema1.out", "w");
    if (fisier == NULL) {
        fprintf(output, "Eroare la deschidere");
        return 1;
    }
    if (output == NULL) {
        fprintf(output, "Eroare la deschidere");
        return 1;
    }
    int num_linie = 0;
    while (fgets(sir, sizeof(sir), fisier)) {
        if (num_linie != 0) {
            /* trec peste prima linie
            in care aveam numarul de comenzi. Eu am 
            optat pentru while deci nu am nevoie
            de acesta.*/
            if (sir[strlen(sir) - 1] == '\n')
                    sir[strlen(sir) - 1] = '\0';
                // elimin newline-ul de la finalul sirului
        char copie_sir[200];
        strcpy(copie_sir, sir);  // fac o copie a sirului
        strtok(copie_sir, " ");
        // vreau sa retin doar primul cuvant.
        copie_sir[strlen(copie_sir)] = '\0';
        // acum in copie_sir am doar primul cuvant din sir.
        // acum ma intreb ce anume adaug in coada =>
        // astfel trebuie sa am doar acele comenzi UPDATE si SEARCH
        if ((strcmp(copie_sir, "MOVE_LEFT") == 0)
        || (strcmp(copie_sir, "MOVE_RIGHT") == 0)
        || (strcmp(copie_sir, "WRITE") == 0)
        || (strcmp(copie_sir, "CLEAR_CELL") == 0)
        || (strcmp(copie_sir, "CLEAR_ALL") == 0)
        || (strcmp(copie_sir, "INSERT_LEFT") == 0)
        || (strcmp(copie_sir, "INSERT_RIGHT") == 0)
        || (strcmp(copie_sir, "SEARCH") == 0 )
        || (strcmp(copie_sir, "SEARCH_LEFT") == 0 )
        || (strcmp(copie_sir, "SEARCH_RIGHT") == 0 )) {
            IntrQ(c, sir);  // introduc sirul in coada
        // (!! CEL COMPLET, SI CU NUMARUL DE DUPA AFERENT DACA ARE)
        // pentru a stii mai incolo si ce valori sa caut in search sau
        // sa inserez la insert, etc etc.
        } else {
            // fac extragerea din lista daca intalnesc EXECUTE.
            // afisez daca am SHOW sau SHOW_CURRENT
            // Inversez ordinea cozii daca am SWITCH
            if (strcmp(copie_sir, "EXECUTE") == 0) {
                char *com_for_exec = (char*)malloc(101 * sizeof(char));
                if(!com_for_exec) {
                    return 1;
                    fprintf(output, "Eroare la alocare");
                }
                char *val_extrasa = ExtrQ(c);
                /* am retinut aici intr-o alta variabila, deoarece
                daca dadeam free direct lui com_for_exec dadea
                eroare cu valgrind, pentru ca cel mai
                probabil pierdeam adresa de memorie. */
                if (val_extrasa != NULL) {
                    strcpy(com_for_exec, val_extrasa);
                    free(val_extrasa);
                }
                // in cele de mai SUS, am pus in com_for_exec, comanda, adica primul cuvant din sirul
                // citit de la tastatura de pe fiecare linie de input.
                if (com_for_exec != NULL) {
                    char *com_for_exec_for_dezaloc = com_for_exec;
                    // pentru a face free la finalul if ului
                    if (strstr(com_for_exec, "INSERT_RIGHT") != NULL) {
                    // COMANDA 1
                    // stiu ca aceasta comanda e formata dintr un string si un caracter.
                        char valoare = com_for_exec[strlen(com_for_exec) - 1];
                        // am extras valoarea din comanda.
                        insert_right(tren, valoare);
                    } else if (strstr(com_for_exec, "INSERT_LEFT") != NULL) {
                        // COMANDA 2
                        char valoare = com_for_exec[strlen(com_for_exec) - 1];
                        // pentru a stii ce valoare voi pune in vagonul de inserat.
                        insert_left(tren, valoare, output);
                    } else if (strstr(com_for_exec, "MOVE_LEFT") != NULL) {
                        // COMANDA 3
                        move_left(tren);
                    } else if(strstr(com_for_exec, "MOVE_RIGHT") != NULL) {
                        // COMANDA 4
                        move_right(tren);
                    } else if (strstr(com_for_exec, "WRITE") != NULL) {
                        // COMANDA 4
                        char valoare = com_for_exec[strlen(com_for_exec) - 1];
                        write_c(tren, valoare);
                    } else if (strstr(com_for_exec, "CLEAR_CELL") != NULL) {
                        // COMANDA 5
                        clear_cell(tren);
                    } else if (strstr(com_for_exec, "CLEAR_ALL") != NULL) {
                        // COMANDA 6
                        clear_all(tren);
                    } else if (strstr(com_for_exec, "SEARCH_RIGHT") != NULL) {
                        // COMANDA 7
                        // preiau sirul pe care vreau sa il caut cu functia mea search_right.
                        char *element = (char*)malloc(200 * sizeof(char));
                        if (!element) {
                            fprintf(output, "Eroare la alocare");
                            return 1;
                        }
                        char *element_init = element;
                        // i am facut copie, deoarece nu mergea
                        // sa ii dau free(element) la finalul blocului if,
                        // deoarece zona era realocata de strtok.
                        strcpy(element, com_for_exec);
                        strtok(element, " ");
                        element[strlen(element)] = '\0';
                        element = strtok(NULL, " ");
                        // acum in element am sirul pe care vreau sa il caut.
                        search_right(tren, element, output);
                        free(element_init);
                        // i am dat free sirului initial, a carui adresa NU i-am pierdut-o.
                    } else if (strstr(com_for_exec, "SEARCH_LEFT") != NULL) {
                        // COMANDA 8
                        char *element = (char*)malloc(200 * sizeof(char));
                        if (!element) {
                            fprintf(output, "Eroare la alocare");
                            return 1;
                        }
                        char *element_init = element;
                        strcpy(element, com_for_exec);
                        strtok(element, " ");
                        element[strlen(element)] = '\0';
                        element = strtok(NULL, " ");
                        search_left(tren, element, output);
                        free(element_init);
                    } else if (strstr(com_for_exec, "SEARCH") != NULL) {\
                        // COMANDA 9
                        char *element = (char*)malloc(200 * sizeof(char));
                        if (!element) {
                            fprintf(output, "Eroare la alocare");
                            return 1;
                        }
                        char *element_init = element;
                        strcpy(element, com_for_exec);
                        strtok(element, " ");
                        element[strlen(element)] = '\0';
                        element = strtok(NULL, " ");
                        search(tren, element, output);
                        free(element_init);
                    }
                if (com_for_exec_for_dezaloc != NULL) {
                free(com_for_exec_for_dezaloc);
                // eliberez memoria pentru valoarea extrasa!!!
                }
                }
            } else if (strcmp(copie_sir, "SHOW") == 0) {
            // daca am comanda SHOW, apelez functia de afisare a trenului.
                show(tren, output);
            } else if (strcmp(copie_sir, "SHOW_CURRENT") == 0) {
            // daca am comanda SHOW_CURRENT, apelez
            // functia de afisare a mecanicului.
                show_current(tren, output);
            } else if (strcmp(copie_sir, "SWITCH") == 0) {
                // daca am comanda SWITCH, apelez functia switch.
                switch_c(c);
            }
        }
    }
    num_linie++;
}
Distruge_tren(tren);
DistrQ(&c);
fclose(fisier);
fclose(output);
return 0;
}
