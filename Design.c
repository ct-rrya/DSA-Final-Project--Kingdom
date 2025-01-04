# include "Kingdom.h" 

void clearScreen() 
{
    system(CLEAR);
}

void typeText(const char* text, int delay_ms) 
{
    for (int i = 0; text[i] != '\0'; i++) {
        printf("%c", text[i]);
        fflush(stdout);
        
        #ifdef _WIN32
            Sleep(delay_ms);  
        #else
            usleep(delay_ms * 1000); 
        #endif
    }
}

void displayBanner() 
{
    clearScreen();
    printf(BOLD_ON"\n");
    printf(GOLD"\n+------------------------------------------------------------------------------------------+\n");
    printf("|                                                                                          |\n");
    printf("|                                  THE KINGDOM OF ELDORIA                                  |\n");
    printf("|                                                                                          |\n");
    printf("+------------------------------------------------------------------------------------------+\n"RESET, OFF);
}

void showIntroduction() {
    displayBanner();
    printf("\n\n"ITALIC_ON);
    typeText(ITALIC_ON"In the realm of eternal glory, where heroes are forged and kingdoms rise and fall...", 30);
    typeText("\n\n\tYou stand at the threshold of destiny, the architect of a dynasty yet to be written\nin the annals of time. ", 30);
    typeText("Welcome to the Kingdom of Eldoria, where your choices will carve the\npath for a new age of power and glory. ", 30);
    typeText("In this land, the fate of many shall rest upon your\nshoulders. Will you lead with wisdom, or will the tides of fate consume you? ", 30);
    typeText("The journey\nbegins now, as the winds of destiny call upon you. Will you answer? "OFF, 30);
    typeText("\n\nPress [ENTER] to embark upon your epic journey...", 30);
    getchar();
}

void displayKingdom(Knight *target, int level) 
{
    //Uses pre-order traversal: Current → Left → Right.
    if (target == NULL) return;


    // Print the details of the current knight with appropriate indentation.
    // indentation
    for (int i = 0; i < level; i++) {
        printf("   "); 
    }

    // details of current knight
    printf("%s (%d gold, %d exp, %s)\n", target->name, target->gold, target->exp, target->role);

    displayKingdom(target->leftSub, level + 1);
    displayKingdom(target->rightSub, level + 1);

    // para estitik ang pagka display, na siya hierarchical visualization
}

void displaySubordinates(Knight *sub) 
{
    // para ra display the status sa knight
    if (sub == NULL) {
        typeText(RED"\nAlas, this member cannot be found in our records."RESET, 30);
        return;
    }

    clearScreen();
    char message[200];
    printf(GOLD"\n\n+------------------------------------------------------------------------------------------+\n\n"RESET);
    sprintf(message, "== The Court of %s ==", sub->name);
    typeText(message, 30);
    
    printf("\n\nLeader: %s (%s)\n", sub->name, sub->role);
    printf("Personal Treasury: %d gold\n", sub->gold);
    printf("Knight Experience: %d exp", sub->exp);
    printf("\nKingdom Treasury: %d gold\n\n", computeTotalGold(sub));
    
    printf("Direct Subordinates:\n");

    if (sub->leftSub != NULL) 
    {
        printf("Left Knight: %s (%d gold, %d exp)\n", sub->leftSub->name, computeTotalGold(sub->leftSub), sub->leftSub->exp);
    } 
    else {
    printf("Left Knight: Position Vacant\n");
    }

    if (sub->rightSub != NULL) {
        printf("Right Knight: %s (%d gold, %d exp)\n", sub->rightSub->name, computeTotalGold(sub->rightSub), sub->rightSub->exp);
    } else {
        printf("Right Knight: Position Vacant\n");
    }
}

