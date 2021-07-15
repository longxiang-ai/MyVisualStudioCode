s = input()
string = ''


def ishex(char):
    if char >= '0' and char <= '9' or char >= 'A' and char <= 'F' or char >= 'a' and char <= 'f' or char == '-':
        return True
    else:
        return False


for i in range(len(s)):
    if(ishex(s[i])):
        string += s[i]

out = ''
if s[0] != '#':
    if string[0] == '-':
        out += '-'
    for i in range(len(string)):
        if string[i] != '-':
            out += string[i]
    print(int(out, 16))
else:
    print('0')
