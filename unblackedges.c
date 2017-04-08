/*
 * unblackedges.c
 * by Samuel Weaver (sweave05) and Ross Kamen (rkamen02)
 * September 27, 2016
 * HW2
 *
 * unblackedges.c takes a bitmap and turns all black edges in it to white.
 * A blackedge is a pixel that is either on the edge of the picture and black
 * or adjacent to a blackedge pixel. 
 */

#include <pnmrdr.h>
#include <stack.h>
#include <stdio.h>
#include <stdlib.h>
#include "bit2.h"

struct coord {
        int x;
        int y;
};

typedef struct coord coord;

void initialize_stack( Bit2_T *image, Stack_T *coord_stack);
void file_to_array( FILE *f, Bit2_T *image);
void free_stack( Stack_T *stack);
void print_new_image( Bit2_T *image);
void print_pixel(int x, int y, Bit2_T image, int val, void *cl);
void push_neighbors( Bit2_T *image, Stack_T *coord_stack, coord coord);
void remove_black_edges( Bit2_T *image);

int main( int argc, char *argv[])
{
        if ( argc > 2) {
                fprintf( stderr, "Too many arguments\n");
                exit( EXIT_FAILURE);
        }

        FILE *file = NULL;
        Bit2_T image;

        if (argc == 2) {
                file = fopen( argv[1], "rb");
                
                if ( file == NULL) {
                        fprintf( stderr, "Error in file opening");
                        exit( EXIT_FAILURE);
                }
        } else {
                file = stdin;
        }
        
        file_to_array( file, &image);
        fclose( file);
        remove_black_edges( &image);
        print_new_image( &image);

        Bit2_free( &image);
        return 0;              
}

/*
 * intialize_stack
 *      purp: add all of the edge pixels in image to the stack in the form of 
 *              coords
 *      args: a pointer to a Bit2_T representing an image, a pointer to
 *              a stack of coords
 */
void initialize_stack( Bit2_T *image, Stack_T *coord_stack)
{
        int width = Bit2_width( *image);
        int height = Bit2_height( *image);

        struct coord *edge_coord;
        
        /* Iterate through the collumns from left to right */
        for ( int col = 0; col < width; col ++) {
                
                /* If we are in the first or last collumn */
                if ( (col == 0) || (col == (width - 1))) {
                        
                        /* Add every pixel in that collumn */
                        for ( int row = 0; row < height; row ++) {
                                
                                edge_coord = malloc( sizeof( struct coord));
                                
                                if (edge_coord == NULL) {
                                        fprintf(stderr, 
                                                "Could not allocate memory.\n");
                                        exit( EXIT_FAILURE);
                                }       
                                
                                edge_coord -> x = col;
                                edge_coord -> y = row;
                                Stack_push( *coord_stack, (void *)edge_coord);
                        }
                } else { /* If we are not in the first or last collumn */
                        
                        edge_coord = malloc( sizeof( struct coord));
                        if (edge_coord == NULL) {
                                fprintf(stderr, 
                                        "Could not allocate memory.\n");
                                exit( EXIT_FAILURE);
                        }
                        
                        /* Add the top pixel */
                        edge_coord -> x = col;
                        edge_coord -> y = 0;
                        Stack_push( *coord_stack, (void *)edge_coord);
                        
                        /* Add the bottom pixel */
                        edge_coord = malloc( sizeof( struct coord));
                        edge_coord -> x = col;
                        edge_coord -> y = height - 1;
                        Stack_push( *coord_stack, (void *)edge_coord); 
                }
        }
}

/*
 * file_to_array
 *      purp: given a bitmap file, populates the given Bit2_T with its pixels
 *      args: a pointer to a bitmap file, a pointer to a unitialized Bit2_T
 */
void file_to_array(FILE *f, Bit2_T *image)
{
        Pnmrdr_T rdr;
        int width, height, pixel;
        
        rdr = Pnmrdr_new(f);

        if ( Pnmrdr_data(rdr).type != Pnmrdr_bit) {
                fprintf( stderr, "Wrong file type");
                exit( EXIT_FAILURE);
        }
        
        width = Pnmrdr_data(rdr).width;
        height = Pnmrdr_data(rdr).height;
        *image = Bit2_new( width, height);
        
        for ( int row = 0; row < height; row++) {
                for ( int col = 0; col < width; col++) {
                        pixel = Pnmrdr_get( rdr);
                        
                        /* Bit2_Ts are intialized with 0s, we only set 1s */
                        if ( pixel == 1) {
                                Bit2_set( *image, col, row);
                        }
                }
        }
        
        Pnmrdr_free(&rdr);
}

