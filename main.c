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

void rotbmp24(int *img, int width);

int main(int argc, char* argv[]) {
    if(argc < 3) {
        printf("Error. Syntax: ./main [path_to_source] [path_to_target]\n");
        return -1;
    }

    FILE *fp;
    fp = fopen(argv[1], "r");

    struct BMPHeader bmph;

    fread(&bmph, sizeof(struct BMPHeader), 1, fp);

    int* data = (int*)malloc(4*bmph.width_px*bmph.height_px*sizeof(int));

    for(int i = 0; i < bmph.width_px*bmph.height_px; ++i)
        fread(&data[i], sizeof(int), 1, fp);

    fclose(fp);


    rotbmp24(data, bmph.width_px);
    

    FILE *target;
    target = fopen(argv[2], "w");

    fwrite(&bmph, sizeof(struct BMPHeader), 1, target);

    for(int i = 0; i < bmph.width_px*bmph.height_px*3; ++i)
        fwrite(&data[i], sizeof(int), 1, target);

    fclose(target);

    free(data);

    printf("Done.\n");

    return 0;
}
