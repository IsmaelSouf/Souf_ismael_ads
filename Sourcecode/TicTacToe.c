#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX 10

char board[MAX] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
char choices[MAX] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
char symbols[MAX] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

struct TicTacToe
{
    int gameID;
    char choices[MAX];
    char symbols[MAX];
    struct TicTacToe *next;
};

//Data Structure for stack
struct stack
{
    int top;
    //define max capacity of stack
    unsigned maxsize;
    char *moves;
};

//Utility function to initialize stack
struct stack *init_stack(unsigned capacity)
{
    struct stack *s = (struct stack*)malloc(sizeof(struct stack));
    s->maxsize = capacity;
    s->top = -1;
    s->moves = (char*)malloc(sizeof(char) * s->maxsize);
    return s;
}

//Function prototype
int stackFull();
int stackEmpty();
char pop();
void resetBoard();
void Game();
void read();
void createBoard();
void recordGame();
void write();
void replay();
void resetMoves();
void undoMove();
void redoMove();
int  gameWin();

//Utility function to check if the stack if full
int stackFull(struct stack *s)
{
    return s->top == s->maxsize -1;
}

//Utility function to check if the stack is empty
int stackEmpty(struct stack *s)
{
    return s->top == -1;
}

//Utility function to add an item in the stack
void push(struct stack *s, char item)
{
    //If stack full adding an element would lead to a stack overflow
    if(stackFull(s))
    {
        printf("Stack is full . Couldn ’t push %c onto stack\n",item);
        return;
    }
    //Add element and incremment top index
    s->moves[++s->top] = item;
}

//Utility function to pop top element from the stack
char pop(struct stack *s)
{
    //If stack is empty it would lead to an underflow
    if(stackEmpty(s))
    {
        printf("Stack is empty\n");
        return s->top;
    }
    //Decrement stack size by 1
    return s->moves[s->top--];
}

//Function to reset the board to its initial state
void resetBoard()
{
    board[1] = '1';
    board[2] = '2';
    board[3] = '3';
    board[4] = '4';
    board[5] = '5';
    board[6] = '6';
    board[7] = '7';
    board[8] = '8';
    board[9] = '9';
}

//Function to create a TicTacToe game
void Game(struct TicTacToe **gameOne, int gameID, char choices[10], char symbols[10])
{
    struct TicTacToe *new_game = (struct TicTacToe*)malloc(sizeof(struct TicTacToe));
    struct TicTacToe *last_game = *gameOne;
    new_game->gameID = gameID;
    strcpy(new_game->choices,choices);
    strcpy(new_game->symbols, symbols);
    new_game->next = NULL;
    if(*gameOne == NULL)
    {
        *gameOne = new_game;
        return;
    }
    while(last_game->next != NULL)
    {
        last_game = last_game->next;
    }
    last_game->next = new_game;
    return;
}

//Read every move of the game into the file
void read(struct TicTacToe **gameOne)
{
    FILE *outfile = fopen("save.txt","r");
    char symbols[MAX];
    char choices[MAX];
    int count = 0;
    
    while(fscanf(outfile, "%s %s", choices, symbols) != EOF)
    {
        Game(gameOne, count, choices, symbols);
        count++;
    }
    
    fclose(outfile);
}

//Function to find record game
void recordGame(struct TicTacToe ** gameOne, int gameID){
    
    int found = 0;
    struct TicTacToe *current_game = *gameOne;
    while(current_game != NULL){
        if(current_game->gameID == gameID){
            found = 1;
            for(int i = 0; i < 9; i ++){
                
                if(current_game->choices[i] == '1' && (current_game->symbols[i] == 'O' || current_game->symbols[i] == 'X')){
                    board[1] = current_game->symbols[i];
                    createBoard();
                }
                else if(current_game->choices[i] == '2' && (current_game->symbols[i] == 'O' || current_game->symbols[i] == 'X')){
                    board[2] = current_game->symbols[i];
                    createBoard();
                }
                else if(current_game->choices[i] == '3' && (current_game->symbols[i] == 'O' || current_game->symbols[i] == 'X')){
                    board[3] = current_game->symbols[i];
                    createBoard();
                }
                else if(current_game->choices[i] == '4' && (current_game->symbols[i] == 'O' || current_game->symbols[i] == 'X')){
                    board[4] = current_game->symbols[i];
                    createBoard();
                }
                else if(current_game->choices[i] == '5' && (current_game->symbols[i] == 'O' || current_game->symbols[i] == 'X')){
                    board[5] = current_game->symbols[i];
                    createBoard();
                }
                else if(current_game->choices[i] == '6' && (current_game->symbols[i] == 'O' || current_game->symbols[i] == 'X')){
                    board[6] = current_game->symbols[i];
                    createBoard();
                }
                else if(current_game->choices[i] == '7' && (current_game->symbols[i] == 'O' || current_game->symbols[i] == 'X')){
                    board[7] = current_game->symbols[i];
                    createBoard();
                }
                else if(current_game->choices[i] == '8' && (current_game->symbols[i] == 'O' || current_game->symbols[i] == 'X')){
                    board[8] = current_game->symbols[i];
                    createBoard();
                }
                else if(current_game->choices[i] == '9' && (current_game->symbols[i] == 'O' || current_game->symbols[i] == 'X')){
                    board[9] = current_game->symbols[i];
                    createBoard();
                }
            }
            
            
        }
        current_game = current_game->next;
    }
    
    if(found == 0)
    {
        printf("Game Id not found");
    }
}

