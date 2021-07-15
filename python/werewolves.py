class werewolf:
    def __init__(self):
        self.N, self.M, self.L = map(int, input().split())
        self.statement = []
        for _ in range(self.N):
            self.statement.append(int(input()))
        print(self.statement)
        self.wolf = []
        find = self.backtracking(self.N)
        if find:
            print(self.wolf)

    def fitrule(self, wolf):

        result = []
        liers = []
        for _ in range(self.N+1):
            result .append(1)

        for i in range(len(wolf)):
            result[wolf[i]] = -1

        for i in range(1, self.N+1):
            flag = int(result[i] * i)
            for j in range(1, self.N+1):
                if self.statement[j] == -1 * flag:
                    liers.append(j)

        l = len(liers)
        w = 0
        if l == self.L:
            for i in range(l):
                if result[liers[i]] < 0:
                    w += 1
            if w > 0 and w < len(wolf):
                return True
        return False

    def backtracking(self, depth):
        if len(self.wolf) == self.M:
            if self.fitrule(self.wolf.copy()):
                return True
            else:
                return False
        while depth > 0:
            self.wolf.append(depth)
            if self.backtracking(depth-1):
                return True
            else:
                self.wolf.pop()
            depth -= 1
        return False


were = werewolf()
# were.PrintResult()
