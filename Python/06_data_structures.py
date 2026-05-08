# 06 - Data Structures: List, Tuple, Set, Dictionary

# =========================================================
# LIST — ordered, mutable, allows duplicates
# =========================================================
print("=== LIST ===")
fruits = ["apple", "banana", "cherry"]

fruits.append("date")           # add to end
fruits.insert(1, "blueberry")   # insert at index
fruits.remove("banana")         # remove by value
popped = fruits.pop()           # remove & return last item

print(fruits)
print(f"Popped: {popped}")
print(f"Length: {len(fruits)}")
print(f"Index of cherry: {fruits.index('cherry')}")
print(f"apple count: {fruits.count('apple')}")

# Slicing [start:stop:step]
nums = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
print(nums[2:5])        # [2, 3, 4]
print(nums[:4])         # [0, 1, 2, 3]
print(nums[7:])         # [7, 8, 9]
print(nums[::2])        # every other: [0, 2, 4, 6, 8]
print(nums[::-1])       # reversed:    [9, 8, 7, ...]

# Sorting
scores = [5, 2, 8, 1, 9]
scores.sort()                           # in-place ascending
print(scores)
scores.sort(reverse=True)               # descending
print(scores)
print(sorted(scores))                   # returns new list, original unchanged

# List unpacking
a, b, *rest = [1, 2, 3, 4, 5]
print(a, b, rest)       # 1 2 [3, 4, 5]


# =========================================================
# TUPLE — ordered, IMMUTABLE (can't change after creation)
# =========================================================
print("\n=== TUPLE ===")
point = (10, 20)
x, y = point            # unpacking
print(f"x={x}, y={y}")

rgb = (255, 128, 0)
print(f"Red channel: {rgb[0]}")

# Tuples are faster than lists and safe to use as dict keys
# Single-element tuple needs a trailing comma
single = (42,)
print(type(single))     # <class 'tuple'>


# =========================================================
# SET — unordered, unique values only
# =========================================================
print("\n=== SET ===")
s = {3, 1, 4, 1, 5, 9, 2, 6, 5}    # duplicates dropped
print(s)                             # order not guaranteed

s.add(7)
s.discard(3)    # remove if present (no error if missing)
print(7 in s)   # True

a = {1, 2, 3, 4}
b = {3, 4, 5, 6}
print(a | b)    # union:        {1,2,3,4,5,6}
print(a & b)    # intersection: {3,4}
print(a - b)    # difference:   {1,2}
print(a ^ b)    # symmetric diff: {1,2,5,6}


# =========================================================
# DICTIONARY — key → value pairs (ordered since Python 3.7)
# =========================================================
print("\n=== DICTIONARY ===")
person = {
    "name": "Alice",
    "age":  30,
    "city": "Warsaw"
}

print(person["name"])                       # access by key
print(person.get("job", "unemployed"))      # safe get with default

person["email"] = "alice@example.com"       # add new key
person["age"] = 31                          # update existing key
del person["city"]                          # delete key

print(person)
print(list(person.keys()))
print(list(person.values()))
print(list(person.items()))                 # list of (key, value) tuples

# Iterating
for key, value in person.items():
    print(f"  {key}: {value}")

# Merging dicts (Python 3.9+)
defaults = {"theme": "dark", "lang": "en"}
config   = {"lang": "pl", "size": 14}
merged   = defaults | config               # config values win on conflict
print(merged)

# Nested dict
users = {
    "alice": {"age": 30, "role": "admin"},
    "bob":   {"age": 25, "role": "user"},
}
print(users["alice"]["role"])
