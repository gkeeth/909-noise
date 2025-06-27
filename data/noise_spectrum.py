#!/usr/bin/env -S uv run --script
# /// script
# requires-python = ">=3.13"
# dependencies = [
#     "matplotlib",
#     "numpy",
#     "scipy",
# ]
# ///


import matplotlib.pyplot as plt
import numpy as np
from scipy.signal import welch

# calculate bandwidth
# see how bandwidth changes with clock speed
# see how bandwidth changes with NPN buffer

def plot_spectrum(filename: str | None = None, noise: np.ndarray | None = None, plot_sine: bool = False) -> None:
    if filename:
        noise = np.loadtxt(filename, delimiter=",", skiprows=1).transpose()
    assert noise is not None

    noise[1] -= noise[1].mean()
    spectrum = np.abs(np.fft.rfft(noise[1]))
    T = noise[0][1] - noise[0][0]
    bins = np.fft.rfftfreq(noise[1].size, d=T)

    plt.figure()
    plt.semilogy(bins, spectrum)
    plt.title(f"Spectrum from {filename}")
    plt.xlabel("Frequency (Hz)")
    plt.ylabel("Magnitude")
    plt.xlim((-5000, 2e5))
    plt.ylim((1e-2, 1e6))
    plt.grid()

    psd = welch(noise[1], fs=1/T)
    plt.figure()
    plt.semilogy(psd[0], psd[1])
    plt.title(f"PSD from {filename}")
    plt.xlabel("Frequency (Hz)")
    plt.ylabel("PSD ($\\mathrm{V}^2 / \\mathrm{Hz}$)")
    plt.xlim((-5000, 2e5))
    plt.ylim((1e-9, 1e-3))
    plt.grid()

    # plt.figure()
    # plt.plot(noise[0], noise[1])

    if plot_sine:
        sine = noise.copy()
        f1 = 1000
        f2 = 11000
        sine[1] = 2 * np.sin(2*np.pi*f1*sine[0]) + np.sin(2*np.pi*f2*sine[0])
        sine_spec = np.abs(np.fft.rfft(sine[1]))
        plt.figure()
        # plt.plot(sine[0], sine[1])
        plt.plot(bins, sine_spec)
        plt.title(f"Sine with frequencies {f1} Hz and {f2} Hz")
        plt.xlabel("Frequency (Hz)")
        plt.ylabel("Magnitude")
        plt.xlim((0, 2e4))


def main() -> None:
    files = [
        "3v3_100ms.csv",
        "40109_100ms.csv",
        "4504_100ms.csv",
        "filter_100ms.csv",
    ]
    for f in files:
        plot_spectrum(f)
    plt.show()


if __name__ == "__main__":
    main()