//Write every moves into the file using arrays
void write(char * choices, char * symbols)
{
    FILE *infile = fopen("save.txt", "a+");
    if (infile != NULL)
    {
        
        fprintf(infile,"%s %s\n",choices, symbols);
        fclose(infile);
    }
    else
    {
        printf("The file for storing choices and marks is empty\n");
        return;
    }
}

//Replay move played during the tic tac toe game
void replay(char *choices, char *symbols){
    
    for(int i = 1; i < 10; i++){
        
        if(choices[i] == '1' && (symbols[i] == 'O' || symbols[i] == 'X')){
            board[1] = symbols[i];
            createBoard();
        }
        
        else if(choices[i] == '2' && (symbols[i] == 'O' || symbols[i] == 'X')){
            board[2] = symbols[i];
            createBoard();
        }
        
        else if(choices[i] == '3' && (symbols[i] == 'O' || symbols[i] == 'X')){
            board[3] = symbols[i];
            createBoard();
        }
        
        else if(choices[i] == '4' && (symbols[i] == 'O' || symbols[i] == 'X')){
            board[4] = symbols[i];
            createBoard();
        }
        
        else if(choices[i] == '5' && (symbols[i] == 'O' || symbols[i] == 'X')){
            board[5] = symbols[i];
            createBoard();
        }
        
        else if(choices[i] == '6' && (symbols[i] == 'O' || symbols[i] == 'X')){
            board[6] = symbols[i];
            createBoard();
        }
        
        else if(choices[i] == '7' && (symbols[i] == 'O' || symbols[i] == 'X')){
            board[7] = symbols[i];
            createBoard();
        }
        
        else if(choices[i] == '8' && (symbols[i] == 'O' || symbols[i] == 'X')){
            board[8] = symbols[i];
            createBoard();
        }
        
        else if(choices[i] == '9' && (symbols[i] == 'O' || symbols[i] == 'X')){
            board[9] = symbols[i];
            createBoard();
        }
        
    }
    
}

//Reset moves of the game
void resetMoves(char * choices, char * symbols){
    choices[1] = '1';
    choices[2] = '2';
    choices[3] = '3';
    choices[4] = '4';
    choices[5] = '5';
    choices[6] = '6';
    choices[7] = '7';
    choices[8] = '8';
    choices[9] = '9';
    symbols[1] = '1';
    symbols[2] = '2';
    symbols[3] = '3';
    symbols[4] = '4';
    symbols[5] = '5';
    symbols[6] = '6';
    symbols[7] = '7';
    symbols[8] = '8';
    symbols[9] = '9';
}

//Function to undo move on the board
void undoMove(struct stack * undoSymbols, struct stack * undoChoices, struct stack * redoSymbols, struct stack * redoChoices){
    char symbol = pop(undoSymbols);
    char choice = pop(undoChoices);
    push(redoSymbols, symbol);
    push(redoChoices, choice);
    
    if(choice == '1'){
        board[1] = '1';
    }
    else if(choice == '2'){
        board[2] = '2';
    }
    else if(choice == '3'){
        board[3] = '3';
    }
    else if(choice == '4'){
        board[4] = '4';
    }
    else if(choice == '5'){
        board[5] = '5';
    }
    else if(choice == '6'){
        board[6] = '6';
    }
    else if(choice == '7'){
        board[7] = '7';
    }
    else if(choice == '8'){
        board[8] = '8';
    }
    else if(choice == '9'){
        board[9] = '9';
    }
}
//Function to redo move on the board
void redoMove(struct stack * undoSymbols, struct stack * undoChoices, struct stack * redoSymbols, struct stack * redoChoices){
    char symbol = pop(redoSymbols);
    char choice = pop(redoChoices);
    push(undoSymbols, symbol);
    push(undoChoices, choice);
    if(choice == '1'){
        board[1] = symbol;
    }
    else if(choice == '2'){
        board[2] = symbol;
    }
    else if(choice == '3'){
        board[3] = symbol;
    }
    else if(choice == '4'){
        board[4] = symbol;
    }
    else if(choice == '5'){
        board[5] = symbol;
    }
    else if(choice == '6'){
        board[6] = symbol;
    }
    else if(choice == '7'){
        board[7] = symbol;
    }
    else if(choice == '8'){
        board[8] = symbol;
    }
    else if(choice == '9'){
        board[9] = symbol;
    }
}

