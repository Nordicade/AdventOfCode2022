# Using readlines()
file = open('Day5/cargo.txt', 'r')
lines = file.readlines()
dict = {}

for i in range(9):
    dict[i] = ''

count = 0
for line in lines:
    if(count < 8):
        modifiedLine = ''
        line = line.replace('[', '').replace(']', '').replace('\n', '')
        for i in range(len(line)):
            if i % 2 == 0:
                modifiedLine = modifiedLine + line[i]
        modifiedLine = modifiedLine.replace('  ', ' ')
        # modifiedLine = line.replace('[', '').replace(']', '').replace('\n', '').replace('     ', ' _ ').split(" ")

        # we are starting from teh top of the list of items
        # to reflect that, we will push to the front of the list,
        # so if we hear "move 2 from 1"
        # we will take the front two items of the string instead of back
        for i in range(9):
            print(modifiedLine)
            dict[i] =  modifiedLine[i] + dict[i]
            print(dict)
    elif (count == 8 or count == 9):
        print('---')
        for i in range(9):
            dict[i] = dict[i].strip()
            print(dict[i])
    else:
        # TODO VALUES ARE OFF BY 1, EITHER REANGE 1,10 OR INCREMENT WHEN READING
        # parse moves
        modifiedLine = line.replace("move ", '').replace(" from ",",").replace(" to ",",").replace('\n','').split(',')
        for index in range(1, len(modifiedLine)):
            modifiedLine[index] = int(modifiedLine[index]) - 1
        movedString = ''
        print(modifiedLine)
        # substring so we know what we are moving
        movedStringStart = len(dict[modifiedLine[1]]) - (int(modifiedLine[0]))
        movedString = dict[int(modifiedLine[1])][movedStringStart:len(dict[modifiedLine[1]])]
        print("This is the stack before we modify")
        print(dict[int(modifiedLine[1])])
        print("This is the soon to be moved portion")
        print(movedString)
        # substring and store the untouched string into the dict at modifiedLine[1]
        replacedString = dict[int(modifiedLine[1])][0:movedStringStart]
        print("this is what we are storing into the stakc we are removing from")
        print(replacedString)
        dict[int(modifiedLine[1])] = replacedString
        # prepend the movedString to dict[int(modifiedLine[2]]
        print("this is the stack we are placing on top of before we do so")
        print(dict[int(modifiedLine[2])])
        dict[int(modifiedLine[2])] = dict[int(modifiedLine[2])] + movedString
        print("this is the stack after we've added the modified string to it")
        print(dict[int(modifiedLine[2])])
        print("finished")
        print(dict)
        print(count)
        
    count = count + 1
print(dict)
print(" <><><><><>< ")
for i in range(9):
    print(dict[i][len(dict[i]) - 1:len(dict[i])])