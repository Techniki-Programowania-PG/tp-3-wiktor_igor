#ifndef PRZETWARZANIE_SYGNALU_H
#define PRZETWARZANIE_SYGNALU_H

#include <vector>
#include <complex>

using namespace std;

vector<double> generuj_sinus(int liczba_probek, double czestotliwosc, double czas_pocz, double czas_kon, double amplituda = 1.0);
vector<double> generuj_cosinus(int liczba_probek, double czestotliwosc, double czas_pocz, double czas_kon, double amplituda = 1.0);
vector<double> generuj_prostokatny(int liczba_probek, double czestotliwosc, double czas_pocz, double czas_kon, double amplituda = 1.0);
vector<double> generuj_piloksztaltny(int liczba_probek, double czestotliwosc, double czas_pocz, double czas_kon, double amplituda = 1.0);

vector<complex<double>> dft(const vector<double>& sygnal);
vector<complex<double>> idft(const vector<complex<double>>& widmo);

vector<double> operator*(const vector<double>& vec, double skalar);
vector<double> operator*(double skalar, const vector<double>& vec);
vector<double> operator+(const vector<double>& a, const vector<double>& b);

vector<complex<double>> filtruj_dolnoprzepustowo(const vector<complex<double>>& widmo, double prog);

vector<vector<double>> sygnal_1d_na_2d(const vector<double>& sygnal, int powtorzenia);
vector<vector<double>> filtruj_2d_srednia(const vector<vector<double>>& obraz);

#endif