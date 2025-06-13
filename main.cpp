#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <conio.h>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

void handleSpecialCard(int specialCardType);

// Color codes for Uno cards
const int BLACK = 0;
const int BLUE = 1;
const int GREEN = 2;
const int RED = 4;
const int YELLOW = 6;
const int WHITE = 7;

bool skipcardturn = false;  // Flag for skipping card
int currentColor = -1; 

//// Function to clear the screen
void clearScreen() {
    system("CLS");
}

// Function to set console text and background color
void setColor(int textColor, int bgColor) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, (bgColor << 4) | textColor); 	
}

void setcolormenu(int textColor) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, textColor);
}

// Function to display the main menu
void displayMenu() {
    
    setcolormenu(11); // Bright Cyan

    cout << "====================================================" << endl;
    cout << "|                                                  |" << endl;
    cout << "|             WELCOME TO THE GAME MENU             |" << endl;
    cout << "|                                                  |" << endl;
    cout << "====================================================" << endl;

    setcolormenu(14); // Yellow
    cout << "\n*************** MAIN MENU ***************" << endl;

    setcolormenu(13); // Purple
    
    cout << "1. Start New Game" << endl;
    cout << "2. Resume Game" << endl;
    cout << "3. View Histroy" << endl;
    cout << "4. Exit" << endl;

    setcolormenu(12); // Bright Red
    cout << "\nPlease enter your choice: ";

    setcolormenu(15); // white
}



// Function to set the card color based on its value
void setCardColor(int card) {
    // Blue cards: 0–100
    if (card < 100 && card >= 0) {
        setColor(WHITE, BLUE);
    }
    // Green cards: 100–200
    else if (card < 200) {
        setColor(WHITE, GREEN);
    }
    // Red cards: 200–300
    else if (card < 300) {
        setColor(WHITE, RED);
    }
    // Yellow cards: 300–400
    else if (card < 400) {
        setColor(WHITE, YELLOW);
    }
    // Black cards: 400+
    else if (card >= 400) {
        setColor(WHITE, BLACK);
    }
}

//Function to print uno on cards
void setUNoCardColor(int card) {
        setColor(WHITE, BLACK);
}

// Function to print the top/bottom border of a card
void printCard(int card) {
    setCardColor(card);
    cout << " ------ ";
    setColor(WHITE, BLACK);
    cout << " ";
}

// Function to print the upper or lower sections of a card
void printsec(int card) {
    setCardColor(card);
    cout << "-      -";
    setColor(WHITE, BLACK);
    cout << " ";
}

// Function to print the middle of the card with its value
void printCardValue(int card) {
    setCardColor(card);
    if (card % 100 == 10) {              // Skip card
        cout << "-  S   -";
    } else if (card % 100 == 11) {       // Reverse card
        cout << "-  R   -";
    } else if (card % 100 == 12) {       // Draw Two
        cout << "-  D2  -";
    } else if (card % 100 == 13) {       // Wild card
        cout << "-  W   -";
    } else if (card % 100 == 14) {       // Wild Draw Four
        cout << "-  W4  -";
    } else {                             // Numbered card
        if (card % 100 < 10) {
            cout << "-  0" << card % 100 << "  -";
        } else {
            cout << "-  " << card % 100 << "  -";
        }
    }
    setColor(WHITE, BLACK);
    cout << " ";
}


// Function to print the bottom border of a card
void printbase(int card) {
    setCardColor(card);
    cout << " ------ ";
    setColor(WHITE, BLACK);
    cout << " ";
}

void printuperUNOCard(int card) {
    setUNoCardColor(card);
    cout << " ------ ";
    setColor(WHITE, BLACK);
    cout << " ";
}

// Function to print the upper or lower sections of a card
void printLowerUNo(int card) {
    setUNoCardColor(card);
    cout << "-      -";
    setColor(WHITE, BLACK);
    cout << " ";
}

//Funtion to print UNO
void printUNO(int card) {
    setUNoCardColor(card);
    cout << "-  UNO -"; 
    setColor(WHITE, BLACK);
    cout << " ";
}

// Function to print the bottom border of a card
void printLowerUNo2(int card) {
    setUNoCardColor(card);
    cout << " ------ ";
    setColor(WHITE, BLACK);
    cout << " ";
}

