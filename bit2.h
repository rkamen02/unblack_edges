/*
 * bit2.h
 * by Samuel Weaver (sweave05) and Ross Kamen (rkamen02)
 * September 21, 2016
 * HW2
 * 
 * User interface for the Bit2_T structure and functions.
 * 
 * A Bit2_T is a strucutre that represents a 2D Array of bits.
 * It may only store the values 1 and 0.
 *
 */

#ifndef BIT2_H
#define BIT2_H

#include "bit.h"

typedef struct Bit2_T *Bit2_T;



/***            USER FUNCTIONS                          */



/* 
 * Returns the number of 1s stored in the given Bit2_T.
 * Throws CRE if array is unitialized or has been 
 * improperly tampered with by the user.
 */
int Bit2_count( Bit2_T array );

/* 
 * Returns the value in Bit2_T at the given coordinate.
 * Throws CRE if array is unitialized or has been 
 * improperly tampered with by the user.
 * Throws CRE if (x,y) is out of the bounds of array.
 */
int Bit2_get( Bit2_T array, int x, int y );

/*
 * Returns the height of the given Bit2_T.
 * Throws CRE if array is unitialized or has been 
 * improperly tampered with by the user.
 */
int Bit2_height(Bit2_T array );

/* 
 * Sets the bit at the given cordinate in the given Bit2_T to the given value.
 * Returns the previous value of (x,y).
 * Throws CRE if array is unitialized or has been 
 * improperly tampered with by the user.
 * Throws CRE if (x,y) is out of the bounds of array.
 */
int Bit2_put( Bit2_T array, int x, int y, int v );

/* 
 * Returns the width of the given Bit2_T
 * Throws CRE if array is unitialized or has been 
 * improperly tampered with by the user.
 */
int Bit2_width( Bit2_T array );



/* 
 * Allocates space for and creates a new Bit2_T of the given size
 * Throws CRE if width or height are not natural numbers.
 */
Bit2_T Bit2_new( int width, int height );



/* 
 * Sets the bit at the given coordinate in the given Bit2_T to 0.
 * Throws CRE if array is unitialized or has been 
 * improperly tampered with by the user.
 * Throws CRE if (x,y) is out of the bounds of array.
 */
void Bit2_clear( Bit2_T array, int x, int y);

/* 
 * Sets all of the bits in the box defined with the corners (x1, y1)
 * and (x2, y2) to 0. Either coordinate may define any of the corners.
 * Throws CRE if array is unitialized or has been 
 * improperly tampered with by the user.
 * Throws CRE if (x1,y1) or (x2, y2) is out of the bounds of array.
 */
void Bit2_clear_box( Bit2_T array, int x1, int y1, int x2, int y2 );

/* 
 * Frees all of the memory allocated for and in the given Bit2_T
 * Throws CRE if array is unitialized or has been 
 * improperly tampered with by the user.
 */
void Bit2_free( Bit2_T *array );

/* 
 * Applies the given function to every bit in the given Bit2_T. Iterates
 * down a collumn before moving to the next one.
 * Throws CRE if array is unitialized or has been 
 * improperly tampered with by the user.
 */
void Bit2_map_col_major( Bit2_T array, 
                         void apply(    int x, 
                                        int y, 
                                        Bit2_T array, 
                                        int val, 
                                        void *cl ), 
                         void *cl );

/*
 * Applies the given function to every bit in the given Bit2_T. Iterates
 * down a row before moving to the next one.
 * Throws CRE if array is unitialized or has been 
 * improperly tampered with by the user.
 */
void Bit2_map_row_major( Bit2_T array, 
                         void apply(    int x, 
                                        int y, 
                                        Bit2_T array, 
                                        int val, 
                                        void *cl ), 
                         void *cl );

/* 
 * Sets the bit at the given coordinate in the given Bit2_T to its opposite.
 * Throws CRE if array is unitialized or has been 
 * improperly tampered with by the user.
 * Throws CRE if (x,y) is out of the bounds of array.
 */
void Bit2_not( Bit2_T array, int x, int y );

/* 
 * Sets all of the bits in the box defined with the corners (x1, y1)
 * and (x2, y2) to their opposites. Either coordinate may define 
 * any of the corners. 
 * Throws CRE if array is unitialized or has been 
 * improperly tampered with by the user.
 * Throws CRE if (x1,y1) or (x2, y2) is out of the bounds of array.
 */
void Bit2_not_box( Bit2_T array, int x1, int y1, int x2, int y2 );

/* 
 * Sets all of the bits in the box defined with the corners (x1, y1)
 * and (x2, y2) to the given value. Either coordinates may define 
 * any of the corners.
 * Throws CRE if array is unitialized or has been 
 * improperly tampered with by the user.
 * Throws CRE if (x1,y1) or (x2, y2) is out of the bounds of array.
 */
void Bit2_put_box( Bit2_T array, int x1, int y1, int x2, int y2, int val );

/* 
 * Sets the bit at the given cordinate in the given Bit2_T to 1.
 * Throws CRE if array is unitialized or has been 
 * improperly tampered with by the user.
 * Throws CRE if (x,y) is out of the bounds of array.
 */
void Bit2_set( Bit2_T array, int x, int y );

/* 
 * Sets all of the bits in the box defined with the corners (x1, y1)
 * and (x2, y2) to 1. Either coordinates may define any of the corners.
 * Throws CRE if array is unitialized or has been 
 * improperly tampered with by the user.
 * Throws CRE if (x1,y1) or (x2, y2) is out of the bounds of array.
 */
void Bit2_set_box( Bit2_T array, int x1, int y1, int x2, int y2 );

#endif
