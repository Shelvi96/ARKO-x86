#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#pragma pack(push, 1)
struct  BMPHeader {
    uint16_t type;              // Magic identifier: 0x4d42
    uint32_t size;              // File size in bytes
    uint16_t reserved1;         // Not used
    uint16_t reserved2;         // Not used
    uint32_t offset;            // Offset to image data in bytes from beginning of file
    uint32_t dib_header_size;   // DIB Header size in bytes
    int32_t  width_px;          // Width of the image
    int32_t  height_px;         // Height of image
    uint16_t num_planes;        // Number of color planes
    uint16_t bits_per_pixel;    // Bits per pixel
    uint32_t compression;       // Compression type
    uint32_t image_size_bytes;  // Image size in bytes
    int32_t  x_resolution_ppm;  // Pixels per meter
    int32_t  y_resolution_ppm;  // Pixels per meter
    uint32_t num_colors;        // Number of colors
    uint32_t important_colors;  // Important colors // total 54 bits
};
#pragma pack(pop)

void rotbmp24(void *img, int width);

int main(int argc, char* argv[]) {
    if(argc < 3) {
        printf("Error. Syntax: ./main [path_to_source] [path_to_target]\n");
        return -1;
    }

    FILE *fp;
    fp = fopen(argv[1], "r");

    struct BMPHeader bmph;

    fread(&bmph, sizeof(struct BMPHeader), 1, fp);
// #define char int
    // int *datar, *datag, *datab;
    // datar = (int*)malloc(bmph.width_px*bmph.height_px*sizeof(int));
    // datag = (int*)malloc(bmph.width_px*bmph.height_px*sizeof(int));
    // datab = (int*)malloc(bmph.width_px*bmph.height_px*sizeof(int));
    char* data = (char*)malloc(3*bmph.width_px*bmph.height_px*sizeof(char));

    // for(int i = 0; i < bmph.width_px*bmph.height_px; ++i) {
    //     datar[i] = fgetc(fp);
    //     datag[i] = fgetc(fp);
    //     datab[i] = fgetc(fp);
    // }

    for(int i = 0; i < 3*bmph.width_px*bmph.height_px; ++i) {
        data[i] = fgetc(fp);
        printf("%d\n", data[i]);
    }

    fclose(fp);

    /* funkcjaaa */
    rotbmp24(data, bmph.width_px);

/*    for(int i = 0; i < bmph.width_px*bmph.height_px; ++i) {
        int x = i%bmph.width_px;
        int y = i/bmph.width_px;

        if (x < y) {
            int coord = y*bmph.width_px + x;
            int new_coord = x*bmph.width_px + y;

            int r = datar[coord];
            int g = datag[coord];
            int b = datab[coord];

            datar[coord] = datar[new_coord];
            datag[coord] = datag[new_coord];
            datab[coord] = datab[new_coord];

            datar[new_coord] = r;
            datag[new_coord] = g;
            datab[new_coord] = b;
        }
    }

    for(int i = 0; i < bmph.width_px*bmph.height_px; ++i) {
        int x = i%bmph.width_px;
        int y = i/bmph.width_px;

        if (y < bmph.width_px/2) {
            int coord = y*bmph.width_px + x;
            y = bmph.width_px - y;
            int new_coord = y*bmph.width_px + x;

            int r = datar[coord];
            int g = datag[coord];
            int b = datab[coord];

            datar[coord] = datar[new_coord];
            datag[coord] = datag[new_coord];
            datab[coord] = datab[new_coord];

            datar[new_coord] = r;
            datag[new_coord] = g;
            datab[new_coord] = b;
        }
    }
*/
    /* koniec funkcjiiii */

    FILE *target;
    target = fopen(argv[2], "w");

    fwrite(&bmph, sizeof(struct BMPHeader), 1, target);

    // for(int i = 0; i < bmph.width_px*bmph.height_px; ++i) {
    //     fputc(datar[i], target);
    //     fputc(datag[i], target);
    //     fputc(datab[i], target);
    // }

    for(int i = 0; i < 3*bmph.width_px*bmph.height_px; ++i) {
        fputc(data[i], target);
    }

    fclose(target);

    // free(datar);
    // free(datag);
    // free(datab);

    free(data);

    printf("Done.\n");

    return 0;
}
