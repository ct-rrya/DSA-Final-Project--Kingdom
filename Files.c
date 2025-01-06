# include "Kingdom.h"

void saveTree(FILE *file, Knight *current, int level) {
    // performs a pre-order traversal (root, left, right) to save the tree structure.

    // if ang current kay wala na like, NULL na sha, stop na pls
    if (current == NULL) {
        return;
    }

    // int level, for indentation purposes lang, to know asa na nga depth sa tree
    // root has ofc, 0 indentation, followed by second leve with 3 space-indentation, level 3 with 6 space-indentation and so on 
    // printing indentation
    for (int i = 0; i < level; i++) {
        fprintf(file, "   "); 
    }
    
    // writing to the file with the format name gold exp role
    // each attribute is written to the file separated by spaces and \n to move to the next line
    fprintf(file, "%s %d %d %s\n", 
            current->name,
            current->gold,
            current->exp,
            current->role);
    
    // recurse for the left and right subtree
    // level + 1 para inig balik-balik niya kay consistent ang formatting, mo add sha space according to level(depth)
    saveTree(file, current->leftSub, level + 1);
    saveTree(file, current->rightSub, level + 1);
}

Knight *loadTree(FILE *file) {
    char line[150];
    Knight *root = NULL;
    Knight *current = NULL;
    int currentLevel = -1;
    Knight *parents[100];
    int parentLevels[100];
    int parentIndex = -1;

    fseek(file, 0, SEEK_SET);

    while (fgets(line, sizeof(line), file)) {
        char name[50], role[50];
        int gold, level = 0, exp = 0;

        line[strcspn(line, "\r\n")] = 0; // removes any ewline characters, that wer epossibly accidentally typed
        
        while (line[level * 3] == ' ') { // this counts the spaces para kahibalo ang program unsa na sha nga level
            level++;
        }
        
        // extracts the attributes from each line
        if (sscanf(line + (level * 3), "%49s %d %d %49[^\n]", name, &gold, &exp, role) != 4) {
            printf("Debug: Failed to parse line: %s\n", line);
            continue;
        }

        // need ta ani coz, we dun knoe pila ka knights we have ahead, so we have to have a storage to hold the data
        // kay we reconstruct it fresh from the text file hhh
        Knight *newKnight = createNew(name, role);
        if (!newKnight) continue;
        
        newKnight->gold = gold;
        newKnight->exp = exp;

        // decision sha if i-place ba ang knight either as a root, lef tor right base sa indentation
        if (level == 0) { // the higher the level, naa sha sa ilawm 
        // but if 0 siya, ofc siya maoy root
            root = newKnight; // so ang newKnight mahimong siyang root
            parentIndex = 0; // kay ofc first knight sha
            parents[parentIndex] = root; // so root sha meaning parent
            parentLevels[parentIndex] = level; // so sa level sa mga parent siya maoy naas taas
            
        } else { // pero ofc, if wala siya s alevel 0
            while (parentIndex >= 0 && parentLevels[parentIndex] >= level) { // this line checks asa siya dapit nga level
            // thru comparing the indexes, if weve gone too deep na
                parentIndex--;
                // if true, then we have to move up up
                // continue na siya until makit-an ang parent
            }
            
            // this is the main part where ma rebuild gyud niya ang tree
            if (parentIndex >= 0) {
                Knight *parent = parents[parentIndex]; // kuaon ang parent na na assign during the previos code
                if (parent->leftSub == NULL) { // i check ang ;eft side if wala sulod, then adto isulod ang neKnight
                    parent->leftSub = newKnight;
                } else if (parent->rightSub == NULL) { // but if right ang walay sulod, ofc adto siya
                    parent->rightSub = newKnight;
                }

                // increment para modagan siya s alain knight na naa sa tree
                parentIndex++;
                parents[parentIndex] = newKnight; // tas ang newKnight ma-add siya s alinya s amga parnets na
                parentLevels[parentIndex] = level;
            }
        }
    }

    return root; // importante, kay root is where all start man
}