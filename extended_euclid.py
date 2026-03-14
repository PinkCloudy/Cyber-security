def degree(poly):
    """Tính bậc của đa thức (vị trí của bit 1 cao nhất)"""
    return len(bin(poly)) - 3 if poly > 0 else -1

def poly_div(a, b):
    """Phép chia đa thức trong GF(2), trả về Thương (q) và Dư (r)"""
    q = 0
    r = a
    deg_b = degree(b)
    while degree(r) >= deg_b:
        shift = degree(r) - deg_b
        q ^= (1 << shift)    # Cộng (XOR) vào thương
        r ^= (b << shift)    # Trừ (XOR) đa thức bị chia
    return q, r

def poly_mul(a, b):
    """Phép nhân đa thức trong GF(2)"""
    res = 0
    while b > 0:
        if b & 1: 
            res ^= a
        a <<= 1
        b >>= 1
    return res

def extended_euclidean_gf2(m_x, b_x):
    """Thuật toán Euclidean mở rộng trên GF(2)"""
    print(f"{'i':<3} | {'r_i(x)':<10} | {'q_i(x)':<10} | {'w_i(x)':<10}")
    print("-" * 45)
    
    # Khởi tạo các giá trị ban đầu
    r_prev, r_curr = m_x, b_x
    w_prev, w_curr = 0, 1
    
    print(f"{'-1':<3} | {r_prev:<10} | {'-':<10} | {w_prev:<10}")
    print(f"{'0':<3} | {r_curr:<10} | {'-':<10} | {w_curr:<10}")
    
    i = 1
    while r_curr != 0:
        # Tính q_i và r_i
        q, r_next = poly_div(r_prev, r_curr)
        # Tính w_i = w_{i-2} - q_i * w_{i-1} (trong GF(2) phép trừ là XOR)
        w_next = w_prev ^ poly_mul(q, w_curr)
        
        print(f"{i:<3} | {r_next:<10} | {q:<10} | {w_next:<10}")
        
        # Cập nhật cho vòng lặp tiếp theo
        r_prev, r_curr = r_curr, r_next
        w_prev, w_curr = w_curr, w_next
        i += 1
        
    print(f"\n=> Nghịch đảo nhân là: {w_prev}")
    return w_prev

# --- KIỂM THỬ ---
m = 1033 # x^10 + x^3 + 1
a = 523
b = 1015

print("TÌM NGHỊCH ĐẢO CỦA a = 523:")
extended_euclidean_gf2(m, a)

print("\nTÌM NGHỊCH ĐẢO CỦA b = 1015:")
extended_euclidean_gf2(m, b)