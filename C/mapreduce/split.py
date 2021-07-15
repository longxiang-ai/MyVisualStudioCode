n = 3
for i in range(1, n+1):
    path = 'C\\mapreduce\\test' + str(i) + '.txt'
    f = open(path, 'r')
    string = f.read()
    # print(string)
    words = ''.join([i.lower()
                     for i in string if i.isalpha() or i.isspace()]).split()

    # print(words)
    words.sort(key=None, reverse=False)
    # print(words)
    dic = {}
    for _ in words:
        if _ in dic:
            dic[_] += 1
        else:
            dic[_] = 1
    # print(dic)
    a = sorted(dic.items(), key=lambda asd: asd[1], reverse=True)
    # print(dic)
    out = open('C\\mapreduce\\result' + str(i) + '.txt', 'w+')
    out.write(str(a))
    out.close()
