// podzial_sekretu2.cpp: definiuje punkt wejścia dla aplikacji konsolowej.
//

#include "stdafx.h"
#include <iostream>
#include <cstdlib>

using namespace std;

bool isPrime(int number)
{
	for (int a = 2; a < number; a++) {
		if (number % a == 0) {
			return false;
		}
	}
	return true;
}

long int potega(long int podstawa, int wykladnik)
{
	int wynik = 1;

	for (int i = 0; i<wykladnik; i++)
		wynik *= podstawa;

	return wynik;
}

int sekret_tryw(int s, int n, int k) {

	if (s > k)
		return false;

	//int k = 1000; //wartość określająca rozmiar przestrzeni liczbowej
	//int n = 5; //ilość udziałów
	//int s = 954; //wartość sekretu 0 do k-1
	int sn[1000];

	for (int i = 0; i < n; i++) {
		if (i == n - 1) {
			int temp = s;
			for (int k = 0; k < n - 1; k++) {
				temp = temp - sn[k];
			}

			sn[i] = temp % k;
		}
		else {
			sn[i] = rand() % k;
		}
	}

	int s_odt;
	int temp = 0;

	for (int i = 0; i < n; i++) {

		cout << "s" << i << ": " << sn[i] << endl;

		temp = temp + sn[i];
	}

	s_odt = temp % k;

	cout << "s: " << s_odt << endl;

	return true;
}

int shamir(int s, int n_calk, int n_wym, int pierwsza) {

	if (n_calk < n_wym) {
		return false;
	}

	int sn[1000];
	int a[1000];
	double l[1000];
	int prime = 2;

	//losowanie liczby pierwszej
	if (isPrime(pierwsza) != true || pierwsza < s || pierwsza < n_calk) {
		for (int i = 1; i > 0;) {
			prime = rand() % 1000;
			if (isPrime(prime) == true && prime > s && prime > n_calk) {
				break;
			}
		}
	}
	else {
		prime = pierwsza;
	}
	
	//wyznaczenie współczynników a wielomianu
	for (int i = 0; i < n_wym - 1; i++) {
		a[i] = rand();

		cout << "a" << i << ": " << a[i] << endl;
	}

	//obliczanie udziałów s
	for (int i = 0; i < n_calk; i++) {

		sn[i] = 0;

		for (int k = 0; k < n_wym - 1; k++) {

				sn[i] = sn[i] + (a[k] * potega((i + 1), (k+1)));
		}
		sn[i] = (sn[i] + s) % prime;
	}

	//Wyświetlanie danych
	cout << endl << "Sekret: " << s << endl;
	cout << "Prime: " << prime << endl << endl;
	for (int i = 0; i < n_calk; i++) {
		cout << "s" << i + 1 << ": " << sn[i] << "  (" << sn[i] << ", " << i + 1 << ")" << endl;

	}

	//wyznaczanie wartości wyrazu wolnego z wielomianu interpolacyjnego
	for (int k = 0; k < n_wym; k++) {

		int mianownik = 1;
		int licznik = 1;

		for (int j = 0; j < n_wym; j++) {

			if ((j + 1) != (k + 1)) {
				licznik = licznik * (j + 1) * (-1);
				mianownik = mianownik * ((k + 1) - (j + 1));
			}			
		}
		//cout << endl << "Licznik " << k << ": " << licznik;
		//cout << endl << "Mianownik " << k << ": " << mianownik << endl;
		l[k] = licznik / mianownik;
	}

	int sum = 0;
	int new_sekret = 0;

	//wyznaczanie wartości sekretu przy pomocy uzyskanych wartości wyrazów wolnych, liczby pierwszej i udziałów częściowych
	for (int i = 0; i < n_wym; i++) {
		int sum = 0;
		sum = sn[i] * l[i];
		sum = sum % prime;
		new_sekret += sum;
	}

	cout << endl << "Wartosc sekretu: " << new_sekret << endl << endl;

	return true;
}



int main()
{
	cout << "Metoda trywialna: " << endl;
	sekret_tryw(323, 5, 1000);
	cout << endl;
	cout << "Schemat Shamira: " << endl;
	shamir(323, 4, 4, 827);


	system("pause");

    return 0;
}

