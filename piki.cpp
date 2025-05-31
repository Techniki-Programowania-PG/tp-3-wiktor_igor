#include "piki.hpp"

using namespace std;

vector<size_t> znajdz_piki(const vector<double>& sygnal, double prog, size_t min_odleglosc)
{
    vector<size_t> piki;
    size_t ostatni = -min_odleglosc - 1;
    for (size_t i = 1; i + 1 < sygnal.size(); ++i)
    {
        if (sygnal[i] > prog && sygnal[i] > sygnal[i - 1] && sygnal[i] > sygnal[i + 1] && (i - ostatni > min_odleglosc))
        {
            piki.push_back(i);
            ostatni = i;
        }
    }
    return piki;
}