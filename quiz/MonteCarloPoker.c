/*
 * File: poker_monte_carlo_fixed.c
 *
 * Title:
 * Monte Carlo Simulation of 7-Card Poker Hand Probabilities in C
 *
 * Description:
 * This program simulates 7-card poker hands using Monte Carlo sampling.
 * A standard 52-card deck is represented using a struct containing an enum
 * suit and a short pip value.
 *
 * The program correctly evaluates 7-card poker hands by checking all
 * 21 possible 5-card combinations and selecting the best possible hand.
 *
 * It estimates probabilities for standard poker rankings using
 * 1,000,000 random simulations.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DECK_SIZE 52
#define HAND_SIZE 7
#define SIMULATIONS 1000000

/* ---------------- Card Structure ---------------- */

typedef enum {
    CLUBS,
    DIAMONDS,
    HEARTS,
    SPADES
} Suit;

typedef struct {
    Suit suit;
    short pip;   /* 2–14 (Ace = 14) */
} Card;

/* ---------------- Hand Types ---------------- */

typedef enum {
    HIGH_CARD,
    ONE_PAIR,
    TWO_PAIR,
    THREE_KIND,
    STRAIGHT,
    FLUSH,
    FULL_HOUSE,
    FOUR_KIND,
    STRAIGHT_FLUSH,
    ROYAL_FLUSH
} HandType;

/* ---------------- Deck ---------------- */

void createDeck(Card deck[]) {
    int i = 0;
    for (int s = 0; s < 4; s++) {
        for (int p = 2; p <= 14; p++) {
            deck[i].suit = (Suit)s;
            deck[i].pip = p;
            i++;
        }
    }
}

void swap(Card *a, Card *b) {
    Card temp = *a;
    *a = *b;
    *b = temp;
}

void shuffleDeck(Card deck[]) {
    for (int i = DECK_SIZE - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        swap(&deck[i], &deck[j]);
    }
}

/* ---------------- 5-Card Evaluation ---------------- */

int isFlush(Card h[]) {
    for (int i = 1; i < 5; i++) {
        if (h[i].suit != h[0].suit) return 0;
    }
    return 1;
}

int isStraight(int r[]) {
    int count = 0;

    for (int i = 2; i <= 14; i++) {
        if (r[i] == 1) {
            count++;
            if (count == 5) return 1;
        } else {
            count = 0;
        }
    }

    /* wheel straight A-2-3-4-5 */
    if (r[14] && r[2] && r[3] && r[4] && r[5])
        return 1;

    return 0;
}

HandType evaluateFive(Card h[]) {

    int r[15] = {0};

    for (int i = 0; i < 5; i++)
        r[h[i].pip]++;

    int pairs = 0, three = 0, four = 0;

    for (int i = 2; i <= 14; i++) {
        if (r[i] == 4) four++;
        else if (r[i] == 3) three++;
        else if (r[i] == 2) pairs++;
    }

    int flush = isFlush(h);
    int straight = isStraight(r);

    if (straight && flush && r[10] && r[11] && r[12] && r[13] && r[14])
        return ROYAL_FLUSH;

    if (straight && flush)
        return STRAIGHT_FLUSH;

    if (four)
        return FOUR_KIND;

    if (three && pairs >= 1)
        return FULL_HOUSE;

    if (flush)
        return FLUSH;

    if (straight)
        return STRAIGHT;

    if (three)
        return THREE_KIND;

    if (pairs >= 2)
        return TWO_PAIR;

    if (pairs == 1)
        return ONE_PAIR;

    return HIGH_CARD;
}

/* ---------------- 7-card → best 5-card ---------------- */

void copyFive(Card src[], Card dest[], int idx[]) {
    for (int i = 0; i < 5; i++)
        dest[i] = src[idx[i]];
}

/* all 21 combinations of 7 choose 5 */
int comb[21][5] = {
    {0,1,2,3,4},{0,1,2,3,5},{0,1,2,3,6},
    {0,1,2,4,5},{0,1,2,4,6},{0,1,2,5,6},
    {0,1,3,4,5},{0,1,3,4,6},{0,1,3,5,6},
    {0,1,4,5,6},{0,2,3,4,5},{0,2,3,4,6},
    {0,2,3,5,6},{0,2,4,5,6},{0,3,4,5,6},
    {1,2,3,4,5},{1,2,3,4,6},{1,2,3,5,6},
    {1,2,4,5,6},{1,3,4,5,6},{2,3,4,5,6}
};

HandType evaluateSeven(Card seven[]) {

    HandType best = HIGH_CARD;
    Card five[5];

    for (int i = 0; i < 21; i++) {

        copyFive(seven, five, comb[i]);

        HandType h = evaluateFive(five);

        if (h > best)
            best = h;
    }

    return best;
}

/* ---------------- MAIN ---------------- */

int main() {

    Card deck[DECK_SIZE];
    Card hand[HAND_SIZE];

    long long count[10] = {0};

    srand(time(NULL));

    createDeck(deck);

    for (long long i = 0; i < SIMULATIONS; i++) {

        shuffleDeck(deck);

        for (int j = 0; j < HAND_SIZE; j++)
            hand[j] = deck[j];

        HandType result = evaluateSeven(hand);

        count[result]++;
    }

    printf("7-Card Poker Monte Carlo Simulation\n");
    printf("Simulations: %d\n\n", SIMULATIONS);

    printf("High Card       : %.6f\n", (double)count[HIGH_CARD] / SIMULATIONS);
    printf("One Pair        : %.6f\n", (double)count[ONE_PAIR] / SIMULATIONS);
    printf("Two Pair        : %.6f\n", (double)count[TWO_PAIR] / SIMULATIONS);
    printf("Three Kind      : %.6f\n", (double)count[THREE_KIND] / SIMULATIONS);
    printf("Straight        : %.6f\n", (double)count[STRAIGHT] / SIMULATIONS);
    printf("Flush           : %.6f\n", (double)count[FLUSH] / SIMULATIONS);
    printf("Full House      : %.6f\n", (double)count[FULL_HOUSE] / SIMULATIONS);
    printf("Four Kind       : %.6f\n", (double)count[FOUR_KIND] / SIMULATIONS);
    printf("Straight Flush  : %.6f\n", (double)count[STRAIGHT_FLUSH] / SIMULATIONS);
    printf("Royal Flush     : %.6f\n", (double)count[ROYAL_FLUSH] / SIMULATIONS);

    return 0;
}