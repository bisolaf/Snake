#include "game.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <stddef.h>

#include "linked_list.h"
#include "mbstrings.h"
#include "common.h"

int remove_free(node_t** head) {
    int* remove = remove_last(head);
    int value = *remove;
    free(remove);
    return value;
}

// enum dirc change_dir(enum input_key dirc){
//     if (dirc == INPUT_LEFT){
//         return RIGHT;
//     }
//     if (dirc == INPUT_RIGHT){
//         return LEFT;
//     }
//     if (dirc == INPUT_DOWN){
//         return UP;
//     }
//     if (dirc == INPUT_UP){
//         return DOWN;
//     }
//     return RIGHT;
// }


 snake_t* create_snake() {
    // Allocate memory for the snake struct
    snake_t* new_snake = (snake_t*)malloc(sizeof(snake_t));
    if (new_snake == NULL) {
        // Handle memory allocation failure
        // For example, print an error message and return NULL
        return NULL;
    }
    
    // Initialize the fields of the snake struct if needed
    new_snake->head = NULL; // Initialize g_snakeloc to NULL or allocate memory for it
    new_snake->g_snakedirc = RIGHT; // Initialize g_snakedirc to a default value
    
    // Return a pointer to the newly created snake struct
    return new_snake;
}

/** Updates the game by a single step, and modifies the game information
 * accordingly. Arguments:
 *  - cells: a pointer to the first integer in an array of integers representing
 *    each board cell.
 *  - width: width of the board.
 *  - height: height of the board.
 *  - snake_p: pointer to your snake struct (not used until part 3!)
 *  - input: the next input.
 *  - growing: 0 if the snake does not grow on eating, 1 if it does.
 */