void main_menu()
{
    printf("\n                  HELLO !\n\n");
    printf("     WELCOME TO THE GAME OF TIC TAC TOE\n\n");
    printf("     **********************************\n");
    printf("\n                0. EXIT\n");
    printf("\n                1. GAME\n");
    printf("\n                2. SEARCH GAME\n");
    printf("\n                3. HELP\n");
}

//main function
int main(){
    
    char option[10];
    while(1){
        int start;
        main_menu();
        scanf("%d",&start);
        
        if(start == 0)
        {
            exit(0);
        }
        else if(start == 1){
            do{
                resetBoard();
                
                int player = 1, i, choice;
                
                char symbol;
                
                int j = 1;
                resetMoves(choices, symbols);
                
                //Create stack of capacity 9
                struct stack * UndoSymbols = init_stack(9);
                struct stack * UndoChoices = init_stack(9);
                struct stack * RedoSymbols = init_stack(9);
                struct stack * RedoChoices = init_stack(9);
                
                createBoard();
                
                
                do{
                    
                    createBoard();
                    
                    player = (player % 2) ? 1 : 2;
                    symbol = (player == 1) ? 'X' : 'O';
                    
                    printf("Player %d, enter a number (PRESS 10 to undo/ PRESS 11 to redo) ", player);
                    scanf("%d", &choice);
                    
                    //Set the choice selected to be the mark on the board, push into the stack in order to allow undo
                    if(choice == 1 && board[1] == '1')
                    {
                        board[1] = symbol;
                        symbols[j] = symbol;
                        choices[j] = '1';
                        j++;
                        push(UndoChoices, '1');
                        push(UndoSymbols, symbol);
                        createBoard();
                    }
                    else if(choice == 2 && board[2] == '2'){
                        board[2] = symbol;
                        symbols[j] = symbol;
                        choices[j] = '2';
                        j++;
                        push(UndoChoices, '2');
                        push(UndoSymbols, symbol);
                        createBoard();
                    }
                    
                    else if(choice == 3 && board[3] == '3'){
                        board[3] = symbol;
                        symbols[j] = symbol;
                        choices[j] = '3';
                        j++;
                        push(UndoChoices, '3');
                        push(UndoSymbols, symbol);
                        createBoard();
                    }
                    
                    else if(choice == 4 && board[4] == '4'){
                        board[4] = symbol;
                        symbols[j] = symbol;
                        choices[j] = '4';
                        j++;
                        push(UndoChoices, '4');
                        push(UndoSymbols, symbol);
                        createBoard();
                    }
                    
                    else if(choice == 5 && board[5] == '5'){
                        board[5] = symbol;
                        symbols[j] = symbol;
                        choices[j] = '5';
                        j++;
                        push(UndoChoices, '5');
                        push(UndoSymbols, symbol);
                        createBoard();
                    }
                    
                    else if(choice == 6 && board[6] == '6'){
                        board[6] = symbol;
                        symbols[j] = symbol;
                        choices[j] = '6';
                        j++;
                        push(UndoChoices, '6');
                        push(UndoSymbols, symbol);
                        createBoard();
                    }
                    
                    else if(choice == 7 && board[7] == '7'){
                        board[7] = symbol;
                        symbols[j] = symbol;
                        choices[j] = '7';
                        j++;
                        push(UndoChoices, '7');
                        push(UndoSymbols, symbol);
                        createBoard();
                    }
                    
                    else if(choice == 8 && board[8] == '8'){
                        board[8] = symbol;
                        symbols[j] = symbol;
                        choices[j] = '8';
                        j++;
                        push(UndoChoices, '8');
                        push(UndoSymbols, symbol);
                        createBoard();
                    }
                    else if(choice == 9 && board[9] == '9'){
                        board[9] = symbol;
                        symbols[j] = symbol;
                        choices[j] = '9';
                        j++;
                        push(UndoChoices, '9');
                        push(UndoSymbols, symbol);
                        createBoard();
                        
                        
                    }
                    
                    else if(choice == 10){
                        if(!(stackEmpty(UndoChoices) && stackEmpty(UndoSymbols)))
                        {
                            undoMove(UndoSymbols, UndoChoices, UndoSymbols, RedoChoices);
                            createBoard();
                        }
                        else
                        {
                            player--;
                            printf("You have 0 moves on the board!");
                            getchar();
                        }
                    }
                    
                    else if(choice == 11){
                        if(!(stackEmpty(RedoChoices) && stackEmpty(UndoSymbols)))
                        {
                            redoMove(UndoSymbols,UndoChoices,UndoSymbols,RedoChoices);
                            createBoard();
                        }
                        else
                        {
                            
                            printf("Error: You can't redo!");
                            player--;
                            getchar();
                        }
                    }
                    
                    else
                    {
                        
                        printf("Invalid Choice");
                        player--;
                        getchar();
                    }
                    
                    i = gameWin();
                    player++;
                    
                }while(i == -1);
                
                createBoard();
                
                if(i == 1){
                    printf("==>\aPlayer %d win\n ", --player);
                    for(int i = 0; i <= UndoChoices->top; i++){
                        printf("%c", UndoChoices->moves[i]);
                    }
                    printf("\n");
                    for(int i = 0; i <= UndoSymbols->top;  i++){
                        printf("%c", UndoSymbols->moves[i]);
                    }
                    
                    write(UndoChoices->moves, UndoSymbols->moves);
                    
                    getchar();
                    resetBoard();
                    replay(choices,symbols);
                    printf("\nPlay Again?(yes/no)\n");
                    scanf("%s", option);
                }
                else
                {
                    printf("==>\aGame draw");
                    for(int i = 0; i <= UndoChoices->top; i++){
                        printf("%c", UndoChoices->moves[i]);
                    }
                    printf("\n");
                    for(int i = 0; i <= UndoSymbols->top;  i++){
                        printf("%c", UndoSymbols->moves[i]);
                    }
                    write(UndoChoices->moves, UndoSymbols->moves);
                    getchar();
                    resetBoard();
                    replay(choices,symbols);
                    printf("Play Again?(yes/no)\n");
                    scanf("%s", option);
                }
                getchar();
                
            }while(strcmp(option, "yes") == 0);
        }
        
        else if(start == 2){
            int gameID = -1;
            resetBoard();
            createBoard();
            struct TicTacToe * game = NULL;
            printf("Game\n");
            read(&game);
            printf("\nEnter Game Id: ");
            scanf("%d", &gameID);
            printf("gameID is %d\n", gameID);
            recordGame(&game, gameID);
            scanf("%s", option);
            system("clear");
        }
        else if(start == 3)
        {
            
            printf("1. The game is played on a grid that's 3 squares by 3 squares.\n");
            printf("2. You are X, your friend is O. Players take turns putting their marks in empty squares.\n");
            printf("3. The first player to get 3 of her marks in a row (up, down, across, or diagonally) is the winner.\n");
            printf("4. When all 9 squares are full, the game is over. If no player has 3 marks in a row, the game ends in a tie.\n\n");
            printf("Press any key to go back to the main menu\n");
            scanf("%s", option);
            system("clear");
            
        }
        else
        {
            printf("Please Select 0. Exit, 1. Game, 2. Search Game. or 3. Help.\n");
            exit(1);
        }
        
    }
    
    return 0;
}

