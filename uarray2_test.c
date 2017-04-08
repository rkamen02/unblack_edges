#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "uarray2.h"

const int width = 9;
const int height = 9;
const int size = sizeof( int);

void insert_values( int x, int y, UArray2_T t, void *value, void *cl){
        (void)cl;

        int *value_at = (int *)UArray2_at( t, x, y);
        assert( value_at == value);
        assert( *value_at == *((int *)value));

        *value_at = (x * x) + (y * y);
}

void check_values( int x, int y, UArray2_T t, void *value, void *cl){
        (void)cl;

        int *value_at = (int *)UArray2_at( t, x, y);
        assert( value_at == value);
        assert( *value_at == *((int *)value));

        assert( ((x * x) + (y * y)) == *value_at);
}

void print( int x, int y, UArray2_T t, void *value, void *cl){
        (void)cl;

        int *value_at = (int *)UArray2_at( t, x, y);
        assert( value_at == value);
        assert( *value_at == *((int *)value));

        printf( "%-3d ", *value_at);
        if( x == (width - 1)){
                printf( "\n");
        }       
}

int main() {
                
        UArray2_T t;
        
        //t = UArray2_new( -width, height, size);
        //t = UArray2_new( width, -height, size);
        //t = UArray2_new( width, height, -1);
        
        t = UArray2_new( width, height, size);
        
        assert( width == UArray2_width( t));
        assert( height == UArray2_height( t));
        assert( size == UArray2_size( t));
        
        UArray2_map_col_major( t, insert_values, NULL);
        UArray2_map_row_major( t, check_values, NULL);
        
        UArray2_map_row_major( t, print, NULL);
        
        UArray2_free( &t);
        
        return EXIT_SUCCESS;
}
