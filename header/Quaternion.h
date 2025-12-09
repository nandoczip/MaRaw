#ifndef QUATERNION_H
#define QUATERNION_H 1

#define Q_DIM 4


#include <stdio.h>

#include "type_shortage.h"


typedef double vec_sclr_t;

typedef struct {
	vec_sclr_t e[4];
} quaternion_t;

quaternion_t quaternion_add(quaternion_t a, quaternion_t b);
quaternion_t quaternion_sub(quaternion_t a, quaternion_t b);	
quaternion_t quaternion_mul(quaternion_t a, quaternion_t b);
quaternion_t quaternion_div(quaternion_t a, quaternion_t b);

void quaternion_addeq(quaternion_t* a, quaternion_t b);
void quaternion_subeq(quaternion_t* a, quaternion_t b);	
void quaternion_muleq(quaternion_t* a, quaternion_t b);
void quaternion_diveq(quaternion_t* a, quaternion_t b);

quaternion_t quaternion_exp(quaternion_t a);
quaternion_t quaternion_qpow(quaternion_t base, quaternion_t exp);
quaternion_t quaternion_upow(quaternion_t base, ui32 exp);
quaternion_t quaternion_sqrt(quaternion_t a);
quaternion_t quaternion_log(quaternion_t a);

quaternion_t quaternion_conj(quaternion_t);

vec_sclr_t quaternion_lensq(quaternion_t a);
vec_sclr_t quaternion_len(quaternion_t a);

ui8 quaternion_eq(quaternion_t, quaternion_t);

void quaternion_print(quaternion_t a);

#endif
