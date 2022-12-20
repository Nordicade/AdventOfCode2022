# Using readlines()
file = open('Day10/input.txt', 'r')
Lines = file.readlines()
queue = []
screen = []

for i in range(6):
    row = []
    for j in range(40):
        row.append('.')
    screen.append(row)

X = 1
for line in Lines:
    print(line)
    if line.startswith("noop"):
        queue.append(X)
    if line.startswith("addx"):
        queue.append(X)
        queue.append(X)
        number = line.split(" ")[1]
        print(number)
        X = X + int(number)
print("- - -")
index = 0
for val in queue:
    index = index + 1
    print(str(index) + " : " + str(val))


# THE FOLLOWING CODE IS ONLY USED FOR PHASE 2
count = 0

for rowIndex in range(len(screen)):
    for pixelIndex in range(len(screen[rowIndex])):
        if pixelIndex + (rowIndex * 40) == 40:
            print(str(pixelIndex + (rowIndex * 40)) + "th pixel printed, debug " + str(queue[pixelIndex]) + " at cycle " + str(pixelIndex))
        if queue[pixelIndex + (rowIndex * 40)] == count % 40 or queue[pixelIndex + (rowIndex * 40)] + 1 == count % 40 or queue[pixelIndex + (rowIndex * 40)] - 1 == count % 40:
            print(str(pixelIndex + (rowIndex * 40)) + "th pixel printed, since " + str(queue[pixelIndex]) + " at cycle " + str(pixelIndex))
            screen[rowIndex][pixelIndex] = "#"
        count = count + 1

    #         for row in screen:
    # print(row)

with open("Day10/output.txt", "w") as f:
  for row in screen:
      for pixel in row:
        f.write(pixel)
      f.write("\n")
# THE FOLLOWING CODE IS ONLY USED FOR PHASE 1    
# print("Signal strengths")
# print(str(20) + " : " + str(queue[20]))
# twenty = 20 * queue[19]
# print(str(60) + " : " + str(queue[60]))
# sixty = 60 * queue[59]
# print(str(100) + " : " + str(queue[100]))
# hundred = 100 * queue[99]
# print(str(140) + " : " + str(queue[140]))
# oneforty = 140 * queue[139]
# print(str(180) + " : " + str(queue[180]))
# oneeighty = 180 * queue[179]
# print(str(220) + " : " + str(queue[220]))
# twotwenty = 220 * queue[219]

# sumSignalStrength = twenty + sixty + hundred + oneforty + oneeighty + twotwenty
# print("Final Answer")
# print(sumSignalStrength)