// Function to display a player's hand
void printPlayerHand(const int player[], int playerSize) {
    // Top of cards
	for (int i = 0; i < playerSize; ++i) {
        printCard(player[i]);
    }
    cout << endl;
    
    // Upper section
	for (int i = 0; i < playerSize; ++i) {
        printsec(player[i]);
    }
    cout << endl;

	// Middle section with values
    for (int i = 0; i < playerSize; ++i) {
        printCardValue(player[i]);
    }
    cout << endl;
    
    // Lower section
	for (int i = 0; i < playerSize; ++i) {
        printsec(player[i]);
    }
    cout << endl;
	
	// Bottom of cards
	for (int i = 0; i < playerSize; ++i) {
        printbase(player[i]);
    }
    cout << endl;
}

// Function to display a player's hand UNO
void printPlayerHandUNO(const int player[], int playerSize) {
    // Top of cards
    for (int i = 0; i < playerSize; ++i) {
        printuperUNOCard(player[i]);
    }
    cout << endl;

    // Upper section
    for (int i = 0; i < playerSize; ++i) {
       printLowerUNo(player[i]);
    }
    cout << endl;

    // Middle section with values
    for (int i = 0; i < playerSize; ++i) {
        printUNO(player[i]);
    }
    cout << endl;

    // Lower section
    for (int i = 0; i < playerSize; ++i) {
        printLowerUNo(player[i]);
    }
    cout << endl;

    // Bottom of cards
    for (int i = 0; i < playerSize; ++i) {
        printLowerUNo2(player[i]);
    }
    cout << endl;
}

// Function to display the top card (discard pile)
void printTopCard(int topCard) {
    cout << "\n                 ";
    printCard(topCard);
    cout << "\n                 ";
    printsec(topCard);
    cout << "\n                 ";
    printCardValue(topCard);
    cout << "\n                 ";
    printsec(topCard);
    cout << "\n                 ";
    printbase(topCard);
    cout << endl;
}

void initializeDeck(int unodeck[][15]) {
    // Initialize colored cards
    // Initialize Red, Blue, Green, Yellow cards
 	// Initialize Red, Blue, Green, Yellow cards
    for (int color = 0; color < 4; ++color) {
        int rowStart = color * 2;  // Each color has 2 rows
        int colorBase = color * 100;  // Red -> 0, Blue -> 200, Green -> 400, Yellow -> 600

        // Row 0 (0 to 12), Row 1 (100 to 112) for each color
        for (int i = 0; i <= 12; ++i) {
            unodeck[rowStart][i] = colorBase + i;      // First set of cards
            unodeck[rowStart + 1][i] = colorBase + i;  // Second set of cards
        }

        // Fill unused columns with -1
        for (int i = 13; i < 15; ++i) {
            unodeck[rowStart][i] = -1;
            unodeck[rowStart + 1][i] = -1;
        }
    }

    // Initialize Wild and Wild Draw Four cards in row 8
    for (int i = 0; i < 4; ++i) {
        unodeck[8][i] = 413;  // Wild card
        unodeck[8][i + 4] = 414;  // Wild Draw Four card
    }

    // Fill unused columns in row 8 with -1
    for (int i = 8; i < 15; ++i) {
        unodeck[8][i] = -1;
    }
	unodeck[1][0]=-1;
 	unodeck[2][0]=-1;
 	unodeck[4][0]=-1;
    unodeck[6][0]=-1;

}

void shuffleDeck(int unodeck[][15]) {

    int shuffle = 0; // Count successful shuffles
    while (shuffle < 50) { // Ensure exactly 50 valid swaps
        
		int row1 = rand() % 9;
        int col1 = rand() % 15;
        int row2 = rand() % 9;
        int col2 = rand() % 15;

        // Swap only if both cards are valid
        if (unodeck[row1][col1] != -1 && unodeck[row2][col2] != -1) {
            int temp = unodeck[row1][col1];
            unodeck[row1][col1] = unodeck[row2][col2];
            unodeck[row2][col2] = temp;

            ++shuffle; // Increment swap count
        }
    }
}

void dealCards(int player1[], int& player1Size, int player2[], int& player2Size, int unodeck[][15], int& deckIndex) {
    // Ensure that the deck has enough cards left for both players
    if (deckIndex + 14 >= 108) {
        cout << "Not enough cards in the deck!" << endl;
        return; // Prevent dealing if the deck is out of cards
    }

    // Reset the sizes for both players
    player1Size = 0;
    player2Size = 0;

    // Deal 7 cards to each player
    while (player1Size < 7 || player2Size < 7) {
        // Deal card to player 1 if the card is not -1 nad -2
        if (unodeck[deckIndex / 15][deckIndex % 15] != -1 && player1Size < 7 && unodeck[deckIndex / 15][deckIndex % 15] != -2) {
            player1[player1Size++] = unodeck[deckIndex / 15][deckIndex % 15];
            unodeck[deckIndex / 15][deckIndex % 15] =  -2;
			deckIndex++;
    
        } else {
            deckIndex++; // Skip the -1 card and -2 card
        }

        // Deal card to player 2 if the card is not -1 and -2
        if (unodeck[deckIndex / 15][deckIndex % 15] != -1 && player2Size < 7 && unodeck[deckIndex / 15][deckIndex % 15] != -2) {
            player2[player2Size++] = unodeck[deckIndex / 15][deckIndex % 15];
            unodeck[deckIndex / 15][deckIndex % 15] =  -2;
			deckIndex++;
            
        } else {
            deckIndex++; // Skip the -1 card and -2 card
        }
    }
}

