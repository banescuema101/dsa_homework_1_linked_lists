    Pentru început, în fisierul operatii.c am implementat functiile de care m am ajutat ca in fisieruk tema1.c,
sa implementez taskurile problemei. Antetele functiilor, cat si structurile pe care le-am folosit sunt
implementate in fisierul operatii.h.
    Astfel, structura pentru celula si lista este preluata conform cursului, doar ca info e de tip char, deoarece ne propunem
ca in vagoanele trenului sa memoram cate un caracter. La fel si coada, cu informatie de tip char* (pentru ca vreau sa retin
nume de comenzi). Pentru coada am folosit alta structura de lista, pentru ca nu mai aveam nevoie de o lista cu santinela,
circulara, ci doar de una dublu inlantuita. Trenul este implementat cu structura tren care contine santinela(=locomotiva), de tip
pointer la celula ( de tip *TLista) si mecanicul, asemenea, dar va fi pozitionat unde vrea utilizatorul si respectand cerintele.
.....................................................
...............DESCRIEREA FUNCTIILOR.................
.....................................................

/* Aproape fiecare legatura pe care am realizat-o intre elementele din liste este comentata corespunzator. */


1. TLista AlocCelula(char elem), aloca o celula, populand campurile corespunzator, conform teoriei de la curs.

2. Tren* InitTren(void), intoarce trenuletul in forma lui initiala, ce va contine santinela, cat si primul si unicul vagon, 
inscriptionat cu '#' (vagon1). Am facut alocari pentru structura tren, pentru celulele spre care vor indica santinela si mecanic,
verificand daca alocarile s-au realizat cu succes, altfel eliberand memoria din ,,interior spre exterior,,. Am facut apoi urmatoarele legaturi:
Am setat santinela pe pozitie, apoi am legat-o la dreapta (urm) de primul vagon, vagon1. Legatura din stanga (pre) am realizat-o
sa indice spre vagon1. Apoi am realizat legatura intre primul vagon si santinela si la dreapta intre primul vagon si santinela.
Mecanicul l-am setat la celula vagon1, adica primul vagon din tren. Functia imi returneaza pointerul *tren, pentru a putea fi
ulterior modificat transmitandu-l ca parametru altor functii ulterioare.

3. void show(Tren* tren, FILE *output) este destinata spre a afisa trenuletul in fisierul de iesire tema1.out. Am parcurs trenul
folosind pointerul curr (de tip TLista*) care indica spre primul vagon (cel de dupa santinela), pana cand ajung la pozitia unde
se afla santinela (conditia de oprire) si am afisat info, iar pointerul curr coincidea cu amplasarea mecanicului, am afisat info
intre doua bare.
4. void show_current(Tren *tren, FILE *output) afiseaza informatia din vagonul spre care indica mecanicul.

5. void move_left(Tren *tren). Am verificat intitial daca mecanicul s-ar afla in primul vagon verificand daca mecanicul coincide cu primul
vagon de dupa santinela, in acest caz il mut in ultimul vagon ( cel imadiat de dinainte de santinela). Altfel, voi aloca un nou vagon
cu ajutorul functiei Aloc Celula si fac ca tren->m sa puncteze spre acel vagon, care va fi inscriptionat cu #

6. void move_right(Tren *tren). Daca mecanicul se va afla in ultimul vagon cuplez un vagon la final cu ajutorul functiei insert_end si
setez mecanicul acolo, altfel setez mecanicul la celula urmatoare mecanicului initial.

7. insertend(). Insereaza un vagon la finalul trenuletului, cu alocarea unei noi celula si creerea legaturilor corespunzatoare.

8 void clear_cell(Tren *tren). In aceasta functie am tratat cele 3 cazuri: (1) daca elimin primul vagon si acesta nu este singur in tren, si fac
legaturile (am comentat ce am facut prin fiecare legatura, in fsierul operatii.c), (2)daca elimin vagonul 1 si acesta e singurul
vagon din tren, caz in care trenul revine la forma sa initiala.(vezi comentarii), (3) cazul in care nu se afla nici in situaitia (1),
nici in situaitia (2)

9. void clear_all(Tren *tren). Aici, ma folosesc de functia clear_cell care sterge vagonul spre care puncteaza mecanicul. Setez initial
mecanicul la final si apoi apelez functia clear_cell, intr o bucla while, operatia repetandu-se pana cand ajung la primul vagon de dupa
santinela ( nu il elimin si pe acela). Apoi populez informatia din celula spre care puncteaza in acest moment mecanicul, cu caracterul #

