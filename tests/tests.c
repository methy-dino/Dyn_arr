#include<stdio.h>
#include"dyn_arr.h"
#include<assert.h>
int int_ptr_equal(void* int_a, void* int_b){
	if (**((int**)int_a) == **((int**)int_b)){
		return 0;
	}
	return 1;
}
void int_print(void* num){
	printf("%d", *(int*)num);
}
void free_int(void* intptr){
    //printf("called");
    //printf("returned: %d\n", *(int*)intptr);
    free(*(void**)intptr);
}
int index_tests(){
	int test[4] = {213, 543, 7569, 18932};
	Dyn_arr* arr = build_arr(test, 4, sizeof(int));
	arr_remove(arr, 1);
	int a = 10;
	arr_add_at(arr, &a, 2);
	assert(*(int*)arr_get(arr, 2) == a);
    printf("I T1 PASS\n");
    arr_remove(arr, arr_find(arr, &a));
    int testcp = 543;
    arr_add_at(arr, &testcp, 1);
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
		int* d_match = malloc(sizeof(int));  
		*c = 98;
    *d = 8;
		*d_match = 8;
    Dyn_arr* del = empty_arr(3,sizeof(int*));
    arr_add(del, &c);
    arr_add(del, &d);
		assert(arr_seek(del, &d_match, &int_ptr_equal) == 1);
    printf("I T4 PASS\n");
		*d_match = 9;
		assert(arr_seek(del, &d_match, &int_ptr_equal) == -1);
		printf("I T5 PASS\n");
		arr_discard(del, &free_int);
    printf("I T6 PASS\n");
		arr_print(arr, &int_print);
		printf("I T7 PASS\n");
		arr_discard(arr, NULL);
		printf("I T8 PASS\n");
	return 0;
}
