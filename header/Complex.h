#ifndef COMPLEX
#define COMPLEX 1

#include <stdio.h>

#include "type_shortage.h"


typedef double vec_sclr_t;

typedef struct {
	vec_sclr_t m_r, m_i;
} complex_t;


complex_t complex_add(complex_t a, complex_t b);
complex_t complex_sub(complex_t a, complex_t b);	
complex_t complex_mul(complex_t a, complex_t b);
complex_t complex_div(complex_t a, complex_t b);

void complex_addeq(complex_t* a, complex_t b);
void complex_subeq(complex_t* a, complex_t b);	
void complex_muleq(complex_t* a, complex_t b);
void complex_diveq(complex_t* a, complex_t b);

complex_t complex_exp(complex_t a);
complex_t complex_cpow(complex_t base, complex_t exp);
complex_t complex_fpow(complex_t base, vec_sclr_t exp);
complex_t complex_upow(complex_t base, ui32 exp);
complex_t complex_sqrt(complex_t a);
complex_t complex_log(complex_t a);

complex_t complex_conj(complex_t);

vec_sclr_t complex_lensq(complex_t a);
vec_sclr_t complex_len(complex_t a);

void complex_print(complex_t a);

#endif