void displayHelp() {
    printf(GREEN"================================ PROGRAM GUIDE ================================\n\n");
    printf(ITALIC_ON"\t\t\tWelcome to the Kingdom System Guide!\n"OFF);
    printf(BOLD_ON"\nFeatures and System Explanation\n\n"OFF);

    printf(GREEN"1. Recruit a new knight to our cause\n");
    printf("   Purpose: Recruit a new knight and assign them to a leader.\n");

    printf("\n2. Inspect knight's status\n");
    printf("   Purpose: View detailed information about a knight and their subordinates.\n   The program will display the knight's role, gold, experience, and their\n   subordinates.\n");

    printf("\n3. View the entire kingdom's hierarchy\n");
    printf("   Purpose: The program will display the kingdom's hierarchy starting from the\n   king and including all subordinates.\n");

    printf("\n4. Exile a knight\n");
    printf("   Purpose: Remove a knight and all their subordinates from the kingdom.\n");

    printf("\n5. Convert experience to gold\n");
    printf("   Purpose: Convert the experience points of a knight into gold.\n");
    printf("   Convertion Rate:\n");
    printf("     500 exp is equivalent to 100 gold\n");

    printf("\n6. Save the kingdom's records and retire\n");
    printf("   Purpose: Save the current state of the kingdom to a file. You can choose to \n   continue or exit the program.\n");

    printf("\n7. Demolish kingdom\n");
    printf("   Purpose: Permanently delete all records of the kingdom and end the game.\n");
    printf("   Confirm if you want to demolish the kingdom. If confirmed, the kingdom will \n   be deleted, and a farewell message will be displayed.\n");

    printf("\n8. Program Guide\n");
    printf("   Purpose: Display this guide for assistance.\n");

    printf("\n====================================================================================\n"RESET);

    printf(GREEN"============================ EXPERIENCE AND GOLD SYSTEM ============================\n\n"RESET);
    printf(ITALIC_ON"\t\t\tExperience System\n"OFF);

    printf(GREEN"1. Every knight in the kingdom has an experience attribute (exp), which measures\n   their progress and achievements.\n");
    printf("2. Knights gain experience through recruitment actions. Specifically, when a knight\n   recruits another knight, they gain 1000 experience points.\n");
    printf("3. Experience is also a factor in determining a knight's role within the kingdom.\n");

    printf(BOLD_ON"\nRoles Based on Experience:\n"OFF);
    printf(GREEN"   Knights can be promoted to higher roles based on their accumulated experience:\n");
    printf("   - Knight: Initial role with starting experience of 1000 EXP.\n");
    printf("   - Veteran Knight: Requires at least 2000 EXP.\n");
    printf("   - Elite Knight: Requires at least 3000 EXP.\n");
    printf("   - King: Requires at least 5000 EXP.\n");
    printf("   The function updateKnightRole is used to update a knight's role based on their\n   current experience.\n"RESET);

    printf(ITALIC_ON"\n\n\t\t\tGold System\n\n"OFF);

    printf(GREEN"1. Gold is the currency used within the kingdom and is crucial for various actions\n   like recruiting new knights.\n");
    printf("2. Each knight has a gold attribute (gold) that represents their wealth.\n");

    printf(BOLD_ON"\nRecruitment Cost:\n"OFF);

    printf(GREEN"   1. Recruiting a new knight requires paying a recruitment fee of 100 gold.\n");
    printf("   2. If a leader successfully recruits a knight, they gain an additional gold bonus:\n");
    printf("      - Recruiting the first knight (left knight) gives an extra 100 gold.\n");
    printf("      - Recruiting the second knight (right knight) gives an extra 200 gold.\n");

    printf(BOLD_ON"\nConverting Experience to Gold:\n"OFF);

    printf(GREEN"1. Knights can convert their experience points into gold.\n");
    printf("2. The conversion rate is 500 EXP = 100 Gold.\n");
    printf("3. Knights must have at least 500 EXP to perform a conversion.\n");
    printf("4. The function convertExpToGold handles this conversion process, allowing knights to trade\n   their experience for gold in multiples of 500 EXP.\n");

    printf(BOLD_ON"\n===== Example Flow ===== \n"OFF);

    printf(GREEN"\nRecruitment:\n");
    printf("   1. A leader with enough gold (at least 100) recruits a new knight.\n");
    printf("   2. The leader pays 100 gold for the recruitment.\n");
    printf("   3. The leader gains 1000 EXP for each new knight they recruit.\n");
    printf("   4. The leader also receives a gold bonus (100 for the first knight, 200 for the second\n      knight).\n");

    printf(GREEN"\nPromotion:\n");
    printf("   1. As knights accumulate experience, their roles can be updated.\n");
    printf("   2. A knight with 2000+ EXP becomes a Veteran Knight.\n");
    printf("   3. A knight with 3000+ EXP becomes an Elite Knight.\n");
    printf("   4. A knight with 5000+ EXP becomes a King.\n");

    printf(GREEN"\nExperience to Gold Conversion:\n");
    printf("   1. Knights with excess experience can convert their experience to gold.\n");
    printf("   2. For every 500 EXP converted, they gain 100 gold.\n");
    printf("   3. This allows knights to increase their gold reserves, which can be used for further\n      recruitment or other actions.\n");

    printf("\n====================================================================================\n"RESET);
    printf(BLUE"================================ PROJECT CONTRIBUTORS ================================\n\n");
    printf("GROUP: 4\nPROGRAM & SECTION: BSIT 2A\n\n");
    printf("\t\t\tCabardo, Carmela\n");
    printf("\t\t\tConde, Jhemarsh Lee\n");
    printf("\t\t\tCongson, Jovannie\n");
    printf("\t\t\tDela Pieza, Frances Mae\n");
    printf("\t\t\tEdano, Merry Apple\n");
    printf("\t\t\tIsmael, Vince Alger\n");
    printf("\n====================================================================================\n"RESET);
}