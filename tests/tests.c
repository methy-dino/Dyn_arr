#include<stdio.h>
#include"dyn_arr.h"
#include<assert.h>
void free_int(void* intptr){
    //printf("called");
    //printf("returned: %d\n", *(int*)intptr);
    free(*(void**)intptr);
}
int index_tests(){
	int test[4] = {213, 543, 7569, 18932};
	Dyn_arr* arr = build_arr(test, 4, sizeof(int));
	arr_remove(arr, 1);
	int* a = malloc(sizeof(int));
    *a = 10;
	arr_add_at(arr, a, 2);
	assert(*(int*)arr_get(arr, 2) == *a);
    printf("I T1 PASS\n");
    arr_remove(arr, arr_find(arr, a));
    int* testcp = malloc(sizeof(int));
    *testcp = 543;
    arr_add_at(arr, testcp, 1);
    for (size_t i = 0; i < arr->length; i++){
        //printf("%d == %d\n", *(int*)arr_get(arr, i), test[i]);
        assert(*(int*)arr_get(arr, i) == test[i]);
    }
    printf("I T2 PASS\n");
		int b = 10135;
		//check for proper growth
		for (int i = 0; i < 200; i++){
			arr_add(arr, &b);
		}
	printf("I T3 PASS\n");
    int* c = malloc(sizeof(int));
    int* d = malloc(sizeof(int));   
    *c = 98;
    *d = 8;    
    Dyn_arr* del = empty_arr(3,sizeof(int*));
    arr_add(del, &c);
    arr_add(del, &d);
    arr_discard(del, &free_int);
    printf("I T4 PASS\n");
	return 0;
}
