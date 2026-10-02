/**
 * ============================================================================
 * Program     : Sistem Transportasi Online (TRKB Ride-Hailing App) - Soal 2
 * Mata Kuliah : Pemrograman Lanjut (FTM25602014)
 * Topik       : Class, Object, Method, Enkapsulasi, Overloading, Overriding
 * Nama        : Hellyos Ageng Haqiqie
 * NIM         : 163251001
 * Prodi       : Teknik Robotika dan Kecerdasan Buatan (TRKB)
 * Fakultas    : Fakultas Teknologi Maju dan Multidisiplin (FTMM)
 * Universitas : Universitas Airlangga
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <memory>
#include <algorithm>

using namespace std;

// ============================================================================
// 1. CLASS KENDARAAN (Enkapsulasi)
// Atribut: plat_nomor, merk, tahun
// ============================================================================
class Kendaraan {
private:
    string m_platNomor;
    string m_merk;
    int m_tahun;

public:
    Kendaraan() : m_platNomor(""), m_merk(""), m_tahun(2020) {}
    Kendaraan(const string& plat, const string& merk, int tahun)
        : m_platNomor(plat), m_merk(merk), m_tahun(tahun) {}

    // Getter dan Setter
    string getPlatNomor() const { return m_platNomor; }
    void setPlatNomor(const string& plat) { if (!plat.empty()) m_platNomor = plat; }

    string getMerk() const { return m_merk; }
    void setMerk(const string& merk) { if (!merk.empty()) m_merk = merk; }

    int getTahun() const { return m_tahun; }
    void setTahun(int tahun) { if (tahun > 1990) m_tahun = tahun; }

    void tampilkanInfo() const {
        cout << m_merk << " (" << m_platNomor << ", " << m_tahun << ")";
    }
};

// ============================================================================
// 2. CLASS PENGGUNA (Enkapsulasi & Status Loyalitas)
// Atribut: id_pengguna, nama
// ============================================================================
class Pengguna {
private:
    string m_idPengguna;
    string m_nama;
    int m_jumlahPerjalanan;

public:
    Pengguna() : m_idPengguna(""), m_nama(""), m_jumlahPerjalanan(0) {}
    Pengguna(const string& id, const string& nama)
        : m_idPengguna(id), m_nama(nama), m_jumlahPerjalanan(0) {}

    // Getter dan Setter
    string getIdPengguna() const { return m_idPengguna; }
    void setIdPengguna(const string& id) { if (!id.empty()) m_idPengguna = id; }

    string getNama() const { return m_nama; }
    void setNama(const string& nama) { if (!nama.empty()) m_nama = nama; }

    int getJumlahPerjalanan() const { return m_jumlahPerjalanan; }
    void setJumlahPerjalanan(int jml) { if (jml >= 0) m_jumlahPerjalanan = jml; }

    void tambahPerjalanan() { m_jumlahPerjalanan++; }

    /**
     * Penentuan Status Loyalitas Pengguna:
     * - Bronze: >= 3x perjalanan
     * - Silver: >= 5x perjalanan
     * - Gold  : >= 10x perjalanan -> Mendapatkan potongan 20% biaya otomatis
     */
    string getStatusLoyalitas() const {
        if (m_jumlahPerjalanan >= 10) return "Gold";
        if (m_jumlahPerjalanan >= 5)  return "Silver";
        if (m_jumlahPerjalanan >= 3)  return "Bronze";
        return "Reguler";
    }

    // Diskon otomatis loyalty jika Gold (20% = 0.20)
    double getDiskonLoyalitas() const {
        if (m_jumlahPerjalanan >= 10) {
            return 0.20; // Diskon 20%
        }
        return 0.0;
    }

    void tampilkanInfo() const {
        cout << "| " << left << setw(12) << m_idPengguna 
             << "| " << setw(22) << m_nama 
             << "| " << setw(18) << m_jumlahPerjalanan 
             << "| " << setw(12) << getStatusLoyalitas() << " |\n";
    }
};

