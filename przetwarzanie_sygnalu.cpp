#define _USE_MATH_DEFINES
#include <cmath>
#include <complex>
#include <vector>
#include <stdexcept>
#include <algorithm>
#include <iostream>
#include "przetwarzanie_sygnalu.hpp"

using namespace std;

vector<double> generuj_sinus(int N, double f, double t0, double t1, double A)
{
    vector<double> s(N);
    double dt = (t1 - t0) / N;
    for (int i = 0; i < N; ++i)
    {
        double t = t0 + i * dt;
        s[i] = A * sin(2 * M_PI * f * t);
    }
    return s;
}

vector<double> generuj_cosinus(int N, double f, double t0, double t1, double A)
{
    vector<double> s(N);
    double dt = (t1 - t0) / N;
    for (int i = 0; i < N; ++i)
    {
        double t = t0 + i * dt;
        s[i] = A * cos(2 * M_PI * f * t);
    }
    return s;
}

vector<double> generuj_prostokatny(int N, double f, double t0, double t1, double A)
{
    vector<double> s(N);
    double dt = (t1 - t0) / N;
    for (int i = 0; i < N; ++i)
    {
        double t = t0 + i * dt;
        s[i] = sin(2 * M_PI * f * t) >= 0 ? A : -A;
    }
    return s;
}

vector<double> generuj_piloksztaltny(int N, double f, double t0, double t1, double A)
{
    vector<double> s(N);
    double dt = (t1 - t0) / N;
    for (int i = 0; i < N; ++i)
    {
        double t = t0 + i * dt;
        s[i] = A * 2.0 * (f * t - floor(0.5 + f * t));
    }
    return s;
}

vector<complex<double>> dft(const vector<double>& sygnal)
{
    int N = static_cast<int>(sygnal.size());
    vector<complex<double>> X(N);
    for (int k = 0; k < N; ++k)
    {
        complex<double> suma = 0;
        for (int n = 0; n < N; ++n)
        {
            double kat = -2.0 * M_PI * k * n / N;
            suma += sygnal[n] * complex<double>(cos(kat), sin(kat));
        }
        X[k] = suma;
    }
    return X;
}

vector<complex<double>> idft(const vector<complex<double>>& widmo)
{
    int N = static_cast<int>(widmo.size());
    vector<complex<double>> x(N);
    for (int n = 0; n < N; ++n)
    {
        complex<double> suma = 0;
        for (int k = 0; k < N; ++k)
        {
            double kat = 2.0 * M_PI * k * n / N;
            suma += widmo[k] * complex<double>(cos(kat), sin(kat));
        }
        x[n] = suma / static_cast<double>(N);
    }
    return x;
}

vector<double> operator*(const vector<double>& vec, double skalar)
{
    vector<double> wynik(vec.size());
    transform(vec.begin(), vec.end(), wynik.begin(), [skalar](double v) { return v * skalar; });
    return wynik;
}

vector<double> operator*(double skalar, const vector<double>& vec)
{
    return vec * skalar;
}

vector<double> operator+(const vector<double>& a, const vector<double>& b)
{
    if (a.size() != b.size()) {
        throw invalid_argument("Wektory musza miec taka sama dlugosc");
    }
    vector<double> wynik(a.size());
    for (size_t i = 0; i < a.size(); ++i)
    {
        wynik[i] = a[i] + b[i];
    }
    return wynik;
}

vector<complex<double>> filtruj_dolnoprzepustowo(const vector<complex<double>>& widmo, double prog)
{
    int N = static_cast<int>(widmo.size());
    vector<complex<double>> filtrowane(N);
    for (int k = 0; k < N; ++k) {
        double czestotliwosc = static_cast<double>(k) / N;
        if (czestotliwosc <= prog) {
            filtrowane[k] = widmo[k];
        } else {
            filtrowane[k] = 0;
        }
    }
    return filtrowane;
}

vector<vector<double>> sygnal_1d_na_2d(const vector<double>& sygnal, int powtorzenia)
{
    vector<vector<double>> obraz(powtorzenia, sygnal);
    return obraz;
}

vector<vector<double>> filtruj_2d_srednia(const vector<vector<double>>& obraz)
{
    int rows = obraz.size();
    int cols = obraz[0].size();
    vector<vector<double>> wynik(rows, vector<double>(cols, 0.0));

    for (int i = 1; i < rows - 1; ++i)
    {
        for (int j = 1; j < cols - 1; ++j)
        {
            double suma = 0.0;
            for (int di = -1; di <= 1; ++di)
            {
                for (int dj = -1; dj <= 1; ++dj)
                {
                    suma += obraz[i + di][j + dj];
                }
            }
            wynik[i][j] = suma / 9.0;
        }
    }
    return wynik;
}
