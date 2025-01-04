#include "Kingdom.h"

Knight *createNew(char *name, char *role) 
{
    Knight *newSub = (Knight *)malloc(sizeof(Knight));
    if (newSub == NULL) {
        typeText(RED"\nThe kingdom's resources are stretched thin. Unable to accommodate new recruits."RESET, 30);
        return NULL;
    }

    strcpy(newSub->name, name);
    strcpy(newSub->role, role);
    newSub->gold = 0;
    newSub->exp = 1000;
    newSub->leftSub = NULL;
    newSub->rightSub = NULL;

    return newSub;
}

Knight *findMember(Knight *current, char *name) 
// current : a pointer to the current node, since we prefer preOrder na traversal
// sa root gyud siya magsugod

// name : a pointer to the knight we are searching for
{   
    // if the current is empty it returns null para ma indicate that the name is not found
    if (current == NULL) return NULL;
    
    // strcasecmp : is library function where we compare two string, case-insensitive, 
    // so di mag matter kung lowercase or upper case ang gitype

    // so in this part, we compare current node's name sa target name nato
    // if same sila, then i return niya ang current node
    if (strcasecmp(current->name, name) == 0) return current;

    // so kani nga part kay recursion siya for the left subtree na
    // if found na ang target name, ma store na siya sa FOUND pointer
    Knight *found = findMember(current->leftSub, name);
    if (found != NULL) return found;

    // so if di siya makit-an sa left naa siya sa right, so we recurse to right subtree
    return findMember(current->rightSub, name);
}

Knight *findParent(Knight *current, Knight *child) {
    // current : ofc pointer sa current node hahaha
    // child : pointer sa node nga pangitaon ang iya parent

    // if current kay null, meaning walay sulod ang tree or naabot nas last
    // if child is null so basin invalid input
    // if ang current kay ang root tapos same siya sa child then di siya pwede
    // kay parent naman siya daan
    if (current == NULL || child == NULL || current == child) {
        return NULL;
    }

    //  this checks if the current node (root) is the parent of the child.
    // if the left child of the current node is the child, then current is tha parent
    // same logic goes with the right child of the current node
    if (current->leftSub == child || current->rightSub == child) {
        // if either condition is true, this returns the current node (root)
        return current;
    }

    // if ang current node is not the parent, then proceed to recurse left and right subtree
    Knight *leftParent = findParent(current->leftSub, child);
    if (leftParent != NULL) {
        return leftParent;
    }
    return findParent(current->rightSub, child);
}

void saveKingdom() {
    FILE *file = fopen("KINGDOM.txt", "w");
    if (file == NULL) {
        printf(RED"\n\n===\nFailed to record the kingdom's history in the scrolls."RESET);
        return;
    }
    saveTree(file, kingdomRoot, 0); 
    fclose(file);
    sleep(1);
}

void updateKnightRole(Knight *knight) {
    if (knight->exp >= KING_EXP_THRESHOLD) {
        strcpy(knight->role, "King");
    } else if (knight->exp >= ELITE_EXP_THRESHOLD) {
        strcpy(knight->role, "Elite Knight");
    } else if (knight->exp >= VETERAN_EXP_THRESHOLD) {
        strcpy(knight->role, "Veteran Knight");
    }
}

void recruit(Knight *leader, char *recName, char *recRole) 
{
    clearScreen();

    for (int i = 0; recName[i] != '\0'; i++) {
        if (!isalpha(recName[i])) {
            printf(RED"\n\n===\nMy liege, the name must contain only alphabetic characters!"RESET);
            printf("\nPress Enter to continue...");
            getchar();
            return;
        }
    }

    if (leader->gold < RECRUITMENT_COST) {
        printf(RED"\n\n===\nMy liege, I am afraid your treasury is not enough to earn a brave soul."RESET);
        sleep(2);
        return;
    }

    if (leader == NULL) {
        printf(RED"\n\n===\nMy liege, I regret to inform you that this leader cannot be found in our ranks."RESET);
        return;
    }

    if (findMember(kingdomRoot, recName) != NULL) {
        printf(RED"\n\n===\nA member with this name already exists in the kingdom."RESET);
        sleep(2);
        return;
    }

    char story[500];
    printf(ITALIC_ON"\nIn the grand halls of %s's command post..."OFF, leader->name);
    typeText(story, 30);

    Knight *newKnight = createNew(recName, recRole);
    if (newKnight == NULL) return; 

    if (leader->leftSub == NULL) 
    {
        printf(GOLD"\n\n+------------------------------------------------------------------------------------------+\n"RESET);
        printf(ITALIC_ON "\n\tA steadfast warrior steps forth, their armor gleaming faintly under the torchlight.\n");
        printf("The hall falls silent as the warrior kneels, ledging their blade and loyalty to the realm.");
        leader->leftSub = newKnight; // as left knight
        leader->gold -= RECRUITMENT_COST;
        leader->gold += 100;
        updateKnightRole(leader);
        sprintf(story, BOLD_ON BLUE "\n\n\tWith a solemn nod, %s proclaims, 'By royal decree, I name thee, %s, my sworn \nleft knight. Rise and serve with honor!'\n" OFF RESET, leader->name, recName);
        saveKingdom();
    } 
    else if (leader->rightSub == NULL) 
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
    else 
    {
    printf(RED "\n\tAlas! The ranks beneath this noble leader are already brimming with steadfast \nand loyal knights, each sworn to their sacred duty." RESET);
    free(newKnight);
        
        return;
    }
    
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

void freeKnight(Knight *knight) {
    if (knight == NULL) return;
    freeKnight(knight->leftSub);
    freeKnight(knight->rightSub);
    free(knight);
}

void exileKnight(Knight *root, char *name) 
{
    if (root == NULL || strcmp(root->name, name) == 0) {
        printf(RED"Cannot exile the king or the root of the kingdom.\n"RESET);
        return;
    }

    Knight *knightToExile = findMember(root, name);
    if (knightToExile == NULL) {
        printf(RED"No knight with the name %s found in the kingdom.\n"RESET, name);
        return;
    }

    printf("Warning: Exiling knight %s will also remove all its subordinates.\n", name);
    printf("Do you want to proceed? (yes/no): ");
    char confirmation[4];
    scanf("%3s", confirmation);
    if (strcasecmp(confirmation, "yes") != 0) {
        printf("\nExile operation cancelled.\n");
        return;
    }

    Knight *parent = findParent(root, knightToExile);
    if (parent != NULL) {
        if (parent->leftSub == knightToExile) {
            parent->leftSub = NULL;
        } else if (parent->rightSub == knightToExile) {
            parent->rightSub = NULL;
        }
    }

    freeKnight(knightToExile);
    printf(ITALIC_ON"\nKnight %s and all its subordinates have been exiled."OFF, name);

    saveKingdom();
}

void demolishKingdom() {
    FILE *file = fopen("KINGDOM.txt", "w");
    if (file == NULL) {
        printf(RED"\n\n===\nFailed to erase the kingdom's history from the scrolls."RESET);
        return;
    }
    fclose(file);

    freeKnight(kingdomRoot);
    kingdomRoot = NULL;

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