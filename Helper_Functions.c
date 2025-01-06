# include "Kingdom.h"

Knight *createNew(char *name, char *role) 
{
    // himo ug new knight
    Knight *newSub = (Knight *)malloc(sizeof(Knight)); // allocate memory
    if (newSub == NULL) { // check if na allocate ba sha
        typeText(RED"\nThe kingdom's resources are stretched thin. Unable to accommodate new recruits."RESET, 30);
        return NULL;
    }

    // tas initialize na
    strcpy(newSub->name, name);
    strcpy(newSub->role, role);
    newSub->gold = 0;
    newSub->exp = 1000; // every knight, after sila ma recruit, naa na sla daan 1000 exp, kay need man nila gold to be able to recruit their own knight
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

void freeKnight(Knight *knight) { // tp free alocated memory, to avoid memory leaks
    if (knight == NULL) return;
    freeKnight(knight->leftSub);
    freeKnight(knight->rightSub);
    free(knight);
}

void updateKnightRole(Knight *knight) { // to promote  aknight aheheh
    /*
    if (knight->exp >= KING_EXP_THRESHOLD) {
        strcpy(knight->role, "King");
    } else if (knight->exp >= ELITE_EXP_THRESHOLD) {
        strcpy(knight->role, "Elite Knight");
    } else if (knight->exp >= VETERAN_EXP_THRESHOLD) {
        strcpy(knight->role, "Veteran Knight");
    }
    */

    if (strcmp(knight->role, "King") == 0) {
        return;  // Don't promote the king
    }

    if (knight->exp >= ELITE_EXP_THRESHOLD) {
        strcpy(knight->role, "Elite Knight");
    } else if (knight->exp >= VETERAN_EXP_THRESHOLD) {
        strcpy(knight->role, "Veteran Knight");
    }
}