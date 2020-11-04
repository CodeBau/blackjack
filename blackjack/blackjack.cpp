#pragma warning(disable:4996)

#include <iostream>
#include <time.h>               //czas do funkcji losowej
#include <cstdlib>              //cst do czyszczenia ekranu
#include <iomanip>              //do setw - czyli odsuwania napisu
#include <conio.h>              //zeby dzialalo klikanie responsywne, po nacisnieciu klawisza odrazu wybierana opcja. ****

using namespace std;
int karta[52][2];               //[lp][wartosc]
string kartas[52];              //[jaka karta]
int numer;                      // do sprawdzenia podaje numer karty US
int byla[52];                   // tablica ze zuzytymi kartami
int lp;                         // liczba porzadkowa w tali
string symbols;                 // zmienna potrzebna do przerabiania int na string
string koncowy;                 // zmienna potrzebna do przerabiania int na string
int wartosc;                    // ile pkt ma karta w oczko
string kolor;                   // kolor karty
char tn;                                // T/N wybor czy grasz
int wylosowana;                 // nr karty wylosowanej
int suma_k = 0;                   //suma oczek dla krupiera
int suma_g = 0;                   //suma oczek dla gracza
int ile_wylosowanych = 0;         //suma kart wylosowanych
int losowanie_ok;               //akceptowanie wylosowanej karty/ unikalnojsc karty


int losowanie()                                                                                 //funkcja losowania karty bez powtorzenia
{
    srand(time(NULL));
    do
    {
        wylosowana = rand() % 51 + 1;
        wylosowana = rand() % 51 + 1;                                                     //losowanie 2 razy bo druga zawsze lepsza

        losowanie_ok = 1;

        for (int zw = 1; zw <= ile_wylosowanych; zw++)
        {
            if (wylosowana == byla[zw - 1])
                losowanie_ok = 0;
        }

        if (losowanie_ok == 1)
        {
            byla[ile_wylosowanych] = wylosowana;
            ile_wylosowanych++;
        }

    } while (losowanie_ok != 1);
    return wylosowana;
}

void punkty(int suma)                                                               //void na odmiane punkty
{
    switch (suma)                                                                   //case na koncowke punkt,punkty,ponktow
    {
    case 1:
        cout << " punkt.";
        break;

    case 2:
    case 3:
    case 4:
        cout << " punkty.";
        break;

    default:
        cout << " punktow.";
    }
}

