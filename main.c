#include "Kingdom.h"

Knight *kingdomRoot = NULL;

int main() 
{
    char kingName[50];

    FILE *file = fopen("KINGDOM.txt", "r");
    if (file != NULL) 
    {
        kingdomRoot = loadTree(file);
        fclose(file);
    }

    if (kingdomRoot == NULL) 
    {
        showIntroduction();

    typeText("\nWhat is the name of the king?", 30);
    printf("\nEnter your name: ");
    scanf("%s", kingName);
    getchar();



    kingdomRoot = createNew(kingName, "Knight");
    kingdomRoot->gold = 100;
    kingdomRoot->exp = 1000;  


    printf(GOLD"\n\n+------------------------------------------------------------------------------------------+\n\n"RESET);
    printf("\nAll hail the Sir %s, the ruler of Eldoria!", kingName);
    printf(GOLD"\n\n+------------------------------------------------------------------------------------------+\n\n"RESET);
    sleep(2);

    } 
    
    else 
    {   
        printf(GOLD"\n\n+------------------------------------------------------------------------------------------+\n\n"RESET);
        typeText("Welcome back to the Kingdom of Eldoria, noble ruler!", 30);
        printf(GOLD"\n\n+------------------------------------------------------------------------------------------+\n\n"RESET);
        sleep(2);
    }

    while (1) 
    {
        displayBanner();
        printf("\nWhat actions shall you take, my liege?\n\n");
        printf("1. Recruit a new knight to our cause\n");
        printf("2. Inspect a knight's status\n");
        printf("3. View the entire kingdom's hierarchy\n");
        printf("4. Exile a knight\n");
        printf("5. Convert experience to gold\n");
        printf("6. Save the kingdom's records and retire\n");
        printf("7. Demolish kingdom\n");
        printf("8. Program Guide\n\n");
        
        printf("Your command: ");
        int choice;
        scanf("%d", &choice);
        getchar(); 

        switch(choice) {
            case 1: {
                clearScreen();
                displayBanner();
                char recruitName[50];
                typeText("\nWho shall lead this new recruit?", 30);
                printf("\nEnter leader's name: ");
                scanf("%s", kingName);
                getchar();
                
                typeText("\nAnd who is this brave soul seeking to join our ranks?", 30);
                printf("\nEnter recruit's name: ");
                scanf("%s", recruitName);
                getchar();

                Knight *leader = findMember(kingdomRoot, kingName);
                if (leader != NULL) {
                    recruit(leader, recruitName, "Knight");
                } else {
                    typeText(RED"\nMy liege, I cannot find this leader in our records."RESET, 30);
                    printf(GOLD"\n+------------------------------------------------------------------------------------------+\n\n"RESET);
                    printf("\nPress Enter to continue...");
                    getchar();
                }
                break;
            }
            case 2: {
                clearScreen();
                displayBanner();
                char memberName[50];
                typeText("\nWhose court shall we examine?", 30);
                printf("\nEnter knight's name: ");
                scanf("%s", memberName);
                getchar();

                Knight *member = findMember(kingdomRoot, memberName);
                displaySubordinates(member);
                printf(GOLD"\n+------------------------------------------------------------------------------------------+\n\n"RESET);
                printf("\nPress Enter to continue...");
                getchar();
                break;
            }
            case 3: {
                clearScreen();
                displayBanner();
                typeText("\n\nBehold, the grand hierarchy of our kingdom!", 30);
                printf("\n");

                printf(GOLD"\n\n+------------------------------------------------------------------------------------------+\n\n"RESET);
                printf("Kingdom Treasury: %d gold\n\n", computeTotalGold(kingdomRoot));
                displayKingdom(kingdomRoot, 0);
                printf(GOLD"\n+------------------------------------------------------------------------------------------+\n\n"RESET);
                printf("\nPress Enter to continue...");
                getchar();
                break;
            }
            case 4: 
            {
                clearScreen();
                displayBanner();
                char memberName[50];
                typeText("\nWho shall be exiled from the kingdom?", 30);
                printf("\nEnter knight's name to be exiled: ");
                scanf("%s", memberName);
                getchar();
                printf(GOLD"\n\n+------------------------------------------------------------------------------------------+\n\n"RESET);
                exileKnight(kingdomRoot, memberName);
                printf(GOLD"\n\n+------------------------------------------------------------------------------------------+\n\n"RESET);
                printf("\nPress Enter to continue...");
                getchar();
                sleep(2);
                break;
            }
            case 5: {
                clearScreen();
                displayBanner();
                char knightName[50];
                typeText("\nWho's experience shall we convert to gold?", 30);
                printf("\nEnter knight's name: ");
                scanf("%s", knightName);
                getchar();

                Knight *knight = findMember(kingdomRoot, knightName);
                if (knight != NULL) {
                    printf(GOLD"\n\n+------------------------------------------------------------------------------------------+\n\n"RESET);
                    convertExpToGold(knight);
                    printf(GOLD"\n\n+------------------------------------------------------------------------------------------+\n\n"RESET);
                } else {
                    printf(GOLD"\n\n+------------------------------------------------------------------------------------------+\n\n"RESET);
                    printf(RED"\nMy liege, I cannot find this knight in our records."RESET);
                    printf(GOLD"\n\n+------------------------------------------------------------------------------------------+\n\n"RESET);
                    printf("\nPress Enter to continue...");
                    getchar();
                }
                break;
            }
            case 6: {
                clearScreen();
                displayBanner();
                typeText("\nPreserving the kingdom's legacy for future generations...\n", 30);
                saveKingdom();
                printf(ITALIC_ON"\n\n===\nThe kingdom's records have been preserved for posterity."OFF);
                printf(GOLD"\n\n+------------------------------------------------------------------------------------------+\n\n"RESET);
                printf("\nPress enter to continue or 0 to exit...");
                char choice = getchar();
                if (choice == '0') {
                    printf(GREEN"\nFare thee well, my liege!\n\n"RESET);
                    return 0;
                } else if (choice == '\n') {
                    sleep(2);
                    break;
                }
            }
            case 7: {
                clearScreen();
                displayBanner();
                typeText("\nMy liege, art thou certain thou wouldst destroy the kingdom? This choice cannot be undone. \n(yes/no): ", 30);
                char confirmation[4];
                scanf("%3s", confirmation);
                getchar(); 

                if (strcasecmp(confirmation, "yes") == 0) {
                    clearScreen();
                    printf(GOLD"\n\n+------------------------------------------------------------------------------------------+\n\n"RESET);
                    demolishKingdom();
                    typeText("\n\nFarewell, noble ruler!", 30);
                    printf(GOLD"\n\n+------------------------------------------------------------------------------------------+\n\n"RESET);
                    sleep(2);

                    clearScreen();
                    printf(BOLD_ON"\n");
                    printf(GREEN"\n+------------------------------------------------------------------------------------------+\n");
                    printf("|                                                                                          |\n");
                    printf("|                            May your reign be long remembered.                            |\n");
                    printf("|                                                                                          |\n");
                    printf("+------------------------------------------------------------------------------------------+\n"RESET, OFF);
                    return 0;
                } else {
                    printf(GREEN"\n\n+------------------------------------------------------------------------------------------+\n\n"RESET);
                    typeText("My liege, the kingdom hath been spared from destruction. Thy mercy shall be remembered by \nall who dwell within these walls.", 30);
                    printf(GREEN"\n\n+------------------------------------------------------------------------------------------+\n\n"RESET);
                    printf("\nPress Enter to continue...");
                    getchar();
                }
                break;
            }
            case 8: {
                clearScreen();
                displayHelp();
                printf("\nPress Enter to continue...");
                getchar();
                break;
            }
            default: {
                printf(RED"\nI'm afraid I don't understand your command, my liege."RESET);
                printf("\n\nPress Enter to continue...");
                getchar();
            }
        }
    }

    return 0;
}