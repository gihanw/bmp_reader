#include <stdio.h>
#include "bmp_reader.h"

int main(int argc, char** argv)
{
        if (argv[1] == NULL)
        {
                printf ("usage: test [bitmap .bmp]\n");
                exit(EXIT_FAILURE);
        }
        bmpReader bmp(argv[1]);
        bmp.load();

        int row, col, c;

        for (row = 0; row < bmp.infohead.height; row++) {
                for (col = 0; col < bmp.infohead.width; col++) {
                        for (c = 0; c < bmp.colors; c++) {
                                printf ("bmp.pixel[%d][%d][%d]: %d\n", row, col, c, bmp.pixel[row][col][c]);
                        }
                }
        }

        exit(EXIT_SUCCESS);
}
