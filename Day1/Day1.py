# Using readlines()
file = open('Day1/calories.txt', 'r')
Lines = file.readlines()
  
count = 0
list = list()
list.append(0)
for line in Lines:
    if(line == '\n'):
        count += 1
        list.append(0)
    else:
        list[count] += int(line)

for calories in list:
    if calories > greatestSoFar:
        greatestSoFar = calories

print(greatestSoFar)

list.sort(reverse=True)
print( list[0] + list[1] + list[2])
