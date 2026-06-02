/*
 * File: poker_monte_carlo.cpp
 * Author: Your Name
 *
 * Description:
 * This program simulates 7-card poker hands using a Monte Carlo
 * method. A deck of 52 cards is represented using a Card struct
 * containing an enumerated suit and a short pip value.
 *
 * The deck is shuffled randomly and 7-card hands are dealt.
 * The program evaluates the frequency of:
 *   - No Pair
 *   - One Pair
 *   - Two Pair
 *   - Three of a Kind
 *   - Full House
 *   - Four of a Kind
 *
 * At least 1,000,000 hands are generated and the resulting
 * probabilities are reported.
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <ctime>

using namespace std;

/*
 * Enumeration representing card suits.
 */
enum Suit {
    CLUBS,
    DIAMONDS,
    HEARTS,
    SPADES
};

/*
 * Structure representing a card.
 */
struct Card {
    Suit suit;
    short pip;
};

/*
 * Creates a standard 52-card deck.
 */
vector<Card> createDeck() {
    vector<Card> deck;

    for (int suit = CLUBS; suit <= SPADES; suit++) {
        for (short pip = 2; pip <= 14; pip++) {
            Card card;
            card.suit = static_cast<Suit>(suit);
            card.pip = pip;
            deck.push_back(card);
        }
    }

    return deck;
}

/*
 * Randomly shuffles a deck.
 */
void shuffleDeck(vector<Card>& deck) {
    static random_device rd;
    static mt19937 gen(rd());

    shuffle(deck.begin(), deck.end(), gen);
}

/*
 * Classification of hand types required
 * by the assignment.
 */
enum HandType {
    NO_PAIR,
    ONE_PAIR,
    TWO_PAIR,
    THREE_KIND,
    FULL_HOUSE,
    FOUR_KIND
};

/*
 * Evaluates a 7-card hand.
 */
HandType evaluateHand(const vector<Card>& hand) {

    int rankCount[15] = {0};

    for (const Card& card : hand) {
        rankCount[card.pip]++;
    }

    int pairs = 0;
    bool three = false;
    bool four = false;

    for (int i = 2; i <= 14; i++) {

        if (rankCount[i] == 4)
            four = true;

        else if (rankCount[i] == 3)
            three = true;

        else if (rankCount[i] == 2)
            pairs++;
    }

    if (four)
        return FOUR_KIND;

    if (three && pairs >= 1)
        return FULL_HOUSE;

    if (three)
        return THREE_KIND;

    if (pairs >= 2)
        return TWO_PAIR;

    if (pairs == 1)
        return ONE_PAIR;

    return NO_PAIR;
}

int main() {

    const long long SIMULATIONS = 1000000;

    long long noPair = 0;
    long long onePair = 0;
    long long twoPair = 0;
    long long threeKind = 0;
    long long fullHouse = 0;
    long long fourKind = 0;

    vector<Card> deck = createDeck();

    for (long long i = 0; i < SIMULATIONS; i++) {

        shuffleDeck(deck);

        vector<Card> hand(deck.begin(), deck.begin() + 7);

        HandType result = evaluateHand(hand);

        switch (result) {

            case NO_PAIR:
                noPair++;
                break;

            case ONE_PAIR:
                onePair++;
                break;

            case TWO_PAIR:
                twoPair++;
                break;

            case THREE_KIND:
                threeKind++;
                break;

            case FULL_HOUSE:
                fullHouse++;
                break;

            case FOUR_KIND:
                fourKind++;
                break;
        }
    }

    cout << "Monte Carlo Simulation Results\n";
    cout << "Hands Simulated: "
         << SIMULATIONS << "\n\n";

    cout << "No Pair      : "
         << (double)noPair / SIMULATIONS << endl;

    cout << "One Pair     : "
         << (double)onePair / SIMULATIONS << endl;

    cout << "Two Pair     : "
         << (double)twoPair / SIMULATIONS << endl;

    cout << "Three Kind   : "
         << (double)threeKind / SIMULATIONS << endl;

    cout << "Full House   : "
         << (double)fullHouse / SIMULATIONS << endl;

    cout << "Four Kind    : "
         << (double)fourKind / SIMULATIONS << endl;

    return 0;
}