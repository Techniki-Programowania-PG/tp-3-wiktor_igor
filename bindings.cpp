#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/complex.h>
#include "przetwarzanie_sygnalu.hpp"
#include "piki.hpp"

namespace py = pybind11;

PYBIND11_MODULE(sygnaly, m)
{
    m.doc() = "Biblioteka C++ do przetwarzania sygnalow jako modul pythonowy przy uzyciu pybind11";

    m.def("generuj_sinus", &generuj_sinus, "Generuj sygnal sinusoidalny",
          py::arg("N"), py::arg("f"), py::arg("t0"), py::arg("t1"), py::arg("A"));

    m.def("generuj_cosinus", &generuj_cosinus, "Generuj sygnal cosinusoidalny",
          py::arg("N"), py::arg("f"), py::arg("t0"), py::arg("t1"), py::arg("A"));

    m.def("generuj_prostokatny", &generuj_prostokatny, "Generuj sygnal prostokatny",
          py::arg("N"), py::arg("f"), py::arg("t0"), py::arg("t1"), py::arg("A"));

    m.def("generuj_piloksztaltny", &generuj_piloksztaltny, "Generuj sygnaL piLokształtny",
          py::arg("N"), py::arg("f"), py::arg("t0"), py::arg("t1"), py::arg("A"));

    m.def("dft", &dft, "Transformata Fouriera");
    m.def("idft", &idft, "Odwrotna transformata Fouriera");

    m.def("filtruj_dolnoprzepustowo", &filtruj_dolnoprzepustowo,
          "Filtracja dolnoprzepustowa (1D)", py::arg("widmo"), py::arg("prog"));

    m.def("znajdz_piki", &znajdz_piki,
          "Wykrywanie pikow w sygnale", py::arg("sygnal"), py::arg("prog"), py::arg("min_odleglosc"));

      m.def("sygnal_1d_na_2d", &sygnal_1d_na_2d, "Zamiana 1D na 2D");
      
    m.def("filtruj_2d_srednia", &filtruj_2d_srednia, "Filtracja 2D - średnia 3x3");

}
