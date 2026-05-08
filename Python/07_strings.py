# 07 - Strings
# Strings are immutable sequences of characters.

s = "Hello, World!"

# --- Indexing and slicing ---
print(s[0])         # H
print(s[-1])        # !  (negative = from the end)
print(s[7:12])      # World
print(s[::-1])      # reverse the string

# --- Common methods ---
print(s.upper())                    # HELLO, WORLD!
print(s.lower())                    # hello, world!
print(s.title())                    # Hello, World!
print(s.strip())                    # remove leading/trailing whitespace
print("  hi  ".strip())            # "hi"
print("  hi  ".lstrip())           # "hi  "
print(s.replace("World", "Python"))# Hello, Python!
print(s.startswith("Hello"))       # True
print(s.endswith("!"))             # True
print(s.find("World"))             # 7  (-1 if not found)
print(s.count("l"))                # 3

# --- Split and join ---
csv = "apple,banana,cherry"
parts = csv.split(",")
print(parts)                        # ['apple', 'banana', 'cherry']
print(" | ".join(parts))           # apple | banana | cherry

words = "  too   many   spaces  ".split()   # splits on any whitespace
print(words)

# --- Checking content ---
print("hello".isalpha())    # True  — only letters
print("123".isdigit())      # True  — only digits
print("abc123".isalnum())   # True  — letters + digits
print("   ".isspace())      # True

# --- String formatting ---
name, age = "Alice", 30

# f-string (recommended)
print(f"Name: {name}, Age: {age}")
print(f"Pi: {3.14159:.2f}")         # 2 decimal places
print(f"{'left':<10}|")             # left-align in 10 chars
print(f"{'right':>10}|")            # right-align
print(f"{1234567:,}")               # 1,234,567 (thousand separator)

# .format()
print("Name: {}, Age: {}".format(name, age))
print("{name} is {age}".format(name=name, age=age))

# % (old style)
print("Name: %s, Age: %d" % (name, age))

# --- Multiline strings ---
text = """
Line 1
Line 2
Line 3
""".strip()
print(text)

# --- Raw strings — backslashes are literal (useful for file paths, regex) ---
path  = r"C:\Users\Alice\Documents"
print(path)

# --- String multiplication and membership ---
print("-" * 20)
print("ell" in "hello")     # True

# --- encode / decode ---
encoded = "hello".encode("utf-8")   # bytes
print(encoded)                      # b'hello'
print(encoded.decode("utf-8"))      # hello
