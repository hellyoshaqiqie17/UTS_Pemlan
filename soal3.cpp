/**
 * ============================================================================
 * Program     : Simulasi Robot Differential Drive Multi-Input - Soal 3
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
#include <cmath>
#include <string>
#include <iomanip>
#include <algorithm>

using namespace std;

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// ============================================================================
// 1. BASE CLASS ROBOT (Abstraksi & Polymorphism untuk Overriding)
// ============================================================================
class Robot {
protected:
    string m_namaRobot;

public:
    Robot(const string& nama = "Generic Robot") : m_namaRobot(nama) {}
    virtual ~Robot() = default;

    string getNamaRobot() const { return m_namaRobot; }
    void setNamaRobot(const string& nama) { m_namaRobot = nama; }

    // Pure Virtual Methods (Harus di-Override oleh Derived Class)
    virtual void update(float dt) = 0;
    virtual void tampilkanPosisi(float tRelatif, float tTotal) const = 0;
    virtual void resetPosisi() = 0;
};

// ============================================================================
// 2. CLASS DIFFERENTIAL DRIVE ROBOT (Inheritance, Enkapsulasi, Overloading, Overriding)
// ============================================================================
class DifferentialDriveRobot : public Robot {
private:
    // Atribut Posisi dan Orientasi (Enkapsulasi: Private)
    float m_x;     // Posisi sumbu-x (meter)
    float m_y;     // Posisi sumbu-y (meter)
    float m_theta; // Orientasi sudut hadap robot (radian)

    // Parameter Fisik Roda Robot
    float m_r;     // Jari-jari roda (meter)
    float m_L;     // Jarak antar roda / track width (meter)

    // Kecepatan Sudut Roda Saat Ini (rad/s)
    float m_wL;
    float m_wR;

    // Helper untuk normalisasi sudut theta ke rentang [-pi, pi]
    float normalisasiSudut(float sudut) const {
        while (sudut > M_PI)  sudut -= 2.0f * M_PI;
        while (sudut < -M_PI) sudut += 2.0f * M_PI;
        return sudut;
    }

public:
    // ========================================================================
    // CONSTRUCTOR OVERLOADING
    // ========================================================================
    // Versi 1: Default constructor (r = 0.1m, L = 0.4m, posisi awal di 0,0,0)
    DifferentialDriveRobot()
        : Robot("TRKB-DiffBot"), m_x(0.0f), m_y(0.0f), m_theta(0.0f),
          m_r(0.1f), m_L(0.4f), m_wL(0.0f), m_wR(0.0f) {}

    // Versi 2: Parameter geometri roda
    DifferentialDriveRobot(float r, float L)
        : Robot("TRKB-DiffBot"), m_x(0.0f), m_y(0.0f), m_theta(0.0f),
          m_r(r > 0 ? r : 0.1f), m_L(L > 0 ? L : 0.4f), m_wL(0.0f), m_wR(0.0f) {}

    // Versi 3: Parameter geometri roda dan inisialisasi koordinat awal
    DifferentialDriveRobot(float r, float L, float x0, float y0, float theta0, const string& nama = "TRKB-DiffBot")
        : Robot(nama), m_x(x0), m_y(y0), m_theta(normalisasiSudut(theta0)),
          m_r(r > 0 ? r : 0.1f), m_L(L > 0 ? L : 0.4f), m_wL(0.0f), m_wR(0.0f) {}

    // ========================================================================
    // GETTER & SETTER (ENKAPSULASI)
    // ========================================================================
    float getX() const { return m_x; }
    void setX(float x) { m_x = x; }

    float getY() const { return m_y; }
    void setY(float y) { m_y = y; }

    float getTheta() const { return m_theta; }
    void setTheta(float theta) { m_theta = normalisasiSudut(theta); }

    float getThetaDerajat() const {
        return m_theta * 180.0f / static_cast<float>(M_PI);
    }

    float getR() const { return m_r; }
    void setR(float r) { if (r > 0) m_r = r; }

    float getL() const { return m_L; }
    void setL(float L) { if (L > 0) m_L = L; }

    float getWL() const { return m_wL; }
    float getWR() const { return m_wR; }

    void setKecepatanRoda(float wL, float wR) {
        m_wL = wL;
        m_wR = wR;
    }

    // Overload setKecepatan untuk gerak lurus dengan kecepatan linear v
    void setKecepatanRoda(float vLinear) {
        float w = vLinear / m_r;
        m_wL = w;
        m_wR = w;
    }

    // ========================================================================
    // METHOD KINEMATIKA & METHOD OVERLOADING: update()
    //
    // Rumus Kinematika Differential Drive:
    // v       = (r / 2) * (wR + wL)
    // omega   = (r / L) * (wR - wL)
    // vx      = v * cos(theta)
    // vy      = v * sin(theta)
    // dx      = vx * dt
    // dy      = vy * dt
    // dtheta  = omega * dt
    // x_baru  = x_lama + dx
    // y_baru  = y_lama + dy
    // theta_baru = theta_lama + dtheta
    // ========================================================================

    // Versi 1 (Instruksi Tugas No. 2): update dengan input langsung wL, wR, dt
    void update(float wL, float wR, float dt) {
        m_wL = wL;
        m_wR = wR;

        // Kecepatan translasi (v) dan kecepatan sudut (omega)
        float v = (m_r / 2.0f) * (m_wR + m_wL);
        float omega = (m_r / m_L) * (m_wR - m_wL);

        // Kecepatan translasi robot pada sumbu x dan y
        float vx = v * cos(m_theta);
        float vy = v * sin(m_theta);

        // Perubahan kecil dx, dy, dan dtheta
        float dx = vx * dt;
        float dy = vy * dt;
        float dtheta = omega * dt;

        // Pembaruan posisi baru
        m_x += dx;
        m_y += dy;
        m_theta = normalisasiSudut(m_theta + dtheta);
    }

    // Versi 2 (Overriding & Overloading): update dengan internal state wL, wR
    void update(float dt) override {
        update(m_wL, m_wR, dt);
    }

    // Method Overriding: tampilkanPosisi
    void tampilkanPosisi(float tRelatif, float tTotal) const override {
        cout << "  [t = " << fixed << setprecision(1) << setw(4) << tRelatif << " s"
             << " | Tot = " << setw(5) << tTotal << " s] "
             << "x = " << setw(7) << fixed << setprecision(3) << m_x << " m | "
             << "y = " << setw(7) << fixed << setprecision(3) << m_y << " m | "
             << "theta = " << setw(7) << fixed << setprecision(3) << m_theta << " rad ("
             << setw(6) << fixed << setprecision(1) << getThetaDerajat() << " deg)\n";
    }

    // Method Overriding: resetPosisi
    void resetPosisi() override {
        m_x = 0.0f;
        m_y = 0.0f;
        m_theta = 0.0f;
        m_wL = 0.0f;
        m_wR = 0.0f;
    }

    // ========================================================================
    // PEMETAAN PERINTAH KONTROL (maju, mundur, kiri, kanan, stop)
    // ========================================================================
    bool terapkanPerintah(const string& perintah, float& targetWL, float& targetWR) {
        string cmd = perintah;
        transform(cmd.begin(), cmd.end(), cmd.begin(), ::tolower);

        if (cmd == "maju") {
            // Gerak maju lurus: kedua roda berputar positif
            targetWL = 5.0f;
            targetWR = 5.0f;
            return true;
        } else if (cmd == "mundur") {
            // Gerak mundur lurus: kedua roda berputar negatif
            targetWL = -5.0f;
            targetWR = -5.0f;
            return true;
        } else if (cmd == "kiri") {
            // Belok kiri di tempat (spin turn CCW)
            targetWL = -2.0f;
            targetWR = +2.0f;
            return true;
        } else if (cmd == "kanan") {
            // Belok kanan di tempat (spin turn CW)
            targetWL = +2.0f;
            targetWR = -2.0f;
            return true;
        } else if (cmd == "stop") {
            // Berhenti
            targetWL = 0.0f;
            targetWR = 0.0f;
            return true;
        } else if (cmd == "selesai") {
            return false;
        } else {
            cout << "  [PERINGATAN] Perintah \"" << perintah 
                 << "\" tidak dikenali! Perintah valid: maju, mundur, stop, kiri, kanan, selesai.\n";
            return false;
        }
    }

    /**
     * Menjalankan perintah selama durasi detik (default 5.0s)
     * dengan step dt (default 0.1s), dan menampilkan posisi tiap intervalDisplay (1.0s).
     */
    void jalankanPerintah(const string& perintah, float durasi, float dt, float intervalDisplay, float& waktuTotalAkumulasi) {
        float wL = 0.0f, wR = 0.0f;
        if (!terapkanPerintah(perintah, wL, wR)) {
            return;
        }

        cout << "\n>>> Mengeksekusi perintah: [" << perintah << "]\n";
        cout << "    Parameter: wL = " << wL << " rad/s, wR = " << wR << " rad/s | "
             << "Durasi = " << durasi << " s, dt = " << dt << " s\n";
        cout << "    ----------------------------------------------------------------------\n";

        int totalLangkah = static_cast<int>(round(durasi / dt));
        int langkahPerDisplay = static_cast<int>(round(intervalDisplay / dt));

        for (int step = 1; step <= totalLangkah; ++step) {
            // Panggil method update(wL, wR, dt)
            update(wL, wR, dt);
            waktuTotalAkumulasi += dt;

            // Tampilkan hasil posisi tiap 1 detik (setiap 10 langkah dt = 0.1)
            if (step % langkahPerDisplay == 0) {
                float tRelatif = step * dt;
                tampilkanPosisi(tRelatif, waktuTotalAkumulasi);
            }
        }
        cout << "    ----------------------------------------------------------------------\n";
    }
};

