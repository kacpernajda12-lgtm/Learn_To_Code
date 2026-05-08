# 05 - Functions

# --- Basic function ---
def greet():
    print("Hello from a function!")

greet()

# --- Parameters and return value ---
def add(a, b):
    return a + b

print(add(3, 7))        # 10

# --- Default parameters ---
def greet_user(name, greeting="Hello"):
    print(f"{greeting}, {name}!")

greet_user("Alice")                 # Hello, Alice!
greet_user("Bob", "Good morning")   # Good morning, Bob!

# --- Keyword arguments (order doesn't matter) ---
def describe(name, age, city):
    print(f"{name}, {age}, from {city}")

describe(age=30, city="Warsaw", name="Carol")

# --- *args — variable number of positional arguments ---
def total(*numbers):
    return sum(numbers)

print(total(1, 2, 3))           # 6
print(total(10, 20, 30, 40))    # 100

# --- **kwargs — variable number of keyword arguments ---
def show_info(**details):
    for key, value in details.items():
        print(f"  {key}: {value}")

show_info(name="Dave", age=25, job="developer")

# --- Combining all parameter types ---
def mixed(required, default="x", *args, **kwargs):
    print(f"required={required}, default={default}")
    print(f"args={args}")
    print(f"kwargs={kwargs}")

mixed("a", "b", 1, 2, 3, color="red", size=10)

# --- Multiple return values (returns a tuple) ---
def min_max(numbers):
    return min(numbers), max(numbers)

lo, hi = min_max([3, 1, 8, 2, 5])
print(f"min={lo}, max={hi}")

# --- Recursion ---
def factorial(n):
    if n <= 1:
        return 1
    return n * factorial(n - 1)

print(f"5! = {factorial(5)}")   # 120

# --- Type hints (Python 3.5+) — not enforced, just documentation ---
def multiply(a: int, b: int) -> int:
    return a * b

print(multiply(4, 5))

# --- Docstrings — describe what a function does ---
def celsius_to_fahrenheit(c: float) -> float:
    """Convert Celsius to Fahrenheit."""
    return c * 9/5 + 32

print(celsius_to_fahrenheit(100))   # 212.0
help(celsius_to_fahrenheit)         # prints the docstring
