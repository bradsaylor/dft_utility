import numpy as np

raw = np.fromfile("../test_output.bin", dtype=np.float64)
complex_data = raw[::2] + 1j * raw[1::2]
