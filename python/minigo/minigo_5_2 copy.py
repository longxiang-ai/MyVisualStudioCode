# 导入黑白棋文件
from game import Game
import random
import board
import game


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


class AIPlayer_old:
    """
    AI 玩家
    """

    def __init__(self, color):
        """
        玩家初始化
        :param color: 下棋方，'X' - 黑棋，'O' - 白棋
        """

        self.color = color

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
        # -----------------请实现你的算法代码--------------------------------------
        color = self.color
        action_list = list(board.get_legal_actions(color))
        weight_table = []
        weight_table.append([100, -8, 8, 6, 6, 8, -8, 100])
        weight_table.append([-8, -25, -4, -3, -3, -4, -25, -8])
        weight_table.append([8, -4, 7, 4, 4, 7, -4, 8])
        weight_table.append([6, -3, 4, 0, 0, 4, -3, 6])
        weight_table.append([6, -3, 4, 0, 0, 4, -3, 6])
        weight_table.append([8, -4, 7, 4, 4, 7, -4, 8])
        weight_table.append([-8, -25, -4, -3, -3, -4, -25, -8])
        weight_table.append([100, -8, 8, 6, 6, 8, -8, 100])

        def CalValue(self, board, color, weight_table):
            v = 0
            op = 'O' if color == 'X' else 'X'
            for x in range(8):
                for y in range(8):
                    if board[x][y] == color:
                        v += weight_table[x][y]
                    elif board[x][y] == op:
                        v -= weight_table[x][y]
            return v

        def maxvalue(self, board, color, depth=0):
            v = -10000
            scores = []
            MAXDEPTH = 3
            action_list = list(board.get_legal_actions(color))

            if game_over(self, board) or depth == MAXDEPTH:
                return CalValue(self, board, color, weight_table)
            elif len(action_list) > 0:
                for i in range(len(action_list)):
                    temp = board._move(action_list[i], color)
                    scores.append(minvalue(self, board, color, depth + 1))
                    board.backpropagation(action_list[i], temp, color)
                v = min(scores)
            return v

        def minvalue(self, board, color, depth=0):
            v = +10000
            MAXDEPTH = 3
            color = self.color
            scores = []
            action_list = list(board.get_legal_actions(color))
            if game_over(self, board) or depth == MAXDEPTH:
                return CalValue(self, board, color, weight_table)
            elif len(action_list) > 0:
                for i in range(len(action_list)):
                    temp = board._move(action_list[i], color)
                    scores.append(maxvalue(self, board, color, depth + 1))
                    board.backpropagation(action_list[i], temp, color)
                v = max(scores)
            return v

        def MaxMin_Search(self, board, action_list):
            max = -100
            color = self.color
            for i in range(len(action_list)):
                temp = board._move(action_list[i], color)
                MINVALUE = minvalue(self, board, color, 0)
                if MINVALUE > max:
                    max = MINVALUE
                    index = i
                board.backpropagation(action_list[i], temp, color)
            if len(action_list) > 0:
                try:
                    return action_list[index]
                except:
                    return action_list[0]
            else:
                return None

        if len(action_list) == 0:
            action = None
        else:
            action = MaxMin_Search(self, board, action_list)
        return action


