import cs50

while True:
    print("Height: ", end="")
    Height = cs50.get_int()
    if Height > 0 and Height < 23:
        break
    
n = Height

for i in range(n):
    print(" "*(Height - 1), end="")
    print("#"*(2+i), end="")
    print(" ", end="")
    print("#"*(2+i))
    Height = Height-1
    
    