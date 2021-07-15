class safe_fruit():
    def __init__(self):
        N, M = map(int, input().split())

        self.pricedic = {}
        self.fruitlist = []
        self.map = []
        self.max = set()
        unsafe_pairs = []

        for i in range(N):
            unsafe_pairs.append(input().split())

        for i in range(M):
            self.map.append([])
            for j in range(M):
                if i != j:
                    self.map[i].append(1)
                else:
                    self.map[i].append(0)
        
        for k in range(len(unsafe_pairs)):
            a,b = map(int,unsafe_pairs[k])
            self.map[a-1][b-1] = 0
            self.map[b-1][a-1] = 0
            
        for i in range(M):
            name, price = input().split()
            self.pricedic[name] = int(price)
            self.fruitlist.append(name)
        
        self.Calculate()

    def N(self, v):
        """
        返回与v相连的节点集合
        """
        near = set()
        for thisfruit in self.fruitlist:
            if self.map[int(thisfruit) - 1][int(v)-1] != 0:
                near = near | set([thisfruit])
        return near

    def CountSum(self, s):
        sum = 0
        for element in s:
            sum += self.pricedic[element]
        return sum

    def BronKerbosch(self, R, P, X):
        """
        R,P,X are sets of vertexs
        R :在团中的节点
        P :还未处理的节点
        X :已经排除的节点
        """
        if len(P) == 0 and len(X) == 0:
            if len(R) > len(self.max) or (len(R) == len(self.max) and self.CountSum(R) < self.CountSum(self.max)):
                self.max = R.copy()
            return R

        for v in P:
            self.BronKerbosch(R | set([v]), P & self.N(v), X & self.N(v))
            P = P - set([v])
            X = X | set([v])

    def Calculate(self):
        self.BronKerbosch(set(), set(self.fruitlist), set())
        maxlist = list(self.max)
        maxlist.sort()
        print(len(maxlist))
        for i in range(len(maxlist)):
            if i == 0:
                print(maxlist[i], end="")
            else:
                print(" ", maxlist[i], sep="", end='')
        print()
        print(self.CountSum(maxlist))

a = safe_fruit()

