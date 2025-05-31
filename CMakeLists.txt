cmake_minimum_required(VERSION 3.14)
project(sygnaly)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(
  matplotplusplus
  GIT_REPOSITORY https://github.com/alandefreitas/matplotplusplus.git
  GIT_TAG        master
)
FetchContent_MakeAvailable(matplotplusplus)

add_executable(wizualizacja main.cpp przetwarzanie_sygnalu.cpp piki.cpp)

target_link_libraries(wizualizacja matplot)

# Pybind11 support
FetchContent_Declare(
  pybind11
  GIT_REPOSITORY https://github.com/pybind/pybind11.git
  GIT_TAG v2.11.1  # lub inna stabilna wersja
)
FetchContent_MakeAvailable(pybind11)

pybind11_add_module(sygnaly bindings.cpp przetwarzanie_sygnalu.cpp piki.cpp)
target_link_libraries(sygnaly PRIVATE matplot)