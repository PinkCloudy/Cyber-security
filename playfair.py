def prepare_text(text):
    # Loại bỏ khoảng trắng và đổi thành chữ in hoa
    text = text.replace(" ", "").upper()
    # Thay thế J bằng I (quy ước Playfair)
    text = text.replace("J", "I")
    return text

def generate_key_matrix(key):
    # Tạo ma trận khóa 5x5
    key = prepare_text(key)
    matrix = []
    seen = set()
    
    # Thêm các ký tự từ khóa vào ma trận
    for char in key:
        if char not in seen:
            matrix.append(char)
            seen.add(char)
            
    # Thêm các ký tự còn lại trong bảng chữ cái (trừ J)
    alphabet = "ABCDEFGHIKLMNOPQRSTUVWXYZ"
    for char in alphabet:
        if char not in seen:
            matrix.append(char)
            
    # Chuyển thành dạng lưới 5x5
    return [matrix[i:i+5] for i in range(0, 25, 5)]

def find_position(matrix, char):
    # Tìm vị trí hàng và cột của ký tự
    for row in range(5):
        for col in range(5):
            if matrix[row][col] == char:
                return row, col
    return None

def encrypt_playfair(plaintext, key):
    matrix = generate_key_matrix(key)
    plaintext = prepare_text(plaintext)
    
    # Xử lý các cặp ký tự trùng nhau (ví dụ: HELLO -> HELXLO)
    processed_text = ""
    i = 0
    while i < len(plaintext):
        char1 = plaintext[i]
        if i + 1 < len(plaintext):
            char2 = plaintext[i+1]
            if char1 == char2:
                processed_text += char1 + "X"
                i += 1
            else:
                processed_text += char1 + char2
                i += 2
        else:
            processed_text += char1 + "X" # Thêm X nếu lẻ ký tự cuối
            i += 1
            
    ciphertext = ""
    for i in range(0, len(processed_text), 2):
        r1, c1 = find_position(matrix, processed_text[i])
        r2, c2 = find_position(matrix, processed_text[i+1])
        
        if r1 == r2: # Cùng hàng -> Lấy ký tự bên phải
            ciphertext += matrix[r1][(c1 + 1) % 5]
            ciphertext += matrix[r2][(c2 + 1) % 5]
        elif c1 == c2: # Cùng cột -> Lấy ký tự bên dưới
            ciphertext += matrix[(r1 + 1) % 5][c1]
            ciphertext += matrix[(r2 + 1) % 5][c2]
        else: # Hình chữ nhật -> Lấy giao điểm
            ciphertext += matrix[r1][c2]
            ciphertext += matrix[r2][c1]
            
    return ciphertext

# --- CHẠY THỬ ---
key_input = "MONARCHY"
text_input = "Do you like to study a cryptography course"

print(f"Key: {key_input}")
print(f"Plaintext: {text_input}")
encrypted = encrypt_playfair(text_input, key_input)
print(f"Ciphertext: {encrypted}")