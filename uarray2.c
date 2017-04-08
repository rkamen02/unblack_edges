/*
 * uarray2.c
 * by Samuel Weaver (sweave05) and Ross Kamen (rkamen02)
 * September 27, 2016
 * HW2
 * 
 * Implementation of the UArray2_T functions.
 *
 */

#include <stdlib.h>
#include <assert.h>
#include "uarray2.h"



/***            STRUCTURE DEFINTION                     */



struct UArray2_T {
        int *width;
        int *height;
        int *size;
        UArray_T *array;

};



/***            HELPER FUNCTIONS                        */

int  UArray2_index( UArray2_T array, int x, int y );
void UArray2_assert_array( UArray2_T array );
void UArray2_assert_coords( UArray2_T array, int x, int y);

/*
 *
 * index 
 *      purp: calculate the index in the 1D array of the value at (x,y)
 *      args: the array, x coordinate, y coordinate
 *      rets: the index where (x,y) is held
 *
 */
int UArray2_index( UArray2_T array, int x, int y )
{
        UArray2_assert_array( array);
        UArray2_assert_coords( array, x, y);

        int height = UArray2_height( array);

        return (height * x) + y;
}

/*
 *
 * assert_array 
 *      purp: runs a series of assertions making sure the given array has
 *              been properly intialized and constructed
 *      args: an array
 *      rets: nothing
 *
 */
void UArray2_assert_array( UArray2_T array )
{
        assert( array != NULL );
        assert( sizeof( array) == sizeof( UArray2_T));
        assert( sizeof( *array) == sizeof( struct UArray2_T));
        assert( (*(array->width) > 0) && (*(array->height) > 0));
}

/*
 *
 * assert_coords
 *      purp: runs a series of assertions making sure the given coordinates
 *              fall within the bounds of the given array
 *      args: an array, x coordinate, y coordinate
 *      rets: nothing
 *
 */
void UArray2_assert_coords( UArray2_T array, int x, int y)
{
        UArray2_assert_array( array);
        assert( (x >= 0) && (y >= 0));

        int width = UArray2_width( array);
        int height = UArray2_height( array);

        assert( (width > 0) && (height > 0));
        assert( (x < width) && (y < height));
}

/***            PUBLIC FUNCTIONS                        */



/*
 *
 * width
 *      purp: returns the width of the given array
 *      args: an array
 *      rets: its width
 *
 */
int UArray2_width(UArray2_T array)
{
        UArray2_assert_array( array);
        return *(array -> width);
}

/*
 *
 * height
 *      purp: returns the height of the given array
 *      args: an array
 *      rets: its height
 *
 */
int UArray2_height(UArray2_T array)
{
        UArray2_assert_array( array);
        return *(array -> height);
}

/*
 *
 * size 
 *      purp: returns the size of an individual element in the given array
 *      args: an array
 *      rets: the size of one of its elements
 *
 */
int UArray2_size(UArray2_T array)
{
        UArray2_assert_array( array);
        return *(array -> size);
}

/*
 *
 * new
 *      purp: constructs a UArray2_T abiding by the given constraints
 *      args: a width, height, and element size
 *      rets: the UArray2_T
 *
 */
UArray2_T UArray2_new(int width, int height, int size)
{
        assert( (width > 0) && (height > 0) && (size > 0));
        
        int length = width * height;
        UArray_T UArray_1D = UArray_new( length, size);
        UArray2_T UArray_2D = malloc( sizeof( struct UArray2_T));

        assert( UArray_2D != NULL);

        /*malloc space for the data in the UArray2_T struct */
        UArray_2D -> width = malloc( sizeof( int));
        UArray_2D -> height = malloc( sizeof( int));
        UArray_2D -> size = malloc( sizeof( int));
        UArray_2D -> array = malloc( sizeof( UArray_1D));

        assert( UArray_2D -> width != NULL);
        assert( UArray_2D -> height != NULL);
        assert( UArray_2D -> size != NULL);
        assert( UArray_2D -> array != NULL);

        /*set all of the data in UArray2_T structure*/
        *(UArray_2D -> width) = width;
        *(UArray_2D -> height) = height;
        *(UArray_2D -> size) = size;
        *(UArray_2D -> array) = UArray_1D;

        return UArray_2D;
}

/*
 *
 * at
 *      purp: element retrieval
 *      args: an array, x coordinate, y coordinate
 *      rets: a pointer to the element at (x, y)
 *
 */
void *UArray2_at(UArray2_T array, int x, int y)
{
        UArray2_assert_array( array);
        UArray2_assert_coords( array, x, y);

        int index = UArray2_index( array, x, y);
        return UArray_at( *(array -> array), index);
}

/*
 *
 * map_col_major
 *      purp: iterates through the given array applying the given function
 *              to each element. Iterates from left to right then up to down
 *      args: an array, function to apply, closure void pointer
 *      rets: nothing
 *
 */
void UArray2_map_col_major(UArray2_T array, 
                void apply(int x, int y, UArray2_T array, void *z, void *cl), 
                void *cl)
{
        UArray2_assert_array( array);
        
        int height = UArray2_height( array);
        int width = UArray2_width( array);
        void *item;
        
        /*Iterate down rows*/
        for( int x = 0; x < width; x++){
                /*Iterate down collumns first*/
                for( int y = 0; y < height; y++){
                        item = UArray2_at( array, x, y);
                        apply( x, y, array, item, cl);
                }
        }
}

/*
 *
 * map_row_major
 *      purp: iterates through the given array applying the given function
 *              to each element. Iterates from top to bottom then left to right
 *      args: an array, function to apply, closure void pointer
 *      rets: nothing
 *
 */
void UArray2_map_row_major(UArray2_T array, 
                void apply(int x, int y, UArray2_T array, void *z, void *cl), 
                void *cl)
{
        UArray2_assert_array( array);
        
        int height = UArray2_height( array);
        int width = UArray2_width( array);
        void *item;
        
        /* Iterate down collumns */
        for( int y = 0; y < height; y++){
                /*Iterate down rows first */
                for( int x = 0; x < width; x++){
                        item = UArray2_at( array, x, y);
                        apply( x, y, array, item, cl);
                }
        }
}

/*
 *
 * map_col_major
 *      purp: frees all the memory allocated for an in a UArray2_T
 *      args: a pointer to an array
 *      rets: nothing
 *
 */
void UArray2_free(UArray2_T *array)
{
        UArray2_assert_array( *array);

        /*Free all of the stored integers*/
        free( (*array) -> height);
        free( (*array) -> width);
        free( (*array) -> size);
        
        /*Free the array the free the space allocated for it*/
        UArray_free( (*array) -> array);
        free( (*array) -> array);
        
        /*Free the space allocated for the structure*/
        free( *array);
        
}