// ============================================================================
// SIMULASI OTOMATIS & MENU INTERAKTIF
// ============================================================================
void jalankanSimulasiOtomatis(DifferentialDriveRobot& robot) {
    cout << "\n====================================================================\n";
    cout << "     MENJALANKAN SIMULASI ROBOT DIFFERENTIAL DRIVE OTOMATIS         \n";
    cout << "====================================================================\n";
    cout << "Parameter Robot:\n";
    cout << "  - Jari-jari roda (r)     : " << robot.getR() << " meter\n";
    cout << "  - Jarak antar roda (L)   : " << robot.getL() << " meter\n";
    cout << "  - Posisi Awal            : x = 0.000 m, y = 0.000 m, theta = 0.000 rad\n";
    cout << "  - Durasi per perintah    : 5 detik (dt = 0.1 detik)\n";
    cout << "  - Tampilan posisi        : Setiap 1 detik\n";
    cout << "====================================================================\n";

    float waktuTotal = 0.0f;
    vector<string> skenarioPerintah = {"maju", "kiri", "maju", "kanan", "mundur", "stop"};

    for (const auto& cmd : skenarioPerintah) {
        robot.jalankanPerintah(cmd, 5.0f, 0.1f, 1.0f, waktuTotal);
    }

    cout << "\n[SIMULASI SELESAI]\n";
    cout << "Posisi Akhir Robot:\n";
    cout << "  x     = " << fixed << setprecision(4) << robot.getX() << " meter\n";
    cout << "  y     = " << fixed << setprecision(4) << robot.getY() << " meter\n";
    cout << "  theta = " << fixed << setprecision(4) << robot.getTheta() << " radian ("
         << fixed << setprecision(2) << robot.getThetaDerajat() << " derajat)\n";
    cout << "====================================================================\n\n";
}

