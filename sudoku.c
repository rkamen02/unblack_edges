/*
 * sudoku.c
 * by Samuel Weaver (sweave05) and Ross Kamen (rkamen02)
 * September 27, 2016
 * HW2
 *
 * sudoku.c verifies the validity of a potential sudoku solution.
 * It returns 0 for a valid solution and 1 for an invalid solution.
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <pnmrdr.h>
#include <math.h>
#include "uarray2.h"

int read_and_check(FILE *f);
int check_sudoku(Pnmrdr_T rdr);
int check_row(UArray2_T sudoku, int row);
int check_col(UArray2_T sudoku, int col);
int check_box(UArray2_T sudoku, int x, int y);
int check_vect( int vect[]);

int main( int argc, char *argv[])
{
        assert(argc <= 2);

        FILE *solution = NULL;
        int answer;

        if (argc == 2){
                solution = fopen( argv[1], "rb");
                assert( solution != NULL);
        } else {
                solution = stdin;
        }

        answer = read_and_check(solution);
        fclose(solution);

        return answer;
}

/*
 * read_and_check
 *      purp: creates a Pnmrdr and verifies the file specifications
 *      args: pointer to a FILE
 *      rets: 0 for potential sudoku solution, 1 for invalid solution
 */
int read_and_check(FILE *f)
{
        int answer;
        Pnmrdr_T rdr;
        int width, height, denominator;

        rdr = Pnmrdr_new(f);

        /* make sure the file meets specifications */
        assert( Pnmrdr_data(rdr).type == Pnmrdr_gray);
        width = Pnmrdr_data(rdr).width;
        height = Pnmrdr_data(rdr).height;
        denominator = Pnmrdr_data(rdr).denominator;
        assert( (width == 9) && (height == 9) && (denominator == 9));

        answer = check_sudoku(rdr);

        Pnmrdr_free(&rdr);

        return answer;
}

/*
 * check_sudoku
 *      purp: verifies the validity of the sudoku solution
 *      args: Pnmrdr_T
 *      rets: 0 for potential sudoku solution, 1 for invalid solution
 */
int check_sudoku(Pnmrdr_T rdr)
{
        UArray2_T sudoku;
        int value;
        int *valuep;
        int x, y;

        /* sum total of valid rows, cols, and boxes in the sudoku board */
        /* anything under 27 is an invalid board */
        int results = 0;

        sudoku = UArray2_new(9,9,sizeof(int));

        /* populate the UArray2. verify each number is valid */
        for (int i = 0; i < 9; i++){
                for (int j = 0; j < 9; j++){
                        value = Pnmrdr_get(rdr);
                        assert( (value > 0) && (value <= 9) );
                        valuep = (int *)UArray2_at( sudoku, i, j);
                        *valuep = value;
                }
        }

        /* break UArray2 into rows/cols/boxes and verify each */
        for (int i = 0; i < 9; i++){
                results += check_row( sudoku, i);
                results += check_col( sudoku, i);

                /* (x,y) represents the top left corner of each box
                 * will be (0,0), (0,3), (0,6), (3, 0), (3,3), etc. */
                x = floor( i / 3 );
                y = i - (3 * x);
                x *= 3;
                y *= 3;
                results += check_box( sudoku, x, y);
        }

        UArray2_free(&sudoku);

        if (results != 27) {
                return 1;
        }
        return 0;
}

/*
 * check_row
 *      purp: constructs a 1D array for a given row number from
                a 2D array
 *      args: UArray2_T sudoku board, int row number
 *      rets: 1 for valid row, 0 for invalid row
 */
int check_row( UArray2_T sudoku, int i)
{
        int row[9];
        int *valuep;
        for (int y = 0; y < 9; y++){
                valuep = (int *)UArray2_at( sudoku, i, y);
                row[ y] = *valuep;
        }

        return( check_vect( row));
}

/* check_col
 *      purp: constructs a 1D array for a given col number from
 *              a 2D array
 *      args: UArray2_T sudoku board, int col number
 *      rets: 1 for valid row, 0 for invalid row
 */
int check_col( UArray2_T sudoku, int i)
{
        int col[9];
        int *valuep;
        for (int x = 0; x < 9; x++){
                valuep = (int *)UArray2_at( sudoku, x, i);
                col[x] = *valuep;
        }

        return( check_vect( col));

}

/*
 * check_box
 *      purp: constructs a 1D array of all numbers in
 *              a given 3x3 box from a 2D array
 *      args: UArray2_T sudoku board, int x coord, int y coord
 *      rets: 1 for valid box, 0 for invalid box
 */
int check_box( UArray2_T sudoku, int x, int y)
{
        int box[9];
        int *valuep;
        int index = 0;
        for (int col = x; col < (x+3); col++){
                for (int row = y; row < (y+3); row++){
                        valuep = (int *)UArray2_at( sudoku, row, col);
                        box[index] = *valuep;
                        index++;
                }
        }

        return( check_vect( box));
}

/*
 * check_vect
 *      purp: checks whether all numbers in an array are different
 *              in a 9-digit array
 *      args: int array
 *      rets: 1 for a nonrepeating array, 0 for an array with repeats
 */
int check_vect( int vect[])
{
        for (int i = 0; i < 9; i++){
                assert( (vect[i] > 0) && (vect[i] <= 9) );
                for (int j = (i + 1); j < 9; j++){
                        if ( vect[i] == vect[j] ){
                                return 0;
                        }
                }
        }

        return 1;
}
