# Using readlines()
file = open('Day6/signal.txt', 'r')
Lines = file.readlines()

startingIndex = 0
solutionNotFound = True

def isUnique(fragment):
    dict = {}
    for letter in fragment:
        if letter in dict:
            return False
        dict[letter] = True
    return True

for line in Lines:
    print(line)
    while(solutionNotFound):
        if isUnique(line[startingIndex : startingIndex + 14]):
            print(startingIndex + 14)
            exit(0)
        startingIndex = startingIndex + 1