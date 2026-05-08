# 08 - Classes and Object-Oriented Programming (OOP)

# =========================================================
# BASE CLASS
# =========================================================
class Animal:
    # Class variable — shared by ALL instances
    kingdom = "Animalia"

    def __init__(self, name: str, age: int):
        # Instance variables — unique to each object
        self.name = name
        self.age  = age

    # Regular method — receives the instance as 'self'
    def speak(self) -> str:
        return f"{self.name} makes a sound"

    # __str__ — called by print() and str()
    def __str__(self) -> str:
        return f"Animal(name={self.name}, age={self.age})"

    # __repr__ — unambiguous representation (for debugging)
    def __repr__(self) -> str:
        return f"Animal({self.name!r}, {self.age!r})"

    @classmethod
    def create_unknown(cls):
        """Factory: create an Animal with unknown details."""
        return cls("Unknown", 0)

    @staticmethod
    def is_valid_age(age: int) -> bool:
        """No access to instance or class — pure utility."""
        return age >= 0


# =========================================================
# INHERITANCE
# =========================================================
class Dog(Animal):
    def __init__(self, name: str, age: int, breed: str):
        super().__init__(name, age)     # call parent __init__
        self.breed = breed

    def speak(self) -> str:             # override parent method
        return f"{self.name} says: Woof!"

    def fetch(self, item: str) -> str:
        return f"{self.name} fetches the {item}!"

class Cat(Animal):
    def speak(self) -> str:
        return f"{self.name} says: Meow!"


# =========================================================
# ENCAPSULATION — private / protected conventions
# =========================================================
class BankAccount:
    def __init__(self, owner: str, balance: float = 0.0):
        self.owner    = owner
        self._balance = balance     # _single  = "protected" (convention)
        self.__secret = "12345"     # __double = name-mangled (harder to access)

    @property
    def balance(self) -> float:     # getter — access like an attribute
        return self._balance

    @balance.setter
    def balance(self, amount: float):   # setter — validate before assigning
        if amount < 0:
            raise ValueError("Balance cannot be negative")
        self._balance = amount

    def deposit(self, amount: float):
        self._balance += amount
        return self

    def withdraw(self, amount: float):
        if amount > self._balance:
            raise ValueError("Insufficient funds")
        self._balance -= amount
        return self

    def __str__(self):
        return f"Account({self.owner}, ${self._balance:.2f})"


# =========================================================
# SPECIAL (DUNDER) METHODS — make objects behave like builtins
# =========================================================
class Vector:
    def __init__(self, x: float, y: float):
        self.x = x
        self.y = y

    def __add__(self, other):       # v1 + v2
        return Vector(self.x + other.x, self.y + other.y)

    def __mul__(self, scalar):      # v * 3
        return Vector(self.x * scalar, self.y * scalar)

    def __len__(self):              # len(v)
        return 2

    def __eq__(self, other):        # v1 == v2
        return self.x == other.x and self.y == other.y

    def __str__(self):
        return f"Vector({self.x}, {self.y})"


# =========================================================
if __name__ == "__main__":
    # Basic class usage
    dog = Dog("Rex", 3, "Labrador")
    cat = Cat("Whiskers", 5)

    print(dog)
    print(dog.speak())
    print(cat.speak())
    print(dog.fetch("ball"))
    print(f"Kingdom: {Dog.kingdom}")    # class variable

    # Polymorphism — treat all animals the same way
    print("\n--- Polymorphism ---")
    animals = [dog, cat, Animal.create_unknown()]
    for animal in animals:
        print(animal.speak())

    # isinstance check
    print(isinstance(dog, Animal))  # True — Dog IS-A Animal
    print(isinstance(dog, Cat))     # False

    # Encapsulation
    print("\n--- BankAccount ---")
    acc = BankAccount("Alice", 1000)
    acc.deposit(500).withdraw(200)  # method chaining
    print(acc)
    print(f"Balance: {acc.balance}")

    try:
        acc.balance = -100          # triggers setter validation
    except ValueError as e:
        print(f"Error: {e}")

    # Dunder methods
    print("\n--- Vector ---")
    v1 = Vector(1, 2)
    v2 = Vector(3, 4)
    print(v1 + v2)          # Vector(4, 6)
    print(v1 * 3)           # Vector(3, 6)
    print(v1 == Vector(1,2))# True
    print(len(v1))          # 2
