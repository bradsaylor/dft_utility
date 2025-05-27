import os
import numpy as np
import matplotlib
import matplotlib.pyplot as plt
matplotlib.use("TkAgg")

def plot_all_bin_files(directory):
    plt.figure(figsize=(12, 6))

    for filename in os.listdir(directory):
        if filename.endswith(".bin"):
            filepath = os.path.join(directory, filename)

            # Read binary data as complex128 (assuming interleaved real/imag pairs)
            data = np.fromfile(filepath, dtype=np.complex128)

            # Plot magnitude spectrum
            plt.plot(np.abs(data), label=filename)

    plt.title("Overlay of DFT Magnitudes from .bin Files")
    plt.xlabel("Frequency Bin")
    plt.ylabel("Magnitude")
    plt.legend()
    plt.grid(True)
    plt.tight_layout()
    plt.show()

# Example usage
output_dir = "./output/"
plot_all_bin_files(output_dir)