//Discard Pile Function
void UpdateDiscardPile(int disPile[], int topCard, int& discard , int unodeck[][15], int& deckIndex) {
    
	if(discard<109){
		disPile[discard] = topCard;  //Updating the discard pIle
	}
	
	if(deckIndex > 135){
		
		//Shuffling the discard Pile	
		for( int i = 0 ; i < 50 ;  i++){
			int index = rand() % 108;
		
			int temp = disPile[i];
        	disPile[i] = disPile[index];
        	disPile[index] = temp;	
		}
	
		int k = 0;	
		//Asigning the discardpile to the unodeck/
		for(int i = 0 ; i < 9 ; i++){
			for (int j  = 0 ;  j < 15 ; j++){
				if(k >= discard-1){
					break;
				}else{
				unodeck[i][j] = disPile[k];
				k++;
				}
			}
		}
		deckIndex = 0;
		discard = 1;
	}
}

//Function to call UNO
bool callUno(int& handSize, int& deckIndex, int playerHand[], int unodeck[][15] , char& choice) {
   
    if ((choice == 'u' || choice == 'U') && handSize == 2) {
        
		return true;
		
	} else { 
        	//Penalty for not calling UNO and for calling early.
            for (int i = 0; i < 2; ++i) {
            	while( unodeck[deckIndex / 15][deckIndex % 15] == -1 || unodeck[deckIndex / 15][deckIndex % 15] == -2){
            		deckIndex++;
				    if (deckIndex >= 108) {
        				cout << "No cards left in the deck!\n";
        				break;  // Exit the loop if there are no more cards to draw
    				}
				}
					
                int drawnCard = unodeck[deckIndex / 15][deckIndex % 15];  // Get the next card in the deck
                unodeck[deckIndex / 15][deckIndex % 15] = -2;
				deckIndex++; 

                playerHand[handSize] = drawnCard;
                handSize++;
                printCardValue(drawnCard); 
            }
            return false; 
        }
    }
    

// Function to check if a play is valid
bool isValidPlay(int playerCard, int topCard) {

    if (currentColor != -1) { // A Wild card has set a color
        return (playerCard / 100 == currentColor) || (playerCard / 100 == 4); // Match chosen color or Wild card
    }
    return (playerCard / 100 == topCard / 100) || (playerCard % 100 == topCard % 100) || (playerCard / 100 == 4);
}

