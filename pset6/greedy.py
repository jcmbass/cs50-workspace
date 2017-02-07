import cs50

while True:
    owed = cs50.get_float()
    if owed > 0:
        break
    
quarter = 25
dime = 10
nickles = 5
pennies = 1
counter = 0

owed *= 100

change = round(owed)

while (change >= 25):
    change = change - quarter
    counter = counter + 1
    
while (change >= 10):
    change = change - dime
    counter = counter + 1

while (change >= 5):
    change = change - nickles
    counter = counter + 1

while (change >= 1):
    change = change - pennies
    counter = counter +1
    
print(counter)