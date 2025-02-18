#include <math.h>

#include "type_shortage.h"

typedef f64 vec_slr_t;

#define USE_VEC(DIM) \
 \
typedef struct {  \
    vec_slr_t m_vector[DIM]; \
} vec##DIM ##_t; \
 \
vec##DIM ##_t vec##DIM ##_add(vec##DIM ##_t a, vec##DIM ##_t b); \
 \
vec##DIM ##_t vec##DIM ##_sub(vec##DIM ##_t a, vec##DIM ##_t b); \
 \
vec##DIM ##_t vec##DIM ##_mul(vec##DIM ##_t a, vec_slr_t b);  \
 \
vec##DIM ##_t vec##DIM ##_div(vec##DIM ##_t a, vec_slr_t b); \
 \
vec##DIM ##_t vec##DIM ##_norm(vec##DIM ##_t a); \
 \
void vec##DIM ##_addeq(vec##DIM ##_t* a, vec##DIM ##_t b); \
 \
void vec##DIM ##_subeq(vec##DIM ##_t* a, vec##DIM ##_t b); \
 \
void vec##DIM ##_muleq(vec##DIM ##_t* a, vec_slr_t b); \
 \
void vec##DIM ##_diveq(vec##DIM ##_t* a, vec_slr_t b); \
 \
void vec##DIM ##_normeq(vec##DIM ##_t* a); \
 \
vec_slr_t vec##DIM ##_dot(vec##DIM ##_t a, vec##DIM ##_t b); \
 \
vec_slr_t vec##DIM ##_len(vec##DIM ##_t a); \
 \
vec_slr_t vec##DIM ##_lensq(vec##DIM ##_t a); \
 \
vec_slr_t vec##DIM ##_dist(vec##DIM ##_t a, vec##DIM ##_t b); \
 \
 \
vec##DIM ##_t vec##DIM ##_add(vec##DIM ##_t a, vec##DIM ##_t b) { \
    vec##DIM ##_t c; \
 \
    for (ui32 i = 0; i < DIM; i++) { \
        c.m_vector[i] = a.m_vector[i] + b.m_vector[i]; \
    } \
 \
    return c; \
} \
 \
vec##DIM ##_t vec##DIM ##_sub(vec##DIM ##_t a, vec##DIM ##_t b) { \
    vec##DIM ##_t c; \
 \
    for (ui32 i = 0; i < DIM; i++) { \
        c.m_vector[i] = a.m_vector[i] - b.m_vector[i]; \
    } \
 \
    return c; \
} \
 \
vec##DIM ##_t vec##DIM ##_mul(vec##DIM ##_t a, vec_slr_t b) { \
    vec##DIM ##_t c; \
 \
    for (ui32 i = 0; i < DIM; i++) { \
        c.m_vector[i] = b * a.m_vector[i]; \
    } \
 \
    return c; \
} \
 \
vec##DIM ##_t vec##DIM ##_div(vec##DIM ##_t a, vec_slr_t b) { \
    vec##DIM ##_t c; \
 \
    for (ui32 i = 0; i < DIM; i++) { \
        c.m_vector[i] = a.m_vector[i] / b; \
    } \
 \
    return c; \
} \
 \
vec##DIM ##_t vec##DIM ##_norm(vec##DIM ##_t a) { \
    return vec##DIM ##_div(a, vec##DIM ##_len(a)); \
} \
 \
 \
void vec##DIM ##_addeq(vec##DIM ##_t* a, vec##DIM ##_t b) { \
    for (ui32 i = 0; i < DIM; i++) { \
        a->m_vector[i] += b.m_vector[i]; \
    } \
} \
 \
void vec##DIM ##_subeq(vec##DIM ##_t* a, vec##DIM ##_t b) { \
    for (ui32 i = 0; i < DIM; i++) { \
        a->m_vector[i] -= b.m_vector[i]; \
    } \
} \
 \
void vec##DIM ##_muleq(vec##DIM ##_t* a, vec_slr_t b) { \
    for (ui32 i = 0; i < DIM; i++) { \
        a->m_vector[i] *= b; \
    } \
} \
 \
void vec##DIM ##_diveq(vec##DIM ##_t* a, vec_slr_t b) { \
    for (ui32 i = 0; i < DIM; i++) { \
        a->m_vector[i] /= b; \
    } \
} \
 \
void vec##DIM ##_normeq(vec##DIM ##_t* a) { \
    vec##DIM ##_diveq(a, vec##DIM ##_len(*a)); \
} \
 \
