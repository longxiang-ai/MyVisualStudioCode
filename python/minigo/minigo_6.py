# 导入黑白棋文件
from game import Game
import random
import board
import math

class RandomPlayer:
    """
    随机玩家, 随机返回一个合法落子位置
    """

    def __init__(self, color):
        """
        玩家初始化
        :param color: 下棋方，'X' - 黑棋，'O' - 白棋
        """
        self.color = color

    def random_choice(self, board):
        """
        从合法落子位置中随机选一个落子位置
        :param board: 棋盘
        :return: 随机合法落子位置, e.g. 'A1' 
        """
        # 用 list() 方法获取所有合法落子位置坐标列表
        action_list = list(board.get_legal_actions(self.color))

        # 如果 action_list 为空，则返回 None,否则从中选取一个随机元素，即合法的落子坐标
        if len(action_list) == 0:
            return None
        else:
            return random.choice(action_list)

    def get_move(self, board):
        """
        根据当前棋盘状态获取最佳落子位置
        :param board: 棋盘
        :return: action 最佳落子位置, e.g. 'A1'
        """
        if self.color == 'X':
            player_name = '黑棋'
        else:
            player_name = '白棋'
        print("请等一会，对方 {}-{} 正在思考中...".format(player_name, self.color))
        action = self.random_choice(board)
        return action


class HumanPlayer:
    """
    人类玩家
    """

    def __init__(self, color):
        """
        玩家初始化
        :param color: 下棋方，'X' - 黑棋，'O' - 白棋
        """
        self.color = color

    def get_move(self, board):
        """
        根据当前棋盘输入人类合法落子位置
        :param board: 棋盘
        :return: 人类下棋落子位置
        """
        # 如果 self.color 是黑棋 "X",则 player 是 "黑棋"，否则是 "白棋"
        if self.color == "X":
            player = "黑棋"
        else:
            player = "白棋"

        # 人类玩家输入落子位置，如果输入 'Q', 则返回 'Q'并结束比赛。
        # 如果人类玩家输入棋盘位置，e.g. 'A1'，
        # 首先判断输入是否正确，然后再判断是否符合黑白棋规则的落子位置
        while True:
            action = input(
                "请'{}-{}'方输入一个合法的坐标(e.g. 'D3'，若不想进行，请务必输入'Q'结束游戏。): ".format(player,
                                                                             self.color))

            # 如果人类玩家输入 Q 则表示想结束比赛
            if action == "Q" or action == 'q':
                return "Q"
            else:
                row, col = action[1].upper(), action[0].upper()

                # 检查人类输入是否正确
                if row in '12345678' and col in 'ABCDEFGH':
                    # 检查人类输入是否为符合规则的可落子位置
                    if action in board.get_legal_actions(self.color):
                        return action
                else:
                    print("你的输入不合法，请重新输入!")


class Tree():
    """
    树的抽象基类
    """

    # 叫做位置的内嵌类，用于封装节点
    class Position():

        def element(self):
            raise NotImplementedError('must be implemented by subclass')

        def __eq__(self, other):
            raise NotImplementedError('must be implemented by subclass')

    def root(self):
        """
        return 根节点的position
        """
        raise NotImplementedError('must be implemented by subclass')

    def parent(self, p):
        """

        :param p:一个位置对象
        :return: 返回p的父节点的position对象，如果p是根节点则饭后空
        """
        raise NotImplementedError('must be implemented by subclass')

    def num_children(self, p):
        """

        :param p:一个位置对象
        :return: 返回该位置的孩子节点的数量
        """
        raise NotImplementedError('must be implemented by subclass')

    def children(self, p):
        """

        :param p: 一个位置对象
        :return: 返回位置p的孩子的迭代
        """
        raise NotImplementedError('must be implemented by subclass')

    def __len__(self):
        """

        :return: 返回整个树的节点个数
        """
        raise NotImplementedError('must be implemented by subclass')

    def is_root(self, p):
        return self.root() == p

    def is_leaf(self, p):
        return self.num_children(p) == 0

    def is_empty(self):
        return len(self) == 0


