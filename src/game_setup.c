#include "game_setup.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

#include "game.h"
#include "common.h"

// Some handy dandy macros for decompression
#define E_CAP_HEX 0x45
#define E_LOW_HEX 0x65
#define G_CAP_HEX 0x47
#define G_LOW_HEX 0x67
#define S_CAP_HEX 0x53
#define S_LOW_HEX 0x73
#define W_CAP_HEX 0x57
#define W_LOW_HEX 0x77
#define DIGIT_START 0x30
#define DIGIT_END 0x39

/** Initializes the board with walls around the edge of the board.
 *
 * Modifies values pointed to by cells_p, width_p, and height_p and initializes
 * cells array to reflect this default board.
 *
 * Returns INIT_SUCCESS to indicate that it was successful.
 *
 * Arguments:
 *  - cells_p: a pointer to a memory location where a pointer to the first
 *             element in a newly initialized array of cells should be stored.
 *  - width_p: a pointer to a memory location where the newly initialized
 *             width should be stored.
 *  - height_p: a pointer to a memory location where the newly initialized
 *              height should be stored.
 */
enum board_init_status initialize_default_board(int** cells_p, size_t* width_p,
                                                size_t* height_p) {
    *width_p = 20;
    *height_p = 10;
    int* cells = malloc(20 * 10 * sizeof(int));
    *cells_p = cells;
    for (int i = 0; i < 20 * 10; i++) {
        cells[i] = PLAIN_CELL;
    }

    // Set edge cells!
    // Top and bottom edges:
    for (int i = 0; i < 20; ++i) {
        cells[i] = FLAG_WALL;
        cells[i + (20 * (10 - 1))] = FLAG_WALL;
    }
    // Left and right edges:
    for (int i = 0; i < 10; ++i) {
        cells[i * 20] = FLAG_WALL;
        cells[i * 20 + 20 - 1] = FLAG_WALL;
    }

    // Set grass cells!
    // Top and bottom edges:
    for (int i = 1; i < 19; ++i) {
        cells[i + 20] = FLAG_GRASS;
        cells[i + (20 * (9 - 1))] = FLAG_GRASS;
    }
    // Left and right edges:
    for (int i = 1; i < 9; ++i) {
        cells[i * 20 + 1] = FLAG_GRASS;
        cells[i * 20 + 19 - 1] = FLAG_GRASS;
    }

    // Add snake
    cells[20 * 2 + 2] = FLAG_SNAKE;

    return INIT_SUCCESS;
}


/** Initialize variables relevant to the game board.
 * Arguments:
 *  - cells_p: a pointer to a memory location where a pointer to the first
 *             element in a newly initialized array of cells should be stored.
 *  - width_p: a pointer to a memory location where the newly initialized
 *             width should be stored.
 *  - height_p: a pointer to a memory location where the newly initialized
 *              height should be stored.
 *  - snake_p: a pointer to your snake struct (not used until part 3!)
 *  - board_rep: a string representing the initial board. May be NULL for
 * default board.
 */
enum board_init_status initialize_game(int** cells_p, size_t* width_p,
                                       size_t* height_p, snake_t* snake_p,
                                       char* board_rep) {
    snake_t snakel;
    snakel.g_snakedirc = RIGHT;
    snakel.head = NULL;
    *snake_p = snakel;



    g_game_over = 0;
    g_score = 0;
    
    enum board_init_status result;

    if (board_rep){
        result = decompress_board_str(cells_p, width_p, height_p, snake_p, board_rep);
        place_food(*cells_p, *width_p, *height_p);
        // int i = 0;
        for (size_t i = 0; i < ((*width_p) * (*height_p)); i++){
            if ((*cells_p)[i] == FLAG_SNAKE){
                int locs = i;
                insert_first(&(snake_p->head), &locs, sizeof(locs));
                break;
            }
            
    }
    }
    else{
        result = initialize_default_board(cells_p, width_p, height_p);
        place_food(*cells_p, *width_p, *height_p);
        int loc =  42;
        insert_first(&(snake_p->head), &loc, sizeof(loc));
    
        
    }
    return result;
}
 // set board letters
int set_board(char ele) {
    switch (ele) {
        case 'S':
            return FLAG_SNAKE;
        case 'W':
            return FLAG_WALL;
        case 'E':
            return PLAIN_CELL;
        case 'G':
            return FLAG_GRASS;
        default:
            return -1; 
    }
}
/**
This function helps to fill put the array with each type
*/
void fill_array (int head, int end, int* cells, int max, int ele){
    int i;
    for (i = head; i < head+end; i = i+1) {
        if (i<max){
        cells[i] = ele;
    }
}
}


