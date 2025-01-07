#include "Kingdom.h"

void saveKingdom() { // saving the current state of the kingdom padung sa text file
    FILE *file = fopen("KINGDOM.txt", "w"); // open ang file thru write mode (w)
    if (file == NULL) { // kung mag file awww
        printf(RED"\n\n===\nFailed to record the kingdom's history in the scrolls."RESET);
        return;
    }
    // 0 kay starting level ofc, start gyud tas root
    saveTree(file, kingdomRoot, 0); 
    fclose(file); // tas close balik file
    sleep(2);
}

void recruit(Knight *leader, char *recName, char *recRole) 
{
    clearScreen();

    // input validation, basin number or other character ang gityoe nga recName
    for (int i = 0; recName[i] != '\0'; i++) {
        if (!isalpha(recName[i])) {
            printf(RED"\n\n===\nMy liege, the name must contain only alphabetic characters!"RESET);
            printf("\nPress Enter to continue...");
            getchar();
            return;
        }
    }

     // check if naa ba na nga leader sa file
    if (leader == NULL) {
        printf(RED"\n\n===\nMy liege, I regret to inform you that this leader cannot be found in our ranks."RESET);
        return;
    }

    // check if ang gold sa leader kay enought o recruit hahahaha
    if (leader->gold < RECRUITMENT_COST) {
        printf(RED"\n\n===\nMy liege, I am afraid your treasury is not enough to earn a brave soul."RESET);
        sleep(2);
        return;
    }

    // check if naa na bay in ana nga name, di sha llowed okay
    if (findMember(kingdomRoot, recName) != NULL) {
        printf(RED"\n\n===\nA member with this name already exists in the kingdom."RESET);
        sleep(2);
        return;
    }

    char story[500];
    printf(ITALIC_ON"\nIn the grand halls of %s's command post..."OFF, leader->name);
    typeText(story, 30);

    // tas if oks na, create na tag newKnight
    Knight *newKnight = createNew(recName, recRole);
    if (newKnight == NULL) return; 

    // check ang left side sa leader if na aba tawo
    if (leader->leftSub == NULL) 
    {
        printf(GOLD"\n\n+------------------------------------------------------------------------------------------+\n"RESET);
        printf(ITALIC_ON "\n\tA steadfast warrior steps forth, their armor gleaming faintly under the torchlight.\n");
        printf("The hall falls silent as the warrior kneels, ledging their blade and loyalty to the realm.");
        leader->leftSub = newKnight; // assign as left knight
        leader->gold -= RECRUITMENT_COST; // minusan ang gold saleader
        leader->gold += 100; // tas addan nasad 100 ang leader HAHAHAHHAH, di magbuot sa developer
        updateKnightRole(leader); // tas update ang role niya
        sprintf(story, BOLD_ON BLUE "\n\n\tWith a solemn nod, %s proclaims, 'By royal decree, I name thee, %s, my sworn \nleft knight. Rise and serve with honor!'\n" OFF RESET, leader->name, recName);
        saveKingdom();
    } 
    else if (leader->rightSub == NULL)  // if ang right naay vacant position, cmpri ari ibutang ang new knight
    {
        printf(GOLD"\n\n+---------------------------------------------------------------------------------------+\n"RESET);
        printf(ITALIC_ON "\n\tFrom the shadows of the hall, a determined warrior steps forward, their cloak \nbillowing with the draft of ancient stone walls. ");
        printf("The gathered courtiers hold their breath\nas the warrior kneels, swearing their unwavering allegiance to the crown.");
        leader->rightSub = newKnight; // a right knight
        leader->gold -= RECRUITMENT_COST;
        leader->gold += 200; // bonus 100 for recruiting 2 knights
        updateKnightRole(leader);
        sprintf(story, BOLD_ON BLUE "\n\n\tRaising a hand in declaration, %s proclaims, 'By royal decree, I name thee, %s, \nmy sworn right knight. Bear the crest of this kingdom with pride and valor!'\n" OFF RESET, leader->name, recName);
        saveKingdom();
    } 
    else // kung parehong occupied... awts
    {
    printf(RED "\n\tAlas! The ranks beneath this noble leader are already brimming with steadfast \nand loyal knights, each sworn to their sacred duty." RESET);
    free(newKnight);
        
        return;
    }
    
    // para i update ang exp ug role
    Knight *current = leader;
    while (current != NULL) {
        current->exp += 1000;
        //current->gold += 100;
        updateKnightRole(current);
        current = findParent(kingdomRoot, current);
        saveKingdom();
    }
    
    typeText(story, 30);
    printf("\n\tThe kingdom grows ever mightier, its strength forged anew with the addition of such\nvaliant souls. ");
    printf("Each knight who joins our cause brings honor to the realm and fortifies \nthe banners of our sovereignty.\n\n");
    printf(GOLD"+---------------------------------------------------------------------------------------+\n"RESET);

    printf("\nPress Enter to continue...");
    getchar();
}

