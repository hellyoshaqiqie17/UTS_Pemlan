/**
 * ============================================================================
 * Program     : Sistem Informasi Perpustakaan Umum (PBO C++)
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
#include <algorithm>
#include <memory>

using namespace std;

// ============================================================================
// 1. CLASS BUKU (Enkapsulasi)
// ============================================================================
class Buku {
private:
    string m_idBuku;
    string m_namaBuku;
    bool m_isDipinjam;

public:
    // Constructor Overloading
    Buku() : m_idBuku(""), m_namaBuku(""), m_isDipinjam(false) {}

    Buku(const string& id, const string& nama) 
        : m_idBuku(id), m_namaBuku(nama), m_isDipinjam(false) {}

    // Getter dan Setter (Enkapsulasi)
    string getIdBuku() const { return m_idBuku; }
    void setIdBuku(const string& id) { 
        if (!id.empty()) m_idBuku = id; 
    }

    string getNamaBuku() const { return m_namaBuku; }
    void setNamaBuku(const string& nama) { 
        if (!nama.empty()) m_namaBuku = nama; 
    }

    bool isDipinjam() const { return m_isDipinjam; }
    void setDipinjam(bool status) { m_isDipinjam = status; }

    void tampilkanInfo() const {
        cout << "| " << left << setw(10) << m_idBuku 
             << "| " << setw(30) << m_namaBuku 
             << "| " << setw(15) << (m_isDipinjam ? "Dipinjam" : "Tersedia") << " |\n";
    }
};

// ============================================================================
// 2. BASE CLASS ORANG (Abstraksi & Polymorphism untuk Overriding)
// ============================================================================
class Orang {
protected:
    string m_id;
    string m_nama;

public:
    Orang(const string& id = "", const string& nama = "") 
        : m_id(id), m_nama(nama) {}

    virtual ~Orang() = default;

    // Getter & Setter
    string getId() const { return m_id; }
    void setId(const string& id) { if (!id.empty()) m_id = id; }

    string getNama() const { return m_nama; }
    void setNama(const string& nama) { if (!nama.empty()) m_nama = nama; }

    // Virtual Methods untuk di-Override oleh Derived Class
    virtual void tampilkanInfo() const {
        cout << "ID: " << m_id << " | Nama: " << m_nama << "\n";
    }

    virtual double hitungBiayaLayanan(double tarifDasar) {
        return tarifDasar;
    }
};

// ============================================================================
// 3. DERIVED CLASS PEGAWAI (Inheritance & Overriding)
// ============================================================================
class Pegawai : public Orang {
private:
    string m_jabatan;

public:
    Pegawai() : Orang("", ""), m_jabatan("Staff") {}
    Pegawai(const string& id, const string& nama, const string& jabatan = "Petugas Layanan")
        : Orang(id, nama), m_jabatan(jabatan) {}

    string getJabatan() const { return m_jabatan; }
    void setJabatan(const string& j) { m_jabatan = j; }

    // Overriding method tampilkanInfo
    void tampilkanInfo() const override {
        cout << "| " << left << setw(12) << m_id 
             << "| " << setw(25) << m_nama 
             << "| " << setw(20) << m_jabatan << " |\n";
    }

    // Overriding method hitungBiayaLayanan (Pegawai bebas biaya administrasi)
    double hitungBiayaLayanan(double tarifDasar) override {
        (void)tarifDasar;
        return 0.0; // Bebas biaya untuk pegawai
    }
};

// ============================================================================
// 4. DERIVED CLASS MEMBER (Inheritance, Enkapsulasi, & Overriding)
// ============================================================================
class Member : public Orang {
private:
    int m_totalPinjam;
    int m_level;
    int m_countLevel1;
    int m_countLevel2;
    int m_freePinjam;

public:
    Member() 
        : Orang("", ""), m_totalPinjam(0), m_level(0), 
          m_countLevel1(0), m_countLevel2(0), m_freePinjam(0) {}

    Member(const string& id, const string& nama)
        : Orang(id, nama), m_totalPinjam(0), m_level(0), 
          m_countLevel1(0), m_countLevel2(0), m_freePinjam(0) {}

    // Getter dan Setter
    int getTotalPinjam() const { return m_totalPinjam; }
    int getLevel() const { return m_level; }
    int getFreePinjam() const { return m_freePinjam; }

    void setFreePinjam(int fp) { 
        if (fp >= 0) m_freePinjam = fp; 
    }

    /**
     * Logika Peningkatan Status Level Member:
     * - Level 1: Telah meminjam buku 3x -> Mendapatkan Free pinjam 1x
     * - Level 2: Telah mencapai level 1 sebanyak 3x -> Mendapatkan Free pinjam 3x
     * - Level 3: Telah mencapai level 2 sebanyak 3x -> Mendapatkan Free pinjam 5x
     */
    void catatPeminjamanBaru() {
        m_totalPinjam++;

        // Setiap kelipatan 3 kali peminjaman mencapai syarat Level 1
        if (m_totalPinjam % 3 == 0) {
            m_countLevel1++;
            if (m_level < 1) m_level = 1;
            m_freePinjam += 1;
            cout << "  [BONUS] Member " << m_nama 
                 << " mencapai capaian Level 1! Mendapatkan 1x Free Pinjam.\n";

            // Jika telah mencapai Level 1 sebanyak 3 kali (total 9x pinjam)
            if (m_countLevel1 % 3 == 0) {
                m_countLevel2++;
                if (m_level < 2) m_level = 2;
                m_freePinjam += 3;
                cout << "  [BONUS SPESIAL] Member " << m_nama 
                     << " mencapai Level 2 (3x Level 1)! Mendapatkan 3x Free Pinjam.\n";

                // Jika telah mencapai Level 2 sebanyak 3 kali (total 27x pinjam)
                if (m_countLevel2 % 3 == 0) {
                    m_level = 3;
                    m_freePinjam += 5;
                    cout << "  [BONUS MAKSIMAL] Member " << m_nama 
                         << " mencapai Level 3 (3x Level 2)! Mendapatkan 5x Free Pinjam.\n";
                }
            }
        }
    }

    // Overriding method hitungBiayaLayanan
    // Jika member memiliki kuota Free Pinjam, gunakan kuota tersebut (biaya = Rp. 0)
    double hitungBiayaLayanan(double tarifDasar) override {
        if (m_freePinjam > 0) {
            m_freePinjam--;
            cout << "  [PROMO] Kuota Free Pinjam digunakan! Sisa kuota gratis: " 
                 << m_freePinjam << "\n";
            return 0.0;
        }
        return tarifDasar;
    }

    // Overriding method tampilkanInfo
    void tampilkanInfo() const override {
        cout << "| " << left << setw(10) << m_id 
             << "| " << setw(20) << m_nama 
             << "| Level " << setw(4) << m_level 
             << "| " << setw(14) << m_totalPinjam 
             << "| " << setw(13) << m_freePinjam << " |\n";
    }
};

