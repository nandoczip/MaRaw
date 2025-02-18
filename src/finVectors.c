#include "Vectors.h"


vec3_t vec3_add(vec3_t a, vec3_t b) {
    vec3_t c;

    for (ui32 i = 0; i < 3; i++) {
        c.m_vector[i] = a.m_vector[i] + b.m_vector[i];
    }

    return c;
}

vec3_t vec3_sub(vec3_t a, vec3_t b) {
    vec3_t c;

    for (ui32 i = 0; i < 3; i++) {
        c.m_vector[i] = a.m_vector[i] - b.m_vector[i];
    }

    return c;
}

vec3_t vec3_mul(vec3_t a, vec_slr_t b) {
    vec3_t c;

    for (ui32 i = 0; i < 3; i++) {
        c.m_vector[i] = b * a.m_vector[i];
    }

    return c;
}

vec3_t vec3_div(vec3_t a, vec_slr_t b) {
    vec3_t c;

    for (ui32 i = 0; i < 3; i++) {
        c.m_vector[i] = a.m_vector[i] / b;
    }

    return c;
}


// a += b;

void vec3_addeq(vec3_t* a, vec3_t b) {
    for (ui32 i = 0; i < 3; i++) {
        a->m_vector[i] += b.m_vector[i];
    }
}

void vec3_subeq(vec3_t* a, vec3_t b) {
    for (ui32 i = 0; i < 3; i++) {
        a->m_vector[i] -= b.m_vector[i];
    }
}

void vec3_muleq(vec3_t* a, vec_slr_t b) {
    for (ui32 i = 0; i < 3; i++) {
        a->m_vector[i] *= b;
    }
}

void vec3_diveq(vec3_t* a, vec_slr_t b) {
    for (ui32 i = 0; i < 3; i++) {
        a->m_vector[i] /= b;
    }
}

vec_slr_t vec3_dot(vec3_t a, vec3_t b) {
    vec_slr_t c = 0;

    for (ui32 i = 0; i < 3; i++) {
        c += a.m_vector[i] * b.m_vector[i];
    }

    return c;
}

vec3_t vec3_cross(vec3_t a, vec3_t b) {
    vec3_t c;

    c.m_vector[0] = a.m_vector[1] * b.m_vector[2] - a.m_vector[2] * b.m_vector[1];
    c.m_vector[1] = a.m_vector[2] * b.m_vector[0] - a.m_vector[0] * b.m_vector[2];
    c.m_vector[2] = a.m_vector[0] * b.m_vector[1] - a.m_vector[1] * b.m_vector[0];

    return c;
}

// latex
// lensq = \sum_{i=0}^{N} a_i^2
// len = \sqrt{lensq}

vec_slr_t vec3_lensq(vec3_t a) {
    vec_slr_t c;

    for (ui32 i = 0; i < 3; i++) {
        c += a.m_vector[i] * a.m_vector[i]; 
    }

    return c;
}

vec_slr_t vec3_len(vec3_t a) {
    return sqrt(vec3_lensq(a));
}

vec_slr_t vec3_dist(vec3_t a, vec3_t b) {
    return vec3_len(vec3_sub(a, b));
}

/*-----------------VEC4--------------------------*/

vec4_t vec4_add(vec4_t a, vec4_t b) {
    vec4_t c;

    for (ui32 i = 0; i < 4; i++) {
        c.m_vector[i] = a.m_vector[i] + b.m_vector[i];
    }

    return c;
}

vec4_t vec4_sub(vec4_t a, vec4_t b) {
    vec4_t c;

    for (ui32 i = 0; i < 4; i++) {
        c.m_vector[i] = a.m_vector[i] - b.m_vector[i];
    }

    return c;
}

vec4_t vec4_mul(vec4_t a, vec_slr_t b) {
    vec4_t c;

    for (ui32 i = 0; i < 4; i++) {
        c.m_vector[i] = b * a.m_vector[i];
    }

    return c;
}

vec4_t vec4_div(vec4_t a, vec_slr_t b) {
    vec4_t c;

    for (ui32 i = 0; i < 4; i++) {
        c.m_vector[i] = a.m_vector[i] / b;
    }

    return c;
}


// a += b;

void vec4_addeq(vec4_t* a, vec4_t b) {
    for (ui32 i = 0; i < 4; i++) {
        a->m_vector[i] += b.m_vector[i];
    }
}

void vec4_subeq(vec4_t* a, vec4_t b) {
    for (ui32 i = 0; i < 4; i++) {
        a->m_vector[i] -= b.m_vector[i];
    }
}

void vec4_muleq(vec4_t* a, vec_slr_t b) {
    for (ui32 i = 0; i < 4; i++) {
        a->m_vector[i] *= b;
    }
}

void vec4_diveq(vec4_t* a, vec_slr_t b) {
    for (ui32 i = 0; i < 4; i++) {
        a->m_vector[i] /= b;
    }
}

vec_slr_t vec4_dot(vec4_t a, vec4_t b) {
    vec_slr_t c = 0;

    for (ui32 i = 0; i < 4; i++) {
        c += a.m_vector[i] * b.m_vector[i];
    }

    return c;
}


// latex
// lensq = \sum_{i=0}^{N} a_i^2
// len = \sqrt{lensq}

vec_slr_t vec4_lensq(vec4_t a) {
    vec_slr_t c;

    for (ui32 i = 0; i < 4; i++) {
        c += a.m_vector[i] * a.m_vector[i]; 
    }

    return c;
}

vec_slr_t vec4_len(vec4_t a) {
    return sqrt(vec4_lensq(a));
}

vec_slr_t vec4_dist(vec4_t a, vec4_t b) {
    return vec4_len(vec4_sub(a, b));
}