// ============================================================================
// 3. CLASS DRIVER (Enkapsulasi & Overriding Target)
// Atribut: id_driver, nama_driver, tipe_kendaraan, tarif_per_km
// ============================================================================
class Driver {
protected:
    string m_idDriver;
    string m_namaDriver;
    string m_tipeKendaraan; // "Motor" / "Mobil"
    double m_tarifPerKm;
    Kendaraan m_kendaraan;

public:
    Driver() 
        : m_idDriver(""), m_namaDriver(""), m_tipeKendaraan("Motor"), 
          m_tarifPerKm(3000.0) {}

    Driver(const string& id, const string& nama, const string& tipe, double tarif = 3000.0)
        : m_idDriver(id), m_namaDriver(nama), m_tipeKendaraan(tipe), 
          m_tarifPerKm(tarif) {}

    virtual ~Driver() = default;

    // Getter dan Setter
    string getIdDriver() const { return m_idDriver; }
    void setIdDriver(const string& id) { if (!id.empty()) m_idDriver = id; }

    string getNamaDriver() const { return m_namaDriver; }
    void setNamaDriver(const string& nama) { if (!nama.empty()) m_namaDriver = nama; }

    string getTipeKendaraan() const { return m_tipeKendaraan; }
    void setTipeKendaraan(const string& tipe) { if (!tipe.empty()) m_tipeKendaraan = tipe; }

    double getTarifPerKm() const { return m_tarifPerKm; }
    void setTarifPerKm(double tarif) { if (tarif > 0) m_tarifPerKm = tarif; }

    Kendaraan getKendaraan() const { return m_kendaraan; }
    void setKendaraan(const Kendaraan& k) { m_kendaraan = k; }

    // Method virtual untuk di-override oleh PremiumDriver
    virtual double hitungTarif(double jarakKm) const {
        return jarakKm * m_tarifPerKm;
    }

    virtual string getKategoriLayanan() const {
        return "Standar";
    }

    virtual void tampilkanProfil() const {
        cout << "| " << left << setw(10) << m_idDriver 
             << "| " << setw(22) << m_namaDriver 
             << "| " << setw(15) << m_tipeKendaraan 
             << "| " << setw(12) << getKategoriLayanan() 
             << "| Rp. " << right << setw(8) << fixed << setprecision(0) << m_tarifPerKm << "/km |\n";
    }
};

// ============================================================================
// 4. CLASS TURUNAN PREMIUM DRIVER (Inheritance & Overriding)
// Meng-override method hitungTarif(): tarif normal + 20%
// ============================================================================
class PremiumDriver : public Driver {
private:
    double m_bonusFasilitas; // Biaya layanan premium tambahan (20%)

public:
    PremiumDriver(const string& id, const string& nama, const string& tipe, double tarif = 4500.0)
        : Driver(id, nama, tipe, tarif), m_bonusFasilitas(0.20) {}

    // Overriding method hitungTarif()
    double hitungTarif(double jarakKm) const override {
        double tarifDasar = Driver::hitungTarif(jarakKm);
        double tarifPremium = tarifDasar * (1.0 + m_bonusFasilitas); // Tarif normal + 20%
        return tarifPremium;
    }

    string getKategoriLayanan() const override {
        return "PREMIUM (+20%)";
    }

    void tampilkanProfil() const override {
        Driver::tampilkanProfil();
    }
};

// ============================================================================
// 5. CLASS PESANAN (Enkapsulasi)
// Atribut: id_pesanan, id_pengguna, id_driver, jarak_tempuh, biaya
// ============================================================================
class Pesanan {
private:
    string m_idPesanan;
    string m_idPengguna;
    string m_idDriver;
    double m_jarakTempuh;
    double m_biaya;

public:
    Pesanan() 
        : m_idPesanan(""), m_idPengguna(""), m_idDriver(""), 
          m_jarakTempuh(0.0), m_biaya(0.0) {}

    Pesanan(const string& idPesanan, const string& idPengguna, const string& idDriver,
            double jarak, double biaya)
        : m_idPesanan(idPesanan), m_idPengguna(idPengguna), m_idDriver(idDriver),
          m_jarakTempuh(jarak), m_biaya(biaya) {}

    // Getter dan Setter
    string getIdPesanan() const { return m_idPesanan; }
    void setIdPesanan(const string& id) { if (!id.empty()) m_idPesanan = id; }