// ============================================================================
// 5. CLASS TRANSAKSI PEMINJAMAN
// ============================================================================
class TransaksiPeminjaman {
private:
    string m_idTransaksi;
    string m_idMember;
    string m_idBuku;
    string m_tglPinjam;
    string m_tglKembali;
    double m_biaya;
    bool m_sudahKembali;

public:
    TransaksiPeminjaman(const string& idTrx, const string& idMember, const string& idBuku,
                        const string& tglPinjam, double biaya)
        : m_idTransaksi(idTrx), m_idMember(idMember), m_idBuku(idBuku),
          m_tglPinjam(tglPinjam), m_tglKembali("-"), m_biaya(biaya), m_sudahKembali(false) {}

    string getIdTransaksi() const { return m_idTransaksi; }
    string getIdMember() const { return m_idMember; }
    string getIdBuku() const { return m_idBuku; }
    string getTglPinjam() const { return m_tglPinjam; }
    string getTglKembali() const { return m_tglKembali; }
    double getBiaya() const { return m_biaya; }
    bool isSudahKembali() const { return m_sudahKembali; }

    void setKembali(const string& tglKembali) {
        m_tglKembali = tglKembali;
        m_sudahKembali = true;
    }
};

// ============================================================================
// 6. CLASS PERPUSTAKAAN (Manajer Sistem & Method Overloading)
// ============================================================================
class Perpustakaan {
private:
    vector<Buku> m_daftarBuku;
    vector<Pegawai> m_daftarPegawai;
    vector<Member> m_daftarMember;
    vector<TransaksiPeminjaman> m_riwayatPinjam;
    double m_totalPendapatan;
    const double TARIF_PINJAM_DEFAULT = 1000.0; // Biaya Rp. 1000 per buku

public:
    Perpustakaan() : m_totalPendapatan(0.0) {}

