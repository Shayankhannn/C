/*
 * ============================================================
 * File: hex_game_hw4.cpp
 *
 * Project: Hex Game (Graph-Based Path Finding - HW4)
 *
 * Description:
 * This program implements the Hex board game using a graph
 * representation. The board is modeled as a 2D grid where each
 * cell acts as a node in a graph with up to 6 neighbors.
 *
 * Players take turns placing markers:
 * - Blue connects TOP to BOTTOM
 * - Red connects LEFT to RIGHT
 *
 * The program validates moves, displays an ASCII board, and
 * determines the winner using Depth First Search (DFS) path
 * traversal.
 *
 * NOTE:
 * This version does NOT include AI (as required for HW4).
 * ============================================================
 */

#include <iostream>
#include <vector>

using namespace std;

/*
 * Class: HexGame
 * Encapsulation:
 * - Board data is private
 * - All operations are handled through public methods
 */
class HexGame {

private:
    int size;

    vector<vector<int>> board;

    const int EMPTY = 0;
    const int BLUE  = 1;
    const int RED   = 2;

    /*
     * Function: dfs
     * Purpose:
     * Performs depth-first search to detect a winning path.
     *
     * Parameters:
     * r, c     - current position
     * player   - BLUE or RED
     * visited  - tracks visited nodes to avoid cycles
     *
     * Returns:
     * true if a winning path is found
     */
    bool dfs(int r, int c, int player, vector<vector<bool>>& visited) {

        if (r < 0 || r >= size || c < 0 || c >= size)
            return false;

        if (visited[r][c] || board[r][c] != player)
            return false;

        visited[r][c] = true;

        /* Winning conditions */
        if (player == BLUE && r == size - 1) return true;
        if (player == RED  && c == size - 1) return true;

        /* Hex graph neighbors (6 directions) */
        int dr[6] = {-1, -1, 0, 0, 1, 1};
        int dc[6] = {0, 1, -1, 1, -1, 0};

        for (int i = 0; i < 6; i++) {
            if (dfs(r + dr[i], c + dc[i], player, visited))
                return true;
        }

        return false;
    }

public:

    /*
     * Constructor
     * Initializes board with all cells empty
     */
    HexGame(int n = 11) {
        size = n;
        board.resize(size, vector<int>(size, EMPTY));
    }

    /*
     * Function: printBoard
     * Purpose:
     * Displays ASCII representation of board
     */
    void printBoard() {

        cout << "\n   ";
        for (int j = 0; j < size; j++)
            cout << j << " ";

        cout << "\n";

        for (int i = 0; i < size; i++) {

            cout << i << "  ";

            for (int j = 0; j < size; j++) {

                if (board[i][j] == BLUE) cout << "B ";
                else if (board[i][j] == RED) cout << "R ";
                else cout << ". ";
            }

            cout << "\n";
        }

        cout << "\n";
    }

    /*
     * Function: isValidMove
     * Purpose:
     * Checks whether a move is inside bounds and empty
     */
    bool isValidMove(int r, int c) {
        return (r >= 0 && r < size &&
                c >= 0 && c < size &&
                board[r][c] == EMPTY);
    }

    /*
     * Function: makeMove
     * Purpose:
     * Places a player's piece on the board
     */
    void makeMove(int r, int c, int player) {
        board[r][c] = player;
    }

    /*
     * Function: checkWin
     * Purpose:
     * Determines if a player has won using DFS search
     */
    bool checkWin(int player) {

        vector<vector<bool>> visited(size, vector<bool>(size, false));

        if (player == BLUE) {

            for (int j = 0; j < size; j++) {
                if (board[0][j] == BLUE &&
                    dfs(0, j, BLUE, visited))
                    return true;
            }
        }

        if (player == RED) {

            for (int i = 0; i < size; i++) {
                if (board[i][0] == RED &&
                    dfs(i, 0, RED, visited))
                    return true;
            }
        }

        return false;
    }

    /*
     * Function: play
     * Purpose:
     * Main game loop handling input and turn switching
     */
    void play() {

        int r, c;
        int turn = BLUE;
        int moves = 0;
        int maxMoves = size * size;

        cout << "HEX GAME (HW4 - Graph + DFS)\n";
        cout << "Blue = TOP → BOTTOM\n";
        cout << "Red  = LEFT → RIGHT\n\n";

        printBoard();

        while (moves < maxMoves) {

            cout << ((turn == BLUE) ? "Blue move: " : "Red move: ");
            cin >> r >> c;

            if (!isValidMove(r, c)) {
                cout << "Invalid move. Try again.\n";
                continue;
            }

            makeMove(r, c, turn);
            moves++;

            printBoard();

            if (checkWin(turn)) {
                cout << (turn == BLUE ? "BLUE WINS!\n" : "RED WINS!\n");
                return;
            }

            turn = (turn == BLUE) ? RED : BLUE;
        }

        cout << "Game Draw!\n";
    }
};

/* ---------------- MAIN ---------------- */
int main() {

    HexGame game(11);
    game.play();

    return 0;
}