    string getIdPengguna() const { return m_idPengguna; }
    void setIdPengguna(const string& id) { if (!id.empty()) m_idPengguna = id; }

    string getIdDriver() const { return m_idDriver; }
    void setIdDriver(const string& id) { if (!id.empty()) m_idDriver = id; }

    double getJarakTempuh() const { return m_jarakTempuh; }
    void setJarakTempuh(double jarak) { if (jarak >= 0) m_jarakTempuh = jarak; }

    double getBiaya() const { return m_biaya; }
    void setBiaya(double biaya) { if (biaya >= 0) m_biaya = biaya; }

    void tampilkanInfo() const {
        cout << "| " << left << setw(12) << m_idPesanan 
             << "| " << setw(14) << m_idPengguna 
             << "| " << setw(12) << m_idDriver 
             << "| " << right << setw(8) << fixed << setprecision(1) << m_jarakTempuh << " km " 
             << "| Rp. " << setw(10) << fixed << setprecision(0) << m_biaya << " |\n";
    }
};

// ============================================================================
// 6. CLASS APLIKASI TRANSPORTASI (TRKBRideHailingApp)
// Mengatur registrasi, pembuatan pesanan (Overloading), dan pelaporan
// ============================================================================
class TRKBRideHailingApp {
private:
    vector<Pengguna> m_daftarPengguna;
    vector<shared_ptr<Driver>> m_daftarDriver;
    vector<Pesanan> m_daftarPesanan;
    double m_totalPendapatan;

public:
    TRKBRideHailingApp() : m_totalPendapatan(0.0) {}

    // 2.a Form Registrasi Pengguna
    void registrasiPengguna(const string& id, const string& nama) {
        for (const auto& u : m_daftarPengguna) {
            if (u.getIdPengguna() == id) {
                cout << "[ERROR] Pengguna dengan ID " << id << " sudah ada!\n";
                return;
            }
        }
        m_daftarPengguna.emplace_back(id, nama);
        cout << "[SUKSES] Pengguna \"" << nama << "\" (" << id << ") berhasil didaftarkan.\n";
    }

    // 2.b Form Registrasi Driver (Reguler & Premium)
    void registrasiDriver(const string& id, const string& nama, const string& tipeKendaraan, 
                          double tarifPerKm = 3000.0, bool isPremium = false) {
        for (const auto& d : m_daftarDriver) {
            if (d->getIdDriver() == id) {
                cout << "[ERROR] Driver dengan ID " << id << " sudah terdaftar!\n";
                return;
            }
        }

        if (isPremium) {
            m_daftarDriver.push_back(make_shared<PremiumDriver>(id, nama, tipeKendaraan, tarifPerKm));
            cout << "[SUKSES] Driver Premium \"" << nama << "\" (" << id << ") berhasil didaftarkan.\n";
        } else {
            m_daftarDriver.push_back(make_shared<Driver>(id, nama, tipeKendaraan, tarifPerKm));
            cout << "[SUKSES] Driver Reguler \"" << nama << "\" (" << id << ") berhasil didaftarkan.\n";
        }
    }

    // Helper Finders
    Pengguna* cariPengguna(const string& id) {
        for (auto& u : m_daftarPengguna) {
            if (u.getIdPengguna() == id) return &u;
        }
        return nullptr;
    }

    shared_ptr<Driver> cariDriver(const string& id) {
        for (auto& d : m_daftarDriver) {
            if (d->getIdDriver() == id) return d;
        }
        return nullptr;
    }

    // ========================================================================
    // 4. OVERLOADING METHOD buatPesanan()
    // Versi 1: parameter (id_pengguna, id_driver, jarak_tempuh)
    // Versi 2: parameter (id_pengguna, id_driver, jarak_tempuh, diskon)
    // ========================================================================
    bool buatPesanan(const string& idPengguna, const string& idDriver, double jarakTempuh) {
        return buatPesanan(idPengguna, idDriver, jarakTempuh, 0.0);
    }