    // Form Tambah Buku
    void tambahBuku(const string& id, const string& nama) {
        for (const auto& b : m_daftarBuku) {
            if (b.getIdBuku() == id) {
                cout << "[ERROR] ID Buku " << id << " sudah terdaftar!\n";
                return;
            }
        }
        m_daftarBuku.emplace_back(id, nama);
        cout << "[SUKSES] Buku \"" << nama << "\" (" << id << ") berhasil didaftarkan.\n";
    }

    // Form Tambah Pegawai
    void tambahPegawai(const string& id, const string& nama, const string& jabatan = "Staff") {
        for (const auto& p : m_daftarPegawai) {
            if (p.getId() == id) {
                cout << "[ERROR] ID Pegawai " << id << " sudah terdaftar!\n";
                return;
            }
        }
        m_daftarPegawai.emplace_back(id, nama, jabatan);
        cout << "[SUKSES] Pegawai \"" << nama << "\" (" << id << ") berhasil didaftarkan.\n";
    }

    // Form Tambah Member
    void tambahMember(const string& id, const string& nama) {
        for (const auto& m : m_daftarMember) {
            if (m.getId() == id) {
                cout << "[ERROR] ID Member " << id << " sudah terdaftar!\n";
                return;
            }
        }
        m_daftarMember.emplace_back(id, nama);
        cout << "[SUKSES] Member \"" << nama << "\" (" << id << ") berhasil didaftarkan.\n";
    }

    // Helper Finders
    Buku* cariBuku(const string& id) {
        for (auto& b : m_daftarBuku) {
            if (b.getIdBuku() == id) return &b;
        }
        return nullptr;
    }

    Member* cariMember(const string& id) {
        for (auto& m : m_daftarMember) {
            if (m.getId() == id) return &m;
        }
        return nullptr;
    }

    // ========================================================================
    // METHOD OVERLOADING: pinjamBuku()
    // Versi 1: pinjam dengan ID_Member, ID_Buku, ID_Tanggal_Pinjam
    // Versi 2: pinjam dengan tambahan durasi dan diskon/promo khusus
    // ========================================================================
    bool pinjamBuku(const string& idMember, const string& idBuku, const string& tglPinjam) {
        return pinjamBuku(idMember, idBuku, tglPinjam, 7, 0.0); // Default durasi 7 hari
    }

    bool pinjamBuku(const string& idMember, const string& idBuku, const string& tglPinjam, 
                    int durasiHari, double diskonKhusus) {
        Member* member = cariMember(idMember);
        if (!member) {
            cout << "[ERROR] Member dengan ID " << idMember << " tidak ditemukan!\n";
            return false;
        }

        Buku* buku = cariBuku(idBuku);
        if (!buku) {
            cout << "[ERROR] Buku dengan ID " << idBuku << " tidak ditemukan!\n";
            return false;
        }

        if (buku->isDipinjam()) {
            cout << "[GAGAL] Buku \"" << buku->getNamaBuku() << "\" saat ini sedang dipinjam.\n";
            return false;
        }

        // Hitung biaya menggunakan polymorphism (Overriding hitungBiayaLayanan)
        double tarifAwal = TARIF_PINJAM_DEFAULT - diskonKhusus;
        if (tarifAwal < 0) tarifAwal = 0;
        double biayaFinal = member->hitungBiayaLayanan(tarifAwal);

        // Catat peminjaman dan update leveling
        member->catatPeminjamanBaru();
        buku->setDipinjam(true);

        m_totalPendapatan += biayaFinal;

        string idTrx = "TRX-" + to_string(m_riwayatPinjam.size() + 101);
        m_riwayatPinjam.emplace_back(idTrx, idMember, idBuku, tglPinjam, biayaFinal);

        cout << "[TRANSAKSI SUKSES] ID Transaksi: " << idTrx << "\n";
        cout << "  Member : " << member->getNama() << " (" << idMember << ")\n";
        cout << "  Buku   : " << buku->getNamaBuku() << " (" << idBuku << ")\n";
        cout << "  Tgl    : " << tglPinjam << " (Durasi: " << durasiHari << " hari)\n";
        cout << "  Biaya  : Rp. " << fixed << setprecision(0) << biayaFinal << "\n";

        return true;
    }