int main()
{
    for (int i = 1; i <= 4; i++)
    {
        if (i == 1)
            kolor = "Czerwo";
        else if (i == 2)
            kolor = "Zolandz";
        else if (i == 3)
            kolor = "Dzwonek";
        else if (i == 4)
            kolor = "Wino";

        for (int e = 1; e <= 13; e++)
        {
            lp = e + (i - 1) * 13;
            karta[lp - 1][1] = lp;

            if (e >= 1 && e <= 9)
            {
                sprintf((char*)symbols.c_str(), "%d", e + 1);
                koncowy = symbols.c_str();
                kartas[lp - 1] = koncowy + " " + kolor;
                karta[lp - 1][2] = e + 1;
            }
            else if (e == 10)
            {
                kartas[lp - 1] = "J " + kolor;
                karta[lp - 1][2] = 2;
            }
            else if (e == 11)
            {
                kartas[lp - 1] = "Q " + kolor;;
                karta[lp - 1][2] = 3;
            }
            else if (e == 12)
            {
                kartas[lp - 1] = "K " + kolor;
                karta[lp - 1][2] = 4;
            }
            else
            {
                kartas[lp - 1] = "A " + kolor;
                karta[lp - 1][2] = 11;
            }
        } // do for z e

    } //do for z i


    for (int i = 1; i <= 50; i++)
    {
        if (i == 1)
        {
            cout << "Rozpoczynamy gre? T/N: ";
            tn = _getch();
        }
        else
        {
            cout << "Chcesz kolejna karte? T/N: ";
            tn = _getch();
        }

        switch (tn)
        {
        case 't':
        case 'T':
        {
            if (i == 1)
            {
                system("cls");
                cout << "==========Runda " << i << "==========" << endl;

                losowanie();                                                                                                                                                                            //wylosowanna 1 karta dla krupiera

                cout << "Krupier wylosowal karty: " << endl;
                cout << "Dwie dla siebie: " << kartas[wylosowana] << " oraz karte ??" << endl;
                cout << setw(60) << "ma teraz: ";
                suma_k = suma_k + karta[wylosowana][2];
                cout << suma_k << " + ??";
                punkty(suma_k);
                cout << endl << endl << endl;

                losowanie();                                                                                                                                                                              //wylosowanna 2, "zakryta" karta dla krupiera

                losowanie();                                                                                                                                                                            //karta wylosowana dla grasza
                cout << "Dwie karty dla Ciebie: " << kartas[wylosowana] << " oraz ";
                suma_g = suma_g + karta[wylosowana][2];
                losowanie();
                cout << kartas[wylosowana] << endl;
                cout << setw(62) << " masz teraz: ";
                suma_g = suma_g + karta[wylosowana][2];
                cout << suma_g;
                punkty(suma_g);
                cout << endl << endl << endl;
            }
            else
            {
                system("cls");
                cout << "==========Runda " << i << "==========" << endl;
                cout << "Krupier posiada: " << endl;                                                                                                                                        // przypomnienie kar posiadanych przez krupiera
                cout << kartas[byla[0]] << " oraz karte ??" << endl;
                cout << setw(54) << "ma: ";
                cout << suma_k << " + ??";
                punkty(suma_k);
                cout << endl << endl;

                losowanie();                                                                                                                                                                            //kolejna karta wylosowana dla grasza
                cout << "Dla Ciebie wylosowal kolejna karte: " << kartas[wylosowana] << endl;
                cout << setw(60) << " masz teraz: ";
                suma_g = suma_g + karta[wylosowana][2];
                cout << suma_g;
                punkty(suma_g);
                cout << endl << endl << endl;

                if (suma_g > 21)
                {
                    cout << "Niestety przegrywasz" << endl << endl << endl << endl << endl << endl << endl << endl;
                    i = 51;
                }
            }

            /*for (int z=1; z<ile_wylosowanych+1; z++)                                                                                                                          //sprawdzenie wylosowanych liczb
            {
                cout<<z<<" - ";
                cout<<byla[z-1]<<endl;
            }
            */
        }
        break;

        case 'n':
        case 'N':
        {
            if (i == 1)
            {

                cout << endl << "No to nie" << endl << endl << endl << endl << endl << endl << endl << endl;
                i = 51;
            }
            else
            {
                system("cls");
                cout << "==========Runda " << i - 1 << "==========" << endl;
                cout << "Krupier obraca karte ?? Byla nia: " << kartas[byla[1]] << endl;                                                                               // krupier obraca karte zagadke
                cout << "Posiada: " << kartas[byla[0]] << " oraz " << kartas[byla[1]] << endl;
                suma_k = suma_k + karta[byla[1]][2];
                cout << setw(54) << "ma: ";
                cout << suma_k;
                punkty(suma_k);
                cout << endl << endl;
                cout << setw(54) << "Ty natomiast: ";
                cout << suma_g;
                punkty(suma_g);
                cout << endl << endl << endl;
                if (suma_g > suma_k)
                    cout << "Wygrywasz!" << endl << endl << endl << endl << endl << endl << endl << endl;
                else if (suma_g < suma_k)
                    cout << "Przerywasz!" << endl << endl << endl << endl << endl << endl << endl << endl;
                else
                    cout << "Remis" << endl << endl << endl << endl << endl << endl << endl << endl;
                i = 51;
            }

        }
        break;

        default:
        {
            cout << "Nie ma takiej opcji" << endl;
            i--;
        }

        }
    }
    return 0;
} //do maina
