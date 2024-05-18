from enum import Enum, auto

# Define an enumeration class using the Enum base class
class Color(Enum):
    RED = 1
    GREEN = 2
    BLUE = 3

# Access enumeration members
print(Color.RED)        # Color.RED
print(Color.RED.name)   # 'RED'
print(Color.RED.value)  # 1

# Iterate over enumeration members
for color in Color:
    print(color)

# Use Enum.auto() to automatically assign unique values
class Direction(Enum):
    NORTH = auto()
    SOUTH = auto()
    EAST = auto()
    WEST = auto()

# Access enumeration members
print(Direction.NORTH)        # Direction.NORTH
print(Direction.NORTH.name)   # 'NORTH'
print(Direction.NORTH.value)  # 1

# Iterate over enumeration members
for direction in Direction:
    print(direction)

