#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

#define INITIAL_CAPACITY 10;

typedef struct {
    int *data;
    size_t size;
    size_t capacity;
} ArrayList;

ArrayList *arraylist_new(size_t initial_capacity) {
    if (initial_capacity == 0) {
        initial_capacity = INITIAL_CAPACITY;
    }

    ArrayList *list = malloc(sizeof(ArrayList));
    if (list == NULL) return NULL;


    list->data = malloc(sizeof(int) * initial_capacity);
    if (list->data == NULL) {
        free(list);
        return NULL;
    }

    list->capacity = initial_capacity;
    list->size = 0;

    return list;
}

bool arraylist_insert(ArrayList *list, int value) {
    if (list->size == list->capacity) {
        size_t new_capacity = list->capacity * 2;
        int *new_data = realloc(list->data, new_capacity * sizeof(int));
        if (new_data == NULL) {
            return false;
        }
        list->data = new_data;
        list->capacity = new_capacity;
    }

    list->data[list->size] = value;
    list->size++;
    return true;
}

bool arraylist_get(ArrayList *list, size_t position, int *out_value) {
    if (position >= list->size) return false;
    *out_value = list->data[position];
    return true;
}

bool arraylist_set(ArrayList *list, size_t position, int in_value) {
    if (position >= list->size) return false;
    list->data[position] = in_value;
    return true;
}

bool arraylist_remove(ArrayList *list, size_t position) {
    if (position >= list->size) return false;
    for (size_t i = position; i < list->size - 1; i++) {
        list->data[i] = list->data[i+1];
    }
    list->size--;
    return true;
}

bool arraylist_destroy(ArrayList *list) {
    if (list == NULL) return false;
    free(list->data);
    free(list);
    return true;
}

void arraylist_printinfo(ArrayList *list) {
    printf("list data: %p\n", list->data);
    printf("list capacity: %lu\n", list->capacity);
    printf("list size: %lu\n", list->size);
}

void arraylist_print(ArrayList *list, int num_bytes) {
    // computes the max number of bytes to represent a int number , which is
    // the max_digits plus 1 bytes for the sign
    int item_bytes = (floor(log10(2^(num_bytes * 8 - 1) - 1)) + 1) + 1;
    
    // 2 brackets + 1 terminator
    size_t str_size = 2 + 1;
    
    // (max_digits + 1 comma + 1 space) for each list elements but the last one + the last max_digits element
    if (list->size) str_size += (item_bytes + 2)  * (list->size - 1) + item_bytes;
    
    // init the str_list only with the opened bracket
    char str_list[str_size];
    str_list[0] = '[';
    str_list[1] = 0;

    if(list->size) {
        for (size_t i = 0; i < list->size - 1; i++) {
            size_t l = strlen(str_list);
            sprintf(str_list + l, "%d, ", list->data[i]);
        }
        sprintf(str_list + strlen(str_list), "%d]", list->data[list->size - 1]);
    } else {
        sprintf(str_list + strlen(str_list), "%s", "]");
    }
    printf("list%s\n", str_list);
}



int main(void) {
    ArrayList *list = arraylist_new(2);
    int num_bytes = sizeof(int);

    arraylist_insert(list, 2);
    arraylist_insert(list, 4);
    arraylist_insert(list, 43);
    arraylist_insert(list, 32);
    arraylist_insert(list, 5);
    arraylist_insert(list, 67);
    arraylist_print(list, num_bytes);

    arraylist_set(list, 2, 15);
    arraylist_print(list, num_bytes);

    int out_value;
    arraylist_get(list, 5, &out_value);
    printf("got value %d\n", out_value);

    arraylist_remove(list, 3);
    arraylist_print(list,num_bytes);

    arraylist_remove(list, 1);
    arraylist_print(list, num_bytes);
    
    arraylist_remove(list, 0);
    arraylist_remove(list, 0);
    arraylist_remove(list, 0);
    arraylist_remove(list, 0);
    arraylist_print(list, num_bytes);
}
