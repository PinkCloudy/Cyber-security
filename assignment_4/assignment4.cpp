#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

string rc4_detailed_trace(vector<int> key, string plaintext, int N = 10) {
    cout << "===================================================================================================================" << endl;
    cout << "BAT DAU MA HOA RC4 VOI KHONG GIAN N=" << N << endl;
    cout << "Khoa K: [";
    for (size_t idx = 0; idx < key.size(); ++idx) {
        cout << key[idx] << (idx == key.size() - 1 ? "" : ", ");
    }
    cout << "]" << endl;
    cout << "Ban ro: '" << plaintext << "'" << endl;
    cout << "===================================================================================================================" << endl;

    // -----------------------------------------------------
    // BƯỚC 1 & 2: KHỞI TẠO VÀ HOÁN VỊ MẢNG S (KSA) [1]
    // -----------------------------------------------------
    vector<int> S(N);
    vector<int> T(N);
    int keylen = key.size();

    // Khởi tạo mảng S và mảng tạm T
    for (int i = 0; i < N; ++i) {
        S[i] = i;
        T[i] = key[i % keylen];
    }

    // Hoán vị khởi tạo S
    int j = 0;
    for (int i = 0; i < N; ++i) {
        j = (j + S[i] + T[i]) % N;
        // Đổi chỗ S[i] và S[j]
        swap(S[i], S[j]);
    }

    cout << "Mang S sau buoc khoi tao (KSA): [";
    for (int i = 0; i < N; ++i) {
        cout << S[i] << (i == N - 1 ? "" : ", ");
    }
    cout << "]\n\n";

    // -----------------------------------------------------
    // BƯỚC 3: SINH DÒNG KHÓA VÀ MÃ HÓA (PRGA) [2]
    // -----------------------------------------------------
    int i = 0;
    j = 0;

    // Header của bảng
    string header = "| Char | ASCII | i  | j  | S[i] | S[j] | Mang S (sau swap)               | t  | k  | Phep XOR   | Cipher ASCII | Ban ma |";
    string separator(header.length(), '-');

    cout << separator << endl;
    cout << header << endl;
    cout << separator << endl;

    string ciphertext = "";

    for (char c : plaintext) {
        int m_t = (int)c; // Mã ASCII của ký tự bản rõ

        // Tính toán i, j
        i = (i + 1) % N;
        j = (j + S[i]) % N;

        // Lấy giá trị S[i], S[j] trước khi swap để hiển thị
        int si_val = S[i];
        int sj_val = S[j];

        // Đổi chỗ S[i] và S[j]
        swap(S[i], S[j]);

        // Tính chỉ số t và khóa k
        int t = (S[i] + S[j]) % N;
        int k = S[t];

        // Phép XOR mã hóa
        int c_t = m_t ^ k;
        char c_char = (char)c_t;
        ciphertext += c_char;

        // Chuỗi định dạng mảng S để hiển thị
        string s_str = "[";
        for (int idx = 0; idx < N; ++idx) {
            s_str += to_string(S[idx]) + (idx == N - 1 ? "" : ", ");
        }
        s_str += "]";
        
        string xor_str = to_string(m_t) + " ^ " + to_string(k);

        // In từng dòng của bảng (sử dụng setw để căn lề)
        cout << "| " << left << setw(4) << c 
             << " | " << left << setw(5) << m_t 
             << " | " << left << setw(2) << i 
             << " | " << left << setw(2) << j 
             << " | " << left << setw(4) << si_val 
             << " | " << left << setw(4) << sj_val 
             << " | " << left << setw(31) << s_str 
             << " | " << left << setw(2) << t 
             << " | " << left << setw(2) << k 
             << " | " << left << setw(10) << xor_str 
             << " | " << left << setw(12) << c_t 
             << " | " << left << setw(6) << c_char << " |" << endl;
    }
    cout << separator << endl;

    // In kết quả bản mã hoàn chỉnh
    cout << "\n=> KET QUA BAN MA HOAN CHINH: " << ciphertext << endl;
    return ciphertext;
}

int main() {
    // Vector trạng thái bài toán kích thước N=10
    int N = 10;
    
    // Hạt mầm K và Bản rõ
    vector<int> K = {2, 4, 1, 7};
    string plaintext = "cybersecurity";

    // Gọi hàm thực thi
    rc4_detailed_trace(K, plaintext, N);

    return 0;
}