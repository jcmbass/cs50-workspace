import cs50
import sys


if len(sys.argv) != 2:
    print("missing command-line argument")
    exit(1)

else:
    print("s: ", end="")
    s = cs50.get_string()
    if s == None:
        exit(1)
        
    for i in range(len(s)):
        if(s[i].isalpha()):
            if(s[i].isupper()):
                c = chr(((abs(ord('A') - ord(s[i])) + int(sys.argv[1])) % 26) + ord('A'))
                print(c, end="")
            elif(s[i].islower()):
                c = chr(((abs(ord('a') - ord(s[i])) + int(sys.argv[1])) % 26) + ord('a'))
                print(c, end="")
            else:
                print("{}".format(s[i]))
    print()
    exit(0)