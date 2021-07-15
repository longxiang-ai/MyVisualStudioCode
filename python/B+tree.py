import queue


class tree:
    """
    B+树的抽象类，内部包括类Node，以及B+tree的构筑过程
    M = 3
    """
    class Node:
        def __init__(self, element):
            if isinstance(element, list) or element == None:
                self.element = element
            elif isinstance(element, int):
                self.element = [element]
            else:
                self.element = None
            self.parent = None
            self.left = None
            self.mid = None
            self.right = None
            self.depth = 0

        # def FindDepth(self):
        #     return self.depth

        def PrintNode(self):
            print(self.element, end='')

    def __init__(self):
        """
        初始化树，其操作包括：
        1. 读入所有节点，当重复时打印
        2. 将节点逐次插入到根节点中
        3. 打印建立好的树
        parameter :
        1. N: 总节点数（不重复）
        2. nodelist: 读入的节点列表
        3. root : 根节点
        """
        # self.N = int(input())
        _ = int(input())
        readlist = list(map(int, input().split()))
        self.nodelist = []
        for i in range(len(readlist)):
            if readlist[i] not in self.nodelist:
                self.nodelist.append(readlist[i])
            else:
                print("Key {:} is duplicated".format(readlist[i]))
        self.N = len(self.nodelist)
        # print(self.nodelist)
        # 初始化过程
        self.root = self.Node(None)
        for i in range(self.N):
            self.Insert(self.root, self.Node(self.nodelist[i]))
        # testing code
        self.root = self.Node(3.5)
        # testing code
        self.PrintTree(thisroot=self.root)

    def Insert(self, root, node):
        """
        将该节点插入到树中，期间可能出现分裂的操作
        """
        pass

    def PrintTree(self, thisroot=None):
        """
        打印整棵树
        """
        PrintQueue = queue.Queue(maxsize=self.N)
        thisnode = thisroot
        lastdepth = 0
        while thisnode != None:
            # 换行
            if thisnode.depth != lastdepth:
                print()
                lastdepth = thisnode.depth
            # 打印点
            thisnode.PrintNode()
            # 将该点的非空孩子加入到打印的序列中
            if thisnode.left != None:
                PrintQueue.put(thisnode.left)
            if thisnode.mid != None:
                PrintQueue.put(thisnode.mid)
            if thisnode.right != None:
                PrintQueue.put(thisnode.right)
            # 如果打印的序列仍然非空，那么转换下一个打印的点
            if PrintQueue.empty():
                thisnode = None
            else:
                thisnode = PrintQueue.get()


a = tree()
