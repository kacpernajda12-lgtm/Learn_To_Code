# 11 - File I/O
# Always use 'with' — it closes the file automatically even if an error occurs.

import os
import json
import csv

# =========================================================
# WRITE and READ text files
# =========================================================
path = "sample.txt"

# Write (creates or overwrites)
with open(path, "w", encoding="utf-8") as f:
    f.write("Line 1\n")
    f.write("Line 2\n")
    f.writelines(["Line 3\n", "Line 4\n"])

print("Written sample.txt")

# Read entire file at once
with open(path, "r", encoding="utf-8") as f:
    content = f.read()
print(content)

# Read line by line (memory efficient for large files)
with open(path, "r", encoding="utf-8") as f:
    for line in f:
        print(line.strip())

# Read all lines into a list
with open(path, "r", encoding="utf-8") as f:
    lines = f.readlines()
print(f"Total lines: {len(lines)}")

# Append to an existing file
with open(path, "a", encoding="utf-8") as f:
    f.write("Line 5 (appended)\n")


# =========================================================
# CSV
# =========================================================
csv_path = "students.csv"

students = [
    {"name": "Alice", "age": 20, "grade": 9.2},
    {"name": "Bob",   "age": 22, "grade": 7.8},
    {"name": "Carol", "age": 21, "grade": 8.5},
]

# Write CSV
with open(csv_path, "w", newline="", encoding="utf-8") as f:
    writer = csv.DictWriter(f, fieldnames=["name", "age", "grade"])
    writer.writeheader()
    writer.writerows(students)

# Read CSV
print("\n--- CSV ---")
with open(csv_path, "r", encoding="utf-8") as f:
    reader = csv.DictReader(f)
    for row in reader:
        print(dict(row))


# =========================================================
# JSON
# =========================================================
json_path = "config.json"

config = {
    "app": "LearnCode",
    "version": 1,
    "features": ["c++", "python"],
    "settings": {"dark_mode": True, "font_size": 14}
}

# Write JSON
with open(json_path, "w", encoding="utf-8") as f:
    json.dump(config, f, indent=2)

# Read JSON
with open(json_path, "r", encoding="utf-8") as f:
    loaded = json.load(f)

print("\n--- JSON ---")
print(loaded["app"])
print(loaded["settings"]["font_size"])

# JSON ↔ string (without files)
json_str = json.dumps(config, indent=2)    # dict → string
back     = json.loads(json_str)            # string → dict
print(back["version"])


# =========================================================
# OS MODULE — file/directory operations
# =========================================================
print("\n--- os module ---")
print(os.getcwd())                                  # current directory
print(os.path.exists(path))                         # True
print(os.path.basename(path))                       # sample.txt
print(os.path.splitext(path))                       # ('sample', '.txt')
print(os.path.getsize(path), "bytes")

# List directory contents
files = [f for f in os.listdir(".") if os.path.isfile(f)]
print(f"Files in cwd: {files}")

# Cleanup
for f in [path, csv_path, json_path]:
    if os.path.exists(f):
        os.remove(f)
print("Temp files removed.")
