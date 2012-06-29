#include "bmp_reader.h"

bmpReader::bmpReader()
{

}

bmpReader::bmpReader(char *file)
{
        filename = file;
}

bmpReader::~bmpReader()
{
        free(pixel);
}

void bmpReader::load()
{
        int fd;
        if (filename == NULL) {
                exit(-1);
        }
        fd = open(filename, O_RDONLY);

        ssize_t n;
        int val;

        // grabbing the header
        // magic numbers
        if (lseek(fd, 0, SEEK_SET) != -1)
                n = read(fd, &val, 1);
        magic.magic[0] = val;

        if (lseek(fd, 0, SEEK_CUR) != -1)
                n = read(fd, &val, 1);
        magic.magic[1] = val;

        // file size
        if (lseek(fd, 0, SEEK_CUR) != -1)
                n = read(fd, &val, 4);
        head.filesz = val;

        // creator 1
        if (lseek(fd, 0, SEEK_CUR) != -1)
                n = read(fd, &val, 2);
        head.creator1 = val;

        // creator 2
        if (lseek(fd, 0, SEEK_CUR) != -1)
                n = read(fd, &val, 2);
        head.creator2 = val;

        // bitmap offset
        if (lseek(fd, 0, SEEK_CUR) != -1)
                n = read(fd, &val, 4);
        head.bmp_offset = val;

        // header size
        if (lseek(fd, 0, SEEK_CUR) != -1)
                n = read(fd, &val, 4);
        infohead.header_sz = val;

        // width
        if (lseek(fd, 0, SEEK_CUR) != -1)
                n = read(fd, &val, 4);
        infohead.width = val;

        // height
        if (lseek(fd, 0, SEEK_CUR) != -1)
                n = read(fd, &val, 4);
        infohead.height = val;

        // planes
        if (lseek(fd, 0, SEEK_CUR) != -1)
                n = read(fd, &val, 2);
        infohead.nplanes = val;

        // bits per pixel
        if (lseek(fd, 0, SEEK_CUR) != -1)
                n = read(fd, &val, 2);
        infohead.bitspp = val;

        // compression type
        if (lseek(fd, 0, SEEK_CUR) != -1)
                n = read(fd, &val, 4);
        infohead.compress_type = val;

        // size of raw data including padding
        if (lseek(fd, 0, SEEK_CUR) != -1)
                n = read(fd, &val, 4);
        infohead.bmp_bytesz = val;

        // horizontal resolution
        if (lseek(fd, 0, SEEK_CUR) != -1)
                n = read(fd, &val, 4);
        infohead.hres = val;

        // vertical resolution
        if (lseek(fd, 0, SEEK_CUR) != -1)
                n = read(fd, &val, 4);
        infohead.vres = val;

        // number of colors on the palette
        if (lseek(fd, 0, SEEK_CUR) != -1)
                n = read(fd, &val, 4);
        infohead.ncolors = val;

        // important colors
        if (lseek(fd, 0, SEEK_CUR) != -1)
                n = read(fd, &val, 4);
        infohead.nimpcolors = val;

        pixel = (int ***)malloc(infohead.height * sizeof(int *));

        int row, col, c;
        // bits per pixel
        if (infohead.bitspp == 24) colors = 3;
        else colors = 4;

        // padding size
        int padding;
        padding = (infohead.bmp_bytesz - infohead.height*infohead.width*colors)/infohead.height;

        for (row = 0; row < infohead.height; row++) {
                pixel[row] = (int** )malloc(infohead.width * sizeof(int *));
        }

        for (row = 0; row < infohead.height; row++) {
                for (col = 0; col < infohead.width; col++) {
                        pixel[row][col] = (int* )malloc(colors * sizeof(int *));
                }
        }

        // reading data
        off_t pos = lseek(fd, head.bmp_offset, SEEK_SET);

        for (row = infohead.height-1; row >= 0; row--) {
                for (col = 0; col < infohead.width; col++) {
                        for (c = 0; c < colors; c++) {
                                if (lseek(fd, 0, SEEK_CUR) != -1)
                                        n = read(fd, &val, 1);
                                pixel[row][col][c] = val;
                        }
                }
                if (lseek(fd, 0, SEEK_CUR) != -1)
                        n = read(fd, &val, padding);
        }

}
