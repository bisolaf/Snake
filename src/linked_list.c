#include "linked_list.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

/**
 * In this file, you will find the partial implementation of common doubly
 * linked list functions.
 *
 * Your first task is to debug some of the functions!
 *
 * After you have found all of the bugs, you will be writing three doubly
 * linked list functions and test them.
 *
 */

/**
 * find and return the length of the list
 *
 * given a pointer to the head of list
 */
int length_list(node_t* head_list) {
  int len = 0;
  if (!head_list) {
    return len;
  }
  node_t* current = head_list;
  while (current) {
    len++;
    current = current->next;
  }
  return len;
}

/**
 * returns the value of the head of the list
 *
 * given pointer to the head of the list
 */
void* get_first(node_t* head_list) { 
  if (head_list) {
    return head_list->data; 
  }
  return NULL;
  
}
  

/** returns the value of the last element of the list
 *
 * given a pointer to the head of the list
 */
void* get_last(node_t* head_list) {
  if (head_list) {
  node_t* curr = head_list;
  while (curr->next) {
    curr = curr->next;
  }
    return curr->data;  
  }
  return NULL;
  }

/** TODO: implement this!
 * inserts element at the beginning of the list
 *
 * given a pointer to the head of the list, a void pointer representing the
 * value to be added, and the size of the data pointed to
 *
 * returns nothing
 */
void insert_first(node_t** head_list, void* to_add, size_t size) { 
  // if the value to be added is empty
  if (!to_add) {
    return;
  }
  // initialize a new node and assign memory
  node_t* new_node = (node_t*)malloc(sizeof(node_t)); 

  void* new_data = malloc(size);
  memcpy(new_data, to_add, size);
  new_node->data = new_data;
//check if list is populated
  if (!(*head_list)) {  
    *head_list = new_node;
    new_node->prev = NULL;
    new_node->next = NULL;
    return;
  }

  node_t* curr = *head_list;
  new_node->prev = NULL;
  new_node->next= curr; 
  curr->prev = new_node;
  *head_list = new_node;
  }

/**
 * inserts element at the end of the linked list
 *
 * given a pointer to the head of the list, a void pointer representing the
 * value to be added, and the size of the data pointed to
 *
 * returns nothing
 */
void insert_last(node_t** head_list, void* to_add, size_t size) {
  if (!to_add) {
    return;
  }

  node_t* new_node = (node_t*)malloc(sizeof(node_t));
  void* new_data = malloc(size);
  memcpy(new_data, to_add, size);
  new_node->data = new_data;

  if (!(*head_list)) { 
    *head_list = new_node;
    new_node->prev = NULL;
    new_node->next = NULL;
    return;
  }node_t* curr = *head_list;
  while (curr->next) {
    curr = curr->next;
  }curr->next = new_node;
  new_node->prev = curr;
  new_node->next= NULL;
}

/** TODO: implement this!
 * gets the element from the linked list
 *
 * given a pointer to the head of the list and an index into the linked list
 * you need to check to see if the index is out of bounds (negative or longer
 * than linked list)
 *
 * returns the string associated with an index into the linked list
 */
void* get(node_t* head_list, int index) { 
  
  node_t* curr = head_list; // set current
  int counter = 0;

  while (curr) {
    if (counter == index){
      return curr->data;
    }
    curr = curr->next;
    counter = counter+ 1;
  }
  return NULL; 

  if (!head_list){ //is list empty?
    return NULL;
  }

  if (index <0 ){ // is index out of bounds?
    return NULL;
  }
}

/**
 * removes element from linked list
 *
 * given a pointer to the head of list, a void pointer of the node to remove
 * you need to account for if the void pointer doesn't exist in the linked list
 *
 * returns 1 on success and 0 on failure of removing an element from the linked
 * list
 */
int remove_element(node_t **head_list, void *to_remove, size_t size) {
  node_t* curr = *head_list;

  while (curr) {
    if (!memcmp(curr->data, to_remove, size)) { 
      if (curr->next) {
        curr->next->prev = curr->prev;
      }
      if (curr == *head_list) {
        *head_list = curr->next;
      } else {
        curr->prev->next = curr->next;
      }
      free(curr->data);
      free(curr);
      return 1;
    }
    curr = curr->next;
  }

  return 0;
  if (!(*head_list)) {
    return 0;  //failure of removing an element
  }
}

/**
 * reverses the list given a double pointer to the first element
 *
 * returns nothing
 */
void reverse_helper(node_t** head_list) {
    if (!head_list ){
        return;
    }
   if (!(*head_list)) {
    return;
   }

    node_t* curr = *head_list;
    node_t* placeholder = NULL;

    while (curr) {
        node_t* next_node = curr->next;
        curr->next = placeholder;
        curr->prev = next_node;
        placeholder = curr;
        curr = next_node;
    }

    *head_list = placeholder;
}

/**
 * calls a helper function that reverses the linked list
 *
 * given a pointer to the first element
 *
 * returns nothing
 */
void reverse(node_t** head_list) {
  if (head_list) {
    reverse_helper(head_list);
  }
}

/**
 * removes the first element of the linked list if it exists
 *
 * given a pointer to the head of the linked list
 *
 * returns the void pointer of the element removed
 *
 */
void* remove_first(node_t** head_list) {
  if (!(*head_list)) {
    return NULL;
  }
  node_t* curr = *head_list;
  *head_list = (*head_list)->next;

  if (*head_list) {
    (*head_list)->prev = NULL;
  }

  // free(curr->data);
  // free(curr);

  // return curr->data;
  void* result = curr->data;

  // Free memory of the removed node
  free(curr);

  return result;

}

/** TODO: implement this!
 * removes the last element of the linked list if it exists
 *
 * given a pointer to the head of the linked list
 *
 * returns the void pointer of the element removed
 *
 */
void* remove_last(node_t** head_list) { 
  
  if (!(*head_list)) { // if empty
    return NULL;
  }
  
  node_t* curr = *head_list;
  while (curr->next) {
    curr = curr->next;
  }
  if (curr == *head_list) {
    *head_list = NULL;
  } else { //remove node
    curr->prev->next = NULL;
  }
  void* data = curr->data;
  free(curr); // fixes address sanitizer issue

  return data; //ptr not val

  }