void playTurn(int player[], int& playerSize, int& topCard, int unodeck[][15], int& deckIndex, const string& playerName, bool& skipTurn, int nextPlayer[] , int& player2Size ,const string& nextPlayerName, int& discard, int discardPile[] ,bool& exit)
{
     int choice1;
	// Display player hand and top card
   	clearScreen();
    
	cout << playerName << "'s Hand:\n";
    printPlayerHand(player, playerSize);
    
	cout << "Top Card:\n";
    printTopCard(topCard);
    
	cout << nextPlayerName << "'s Hand:\n";
    printPlayerHandUNO(nextPlayer, player2Size); // Make the cards of the nextplayer say UNO

	cout<<endl;
	cout << endl;
	
	cout<<  "                        "<<playerName << "'s Turn." <<endl;
	
	cout<< endl;
	
    // Check if the player has a valid card to play
    bool hasPlayableCard = false;
    
	for (int i = 0; i < playerSize; ++i) {
        if (isValidPlay(player[i], topCard)) {
            hasPlayableCard = true;
            break; // Found a playable card, no need to continue checking
        }
    }
	
	if(!hasPlayableCard && deckIndex>135){
			UpdateDiscardPile(discardPile, topCard, discard , unodeck, deckIndex);
	}

    // Ask the player what they want to do: Play a card or Draw a card
    cout << "Do you want to play a card or draw a card? (1 for play, 0 for draw) (E for exit): ";
    char choice;
    cin >> choice;

	if(playerSize >= 2 &&  (choice == 'u' || choice == 'U')){
    	//Uno call
    	if(callUno( playerSize, deckIndex, player, unodeck , choice)){
    		cout<<"You called UNO sucessfully."<<endl;
    		cout << "Do you want to play a card or draw a card? (1 for play, 0 for draw):";
			cin >> choice;
		}else{
			cout << "Penalty applied for calling UNO earlier!" << endl;
		}
	}else if((choice != 'u' || choice != 'U') && playerSize == 2 && hasPlayableCard){
		
		if(callUno( playerSize, deckIndex, player, unodeck, choice)){
    		cout<<"You called UNO sucessfully."<<endl;
		}else{
			cout << "Penalty applied for not calling UNO!" << endl;
		}
	}
    //TO exit the game.
    if(choice == 'E' || choice == 'e'){
		char confirmation;
		cout << "Do you really want to exit the game? (Y for yes , N for Continue)" << endl;
		cin >> confirmation;
		
		if(confirmation == 'y' || confirmation == 'Y'){
			cout<< "Exiting the game..." <<endl;
			exit = true;
			return;
		}else{
			cout << "Do you want to play a card or draw a card? (1 for play, 0 for draw):";
			cin >> choice;
		}
		
	}
	
    // If the player chooses to play a card
    if (choice == '1') {
        if (!hasPlayableCard) {
            cout << "You don't have a valid card to play. Please draw a card.\n";
            skipTurn = true; // Skip the turn if player cannot play
        }else{
            // If the player has a valid card, let them choose which card to play
            cout << "Choose a card to play (0 to " << playerSize - 1 << "): ";
			cin >> choice1;

            // Ensure the choice is valid
            while (choice1 < 0 || choice1 >= playerSize || !isValidPlay(player[choice1], topCard)) {
                cout << "Invalid choice. Choose again: ";
                cin >> choice1;
            }

            // Play the chosen card
            discard++;  //for discard pile
            topCard = player[choice1];
            player[choice1] = player[--playerSize]; // Remove the card from hand
            cout << "You played: ";
            printCardValue(topCard);
            cout << endl;

            // Handle special card effects (Skip, Reverse, Wild, etc.)
            int cardType = topCard % 100;  // Get the special card type (e.g., Skip, Reverse, Draw Two, Wild)
            handleSpecialCard(cardType);   // Call the handleSpecialCard function
           
            if (cardType == 14) {
                // Wild Draw Four is played, so the next player must draw 4 cards
                cout << playerName << " played a Wild Draw Four card! " << endl;
                
				for (int i = 0; i < 4; ++i) {
                    // Draw a card for the next player
                    while( unodeck[deckIndex / 15][deckIndex % 15] == -1 || unodeck[deckIndex / 15][deckIndex % 15] == -2){
            		 deckIndex++;
				    	if (deckIndex >= 108) {
        					cout << "No cards left in the deck!\n";
        					break;  // Exit the loop if there are no more cards to draw
    					}
					}
					
                    int drawnCard = unodeck[deckIndex / 15][deckIndex % 15];  // Get the next card in the deck
                    unodeck[deckIndex / 15][deckIndex % 15] = -2;
					deckIndex++;  // Increment the deck index

                    // Add the drawn card to the next player's hand
                    nextPlayer[player2Size] = drawnCard;  // Assuming nextPlayer is the array holding the next player's cards
                    player2Size++;  // Increase the hand size of nextPlayer
                    cout << nextPlayerName << " drew a card: ";
                    printCardValue(drawnCard);  // Display the card drawn
                }
            }
            
            if (cardType == 12) {
                // Wild Draw Four is played, so the next player must draw 4 cards
                cout << playerName << " played a Draw Two card! " << endl;
                
				for (int i = 0; i < 2; ++i) {
                    // Draw a card for the next player
                    while( unodeck[deckIndex / 15][deckIndex % 15] == -1 || unodeck[deckIndex / 15][deckIndex % 15] == -2){
            		 deckIndex++;
				    	if (deckIndex >= 108) {
        					cout << "No cards left in the deck!\n";
        					break;  // Exit the loop if there are no more cards to draw
    					}
					}
					
                    int drawnCard = unodeck[deckIndex / 15][deckIndex % 15];  // Get the next card in the deck
                    unodeck[deckIndex / 15][deckIndex % 15] = -2;
					deckIndex++;  // Increment the deck index

                    // Add the drawn card to the next player's hand
                    nextPlayer[player2Size] = drawnCard;  // Assuming nextPlayer is the array holding the next player's cards
                    player2Size++;  // Increase the hand size of nextPlayer
                    cout << nextPlayerName << " drew a card: ";
                    printCardValue(drawnCard);  // Display the card drawn
                }
            }
            
		    if (currentColor != -1 && topCard / 100 != 4) {
    			currentColor = -1; // Reset color restriction for regular cards
			}
		

        }
    } else if (choice == '0') {
        
		if (hasPlayableCard) {
            cout << "You cannot draw a card, you have a valid card to play.\n";
            // Ask the player to play the card instead
            cout << "Please play a card.\n";
            skipTurn = true; // Skip the turn if the player refuses to play
        } else {
            // Player draws a card
            cout << "Drawing a card...\n";
            
            while( unodeck[deckIndex / 15][deckIndex % 15] == -1 || unodeck[deckIndex / 15][deckIndex % 15] == -2){
            	deckIndex++;
				   if (deckIndex >= 108) {
        			cout << "No cards left in the deck!\n";
        			break;  // Exit the loop if there are no more cards to draw
    				}
			}
			
			int drawnCard = unodeck[deckIndex / 15][deckIndex % 15];
			unodeck[deckIndex / 15][deckIndex % 15] = -2;
			deckIndex++;
            cout << "You drew: ";
            printCardValue(drawnCard);
            cout << endl;

			  // Add the drawn card to the player's hand
            if (playerSize < 108) { // Assuming maximum hand size of 20
                player[playerSize] = drawnCard;
                playerSize++;
                cout << "Card added to your hand.\n";
            } 
            
			// If the drawn card is playable, ask the player if they want to play it
           if (isValidPlay(drawnCard, topCard)) {
  			
			   cout << "The drawn card is playable! Do you want to play it? (1 for yes, 0 for no): ";
   			   cin >> choice1;
  				
				if (choice1 == 1) {
        			
					topCard = drawnCard;
        			discard++;
       				cout << "You played: ";
        			printCardValue(topCard);
      				cout << endl;

        			// Remove the card from the player's hand
        			playerSize--; // Decrease the hand size first
       				
					for (int i = 0; i < playerSize; ++i)
					{
           				if (player[i] == drawnCard) {
                			for (int j = i; j < playerSize; ++j) {
                    			player[j] = player[j + 1]; // Shift cards to fill the gap
                				}
                			break;
           				}
        			}
        
        			 // Handle special card effects (Skip, Reverse, Wild, etc.)
        			int cardType = topCard % 100;  // Get the special card type (e.g., Skip, Reverse, Draw Two, Wild)
        			handleSpecialCard(cardType);   // Call the handleSpecialCard function
            		
					if (cardType == 14) {
                	 // Wild Draw Four is played, so the next player must draw 4 cards
                		cout << playerName << " played a Wild Draw Four card! " << endl;
                		
						for (int i = 0; i < 4; ++i) {
                    		 while( unodeck[deckIndex / 15][deckIndex % 15] == -1 || unodeck[deckIndex / 15][deckIndex % 15] == -2){
            					deckIndex++;
				    			
								if (deckIndex >= 108) {
        							cout << "No cards left in the deck!\n";
        							break;  // Exit the loop if there are no more cards to draw
    							}
							}
					
                    		int drawnCard = unodeck[deckIndex / 15][deckIndex % 15];  // Get the next card in the deck
                    		unodeck[deckIndex / 15][deckIndex % 15] = -2;
							deckIndex++; 

					        // Add the drawn card to the next player's hand
                    		nextPlayer[player2Size] = drawnCard;  // Assuming nextPlayer is the array holding the next player's cards
                    		player2Size++;  // Increase the hand size of nextPlayer
                    		cout << nextPlayerName << " drew a card: ";
                    		printCardValue(drawnCard);  // Display the card drawn
               			}
            		}
            
            		if (cardType == 12) {
                		// Wild Draw Two is played, so the next player must draw 2 cards
                		cout << playerName << " played a Draw Two card! " << endl;
                
						for (int i = 0; i < 2; ++i) {
                    		// Draw a card for the next player
                    		 while( unodeck[deckIndex / 15][deckIndex % 15] == -1 || unodeck[deckIndex / 15][deckIndex % 15] == -2){
            					deckIndex++;
				    			if (deckIndex >= 108) {
        							cout << "No cards left in the deck!\n";
        							break;  // Exit the loop if there are no more cards to draw
    							}
							}
					
                    		int drawnCard = unodeck[deckIndex / 15][deckIndex % 15];  // Get the next card in the deck
                    		unodeck[deckIndex / 15][deckIndex % 15] = -2;
							deckIndex++;  

                    		// Add the drawn card to the next player's hand
                    		nextPlayer[player2Size] = drawnCard;  // Assuming nextPlayer is the array holding the next player's cards
                    		player2Size++;  // Increase the hand size of nextPlayer
                    		cout << nextPlayerName << " drew a card: ";
                    		printCardValue(drawnCard);  // Display the card drawn
                		}
            		}
            
                    
           			if (currentColor != -1 && topCard / 100 != 4) {
    					currentColor = -1; // Reset color restriction for regular cards
					}

		            return; // Turn ends after playing the drawn card
                }
            }

            // If the drawn card is not playable, skip the turn
            cout << "The drawn card is not playable. Your turn is skipped.\n"; 
		
        }
    } else {
        cout << "Invalid choice.\n";
        skipTurn = true; // If the player enters an invalid choice, skip the turn to get back that player.
    }
}