/** 
This function helps to read the numbers of each compressed string and turn it into an int so we can pass
into like B 789 it will return the 789 or an error*/
int read_b (char* compressed_string){
    char* boarddim = strtok(compressed_string, "|");

    int rownumber = 0; //initialize the row
    if (boarddim[0] == 'B'){
        // boarddim ++; // increment
        rownumber =atoi(&boarddim[1]); //store first number
    }     
    return rownumber;
}
//find all the mumbers after the character x
int read_x (char* compressed_string){
    // char* tobefreed = strdup(compressed_string);
    char* boarddim = strtok(compressed_string, "|");

    int col = 0;
    int i = 0;
    while (boarddim[i] != '\0') { 
        if (boarddim[i] == 'x'){ // find element that has x
            col = atoi(boarddim + i +  1); //store first number
            break;
        }    
        i = i + 1; 
    }
    return col;
}
char* read_string (int** cells_p, size_t* width_p, size_t* height_p, char* compressed_string){
    if (compressed_string == NULL) {
        printf("Invalid input: compressed_string is NULL\n");
        return NULL;
    }

    // Make a copy of the compressed string to avoid modifying the original
    char* tobefreed = strdup(compressed_string);
    if (tobefreed == NULL) {
        printf("Memory allocation error\n");
        return NULL;
    }
    char* boarddim = strtok(tobefreed, "|");

    int row = 0;
    int col = 0;

    if (boarddim == NULL) {
        printf("Invalid format: Missing row dimension\n");
        free(tobefreed);
        return NULL;  
    }

    if (boarddim[0] == 'B'){
        row = read_b(compressed_string);
    }
    else{
        printf("Invalid format: Missing column dimension\n");
    }
    boarddim = strtok(NULL, "|");
    if (boarddim == NULL) {
        printf("Invalid format: Missing column dimension\n");
        free(tobefreed);
        return NULL;  // Or return an appropriate error code
    }
    if (boarddim[0] == 'x'){
        col = read_x(boarddim);
     }
    else{
        free(tobefreed);
     }

    *height_p = row;
    *width_p = col;

    free(tobefreed);
    return strtok(NULL, "|");
}
    



/** Takes in a string `compressed` and initializes values pointed to by
 * cells_p, width_p, and height_p accordingly. Arguments:
 *      - cells_p: a pointer to the pointer representing the cells array
 *                 that we would like to initialize.
 *      - width_p: a pointer to the width variable we'd like to initialize.
 *      - height_p: a pointer to the height variable we'd like to initialize.
 *      - snake_p: a pointer to your snake struct (not used until part 3!)
 *      - compressed: a string that contains the representation of the board.
 *
 */
enum board_init_status decompress_board_str(int** cells_p, size_t* width_p,
                                            size_t* height_p, snake_t* snake_p,
                                            char* compressed) {
    
    char* boarddim = strtok(compressed, "|");
    int rownumber = 0; 

    // check if first chracter is a B
    if (boarddim[0] != 'B'){
        return INIT_ERR_BAD_CHAR;
    }
    //check if character is valid
    if (!((boarddim[1] <= 0x39) & (boarddim[1] >= 0x30))){
        return INIT_ERR_BAD_CHAR;
    }

    rownumber =atoi(&boarddim[1]);
    
  
    int i = 1;
    while(boarddim[i] != 'x'){ 
        i++; 
    }
    if(boarddim[i] != 'x'){
        return INIT_ERR_BAD_CHAR;
    }
    
    int columnnumber = atoi(&boarddim[i+1]);
    if(columnnumber == 0){
        return INIT_ERR_BAD_CHAR;
    }

    *width_p = columnnumber;
    *height_p = rownumber;

    int* arr = malloc(columnnumber * rownumber * sizeof(int));
    *cells_p = arr;

    char* tocheck = strtok(NULL, "|");
    int rowcount = 0; 
    int start = 0;
    int snakecount = 0;
  
    
    while (tocheck != NULL){ 
  
        int colcoun = 0;
        int total = 0;
        int len_toc = strlen(tocheck);
        int arrayl = columnnumber * rownumber;

        while(colcoun < len_toc){
        
            int itemn = 1;
            if ((tocheck[colcoun] >= 'A' && tocheck[colcoun] <= 'Z')){
                char letter = tocheck[colcoun];
                itemn = atoi(&tocheck[colcoun+1]);
                total += itemn;
                

                if (!((letter== 'S') || (letter== 'G') || (letter== 'W') || (letter== 'E'))){
                    return INIT_ERR_BAD_CHAR;
                }
                if (itemn == 0){
                    return INIT_ERR_INCORRECT_DIMENSIONS;
                }
                else if (letter == 'S' && (itemn != 0)){
                    snakecount += itemn;
                    
                }

                int chart = set_board(letter);
                
                fill_array(start, itemn, arr, arrayl, chart);
                start +=itemn;
            }
            colcoun++;
        }

        if(total != columnnumber){
            return INIT_ERR_INCORRECT_DIMENSIONS;
        }

        rowcount++;  

        tocheck = strtok(NULL, "|");
    }

    if (rowcount != rownumber){
        return INIT_ERR_INCORRECT_DIMENSIONS;
    }
    
    if (snakecount != 1){
        return INIT_ERR_WRONG_SNAKE_NUM;
    }

    
    return INIT_SUCCESS;

}