void update(int* cells, size_t width, size_t height, snake_t* snake_p,
            enum input_key input, int growing) {
    // `update` should update the board, your snake's data, and global
    // variables representing game information to reflect new state. If in the
    // updated position, the snake runs into a wall or itself, it will not move
    // and global variable g_game_over will be 1. Otherwise, it will be moved
    // to the new position. If the snake eats food, the game score (`g_score`)
    // increases by 1. This function assumes that the board is surrounded by
    // walls, so it does not handle the case where a snake runs off the board.

    // TODO: implement! 
    if (g_game_over == 1){
        return;
    }
    // static enum input_key curr = INPUT_RIGHT;

    // if (input != INPUT_NONE){
    //     if ((curr != change_dir(input)) || (length_list(snake_p->head)< 2)){
    //         curr = input;
    //     }
    // }
    int* pointer = get_first(snake_p->head);
    int move_snake;
    int g_snakeloc = ((*(int*)(snake_p->head->data)));
    move_snake  = *pointer + 1;
    enum dirc g_snakedirc = snake_p->g_snakedirc;
    

    if (input != INPUT_NONE) {
        if (input == INPUT_DOWN){
                snake_p->g_snakedirc = DOWN;
                move_snake  = g_snakeloc + width;
        }
        
        if (input == INPUT_UP){
                move_snake  = g_snakeloc - width;
                snake_p->g_snakedirc = UP;
        }
        if (input == INPUT_RIGHT){
                move_snake  = g_snakeloc + 1;
                snake_p->g_snakedirc = RIGHT;
        } 
        if (input == INPUT_LEFT) { // (input == INPUT_LEFT)
                move_snake  = g_snakeloc - 1;
                snake_p->g_snakedirc = LEFT;        
        }
    }
    else {
            if (g_snakedirc == DOWN){ // direction == DOWN not input! this part of the if statement is when the input is none
                move_snake  = g_snakeloc + width; 
                          
            }     
           if ( g_snakedirc == UP){
                move_snake  = g_snakeloc - width;
            }  
            if (g_snakedirc == LEFT){ //(g_snakedirc == LEFT)
                move_snake  = g_snakeloc - 1;
            }
    }
    ///create a new fuction with enum that moves the opposite direction
        
    //validity
    int tail = (*(int*)get_last(snake_p->head));
        if (cells[move_snake] == FLAG_WALL || (cells[move_snake] == FLAG_SNAKE && move_snake != tail) || (cells[move_snake] == (FLAG_SNAKE | FLAG_GRASS) && move_snake != tail)) {
         g_game_over = 1;
        }

        else {
            //when the next cell 
            if (growing == 1){ //if growing ==1

            if (move_snake == (*(int*)get_last(snake_p->head))) {
                int old_head = *((int*)(snake_p->head->data));
                remove_free(&(snake_p->head));
                insert_first(&(snake_p->head), &old_head, sizeof(old_head));
    
            }
        

//  if (length_list(snake_p->head)>1){
 if (cells[move_snake] == FLAG_SNAKE) {
    // Check the current direction of the snake and the input direction
    // Update the snake's direction if the input is in the opposite direction of its current direction
    if ((g_snakedirc == RIGHT) && (input == INPUT_LEFT)) {
        snake_p->g_snakedirc = RIGHT;
        move_snake =(*(int*)get_last(snake_p->head));
        cells[move_snake - width] = PLAIN_CELL;
        cells[((*(int*)(snake_p->head->data)))] = FLAG_SNAKE; //curr loc
        cells[((*(int*)(snake_p->head->data))) + width] = FLAG_SNAKE;
    }
    if ((g_snakedirc == LEFT) && (input == INPUT_RIGHT)) {
        snake_p->g_snakedirc = LEFT;
            move_snake =(*(int*)get_last(snake_p->head));
         cells[move_snake - width] = PLAIN_CELL;
        cells[((*(int*)(snake_p->head->data)))] = FLAG_SNAKE; //curr loc
        cells[((*(int*)(snake_p->head->data))) + width] = FLAG_SNAKE;
    }
    if ((g_snakedirc == UP) && (input == INPUT_DOWN)) {
        snake_p->g_snakedirc = UP;
        move_snake =(*(int*)get_last(snake_p->head));
         cells[move_snake - width] = PLAIN_CELL;
        cells[((*(int*)(snake_p->head->data)))] = FLAG_SNAKE; //curr loc
        cells[((*(int*)(snake_p->head->data))) + width] = FLAG_SNAKE;
    }
    if ((g_snakedirc == DOWN) && (input == INPUT_UP)) {
        snake_p->g_snakedirc = DOWN;
        move_snake =(*(int*)get_last(snake_p->head));
        cells[move_snake - width] = PLAIN_CELL;
        cells[((*(int*)(snake_p->head->data)))] = FLAG_SNAKE; //curr loc
        cells[((*(int*)(snake_p->head->data))) + width] = FLAG_SNAKE;
    }
}
//  }

            

            if (cells[move_snake] == FLAG_GRASS ){ 
                int old = remove_free(&(snake_p->head));
                insert_first(&(snake_p->head), &move_snake, sizeof(move_snake)); 
                if((cells[old] == FLAG_SNAKE)){ 
                cells[old] = cells[old] ^ FLAG_SNAKE;
                cells[move_snake] = FLAG_SNAKE | FLAG_GRASS;
            }
                else if(cells[old] == (FLAG_SNAKE | FLAG_GRASS)){ 
                cells[old] = FLAG_GRASS;
                cells[move_snake] = FLAG_SNAKE | FLAG_GRASS;
            }
            } 

        else { //plain cell case
            if (cells[move_snake] == PLAIN_CELL){
                int old = remove_free(&(snake_p->head));
                insert_first(&(snake_p->head), &move_snake, sizeof(move_snake)); 
                if (cells[old] == (FLAG_SNAKE | FLAG_GRASS)){
                 cells[move_snake] = FLAG_SNAKE;
                 cells[old] = FLAG_GRASS;
               }
                else{
                 cells[old] = PLAIN_CELL;
    
                 }
            cells[move_snake]  = FLAG_SNAKE;
        }
        }
       }
            

        if ((cells[move_snake] == FLAG_FOOD) || (cells[move_snake] == (FLAG_FOOD | FLAG_GRASS))) {   
            g_score ++;
            place_food(cells, width, height);
            insert_first(&(snake_p->head), &move_snake, sizeof(move_snake)); 
            if (growing == 1){  
                if (cells[move_snake] == (FLAG_FOOD | FLAG_GRASS)){ 
                    cells[move_snake] = FLAG_SNAKE | FLAG_GRASS;
                }
                if (cells[move_snake] == FLAG_FOOD){
                    cells[move_snake] = FLAG_SNAKE;
                   }
            }
                //else case for food
             if (cells[move_snake] == (FLAG_FOOD | FLAG_GRASS)){
                cells[move_snake] = FLAG_SNAKE | FLAG_GRASS;
                cells[g_snakeloc] = cells[g_snakeloc] ^ FLAG_SNAKE;
            }
                 else if (cells[move_snake] == FLAG_FOOD){
                cells[move_snake] = FLAG_SNAKE;
                cells[g_snakeloc] = PLAIN_CELL;
            }
            }
         ///regular functionality snake 0
            if (cells[move_snake] == FLAG_GRASS ){ 
            if((cells[g_snakeloc] == FLAG_SNAKE)){ 
                cells[g_snakeloc] = PLAIN_CELL;
                cells[move_snake] = FLAG_SNAKE | FLAG_GRASS;
            }
            else if(cells[g_snakeloc] == (FLAG_SNAKE | FLAG_GRASS)){ 
            cells[g_snakeloc] = FLAG_GRASS;
            cells[move_snake] = FLAG_SNAKE | FLAG_GRASS;
            }
        } 
        if (cells[move_snake] == PLAIN_CELL){
         if (cells[g_snakeloc] == (FLAG_SNAKE | FLAG_GRASS)){
                cells[move_snake] = FLAG_SNAKE;
                cells[g_snakeloc] = FLAG_GRASS;
                 }
                 else{
                    cells[g_snakeloc]  = PLAIN_CELL;
                 }
            cells[move_snake]  = FLAG_SNAKE;
        }       
            (*(int*)(snake_p->head->data)) = move_snake;
              
        }
        }
            
        
            
             
        
        


        
        
        
    
    
      

