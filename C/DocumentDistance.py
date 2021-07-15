from math import sqrt, acos


class document:
    def __init__(self):
        self.name = self.ReadName()
        self.word = self.ReadWord()

    def ReadName(self):
        return input()

    def ReadWord(self):
        word = ""
        while True:
            string = input()
            if string == '#':
                break
            else:
                word += string
        return word

    def DisplayName(self):
        print(self.name)

    def DisplayWord(self):
        print(self.word)


def change_word(word_list):
    word_list_changed = []
    for word in word_list:
        count = 0
        new_word = word.lower()
        if len(word) > 3:
            if word[-3:].lower() == "ies" or word[-3:].lower() == "ing":
                new_word = word[:-3]
                count += 1
        if len(word) > 2 and count == 0:
            if word[-2:].lower() == "es" or word[-2:].lower() == "ed":
                new_word = word[:-2]
        word_list_changed.append(new_word.lower())
    return word_list_changed


N = int(input())
# name = []
# words = []
documents = []
for i in range(N):
    NewDocument = document()
    NewDocument.DisplayName()
    NewDocument.DisplayWord()
    # name.append(input())
    # word = []
    # word = ReadWord()
    # wordfrequency = []
    # while True:
    #     string = input().split(" ")
    #     if string != ["#"]:
    #         word.extend(string)
    #     else:
    #         break
    # # print(word)
    # word = change_word(word)
    # # print(word)
    # word_read = []
    # for thisword in word:
    #     if(thisword not in word_read):
    #         wordfrequency.append([thisword, word.count(thisword)])
    #         word_read.append(thisword)
    # # print(wordfrequency)
    # words.append(wordfrequency)
# print(words)


def word_list(words):
    this_word_list = []
    for i in range(len(words)):
        this_word_list.append(words[i][0])
    return this_word_list


def frequency_list(words):
    this_fre_list = []
    for i in range(len(words)):
        this_fre_list.append(words[i][1])
    return this_fre_list


def cal_inner_product(vecter1, vecter2):
    sum = 0
    for i in range(len(word_list(vecter1))):
        if word_list(vecter1)[i] in word_list(vecter2):
            sum += frequency_list(vecter1)[i] * frequency_list(vecter2)[i]
    return sum


def cal_angle(vecter1, vecter2):
    return acos(cal_inner_product(vecter1, vecter2)/sqrt(cal_inner_product(vecter1, vecter1)*cal_inner_product(vecter2, vecter2)))


def find_index(name, names):
    for thisname in names:
        if thisname == name:
            return names.index(name)


if N != 0:
    M = int(input())
    for i in range(M):
        namein = input().split(" ")
        index1 = find_index(namein[0], name)
        index2 = find_index(namein[1], name)
        # print(name1, index1)
        # print(name2, index2)
        # print(cal_inner_product(words[index1],words[index2]))
        # print(cal_angle(words[index1],words[index2]))
        print("Case {:}:".format(i+1),
              "{:.3f}".format(cal_angle(words[index1], words[index2])))
