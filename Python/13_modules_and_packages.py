# 13 - Modules, Packages, and the Standard Library
# A module is any .py file. A package is a folder with __init__.py.
# Python ships with a huge standard library — use it before installing anything.

# =========================================================
# IMPORTING
# =========================================================
import math                         # import whole module
from math import sqrt, pi           # import specific names
from math import factorial as fact   # alias

print(math.pow(2, 10))      # 1024.0
print(sqrt(144))             # 12.0
print(pi)                    # 3.14159...
print(fact(6))               # 720

# =========================================================
# MATH
# =========================================================
print("\n--- math ---")
print(math.floor(3.7))      # 3
print(math.ceil(3.2))       # 4
print(math.log(100, 10))    # 2.0
print(math.gcd(48, 18))     # 6
print(math.isclose(0.1+0.2, 0.3))  # True (float comparison)

# =========================================================
# RANDOM
# =========================================================
import random
print("\n--- random ---")
random.seed(42)
print(random.randint(1, 10))                # random int inclusive
print(random.choice(["a","b","c"]))         # pick one
print(random.sample(range(100), 5))         # 5 unique, no replacement
lst = [1,2,3,4,5]
random.shuffle(lst)
print(lst)

# =========================================================
# DATETIME
# =========================================================
from datetime import datetime, date, timedelta
print("\n--- datetime ---")
now  = datetime.now()
today = date.today()
print(now.strftime("%Y-%m-%d %H:%M:%S"))
print(today)

tomorrow = today + timedelta(days=1)
print(f"Tomorrow: {tomorrow}")

bday = date(1990, 6, 15)
age_days = (today - bday).days
print(f"Days since 1990-06-15: {age_days}")

# =========================================================
# COLLECTIONS
# =========================================================
from collections import Counter, defaultdict, deque, namedtuple
print("\n--- collections ---")

# Counter — count occurrences
words = "the cat sat on the mat the cat".split()
c = Counter(words)
print(c.most_common(3))     # [('the',3),('cat',2),('sat',1)]

# defaultdict — no KeyError on missing key
dd = defaultdict(list)
for word in words:
    dd[word[0]].append(word)    # group by first letter
print(dict(dd))

# deque — O(1) append/pop on both ends
dq = deque([1,2,3], maxlen=5)
dq.appendleft(0)
dq.append(4)
print(dq)

# namedtuple — lightweight struct
Point = namedtuple("Point", ["x", "y"])
p = Point(3, 4)
print(p.x, p.y)
print(p._asdict())

# =========================================================
# PATHLIB — modern file path handling
# =========================================================
from pathlib import Path
print("\n--- pathlib ---")
p = Path(".")
print(list(p.glob("*.py"))[:3])         # .py files in cwd

home = Path.home()
print(home)

new_path = home / "Documents" / "test.txt"
print(new_path.suffix)          # .txt
print(new_path.stem)            # test
print(new_path.parent)

# =========================================================
# TYPING — type hints for better code documentation
# =========================================================
from typing import Optional, Union, List, Dict, Tuple

def find_user(user_id: int) -> Optional[Dict[str, Union[str, int]]]:
    """Returns a user dict or None if not found."""
    users = {1: {"name": "Alice", "age": 30}}
    return users.get(user_id)

print("\n--- typing ---")
print(find_user(1))
print(find_user(99))

# =========================================================
# __name__ guard — code that only runs when the file is executed directly
# (not when imported as a module by another file)
# =========================================================
if __name__ == "__main__":
    print("\nRunning as main script")
