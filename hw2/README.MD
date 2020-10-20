# Домашнее задание 2

### 1) Реализовать на языке C/C++ классические операции перемножения квадратных матриц и умножения матрицы на вектор (3 балла) 

Реализовано, для запуска тестов $make test

### 2) Разделить программу на несколько модулей и провести сборку через статическую линковку (2 балла)

Скрипт статической линковки - linker.sh, скомпилированный файл multiplier_static.   
Команда для сборки: $bash linker.sh
### 3) Подготовьте две сборки с флагами -g и  -O3 и измерьте времена выполнения операций с N = 512, 1024..., 4096 (3 бала)


#### Дебаг:     
$make EXECUTABLE=multiplier_g LDFLAGS=-g    
Время работы:   
The time for multiple 512X512 matrix: 4115 ms
The time for multiple 1024X1024 matrix: 66275 ms
The time for multiple 2048X2048 matrix: 1018655 ms


#### 03-оптимизация:   
$make EXECUTABLE=multiplier_O3 OPTIMIZATION=-O3   
Время работы:   
The time for multiple 512X512 matrix: 315 ms
The time for multiple 1024X1024 matrix: 6793 ms
The time for multiple 2048X2048 matrix: 107016 ms
The time for multiple 4096X4096 matrix: 921522 ms


### 4) Измерить времена выполнения программ в виртуальной машине, реальной ОС и (опционально) в докере (3 балла + 0.5 балла за докер)