    bool buatPesanan(const string& idPengguna, const string& idDriver, double jarakTempuh, double diskonPromo) {
        Pengguna* pengguna = cariPengguna(idPengguna);
        if (!pengguna) {
            cout << "[ERROR] Pengguna ID " << idPengguna << " tidak ditemukan!\n";
            return false;
        }

        auto driver = cariDriver(idDriver);
        if (!driver) {
            cout << "[ERROR] Driver ID " << idDriver << " tidak ditemukan!\n";
            return false;
        }

        if (jarakTempuh <= 0) {
            cout << "[ERROR] Jarak tempuh harus lebih besar dari 0 km!\n";
            return false;
        }

        // 5. Overriding hitungTarif() dipanggil secara polimorfis
        double tarifKotor = driver->hitungTarif(jarakTempuh);

        // Diskon Loyalty Pengguna
        double diskonLoyalitas = pengguna->getDiskonLoyalitas(); // 20% jika Gold
        double totalDiskonPersen = diskonLoyalitas + diskonPromo;
        if (totalDiskonPersen > 0.9) totalDiskonPersen = 0.9; // Maksimal diskon 90%

        double nominalPotongan = tarifKotor * totalDiskonPersen;
        double biayaBersih = tarifKotor - nominalPotongan;

        // Catat perjalanan ke pengguna
        pengguna->tambahPerjalanan();

        // Buat objek pesanan
        string idPesanan = "ORD-" + to_string(m_daftarPesanan.size() + 1001);
        m_daftarPesanan.emplace_back(idPesanan, idPengguna, idDriver, jarakTempuh, biayaBersih);

        m_totalPendapatan += biayaBersih;

        cout << "\n------------------------------------------------------------\n";
        cout << "[PEMESANAN SUKSES] ID Pesanan: " << idPesanan << "\n";
        cout << "  Pengguna        : " << pengguna->getNama() << " (" << idPengguna << ")\n";
        cout << "  Driver          : " << driver->getNamaDriver() << " [" << driver->getKategoriLayanan() << "]\n";
        cout << "  Jarak Tempuh    : " << fixed << setprecision(1) << jarakTempuh << " km\n";
        cout << "  Tarif Awal      : Rp. " << fixed << setprecision(0) << tarifKotor << "\n";
        if (diskonLoyalitas > 0) {
            cout << "  Diskon Loyalty  : Potongan Gold (20%)\n";
        }
        if (diskonPromo > 0) {
            cout << "  Diskon Promo    : Potongan Tambahan (" << diskonPromo * 100 << "%)\n";
        }
        cout << "  Total Biaya Akhir: Rp. " << fixed << setprecision(0) << biayaBersih << "\n";
        cout << "  Status Pengguna : " << pengguna->getStatusLoyalitas() 
             << " (" << pengguna->getJumlahPerjalanan() << "x trip)\n";
        cout << "------------------------------------------------------------\n";

        return true;
    }

    // ========================================================================
    // 6. REPORT AKTIVITAS APLIKASI
    // ========================================================================
    void tampilkanLaporanAktivitas() const {
        cout << "\n========================================================================\n";
        cout << "                REPORT AKTIVITAS TRKB RIDE-HAILING APP                  \n";
        cout << "========================================================================\n";

        // a. Daftar Seluruh Pemesanan (id_pesanan, id_pengguna, id_driver, biaya)
        cout << "\n--- (a) DAFTAR SELURUH PEMESANAN ---\n";
        cout << "+-------------+---------------+-------------+--------------+----------------+\n";
        cout << "| ID Pesanan  | ID Pengguna   | ID Driver   | Jarak (km)   | Biaya Final    |\n";
        cout << "+-------------+---------------+-------------+--------------+----------------+\n";
        if (m_daftarPesanan.empty()) {
            cout << "|                        Belum ada pemesanan tercatat.                         |\n";
        } else {
            for (const auto& ord : m_daftarPesanan) {
                ord.tampilkanInfo();
            }
        }
        cout << "+-------------+---------------+-------------+--------------+----------------+\n";

        // b. Total Pendapatan Perusahaan
        cout << "\n--- (b) TOTAL PENDAPATAN PERUSAHAAN ---\n";
        cout << "  >> Total Pendapatan TRKB App: Rp. " 
             << fixed << setprecision(0) << m_totalPendapatan << "\n";

        // c. Status Loyalitas Pengguna
        cout << "\n--- (c) STATUS LOYALITAS PENGGUNA ---\n";
        cout << "+-------------+-----------------------+-------------------+--------------+\n";
        cout << "| ID Pengguna | Nama Pengguna         | Total Perjalanan  | Tier Status  |\n";
        cout << "+-------------+-----------------------+-------------------+--------------+\n";
        for (const auto& u : m_daftarPengguna) {
            u.tampilkanInfo();
        }
        cout << "+-------------+-----------------------+-------------------+--------------+\n";
        cout << "  Keterangan Tier: Bronze (>=3x), Silver (>=5x), Gold (>=10x -> Diskon 20%)\n";
        cout << "========================================================================\n\n";
    }

