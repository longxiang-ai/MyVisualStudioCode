string = input()
output = ''


def isdigit(char):
    if char >= '0' and char <= '9':
        return 1
    else:
        return 0


for i in range(len(string)):
    if isdigit(string[i]):
        output += string[i]
print(int(output))
