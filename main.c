#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

char buffer[10000]; //= {0};   // Initialize the buffer
int bufferLength = 0;

void Interface(){
    printf("===== Text Editor Menu =====\n");
    printf("1. Enter Text (append or edit)\n");
    printf("2. Search for Word\n");
    printf("3. Replace Word\n");
    printf("4. Delete\n");
    printf("5. Save to File \n");
    printf("6. Load from File \n");
    printf("7. Exit(press ESC)\n");
    printf("============================\n");
}

void printBuffer(){
        for(int i=0; i < bufferLength; i++){
            if((int)buffer[i]==13){
                printf("\n");
                }
            else printf("%c",buffer[i]);
                }
}

void enterText(){
    system("cls");
	printBuffer();
	char input;
	while(1){
		input = getch();
		switch(input){
			case 13:{
				printf("\n");
				buffer[bufferLength]=(char)(13);bufferLength++;
				break;
			}
			case 27:{
				return;
				break;
			}
			case 8:{
				printf("\b");
				//buffer[bufferLength]=NULL;
				bufferLength--;
				system("cls");
				printBuffer();
				break;
			}
			default : {
				printf("%c",input);
				buffer[bufferLength]=input;
				bufferLength++;
				break;
			}
		}
	}

}

void searchText(const char *word, const char *buffer, int bufferLength) {
    system("cls");
    printf("Enter word to search:");
    scanf("%s", (char *)word);  // Cast away const to allow modification

    int wordLen = strlen(word);
    int occurrences = 0;

    for (int i = 0; i < bufferLength; i++) {
        if (buffer[i] == word[0]) {
            int match = 1;

            for (int j = 0; j < wordLen; j++) {
                if (buffer[i + j] != word[j]) {
                    match = 0;
                    break;
                }
            }

            if (match) {
                // Print the word in green
                printf("\033[0;32m");
                for (int k = i; k < i + wordLen; k++) {
                    printf("%c", buffer[k]);
                }
                printf("\033[0m");
                occurrences++;
                i += wordLen - 1;  // Move to the last character of the word
            } else {
                printf("%c", buffer[i]);
            }
        } else {
            if ((int)buffer[i] == 13) {
                printf("\n");
            } else {
                printf("%c", buffer[i]);
            }
        }
    }

    printf("\nTotal occurrences of '%s': %d\n", word, occurrences);
    getch();
}

int sizeS(char a[100]){
	int k=0;
	while(a[k] != '\0'){
		k++;
	}
	return k;
}

void replace(){
	system("cls");
	char a[100]={},b[100]={};
	printf("Text to replace:");
	fgets(a, sizeof a, stdin);
	printf("\n\nReplace with:");
	fgets(b, sizeof b, stdin);
	b[strcspn(b, "\n")] = '\0';
	a[strcspn(a, "\n")] = '\0';
	int n = sizeS(a);
	int m = sizeS(b);
    char bufferC[1000000];
    int nbufferLength = 0;
    for (int i = 0; i < bufferLength; i++) {
        if (buffer[i] == a[0]) {
            bool check = true;
            for (int j = 1; j < n; j++) {
                if (buffer[i + j] != a[j]) {
                    check = false;
                    break;
                }
            }
            if (check) {
                for (int k = 0; k < m; k++) {
                    bufferC[nbufferLength] = b[k];
                    nbufferLength++;
                }
                i+=(n-1);
            } else {
                bufferC[nbufferLength] = buffer[i];
                nbufferLength++;
            }
        } else {
            bufferC[nbufferLength] = buffer[i];
            nbufferLength++;
        }
    }

    for (int i = 0; i < nbufferLength; i++) {
        buffer[i] = bufferC[i];
    }
    bufferLength = nbufferLength;
    system("cls");
    printBuffer();
    printf("\n\n...Press any key to continue");
    getch();

}

void deleteBuffer(char *buffer){
    system("cls");
    int choice;
    printf("\033[0;31m");
    printf("Are you sure you want to delete the buffer?(y/n)\n");
    printf("\033[0m");
    choice = getch();
    switch(choice){
        case 121:
           memset(buffer, '\0', strlen(buffer));  // Clear the entire buffer
           printf("Buffer has been deleted.\n");
           break;
        case 110:{
           printf("Canceling.\n");
           system("pause");
           system("cls");
           return;
           }
        default:{
           system("cls");
           printf("\033[0;31m");//changes the color to red in this case
           printf("Invalid choice. Please try again.\n");
           printf("\033[0m");
           system("pause");
           system("cls");
           break;
        }
    }
    getch();
}

void savetoFile() {
    char filename[100] = {};
    system("cls");
    printf("Save as: ");
    scanf("%s", filename);
    // Append ".txt" to the filename
    strcat(filename, ".txt");
    FILE* file;
    file = fopen(filename, "w");
    if (file != NULL) {
        for (int i = 0; i < bufferLength; i++){
            fprintf(file, "%c", buffer[i]);
        }
        fclose(file);
        printf("\nSaved successfully!\n\n");
    } else {
        printf("\nSomething went wrong while saving!\n\n");
    }
    getch();
}

void readFromFile() {
    system("cls");
    printf("Type name of the file: ");
    char filename[100] = {};
    scanf("%s", filename);
    // Append ".txt" to the filename
    strcat(filename, ".txt");

    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Failed to open the file.\n");
        printf("(Press any key to continue)");
        getch();
        return;
    }
    bufferLength = 0;  // Update the global bufferLength
    int ch = fgetc(file);
    while (ch != EOF) {
        buffer[bufferLength] = ch;
        bufferLength++;
        ch = fgetc(file);
    }
    fclose(file);
    printf("Loaded successfully!\n");
    printf("(Press any key to continue)");
    getch();

}

int main()
{
    int choice;
    char word[100];
    while(1){
        Interface();
        printf("Enter your choice: ");
        choice = getch();
        switch (choice) {
            case 49:{
                enterText();
                system("cls");
                break;}
            case 50:{
                searchText(word, buffer, bufferLength);
                system("cls");
                break;}
            case 51:{
                replace();
                system("cls");
                break;
                }
            case 52:{
                deleteBuffer(buffer);
                system("cls");
                break;}
            case 53:{
                savetoFile();
                system("cls");
                break;}
            case 54:{
                readFromFile();
                system("cls");
                break;}
            case 27:{
                printf("Exiting... Goodbye!\n");
                return 0;}
            default:{
                system("cls");
                printf("\033[0;31m");
                printf("Invalid choice. Please try again.\n");
                printf("\033[0m");
                system("pause");
                system("cls");
                break;}
        }
    }
    return 0;
}
