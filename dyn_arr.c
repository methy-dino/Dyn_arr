#include<stdlib.h> // malloc, free and size_t.
#include<string.h> //memcpy
#include<stdio.h>
typedef struct arr {
	// sizeof(char) == 1, can get to any byte using chars.
	char* arr; 
	size_t element_size;
	size_t length;
	size_t capacity;
} Dyn_arr;

char* arr_get(Dyn_arr* arr, size_t index){
	return &(arr->arr[index * arr->element_size]);
}
void grow_darr(Dyn_arr* darr, size_t inc){
	char* n_arr = malloc(darr->element_size * inc + darr->capacity * darr->element_size);
	memcpy(n_arr, darr->arr, darr->capacity * darr->element_size);
    darr->capacity = inc + darr->capacity;
	free(darr->arr);
	darr->arr = n_arr;
}
/* creates a dyn_arr with the provided bytes and lengths; 
 * beware that memory must be allocated since the grow method calls free()
 */
Dyn_arr* init_arr(void* init_vals, size_t init_quan, size_t val_size){
	Dyn_arr* ret = malloc(sizeof(Dyn_arr));
	ret->element_size = val_size;
	ret->length = init_quan;
	ret->capacity = init_quan;
	ret->arr = (char*) init_vals;
	return ret;
}
/* creates a dyn_arr with spare space, copying bytes from init_vals */
Dyn_arr* build_arr(void* init_vals, size_t init_quan, size_t val_size){
	Dyn_arr* ret = malloc(sizeof(Dyn_arr));
	ret->capacity = init_quan;
	ret->arr = malloc(ret->capacity * val_size);
	ret->element_size = val_size;
	ret->length = init_quan;
	memcpy(ret->arr, init_vals, init_quan * val_size);
	return ret;
}
Dyn_arr* empty_arr(size_t init_quan, size_t val_size){
    Dyn_arr* ret = malloc(sizeof(Dyn_arr));
    ret->arr = malloc(init_quan * val_size);
	ret->element_size = val_size;
    ret->length = 0;
	ret->capacity = init_quan;
}
/* puts element at the end of 'arr', checking if it needs to grow to fit that data */
void arr_add(Dyn_arr* arr, void* element){
	if (arr->length == arr->capacity){
		grow_darr(arr, arr->capacity / 2);
	}
	memcpy(arr->arr + arr->length * arr->element_size, element, arr->element_size);
    arr->length++;
}
void arr_add_at(Dyn_arr* arr, void* element, size_t index){
	if (arr->length == arr->capacity){
		grow_darr(arr, arr->length / 2);
	}
	memcpy(arr->arr + (index+1) * arr->element_size, arr->arr + index * arr->element_size , (arr->length - index) * arr->element_size);
	memcpy(arr->arr +index * arr->element_size, element, arr->element_size);
    arr->length++;
}
/* removes the element at index, reducing index of things higher than it. */
void arr_remove(Dyn_arr* arr, size_t index){
	memcpy(arr->arr +index * arr->element_size, arr->arr + (index+1) * arr->element_size, (arr->length - index) * arr->element_size); 
	arr->length--;
}

size_t arr_find(Dyn_arr* arr, void* target, int(*is_equal)(void* a, void* b)){
	if (is_equal != NULL){
		for (size_t i = 0; i < arr->length*arr->element_size; i+= arr->element_size){
  		if (is_equal(target, arr->arr + i) == 0){
				return i / arr->element_size;
			}
  	}
	} else {
		for (size_t i = 0; i < arr->length*arr->element_size; i+= arr->element_size){
			if (memcmp(arr->arr + i, target, arr->element_size) == 0){
				return i / arr->element_size;
			}
		}
	}
	return -1;
}
void arr_discard(Dyn_arr* arr, void(*func)(void* arg)){
    if (func){
        for (size_t i = 0; i < arr->length*arr->element_size; i+= arr->element_size){
            func(arr->arr + i);
        }
    }
    free(arr->arr);
    free(arr);
}
void arr_print(Dyn_arr* arr, void (printer)(void*)){	
	printf("data of array at: %p \n length is %u and capacity is %u, elements occupy %u bytes.\n", (void*) arr, arr->length, arr->capacity, arr->element_size);
	if (printer){
		printf("data of it's contents at: %p\n [", arr->arr);
		for (size_t i = 0; i < (arr->length-1)*arr->element_size; i+= arr->element_size){
    	printer(arr->arr + i);
			printf(", ");
  	}
		printer(arr->arr + arr->length * arr->element_size);
		printf("]\n");
	}
}
// to be used on arr_print.
void addressPrint(void* ptr){
	printf("contents at: %p", ptr);
}
