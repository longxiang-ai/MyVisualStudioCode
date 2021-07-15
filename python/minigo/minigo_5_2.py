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

            if game_over(self,board) or depth == MAXDEPTH:
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
            if game_over(self,board) or depth == MAXDEPTH:
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
        weight_table = []
        weight_table.append([100, -10, 8, 8, 8, 8, -10, 100])
        weight_table.append([-8, -50, 6, 6, 6, 6, -50, -10])
        weight_table.append([8, 6, 7, 4, 4, 7, 6, 8])
        weight_table.append([8, 6, 4, 1, 1, 4, 6, 8])
        weight_table.append([8, 6, 4, 1, 1, 4, 6, 8])
        weight_table.append([8, 6, 7, 4, 4, 7, 6, 8])
        weight_table.append([-10, -50, 6, 6, 6, 6, -50, -10])
        weight_table.append([100, -10, 8, 8, 8, 8, -10, 100])
        
        def CalValue(self, board, weight_table):
            color = self.color
            v = 0
            op = 'O' if color == 'X' else 'X'
            for x in range(8):
                for y in range(8):
                    if board[x][y] == color:
                        v += weight_table[x][y]
                    elif board[x][y] == op:
                        v -= weight_table[x][y]
            return v

        def maxvalue(self, board, alpha, beta, depth=0):

            v = -100000
            action_list = list(board.get_legal_actions(self.color))
            try :
                action = action_list[0]
            except:
                action = None
            MAXDEPTH = 5
            if game_over(self,board) or depth == MAXDEPTH:
                return CalValue(self, board, weight_table),None
            else:
                
                for thisaction in action_list:
                    
                    temp = board._move(thisaction, self.color)
                    v_temp= minvalue(self, board, alpha, beta, depth+1)[0]
                    board.backpropagation(thisaction, temp, self.color)
                    if v_temp > v:
                        v = v_temp
                        action = thisaction
                    alpha = max(alpha, v)
                    if alpha >= beta:
                        return v,action
                return v,action

        def minvalue(self, board, alpha, beta, depth=0):
            action_list = list(board.get_legal_actions(self.color))
            try :
                action = action_list[0]
            except:
                action = None
            v = +100000

            MAXDEPTH = 5
            if game_over(self,board) or depth == MAXDEPTH:
                return CalValue(self, board, weight_table),None
            else:
               
                for thisaction in action_list:
                    # if thisaction in ['A1','A8','H1','H8']:
                    #     return -100000,thisaction
                    temp = board._move(thisaction, self.color)
                    v_temp = maxvalue(self, board, alpha, beta, depth+1)[0]
                    board.backpropagation(thisaction, temp, self.color)
                    if v_temp < v:
                        v = v_temp
                        action = thisaction
                    beta = min(beta, v)

                    if alpha >= beta:
                        return v,action
                return v,action

        def AlphaBeta_Search(self, board):
            action_list = list(board.get_legal_actions(self.color))
            v = -100000
            alpha = -100000
            beta  = +100000
            try:
                action_max = action_list[0]
            except:
                action_max = None
            for thisaction in action_list:
                temp = board._move(thisaction, self.color)
                v_temp = maxvalue(self, board, alpha,beta, depth=0)
                board.backpropagation(thisaction, temp, self.color)
                if v_temp > v:
                    action_max = thisaction
                    v = v_temp
            return action_max
        # def AlphaBeta_Search(self,board):
        #     # action
        #     return maxvalue(self,board,-100000,+100000,0)[1]
        
        return AlphaBeta_Search(self, board)


count_black = 0
play_times = 1
for i in range(play_times):
    # 随机玩家黑棋初始化
    black_player = AIPlayer_old("X")
    # black_player = RandomPlayer("X")
    # 随机玩家白棋初始化
    # white_player = RandomPlayer("O")
    white_player = AIPlayer("O")
    # 游戏初始化，第一个玩家是黑棋，第二个玩家是白棋
    game = Game(black_player, white_player)

    # 开始下棋
    game.run()
    if game.board.get_winner()[0] == 0:
        count_black += 1

print(count_black, '/', play_times)
