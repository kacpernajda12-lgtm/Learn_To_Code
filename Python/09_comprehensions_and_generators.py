# 09 - Comprehensions and Generators
# Comprehensions are concise ways to build collections.
# Generators produce values one at a time — memory efficient.

# =========================================================
# LIST COMPREHENSIONS
# Syntax: [expression for item in iterable if condition]
# =========================================================
print("=== List comprehensions ===")

squares = [x**2 for x in range(1, 11)]
print(squares)

evens = [x for x in range(20) if x % 2 == 0]
print(evens)

# Nested comprehension (flattens a 2D list)
matrix = [[1,2,3],[4,5,6],[7,8,9]]
flat = [n for row in matrix for n in row]
print(flat)

# Transform strings
words = ["hello", "WORLD", "Python"]
normalized = [w.lower().strip() for w in words]
print(normalized)


# =========================================================
# DICT AND SET COMPREHENSIONS
# =========================================================
print("\n=== Dict / Set comprehensions ===")

word_lengths = {w: len(w) for w in ["apple", "banana", "cherry"]}
print(word_lengths)

# Invert a dictionary
original = {"a": 1, "b": 2, "c": 3}
inverted = {v: k for k, v in original.items()}
print(inverted)

unique_squares = {x**2 for x in [-2, -1, 0, 1, 2]}
print(unique_squares)   # {0, 1, 4} — duplicates removed


# =========================================================
# GENERATOR EXPRESSIONS — like list comp but lazy (no list built)
# =========================================================
print("\n=== Generator expressions ===")

# Wrap in () instead of []
gen = (x**2 for x in range(10))
print(gen)                  # <generator object ...>
print(next(gen))            # 0
print(next(gen))            # 1
print(list(gen))            # [4, 9, 16, ...] — rest of the values

# Memory advantage: sum of 1 million squares without building a list
total = sum(x**2 for x in range(1_000_000))
print(f"Sum of squares: {total}")


# =========================================================
# GENERATOR FUNCTIONS — use yield instead of return
# =========================================================
print("\n=== Generator functions ===")

def countdown(n):
    while n > 0:
        yield n             # pause here, return n, resume next call
        n -= 1
    yield "Go!"

for value in countdown(5):
    print(value, end=" ")
print()

# Infinite generator — only safe with break or islice
def integers_from(n):
    while True:
        yield n
        n += 1

from itertools import islice
first_10 = list(islice(integers_from(1), 10))
print(first_10)

# yield from — delegate to another generator
def chain_gen(*iterables):
    for it in iterables:
        yield from it

print(list(chain_gen([1,2], [3,4], [5,6])))


# =========================================================
# ITERTOOLS — powerful tools for iterators
# =========================================================
print("\n=== itertools ===")
import itertools

# product — cartesian product
for pair in itertools.product([1,2], ["a","b"]):
    print(pair, end=" ")
print()

# combinations
print(list(itertools.combinations("ABCD", 2)))

# permutations
print(list(itertools.permutations([1,2,3])))

# groupby
data = sorted([("fruit","apple"),("veg","carrot"),("fruit","banana"),("veg","pea")],
              key=lambda x: x[0])
for key, group in itertools.groupby(data, key=lambda x: x[0]):
    print(key, list(g[1] for g in group))

# accumulate — running total
import itertools
print(list(itertools.accumulate([1,2,3,4,5])))  # [1, 3, 6, 10, 15]
