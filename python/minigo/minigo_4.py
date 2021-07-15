# 导入黑白棋文件
from game import Game
import random
import board


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


class AIPlayer:
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

        # -----------------请实现你的算法代码--------------------------------------
        color = self.color
        action_list = list(board.get_legal_actions(color))
        weight_table = []
        weight_table.append([100, -20, 8, 6, 6, 8, -20, 100])
        weight_table.append([-20, -50, -4, -3, -3, -4, -50, -20])
        weight_table.append([8, -4, 7, 4, 4, 7, -20, 8])
        weight_table.append([6, -3, 4, 0, 0, 4, -3, 6])
        weight_table.append([6, -3, 4, 0, 0, 4, -3, 6])
        weight_table.append([8, -4, 7, 4, 4, 7, -20, 8])
        weight_table.append([-20, -50, -4, -3, -3, -4, -50, -20])
        weight_table.append([100, -20, 8, 6, 6, 8, -20, 100])

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

        def MaxValue(self, board, color, alpha, beta, action, temp):
            if game.game_over():
                v = CalValue(self, board, color, weight_table)
                board.backpropagation(action, temp, color)
                return v, None
            v = -10000
            action = None
            action_list = list(board.get_legal_actions(color))

            for thisaction in action_list:
                temp = board._move(thisaction, color)
                v_temp, action_temp = MinValue(
                    self, board, color, alpha, beta, thisaction, temp)
                board.backpropagation(thisaction, temp, color)
                if v_temp > v:
                    v = v_temp
                    action = action_temp
                alpha = max(alpha, v)
                if alpha >= beta:
                    return v, action
            return v,action

        def MinValue(self, board, color, alpha, beta, action, temp):
            if game.game_over():
                v = CalValue(self, board, color, weight_table)
                board.backpropagation(action, temp, color)
                return v, None
            v = +10000
            action = None
            action_list = list(board.get_legal_actions(color))

            for thisaction in action_list:
                temp = board._move(thisaction, color)
                v_temp, action_temp = MaxValue(
                    self, board, color, alpha, beta, thisaction, temp)
                board.backpropagation(thisaction, temp, color)
                if v_temp < v:
                    v = v_temp
                    action = action_temp
                alpha = max(alpha, v)
                if alpha >= beta:
                    return v, action
            return v,action

        def AlphaBeta_Search(self, board):
            action = MaxValue(self, board, self.color, -
                              10000, +10000, action=None, temp=None)[1]
            return action
        if len(action_list) == 0:
            action = None
        else:
            action = AlphaBeta_Search(self, board)
        return action


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
