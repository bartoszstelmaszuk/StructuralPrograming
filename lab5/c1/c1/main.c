#include <stdio.h>
#include <string.h>
#include <stdlib.h>

enum Rodzaj{OWOC, WARZYWO, INNY}; // Wyliczenie stosujemy, gdy chcemy oznaczyc wiele predefiniowanych rodzajow jakiejs cechy
// Jest to wygodniejszy zapis rownowazny const int OWOC = 0; const int WARZYWO = 1; const int INNY = 2;

#define NAZWA_LEN 16
#define IMIE_LEN 8
#define LICZBA_PRZED 3

struct Przedmiot{ // Struktura jest zbiorem pol, opisanym typami zmiennych
    char nazwa[NAZWA_LEN];
    char kolor[NAZWA_LEN];
    float cena;
    enum Rodzaj rodzaj;
};

typedef struct Klient{ // W strukturach mozemy uzywac innych struktur
    char imie[IMIE_LEN];
    float gotowka;
    struct Przedmiot koszyk[LICZBA_PRZED];
} klient_t;   // wraz ze slowem typedef w ten sposob definiujemy wlasny typ danych (typowo do nazwy oznaczajacej typ dopisuje sie '_t' aby odroznic dany identyfikator od np. nazwy zmiennej)

union Liczba{          // Unia jest jednym polem, do ktorego mozemy odwolywac sie w rozny sposob
    float ulamkowa;
    int calkowita;
};



void print_przedmiot(struct Przedmiot p){ // Do pol struktury odwolujemy sie operatorem "."
    printf("%s jest %s i kosztuje %f.\n", p.nazwa, p.kolor, p.cena);
}

void opisz_przedmiot(struct Przedmiot* p, char* nazwa, char* kolor, enum Rodzaj rodzaj, float cena){
    strcpy(p->nazwa, nazwa); // Do pol wskaznika na strukture odwolujemy sie operatorem "->"
    strcpy(p->kolor, kolor);
    p->cena = cena;
    p->rodzaj = rodzaj;
}

void zaplac(struct Klient* k){
    float suma = 0.0;
    float suma2=0.0;
    int n;
    
    for(n = 0; n < LICZBA_PRZED; n++)
        suma += k->koszyk[n].cena;
    
    if(suma < k->gotowka)
        printf("Klient %s zaplacil %f.\n\n", k->imie, suma);
    else
    {
        printf("Klient %s nie moze zaplacic %f!\n\n", k->imie, suma);
        
        for(n=0; n<LICZBA_PRZED;n++)
        {
            if (k->koszyk[n].rodzaj==0)
            {
                suma2+= k->koszyk[n].cena;
            }
        }
        printf("Klient %s moze zaplacic %f za same owoce\n\n", k->imie, suma2);
    }
}

void wyswietl_liczbe(union Liczba k)
{
    printf("Rozmiar unii: %d\twartosc calkowita: %d\twartosc ulamkowa: %f\n", sizeof(k), k.calkowita, k.ulamkowa);
}

int main(){
    struct Przedmiot banan, pomarancza, pomidor, mleko; // Zmienne odwolujace sie do struktu definiujemy podobnie do typow podstawowych
    struct Przedmiot kompot = { "Kompot wisniowy", "czerwony", 2.5, INNY };  // Przypisanie wartosci do pol struktury od razu w momencie jej deklarowania
    union Liczba k;
    
    opisz_przedmiot(&banan, "Banan", "zolty", OWOC, 1.0);
    opisz_przedmiot(&pomarancza, "Pomarancza", "pomaranczowa", OWOC, 1.5);
    opisz_przedmiot(&pomidor, "Pomidor", "czerwony", WARZYWO, 1.2);
    opisz_przedmiot(&mleko, "Mleko", "biale", INNY, 2.0);
    
    print_przedmiot(banan);
    print_przedmiot(pomarancza);
    print_przedmiot(pomidor);
    print_przedmiot(mleko);
    print_przedmiot(kompot);
    
    printf("\nRozmiar struktury Przedmiot: %d\n", sizeof(struct Przedmiot)); // rozmiar struktury jest suma rozmiarow typow ktore zawiera
    printf("Rozmiar struktury Klient: %d\n", sizeof(struct Klient)); // dlaczego tu jest taki rozmiar?
    printf("Rozmiar typu strukturalnego klient_t: %d\n\n", sizeof(klient_t)); // zapis w tej linijce jest rownowazny zapisowi z linijki powyzszej
    klient_t* klient = malloc(sizeof(klient_t)); // do struktur rowniez mozemy przypisac pamiec dynamicznie; tu dodatkowo korzystamy ze struktury Klient zdefiniowanej jako wlasny typ danych `klient_t`
    
    klient->gotowka = 3.0;
    strcpy(klient->imie, "Ala"); // dlaczego tu robimy tak, a nie poprostu przypisujemy?
    klient->koszyk[0] = banan;
    klient->koszyk[1] = pomarancza;
    klient->koszyk[2] = mleko;
    
    zaplac(klient);
    
    // Dlaczego ponizsze wywolania funkcji wyswietl_liczbe() daja tak rozne wyniki?
    k.calkowita = 5;
    wyswietl_liczbe(k);
    k.ulamkowa = 5;
    wyswietl_liczbe(k);
    
    free(klient);   // musze zwolnic zaalokowana dynamicznie pamiec
    
    return 0;
}