10. void insert_left(Tren *tren, char valoare, FILE*output). Daca mecanicul se afla in primul vagon => erorr, altfel voi face inserarea
vagonului la stanga, cu legaturile precizate in comentarii.

11 void insert_right(Tren *tren, char valoare). Am tratat cele doua cazuri: . Prima data, cand vagonul se afla in ultimul vagon si al doilea
caz va fi cand nu se afla in aceasta situatie. Fiecare legatura este explicata in comentarii, pentru a fi mai usor de vizualizat.

12. void search(Tren *tren, char* s, FILE *output). In primul rand, poz_prim1 va fi un pointer la prima pozitie ( cea buna) 
unde sirul se potriveste cu potentiala insiruire de caractere din tren si din sir, iar poz_prim va fi un pointer la prima pozitie
(cea temporara).
Prima data am verificat daca mecanicul este in ultimul vagon si daca exista doar un vagon in tren. ( cel corespunzator zonei
spre care puncteaza mecanicul). In acest caz, daca lungimea sirului cautat este 1 si coincide acel sir (caracter adica) cu informatia
din celula la care puncteaza mecanicul, inseamna ca l-am gasit si ies din functie, altfel intorc eroare. Altfel, 
cat timp nu am ajuns la sfarsitul potentialei secvente si mai am elemente de parcurs verific daca curr puncteaza spre acelasi loc in care puncteaza
si santinela (cazul in care ajungem la santinela )unde nu trebuie luat in considerare acel element, dar am grija sa modific si ct pe 0 
doar in cazul in care elementul de dupa santinela ar fi diferit de elementul de pe pozitia ct din sirul s. Daca nu sunt in acest
caz special unde trebuie sa nu iau in considerare santinela, verific mai departe succesiunile de caractere, modificand ct = 0. Atunci cand se 
strica succesiunea dorita pe care trebuie sa o caut, si daca ct va ajunge la vreun moment dat la lungimea sirului, atunci voi schimba locul
spre care puncteaza pointerul poz_prim1 la acea celula corespunzatoare ca pozitie primului element din sir.

13 + 14. La functiile search_left si search_right, am mers aproximativ pe acelasi principiu ca mai sus, doar schimband dupa caz 
directia in care parcurg lista si conditia de oprire.
Ultimele 6 functii se refera la coada de comenzi, ai carei pointeri din structura aferenta ei, inc si sf puncteaza spre inceputul,
respectiv sfarsitul listei duble inlantuite ( dar nu va mai fi circulara, si nici cu santinela). Toate, cu toate legaturile
pe care le am mai facut sunt explicate frumos in comentarii, pentru o mai buna vizualizare(sunt asemanatoare cu implementarile din curs).

..........................................................................................
......................DESCRIEREA PROGRAMULUI PRINCIPAL....................................
..........................................................................................
    Am intializat coada si trenuletul si am deschis fisierele de intrare respectiv iesire, tema1.in si tema1.out. Am initializat stringul sir[200],
ca fiind sirul pe care il voi citi din fisierul de intrare, pe fiecare linie in parte, cu fgets. Pentru fiecare sir elimin new-lineurile de la
final, de dupa ce le am citit. Am retinut doar primul cuvant in copie_sir, si am comparat acest string cu comenzile de update si search, si daca
coincideau, atunci, introduceam in lista din coada acel sir( comanda). !!! Eu spun ,,comanda" referindu-ma ca la input putem avea un cuvant,
sau doua cuvinte separate printr-un spatiu.!!! Altfel, daca copie_sir coincidea cu comenda EXECUTE, mi am luat stringul char *val_extrasa,
in care voi pune rezultatul extragerii din coada ( cuvant sau cuvant + cuvant, depinde de comanda), dupa care imediat,
in stringul char *com_for_exec, retin doar prima parte din comanda, ca sa pot mai departe sa apelez functiile care ma intereseaza, corespunzator
daca com_for_exec va fi INSERT_LEFT sau CLEAR_CELL etc.etc. Ce fac in plus in interiorul if-urilor aferente comenzilor SEARCH, SEARCH_LEFT,
SEARCH_RIGHT, trebuie sa retin acolo in if, separat, sirul pe care doresc sa il caut, care reprez, practic partea de dupa spatiu si ceea ce extrag
din coada, pe care l-am retinut in stringul elem, pe care l am si copiat, pentru a il putea elibera din memorie mai tarziu.
    Daca nu il copiam, valgrind dadea eroare, dat fiind ca functia strtok distruge adresa stringului pe care a fost aplicata.
La final, ma mai ocup de functiile de tip QUERY. show, show_current si switch, care fac referire tot la lista din coada.