class MCtree(Tree):
    class Node():
        """
        节点类
        score 表示得分 float 
        times 表示被访问的次数 int 
        children表示第一个孩子 Node
        parent表示父节点 Node
        right表示右边的sibling Node
        """

        def __init__(self, score=0, times=0, parent=None, children=None, right=None):
            self.score = score
            self.times = times
            self.parent = parent
            self.children = children
            self.right = right

    def validate(self, node):
        """
        进行位置验证
        """
        if not isinstance(node, self.Node):
            raise TypeError('node must be proper Node type')
        if node.parent is node:
            raise ValueError('node is no longer valid')
        return node

    def __init__(self):
        self._root = None
        self.size = 0

    def __len__(self):
        return self.size

    def root(self):
        """
        返回树的根节点，如果没有根节点则返回None
        """
        return self.Node(self._root)

    def parent(self, node):
        """
        返回该节点的parent,如果没有父辈节点则返回None
        """
        # if node.parent == None:
        #     raise ValueError("该节点没有父辈节点")
        node = self.validate(node)
        return node.parent

    def children(self, node):
        """
        返回该节点的第一个child
        """
        node = self.validate(node)
        return node.children

    def right(self, node):
        """
        返回该节点的右sibling
        """
        node = self.validate(node)
        return node.right

    def num_children(self, node):
        """
        返回该节点孩子的数量，如果没有孩子则返回0
        """
        if node.children == None:
            return 0
        else:
            count = 1
            temp = node.children
            while temp.right is not None:
                count += 1
                temp = temp.right
            return count

    def add_root(self):
        """
        添加根节点
        """
        if self._root is not None:
            raise ValueError('Root exists')
        self.size += 1
        self._root = self.Node()
        return self._root

    def add_child(self, score, times, node):
        """
        在该节点下增加一个子辈节点
        如果已经存在一个child，则增加这个child的右节点
        """
        node = self.validate(node)
        if node.children is None:
            self.size += 1
            node.children = self.Node(score, times, node, None, None)
            return node.children
        else:
            temp = node.children
            while temp.right is not None:
                temp = temp.right
            self.size += 1
            temp.right = self.Node(score, times, node.parent, None, None)
            return temp.right

    def add_right(self, score, times, node):
        node = self.validate(node)
        if node.right is None:
            self.size += 1
            node.right = self.Node(score, times, node.parent, None, None)
            return node.right
        else:
            temp = node .right
            while temp.right is not None:
                temp = temp.right
            self.size += 1
            temp.right = self.Node(score, times, node.parent, None, None)
            return temp.right


