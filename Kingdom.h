#ifndef KINGDOM_H
#define KINGDOM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> 
#include <ctype.h> // For isalpha()
#ifdef _WIN32
#include <windows.h>
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

#define RECRUITMENT_COST 100
#define VETERAN_EXP_THRESHOLD 2000    // Experience needed to become a Veteran Knight
#define ELITE_EXP_THRESHOLD 3000     // Experience needed to become an Elite Knight
#define KING_EXP_THRESHOLD 5000     // Experience needed to become a King
#define MIN_CONVERSION_EXP 500  // Minimum exp that can be converted

#define RESET "\x1b[0m"
#define GOLD "\x1b[33m"
#define BLUE "\x1b[34m"
#define GREEN "\x1b[32m"
#define RED "\x1b[31m"
#define ITALIC_ON "\033[3m"
#define OFF "\033[0m"
#define BOLD_ON "\033[1m"

typedef struct Knight {
    char name[50];
    char role[50];
    int gold;
    int exp;
    struct Knight *leftSub;
    struct Knight *rightSub;
} Knight;

// MAIN FUNCTIONS encoded on Main_Features.c
    void saveKingdom();
    void demolishKingdom();
    void recruit(Knight *leader, char *recName, char *recRole);
    void exileKnight(Knight *root, char *name);
    void displayKingdom(Knight *target, int level);
    void displaySubordinates(Knight *sub);
    void displayHelp();

// HELPER FUNCTIONS encoded on Helper_Functions
    Knight *createNew(char *name, char *role);
    Knight *findMember(Knight *current, char *name);
    Knight *findParent(Knight *current, Knight *child);
    void freeKnight(Knight *knight);
    void updateKnightRole(Knight *knight);

// FILE HANDLING RELATED FUNCTIONS encoded on Files.c
    void saveTree(FILE *file, Knight *sub, int level);
    Knight *loadTree(FILE *file);

// GOLD AND EXPERIENCE UPDATE FUNCTIONS encoded on GoldExp.c
    int computeTotalGold(Knight *sub);
    void convertExpToGold(Knight *knight);
    
// INTERFACE DESIGN FUNCTIONS encoded on Design.c
    void showIntroduction();
    void typeText(const char *text, int delay);
    void displayBanner();
    void clearScreen();

// the global variable, to be initialized on main.c
extern Knight *kingdomRoot;

#endif