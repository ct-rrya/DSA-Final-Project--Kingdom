#include "Kingdom.h" 

int computeTotalGold(Knight *current) 
{   
    // if tree is empty or reach na ang end of tree or mpty sha ang tree gyud

    // Left subtree → Right subtree → Current node.
    if (current == NULL) return 0;

    int totalGold = current->gold; // gi initialize ra ang totalGold s akung pilay gold sa pinaka unanag knight nga giread
    totalGold += computeTotalGold(current->leftSub); // tas compute sa left
    totalGold += computeTotalGold(current->rightSub); // tas add ari sa right

    /*
    For example kani:

    Art (200)
        /    \
    A (100)  B (50)

    Una bashaon si Art with 200 
    Dagan sa left naa si A with 100
    Then right B with 50

    so 200 + 100 + 50, do math. Them boom, chada.
    */

    return totalGold;
}

void convertExpToGold(Knight *knight) {
    clearScreen();
    displayBanner();
    
    // to display current status of a knight
    printf("\nCurrent Status of %s:", knight->name);
    printf("\nExperience Points: %d", knight->exp);
    printf("\nGold: %d", knight->gold);
    printf("\nConversion Rate: 500 EXP = 100 Gold\n");

    // tas check dayun exp sa knight if maabot ba sa minimum exp nga pwede i convert which is 500
    if (knight->exp < MIN_CONVERSION_EXP) {
        printf(RED"\nInsufficient experience points for conversion. Minimum required: 500 EXP."RESET);
        printf("\n\nPress Enter to continue...");
        getchar();
        return;
    }

    // if false ang ibabaw, padayon ari
    // tas ngayo na sha s aamount i convert, minimunm of 500 ra gyud bawal 0-499
    printf("\nHow much experience would you like to convert to gold?");
    printf("\nEnter amount (minimum of 500 exp): ");
    char input[20];
    int expToConvert;

    // gamit sha to read the user input as string, rag scanf pero string ang pagbasa s aprogram sa katong number i input
    fgets(input, sizeof(input), stdin);

    // check if katong gi input kay number
    int i = 0;
    while (input[i] != '\0' && input[i] != '\n') { 
        if (input[i] < '0' || input[i] > '9') { // if either condition is true, then dili na siya digit
            printf(RED"\nAmount must be a numeric value!"RESET);
            printf("\n\nPress Enter to continue...");
            getchar();
            return;
        }
        i++;
    }

    // tas if false gani tong ibabaw gi input, numer sha, i convert na balik to integer
    sscanf(input, "%d", &expToConvert);

    // if inig modulo niya kay dili sha zero
    if (expToConvert % MIN_CONVERSION_EXP != 0) {
        printf(RED"\nAmount must be a multiple of 500 EXP."RESET);
        printf("\n\nPress Enter to continue...");
        getchar();
        return;
    }

    // if false ibabaw padayun ari
    // check and exp to convert is greater sa iyang exp, if yes kay tala sad
    if (expToConvert > knight->exp) {
        printf(RED"\nInsufficient experience points for this conversion."RESET);
        printf("\n\nPress Enter to continue...");
        getchar();
        return;
    }

    // conversion na
    int goldGained = (expToConvert / MIN_CONVERSION_EXP) * 100;

    // tas ofc bawasan iya exp
    knight->exp -= expToConvert;

    // plusan iya gold heheh
    knight->gold += goldGained;

    // then display dayun updaed status
    printf(GREEN"\nConversion successful!");
    printf("\nConverted %d EXP to %d Gold", expToConvert, goldGained);
    printf("\n\nNew Status:");
    printf("\nExperience Points: %d", knight->exp);
    printf("\nGold: %d"RESET, knight->gold);

    updateKnightRole(knight);
    saveKingdom();

    printf(GOLD"\n+------------------------------------------------------------------------------------------+\n\n"RESET);
    printf("\nPress Enter to continue...");
    getchar();
}