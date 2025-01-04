#include "Kingdom.h" 

int computeTotalGold(Knight *sub) 
{   
    // if tree is empty or reach na ang end of tree
    // It performs a post-order traversal
    // Left subtree → Right subtree → Current node.
    if (sub == NULL) return 0;
    int totalGold = sub->gold;
    totalGold += computeTotalGold(sub->leftSub);
    totalGold += computeTotalGold(sub->rightSub);
    return totalGold;
}

void convertExpToGold(Knight *knight) {
    clearScreen();
    displayBanner();
    
    printf("\nCurrent Status of %s:", knight->name);
    printf("\nExperience Points: %d", knight->exp);
    printf("\nGold: %d", knight->gold);
    printf("\nConversion Rate: 500 EXP = 100 Gold\n");

    if (knight->exp < MIN_CONVERSION_EXP) {
        printf(RED"\nInsufficient experience points for conversion. Minimum required: 500 EXP."RESET);
        printf("\n\nPress Enter to continue...");
        getchar();
        return;
    }

    printf("\nHow much experience would you like to convert to gold?");
    printf("\nEnter amount (minimum of 500 exp): ");
    char input[20];
    int expToConvert;

     fgets(input, sizeof(input), stdin);

    // Check if the input contains only digits (use ASCII values)
    int i = 0;
    while (input[i] != '\0' && input[i] != '\n') {
        if (input[i] < '0' || input[i] > '9') {
            printf(RED"\nAmount must be a numeric value!"RESET);
            printf("\n\nPress Enter to continue...");
            getchar();
            return;
        }
        i++;
    }

    // Convert the valid input to an integer
    sscanf(input, "%d", &expToConvert);

    if (expToConvert % MIN_CONVERSION_EXP != 0) {
        printf(RED"\nAmount must be a multiple of 500 EXP."RESET);
        printf("\n\nPress Enter to continue...");
        getchar();
        return;
    }

    if (expToConvert > knight->exp) {
        printf(RED"\nInsufficient experience points for this conversion."RESET);
        printf("\n\nPress Enter to continue...");
        getchar();
        return;
    }

    int goldGained = (expToConvert / 500) * 100;

    knight->exp -= expToConvert;
    knight->gold += goldGained;

    printf(GREEN"\nConversion successful!");
    printf("\nConverted %d EXP to %d Gold", expToConvert, goldGained);
    printf("\n\nNew Status:");
    printf("\nExperience Points: %d", knight->exp);
    printf("\nGold: %d"RESET, knight->gold);

    updateKnightRole(knight);

    printf(GOLD"\n+------------------------------------------------------------------------------------------+\n\n"RESET);
    printf("\nPress Enter to continue...");
    getchar();
}