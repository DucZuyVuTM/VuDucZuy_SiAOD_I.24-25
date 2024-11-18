from heapq import heappush, heappop, heapify
from collections import defaultdict, Counter

# Cấu trúc Node của cây Huffman
class Node:
    def __init__(self, ch, freq):
        self.ch = ch
        self.freq = freq
        self.left = None
        self.right = None
    
    # Để so sánh các Node trong hàng đợi ưu tiên
    def __lt__(self, other):
        return self.freq < other.freq
    
# Hàm tạo mã Huffman
def encode(root, prefix, huffman_code):
    if root is None:
        return
    
    if root.left is None and root.right is None:
        huffman_code[root.ch] = prefix

    encode(root.left, prefix + '0', huffman_code)
    encode(root.right, prefix + '1', huffman_code)

# Hàm giải mã chuỗi đã mã hóa
def decode(root, index, encoded_str):
    if root is None:
        return index, None
    
    if root.left is None and root.right is None:
        return index, root.ch
    
    index += 1
    if encoded_str[index] == '0':
        return decode(root.left, index, encoded_str)
    else:
        return decode(root.right, index, encoded_str)
    
# Xây dựng cây Huffman và mã hóa văn bản
def build_huffman_tree(text):
    # Tính tần số của các kí tự
    freq = Counter(text)

    # Tạo hàng đợi ưu tiên và chèn từng kí tự với tần số của nó
    heap = [Node(ch, freq) for ch, freq in freq.items()]
    heapify(heap)

    # Xây dựng cây Huffman
    while len(heap) > 1:
        left = heappop(heap)
        right = heappop(heap)
        merged = Node(Node, left.freq + right.freq)
        merged.left = left
        merged.right = right
        heappush(heap, merged)

    root = heap[0]

    # Tạo mã Huffman cho từng kí tự
    huffman_code = {}
    encode(root, '', huffman_code)

    print("Huffman Codes:")
    for ch, code in huffman_code.items():
        print(f"{ch}: {code}")

    print("\nHuffman algorithm")

    print("----------------")
    print("Original string:\n" + text)
    print("Size in bits:", len(text) * 8)

    # Nén văn bản
    encoded_str = ''.join(huffman_code[ch] for ch in text)
    print("\nEncoded string:\n" + encoded_str)
    print("Size in bits:", len(encoded_str))

    # Giải mã văn bản
    print("\nDecoded string:")
    index = -1
    while index < len(encoded_str) - 1:
        index, ch = decode(root, index, encoded_str)
        print(ch, end='')

    print("\n----------------\n")

# Phần chính của chương trình
text = "Suni"
while text != "-1":
    text = input("Write the string (write -1 to exit): ")

    if text != "-1":
        build_huffman_tree(text)

print("Program exited")