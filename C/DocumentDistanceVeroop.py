from math import sqrt, acos


class PorterStemmer:

    def __init__(self):
        """
        """
        self.word = ""
        self.end = 0
        self.start = 0
        self.index = 0

    def IsConsonant(self, index):
        if self.word[index] == 'a' or self.word[index] == 'e' or self.word[index] == 'i' or self.word[index] == 'o' or self.word[index] == 'u':
            return 0
        elif self.word[index] == 'y':
            # 如果这个letter是y，那么考虑，如果它是第一个字母，那么是辅音字母，否则要考虑它前一个字母是不辅音
            if index == self.start:
                return 1
            else:
                return (not self.IsConsonant(index - 1))
        return 1

    def m(self):
        """m() measures the number of consonant sequences between k0 and j.
        if c is a consonant sequence and v a vowel sequence, and <..>
        indicates arbitrary presence,
           <c><v>       gives 0
           <c>vc<v>     gives 1
           <c>vcvc<v>   gives 2
           <c>vcvcvc<v> gives 3
           ....
        """
        n = 0
        i = self.start
        while 1:
            if i > self.index:
                return n
            if not self.IsConsonant(i):
                break
            i = i + 1
        i = i + 1
        while 1:
            while 1:
                if i > self.index:
                    return n
                if self.IsConsonant(i):
                    break
                i = i + 1
            i = i + 1
            n = n + 1
            while 1:
                if i > self.index:
                    return n
                if not self.IsConsonant(i):
                    break
                i = i + 1
            i = i + 1

    def vowelinstem(self):
        """
        k0 到 j 之间，只要包含元音就return 1，否则return 0
        """
        for i in range(self.start, self.index + 1):
            if not self.IsConsonant(i):
                return 1
        return 0

    def doublec(self, j):
        """
        如果 j 和 j - 1 都是辅音字母，return 1，否则 return 0
        """
        if j < (self.start + 1):
            return 0
        if (self.word[j] != self.word[j-1]):
            return 0
        return self.IsConsonant(j)

    def cvc(self, i):
        """
        辅元辅
        """
        if i < (self.start + 2) or not self.IsConsonant(i) or self.IsConsonant(i-1) or not self.IsConsonant(i-2):
            return 0
        ch = self.word[i]
        if ch == 'w' or ch == 'x' or ch == 'y':
            return 0
        return 1

    def ends(self, s):
        """
        以字符串s格式结尾 return 1
        """
        length = len(s)
        if s[length - 1] != self.word[self.end]:  # tiny speed-up
            return 0
        if length > (self.end - self.start + 1):
            return 0
        if self.word[self.end-length+1:self.end+1] != s:
            return 0
        self.index = self.end - length
        return 1

    def setto(self, s):
        """
        """
        length = len(s)
        self.word = self.word[:self.index+1] + \
            s + self.word[self.index+length+1:]
        self.end = self.index + length

    def r(self, s):
        """
        """
        if self.m() > 0:
            self.setto(s)


    def step2(self):
        """step2() maps double suffices to single ones.
        so -ization ( = -ize plus -ation) maps to -ize etc. note that the
        string before the suffix must give m() > 0.
        """
        if self.word[self.end - 1] == 'a':
            if self.ends("ational"):
                self.r("ate")
            elif self.ends("tional"):
                self.r("tion")
        elif self.word[self.end - 1] == 'c':
            if self.ends("enci"):
                self.r("ence")
            elif self.ends("anci"):
                self.r("ance")
        elif self.word[self.end - 1] == 'e':
            if self.ends("izer"):
                self.r("ize")
        elif self.word[self.end - 1] == 'l':
            if self.ends("bli"):
                self.r("ble")  # --DEPARTURE--
            # To match the published algorithm, replace this phrase with
            #   if self.ends("abli"):      self.r("able")
            elif self.ends("alli"):
                self.r("al")
            elif self.ends("entli"):
                self.r("ent")
            elif self.ends("eli"):
                self.r("e")
            elif self.ends("ousli"):
                self.r("ous")
        elif self.word[self.end - 1] == 'o':
            if self.ends("ization"):
                self.r("ize")
            elif self.ends("ation"):
                self.r("ate")
            elif self.ends("ator"):
                self.r("ate")
        elif self.word[self.end - 1] == 's':
            if self.ends("alism"):
                self.r("al")
            elif self.ends("iveness"):
                self.r("ive")
            elif self.ends("fulness"):
                self.r("ful")
            elif self.ends("ousness"):
                self.r("ous")
        elif self.word[self.end - 1] == 't':
            if self.ends("aliti"):
                self.r("al")
            elif self.ends("iviti"):
                self.r("ive")
            elif self.ends("biliti"):
                self.r("ble")
        elif self.word[self.end - 1] == 'g':  # --DEPARTURE--
            if self.ends("logi"):
                self.r("log")
        # To match the published algorithm, delete this phrase

    def step3(self):
        """step3() dels with -ic-, -full, -ness etc. similar strategy to step2."""
        if self.word[self.end] == 'e':
            if self.ends("icate"):
                self.r("ic")
            elif self.ends("ative"):
                self.r("")
            elif self.ends("alize"):
                self.r("al")
        elif self.word[self.end] == 'i':
            if self.ends("iciti"):
                self.r("ic")
        elif self.word[self.end] == 'l':
            if self.ends("ical"):
                self.r("ic")
            elif self.ends("ful"):
                self.r("")
        elif self.word[self.end] == 's':
            if self.ends("ness"):
                self.r("")

    def step4(self):
        """step4() takes off -ant, -ence etc., in context <c>vcvc<v>."""
        if self.word[self.end - 1] == 'a':
            if self.ends("al"):
                pass
            else:
                return
        elif self.word[self.end - 1] == 'c':
            if self.ends("ance"):
                pass
            elif self.ends("ence"):
                pass
            else:
                return
        elif self.word[self.end - 1] == 'e':
            if self.ends("er"):
                pass
            else:
                return
        elif self.word[self.end - 1] == 'i':
            if self.ends("ic"):
                pass
            else:
                return
        elif self.word[self.end - 1] == 'l':
            if self.ends("able"):
                pass
            elif self.ends("ible"):
                pass
            else:
                return
        elif self.word[self.end - 1] == 'n':
            if self.ends("ant"):
                pass
            elif self.ends("ement"):
                pass
            elif self.ends("ment"):
                pass
            elif self.ends("ent"):
                pass
            else:
                return
        elif self.word[self.end - 1] == 'o':
            if self.ends("ion") and (self.word[self.j] == 's' or self.word[self.j] == 't'):
                pass
            elif self.ends("ou"):
                pass
            # takes care of -ous
            else:
                return
        elif self.word[self.end - 1] == 's':
            if self.ends("ism"):
                pass
            else:
                return
        elif self.word[self.end - 1] == 't':
            if self.ends("ate"):
                pass
            elif self.ends("iti"):
                pass
            else:
                return
        elif self.word[self.end - 1] == 'u':
            if self.ends("ous"):
                pass
            else:
                return
        elif self.word[self.end - 1] == 'v':
            if self.ends("ive"):
                pass
            else:
                return
        elif self.word[self.end - 1] == 'z':
            if self.ends("ize"):
                pass
            else:
                return
        else:
            return
        if self.m() > 1:
            self.end = self.j

    def step5(self):
        """step5() removes a final -e if m() > 1, and changes -ll to -l if
        m() > 1.
        """
        self.j = self.end
        if self.word[self.end] == 'e':
            a = self.m()
            if a > 1 or (a == 1 and not self.cvc(self.end-1)):
                self.end = self.end - 1
        if self.word[self.end] == 'l' and self.doublec(self.end) and self.m() > 1:
            self.end = self.end - 1

    def stem(self, word):
        """
        """
        # copy the parameters into statics
        self.word = word
        self.end = len(word) - 1
        self.start = 0

        if self.end <= self.start + 1:
            return self.word  # --DEPARTURE--
        if self.word[self.end] == 's':
            if self.ends("sses"):
                self.end = self.end - 2
            elif self.ends("ies"):
                self.setto("i")
            elif self.word[self.end - 1] != 's':
                self.end = self.end - 1
        if self.ends("eed"):
            if self.m() > 0:
                self.end = self.end - 1
        elif (self.ends("ed") or self.ends("ing")) and self.vowelinstem():
            self.end = self.index
            if self.ends("at"):
                self.setto("ate")
            elif self.ends("bl"):
                self.setto("ble")
            elif self.ends("iz"):
                self.setto("ize")
            elif self.doublec(self.end):
                self.end = self.end - 1
                ch = self.word[self.end]
                if ch == 'l' or ch == 's' or ch == 'z':
                    self.end = self.end + 1
            elif (self.m() == 1 and self.cvc(self.end)):
                self.setto("e")

        if (self.ends("y") and self.vowelinstem()):
            self.word = self.word[:self.end] + 'i' + self.word[self.end+1:]

        self.step2()
        self.step3()
        self.step4()
        self.step5()

        return self.word[self.start:self.end+1]


