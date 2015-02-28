//
//  main.c
//  c3
//
//  Created by Bartosz Stelmaszuk on 28/02/15.
//  Copyright (c) 2015 Bartosz Stelmaszuk. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define DLUGOSC 256

enum Gatunek{Jazz, Pop, Rock};

enum Typ{MP3, WAV, WMA, OPUS};

char* EnumGatunekToString(enum Gatunek gatunek)
{
    switch (gatunek)
    {
        case 0:
            return "Jazz";
            break;
        case 1:
            return "Pop";
            break;
        case 2:
            return "Rock";
            break;
    }
}
char* EnumTypToString(enum Typ typ)
{
    switch (typ)
    {
        case 0:
            return "MP3";
            break;
        case 1:
            return "WAV";
            break;
        case 2:
            return "WMA";
            break;
        case 3:
            return "OPUS";
            break;
    }
}
struct Opis
{
    char wykonawca[DLUGOSC];
    char tytul[DLUGOSC];
    enum Gatunek gatunek;
};

typedef struct plik
{
    char sciezka[DLUGOSC];
    enum Typ typ;
    float czas;
    struct Opis opis;
}plik_t;

void wypelni_plik(plik_t* plik, char* sciezka, enum Typ typ, float czas, char* wykonawca, char* tytul, enum Gatunek gatunek)
{
    strcpy(plik->sciezka, sciezka);
    plik->czas=czas;
    plik->typ=typ;
    plik->opis.gatunek=gatunek;
    strcpy(plik->opis.tytul, tytul);
    strcpy(plik->opis.wykonawca, wykonawca);
}
void wypiszBD(plik_t* utwor,int max)
{
    printf("\n%3s\t%-45s\t%4s\t%-5s\t%-20s\t%-25s\t%-6s\n", "Nr.", "Sciezka", "Typ", "Czas", "Wykonawca", "Tytul", "Gatunek");
    
    for(int i=0; i<max; i++)
    {
        printf("%2d\t%-45s\t%4s\t%-2.2lf\t%-20s\t%-25s\t%-6s\n",i+1, utwor[i].sciezka, EnumTypToString(utwor[i].typ), utwor[i].czas, utwor[i].opis.wykonawca, utwor[i].opis.tytul, EnumGatunekToString(utwor[i].opis.gatunek));
    }
    printf("\n");
}
void wypiszRekord(plik_t*utwor, int i)
{
    printf("\n%3s\t%-45s\t%4s\t%-5s\t%-20s\t%-25s\t%-6s\n", "Nr.", "Sciezka", "Typ", "Czas", "Wykonawca", "Tytul", "Gatunek");
    
    printf("%2d\t%-45s\t%4s\t%-2.2lf\t%-20s\t%-25s\t%-6s\n\n",i, utwor[i-1].sciezka, EnumTypToString(utwor[i-1].typ), utwor[i-1].czas, utwor[i-1].opis.wykonawca, utwor[i-1].opis.tytul, EnumGatunekToString(utwor[i-1].opis.gatunek));
    
}
void dodajRekord(plik_t* utwor)
{
    char sciezka[DLUGOSC];
    printf("\nPodaj sciezke pliku: ");
    while(getchar()!='\n');
    gets(sciezka);
    
    enum Typ typ;
    printf("\nPodaj Typ pliku (0-MP3, 1-WAV, 2-WMA, 3-OPUS): ");
    scanf("%d",&typ);
    
    float czas;
    printf("\nPodaj czas trwania pliku: ");
    scanf("%e", &czas);
    
    char wykonawca[DLUGOSC];
    printf("\nPodaj wykonawce: ");
    while(getchar()!='\n');
    gets(wykonawca);
    
    char tytul[DLUGOSC];
    printf("\nPodaj tytul: ");
    gets(tytul);
    
    enum Gatunek gatunek;
    printf("\nPodaj gatunek (0-Jazz, 1-Pop, 2-Rock): ");
    scanf("%d", &gatunek);
    
    strcpy(utwor->sciezka, sciezka);
    utwor->typ=typ;
    utwor->czas=czas;
    strcpy(utwor->opis.wykonawca, wykonawca);
    strcpy(utwor->opis.tytul, tytul);
    utwor->opis.gatunek=gatunek;
    
    
    
}

int main()
{
    int ile=10, a, flag=1;
    int indeks=4;
    
    plik_t* utwor=malloc(sizeof(plik_t)*ile);
    
    wypelni_plik(&utwor[0], "C://music/SamSmith-StayWithMe", MP3, 3.14, "Sam Smith", "Stay with me", Rock);
    wypelni_plik(&utwor[1], "C://music/JasonMraz-ImYours", OPUS, 3.14, "Jason Mraz", "I'm Yours", Pop);
    wypelni_plik(&utwor[2], "C://music/Adele-SomeoneLikeYou", WMA, 3.5, "Adele", "SomeoneLikeYou", Rock);
    wypelni_plik(&utwor[3], "C://music/ElizeFitzgerald-SmoothSailing", WAV, 3.02, "Elize Fitzgerald", "SmoothSailing", Jazz);
    
    
    while (flag!=0)
    {
        printf("[1]Wyświetl Baze Danych\n");
        printf("[2]Wyswietl pojedynczy rekord\n");
        printf("[3]Dodaj rekord do Bazy Danych\n");
        printf("[4]Zakoncz program\n");
        
        scanf("%d", &a);
        
        switch (a) {
            case 1:
                wypiszBD(utwor, indeks);
                break;
            case 2:
                printf("\nKtory rekord wyswietlic?\t");
                scanf("%d", &a);
                wypiszRekord(utwor, a);
                break;
            case 3:
                if (indeks<ile)
                {
                    dodajRekord(&utwor[indeks]);
                    indeks++;
                }
                else
                {
                    printf("Baza danych zostało zapełniona. Nie można dodać nowego rekordu\n\n");
                }
                break;
            case 4:
                flag=0;
                break;
            
            default:
                printf("Choose number from 1 to 4\n");
                break;
        }
    }
    return 0;
}