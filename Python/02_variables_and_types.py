# 02 - Variables and Types
# Python is dynamically typed — you don't declare types, Python figures them out.

# --- Basic types ---
name    = "Alice"       # str   (string)
age     = 25            # int   (integer)
height  = 1.75          # float (decimal)
is_cool = True          # bool  (True or False)
nothing = None          # NoneType — represents "no value"

print(name, age, height, is_cool, nothing)

# --- type() tells you what type a variable is ---
print(type(name))       # <class 'str'>
print(type(age))        # <class 'int'>
print(type(height))     # <class 'float'>
print(type(is_cool))    # <class 'bool'>

# --- Type conversion ---
x = "42"
print(type(x))          # str
x = int(x)              # convert to int
print(type(x), x + 1)  # int, 43

print(float(7))         # 7.0
print(str(3.14))        # "3.14"
print(bool(0))          # False  (0, "", [], None are all falsy)
print(bool(42))         # True

# --- Multiple assignment ---
a, b, c = 1, 2, 3
print(a, b, c)

x = y = z = 0           # all point to the same value
print(x, y, z)

# --- Swap without a temp variable (Python magic) ---
a, b = b, a
print(a, b)             # 2 1

# --- Constants: by convention use ALL_CAPS (Python doesn't enforce it) ---
MAX_SPEED = 300
PI        = 3.14159

# --- f-strings: the modern way to embed variables in strings ---
print(f"Name: {name}, Age: {age}, Height: {height:.2f}m")
print(f"Next year: {age + 1}")
