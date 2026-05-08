# 12 - Exception Handling

# =========================================================
# BASIC TRY / EXCEPT
# =========================================================
try:
    result = 10 / 0
except ZeroDivisionError:
    print("Cannot divide by zero")

# Multiple except blocks
def parse_number(s):
    try:
        return int(s)
    except ValueError:
        print(f"'{s}' is not a valid number")
    except TypeError:
        print("Expected a string")
    return None

parse_number("42")      # works
parse_number("hello")   # ValueError
parse_number(None)      # TypeError


# =========================================================
# ELSE and FINALLY
# else  — runs only if NO exception was raised
# finally — runs ALWAYS (cleanup)
# =========================================================
def read_file(path):
    try:
        with open(path) as f:
            data = f.read()
    except FileNotFoundError:
        print(f"File not found: {path}")
        return None
    else:
        print(f"Read {len(data)} chars")     # only if open() succeeded
        return data
    finally:
        print("read_file() finished")        # always runs

read_file("nofile.txt")


# =========================================================
# CATCHING MULTIPLE EXCEPTIONS IN ONE LINE
# =========================================================
def safe_divide(a, b):
    try:
        return a / b
    except (ZeroDivisionError, TypeError) as e:
        print(f"Error: {e}")
        return None

safe_divide(10, 0)
safe_divide(10, "x")


# =========================================================
# CUSTOM EXCEPTIONS
# =========================================================
class AppError(Exception):
    """Base class for application errors."""

class ValidationError(AppError):
    def __init__(self, field, message):
        self.field   = field
        super().__init__(f"Validation failed on '{field}': {message}")

class NetworkError(AppError):
    def __init__(self, url, status_code):
        self.status_code = status_code
        super().__init__(f"HTTP {status_code} for {url}")

def validate_age(age):
    if not isinstance(age, int):
        raise ValidationError("age", "must be an integer")
    if age < 0 or age > 150:
        raise ValidationError("age", f"{age} is out of range")
    return age

try:
    validate_age(-5)
except ValidationError as e:
    print(e)
    print(f"Field: {e.field}")


# =========================================================
# RE-RAISE and EXCEPTION CHAINING
# =========================================================
def fetch(url):
    raise ConnectionError("timeout")

def get_user(user_id):
    try:
        fetch(f"/users/{user_id}")
    except ConnectionError as e:
        raise NetworkError(f"/users/{user_id}", 503) from e  # chains the cause

try:
    get_user(1)
except NetworkError as e:
    print(e)
    print(f"Caused by: {e.__cause__}")


# =========================================================
# CONTEXT MANAGERS with exception handling
# =========================================================
class ManagedResource:
    def __enter__(self):
        print("Resource acquired")
        return self

    def __exit__(self, exc_type, exc_val, exc_tb):
        print("Resource released")
        if exc_type is ValueError:
            print(f"Suppressing ValueError: {exc_val}")
            return True         # True suppresses the exception
        return False            # False re-raises it

with ManagedResource() as r:
    print("Using resource")
    raise ValueError("something went wrong")    # suppressed by __exit__

print("Execution continues after suppressed exception")
