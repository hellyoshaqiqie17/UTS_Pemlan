# UTS Pemrograman Lanjut (FTM25602014)

Repository ini berisi implementasi Source code C++ untuk Tugas Proyek Ujian Tengah Semester (UTS) mata kuliah **Pemrograman Lanjut (FTM25602014)**, Program Studi S1 Teknik Robotika dan Kecerdasan Buatan (TRKB), Fakultas Teknologi Maju dan Multidisiplin (FTMM), Universitas Airlangga.

**Identitas Mahasiswa:**
- **Nama**  : Hellyos Ageng Haqiqie
- **NIM**   : 163251001
- **Kelas** : RK-A1 & RK-A2
- **Dosen Pengampu** : Rodik Wahyu Indrawan, M.Tr.T. / Ali Ikhsanul Qauli, Ph.D.
- **Topik** : *Class, Object, Method, Enkapsulasi, Overloading, Overriding*

---

## Daftar Soal dan Penerapan Konsep PBO

### 1. Soal 1: Sistem Informasi Perpustakaan Umum (`soal1.cpp`)
Simulasi sistem perpustakaan umum berbasis PBO lengkap dengan pengelolaan buku, staf pegawai, member, peminjaman, dan pengembalian.
- **Class & Object**: `Buku`, `Orang` (Base class), `Pegawai` (Derived), `Member` (Derived), `TransaksiPeminjaman`, `Perpustakaan`.
- **Enkapsulasi**: Seluruh atribut berpenentu akses `private` dan diakses melalui *getter* serta *setter* tervalidasi.
- **Overloading**: 
  - `pinjamBuku(idMember, idBuku, tglPinjam)`
  - `pinjamBuku(idMember, idBuku, tglPinjam, durasiHari, diskonKhusus)`
  - `cetakLaporan()` dan `cetakLaporan(idMember)`
- **Overriding**:
  - `virtual double hitungBiayaLayanan(double tarifDasar)` pada `Orang`, di-*override* oleh `Pegawai` (biaya Rp. 0) dan `Member` (pemotongan kuota voucher gratis *Free Pinjam*).
- **Logika Level Member**:
  - **Level 1**: Pinjam 3x $\rightarrow$ Bonus 1x Free Pinjam.
  - **Level 2**: Capaian Level 1 sebanyak 3x $\rightarrow$ Bonus 3x Free Pinjam.
  - **Level 3**: Capaian Level 2 sebanyak 3x $\rightarrow$ Bonus 5x Free Pinjam.
- **Tarif Peminjaman**: Rp. 1000 per buku.

### 2. Soal 2: TRKB Ride-Hailing App (`soal2.cpp`)
Simulasi aplikasi transportasi daring dengan entitas pengguna, pengemudi, kendaraan, dan order perjalanan.
- **Class Utama**: `Pengguna`, `Driver`, `Kendaraan`, `Pesanan`, `TRKBRideHailingApp`.
- **Enkapsulasi**: Atribut `private` dengan kendali mutator dan aksesor.
- **Overloading**:
  - `buatPesanan(idPengguna, idDriver, jarak)`
  - `buatPesanan(idPengguna, idDriver, jarak, diskonPromo)`
- **Overriding**:
  - `PremiumDriver` mewarisi `Driver` dan meng-*override* method `hitungTarif(jarak)` dengan menaikkan tarif sebesar +20% (fasilitas premium).
- **Sistem Loyalitas Pengguna**:
  - *Bronze*: Perjalanan $\ge 3\times$.
  - *Silver*: Perjalanan $\ge 5\times$.
  - *Gold*: Perjalanan $\ge 10\times$ $\rightarrow$ Mendapatkan diskon 20% otomatis pada setiap pemesanan.

### 3. Soal 3: Simulasi Robot Differential Drive (`soal3.cpp`)
Simulasi kinematika robot beroda bergerak (*differential drive mobile robot*) di bidang 2D dengan multi-input user.
- **Class & Hirarki**:
  - Base class `Robot` (metode murni virtual `update(dt)`, `tampilkanPosisi()`, `resetPosisi()`).
  - Derived class `DifferentialDriveRobot` meng-*override* seluruh metode virtual.
- **Model Kinematika**:
  $$\begin{aligned}
    v &= \frac{r}{2}(\omega_R + \omega_L), \quad \omega = \frac{r}{L}(\omega_R - \omega_L) \\
    v_x &= v \cos(\theta), \quad v_y = v \sin(\theta) \\
    \Delta x &= v_x \Delta t, \quad \Delta y = v_y \Delta t, \quad \Delta \theta = \omega \Delta t \\
    x_{baru} &= x_{lama} + \Delta x, \quad y_{baru} = y_{lama} + \Delta y, \quad \theta_{baru} = \theta_{lama} + \Delta \theta
  \end{aligned}$$
- **Multi-Input User**: Perintah `maju`, `mundur`, `kiri`, `kanan`, `stop`, dan `selesai`.
- **Kontrol Waktu**: Setiap aksi berjalan selama 5 detik dengan $\Delta t = 0.1\text{ s}$ (50 langkah), posisi $(x, y, \theta)$ dilaporkan setiap interval 1 detik.

---

## Petunjuk Kompilasi

Kompilasi seluruh program C++ dapat dilakukan menggunakan kompiler `g++` (mendukung C++17/C++20):

```bash
# Kompilasi Soal 1
g++ -std=c++17 -Wall -Wextra -O2 soal1.cpp -o soal1.exe

# Kompilasi Soal 2
g++ -std=c++17 -Wall -Wextra -O2 soal2.cpp -o soal2.exe

# Kompilasi Soal 3
g++ -std=c++17 -Wall -Wextra -O2 soal3.cpp -o soal3.exe
```

Untuk menjalankan simulasi terotomatisasi secara cepat:
```bash
# Eksekusi Soal 1
.\soal1.exe

# Eksekusi Soal 2
.\soal2.exe

# Eksekusi Soal 3
.\soal3.exe
```

Setiap program menyediakan 2 mode:
1. **Mode 1**: Simulasi otomatis menyeluruh yang menguji semua skenario pengujian dan aturan bisnis sesuai soal.
2. **Mode 2**: Mode menu interaktif yang dapat menerima masukan manual langsung dari pengguna secara bebas hingga selesai.

---

## Struktur Direktori

```
UTS/
├── images/
│   ├── logo_unair.png
│   ├── trajectory_robot.png
│   ├── uml_soal1.png
│   ├── uml_soal2.png
│   └── uml_soal3.png
├── output/
│   ├── output_soal1.txt
│   ├── output_soal2.txt
│   └── output_soal3.txt
├── generate_diagrams.py
├── run_tests.py
├── references.bib
├── soal1.cpp
├── soal2.cpp
├── soal3.cpp
├── .gitignore
└── README.md
```