void handleSpecialCard(int specialCardType) {
    switch (specialCardType) {
        
		case 10: // Skip card
            cout << "Next player's turn is skipped." << endl; 
            skipcardturn = true;  // Skip the next player's turn
            break;

        case 11: // Reverse card
            cout << "The turn order is reversed." << endl;
            skipcardturn = true; 
            break;

        case 12: // Draw Two card
            cout << "Next player must draw 2 cards and skip their turn." << endl;
            skipcardturn = true;  // Skip the next player's turn
            break;

        case 13:  // Wild card (choose the next color)
    		cout << "You played a Wild card! Choose the next color (0 = Blue, 1 = Green, 2 = Red, 3 = Yellow): ";
    		int colorChoice;
    		cin >> colorChoice;
   		 	
			while (colorChoice < 0 || colorChoice > 3) {
        		cout << "Invalid choice. Choose again (0 = Blue, 1 = Green, 2 = Red, 3 = Yellow): ";
        		cin >> colorChoice;
   		 	}
   		 
			currentColor = colorChoice;  // Set the chosen color
   		    cout << "Next color is: " << (colorChoice == 0 ? "Blue" : colorChoice == 1 ? "Green" : colorChoice == 2 ? "Red" : "Yellow") << endl;
   		    break;

		case 14:  // Wild Draw Four card
    		cout << "You played a Wild Draw Four card! Choose the next color (0 = Blue, 1 = Green, 2 = Red, 3 = Yellow): ";
    		cin >> colorChoice;
    		
			while (colorChoice < 0 || colorChoice > 3) {
        		cout << "Invalid choice. Choose again (0 = Blue, 1 = Green, 2 = Red, 3 = Yellow): ";
        		cin >> colorChoice;
   			}
    
			currentColor = colorChoice;  // Set the chosen color
    		cout << "Next color is: " << (colorChoice == 0 ? "Blue" : colorChoice == 1 ? "Green" : colorChoice == 2 ? "Red" : "Yellow") << endl;
    		skipcardturn = true;  // Skip the next player's turn
   		    break;
	}
}



