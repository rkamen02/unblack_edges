#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "bit2.h"

const int HEIGHT = 10;
const int WIDTH = 5;

void check_and_print(int i, int j, Bit2_T a, int b, void *p1)
{

        (void) p1;

        assert(b == Bit2_get(a, i, j));

        printf("%d ", Bit2_get(a, i, j));

        if ( (i == (WIDTH-1))){
                printf("\n");
        }
}

void check_even_cols(int i, int j, Bit2_T a, int b, void *p1)
{

        (void) p1;

        assert(b == Bit2_get(a, i, j));

        if (j % 2 == 0){
                Bit2_set(a,i,j);
        } else {
                Bit2_clear(a,i,j);
        }

        printf("%d ", Bit2_get(a,i,j));

        if ((j== (HEIGHT-1))){
                printf("\n");
        }
}

int main()
{

        Bit2_T temp;
        temp =  Bit2_new(100,1);
        Bit2_count(temp);


        printf("\nstarting test\n\n");

        printf("making new bit2\n");
        Bit2_T t = Bit2_new(WIDTH,HEIGHT);
        printf("made new bit2\n");

        printf("\ngetting width and height\n");
        printf("width: %d\n", Bit2_width(t));
        printf("height: %d\n", Bit2_height(t));

        printf("\nsetting some bits\n");
        printf("setting 0,0\n");
        Bit2_set(t, 0,0);
//      printf("setting 5, 10\n");
//      Bit2_set(t,5,10);
//      printf("setting -1, 5\n");
//      Bit2_set(t,-1, 5);
//      printf("setting 4, 11\n");
//      Bit2_set(t,4,11);
        Bit2_set(t, 4, 4);
        Bit2_set(t, 3, 2);
        printf("set 0,0: %d\n", Bit2_get(t,0,0));
        printf("set 4,4: %d\n", Bit2_get(t,4,4));
        printf("set 3,2: %d\n", Bit2_get(t,3,2));
        printf("uninitialized 1,1: %d\n", Bit2_get(t,1,1));
        printf("uninitialized 4,5: %d\n", Bit2_get(t,4,5));
        printf("getting 0,0 again: %d\n", Bit2_get(t,0,0));
        Bit2_set(t,0,0);
        printf("resetting and getting 0,0: %d\n", Bit2_get(t,0,0));
        printf("finished setting\n");

        printf("\nclearing some bits\n");
//      printf("clearing -1, 0\n");
//      Bit2_clear(t,-1,0);
//      printf("clearing 0, -1\n");
//      Bit2_clear(t,0,-1);
//      printf("clearing 5, 3\n");
//      Bit2_clear(t,5,3);
//      printf("clearing 3, 10\n");
//      Bit2_clear(t,3,10);
        Bit2_set(t,2,1);
        Bit2_clear(t,2,1);
        Bit2_set(t,4,8);
        Bit2_clear(t,4,8);
        Bit2_clear(t,3,8);
        printf("set then cleared 2,1: %d\n", Bit2_get(t,2,1));
        printf("set then cleared 4,8: %d\n", Bit2_get(t,4,8));
        printf("cleared 3,8: %d\n", Bit2_get(t,3,8));

        printf("\nnot-ing some bits\n");
        Bit2_not(t,1,3);
        Bit2_not(t,2,7);
        Bit2_set(t,3,6);
        Bit2_not(t,3,6);
        Bit2_set(t,4,8);
        Bit2_not(t,4,8);
        printf("not-ed 1,3: %d\n", Bit2_get(t,1,3));
        printf("not-ed 2,7: %d\n", Bit2_get(t,2,7));
        printf("set then not 3,6: %d\n", Bit2_get(t,3,6));
        printf("set then not 4,8: %d\n", Bit2_get(t,4,8)); 

        printf("\nputting some bits\n");
        Bit2_put(t,3,4,0);
        Bit2_put(t,4,6,1);
//      Bit2_put(t,2,9,2);
        printf("put 3,4,0: %d\n", Bit2_get(t,3,4));
        printf("put 4,6,1: %d\n", Bit2_get(t,4,6));
//      printf("put 2,9,2: %d\n", Bit2_get(t,2,9));

        printf("\nset box 0-2, 0-2\n");
        Bit2_set_box(t,0,0,2,2);

        printf("\nmapping to print\n");
        Bit2_map_row_major(t,check_and_print,NULL);

        printf("\nnot box 1-3, 1-3\n");
        Bit2_not_box(t,1,1,3,3);

        printf("\nmapping to print\n");
        Bit2_map_row_major(t,check_and_print,NULL);

        printf("\nclear box 2-4, 2-4\n");
        Bit2_clear_box(t,2,2,4,4);

        printf("\nmapping to print\n");
        Bit2_map_row_major(t,check_and_print,NULL);

        printf("\nput box 0-4, 0-9\n");
        Bit2_put_box(t,0,0,4,9,0);

        printf("\nmapping to print\n");
        Bit2_map_row_major(t,check_and_print,NULL);

        printf("\ncolumn printing\n");
        Bit2_map_col_major(t,check_even_cols,NULL);

        printf("\nfreeing\n");
        Bit2_free(&t);
        printf("freed\n");

        Bit2_free(&temp);

        return EXIT_SUCCESS;

}
