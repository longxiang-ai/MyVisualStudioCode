class safe_fruit():
    def __init__(self):
        N, M = map(int, input().split())

        self.pricedic = {}
        self.fruitlist = []
        self.map = []

        unsafe_pairs = []
        for _ in range(N):
            unsafe_pairs.append(input().split())

        for i in range(M):
            self.map.append([])
            for j in range(M):
                if i != j:
                    self.map[i].append(1)
                else:
                    self.map[i].append(0)

        for i in range(N):
            self.map[int(unsafe_pairs[i][0]) -
                     1][int(unsafe_pairs[i][1]) - 1] = 0
            self.map[int(unsafe_pairs[i][1]) -
                     1][int(unsafe_pairs[i][0]) - 1] = 0

        print(self.map)
        for _ in range(M):
            name, price = input().split()
            self.pricedic[name] = int(price)
            self.fruitlist.append(name)

        print(self.fruitlist)
        print(set(self.fruitlist))
        # print(self.fruits)
        print(self.pricedic)

    def N(self, v):
        """
        返回与v相连的节点集合
        """
        near = []
        for thisfruit in self.fruitlist:
            if self.map[int(thisfruit)-1][int(v)-1] != 0:
                near.append(thisfruit)
        # print(near)
        return set(near)

    def BronKerbosch(self, R, P, X):
        """
        R,P,X are sets of vertexs
        R :在团中的节点
        P :还未处理的节点
        X :已经排除的节点
        """
        if P is None and X is None:
            return R

        for v in P:
            print(self.N(v))
            print("R,P,X = ", R, P, X)
            self.BronKerbosch(R | v, P & self.N(v), X & self.N(v))
            P = P - v
            X = X | v

    def Calculate(self):
        print(self.BronKerbosch(set(), set(self.fruitlist), set()))


a = safe_fruit()
# a.N("009")
a.Calculate()