void saveLoadGameResult(int player[], int& playerSize, int& topCard, int unodeck[][15], int& deckIndex, const string& playerName, bool& skipTurn, int nextPlayer[] , int& player2Size ,const string& nextPlayerName, int& discard, int discardPile[], int currentplayer,const string& filename, int& choice, int& p1wins, int& p2wins ){

	if(choice == 1){
		ofstream file(filename.c_str());// using Open file for output becuz had no other option
    
		if (file.is_open()) {
    
    		file << playerSize << endl; // Player one stored
        
			for (int i = 0; i < playerSize; ++i) {
            	file << player[i] << " ";
        	}
        	file << endl;
		
			file << topCard << endl;
			file << deckIndex <<endl;

        	file << 9 << " " << 15 << endl; // unodeck stored
        	
			for (int i = 0; i < 9; ++i) {
            	for (int j = 0; j < 15; ++j) {
                	file << unodeck[i][j] << " ";
            	}
            	file << endl;
        	}
        
       		file << playerName << endl; // player name stored
       		file << skipTurn << endl; 
        
			file << player2Size << endl; // again same as above
        	
			for (int i = 0; i < playerSize; ++i) {
            	file << nextPlayer[i] << " ";
        	}
        	file << endl;
		
			file << nextPlayerName << endl;
		
			file << 108 << endl; 
        	for (int i = 0; i < 108; ++i) {
            	file << discardPile[i] << " ";
        	}
        	file << endl;
        
			file << discard <<endl;
			file << currentplayer <<endl;
        
			file.close();
        	cout << "Game saved successfully!\n";
    	}
    }
    //Loading the game here
	else if(choice == 2){

    	ofstream file(filename.c_str());
    	
		if (file.is_open()) {

        	file << playerSize << endl;
        	for (int i = 0; i < playerSize; ++i) {
            	file << player[i] << " ";
        	}
        	file << endl;

        	file << topCard << endl;
        	file << deckIndex << endl;

        	for (int i = 0; i < 9; ++i) {
            	for (int j = 0; j < 15; ++j) {
                	file << unodeck[i][j] << " ";
            	}
            	file << endl;
        	}

        	file << player2Size << endl;
        	for (int i = 0; i < player2Size; ++i) {
            	file << nextPlayer[i] << " ";
        	}
        	file << endl;

        	for (int i = 0; i < 108; ++i) {
            	file << discardPile[i] << " ";
        	}
        	file << endl;

        	file << discard << endl;
        	file << currentplayer << endl;
        	file << skipTurn << endl;

        	file.close();
		}
	}else if( choice == 3){
		ofstream file(filename.c_str());// using Open file for output becuz had no other option
    
		if (file.is_open()) {
		
			file <<  p2wins << endl;
			file <<	 p1wins	 << endl;
			
			file.close();
		}
    	
	}
}