class AIPlayer:
    """
    AI 玩家
    算法采用alphabeta剪枝搜索
    """
    def __init__(self, color):
        """
        玩家初始化
        :param color: 下棋方，'X' - 黑棋，'O' - 白棋
        alpha,beta为初始更新的下界和上界
        MAXDEPTH为事先确定的常量递归最大层数，综合测试后决定定为4
        weight_table 为权值表，权值表的构建是基于个人下棋的习惯……
        NumWeight 为修正得分的辅助手段，为尽可能避免无子可走的尴尬境地
        """
        self.color = color
        self.alpha = -10000
        self.beta = 10000
        self.MAXDEPTH = 4
        # 考虑到游戏特性，决定在四个角的位置设置较高的权值，能占角的情况优先占角
        # 在角的斜对角位置 （如B2)等危险位置时，决定给负的权，避免被吃的很惨……
        # 除危险位置的边以外的边位置采取优先占领的策略
        self.weight_table = [
            [125, -20, 15, 15, 15, 15, -20, 125],
            [-20, -40, 5, 5, 5, 5, -40, -20],
            [15, 5, 1, 1, 1, 1, 5, 15],
            [15, 5, 1, 2, 2, 1, 5, 15],
            [15, 5, 1, 2, 2, 1, 5, 15],
            [15, 5, 1, 1, 1, 1, 5, 15],
            [-20, -40, 5, 5, 5, 5, -40, -20],
            [125, -20, 15, 15, 15, 15, -20, 125]
        ]
        self.NumWeight = 0.7

    def CalValue(self, board, color):
        """
        计算当前玩家color下的得分
        注意到这个身份在两个player之间相互交换
        """
        # 作为可行动落子的奖励/惩罚系数
        NumWeight = self.NumWeight
        op = 'O' if self.color == 'X' else 'X'
        v = 0
        # 根据weight_table初步计算当前局势的得分
        for i in range(8):
            for j in range(8):
                if board[i][j] == self.color:
                    v += self.weight_table[i][j]
                elif op == board[i][j]:
                    v -= self.weight_table[i][j]
        # 由于上面的情况下得分分布不是很理想，所以选择另一种修正方式
        # 为了尽可能避免被Pass的局面，建立了修正项
        actions = len(list(board.get_legal_actions(color)))
        if color == self.color:
            v += actions*NumWeight
        else:
            v -= actions*NumWeight
        return v

    def AlphaBeta_Search(self, board, color, alpha, beta, depth=0):
        """
        AlphaBeta剪枝搜索函数
        color为AI玩家的颜色
        alpha,beta为下限和上限
        depth 为递归层数
        """
        # op表示对手的颜色
        op = 'O' if self.color == 'X' else 'X'
        action_list = list(board.get_legal_actions(color))

        if len(action_list) == 0 or depth == self.MAXDEPTH:  # 若无子可走/深度达到递归层数的上限，则终止递归，返回得分值
            return self.CalValue(board, color)
        
        # 玩家MAX行动时期
        if color == self.color:
            for thisaction in action_list:
                # temp 暂时存储落子后翻转的子
                temp = board._move(thisaction, color)
                # 进入玩家MIN行动的递归中
                score = self.AlphaBeta_Search(
                    board, op, alpha, beta, depth+1)
                board.backpropagation(thisaction, temp, color)
                if score > alpha:
                    alpha = score
                # 如果符合剪枝的条件则直接跳出
                if beta < alpha:
                    return alpha
            return alpha
        # 玩家MIN行动时期
        else:
            for thisaction in action_list:
                # temp 暂时存储落子后翻转的子
                temp = board._move(thisaction, color)
                # 进入玩家MAX行动的递归中
                score = self.AlphaBeta_Search(
                    board, op, alpha, beta, depth+1)
                board.backpropagation(thisaction, temp, color)
                if score < beta:
                    beta = score
                # 如果符合剪枝的条件则直接跳出
                if beta < alpha:
                    return beta
            return beta

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

        action = None  # 可以采取的行动事先规定为None
        color = self.color  # 目前的颜色
        op = 'O' if color == 'X' else 'X'  # 对手的颜色
        action_list = list(board.get_legal_actions(self.color))  # 目前局势可以行动的列表
        alpha = self.alpha  # 获取下限
        beta = self.beta    # 获取上限

        if len(action_list) == 0:  # 如果没有可走的，则直接返回 None
            return action
        else:
            for thisaction in action_list:
                # 模拟落子,temp用来存储_move的返回值，即翻转的子
                temp = board._move(thisaction, self.color)
                # 用alphabeta剪枝的方法迭代获得thisaction的得分
                v = self.AlphaBeta_Search(board, op, alpha, beta)
                # 获得得分后进行回溯
                board.backpropagation(thisaction, temp, self.color)
                # 如果高于下界，则更新下界和目前应该采取的最佳动作action
                if v > alpha:
                    action = thisaction
                    alpha = v
        return action


count_black = 0
play_times = 20
for i in range(play_times):
    # 随机玩家黑棋初始化
    # black_player = AIPlayer_old("X")
    black_player = AIPlayer("X")
    # 随机玩家白棋初始化
    white_player = RandomPlayer("O")
    # white_player = AIPlayer("O")
    # 游戏初始化，第一个玩家是黑棋，第二个玩家是白棋
    game = Game(black_player, white_player)

    # 开始下棋
    game.run()
    if game.board.get_winner()[0] == 0:
        count_black += 1

print(count_black, '/', play_times)
