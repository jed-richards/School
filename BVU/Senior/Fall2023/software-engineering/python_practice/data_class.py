from dataclasses import dataclass

@dataclass
class Person:
    name: str
    age: int


p1 = Person("Jed", 22)
print(p1)
print(p1.name)
