#include <stdio.h>
#include <string.h>

#include "png.h"
#include "type_shortage.h"

#ifndef VEC2
#define VEC2 1
USE_VEC(2)
#endif


#define USE_BUFFER(DIM) \
 \
typedef struct { \
    ui32 m_w, m_h; \
    vec##DIM ##_t* m_buffer; \
} buffer##DIM ##_t; \
 \
 \
void buffer##DIM ##_f_to_i(buffer##DIM ##_t* this, void* buffer, ui8 bits) { \
    ui8* b = (ui8*) buffer; \
    vec_sclr_t* vec = (vec_sclr_t*) this->m_buffer; \
 \
    for (ui32 i = 0; i < this->m_w * this->m_h * DIM; i++) { \
        if (vec[i] >= 1.0) { \
            b[i] = ~0; \
        } \
        else if (vec[i] <= 0.0) { \
            b[i] = 0; \
        } \
        else { \
            b[i] = vec[i] * ((vec_sclr_t) ((ui8) (~0))); \
        } \
    } \
} \
 \
i8 buffer##DIM ##_resize(buffer##DIM ##_t* this, ui32 w, ui32 h) { \
    vec##DIM ##_t* new_ptr = (vec##DIM ##_t*) malloc(w * h * sizeof(vec##DIM ##_t) * DIM); \
 \
    if (new_ptr == NULL) { \
        printf("Mem allocation failed"); \
        return -1; \
    } \
 \
    if (this->m_buffer != NULL) { \
        free(this->m_buffer); \
    } \
     \
    this->m_w = w; \
    this->m_h = h; \
 \
    this->m_buffer = new_ptr; \
 \
    return 0; \
} \
 \
void buffer##DIM ##_init(buffer##DIM ##_t* this) { \
    this->m_buffer = NULL; \
} \
 \
i8 buffer##DIM ##_save_png(buffer##DIM ##_t* this, const char* path, ui8 bits_per_chanel) { \
    FILE* fp = fopen(path, "wb"); \
    if(!fp) abort(); \
 \
    png_structp png = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL); \
    if (!png) abort(); \
 \
    png_infop info = png_create_info_struct(png); \
    if (!info) abort(); \
 \
    if (setjmp(png_jmpbuf(png))) abort(); \
 \
    png_init_io(png, fp); \
 \
    png_set_IHDR( \
        png, \
        info, \
        this->m_w, this->m_h, \
        bits_per_chanel, \
        PNG_COLOR_MASK_COLOR | (DIM == 4) * 0b100, \
        PNG_INTERLACE_NONE, \
        PNG_COMPRESSION_TYPE_BASE, \
        PNG_FILTER_TYPE_DEFAULT \
    ); \
    png_write_info(png, info); \
 \
     \
    void* buffer = malloc(bits_per_chanel * DIM * this->m_w * this->m_h / 8); \
 \
    buffer##DIM ##_f_to_i(this, buffer, 8); \
 \
    void** b = (void**) malloc(sizeof(*b) * this->m_h); \
 \
    { \
        int i; \
        void* p; \
 \
        for (i = 0, p = buffer; i < this->m_h; i++, p += this->m_w * DIM * bits_per_chanel / 8) { \
            b[i] = p; \
        } \
    } \
 \
    png_write_image(png, (ui8**) b); \
 \
    png_write_end(png, NULL); \
 \
    fclose(fp); \
 \
    png_destroy_write_struct(&png, &info); \
     \
    free(b); \
    free(buffer); \
 \
    printf("Saved '%s'.\n", path); \
 \
    return 0; \
} \
 \
i8 buffer##DIM ##_save_png_frame(buffer##DIM ##_t* this, const char* folder, ui32 frame, ui8 bits_per_chanel) { \
    ui32 len_0 = strlen(folder); \
    ui32 len_1; \
 \
    if (frame == 0) { \
        len_1 = 1; \
    } \
    else { \
        len_1 = log10(frame) + 1; \
    } \
     \
    char ft[] = ".png"; \
    char* new = (char*) malloc(len_0 + len_1 + 2 + strlen(ft)); \
 \
    strcpy(new, folder); \
    strcpy(&(new[len_0 + len_1 + 1]), ft); \
    new[len_0] = '/'; \
    new[len_0 + len_1 + 1 + strlen(ft)] = 0; \
     \
    for (ui32 i = 0; i < len_1; i++) { \
        ui32 b = pow(10, len_1 - i - 1); \
        new[len_0 + 1 + i] = 48 + ((ui32) (frame / b)); \
        frame %= b; \
    } \
 \
    buffer##DIM ##_save_png(this, new, bits_per_chanel);  \
 \
    free(new); \
} \
 \
i8 buffer##DIM ##_save_raw(buffer##DIM ##_t* this, const char* path) { \
    FILE* f = fopen(path, "wb"); \
     \
    ui8 dim = DIM; \
    ui8 bytes = sizeof(this->m_buffer[0]) / DIM; \
     \
    fwrite("RAW", 1, 4, f); \
    fwrite(&dim, 1, sizeof(dim), f); \
    fwrite(&bytes, 1, sizeof(bytes), f); \
     \
    fwrite(&this->m_w, 1, sizeof(this->m_w), f); \
    fwrite(&this->m_h, 1, sizeof(this->m_h), f); \
 \
    fwrite(this->m_buffer, 1, sizeof(this->m_buffer[0]) * this->m_w * this->m_h, f); \
 \
    fclose(f); \
 \
    printf("Saved '%s'.\n", path); \
 \
    return 1; \
} \
 \
i8 buffer##DIM ##_load_raw(buffer##DIM ##_t* this, const char* path) { \
    FILE* f = fopen(path, "rb"); \
     \
    char s[4]; \
    ui8 dim, bytes; \
 \
    fread(s, 1, sizeof(s), f); \
    fread(&dim, 1, sizeof(dim), f); \
    fread(&bytes, 1, sizeof(bytes), f); \
 \
    if (strcmp(s, "RAW")) { \
        fprintf(stderr, "Control string at position 0 is '%s' (not '%s').\n", s, "RAW"); \
        return 1; \
    } \
    if (dim != DIM) { \
        fprintf(stderr, "Value at position 0 is '%u' (not '%u').\n", dim, DIM); \
        return 1; \
    } \
    if (bytes != sizeof(this->m_buffer[0]) / DIM) { \
        fprintf(stderr, "Value at position 0 is '%u' (not '%lu').\n", bytes, sizeof(this->m_buffer[0]) / DIM); \
        return 1; \
    } \
 \
    fread(&this->m_w, 1, sizeof(this->m_w), f); \
    fread(&this->m_h, 1, sizeof(this->m_h), f); \
     \
    buffer##DIM ##_resize(this, this->m_w, this->m_h); \
 \
    fread(this->m_buffer, 1, sizeof(this->m_buffer[0]) * this->m_w * this->m_h, f); \
     \
    fclose(f); \
 \
    printf("Loaded '%s'.\n", path); \
 \
    return 0; \
} \
 \

