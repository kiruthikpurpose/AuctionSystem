#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Constants
#define MAX_BIDDERS 10
#define MAX_ITEMS 10

// Struct definitions
typedef struct {
    char name[50];
    float amount;
} Bidder;

typedef struct {
    int bidderId;
    float bidAmount;
} Bid;

typedef struct {
    int auctionId;
    char itemName[50];
    Bid currentBid;
    Bidder bidders[MAX_BIDDERS];
    int numBidders;
} Auction;

// Function prototypes
void startAuction(Auction *auction, char *itemName);
void placeBid(Auction *auction, int bidderId, float bidAmount);
void determineWinner(Auction *auction);
void displayAuctionDetails(Auction *auction);

// Global variables
Auction auctions[MAX_ITEMS];
int numAuctions = 0;

int main() {
    // Example usage
    startAuction(&auctions[numAuctions++], "Painting");
    startAuction(&auctions[numAuctions++], "Antique");

    placeBid(&auctions[0], 1, 500.0);  // Bidder 1 bids $500 on the Painting
    placeBid(&auctions[0], 2, 600.0);  // Bidder 2 bids $600 on the Painting
    placeBid(&auctions[1], 1, 1000.0); // Bidder 1 bids $1000 on the Antique

    determineWinner(&auctions[0]);
    determineWinner(&auctions[1]);

    return 0;
}

// Function definitions

void startAuction(Auction *auction, char *itemName) {
    auction->auctionId = numAuctions; // Each auction gets a unique ID
    strcpy(auction->itemName, itemName);
    auction->currentBid.bidderId = -1; // Initialize with no current highest bidder
    auction->currentBid.bidAmount = 0.0;
    auction->numBidders = 0;
    printf("Auction for '%s' has begun.\n", itemName);
}

void placeBid(Auction *auction, int bidderId, float bidAmount) {
    if (bidAmount > auction->currentBid.bidAmount) {
        auction->currentBid.bidderId = bidderId;
        auction->currentBid.bidAmount = bidAmount;
        printf("Bidder %d has placed a bid of $%.2f on the '%s'.\n", bidderId, bidAmount, auction->itemName);
    } else {
        printf("Bidder %d's bid of $%.2f is not higher than the current highest bid.\n", bidderId, bidAmount);
    }
}

void determineWinner(Auction *auction) {
    if (auction->currentBid.bidderId == -1) {
        printf("No bids were placed for the '%s'.\n", auction->itemName);
    } else {
        printf("The winner of the '%s' auction is Bidder %d with a bid of $%.2f.\n", auction->itemName,
               auction->currentBid.bidderId, auction->currentBid.bidAmount);
    }
}

void displayAuctionDetails(Auction *auction) {
    printf("Auction ID: %d\n", auction->auctionId);
    printf("Item Name: %s\n", auction->itemName);
    printf("Current Highest Bid: $%.2f by Bidder %d\n", auction->currentBid.bidAmount,
           auction->currentBid.bidderId);
    printf("Number of Bidders: %d\n", auction->numBidders);
    printf("Bidders:\n");
    for (int i = 0; i < auction->numBidders; ++i) {
        printf("Bidder %d: %s - $%.2f\n", i + 1, auction->bidders[i].name, auction->bidders[i].amount);
    }
}
