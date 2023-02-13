#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;




// funkcja rozwiązująca układ n równań liniowych o n niewiadomych metodą Gaussa wykorzystując pivot 

void GaussWithPivot(float** Tab, int size)
{
	for (int k = 0; k < (size - 1); k++)
	{
		int w = k;
		float max = abs(Tab[k][k]); // abs - absolute value zwraca wartość bezwględną z podanej liczby

		for (int i = (k + 1); i < size; i++)
		{
			if (abs(Tab[i][k]) > max) // jeżeli istnieje element większy od max zmiana elementu największego
			{
				max = abs(Tab[i][k]);
				w = i;
			}
		}

		if (max == 0)  // jeżeli element maksymalny jest równy 0, zostaje wypisany komunikat 
		{
			cout << "Max = 0, nie da sie rozwiazac !" << endl;  // ponieważ już jest to największy element w kolumnie a nie może być 0 na przekątnej 
			return;
		}

		if (w != k)
		{
			float p;
			for (int i = 0; i < (size + 1); i++)
			{
				p = Tab[k][i];
				Tab[k][i] = Tab[w][i];  // podmiana wartości
				Tab[w][i] = p;
			}
		}

		// dalsza część taka sama jak bez pivota
		float mnoznik = 0.0f;
		for (int k = 0; k < (size - 1); k++)
		{
			for (int i = (k + 1); i < size; i++)
			{
				if (Tab[k][k] == 0) // sprawdzenie czy na przekątnej nie ma 0
				{
					cout << "Na przekatnej macierzy wystapila wartosc 0 !!!" << endl;
					return;
				}
				mnoznik = Tab[i][k] / Tab[k][k]; // obliczamy mnoznik
				for (int j = k; j < (size + 1); j++)
				{
					Tab[i][j] -= (mnoznik * Tab[k][j]); // od i-tego wiersza odejmujemy wiersz zerowy pomnożony przez mnożnik 
				}
			}
		}

	}
}


void ShowTab(float** Tab, int size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < (size + 1); j++)
		{
			cout << Tab[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

int main()
{
	int TabPoints[8] = { 1,2,3,4,5,6,7,8 }; // tabela przechowywująca punkty do aproksymacji 
	int TabValue[8] = { 2,4,3,5,6,9,11,11 }; // tabela przechowywująca wartości w punktach do aproksymacji 

	float weight = 1; // dla wszystkich punktów waga jest równa 1
	int size = 2;
	float Tab[8][8];

	float* Tab1 = new float[size];

	for (int k = 0; k < size; k++)
	{
		for (int j = 0; j < size; j++)
		{
			float result = 0;

			for (int i = 0; i < 8; i++)
			{
				result += pow(TabPoints[i], k) * pow(TabPoints[i], j) * weight;
			}
			Tab[k][j] = result;
		}
	}

	for (int k = 0; k < size; k++)
	{
		float result = 0;
		for (int i = 0; i < 8; i++)
		{
			result += pow(TabPoints[i], k) * TabValue[i] * weight;
		}
		Tab1[k] = result;
	}


	float** MacRoz = new float* [size]; // przygotowana tablica dla macierzy rozszerzonej

	for (int i = 0; i < size; i++)
	{
		MacRoz[i] = new float[size + 1];
	}


	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size + 1; j++)
		{
			if (j == size)
			{
				MacRoz[i][j] = Tab1[i];
			}
			else
			{
				MacRoz[i][j] = Tab[i][j];
			}
		}
	}

	GaussWithPivot(MacRoz, 2);

	float* GausResult = new float[size];
	for (int i = 0; i < size; i++)
	{
		GausResult[i] = 1;
	}
	float result = 0;
	for (int i = size - 1; i >= 0; i--)
	{
		result = MacRoz[i][size];
		for (int j = size - 1; j > i; j--)
		{
			result -= MacRoz[i][j] * GausResult[j];
		}
		GausResult[i] = result / MacRoz[i][i];
	}


	cout << "Liczba wezlow: " << 8 << endl<<endl;
	cout << "Wspolczynniki wielomianu aproksymujacego: " << endl;
	for (int i = 0; i < size; i++)
	{
		cout << GausResult[i] << endl;
	}
	cout << endl << "Podane wezly aproksymacji i wartosci w wezlach oraz obliczone wartosci funkcji aproksymujacej w wezlach aproksymacji:" << endl;
	float value = 0;
	for (int i = 0; i < 8; i++)
	{
		value = 0;
		for (int i = 0; i < 8; i++)
		{
			value = 0;
			for (int j = 0; j < size; j++)
			{
				value += pow(TabPoints[i], j) * GausResult[j];
			}
			cout << TabPoints[i] << " " << TabValue[i] << " " << value << endl;
		}
		return 0;
	}
}


	









