# 10 - Decorators
# A decorator wraps a function to add behaviour before/after it runs.
# Syntax: @decorator above a function definition.

import time
import functools

# =========================================================
# HOW DECORATORS WORK — from scratch
# =========================================================

def my_decorator(func):
    @functools.wraps(func)      # preserves the original function's name/docstring
    def wrapper(*args, **kwargs):
        print(f"[Before] calling {func.__name__}")
        result = func(*args, **kwargs)
        print(f"[After]  calling {func.__name__}")
        return result
    return wrapper

@my_decorator
def say_hello():
    print("Hello!")

say_hello()
# @my_decorator is equivalent to: say_hello = my_decorator(say_hello)


# =========================================================
# PRACTICAL DECORATOR: timer
# =========================================================
def timer(func):
    @functools.wraps(func)
    def wrapper(*args, **kwargs):
        start  = time.perf_counter()
        result = func(*args, **kwargs)
        end    = time.perf_counter()
        print(f"{func.__name__} took {end - start:.4f}s")
        return result
    return wrapper

@timer
def slow_sum(n):
    return sum(range(n))

print(slow_sum(1_000_000))


# =========================================================
# PRACTICAL DECORATOR: retry on exception
# =========================================================
def retry(times=3, exceptions=(Exception,)):
    def decorator(func):
        @functools.wraps(func)
        def wrapper(*args, **kwargs):
            for attempt in range(1, times + 1):
                try:
                    return func(*args, **kwargs)
                except exceptions as e:
                    print(f"Attempt {attempt} failed: {e}")
            raise RuntimeError(f"{func.__name__} failed after {times} retries")
        return wrapper
    return decorator

import random
@retry(times=5, exceptions=(ValueError,))
def flaky():
    if random.random() < 0.7:
        raise ValueError("random failure")
    return "success"

try:
    print(flaky())
except RuntimeError as e:
    print(e)


# =========================================================
# PRACTICAL DECORATOR: cache / memoize
# =========================================================
def memoize(func):
    cache = {}
    @functools.wraps(func)
    def wrapper(*args):
        if args not in cache:
            cache[args] = func(*args)
        return cache[args]
    return wrapper

@memoize
def fibonacci(n):
    if n < 2:
        return n
    return fibonacci(n-1) + fibonacci(n-2)

print([fibonacci(n) for n in range(10)])

# Python ships functools.lru_cache which does the same thing
from functools import lru_cache

@lru_cache(maxsize=128)
def fib2(n):
    if n < 2: return n
    return fib2(n-1) + fib2(n-2)

print(fib2(50))


# =========================================================
# STACKING DECORATORS (applied bottom-up)
# =========================================================
def bold(func):
    @functools.wraps(func)
    def wrapper(*args, **kwargs):
        return "**" + func(*args, **kwargs) + "**"
    return wrapper

def italic(func):
    @functools.wraps(func)
    def wrapper(*args, **kwargs):
        return "_" + func(*args, **kwargs) + "_"
    return wrapper

@bold
@italic
def headline(text):
    return text

print(headline("Python"))   # **_Python_**


# =========================================================
# CLASS-BASED DECORATOR
# =========================================================
class CountCalls:
    def __init__(self, func):
        functools.update_wrapper(self, func)
        self.func  = func
        self.count = 0

    def __call__(self, *args, **kwargs):
        self.count += 1
        print(f"{self.func.__name__} called {self.count} time(s)")
        return self.func(*args, **kwargs)

@CountCalls
def greet(name):
    print(f"Hi, {name}!")

greet("Alice")
greet("Bob")
greet("Carol")