/** Sets a random space on the given board to food.
 * Arguments:
 *  - cells: a pointer to the first integer in an array of integers representing
 *    each board cell.
 *  - width: the width of the board
 *  - height: the height of the board
 */
void place_food(int* cells, size_t width, size_t height) {
    /* DO NOT MODIFY THIS FUNCTION */
    unsigned food_index = generate_index(width * height);
    // check that the cell is empty or only contains grass
    if ((*(cells + food_index) == PLAIN_CELL) || (*(cells + food_index) == FLAG_GRASS)) {
        *(cells + food_index) |= FLAG_FOOD;
    } else {
        place_food(cells, width, height);
    }
    /* DO NOT MODIFY THIS FUNCTION */
}

/** Prompts the user for their name and saves it in the given buffer.
 * Arguments:
 *  - `write_into`: a pointer to the buffer to be written into.
 */
void read_name(char* write_into) {
    // TODO: implement! (remove the call to strcpy once you begin your
    // implementation)
    // strcpy(write_into, "placeholder");
    printf("Name >");
    fflush(stdout);
    int args = read(0, write_into, 1000);

    while (args == 1){
        printf("Name Invalid: must be longer than 0 characters.");
        fflush(stderr);

        printf("Name >");
        fflush(stdout);
        args = read(0, write_into, 1000);
    }
    if (args > 1){
        *(write_into + (args-1)) = '\0';
        return;
    }
}

/** Cleans up on game over — should free any allocated memory so that the
 * LeakSanitizer doesn't complain.
 * Arguments:
 *  - cells: a pointer to the first integer in an array of integers representing
 *    each board cell.
 *  - snake_p: a pointer to your snake struct. (not needed until part 3)
 */
void teardown(int* cells, snake_t* snake_p) {
    // TODO: implement!
    // free(snake_p);
    while (snake_p->head != NULL){
        void* node = get_first(snake_p->head);
        remove_element(&(snake_p->head), node, sizeof(*node));
    }
    free(cells);
    // if (snake_p->g_snakeloc->data != NULL){
    //      free(snake_p);
    // }
}
