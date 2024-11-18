from collections import Counter

# Tính tần số các ký tự
def calculate_frequency(data):
    return dict(Counter(data))

# Phân chia ký tự theo phương pháp Shannon–Fano
def shannon_fano(freqs, prefix=''):
    if len(freqs) == 1:
        return {list(freqs.keys())[0]: prefix}

    sorted_freqs = sorted(freqs.items(), key=lambda x: -x[1])
    total_freq = sum(freqs.values())
    cumulative_freq = 0
    for i, (symbol, freq) in enumerate(sorted_freqs):
        cumulative_freq += freq
        if cumulative_freq >= total_freq / 2:
            left_part = dict(sorted_freqs[:i+1])
            right_part = dict(sorted_freqs[i+1:])
            break

    encoding = {}
    encoding.update(shannon_fano(left_part, prefix + '0'))
    encoding.update(shannon_fano(right_part, prefix + '1'))
    return encoding

def encode(encoding, data):
    return ''.join(encoding[char] for char in data)

def decode(encoded_data, decoding):
    decoded_output = ""
    current_bits = ""
    for bit in encoded_data:
        current_bits += bit
        if current_bits in decoding:
            decoded_output += decoding[current_bits]
            current_bits = ""  # Xóa các bit đã giải mã
    return decoded_output

data = ""
while data != "-1":
    # Chuỗi cần mã hóa
    data = input("Write the string (write -1 to exit): ")
    if data != "-1":
        freqs = calculate_frequency(data)
        encoding = shannon_fano(freqs)

        # Sắp xếp Counter theo tần suất giảm dần và in ra
        sorted_freqs = sorted(freqs.items(), key=lambda x: x[1], reverse=True)

        sum = 0
        print("Frequencies:")
        for key, value in sorted_freqs:
            print(f"{key}: {value}")

        # In mã Shannon–Fano cho từng ký tự
        print("Shannon-Fano Encoding:")
        for symbol in encoding:
            print(f"{symbol}: {encoding[symbol]}")            
            sum += len(encoding[symbol])
        print("Sum of encoding bits:", sum)

        print("\nShannon-Fano algorithm")
        print("-----")
        print("Data:\n" + data)
        print("Size in bits:", len(data) * 8)

        # Kết quả mã hóa
        encoded_data = encode(encoding, data)
        print("\nEncoded Data:\n" + encoded_data)
        print("Size in bits:", len(encoded_data))

        decoding = {v: k for k, v in encoding.items()}

        decoded_data = decode(encoded_data, decoding)
        print("\nDecoded Data:\n" + decoded_data)
        print("-----\n")
