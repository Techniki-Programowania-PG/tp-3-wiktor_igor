import numpy as np
import matplotlib.pyplot as plt
import sygnaly

N = 100
f = 5.0
t0 = 0.0
t1 = 1.0
A = 1.0

sygnaly_lista = [
    ("sinusoidalny", sygnaly.generuj_sinus(N, f, t0, t1, A)),
    ("cosinusoidalny", sygnaly.generuj_cosinus(N, f, t0, t1, A)),
    ("protstokatny", sygnaly.generuj_prostokatny(N, f, t0, t1, A)),
    ("piloksztaltny", sygnaly.generuj_piloksztaltny(N, f, t0, t1, A)),
]

for nazwa, sygnal in sygnaly_lista:
    widmo = sygnaly.dft(sygnal)
    amplituda = [abs(c) for c in widmo]

    odtworzony = sygnaly.idft(widmo)
    odtworzony_real = [c.real for c in odtworzony]

    widmo_filtrowane = sygnaly.filtruj_dolnoprzepustowo(widmo, 0.1)
    odtworzony_filtrowany = sygnaly.idft(widmo_filtrowane)
    odtworzony_filtrowany_real = [c.real for c in odtworzony_filtrowany]

    piki = sygnaly.znajdz_piki(sygnal, 0.5, 10)

    plt.figure()
    plt.plot(sygnal)
    plt.title(f"Oryginalny sygnal {nazwa}")

    plt.figure()
    plt.plot(amplituda)
    plt.title(f"Widmo amplitudowe DFT - {nazwa}")

    plt.figure()
    plt.plot(odtworzony_real)
    plt.title(f"Odtworzony sygnal po IDFT - {nazwa}")

    plt.figure()
    plt.plot(odtworzony_filtrowany_real)
    plt.title(f"Po filtracji dolnoprzepustowej - {nazwa}")

    plt.figure()
    plt.plot(sygnal)
    plt.plot(piki, [sygnal[i] for i in piki], 'ro')
    plt.title(f"Sygnal z wykrytymi pikami - {nazwa}")

plt.show()

for nazwa, sygnal in sygnaly_lista:
    
    sygnal2d = sygnaly.sygnal_1d_na_2d(sygnal, 20)
    sygnal2d_filtr = sygnaly.filtruj_2d_srednia(sygnal2d)

    fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(10, 4))
    ax1.imshow(sygnal2d, aspect='auto', cmap='viridis')
    ax1.set_title("Sygnał 2D przed filtracją")

    ax2.imshow(sygnal2d_filtr, aspect='auto', cmap='viridis')
    ax2.set_title("Sygnał 2D po filtracji")
    
plt.tight_layout()
plt.show()