vec_slr_t vec##DIM ##_dot(vec##DIM ##_t a, vec##DIM ##_t b) { \
    vec_slr_t c = 0; \
 \
    for (ui32 i = 0; i < DIM; i++) { \
        c += a.m_vector[i] * b.m_vector[i]; \
    } \
 \
    return c; \
} \
 \
 \
 \
vec_slr_t vec##DIM ##_lensq(vec##DIM ##_t a) { \
    vec_slr_t c = 0; \
 \
    for (ui32 i = 0; i < DIM; i++) { \
        c += a.m_vector[i] * a.m_vector[i];  \
    } \
 \
    return c; \
} \
 \
vec_slr_t vec##DIM ##_len(vec##DIM ##_t a) { \
    return sqrt(vec##DIM ##_lensq(a)); \
} \
 \
vec_slr_t vec##DIM ##_dist(vec##DIM ##_t a, vec##DIM ##_t b) { \
    return vec##DIM ##_len(vec##DIM ##_sub(a, b)); \
} \
 \

#ifdef VEC3
vec3_t vec3_cross(vec3_t a, vec3_t b) {
    vec3_t c;

    c.m_vector[0] = a.m_vector[1] * b.m_vector[2] - a.m_vector[2] * b.m_vector[1];
    c.m_vector[1] = a.m_vector[2] * b.m_vector[0] - a.m_vector[0] * b.m_vector[2];
    c.m_vector[2] = a.m_vector[0] * b.m_vector[1] - a.m_vector[1] * b.m_vector[0];

    return c;
}
#endif



/*vec##DIM ##_t vec##DIM ##_add(vec##DIM ##_t a, vec##DIM ##_t b) {
    vec##DIM ##_t c;

    for (ui32 i = 0; i < DIM; i++) {
        c.m_vector[i] = a.m_vector[i] + b.m_vector[i];
    }

    return c;
}

vec##DIM ##_t vec##DIM ##_sub(vec##DIM ##_t a, vec##DIM ##_t b) {
    vec##DIM ##_t c;

    for (ui32 i = 0; i < DIM; i++) {
        c.m_vector[i] = a.m_vector[i] - b.m_vector[i];
    }

    return c;
}

vec##DIM ##_t vec##DIM ##_mul(vec##DIM ##_t a, vec_slr_t b) {
    vec##DIM ##_t c;

    for (ui32 i = 0; i < DIM; i++) {
        c.m_vector[i] = b * a.m_vector[i];
    }

    return c;
}

vec##DIM ##_t vec##DIM ##_div(vec##DIM ##_t a, vec_slr_t b) {
    vec##DIM ##_t c;

    for (ui32 i = 0; i < DIM; i++) {
        c.m_vector[i] = a.m_vector[i] / b;
    }

    return c;
}



void vec##DIM ##_addeq(vec##DIM ##_t* a, vec##DIM ##_t b) {
    for (ui32 i = 0; i < DIM; i++) {
        a->m_vector[i] += b.m_vector[i];
    }
}

void vec##DIM ##_subeq(vec##DIM ##_t* a, vec##DIM ##_t b) {
    for (ui32 i = 0; i < DIM; i++) {
        a->m_vector[i] -= b.m_vector[i];
    }
}

void vec##DIM ##_muleq(vec##DIM ##_t* a, vec_slr_t b) {
    for (ui32 i = 0; i < DIM; i++) {
        a->m_vector[i] *= b;
    }
}

void vec##DIM ##_diveq(vec##DIM ##_t* a, vec_slr_t b) {
    for (ui32 i = 0; i < DIM; i++) {
        a->m_vector[i] /= b;
    }
}

vec_slr_t vec##DIM ##_dot(vec##DIM ##_t a, vec##DIM ##_t b) {
    vec_slr_t c = 0;

    for (ui32 i = 0; i < DIM; i++) {
        c += a.m_vector[i] * b.m_vector[i];
    }

    return c;
}



vec_slr_t vec##DIM ##_lensq(vec##DIM ##_t a) {
    vec_slr_t c;

    for (ui32 i = 0; i < DIM; i++) {
        c += a.m_vector[i] * a.m_vector[i]; 
    }

    return c;
}

vec_slr_t vec##DIM ##_len(vec##DIM ##_t a) {
    return sqrt(vec##DIM ##_lensq(a));
}

vec_slr_t vec##DIM ##_dist(vec##DIM ##_t a, vec##DIM ##_t b) {
    return vec##DIM ##_len(vec##DIM ##_sub(a, b));
}*/



