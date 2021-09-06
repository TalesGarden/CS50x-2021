from cs50 import get_int

height = get_int("Height: ")

while height < 1 or height > 8:
    height = get_int("Height: ")

space = height - 1
for i in range(height):
    print(" " * space + "#" * (i + 1))
    space = space - 1