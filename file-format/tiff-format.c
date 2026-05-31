/*
This code just on purpose for parse TIFF file format.
The code has bugs and not safe.

TIFF version 6.0

---Hailing Fang
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <string.h>

int
main(int argc, char *argv[])
{
    char *fname = argv[1];
    FILE *fin = fopen(fname, "rb");

    if (!fin)
        exit(1);

    char endian[3];
    if (fread(endian, sizeof(char), 2, fin) == 2) {
        endian[2] = '\0';
        printf("%s\n", endian);
    }

    uint16_t anum;
    if (fread(&anum, sizeof(uint16_t), 1, fin) == 1) {
        printf("%u\n", anum);
    }

    uint32_t offset;
    if (fread(&offset, sizeof(uint32_t), 1, fin) == 1);
    printf("%u\n", offset);

    //IFD
    fseek(fin, offset, SEEK_SET);

    uint16_t tag_num;
    if (fread(&tag_num, sizeof(uint16_t), 1, fin) == 1) {
        printf("%u\n", tag_num);
    }

    char tag_buf[12];
    struct Tag {
        uint32_t ImageWidth; //256
        uint32_t ImageLength; //257
        uint16_t BitsPerSample[3]; //258
        uint16_t Compression; //259
        uint16_t PhotometricInterpretation; //262
        uint32_t StripOffsets[32]; //273, here should be a list.
        uint16_t StripOffsets_n;
        uint16_t SamplesPerPixel; //274
        uint16_t RowsPerStrip; //278
        uint16_t StripByteCounts[32]; //279, here should be a list.
        uint16_t StripByteCounts_n;
        uint32_t XResolution[2]; //282
        uint32_t YResolution[2]; //283
        uint16_t PlanarConfiguration; //284
        char PageName[64]; //285
        uint16_t ResolutionUnit; //296
        uint16_t SampleFormat[3]; //339
    };

    struct Tag tag_dt;
    for (int i = 0; i < tag_num; i++) {
        if (fread(tag_buf, sizeof(char), 12, fin) == 12) {
            uint16_t tag_id = ((uint16_t *)tag_buf)[0];
            uint16_t data_type = ((uint16_t *)tag_buf)[1];
            uint32_t data_num = ((uint32_t *)tag_buf)[1];
            uint32_t * valueoffset_p = (uint32_t *)tag_buf + 2;
            printf("%u %u %u %u\n", tag_id, data_type, data_num, *valueoffset_p);
            if (tag_id == 256) {
                tag_dt.ImageWidth = *valueoffset_p;
            }

            if (tag_id == 257) {
                tag_dt.ImageLength = *valueoffset_p;
            }

            if (tag_id == 258) {
                assert(data_type == 3);
                assert(data_num == 3);
                fpos_t fcp;
                fgetpos(fin, &fcp);
                fseek(fin, *valueoffset_p, SEEK_SET);
                printf("BitsPerSample seek %u\n", ftell(fin));
                fread(tag_dt.BitsPerSample, sizeof(uint16_t), 3, fin);
                fsetpos(fin, &fcp);
            }

            if (tag_id == 259) {
                tag_dt.Compression = (uint16_t)(*valueoffset_p);
            }

            if (tag_id == 262) {
                tag_dt.PhotometricInterpretation = (uint16_t)(*valueoffset_p);
            }

            if (tag_id == 273) {
                tag_dt.StripOffsets_n = data_num;
                if (data_num > 1) {
                    fpos_t fcp;
                    fgetpos(fin, &fcp);
                    fseek(fin, *valueoffset_p, SEEK_SET);
                    printf("StripOffsets seek %u\n", ftell(fin));
                    fread(tag_dt.StripOffsets, sizeof(uint32_t), data_num, fin);
                    fsetpos(fin, &fcp);
                } else {
                    tag_dt.StripOffsets[0] = *valueoffset_p;
                }
            }

            if (tag_id == 274) {
                tag_dt.SamplesPerPixel = (uint16_t)*valueoffset_p;
            }
        
            if (tag_id == 278) {
                tag_dt.RowsPerStrip = *valueoffset_p;
            }
            
            if (tag_id == 279) {
                tag_dt.StripByteCounts_n = data_num;
                if (data_num > 2) {
                    fpos_t fcp;
                    fgetpos(fin, &fcp);
                    fseek(fin, *valueoffset_p, SEEK_SET);
                    printf("StripByteCounts seek %u\n", ftell(fin));
                    fread(tag_dt.StripByteCounts, sizeof(uint16_t), data_num, fin);
                    fsetpos(fin, &fcp);
                }  else {
                    memcpy(valueoffset_p, tag_dt.StripByteCounts, 2);
                }
            }
        
        }
    }

    printf("ImageWidth %u\n", tag_dt.ImageWidth);
    printf("ImageLength %u\n", tag_dt.ImageLength);
    printf("BitsPerSample %u %u %u\n", tag_dt.BitsPerSample[0], tag_dt.BitsPerSample[1], tag_dt.BitsPerSample[2]);
    printf("Compression %u\n", tag_dt.Compression);
    printf("PhotometricInterpretation %u\n", tag_dt.PhotometricInterpretation);
    printf("StripOffsets ");
    for (int i = 0; i < tag_dt.StripOffsets_n; i++) {
        printf("%u ", tag_dt.StripOffsets[i]);
    }
    printf("\n");
    printf("SamplesPerPixel %u\n", tag_dt.SamplesPerPixel);
    printf("RowsPerStrip %u\n", tag_dt.RowsPerStrip);
    printf("StripByteCounts ");
    for (int i = 0; i < tag_dt.StripByteCounts_n; i++) {
        printf("%u ", tag_dt.StripByteCounts[i]);
    }
    printf("\n");

    uint8_t (*img)[tag_dt.ImageWidth * 3] = malloc(tag_dt.ImageWidth * tag_dt.ImageLength * 3);
    void *strip_buf = malloc(tag_dt.RowsPerStrip * tag_dt.ImageWidth * 3);

    int row_n = 0;
    for (int i = 0; i < tag_dt.StripOffsets_n; i++) {
        printf("seek stripoffset %u\n", tag_dt.StripOffsets[i]);
        fseek(fin, tag_dt.StripOffsets[i], SEEK_SET);

        printf("read bytes: %u\n", tag_dt.StripByteCounts[i]);
        fread(strip_buf, sizeof(char), tag_dt.StripByteCounts[i], fin);
        
        memcpy(img[row_n], strip_buf, tag_dt.StripByteCounts[i]);
        row_n += tag_dt.RowsPerStrip;
    }

    FILE *fout = fopen("imgdt.tsv", "w");
    for (int i = 0; i < tag_dt.ImageLength; i++) {
        int j = 0;
        for (; j < tag_dt.ImageWidth - 1; j++) {
            fprintf(fout, "%u,%u,%u\t", img[i][3 * j + 0], img[i][3 * j + 1], img[i][3 * j + 2]);
        }
        fprintf(fout, "%u,%u,%u\n", img[i][3 * j + 0], img[i][3 * j + 1], img[i][3 * j + 2]);
    }

    fclose(fout);
    free(strip_buf);
    free(img);
    fclose(fin);
    return 0;
}