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
        """cvc(i) is TRUE <=> i-2,i-1,i has the form consonant - vowel - consonant
        and also if the second c is not w,x or y. this is used when trying to
        restore an e at the end of a short  e.g.
           cav(e), lov(e), hop(e), crim(e), but
           snow, box, tray.
        """
        if i < (self.start + 2) or not self.IsConsonant(i) or self.IsConsonant(i-1) or not self.IsConsonant(i-2):
            return 0
        ch = self.word[i]
        if ch == 'w' or ch == 'x' or ch == 'y':
            return 0
        return 1

    def ends(self, s):
        """
        k0~k 以字符串s格式结尾 return 1
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
        """setto(s) sets (j+1),...k to the characters in the string s, readjusting k."""
        length = len(s)
        self.word = self.word[:self.index+1] + \
            s + self.word[self.index+length+1:]
        self.end = self.index + length

    def r(self, s):
        """r(s) is used further down."""
        if self.m() > 0:
            self.setto(s)

    def step1ab(self):
        """step1ab() gets rid of plurals and -ed or -ing. e.g.
           caresses  ->  caress
           ponies    ->  poni
           ties      ->  ti
           caress    ->  caress
           cats      ->  cat
           feed      ->  feed
           agreed    ->  agree
           disabled  ->  disable
           matting   ->  mat
           mating    ->  mate
           meeting   ->  meet
           milling   ->  mill
           messing   ->  mess
           meetings  ->  meet
        """
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

    def step1c(self):
        """step1c() turns terminal y to i when there is another vowel in the stem."""
        if (self.ends("y") and self.vowelinstem()):
            self.word = self.word[:self.end] + 'i' + self.word[self.end+1:]

    # def step5(self):
    #     """step5() removes a final -e if m() > 1, and changes -ll to -l if
    #     m() > 1.
    #     """
    #     self.index = self.end
    #     if self.word[self.end] == 'e':
    #         a = self.m()
    #         if a > 1 or (a == 1 and not self.cvc(self.end-1)):
    #             self.end = self.end - 1
    #     if self.word[self.end] == 'l' and self.doublec(self.end) and self.m() > 1:
    #         self.end = self.end - 1

    def stem(self, word):
        """
        """
        # copy the parameters into statics
        self.word = word
        self.end = len(word) - 1
        self.start = 0
        if self.end <= self.start + 1:
            return self.word  # --DEPARTURE--

        self.step1ab()
        self.step1c()
        # self.step2()
        # self.step3()
        # self.step4()
        # self.step5()
        return self.word[self.start:self.end+1]


p = PorterStemmer()
word = "does"
print(p.stem(word))
