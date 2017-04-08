/*
 * uarray2.h
 * by Samuel Weaver (sweave05) and Ross Kamen (rkamen02)
 * September 21, 2016
 * HW2
 * 
 * User interface for the UArray2_T structure and functions.
 *
 * A UArray2_T is a pointer to a structure that represents a homogenous
 * 2D array of unboxed data.
 *
 */

#ifndef UARRAY2_H
#define UARRAY2_H

#include "uarray.h"

typedef struct UArray2_T *UArray2_T;



/* Returns the height of the given UArray2_T */
int UArray2_height( UArray2_T array);

/* Returns the size of a single element in the UArray2_T */
int UArray2_size(   UArray2_T array);

/* Returns the width of the given UArray2_T */
int UArray2_width(  UArray2_T array);



/* Returns a pointer to a newly created UArray2_T */
UArray2_T UArray2_new( int w, int h, int size);



/* 
 * Returns a void pointer to the element in UArray2_T at the given coordinate
 */
void *UArray2_at( UArray2_T array, int x, int y);

/* Frees all of the memory allocated in and for the given UArray2_T */
void  UArray2_free( UArray2_T *array);

/*
 * Applies the given function to each element in the given UArray2_T 
 * iterating down a collumn before going to the next one.
 */
void  UArray2_map_col_major( UArray2_T array, 
                             void apply(int x, 
                                        int y, 
                                        UArray2_T array, 
                                        void *z, 
                                        void *cl), 
                             void *cl);

/*
 * Applies the given function to each element in the given UArray2_T
 * iterating across a row before going down to the next one.
 */
void  UArray2_map_row_major( UArray2_T array, 
                             void apply(int x, 
                                        int y, 
                                        UArray2_T array, 
                                        void *z, 
                                        void *cl), 
                             void *cl);



#undef UArray2_T

#endif