    void tampilkanSemuaDriver() const {
        cout << "\n=== DAFTAR DRIVER TERDAFTAR ===\n";
        cout << "+-----------+-----------------------+----------------+---------------+------------------+\n";
        cout << "| ID Driver | Nama Driver           | Kendaraan      | Kategori      | Tarif Dasar      |\n";
        cout << "+-----------+-----------------------+----------------+---------------+------------------+\n";
        for (const auto& d : m_daftarDriver) {
            d->tampilkanProfil();
        }
        cout << "+-----------+-----------------------+----------------+---------------+------------------+\n";
    }
};

// ============================================================================
// SIMULASI OTOMATIS & INTEGRASI DEMO
// ============================================================================
void jalankanSimulasiOtomatis(TRKBRideHailingApp& app) {
    cout << "\n========================================================\n";
    cout << "     MENJALANKAN SIMULASI TRKB RIDE-HAILING APP         \n";
    cout << "========================================================\n\n";

    // 1. Registrasi Pengguna
    cout << ">>> 1. FORM REGISTRASI PENGGUNA\n";
    app.registrasiPengguna("USR01", "Hellyos Ageng");
    app.registrasiPengguna("USR02", "Ahmad Fauzi");
    app.registrasiPengguna("USR03", "Dewi Sartika");

    // 2. Registrasi Driver (Reguler & Premium)
    cout << "\n>>> 2. FORM REGISTRASI DRIVER\n";
    // Driver Reguler
    app.registrasiDriver("DRV01", "Bambang Pamungkas", "Mobil", 3500.0, false);
    app.registrasiDriver("DRV02", "Joko Motor", "Motor", 2500.0, false);
    // Driver Premium (Menguji Overriding hitungTarif())
    app.registrasiDriver("DRV03", "Hendrawan VIP", "Mobil Alphard", 5000.0, true);

    app.tampilkanSemuaDriver();

    // 3. Simulasi Pemesanan Transportasi
    cout << "\n>>> 3. PEMESANAN DENGAN OVERLOADING & OVERRIDING\n";

    // Versi 1: buatPesanan tanpa diskon promo (Reguler Driver)
    cout << "\n[Kasus A] Pemesanan Reguler (Driver Standar - DRV01):\n";
    app.buatPesanan("USR01", "DRV01", 10.0); // 10 km * 3500 = 35.000

    // Versi 2: buatPesanan dengan Driver Premium (Overriding: tarif normal + 20%)
    cout << "\n[Kasus B] Pemesanan dengan Driver Premium (Overriding Tarif +20% - DRV03):\n";
    app.buatPesanan("USR01", "DRV03", 10.0); // 10 km * 5000 = 50.000 + 20% = 60.000

    // Versi 3: buatPesanan dengan Diskon Promo (Overloading versi kedua)
    cout << "\n[Kasus C] Pemesanan dengan Kode Promo Diskon 15% (Overloading):\n";
    app.buatPesanan("USR02", "DRV02", 8.0, 0.15); // 8 km * 2500 = 20.000 - 15% = 17.000

    // 4. Pengujian Status Loyalitas (Bronze, Silver, Gold)
    cout << "\n>>> 4. PENGUJIAN STATUS LOYALITAS PENGGUNA USR01 MENUJU GOLD\n";
    cout << "[INFO] Menambah trip untuk USR01 hingga menyelesaikan 10x perjalanan...\n";
    for (int i = 3; i <= 10; ++i) {
        app.buatPesanan("USR01", "DRV02", 4.0); // Trip ke-3 s.d 10
    }

    cout << "\n[Kasus D] Pemesanan ke-11 untuk USR01 (Pengguna Berstatus GOLD >= 10x Perjalanan -> Potongan 20% Otomatis!):\n";
    app.buatPesanan("USR01", "DRV01", 10.0); // 10 km * 3500 = 35000 -> diskon 20% = 28000

    // 5. Cetak Laporan Aktivitas
    app.tampilkanLaporanAktivitas();
}

