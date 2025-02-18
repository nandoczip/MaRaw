#include "Vectors.h"
#include "type_shortage.h"

typedef f64 vec_sclr_t;

#define USE_CAM(DIM) \
 \
typedef struct { \
    ui32 m_w, m_h; \
    vec##DIM ##_t m_x, m_n, m_ray;   \
    vec_sclr_t m_fstop; \
} cam##DIM ##_t; \
 \
void cam##DIM ##_calc_ray(cam##DIM ##_t* this, ui32 x, ui32 y) { \
    this->m_ray = (vec##DIM ##_t) { \
        this->m_fstop, \
        (2.0f * x / this->m_w - 1) * (1 - 0.036), \
        ((2.0f * y - this->m_h) / this->m_w) * (1 - 0.036) \
    }; \
} \
 \

