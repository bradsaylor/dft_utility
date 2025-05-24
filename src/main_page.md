# DFT Utility Documentation                         {#mainpage}

#### Purpose

#### Method

#### Usage

``` 
./dft [../path/to/input/file] [output filename] --option value ...
Options:
  --output-mode
      csv:    Output in CSV format
      txt:    Output in ASCII text
      bin:    Output in binary format
  --alg-mode
      direct: Calculate DFT directly
      fft:    Calculate FFT using decimation in time algorithm
      ifft:   Calculate IFFT using decimation in time algroithm
      gtz:    Calculate DFT using Goertzel algorithm
```