int main() {
    DifferentialDriveRobot robot(0.1f, 0.4f); // r = 0.1m, L = 0.4m
    int modePilihan = 0;

    cout << "============================================================\n";
    cout << "   SIMULASI ROBOT DIFFERENTIAL DRIVE (C++) - SOAL 3         \n";
    cout << "   Nama : Hellyos Ageng Haqiqie (163251001)                 \n";
    cout << "   Prodi: Teknik Robotika dan Kecerdasan Buatan (FTMM)      \n";
    cout << "============================================================\n";
    cout << "Pilih mode eksekusi:\n";
    cout << "1. Jalankan Simulasi Otomatis Rangkaian Gerak (Sesuai Soal)\n";
    cout << "2. Masuk ke Mode Interaktif Multi-Input User (Looping Hingga 'selesai')\n";
    cout << "Pilihan Anda (1/2): ";

    if (!(cin >> modePilihan)) {
        modePilihan = 1;
    }

    if (modePilihan == 1) {
        jalankanSimulasiOtomatis(robot);
    } else {
        cout << "\n[MODE INTERAKTIF MULTI-INPUT AKTIF]\n";
        cout << "Masukkan perintah kontrol robot:\n";
        cout << "  - 'maju'    : Bergerak lurus ke depan selama 5 detik\n";
        cout << "  - 'mundur'  : Bergerak lurus ke belakang selama 5 detik\n";
        cout << "  - 'kiri'    : Berputar di tempat ke arah kiri selama 5 detik\n";
        cout << "  - 'kanan'   : Berputar di tempat ke arah kanan selama 5 detik\n";
        cout << "  - 'stop'    : Berhenti diam selama 5 detik\n";
        cout << "  - 'selesai' : Mengakhiri program simulasi\n";
        cout << "Setiap perintah dijalankan selama 5 detik dengan dt = 0.1 s.\n";
        cout << "Hasil posisi ditampilkan setiap 1 detik.\n\n";

        float waktuTotal = 0.0f;
        string perintah;

        while (true) {
            cout << "\nMasukkan perintah (maju/mundur/stop/kiri/kanan/selesai): ";
            cin >> perintah;

            string cmdLower = perintah;
            transform(cmdLower.begin(), cmdLower.end(), cmdLower.begin(), ::tolower);

            if (cmdLower == "selesai") {
                cout << "\nProgram selesai. Posisi akhir robot:\n";
                cout << "  x = " << fixed << setprecision(3) << robot.getX() << " m, "
                     << "y = " << robot.getY() << " m, "
                     << "theta = " << robot.getTheta() << " rad (" 
                     << robot.getThetaDerajat() << " deg)\n";
                break;
            }

            robot.jalankanPerintah(perintah, 5.0f, 0.1f, 1.0f, waktuTotal);
        }
    }

    return 0;
}