    // Form Pengembalian Buku
    bool kembalikanBuku(const string& idMember, const string& idBuku, const string& tglKembali) {
        Member* member = cariMember(idMember);
        if (!member) {
            cout << "[ERROR] Member " << idMember << " tidak ditemukan!\n";
            return false;
        }

        Buku* buku = cariBuku(idBuku);
        if (!buku) {
            cout << "[ERROR] Buku " << idBuku << " tidak ditemukan!\n";
            return false;
        }

        // Cari transaksi aktif
        for (auto& trx : m_riwayatPinjam) {
            if (trx.getIdMember() == idMember && trx.getIdBuku() == idBuku && !trx.isSudahKembali()) {
                trx.setKembali(tglKembali);
                buku->setDipinjam(false);
                cout << "[PENGEMBALIAN SUKSES] Buku \"" << buku->getNamaBuku() 
                     << "\" berhasil dikembalikan oleh " << member->getNama() 
                     << " pada tanggal " << tglKembali << ".\n";
                return true;
            }
        }

        cout << "[GAGAL] Tidak ditemukan catatan peminjaman aktif untuk Buku ID " 
             << idBuku << " oleh Member ID " << idMember << ".\n";
        return false;
    }

    // ========================================================================
    // METHOD OVERLOADING: cetakLaporan()
    // Versi 1: Laporan Umum Lengkap
    // Versi 2: Laporan Spesifik Per Member
    // ========================================================================
    void cetakLaporan() const {
        cout << "\n========================================================================\n";
        cout << "                     REPORT AKTIFITAS PERPUSTAKAAN                      \n";
        cout << "========================================================================\n";

        // (1) Report Peminjaman Buku
        cout << "\n--- (1) DAFTAR PEMINJAMAN BUKU (ID_buku, ID_member) ---\n";
        cout << "+-----------+------------+------------+---------------+--------------+------------+\n";
        cout << "| ID Trans  | ID Buku    | ID Member  | Tgl Pinjam    | Tgl Kembali  | Biaya (Rp) |\n";
        cout << "+-----------+------------+------------+---------------+--------------+------------+\n";
        if (m_riwayatPinjam.empty()) {
            cout << "|                         Belum ada transaksi peminjaman.                     |\n";
        } else {
            for (const auto& trx : m_riwayatPinjam) {
                cout << "| " << left << setw(10) << trx.getIdTransaksi()
                     << "| " << setw(11) << trx.getIdBuku()
                     << "| " << setw(11) << trx.getIdMember()
                     << "| " << setw(14) << trx.getTglPinjam()
                     << "| " << setw(13) << trx.getTglKembali()
                     << "| " << right << setw(10) << fixed << setprecision(0) << trx.getBiaya() << " |\n";
            }
        }
        cout << "+-----------+------------+------------+---------------+--------------+------------+\n";

        // (2) Status Level Member
        cout << "\n--- (2) STATUS LEVEL MEMBER ---\n";
        cout << "+-----------+---------------------+----------+---------------+---------------+\n";
        cout << "| ID Member | Nama Member         | Level    | Total Pinjam  | Sisa Free Pjm |\n";
        cout << "+-----------+---------------------+----------+---------------+---------------+\n";
        for (const auto& m : m_daftarMember) {
            m.tampilkanInfo();
        }
        cout << "+-----------+---------------------+----------+---------------+---------------+\n";

        // (3) Total Pendapatan Dana Perpustakaan
        cout << "\n--- (3) TOTAL PENDAPATAN PERPUSTAKAAN ---\n";
        cout << "  >> Total Pendapatan Masuk: Rp. " 
             << fixed << setprecision(0) << m_totalPendapatan << "\n";
        cout << "========================================================================\n\n";
    }

    void cetakLaporan(const string& idMember) const {
        cout << "\n--- LAPORAN HISTORI MEMBER DENGAN ID: " << idMember << " ---\n";
        bool ketemu = false;
        for (const auto& trx : m_riwayatPinjam) {
            if (trx.getIdMember() == idMember) {
                ketemu = true;
                cout << "  - ID Transaksi: " << trx.getIdTransaksi()
                     << " | ID Buku: " << trx.getIdBuku()
                     << " | Pinjam: " << trx.getTglPinjam()
                     << " | Kembali: " << trx.getTglKembali()
                     << " | Biaya: Rp. " << fixed << setprecision(0) << trx.getBiaya() << "\n";
            }
        }
        if (!ketemu) {
            cout << "  Tidak ditemukan histori transaksi untuk member " << idMember << ".\n";
        }
    }

