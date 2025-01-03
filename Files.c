# include "Kingdom.h"

void saveTree(FILE *file, Knight *sub, int level) {
    // performs a pre-order traversal (root, left, right) to save the tree structure.
    if (sub == NULL) {
        return;
    }

    // printing indentation
    for (int i = 0; i < level; i++) {
        fprintf(file, "   "); 
    }
    
    // writing to the file with the formal name gold exp role
    fprintf(file, "%s %d %d %s\n", 
            sub->name,
            sub->gold,
            sub->exp,
            sub->role);
    
    // recurse for the left and right subtree
    saveTree(file, sub->leftSub, level + 1);
    saveTree(file, sub->rightSub, level + 1);
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
    unsigned char bom[3];
    if (fread(bom, 1, 3, file) == 3) {
        if (!(bom[0] == 0xEF && bom[1] == 0xBB && bom[2] == 0xBF)) {
            fseek(file, 0, SEEK_SET);
        }
    } else {
        fseek(file, 0, SEEK_SET);
    }

    while (fgets(line, sizeof(line), file)) {
        char name[50], role[50];
        int gold, level = 0, exp = 0;

        line[strcspn(line, "\r\n")] = 0;
        
        while (line[level * 3] == ' ') {
            level++;
        }
        
        if (sscanf(line + (level * 3), "%49s %d %d %49[^\n]", name, &gold, &exp, role) != 4) {
            printf("Debug: Failed to parse line: %s\n", line);
            continue;
        }

        Knight *newKnight = createNew(name, role);
        if (!newKnight) continue;
        
        newKnight->gold = gold;
        newKnight->exp = exp;

        if (level == 0) {
            root = newKnight;
            parentIndex = 0;
            parents[parentIndex] = root;
            parentLevels[parentIndex] = level;
        } else {
            while (parentIndex >= 0 && parentLevels[parentIndex] >= level) {
                parentIndex--;
            }
            
            if (parentIndex >= 0) {
                Knight *parent = parents[parentIndex];
                if (parent->leftSub == NULL) {
                    parent->leftSub = newKnight;
                } else if (parent->rightSub == NULL) {
                    parent->rightSub = newKnight;
                }
                parentIndex++;
                parents[parentIndex] = newKnight;
                parentLevels[parentIndex] = level;
            }
        }
    }

    return root;
}