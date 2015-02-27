#include <stdio.h>

int mystrlen(char* str)
{
    int i=0;
    while(str[i++]!=0);
    return i-1;
}

int mystrcmp(char* str1, char* str2)
{
    int flag, i=0;
    do
    {
        flag=(str1[i]==str2[i]);
    }
    while(flag && str1[i]!=0 && str2[i++]!=0);
    return flag;
    
}
int mystrcmp2(char* str1, char* str2)
{
    int flag=1, i=0, k=0;
    int counter=0, output=0;
    int length=mystrlen(str1);
    int length2=mystrlen(str2);
    char* tabW;
    char* tabM;
    int cmplength;
    
    if (length<length2)
    {
        tabW=str2;
        tabM=str1;
    }
    else
    {
        tabW=str1;
        tabM=str2;
    }
    
    cmplength=mystrlen(tabM);
    
    while(tabW[i]!=0)
    {
            if (tabM[k]==tabW[i])
            {
                flag=(tabM[k]==tabW[i]);
                k++;
            }
            else
            {
                flag=0;
                k=0;
            }
            
            i++;
            counter = counter + flag;
            
            if (counter==cmplength)
            {
                output++;
                counter=0;
            }
            
    }
        return output;
}

int main()
{
    // Wyznaczanie dlugosci ciagu znakowego
    char tekst1[]="Ala";
    char tekst2[]="Ala ma kota i Ala";
    
    printf("Dlugosc ciagu znakowego \"%s\" wynosi %d\n", tekst1, mystrlen(tekst1));
    
    int flag=mystrcmp(tekst1, tekst2);
    
    // Wypisanie wyniku
    if(flag==1)
    {
        printf("Ciagi znakowe \"%s\" oraz \"%s\" sa identyczne.\n", tekst1, tekst2);
    }
    else
    {
        printf("Ciagi znakowe \"%s\" oraz \"%s\" sa rozne.\n", tekst1, tekst2);
    }
    
    int counter=mystrcmp2(tekst1, tekst2);
    
    printf("\"%s\" wystepuje w tekscie \"%s\" %d razy\n",tekst1, tekst2, counter);
    
    counter=mystrcmp2(tekst2, tekst1);
    
    printf("\"%s\" wystepuje w tekscie \"%s\" %d razy\n",tekst1, tekst2, counter);
    
    return 0;
}