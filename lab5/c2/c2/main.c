#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

typedef struct Punkt{
    float x;
    float y;
}Punkt_t;

float random01(){
    float temp = rand(); // funkcja rand zwraca liczby calkowite, a my chcemy zmienno przecinkowe z zakresu <0.0;1.0>
    
    return temp / RAND_MAX;
}

void print_punkt(struct Punkt punkt){
    printf("x = %f, y = %f\n", punkt.x, punkt.y);
}

struct Punkt srodkowy_punkt(struct Punkt* punkty, int ile){
    struct Punkt srodkowy;
    srodkowy.x = 0.0;
    srodkowy.y = 0.0;
    
    int n;
    
    printf("Licze srednia dla %d punktow\n", ile);
    
    for(n = 0; n < ile; n++){
        srodkowy.x += punkty[n].x;
        srodkowy.y += punkty[n].y;
    }
    
    srodkowy.x /= ile;
    srodkowy.y /= ile;
    
    return srodkowy; // nie wolno zwracac adresu do lokalnej zmiennej! jak to poprawic?
}

int main(){
    srand(time(NULL)); // inicjacja funkcji losowej ze zmienna wartoscia (aktualny czas), co sie stanie jak tu bedzie ta sama wartosc?
    
    int ile=3, n;
    
    printf("Wpisz ile punktow wylosowac:\n");
    scanf("%d",&ile);
    
    Punkt_t* punkty=malloc(sizeof(Punkt_t)*ile); // to trzeba zrobic dynamicznie (taka deklaracja nie skompiluje sie w niektorych wersjach jezyka C)
    
    for(n = 0; n < ile; n++){
        punkty[n].x = random01();
        punkty[n].y = random01();
        
        print_punkt(punkty[n]);
    }
    
    struct Punkt srodek = srodkowy_punkt(punkty, ile); // zle przekazana jest liczba punktow
    
    print_punkt(srodek);
    
    return EXIT_SUCCESS; // jezeli korzystamy z naglowka stdlib mozemy zrobic tak zamiast pisac return 0;
}