int main() {
    TRKBRideHailingApp app;
    int pilihan = 0;

    cout << "============================================================\n";
    cout << "   TRKB RIDE-HAILING APP (C++ PEMROGRAMAN LANJUT) - SOAL 2  \n";
    cout << "   Nama : Hellyos Ageng Haqiqie (163251001)                 \n";
    cout << "   Prodi: Teknik Robotika dan Kecerdasan Buatan (FTMM)      \n";
    cout << "============================================================\n";
    cout << "Pilih mode eksekusi:\n";
    cout << "1. Jalankan Simulasi Otomatis Lengkap\n";
    cout << "2. Masuk ke Menu Interaktif Manual\n";
    cout << "Pilihan Anda (1/2): ";

    if (!(cin >> pilihan)) {
        pilihan = 1;
    }

    if (pilihan == 1) {
        jalankanSimulasiOtomatis(app);
    } else {
        bool running = true;
        while (running) {
            cout << "\n--- MENU APLIKASI TRANSPORTASI ONLINE ---\n";
            cout << "1. Form Registrasi Pengguna\n";
            cout << "2. Form Registrasi Driver (Reguler / Premium)\n";
            cout << "3. Form Pemesanan Transportasi (Standar)\n";
            cout << "4. Form Pemesanan Transportasi (Dengan Diskon Promo)\n";
            cout << "5. Tampilkan Daftar Driver\n";
            cout << "6. Tampilkan Laporan Aktivitas Aplikasi\n";
            cout << "7. Keluar\n";
            cout << "Pilih menu [1-7]: ";
            int menu;
            if (!(cin >> menu)) break;

            if (menu == 1) {
                string id, nama;
                cout << "Input ID Pengguna : "; cin >> id;
                cin.ignore();
                cout << "Input Nama        : "; getline(cin, nama);
                app.registrasiPengguna(id, nama);
            } else if (menu == 2) {
                string id, nama, tipe;
                double tarif;
                int isPrem;
                cout << "Input ID Driver       : "; cin >> id;
                cin.ignore();
                cout << "Input Nama Driver     : "; getline(cin, nama);
                cout << "Input Tipe Kendaraan  : "; cin >> tipe;
                cout << "Input Tarif per km    : "; cin >> tarif;
                cout << "Apakah Driver Premium? (1=Ya, 0=Tidak): "; cin >> isPrem;
                app.registrasiDriver(id, nama, tipe, tarif, isPrem == 1);
            } else if (menu == 3) {
                string idU, idD;
                double jarak;
                cout << "Input ID Pengguna : "; cin >> idU;
                cout << "Input ID Driver   : "; cin >> idD;
                cout << "Input Jarak (km)  : "; cin >> jarak;
                app.buatPesanan(idU, idD, jarak);
            } else if (menu == 4) {
                string idU, idD;
                double jarak, diskonPersen;
                cout << "Input ID Pengguna    : "; cin >> idU;
                cout << "Input ID Driver      : "; cin >> idD;
                cout << "Input Jarak (km)     : "; cin >> jarak;
                cout << "Input Diskon (0-100%): "; cin >> diskonPersen;
                app.buatPesanan(idU, idD, jarak, diskonPersen / 100.0);
            } else if (menu == 5) {
                app.tampilkanSemuaDriver();
            } else if (menu == 6) {
                app.tampilkanLaporanAktivitas();
            } else if (menu == 7) {
                cout << "Terima kasih telah menggunakan TRKB Ride-Hailing App.\n";
                running = false;
            } else {
                cout << "Pilihan tidak valid!\n";
            }
        }
    }

    return 0;
}