int main() {
    int choice;

	srand(time(0));
    
	int unodeck[9][15]; // Unodeck of 9 by 15 
    int player1Hand[108], player2Hand[108]; // Both player hands.
	int player1HandSize = 0, player2HandSize = 0; // Hand sizes
    int deckIndex = 0; 
	bool skipTurn = false; //For invalid calls
    int topCard = 0; //Top card of the deck.
	int discardPile[108] = {-1}; // Dicard Pile of 106
	int discard = 0;
    int currentPlayer = 1;
    bool exit = false;  // to exit game at anytime			
	string filename = "Save.txt";
	int player1WIns = 0;
	int player2WIns = 0;
	
    while (true) {
        system("cls"); // Clear the console
        displayMenu();

        cin >> choice;

        switch (choice) {
            case 1:
                cout << "\nStarting a new game..." << endl;
                getch();
                
				initializeDeck(unodeck); //Initializing the deck
    			shuffleDeck(unodeck); // Shuffling the deck
    			dealCards(player1Hand, player1HandSize, player2Hand, player2HandSize, unodeck, deckIndex); //Dealing card to the players
       
				while (unodeck[deckIndex / 15][deckIndex % 15] == -1 || unodeck[deckIndex / 15][deckIndex % 15] == 14 || unodeck[deckIndex / 15][deckIndex % 15] == 13) {
    				deckIndex++; // Move to the next card in the deck
				}
	
				topCard = unodeck[deckIndex / 15][deckIndex % 15];
				deckIndex++; // Incrementing after assigning to the topCard to prepare it for the next draw
				discardPile[discard] = topCard;
				discard++;
    			

    			while (!exit) {
      
    				if (skipcardturn) {
            			currentPlayer = (currentPlayer == 1) ? 2 : 1;
						cout << "Skipping turn for Player " << currentPlayer << "...\n";
            			skipcardturn = false;  // Reset skipcardturn for the next round
            			continue;  // Go to the next iteration of the loop (same player keeps turn)
        			}	
      	
					if (skipTurn) {
            			cout << "Skipping turn for Player " << currentPlayer << "...\n";
            			skipTurn = false;  // Reset skipTurn for the next round
						continue;  // Go to the next iteration of the loop (same player keeps turn)
        			}
    	
					if (currentPlayer == 1) {
    					// Player 1's turn
    		
    					playTurn(player1Hand, player1HandSize, topCard, unodeck, deckIndex, "Player 1", skipTurn,player2Hand, player2HandSize , "Player 2", discard, discardPile, exit); 
  	        
						UpdateDiscardPile(discardPile, topCard, discard, unodeck,deckIndex);
						
						if(exit){
							exit = false;
							saveLoadGameResult(player1Hand, player1HandSize, topCard, unodeck, deckIndex, "Player 1", skipTurn,player2Hand, player2HandSize , "Player 2", discard, discardPile,currentPlayer , filename , choice ,player1WIns,player2WIns);
							break;
						}
						
    					if (player1HandSize == 0) {
    						cout<<endl;
        					cout << "Player 1 wins! Congratulations!\n";
        					player1WIns++;
        					getch();
							break;
    					}

					} else {
    					// Player 2's turn

						playTurn(player2Hand, player2HandSize, topCard, unodeck, deckIndex, "Player 2", skipTurn,player1Hand, player1HandSize, "Player 1", discard, discardPile, exit);
     		
						UpdateDiscardPile(discardPile, topCard, discard , unodeck,deckIndex);
			
						if(exit){
							exit = false;
							saveLoadGameResult(player1Hand, player1HandSize, topCard, unodeck, deckIndex, "Player 1", skipTurn,player2Hand, player2HandSize , "Player 2", discard, discardPile, currentPlayer,filename ,choice,player1WIns,player2WIns);
							break;
						}
						
						if (player2HandSize == 0) {
							cout<<endl;
        					cout << "Player 2 wins! Congratulations!\n";
        					player2WIns++;
        					getch();
							break;
    					}

					}
    	  	   		// After the turn, switch to the next player
  		 			if (!skipTurn) {
            			currentPlayer = (currentPlayer == 1) ? 2 : 1;  // Switch to the other player only if skipTurn is false
        			}

    				getch();
				}
               
			    break;
			    
            case 2:
                cout << "\nLoading game..." << endl;
                saveLoadGameResult(player1Hand, player1HandSize, topCard, unodeck, deckIndex, "Player 1", skipTurn,player2Hand, player2HandSize , "Player 2", discard, discardPile, currentPlayer, filename ,choice,player1WIns,player2WIns );
				getch();    			

    			while (!exit) {
      
    				if (skipcardturn) {
            			currentPlayer = (currentPlayer == 1) ? 2 : 1;
						cout << "Skipping turn for Player " << currentPlayer << "...\n";
            			skipcardturn = false;  // Reset skipcardturn for the next round
            			continue;  // Go to the next iteration of the loop (same player keeps turn)
        			}	
      	
					if (skipTurn) {
            			cout << "Skipping turn for Player " << currentPlayer << "...\n";
            			skipTurn = false;  // Reset skipTurn for the next round
						continue;  // Go to the next iteration of the loop (same player keeps turn)
        			}
    	
					if (currentPlayer == 1) {
    					// Player 1's turn
    		
    					playTurn(player1Hand, player1HandSize, topCard, unodeck, deckIndex, "Player 1", skipTurn,player2Hand, player2HandSize , "Player 2", discard, discardPile, exit); 
  	        
						UpdateDiscardPile(discardPile, topCard, discard, unodeck,deckIndex);
						
						if(exit){
							exit = false;
							saveLoadGameResult(player1Hand, player1HandSize, topCard, unodeck, deckIndex, "Player 1", skipTurn,player2Hand, player2HandSize , "Player 2", discard, discardPile,currentPlayer , filename, choice, player1WIns,player2WIns);
							break;
						}
						
    					if (player1HandSize == 0) {
    						cout<< endl;
        					cout << "Player 1 wins! Congratulations!\n";
        					player1WIns++;
							getch();
							break;
    					}

					} else {
    					// Player 2's turn

						playTurn(player2Hand, player2HandSize, topCard, unodeck, deckIndex, "Player 2", skipTurn,player1Hand, player1HandSize, "Player 1", discard, discardPile, exit);
     		
						UpdateDiscardPile(discardPile, topCard, discard , unodeck,deckIndex);
			
						if(exit){
							exit = false;
							saveLoadGameResult(player1Hand, player1HandSize, topCard, unodeck, deckIndex, "Player 1", skipTurn,player2Hand, player2HandSize , "Player 2", discard, discardPile, currentPlayer,filename, choice,player1WIns,player2WIns);
							break;
						}
						
						if (player2HandSize == 0) {
							cout<<endl;
        					cout << "Player 2 wins! Congratulations!\n";
        					player1WIns++;
							getch();
							break;
    					}

					}
    	  	   		// After the turn, switch to the next player
  		 			if (!skipTurn) {
            			currentPlayer = (currentPlayer == 1) ? 2 : 1;  // Switch to the other player only if skipTurn is false
        			}

    				getch();
				}
              
                break;
            case 3:
                cout << "\nViewing Histroy..." << endl;
                
				saveLoadGameResult(player1Hand, player1HandSize, topCard, unodeck, deckIndex, "Player 1", skipTurn,player2Hand, player2HandSize , "Player 2", discard, discardPile, currentPlayer,filename, choice ,player1WIns,player2WIns);
            	cout <<"Player 1's Win's  :" <<player1WIns <<endl;
				cout <<"Player 2's Win's  :" << player2WIns <<endl;	
				getch();    
        
                break;
            case 4:
                cout << "\nExiting... Goodbye!" << endl;
                getch();
                return 0;
            default:
                cout << "\nInvalid choice. Please try again." << endl;
                getch();
        }

    }
    return 0;
}

