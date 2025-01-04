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