    void tampilkanSemuaBuku() const {
        cout << "\n=== DAFTAR KOLEKSI BUKU ===\n";
        cout << "+-----------+-------------------------------+-----------------+\n";
        cout << "| ID Buku   | Judul Buku                    | Status          |\n";
        cout << "+-----------+-------------------------------+-----------------+\n";
        for (const auto& b : m_daftarBuku) {
            b.tampilkanInfo();
        }
        cout << "+-----------+-------------------------------+-----------------+\n";
    }

    void tampilkanSemuaPegawai() const {
        cout << "\n=== DAFTAR PEGAWAI PERPUSTAKAAN ===\n";
        cout << "+-------------+--------------------------+----------------------+\n";
        cout << "| ID Pegawai  | Nama Pegawai             | Jabatan              |\n";
        cout << "+-------------+--------------------------+----------------------+\n";
        for (const auto& p : m_daftarPegawai) {
            p.tampilkanInfo();
        }
        cout << "+-------------+--------------------------+----------------------+\n";
    }
};

// ============================================================================
// SIMULASI OTOMATIS & MENU INTERAKTIF
// ============================================================================
void jalankanSimulasiOtomatis(Perpustakaan& perpus) {
    cout << "\n========================================================\n";
    cout << "     MENJALANKAN SIMULASI LENGKAP SISTEM PERPUSTAKAAN    \n";
    cout << "========================================================\n\n";

    // a. Form Daftar Buku
    cout << ">>> 1. REGISTRASI DAFTAR BUKU\n";
    perpus.tambahBuku("B001", "Pemrograman C++ Modern");
    perpus.tambahBuku("B002", "Struktur Data & Algoritma");
    perpus.tambahBuku("B003", "Kinematika Robotika TRKB");
    perpus.tambahBuku("B004", "Kecerdasan Buatan Lanjut");
    perpus.tambahBuku("B005", "Sistem Kendali Cerdas");

    // b. Form Daftar Pegawai
    cout << "\n>>> 2. REGISTRASI DAFTAR PEGAWAI\n";
    perpus.tambahPegawai("P01", "Budi Santoso", "Kepala Perpustakaan");
    perpus.tambahPegawai("P02", "Siti Aminah", "Staff Pelayanan");

    // c. Form Daftar Member
    cout << "\n>>> 3. REGISTRASI DAFTAR MEMBER\n";
    perpus.tambahMember("M01", "Hellyos Ageng");
    perpus.tambahMember("M02", "Rina Permata");

    // Tampilkan Daftar Awal
    perpus.tampilkanSemuaBuku();
    perpus.tampilkanSemuaPegawai();

    // d. Simulasi Peminjaman untuk Menguji Leveling Member
    cout << "\n>>> 4. SIMULASI TRANSAKSI PEMINJAMAN & PENINGKATAN LEVEL\n";
    cout << "[INFO] Member M01 meminjam buku 1, 2, dan 3 berturut-turut...\n";
    perpus.pinjamBuku("M01", "B001", "2026-10-01"); // Pinjam ke-1 (Biaya 1000)
    perpus.kembalikanBuku("M01", "B001", "2026-10-03");

    perpus.pinjamBuku("M01", "B002", "2026-10-03"); // Pinjam ke-2 (Biaya 1000)
    perpus.kembalikanBuku("M01", "B002", "2026-10-05");

    perpus.pinjamBuku("M01", "B003", "2026-10-05"); // Pinjam ke-3 (Biaya 1000 -> Level 1 tercapai! Free +1)
    perpus.kembalikanBuku("M01", "B003", "2026-10-06");

    cout << "\n[INFO] Menguji penggunaan voucher Free Pinjam untuk Member M01 pada peminjaman ke-4...\n";
    // Pinjam ke-4 menggunakan Method Overloading (dengan parameter durasi dan diskon khusus)
    perpus.pinjamBuku("M01", "B001", "2026-10-07", 14, 0.0); // Biaya harus Rp. 0 karena ada free pinjam!

    // Member M02 juga meminjam buku
    cout << "\n[INFO] Member M02 meminjam buku B004...\n";
    perpus.pinjamBuku("M02", "B004", "2026-10-08");

    // e. Form Pengembalian Buku
    cout << "\n>>> 5. SIMULASI FORM PENGEMBALIAN BUKU\n";
    perpus.kembalikanBuku("M01", "B001", "2026-10-12");

    // g. Cetak Seluruh Laporan
    perpus.cetakLaporan();

    // Uji Method Overloading Cetak Laporan Khusus
    cout << ">>> 6. UJI METHOD OVERLOADING: CETAK LAPORAN SPESIFIK MEMBER M01\n";
    perpus.cetakLaporan("M01");
}

