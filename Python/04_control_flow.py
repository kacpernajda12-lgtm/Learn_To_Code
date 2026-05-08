# 04 - Control Flow

# =========================================================
# IF / ELIF / ELSE
# =========================================================
temperature = 22

if temperature > 30:
    print("Hot outside")
elif temperature > 15:
    print("Nice weather")       # <-- this runs
else:
    print("Cold outside")

# One-liner (ternary)
weather = "warm" if temperature > 20 else "cool"
print(f"It's {weather}")

# Chained comparisons — unique Python feature
age = 25
if 18 <= age < 65:
    print("Working age")


# =========================================================
# MATCH / CASE (Python 3.10+) — like switch
# =========================================================
day = 3

match day:
    case 1: print("Monday")
    case 2: print("Tuesday")
    case 3: print("Wednesday")  # <-- runs
    case 6 | 7: print("Weekend")
    case _: print("Unknown")    # default


# =========================================================
# WHILE loop
# =========================================================
print("\nWhile loop:")
i = 1
while i <= 5:
    print(i, end=" ")
    i += 1
print()

# while with else — runs when condition becomes False (not on break)
n = 3
while n > 0:
    print(n, end=" ")
    n -= 1
else:
    print("-> done")


# =========================================================
# FOR loop — iterates over any iterable
# =========================================================
print("\nFor loop over a list:")
fruits = ["apple", "banana", "cherry"]
for fruit in fruits:
    print(fruit)

# range(start, stop, step)
print("\nrange(1, 10, 2):", end=" ")
for n in range(1, 10, 2):
    print(n, end=" ")
print()

# enumerate — gives index + value
print("\nenumerate:")
for i, fruit in enumerate(fruits, start=1):
    print(f"{i}. {fruit}")

# zip — iterate two lists in parallel
prices = [0.5, 0.3, 0.8]
print("\nzip:")
for fruit, price in zip(fruits, prices):
    print(f"{fruit}: ${price}")


# =========================================================
# BREAK, CONTINUE, ELSE on for
# =========================================================
print("\nBreak at 4:")
for n in range(1, 10):
    if n == 4:
        break
    print(n, end=" ")
print()

print("Skip evens:")
for n in range(1, 10):
    if n % 2 == 0:
        continue
    print(n, end=" ")
print()

# for-else: else block runs only if loop was NOT broken out of
print("\nfor-else (looking for 99):")
for n in [1, 2, 3, 4]:
    if n == 99:
        print("Found 99")
        break
else:
    print("99 not found")
