
## Kurulumlar

> sudo apt-get install gcc make perl  
> sudo apt-get install libopenmpi-dev openmpi-bin libomp-dev

## Çekirdek bilgilerini görmek için:

> cat /proc/cpuinfo

## Kodu Derleme

> mpicc -o <output_dosyası> <kod_dosyası>.c

## Paralel çalıştırma

> mpirun -np <çekirdek_sayısı> <output_dosyası>

## Daha fazla çekirdekte çalıştrma

> pico machine_file.txt   
> mpirun -np <çekirdek_sayısı> --machinefile machine_file.txt <output_dosyası>