int main() {
    Perpustakaan perpustakaan;
    int pilihan = 0;

    cout << "============================================================\n";
    cout << "   PROGRAM PERPUSTAKAAN UMUM BERBASIS PBO (C++) - SOAL 1    \n";
    cout << "   Nama : Hellyos Ageng Haqiqie (163251001)                 \n";
    cout << "   Prodi: Teknik Robotika dan Kecerdasan Buatan (FTMM)      \n";
    cout << "============================================================\n";
    cout << "Pilih mode eksekusi:\n";
    cout << "1. Jalankan Simulasi Otomatis (Lengkap Sesuai Ketentuan Soal)\n";
    cout << "2. Masuk ke Menu Interaktif Manual\n";
    cout << "Pilihan Anda (1/2): ";
    
    if (!(cin >> pilihan)) {
        pilihan = 1;
    }

    if (pilihan == 1) {
        jalankanSimulasiOtomatis(perpustakaan);
    } else {
        bool berjalan = true;
        while (berjalan) {
            cout << "\n--- MENU SISTEM PERPUSTAKAAN ---\n";
            cout << "1. Form Daftar Buku\n";
            cout << "2. Form Daftar Pegawai\n";
            cout << "3. Form Daftar Member\n";
            cout << "4. Form Peminjaman Buku\n";
            cout << "5. Form Pengembalian Buku\n";
            cout << "6. Tampilkan Koleksi Buku & Pegawai\n";
            cout << "7. Cetak Laporan Aktivitas Perpustakaan\n";
            cout << "8. Keluar\n";
            cout << "Pilih menu [1-8]: ";
            int m;
            if (!(cin >> m)) break;

            if (m == 1) {
                string id, nama;
                cout << "Input ID Buku   : "; cin >> id;
                cin.ignore();
                cout << "Input Nama Buku : "; getline(cin, nama);
                perpustakaan.tambahBuku(id, nama);
            } else if (m == 2) {
                string id, nama;
                cout << "Input ID Pegawai   : "; cin >> id;
                cin.ignore();
                cout << "Input Nama Pegawai : "; getline(cin, nama);
                perpustakaan.tambahPegawai(id, nama);
            } else if (m == 3) {
                string id, nama;
                cout << "Input ID Member   : "; cin >> id;
                cin.ignore();
                cout << "Input Nama Member : "; getline(cin, nama);
                perpustakaan.tambahMember(id, nama);
            } else if (m == 4) {
                string idM, idB, tgl;
                cout << "Input ID Member          : "; cin >> idM;
                cout << "Input ID Buku            : "; cin >> idB;
                cout << "Input ID/Tanggal Pinjam  : "; cin >> tgl;
                perpustakaan.pinjamBuku(idM, idB, tgl);
            } else if (m == 5) {
                string idM, idB, tgl;
                cout << "Input ID Member                : "; cin >> idM;
                cout << "Input ID Buku                  : "; cin >> idB;
                cout << "Input ID/Tanggal Pengembalian  : "; cin >> tgl;
                perpustakaan.kembalikanBuku(idM, idB, tgl);
            } else if (m == 6) {
                perpustakaan.tampilkanSemuaBuku();
                perpustakaan.tampilkanSemuaPegawai();
            } else if (m == 7) {
                perpustakaan.cetakLaporan();
            } else if (m == 8) {
                cout << "Terima kasih telah menggunakan sistem perpustakaan.\n";
                berjalan = false;
            } else {
                cout << "Pilihan tidak valid!\n";
            }
        }
    }

    return 0;
}
