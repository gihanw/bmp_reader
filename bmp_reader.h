#ifndef BMP_H
#define BMP_H

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <inttypes.h>
#include <sys/types.h>
#include <unistd.h>

struct bmpfile_magic {
	unsigned char magic[2];
};

struct bmpfile_header {
	uint32_t filesz;
	uint16_t creator1;
	uint16_t creator2;
	uint32_t bmp_offset;
};

typedef struct {
	uint32_t header_sz;
	int32_t width;
	int32_t height;
	uint16_t nplanes;
	uint16_t bitspp;
	uint32_t compress_type;
	uint32_t bmp_bytesz;
	int32_t hres;
	int32_t vres;
	uint32_t ncolors;
	uint32_t nimpcolors;
} BITMAPINFOHEADER;

class bmpReader {
        public:
                bmpReader();
                bmpReader(char *file);
                ~bmpReader();
                void load();
                char *filename;
                struct bmpfile_magic magic;
                struct bmpfile_header head;
                BITMAPINFOHEADER infohead;
                int ***pixel;
                int colors;
};

#endif