/*
 * free_stack
 *      purp: frees all of the memory allocated in and for the given stack
 *      args: a pointer to a stack
 */
void free_stack( Stack_T *stack)
{
        while ( Stack_empty( *stack) == 0) {
                free( Stack_pop( *stack));
        }
        Stack_free( stack);
}

/*
 * print_new_image
 *      purp: prints the given Bit2_T to stdout in plain PDM format
 *      args: a pointer to a Bit2_T that reprsents a bitmap
 */
void print_new_image( Bit2_T *image)
{
        int width = Bit2_width( *image);
        int height = Bit2_height( *image);

        printf("P1\n%d %d\n", width, height);
        Bit2_map_row_major( *image, print_pixel, NULL);
}

/*
 * print_pixel
 *      purp: used with map_row_major for a Bit2_T, prints the image
 *              in English reading format, top left to bottom right, 
 *              left to right with new lines at the end of each row
 *      args: the x coordinate, y coordinate, Bit2_T array, value at (x,y),
 *              pointer to closure variable
 */
void print_pixel(int x, int y, Bit2_T image, int val, void *cl)
{
        (void) cl;
        (void) y;

        int width = Bit2_width( image);

        printf("%d", val);

        if ((x == (width - 1)) || (((x + 1) % 70) == 0)) {
                printf("\n");
        }

}

/*
 * push_neighbors
 *      purp: given an image, stack and coordinate, if the pixel at the given
 *              coordinate is black, pushes its black neighbors onto the stack
 *      args: a pointer to an image, a pointer to a stack of coords, a coord
 */
void push_neighbors( Bit2_T *image, Stack_T *coord_stack, coord coord)
{

        struct coord *push_coord;
        int width = Bit2_width( *image);
        int height = Bit2_height( *image);
        int x = coord.x;
        int y = coord.y;
        int x_neigh, y_neigh;   /* The corrdinate of a neighbor */
        
        /* Each pixel has only four neighbors */
        for (int i = 0; i < 4; i++) {
                x_neigh = i % 2;
                y_neigh = (i + 1) % 2;
                if (i >= 2) {
                        y_neigh *= -1;
                        x_neigh *= -1;
                }
                /* 
                 * The following chart shows the bijection between i and 
                 * the final values of x_mod and y_mod
                 * i  (i % 2) ((i + 1) % 2) x_neigh y_neigh
                 * 0        0             1     0     1   
                 * 1        1             0     1     0
                 * 2        0             1     0    -1 
                 * 3        1             0    -1     0
                 */
                
                /* Set (x_mod, y_mod) to reprsent a neighbor pixel */
                x_neigh += x;
                y_neigh += y;
                
                /* Skip the pixel neighbor if it is out of bounds */
                if (    (x_neigh < 0) || 
                        (y_neigh < 0) || 
                        (x_neigh >= width) || 
                        (y_neigh >= height)) {
                        continue;
                }               
                /* Skip the neighbor if it is white */
                if ( Bit2_get( *image, x_neigh, y_neigh) == 0) {
                        continue;
                }
                /* If the neighbor passes all tests, set and push it */
                push_coord = malloc( sizeof( struct coord));
                if (push_coord == NULL) {
                        fprintf( stderr, "Could not allocate memory.\n");
                        exit( EXIT_FAILURE);
                }
                push_coord -> x = x_neigh;
                push_coord -> y = y_neigh;
                Stack_push( *coord_stack, push_coord);
        }
}

/*
 * remove_black_edges
 *      purp: given a Bit2_T that represents a bitmap, turn all of its 
 *              black edges white
 *      args: a pointer to a Bit2_T
 */
void remove_black_edges( Bit2_T *image)
{
        Stack_T coord_stack = Stack_new();
        struct coord *curr_coord;
        int curr_bit;

        /* Push all edges onto the stack */     
        initialize_stack( image, &coord_stack);

        /* While the stack is not empty */
        while ( Stack_empty(coord_stack) == 0) {
                /* Get the top pixel and its value*/            
                curr_coord = Stack_pop(coord_stack);
                curr_bit = Bit2_get( *image, curr_coord -> x, curr_coord -> y);
                
                /* If it is black, clear it and push its neighbors */
                if ( curr_bit == 1) {
                        Bit2_clear( *image, curr_coord -> x, curr_coord -> y);
                        push_neighbors( image, &coord_stack, *curr_coord);
                }

                free(curr_coord);
        }

        Stack_free( &coord_stack);
}
