// Linear_Regression.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>

using namespace std;

const int n = 52416;			//Ilosc wierszy w kolumnie
//const int n = 100;			//Test na mniejszej ilosci danych
float D[n][8];					//Macierz skladajaca sie z danych pobranych z pliku
float sumaX = 0;
float sumaY = 0;				//Zmienne pomocnicze
float sumaX2 = 0;
float sumaXY = 0;
float tab_X[n];					//Tablica wyboru X
float tab_Y[n];					//Tablica wyboru Y
float wynikI[n];


void wczytywanie_danych()
{

	fstream fileOpen;
	fileOpen.open("projekt3.txt");

	if (!fileOpen.is_open())
	{
		cout << "Blad! Brak pliku badz problem z uprawnieniami :(" << endl;
	}
	else
	{

		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < 8; j++)									//Odczytywanie wartosci z pliku .txt
			{
				fileOpen >> D[i][j];
			}
			
		}
	}
	/*
	for (int i = 0; i < n; i++)
	{
		cout << i << ": ";

		for (int j = 0; j < 8; j++)
		{
			cout << setw(10);
			cout << D[i][j];											//Wyswietla zawartosc pliku ponad 50 tys linijek
		}
		cout << endl;
	}
	*/

	fileOpen.close();

}


void wybor(int a, int b)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (a - 1 == j)												//Wybor kolumn do utworzenia regresji
			{
				tab_X[i] = D[i][j];
			}
			if (b - 1 == j)
			{
				tab_Y[i] = D[i][j];
			}
		}
	}

	/*
	for (int i = 0; i < n; i++)
	{
		cout << setw(8) << tab_X[i] << " " << setw(8) << tab_Y[i] << endl;       //Wyswietlanie wybranych kolumn
	}
	*/
}

void Obliczenia()
{

	double x1, x2;		//szukane x1 = b x2 = a


	for (int i = 0; i < n; i++)
	{
		sumaX += tab_X[i];								//sumowanie wszystkich X
		sumaX2 += tab_X[i] * tab_X[i];					//podnoszenie do kwadratu X
		sumaY += tab_Y[i];								//sumowanie wszystkich Y
		sumaXY += tab_X[i] * tab_Y[i];					//sumowanie X * Y
	}

	x1 = ((n * sumaXY) - (sumaX * sumaY)) / ((n * sumaX2) - (sumaX * sumaX));  //wzor na b
	x2 = (sumaY / n) - (x1 * (sumaX / n));									   //wzor na a
	
	cout << "wartosc a: " << x2 << "  wartosc b: " << x1 << endl;
	cout << "\nOszacowana funkcja regresji wyglada: y = " << x2 << " + " << x1 << "x" << endl;

	for (int i = 0; i < n; i++)
	{																			//wspolrzedne lini regresji
		wynikI[i] = x2 + (x1 * tab_X[i]);
		

	}

	ofstream ZAPIS("Wyniki.txt");

	for (int i = 0; i < n; i++)
	{

		ZAPIS << i + 1 << ":  " << tab_X[i] << "  " << wynikI[i] << endl;			//zapisanie wynikow w pliku Wyniki.txt

	}
	cout << "\nWyniki zostaly eksportowane do pliku Wyniki.txt" << endl;

	ZAPIS.close();

}


int main()
{
	int a, b;																	//deklaracja i wprowadzanie danych


	wczytywanie_danych();

	cout << "\nKtore dane chcesz wybrac do regresji? (UWAGA W kolumnach jest ponad 52 tys danych): \n";
	cout << "\n 1. Temperatura\n 2. Wilgotnosc\n 3. Wilgotnosc wiatru\n 4. Ogolne Przeplywy rozproszone\n 5. Przeplywy rozproszone\n 6. Zuzycie energii strefa 1\n 7. Zuzycie energii strefa 2\n 8. Zuzycie energii strefa 3\n ";
	cout << "\nWybor pierwszy: "; cin >> a;
	cout << "Wybor drugi: "; cin >> b;

	wybor(a, b);
	Obliczenia();

}

