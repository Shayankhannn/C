/*
============================================================
File: hex_monte_carlo_ai.cpp

Project: Hex Game AI (Monte Carlo Based - HW5)

Description:
This program implements a Hex game with an 11x11 board and a
Monte Carlo based AI.

The AI evaluates each possible move by performing multiple
random simulations (rollouts). In each rollout, remaining
moves are played randomly until the board is full, then a
winner is determined using DFS path checking.

The AI selects the move with the highest win ratio.

Human plays against AI interactively.
============================================================
*/

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

class Hex {

private:
    int N;

    vector<vector<int>> board;

    const int EMPTY = 0;
    const int BLUE = 1;
    const int RED = 2;

public:

    Hex(int size = 11) {
        N = size;
        board.resize(N, vector<int>(N, EMPTY));
    }

    /* ---------------- Print Board ---------------- */
    void printBoard() {
        cout << "\n   ";
        for (int j = 0; j < N; j++) cout << j << " ";
        cout << "\n";

        for (int i = 0; i < N; i++) {
            cout << i << "  ";
            for (int j = 0; j < N; j++) {
                if (board[i][j] == BLUE) cout << "B ";
                else if (board[i][j] == RED) cout << "R ";
                else cout << ". ";
            }
            cout << "\n";
        }
        cout << "\n";
    }

    /* ---------------- Move Check ---------------- */
    bool valid(int r, int c) {
        return r >= 0 && r < N &&
               c >= 0 && c < N &&
               board[r][c] == EMPTY;
    }

    /* ---------------- DFS WIN CHECK ---------------- */
    bool dfs(int r, int c, int player, vector<vector<bool>>& vis) {

        if (r < 0 || c < 0 || r >= N || c >= N) return false;
        if (vis[r][c] || board[r][c] != player) return false;

        vis[r][c] = true;

        if (player == BLUE && r == N - 1) return true;
        if (player == RED && c == N - 1) return true;

        int dr[6] = {-1, -1, 0, 0, 1, 1};
        int dc[6] = {0, 1, -1, 1, -1, 0};

        for (int i = 0; i < 6; i++) {
            if (dfs(r + dr[i], c + dc[i], player, vis))
                return true;
        }

        return false;
    }

    bool checkWin(int player) {
        vector<vector<bool>> vis(N, vector<bool>(N, false));

        if (player == BLUE) {
            for (int j = 0; j < N; j++)
                if (board[0][j] == BLUE && dfs(0, j, BLUE, vis))
                    return true;
        }

        if (player == RED) {
            for (int i = 0; i < N; i++)
                if (board[i][0] == RED && dfs(i, 0, RED, vis))
                    return true;
        }

        return false;
    }

    /* ---------------- Random rollout ---------------- */
    int randomPlayout(int startPlayer) {

        vector<vector< int > > temp = board;

        vector<pair<int,int>> empty;

        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                if (temp[i][j] == EMPTY)
                    empty.push_back({i,j});

        int turn = startPlayer;

        while (!empty.empty()) {

            int idx = rand() % empty.size();
            int r = empty[idx].first;
            int c = empty[idx].second;

            temp[r][c] = turn;

            empty.erase(empty.begin() + idx);

            turn = (turn == BLUE) ? RED : BLUE;
        }

        /* Evaluate winner */
        Hex sim(N);
        sim.board = temp;

        if (sim.checkWin(BLUE)) return BLUE;
        if (sim.checkWin(RED)) return RED;

        return 0;
    }

    /* ---------------- AI MOVE ---------------- */
    pair<int,int> bestMove(int player, int simulations = 500) {

        double bestScore = -1;
        pair<int,int> best = {-1, -1};

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {

                if (!valid(i,j)) continue;

                int win = 0;

                board[i][j] = player;

                for (int k = 0; k < simulations; k++) {
                    int result = randomPlayout(player);

                    if (result == player)
                        win++;
                }

                board[i][j] = EMPTY;

                double score = (double)win / simulations;

                if (score > bestScore) {
                    bestScore = score;
                    best = {i,j};
                }
            }
        }

        return best;
    }

    /* ---------------- Play Move ---------------- */
    void move(int r, int c, int p) {
        board[r][c] = p;
    }

    /* ---------------- GAME LOOP ---------------- */
    void play() {

        srand(time(0));

        int human = BLUE;
        int ai = RED;

        int turn = BLUE;

        cout << "HEX AI GAME (Monte Carlo)\n";
        cout << "Blue = Human, Red = AI\n\n";

        printBoard();

        while (true) {

            if (turn == human) {

                int r, c;

                cout << "Your move (row col): ";
                cin >> r >> c;

                if (!valid(r,c)) {
                    cout << "Invalid move!\n";
                    continue;
                }

                move(r,c,human);
            }
            else {
                cout << "AI thinking...\n";

                pair<int,int> m = bestMove(ai, 200); // reduce if slow

                move(m.first, m.second, ai);

                cout << "AI played: " << m.first << " " << m.second << "\n";
            }

            printBoard();

            if (checkWin(turn)) {
                cout << (turn == BLUE ? "BLUE WINS!\n" : "RED WINS!\n");
                break;
            }

            turn = (turn == BLUE) ? RED : BLUE;
        }
    }
};

/* ---------------- MAIN ---------------- */
int main() {

    Hex game(11);
    game.play();

    return 0;
}