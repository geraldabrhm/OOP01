# Tugas Besar 1 IF2210 2021/2022
### Penerapan Konsep OOP dalam Sistem Inventory dan Crafting Minecraft

Repository ini dibuat dalam rangka memenuhi Tugas Besar 1 mata kuliah IF2210 Pemrograman Berorientasi Objek Semester 4 Tahun 2021/2022

## Table of Contents

- [Deskripsi Program](#deskripsi-program)
- [Struktur Repository](#struktur-repository)
- [Requirement](#requirements)
- [How to Use](#how-to-use)
- [Anggota Kelompok](#anggota-kelompok)

## Deskripsi Program

Repository ini berisi penerapan konsep OOP dalam sistem inventory dan crafting. User dapat melakukan beberapa hal melalui `command` seperti crafting (membuat item baru) apabila jenis dan pola item sesuai dengan resep yang ada, mengelola item di inventory, dan seterusnya.

## Struktur Repository

Repository ini terdiri dari directory yaitu sebagai berikut

1. **`config`**, berisi semua config files (items dan recipes)
2. **`src`**, berisi source code program yang terdiri dari bahasa C++
3. **`tests`**, berisi semua test files (input dan answer)

## Requirements

Untuk menjalankan program ini, minimal dibutuhkan C++ compiler seperti GCC

## How to Use

### Menjalankan program utama
Berikut adalah langkah yang dapat diikuti untuk menjalankan program ini:

1. Lakukan cloning repository git clone `https://github.com/geraldabrhm/OOP01.git`
2. Jalankan `cd src`
2. Lakukan compile dengan menjalankan `g++ -std=c++17 .\main.cpp .\MainKrap.cpp .\Item\Item.cpp .\Exception\Exception.cpp .\Boxes\Boxes.cpp .\Boxes\Inventory.cpp .\Boxes\Recipe.cpp .\Boxes\Crafting.cpp -o main.exe  -lstdc++fs`
3. Jalankan `./main.exe`

### Menjalankan dengan Makefile
Makefile digunakan untuk compiling and testing. Untuk menjalankan makefile, pastikan user menggunakan Linux dengan C++17, atau WSL apabila menggunakan Windows
```
sudo apt-get install make g++
make manual
cd src
./main.exe

```

### Jika terjadi masalah dengan filesystem
Masalah ini kemungkinan besar terjadi untuk pengguna Windows.  
Lakukan instalasi GCC terbaru dengan referensi link video berikut ini:.  
[LINK](https://www.youtube.com/watch?v=aXF4A5UeSeM&)

## Anggota Kelompok

- 13520051 Flavia Beatrix Leoni A. S.	
- 13520099 Vincent Prasetiya Atmadja
- 13520108 Muhammad Rakha Athaya
- 13520138 Gerald Abraham Sianturi
- 13520159 Atabik Muhammad Azfa Shofi	
