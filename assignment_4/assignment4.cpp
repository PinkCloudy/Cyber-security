#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

void rc4_encrypt(const vector<int>& key, const string& plaintext) {
    int N = 256; // Không gian trạng thái chuẩn 256
    vector<int> S(N);
    vector<int> T(N);
    int keylen = key.size();

    // ==========================================
    // BƯỚC 1: KHỞI TẠO MẢNG S VÀ T
    // ==========================================
    for (int i = 0; i < N; ++i) {
        S[i] = i;
        T[i] = key[i % keylen];
    }

    // ==========================================
    // BƯỚC 2: HOÁN VỊ KHỞI TẠO (KSA)
    // ==========================================
    int j = 0;
    for (int i = 0; i < N; ++i) {
        j = (j + S[i] + T[i]) % N;
        swap(S[i], S[j]);
    }

    // ==========================================
    // BƯỚC 3: SINH DÒNG KHÓA VÀ MÃ HÓA (PRGA)
    // ==========================================
    int i = 0;
    j = 0;
    string ciphertext = "";

    cout << "\n================ CHI TIET MA HOA ==================" << endl;
    cout << "| Char | ASCII | Khoa k | Ban ma (Char) | Ma Hex  |" << endl;
    cout << "---------------------------------------------------" << endl;

    for (char c : plaintext) {
        // Ép kiểu unsigned char để xử lý đúng mã ASCII
        unsigned char m_t = (unsigned char)c;

        // Xoay vòng mảng S để sinh khóa k
        i = (i + 1) % N;
        j = (j + S[i]) % N;
        swap(S[i], S[j]);

        int t = (S[i] + S[j]) % N;
        int k = S[t];

        // Phép mã hóa XOR (C_i = M_i XOR K_i)
        unsigned char c_t = m_t ^ k;
        ciphertext += c_t;

        // Ký tự hiển thị (nếu là ký tự điều khiển thì in ra dấu '.')
        char display_char = (c_t >= 32 && c_t <= 126) ? (char)c_t : '.';

        // In từng dòng chi tiết
        cout << "| " << left << setw(4) << c 
             << " | " << left << setw(5) << (int)m_t 
             << " | " << left << setw(6) << k 
             << " | " << left << setw(13) << display_char 
             << " |   " << hex << uppercase << setw(2) << setfill('0') << (int)c_t 
             << dec << setfill(' ') << "    |" << endl;
    }
    cout << "===================================================" << endl;

    // In kết quả chuỗi bản mã dạng chuỗi ký tự trực tiếp
    cout << "\n=> Ban ma (Ciphertext - dang chuoi): " << ciphertext << endl;
    
    // In kết quả chuỗi bản mã dạng Hex để dễ copy/paste/đọc
    cout << "=> Ban ma (Ciphertext - dang Hex)  : ";
    for(char c : ciphertext) {
        cout << hex << uppercase << setw(2) << setfill('0') << (int)(unsigned char)c << " ";
    }
    cout << dec << endl;
}

int main() {
    // Khởi tạo khóa K (Bạn có thể thay đổi mảng khóa này)
    vector<int> K = {2, 4, 1, 7}; 
    string plaintext;

    cout << "Thuat toan RC4 - Khong gian trang thai N = 256" << endl;
    cout << "Khoa K hien tai: [4-7]" << endl;
    cout << "----------------------------------------------" << endl;
    
    // Nhập bản rõ từ người dùng
    cout << "Moi ban nhap ban ro (plaintext): ";
    getline(cin, plaintext);

    // Gọi hàm mã hóa
    rc4_encrypt(K, plaintext);

    return 0;
}