//Check winner or draw
int gameWin(){
    if(board[1] == board[2] && board[2] == board[3])
        return 1;
    else if(board[4] == board[5] && board[5] == board[6]){
        return 1;
    }
    else if(board[7] == board[8] && board[8] == board[9]){
        return 1;
    }
    else if(board[1] == board[4] && board[4] == board[7]){
        return 1;
    }
    else if(board[2] == board[5] && board[5] == board[8]){
        return 1;
    }
    else if(board[3] == board[6] && board[6] == board[9]){
        return 1;
    }
    else if(board[1] == board[5] && board[5] == board[9]){
        return 1;
    }
    else if(board[3] == board[5] && board[5] == board[7]){
        return 1;
    }
    else if(board[1] != '1' && board[2] != '2' && board[3] != '3' && board[4] != '4' && board[5] != '5' && board[6] != '6' && board[7] != '7' && board[8] != '8' && board[9] != '9'){
        return 0;
    }
    else{
        return -1;
    }
}

void createBoard(){
    
    system("clear");
    printf("\n\n\tTic Tac Toe\n\n");
    printf("Player 1 (X) - Player 2 (O)\n\n\n");
    printf("       |       |     \n");
    printf("  %c    |   %c   |   %c \n", board[1], board[2], board[3]);
    
    printf("_______|_______|_______\n");
    printf("       |       |     \n");
    
    printf("  %c    |   %c   |   %c \n", board[4], board[5], board[6]);
    
    printf("_______|_______|_______\n");
    printf("       |       |     \n");
    
    printf("  %c    |   %c   |   %c \n", board[7], board[8], board[9]);
    
    printf("       |       |     \n\n");
}



