/*
    Program 2: Wumpus, version 2 (dynamic array)

    Course: CS 211, Fall 2022, Wed 8am lab
    Systems: Mac using Replit 
    Author: Jennifer Le, jle34
*/
#include <stdbool.h> // for bool variables
#include <stdio.h>   
#include <stdlib.h> // for srand

//--------------------------------------------------------------------------------
void displayCave() {
  printf("       ______18______             \n"
         "      /      |       \\           \n"
         "     /      _9__      \\          \n"
         "    /      /    \\      \\        \n"
         "   /      /      \\      \\       \n"
         "  17     8        10     19       \n"
         "  | \\   / \\      /  \\   / |    \n"
         "  |  \\ /   \\    /    \\ /  |    \n"
         "  |   7     1---2     11  |       \n"
         "  |   |    /     \\    |   |      \n"
         "  |   6----5     3---12   |       \n"
         "  |   |     \\   /     |   |      \n"
         "  |   \\       4      /    |      \n"
         "  |    \\      |     /     |      \n"
         "  \\     15---14---13     /       \n"
         "   \\   /            \\   /       \n"
         "    \\ /              \\ /        \n"
         "    16---------------20           \n"
         "\n");
}
//--------------------------------------------------------------------------------
void displayInstruction(){
    printf("Hunt the Wumpus: \n"
        "The Wumpus lives in a completely dark cave of 20 rooms. Each \n"
        "room has 3 tunnels leading to other rooms. \n\n"
        "Hazzards: \n"
        "1. Two rooms have bottomless pits in them. If you go there you fall and die. \n"
        
        "2. Two other rooms have super-bats. If you go there, the bats grab you and \n"
        "   fly you to some random room, which could be troublesome. Then those bats go \n"
        "   to a new room different from where they came from and from the other bats. \n"
        
        "3. The Wumpus is not bothered by the pits or bats, as he has sucker feet and \n"
        "   is too heavy for bats to lift. Usually he is asleep. Two things wake \n"
        "   him up: Anytime you shoot an arrow, or you entering his room. The Wumpus \n"
        "   will move into the lowest-numbered adjacent room anytime you shoot an arrow. \n"
        "   When you move into the Wumpus' room, then he wakes and moves if he is in an \n"    
        "   odd-numbered room, but stays still otherwise. After that, if he is in your \n"
        "   room, he snaps your neck and you die! \n\n"
        
        "Moves: \n"
        "On each move you can do the following, where input can be upper or lower-case: \n"
        
        "1. Move into an adjacent room. To move enter 'M' followed by a space and \n"
        "   then a room number.\n"
        
        "2. Shoot your guided arrow through a list of up to three adjacent rooms, which \n"
        "   you specify. Your arrow ends up in the final room.\n"                          
        "   To shoot enter 'S' followed by the number of rooms (1..3), and then the \n"      
        "   list of the desired number (up to 3) of adjacent room numbers, separated \n"     
        "   by spaces. If an arrow can't go a direction because there is no connecting \n" 
        "   tunnel, it ricochets and moves to the lowest-numbered adjacent room and \n"     
        "   continues doing this until it has traveled the designated number of rooms. \n"  
        "   If the arrow hits the Wumpus, you win! If the arrow hits you, you lose. You  \n"
        "   automatically pick up the arrow if you go through a room with the arrow in   \n"
        "   it. \n"
        
        "3. Enter 'R' to reset the person and hazard locations, useful for testing. \n"     
        "4. Enter 'C' to cheat and display current board positions. \n"                      
        "5. Enter 'D' to display this set of instructions.  \n"                             
        "6. Enter 'P' to print the maze room layout.  \n"                                   
        "7. Enter 'X' to exit the game.   \n\n"                                                                                   
        "Good luck! \n\n");
}
//--------------------------------------------------------------------------------
// takes in a 2D array adjacentRooms[i][j] and initializes the value of each 
// adjacent room where elements at index j are the adjacent rooms of room i
void initializeRooms(int **adjacentRooms) {
    adjacentRooms[0][0] = 0;   adjacentRooms[0][1] = 0;   adjacentRooms[0][2] = 0; 
    adjacentRooms[1][0] = 2;   adjacentRooms[1][1] = 5;   adjacentRooms[1][2] = 8; 
    adjacentRooms[2][0] = 1;   adjacentRooms[2][1] = 3;   adjacentRooms[2][2] = 10;
    adjacentRooms[3][0] = 2;   adjacentRooms[3][1] = 4;   adjacentRooms[3][2] = 12;
    adjacentRooms[4][0] = 3;   adjacentRooms[4][1] = 5;   adjacentRooms[4][2] = 14;
    adjacentRooms[5][0] = 1;   adjacentRooms[5][1] = 4;   adjacentRooms[5][2] = 6;
    adjacentRooms[6][0] = 5;   adjacentRooms[6][1] = 7;   adjacentRooms[6][2] = 15;
    adjacentRooms[7][0] = 6;   adjacentRooms[7][1] = 8;   adjacentRooms[7][2] = 17;
    adjacentRooms[8][0] = 1;   adjacentRooms[8][1] = 7;   adjacentRooms[8][2] = 9;
    adjacentRooms[9][0] = 8;   adjacentRooms[9][1] = 10;  adjacentRooms[9][2] = 18;
    adjacentRooms[10][0] = 2;  adjacentRooms[10][1] = 9;  adjacentRooms[10][2] = 11;
    adjacentRooms[11][0] = 10; adjacentRooms[11][1] = 12; adjacentRooms[11][2] = 19;
    adjacentRooms[12][0] = 13; adjacentRooms[12][1] = 11; adjacentRooms[12][2] = 3;  
    adjacentRooms[13][0] = 12; adjacentRooms[13][1] = 14; adjacentRooms[13][2] = 20;
    adjacentRooms[14][0] = 4;  adjacentRooms[14][1] = 13; adjacentRooms[14][2] = 15;
    adjacentRooms[15][0] = 6;  adjacentRooms[15][1] = 14; adjacentRooms[15][2] = 16;
    adjacentRooms[16][0] = 15; adjacentRooms[16][1] = 17; adjacentRooms[16][2] = 20;
    adjacentRooms[17][0] = 7;  adjacentRooms[17][1] = 16; adjacentRooms[17][2] = 8;
    adjacentRooms[18][0] = 9;  adjacentRooms[18][1] = 17; adjacentRooms[18][2] = 19;
    adjacentRooms[19][0] = 11; adjacentRooms[19][1] = 18; adjacentRooms[19][2] = 20;
    adjacentRooms[20][0] = 13; adjacentRooms[20][1] = 16; adjacentRooms[20][2] = 19;
}
//--------------------------------------------------------------------------------
// assign different rooms at random to person, wumpus, pits, bats, and arrows using 
// srand(), makes sure each room is different 
void assignRooms(int *currentRoom, int *wumpusRoom, int *pit1, int *pit2, 
                 int *bat1, int *bat2, int *arrow) {
    // seed random number generator
    srand(1);

    // assigns rooms to person, wumpus, pit1, pit2, bat1, bat2, then arrow
    // while loops below make sure the rooms assigned are unique
    *currentRoom = rand() % 20 + 1;

    *wumpusRoom = rand() % 20 + 1;
    while (*wumpusRoom == *currentRoom) {
        *wumpusRoom = rand() % 20 + 1;
    }
    *pit1 = rand() % 20 + 1;
    while (*pit1 == (*currentRoom || *wumpusRoom) ) {
        *pit1 = rand() % 20 + 1;
    }
    *pit2 = rand() % 20 + 1;
    while (*pit2 == *currentRoom || *pit2 == *wumpusRoom || *pit2 == *pit1) {
        *pit2 = rand() % 20 + 1;
    }
    *bat1 = rand() % 20 + 1;
    while (*bat1 == *currentRoom || *bat1 == *wumpusRoom || *bat1 == *pit1 || *bat1 == *pit2) {
        *bat1 = rand() % 20 + 1;
    }
    *bat2 = rand() % 20 + 1;
    while (*bat2 == *currentRoom || *bat2 == *wumpusRoom || *bat2 == *pit1 || *bat2 == *pit2 || *bat2 == *bat1) {
        *bat2 = rand() % 20 + 1;
    }
    *arrow = rand() % 20 + 1;
    while (*arrow == *currentRoom || *arrow == *wumpusRoom || *arrow == *pit1 || *arrow == *pit2 || *arrow == *bat1 || *arrow == *bat2) {
        *arrow = rand() % 20 + 1;
    }
}
//--------------------------------------------------------------------------------
// takes in game components and prints message that is outputted before every move 
// is made, prints hazzards in adjacent rooms, and prompts player for input
void enterYourMove(int currentRoom, int wumpusRoom, int pit1, int pit2,
                   int bat1, int bat2, char *command, int **adjacentRooms, int moveCount) {
    printf("You are in room %d. ", currentRoom);
    // checks for hazzards in adjacent room
    int i;
    for (i = 0; i < 3; i++) {
        // checks for wumpus
        if (adjacentRooms[currentRoom][i] == wumpusRoom) {  
            printf("You smell a stench. ");
        }
        // checks for pits
        if (adjacentRooms[currentRoom][i] == pit1 || 
            adjacentRooms[currentRoom][i] == pit2) {
            printf("You feel a draft. ");
        }
        // checks for bats
        if (adjacentRooms[currentRoom][i] == bat1 || 
            adjacentRooms[currentRoom][i] == bat2) {
            printf("You hear rustling of bat wings. ");
        }
    }
    printf("\n\n");
    printf("%d. Enter your move (or 'D' for directions): ", moveCount);
    scanf(" %c", *&command); // incremets while loop in main
}
//--------------------------------------------------------------------------------
// takes in adjacentRooms array, a room, and the room player want to compare to. 
// returns true if the two rooms are adjacent and false otherwise
bool isAdjacent(int **adjacentRooms, int currentRoom, int nextRoom) {
    int i; 
    for (i = 0; i < 3; i++) {
        if (adjacentRooms[currentRoom][i] == nextRoom) { 
            return true;
        }
    }
    return false;
}
//--------------------------------------------------------------------------------
// is called when player enters a room with superbats. 
void superBats(int *currentRoom, int *bat1, int *bat2, int *arrow ) {
    
    printf("Woah... you're flying! \n");
    // room player is flown to 
    int newCurrentRoom = rand() % 20 + 1;  
    // makes sure bats move person to new room
    while (newCurrentRoom == *currentRoom) {
        newCurrentRoom = rand() % 20 + 1;
    }
    int oldRoom = *currentRoom; 
    *currentRoom = newCurrentRoom; 
    printf("You've just been transported by bats to room %d.\n", *currentRoom);

    int newBatRoom;   
    // move superbats to new room
    newBatRoom = rand() % 20 + 1; 
    while (newBatRoom == *currentRoom || newBatRoom == *bat1 || newBatRoom == *bat2) {
        newBatRoom = rand() % 20 + 1;
    }
    // assign new value to superbats
    if ( oldRoom == *bat1) { *bat1 = newBatRoom; }
    if ( oldRoom == *bat2) { *bat2 = newBatRoom; }
    
    // if person finds arrow again
    if (*currentRoom == *arrow) { 
        printf("Congratulations, you found the arrow and can once again shoot.\n");
        *arrow = -1; 
    }
    // call function again if superbats move person to another room with more superbats
    if (*currentRoom == *bat1 || *currentRoom == *bat2) {
        superBats(&*currentRoom, &*bat1, &*bat2, &*arrow); 
    }
}
//--------------------------------------------------------------------------------
// is called when player chooses to move rooms, prints different messages depending
// on which room is choosen and where the obstacles such as pits and bats are. 
void commandM(int *currentRoom, int *wumpusRoom, int pit1, int pit2, int *bat1, int *bat2, 
              int *arrow, int **adjacentRooms, int *moveCount, bool *end) {
    int nextRoom; 
    scanf(" %d", &nextRoom); 
    if (!isAdjacent(adjacentRooms, *currentRoom, nextRoom)) {
        printf("Invalid move.  Please retry. \n\n");
        return;   // exits function, enterMove() at end of 
    }             // lets player try again
    *currentRoom = nextRoom;
     // if person moves to wumpus's room that is odd
    if (*currentRoom == *wumpusRoom && *wumpusRoom % 2 == 1) {
        printf("You hear a slithering sound, as the Wumpus slips away. "
               "\nWhew, that was close! \n");
        // wumpus moves to adjacent room with the lowest value
        *wumpusRoom = adjacentRooms[*wumpusRoom][0];   
    } 
    // if person moves to wumpus's room that is even
    if (*currentRoom == *wumpusRoom && *wumpusRoom % 2 == 0) {
        printf("You briefly feel a slimy tentacled arm as your neck is "
               "snapped. \nIt is over.\n");
        *end = true;
        return;  
    }
    // if person moves to a room with a pit
    if (*currentRoom == pit1 || *currentRoom == pit2) {
        printf("Aaaaaaaaahhhhhh....\n    You fall into a pit and die.\n");
        *end = true;  // triggers while loop to break and game to end
        return; 
    }
    // if person moves to a room with a superbat
    if (*currentRoom == *bat1 || *currentRoom == *bat2) {
        superBats(&*currentRoom, &*bat1, &*bat2, &*arrow);
    }
    // if person moves to a room with an arrow
    if (*currentRoom == *arrow) { 
        printf("Congratulations, you found the arrow and can once again shoot.\n");
        *arrow = -1; 
    }
    (*moveCount)++;
}
//--------------------------------------------------------------------------------
// is called when player chooses to shoot an arrow whether they have one or not
// prints message depending on the rooms the player chooses
void commandS(bool *end, int *wumpusRoom, int currentRoom, int *arrow, 
              int **adjacentRooms, int *moveCount ) {
    // if player has not picked up arrow yet
    if (*arrow != -1) { 
        printf("Sorry, you can't shoot an arrow you don't have.  Go find it.\n\n");
        (*moveCount)++;
        return; 
    } 
    // if player has arrow
    else { 
        printf("Enter the number of rooms (1..3) into which you want to shoot, followed by the rooms themselves: ");
        int numberRooms;
        scanf(" %d", &numberRooms);
        int room; // room player wants to shoot at
        int i = 0; 
        *arrow = currentRoom; 
        while(i < numberRooms) {
            scanf(" %d", &room);
            // if room player chooses is not adjacent
            if (!isAdjacent(adjacentRooms, *arrow, room)) {
                printf("Room %d is not adjacent.  Arrow ricochets...\n", room);
                // arrow moves to adjacent room with lowest value
                *arrow = adjacentRooms[*arrow][0];
                // arrow ricochets to player's room
                if (*arrow == currentRoom) {
                    printf( "You just shot yourself, and are dying.\n"
                            "It didn't take long, you're dead.\n");
                    *end = true; break;
                }
                // arrow ricochets to wumpus's room
                if (*arrow == *wumpusRoom) {
                    printf( "Your arrow ricochet killed the Wumpus, you lucky dog!\n"
                            "Accidental victory, but still you win!\n");
                    *end = true; break;
                }
            }
            // if room player chooses is adjacent
            else {
                *arrow = room; 
                // arrow hits player
                if (*arrow == currentRoom) {
                    printf( "You just shot yourself.  \n"
                            "Maybe Darwin was right.  You're dead.\n");
                    *end = true; break;
                }
                // arrow hits wumpus
                if (*arrow == *wumpusRoom) {
                    printf( "Wumpus has just been pierced by your deadly arrow! \n"
                            "Congratulations on your victory, you awesome hunter you.\n");
                    *end = true; break; 
                }
            }
            i++; 
        }
        // wumpus moves to adjacent room with lowest value after arrow is shot
        *wumpusRoom = adjacentRooms[*wumpusRoom][0];
    }
    (*moveCount)++;
}
//--------------------------------------------------------------------------------
int main() {
    int currentRoom, wumpusRoom;
    int pit1, pit2;
    int bat1, bat2; 
    int arrow;
    assignRooms(&currentRoom, &wumpusRoom, &pit1, &pit2, &bat1, &bat2, &arrow); 
    
    // dynamically allocate space for adjacent room 2D array
    int **adjacentRooms = (int**)malloc(21 * sizeof(int*));
    int i; 
    for (i = 0; i < 21; i++) {
        adjacentRooms[i] = (int*)malloc(3 * sizeof(int));
    } 
    // set values for adjacent rooms
    initializeRooms(adjacentRooms); 

    int moveCount = 1; 
    char command;
    bool end = false;  // signal game's end, true when user dies or wumpus is killed
    
    enterYourMove(currentRoom, wumpusRoom, pit1, pit2, bat1, bat2, &command, adjacentRooms, moveCount);
    while (command != 'x' && command != 'X') {
        // if user wants to move to another room
        if (command == 'm' || command == 'M') {
            commandM(&currentRoom, &wumpusRoom, pit1, pit2, &bat1, &bat2, 
            &arrow, adjacentRooms, &moveCount, &end); 
            if (end) { break; }
        }
        // if user wants to use arrow
        if (command == 's' || command == 'S') {
            commandS(&end, &wumpusRoom, currentRoom, &arrow, adjacentRooms, &moveCount); 
            if (end) { break; }
        }
        // when user wants reset rooms and pick the rooms themselves
        if (command == 'r' || command == 'R') {
            printf("Enter the room locations (1..20) for player, wumpus, pit1, pit2, bats1, bats2, and arrow: \n");
            scanf("%d %d %d %d %d %d %d", &currentRoom, &wumpusRoom, &pit1, &pit2, &bat1, &bat2, &arrow);
        }
        // when user wants the room of all game components displayed
        if (command == 'c' || command == 'C') {
            printf( "Cheating! Game elements are in the following rooms: \n"
    		"Player Wumpus Pit1 Pit2 Bats1 Bats2 Arrow  \n"
    		"%4d %5d %6d %5d %5d %5d %5d \n\n", 
			currentRoom, wumpusRoom, pit1, pit2, bat1, bat2, arrow);
        }
        // when user wants to display cave and instructions
        if (command == 'd' || command == 'D') {
            printf("\n");
            displayCave();
            displayInstruction();
        }
        // when user only wants to display cave
        if (command == 'p' || command == 'P') {
            printf("\n");
            displayCave(); 
        }
        // when user wants to guess where the wumpus is
        if (command == 'g' || command == 'G') {
            printf("Enter room (1..20) you think Wumpus is in: ");
            int roomGuess;
            scanf("%d", &roomGuess);
            if (roomGuess == wumpusRoom) { printf("You won!\n"); }
            if (roomGuess != wumpusRoom) {  printf("You lost!\n"); }
            break;
        }
        enterYourMove(currentRoom, wumpusRoom, pit1, pit2, bat1, bat2, &command, adjacentRooms, moveCount);
        continue; 
    }
    printf("\nExiting Program ...\n");
    return 0;
}
