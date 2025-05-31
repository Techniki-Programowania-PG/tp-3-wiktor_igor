#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <vector>
#include <matplot/matplot.h>
#include "przetwarzanie_sygnalu.hpp"
#include "piki.hpp"


using namespace std;
using namespace matplot;

vector<vector<double>> sygnal1d_na_macierz2d(const vector<double>& sygnal, int wiersze)
{
    vector<vector<double>> macierz(wiersze, sygnal);
    return macierz;
}

void wizualizacja1d(const vector<double>& sygnal, const string& tytul)
{
    int N = sygnal.size();

    auto widmo = dft(sygnal);
    vector<double> amplituda(N);
    for (int i = 0; i < N; ++i)
    {
        amplituda[i] = abs(widmo[i]);
    }

    auto odzyskany_bez_filtru = idft(widmo);
    vector<double> sygnal_odzyskany_bez_filtru(N);
    for (int i = 0; i < N; ++i)
    {
        sygnal_odzyskany_bez_filtru[i] = odzyskany_bez_filtru[i].real();
    }

    auto widmo_filtrowane = filtruj_dolnoprzepustowo(widmo, 0.1);
    auto odzyskany = idft(widmo_filtrowane);
    vector<double> sygnal_odzyskany(N);
    for (int i = 0; i < N; ++i)
    {
        sygnal_odzyskany[i] = odzyskany[i].real();
    }

    figure(); plot(sygnal); title(tytul + " - oryginalny");
    figure(); plot(amplituda); title(tytul + " - widmo przed filtracja");
    figure(); plot(sygnal_odzyskany_bez_filtru); title(tytul + " - po IDFT (bez filtracji)");
    figure(); plot(sygnal_odzyskany); title(tytul + " - po filtracji dolnoprzepustowej");

        auto piki = znajdz_piki(sygnal, 0.5, 2);
    vector<double> wsp_x, wsp_y;
    for (auto i : piki)
    {
        wsp_x.push_back(i);
        wsp_y.push_back(sygnal[i]);
    }
    figure(); plot(sygnal); hold(on); plot(wsp_x, wsp_y, "ro"); title(tytul + " - piki");

}

int main()
{
    int N = 100;
    double czest = 5.0;
    double t0 = 0.0;
    double t1 = 1.0;
    double A = 1.0;

    auto sinus = generuj_sinus(N, czest, t0, t1, A);
    auto cosinus = generuj_cosinus(N, czest, t0, t1, A);
    auto prostokatny = generuj_prostokatny(N, czest, t0, t1, A);
    auto piloksztaltny = generuj_piloksztaltny(N, czest, t0, t1, A);

    wizualizacja1d(sinus, "Sinus");
    wizualizacja1d(cosinus, "Cosinus");
    wizualizacja1d(prostokatny, "Prostokatny");
    wizualizacja1d(piloksztaltny, "Piloksztaltny");

    show();
    return 0;
}