class AIPlayer():
    """
    AI 玩家
    """

    def __init__(self, color):
        """
        玩家初始化
        :param color: 下棋方，'X' - 黑棋，'O' - 白棋
        """
        self.mctree = MCtree()  # 创建蒙特卡洛树
        self.mctree.add_root()  # 添加根节点
        self.color = color
        self.C = 1  # UCB1算法的超参数C

    def get_move(self, board):
        """
        根据当前棋盘状态获取最佳落子位置
        :param board: 棋盘
        :return: action 最佳落子位置, e.g. 'A1'
        """
        if self.color == 'X':
            player_name = '黑棋'
        else:
            player_name = '白棋'
        print("请等一会，对方 {}-{} 正在思考中...".format(player_name, self.color))

        # -----------------请实现你的算法代码--------------------------------------
        def game_over(self, board):
            """
            判断游戏是否结束
            :return: True/False 游戏结束/游戏没有结束
            """

            # 根据当前棋盘，判断棋局是否终止
            # 如果当前选手没有合法下棋的位子，则切换选手；如果另外一个选手也没有合法的下棋位置，则比赛停止。
            b_list = list(board.get_legal_actions('X'))
            w_list = list(board.get_legal_actions('O'))

            is_over = len(b_list) == 0 and len(w_list) == 0  # 返回值 True/False

            return is_over
        color = self.color
        root = self.mctree.root()

        action_list = list(board.get_legal_actions(color))
        weight_table = [[100, -20, 8, 6, 6, 8, -20, 100], [-20, -50, -4, -3, -3, -4, -50, -20], [8, -4, 7, 4, 4, 7, -20, 8], [6, -3, 4, 0, 0, 4, -
                                                                                                                              3, 6], [6, -3, 4, 0, 0, 4, -3, 6], [8, -4, 7, 4, 4, 7, -20, 8], [-20, -50, -4, -3, -3, -4, -50, -20], [100, -20, 8, 6, 6, 8, -20, 100]]
        # print(self.mctree._root.score)

        def SelectPolicy(self, board, v_0):
            """
            选择策略
            输入选择的起始节点v_0
            输出选择步骤的结束节点v
            """
            v = v_0
            while not game_over(self, board):
                if NotExpandChild(v):
                    return Expand(v)
                else:
                    v = UCB1(v, self.C)
            return v  # 这个步骤存疑

        def SimulatePolicy(self, board):
            board_temp = board.copy()
            while not game_over(self,board_temp):
                action_list = list(board.get_legal_actions(color))
                thisaction = random_choice( action_list)
                board_temp = result (board_temp,thisaction)#实行这步动作
            return board_temp    

        

        def BackPropagate(self, board, v, s_t):
            while v is not None:
                v.times += 1
                v.score = v.score - utility(s_t,player_name(v_state))
                v = v.parent
        def Expand(self,board,v):
            action_list = list (board.get_legal_actions(color))
            thisaction = random_choice(action_list)
            v_temp = MCtree.Node()#差数据
            v_temp.times=0
            v_temp.score=0
            v_temp.parent = v
            v_temp.children = None
            add_child(v_temp,v)#缺东西 
        
        def CalUCB(self,v,v_temp):
            l = v_temp.score/v_temp.times +self.C*(math.sqrt(2*math.log(v.times)/math.log(v_temp.times)))
            return l
        
        def UCB1(self, board,v):
            C = self.C
            v_temp = v.children
            Maxscore = 0
            index = 0
            num = 0
            while v_temp is not None:
                num +=1
                UCBvalue = CalUCB(self,v,v_temp)
                if UCBvalue >Maxscore:
                    UCBvalue = Maxscore
                    index = num
                v_temp = v_temp.right
            v_temp = v.children
            for i in range (index):
                v_temp = v_temp.right
            return v_temp
        def UCB_Search(self, board):
            v_0 = MCtree.Node()
            MAXDEPTH = 3
            depth = 0
            while depth <= MAXDEPTH:
                v_t = SelectPolicy(self, board, v_0)
                s_t = SimulatePolicy(self, board, v_t)
                BackPropagate(self, board, v_t, s_t)

                depth +=1
            action = UCB1(v_0, 0)
            return action

        # def CalValue(self, board, color, weight_table):
        #     v = 0
        #     op = 'O' if color == 'X' else 'X'
        #     for x in range(8):
        #         for y in range(8):
        #             if board[x][y] == color:
        #                 v += weight_table[x][y]
        #             elif board[x][y] == op:
        #                 v -= weight_table[x][y]
        #     return v




count_black = 0
play_times = 1
for i in range(play_times):
    # 随机玩家黑棋初始化
    black_player = AIPlayer("X")
    # 随机玩家白棋初始化
    #white_player = RandomPlayer("O")
    white_player = RandomPlayer("O")
    # 游戏初始化，第一个玩家是黑棋，第二个玩家是白棋
    game = Game(black_player, white_player)

    # 开始下棋
    game.run()
    if game.board.get_winner()[0] == 0:
        count_black += 1

print(count_black, '/', play_times)
