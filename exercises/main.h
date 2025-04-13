#pragma once
#include <stdio.h>

void reverse_char_arr_elem_by_elem();
void reverse_int_arr_elem_by_elem();
void reverse_int_arr_byte_by_byte();
void reverse_float_arr_byte_by_byte();
void* reverse_any_arr_byte_by_byte(void* start, void* end);
void* reverse_any_arr_bit_by_bit(void* start, void* end);
int recursion_fib_seq_1(int n);
int iteration_fib_seq(int n);
int recursion_fib_seq_2(int n, int* last);
void test_fib_seq();
void print_any_data_bit_by_bit_1(void* start, unsigned int num);
void print_any_data_bit_by_bit_2(void* start, unsigned int num);
void test_print_byb();
void* recursion_revrs_any_by_byte(void* start, void* end);
void test_recursion_reverse();
void* bubble_sort_linklist(void** head, size_t offsetof_next, int (*pfunc)(const void* elem1, const void* elem2));
void* merge_sort_linklist(void** head, size_t offsetof_next, int (*pfunc)(const void* elem1, const void* elem2));
void test_sort_linklist();
