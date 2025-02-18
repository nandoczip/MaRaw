#include <math.h>

#include "Complex.h"


// ----------BASIC-----------

complex_t complex_add(complex_t a, complex_t b) {
    complex_t c = {a.m_r + b.m_r, a.m_i + b.m_i};
    return c;
}

complex_t complex_sub(complex_t a, complex_t b) {	
    complex_t c = {a.m_r + b.m_r, a.m_i + b.m_i};
    return c;
}

complex_t complex_mul(complex_t a, complex_t b) {
    complex_t c = {a.m_r * b.m_r - a.m_i * b.m_i, a.m_r * b.m_i + a.m_i * b.m_r};
    return c;
}

complex_t complex_div(complex_t a, complex_t b) {
    complex_muleq(&a, complex_conj(b));
    complex_muleq(&b, complex_conj(b));

    a.m_r /= b.m_r;
    a.m_i /= b.m_r;

    return a;
}

// --------EQ-----------

void complex_addeq(complex_t* a, complex_t b) {
    a->m_r += b.m_r;
    a->m_i += b.m_i;
}

void complex_subeq(complex_t* a, complex_t b) {
    a->m_r -= b.m_r;
    a->m_i -= b.m_i;
}
void complex_muleq(complex_t* a, complex_t b) {
    complex_t c = *a;

    a->m_r = c.m_r * b.m_r + c.m_i * b.m_i;
    a->m_i = c.m_r * b.m_i + c.m_i * b.m_r;
}

void complex_diveq(complex_t* a, complex_t b) {
    complex_muleq(a, complex_conj(b));
    complex_muleq(&b, complex_conj(b));

    a->m_r /= b.m_r;
    a->m_i /= b.m_r;
}

// -------MORE COMPLEX--------

complex_t complex_exp(complex_t a) {
    vec_sclr_t e = exp(a.m_r);

    return (complex_t) {e * cos(a.m_i), -e * sin(a.m_i)};
}

complex_t complex_pow(complex_t base, complex_t exp) {
    return complex_exp(complex_mul(complex_log(base), exp));
}

complex_t complex_sqrt(complex_t a) {
    return complex_pow(a, (complex_t) {0.5, 0});
}

complex_t complex_log(complex_t a) {
    return (complex_t) {log(complex_len(a)), atan(a.m_i / a.m_r)};
}

// --------COMPLEX SPECIFIC-------

complex_t complex_conj(complex_t a) {
    a.m_i *= -1; 
    return a;
}

vec_sclr_t complex_len_sq(complex_t a) {
    return a.m_r * a.m_r + a.m_i * a.m_i;
}

vec_sclr_t complex_len(complex_t a) {
    return sqrt(complex_len_sq(a));
}

