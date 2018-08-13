#include <iostream>
#include <array>
#include <ctime> 
#include <cstdlib>

enum Rank
{
    RANK_TWO,
    RANK_THREE,
    RANK_FOUR,
    RANK_FIVE,
    RANK_SIX,
    RANK_SEVEN,
    RANK_EIGHT,
    RANK_NINE,
    RANK_TEN,
    RANK_JACK,
    RANK_QUEEN,
    RANK_KING,
    RANK_ACE,
    MAX_RANKS
};

enum Suit
{
    SUIT_CLUB,
    SUIT_DIAMOND,
    SUIT_HEART,
    SUIT_SPADE,
    MAX_SUITS
};

struct Card 
{
    Rank rank;
    Suit suit;
};

void printCard(const Card &card)
{
    switch(card.rank)
    {
        case RANK_TWO:
            std::cout << "2";
            break;
        case RANK_THREE:
            std::cout << "3";
            break;
        case RANK_FOUR:
            std::cout << "4";
            break;
        case RANK_FIVE:
            std::cout << "5";
            break;
        case RANK_SIX:
            std::cout << "6";
            break;
        case RANK_SEVEN:
            std::cout << "7";
            break;
        case RANK_EIGHT:
            std::cout << "8";
            break;
        case RANK_NINE:
            std::cout << "9";
            break;
        case RANK_TEN:
            std::cout << "10";
            break;
        case RANK_JACK:
            std::cout << "J";
            break;
        case RANK_QUEEN:
            std::cout << "Q";
            break;
        case RANK_KING:
            std::cout << "K";
            break;
        case RANK_ACE:
            std::cout << "A";
            break;
        default:
            break;
    }

    switch(card.suit)
    {
        case SUIT_DIAMOND:
            std::cout << "D";
            break;
        case SUIT_HEART:
            std::cout << "H";
            break;
        case SUIT_CLUB:
            std::cout << "C";
            break;
        case SUIT_SPADE:
            std::cout << "S";
            break;
        default:
            break;
    }
}

void printDeck(const std::array<Card, 52> &deck)
{
    for (const auto &card : deck)
    {
        printCard(card);
        std::cout << " ";
    }

    std::cout << "\n";
}

void swapCard(Card &card1, Card &card2)
{
    Card temp = card1;
    card1 = card2;
    card2 = temp;
}

int getRandomNumber(int min, int max) {
    static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
    return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}

void shuffleDeck(std::array<Card, 52> &deck)
{
    for (int i = 0; i < 52; i++)
    {
        int randIndex = getRandomNumber(0, 51);
        swapCard(deck[i], deck[randIndex]);
    }
}

int getCardValue(const Card &card)
{
    switch (card.rank)
    {
        case RANK_TWO:
            return 2;
        case RANK_THREE:
            return 3;
        case RANK_FOUR:
            return 4;
        case RANK_FIVE:
            return 5;
        case RANK_SIX:
            return 6;
        case RANK_SEVEN:
            return 7;
        case RANK_EIGHT:
            return 8;
        case RANK_NINE:
            return 9;
        case RANK_ACE:
            return 11;
        default:
            return 10;
    }
}

bool playBlackjack(const std::array<Card, 52>  &deck) {
    const Card* cardPtr = &deck[0];
    int playerScore = 0;
    int dealerScore = 0;

    // deal the player 2 cards initially
    playerScore += getCardValue(*cardPtr++);
    playerScore += getCardValue(*cardPtr++);
    std::cout << "Your total score is: " << playerScore << "\n";

    // deal a card to the dealer (other card is face down and unknown)
    dealerScore += getCardValue(*cardPtr++);
    std::cout << "The dealer's score is: " << dealerScore << "\n";

    while (true)
    { 
        if (playerScore > 21)
        {
            return false;
        }

        char action;
        do
        {
            std::cout << "[H]it or [S]tand? ";
            std::cin >> action;
        } while (action != 'H' && action != 'S');
    
        if (action == 'H')
        {
            playerScore += getCardValue(*cardPtr++);
            std::cout << "Your score is now: " << playerScore << "\n";
        }
        else
        {
            std::cout << "Your final score is: " << playerScore << "\n";
            break;
        }
    }

    while (dealerScore < 17)
    {
        dealerScore += getCardValue(*cardPtr++);
        std::cout << "The dealer now has a score of: " << dealerScore << "\n";

        // player wins if dealer busted
        if (dealerScore > 21) {
               return true;
        }
    }

    return (playerScore > dealerScore);
}

int main()
{
    // set random seed to the initial time
    srand(static_cast<unsigned int>(time(0)));

    std::array<Card, 52> deck;

    int card = 0;
    for (int suit = 0; suit < MAX_SUITS; suit++)
    for (int rank = 0; rank < MAX_RANKS; rank++)
    {
        deck[card].suit = static_cast<Suit>(suit);
        deck[card].rank = static_cast<Rank>(rank);
        card++;
    }

    shuffleDeck(deck);

    if (playBlackjack(deck))
        std::cout << "You win!\n";
    else
        std::cout << "You lose!\n";

    return 0;
}




