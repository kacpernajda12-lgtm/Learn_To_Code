# 03 - Operators

# --- Arithmetic ---
print("=== Arithmetic ===")
print(10 + 3)   # 13
print(10 - 3)   # 7
print(10 * 3)   # 30
print(10 / 3)   # 3.333...  (always returns float)
print(10 // 3)  # 3         (floor division — truncates)
print(10 % 3)   # 1         (modulo / remainder)
print(2 ** 8)   # 256       (power — unique to Python)

# --- Augmented assignment ---
print("\n=== Augmented assignment ===")
n = 10
n += 5;  print(n)   # 15
n -= 3;  print(n)   # 12
n *= 2;  print(n)   # 24
n //= 5; print(n)   # 4
n **= 3; print(n)   # 64

# --- Comparison (return True/False) ---
print("\n=== Comparison ===")
print(10 == 10)  # True
print(10 != 3)   # True
print(10 > 3)    # True
print(10 < 3)    # False
print(10 >= 10)  # True
print(10 <= 9)   # False

# --- Logical ---
print("\n=== Logical ===")
print(True and False)   # False
print(True or  False)   # True
print(not True)         # False

# Short-circuit: Python stops evaluating as soon as the result is known
print(0 and 1/0)        # 0 — never evaluates 1/0
print(1 or  1/0)        # 1 — never evaluates 1/0

# --- Identity and membership ---
print("\n=== Identity / Membership ===")
a = [1, 2, 3]
b = a           # same object
c = [1, 2, 3]   # equal but different object

print(a is b)           # True  — same object in memory
print(a is c)           # False — different objects
print(a == c)           # True  — same values

print(2 in  a)          # True
print(5 not in a)       # True

# --- String operators ---
print("\n=== String operators ===")
print("Hello" + " " + "World")     # concatenation
print("Ha" * 3)                    # repetition: HaHaHa
print("py" in "python")            # True