class document:
    def __init__(self):
        """
        初始化参数
        name 储存名字
        word 储存文档的所有单词经过处理后组成的列表（存在重复）
        vector 返回单词：频数 的字典
        """
        self.name = self.ReadName()
        self.word = self.ReadWord()
        self.Vector = self.CalVector()

    def ReadName(self):
        """
        读入名字
        """
        return input()

    def ReadWord(self):
        """
        读入文档的单词并处理
        """
        # 读入字符串并拼接
        word = ""
        while True:
            string = input()
            if string == '#':
                break
            else:
                word += string + ' '
        # 处理stop,将结果转换成小写，并处理es, ies , ed ,ing 等特殊情况
        word_list = []
        i = 0
        while i < len(word):
            if word[i].isalnum():
                j = i
                while j < len(word):
                    if word[j].isalnum():
                        j += 1
                    else:
                        break
                changed_word = self.ChangeWord(word[i:j])
                word_list.append(changed_word)
                # if changed_word not in word_read:
                #     word_read.append(changed_word)
                i = j+1
            else:
                i += 1
        # 返回由纯单词组成的列表
        return word_list

    def ChangeWord(self, word):
        """
        将字母全部小写，并利用porterstemmer方式提取出词干
        """
        p = PorterStemmer()
        # 先全部改成小写字母，再进行词干提取
        return p.stem(word.lower())

    def CalVector(self):
        """
        计算 {单词：频数} 
        返回一个字典
        """
        vector = {}
        for thisword in self.word:
            if thisword in vector:
                vector[thisword] += 1
            else:
                vector[thisword] = 1
        return vector

    def DisplayVector(self):
        print("Vector = ", self.Vector)

    def DisplayName(self):
        print("Name = ", self.name)

    def DisplayWord(self):
        print("word = ", self.word)


def cal_inner_product(doc1, doc2):
    sum = 0
    # for i in range(len(doc1.Vector)):
    #     for j in range(len(doc2.Vector)):
    #         if doc1.Vector[i][0] == doc2.Vector[j][0]:
    #             sum += doc1.Vector[i][1] * doc2.Vector[j][1]
    #             break
    for thisword in doc1.Vector:
        if thisword in doc2.Vector:
            sum += doc1.Vector[thisword] * doc2.Vector[thisword]
    return sum


def cal_angle(doc1, doc2):
    return acos(cal_inner_product(doc1, doc2)/sqrt(cal_inner_product(doc1, doc1)*cal_inner_product(doc2, doc2)))


N = int(input())
documents = []
names = []
for i in range(N):
    NewDocument = document()
    # NewDocument.DisplayName()
    # NewDocument.DisplayWord()
    # NewDocument.DisplayVector()
    documents.append(NewDocument)

M = int(input())
for i in range(M):
    name1, name2 = input().split()
    for thisdoc in documents:
        if thisdoc.name == name1:
            doc1 = thisdoc
        if thisdoc.name == name2:
            doc2 = thisdoc

    print("Case {:}:".format(i+1),
          "{:.3f}".format(cal_angle(doc1, doc2)))
