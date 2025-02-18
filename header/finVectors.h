#include <math.h>

#include "type_shortage.h"

typedef f64 vec_slr_t;

#ifndef VEC + N
#define VEC + N

typedef 
struct Vec3 { 
    vec_slr_t m_vector[3];
} vec3_t;

vec3_t vec3_add(vec3_t a, vec3_t b);

vec3_t vec3_sub(vec3_t a, vec3_t b);

vec3_t vec3_mul(vec3_t a, vec_slr_t b); 

vec3_t vec3_div(vec3_t a, vec_slr_t b);


// a += b;

void vec3_addeq(vec3_t* a, vec3_t b);

void vec3_subeq(vec3_t* a, vec3_t b);

void vec3_muleq(vec3_t* a, vec_slr_t b);

void vec3_diveq(vec3_t* a, vec_slr_t b);


vec_slr_t vec3_dot(vec3_t a, vec3_t b);

vec3_t vec3_cross(vec3_t a, vec3_t b);

vec_slr_t vec3_len(vec3_t a);

vec_slr_t vec3_lensq(vec3_t a);

vec_slr_t vec3_dist(vec3_t a, vec3_t b);

#endif


#ifndef VEC4
#define VEC4

typedef  
struct Vec4 {
    vec_slr_t m_vector[4];
} vec4_t;

vec4_t vec4_add(vec4_t a, vec4_t b);

vec4_t vec4_sub(vec4_t a, vec4_t b);

vec4_t vec4_mul(vec4_t a, vec_slr_t b); 

vec4_t vec4_div(vec4_t a, vec_slr_t b);


// a += b;

void vec4_addeq(vec4_t* a, vec4_t b);

void vec4_subeq(vec4_t* a, vec4_t b);

void vec4_muleq(vec4_t* a, vec_slr_t b);

void vec4_diveq(vec4_t* a, vec_slr_t b);


vec_slr_t vec4_dot(vec4_t a, vec4_t b);

vec_slr_t vec4_len(vec4_t a);

vec_slr_t vec4_lensq(vec4_t a);

vec_slr_t vec4_dist(vec4_t a, vec4_t b);

#endif