void exileKnight(Knight *root, char *name) 
{   
    // check if ang gi enter nga name kay maoy root / king, u cannot exile a king ok
    if (root == NULL || strcmp(root->name, name) == 0) {
        printf(RED"Cannot exile the king or the root of the kingdom.\n"RESET);
        return;
    }

    // pangitaon nag name nga gitype, if walla hayna
    Knight *knightToExile = findMember(root, name);
    if (knightToExile == NULL) {
        printf(RED"No knight with the name %s found in the kingdom.\n"RESET, name);
        return;
    }


    // if makita na, naay warning
    // kay if u exile that knight, mawala sad to iyang mga subordinates
    printf("Warning: Exiling knight %s will also remove all its subordinates.\n", name);
    printf("Do you want to proceed? (yes/no): ");
    char confirmation[4];
    scanf("%3s", confirmation);
    if (strcasecmp(confirmation, "yes") != 0) {
        printf("\nExile operation cancelled.\n");
        return;
    }

    // pangitaon dayun parent ato nga knight
    // if makita sa left, i NULL ang leftSub sa parent
    // otherwise, ang right sub
    Knight *parent = findParent(root, knightToExile);
    if (parent != NULL) {
        if (parent->leftSub == knightToExile) {
            parent->leftSub = NULL;
        } else if (parent->rightSub == knightToExile) {
            parent->rightSub = NULL;
        }
    }

    // tas free
    freeKnight(knightToExile);
    printf(ITALIC_ON"\nKnight %s and all its subordinates have been exiled. \nTaking with them their %d gold pieces."OFF, name, computeTotalGold(knightToExile));

    saveKingdom();
}

void demolishKingdom() {
    FILE *file = fopen("KINGDOM.txt", "w"); // open file in write mode
    if (file == NULL) {
        printf(RED"\n\n===\nFailed to erase the kingdom's history from the scrolls."RESET);
        return;
    }
    fclose(file);

    freeKnight(kingdomRoot); // tas i free and root
    kingdomRoot = NULL; // tas i NULL, mana

    displayBanner();
    printf("\n\n"ITALIC_ON);
    typeText(ITALIC_ON "As the sun sets on the horizon, the once-great kingdom of Eldoria crumbles into the annals\nof history...", 30);
    typeText("\n\n\tThe echoes of battles fought and victories won fade into silence, leaving behind\nonly remnants of a bygone era. ", 30);
    typeText("The grand halls stand empty, and the banners that once flew\nproudly now lie in tatters. ", 30);
    typeText("The realm that was forged with courage and honor has met its\nend, its glory diminished to mere whispers of the past. ", 30);
    typeText("Yet, in its downfall, the kingdom's\nstories will be told, legends of heroes and kings, of valor and sacrifice. ", 30);
    typeText("Eldoria's spirit\nwill live on in the memories of those who once called it home, a testament to the rise and\nfall of empires. ", 30);
    typeText("\n\nPress [ENTER] to acknowledge the end of an era...", 30);
    getchar();
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

void displayKingdom(Knight *target, int level) 
{
    // Uses pre-order traversal: Current → Left → Right.
    if (target == NULL) return;

    // Print the details of the current knight with appropriate indentation.
    // indentation
    for (int i = 0; i < level; i++) {
        printf("   ");
    }

    // Check if the current knight is the king (root) and label as "King"
    if (target == kingdomRoot) {
        printf("King %s (%d gold, %d exp, %s)\n", target->name, target->gold, target->exp, target->role);
    } else {
        // Otherwise, print it as a regular knight
        printf("%s (%d gold, %d exp, %s)\n", target->name, target->gold, target->exp, target->role);
    }

    // Recursively display left and right subordinates
    displayKingdom(target->leftSub, level + 1);
    displayKingdom(target->rightSub, level + 1);

    // para estitik ang pagka display, na siya hierarchical visualization
}