#include <math.h>

#include "Complex.h"


// ----------BASIC-----------

quaternion_t quaternion_add(quaternion_t a, quaternion_t b) {
    return (quaternion_t) {a.m_r + b.m_r, a.m_i + b.m_i, a.m_j + b.m_j, a.m_k + b.m_k};
}

quaternion_t quaternion_sub(quaternion_t a, quaternion_t b) {	
    return (quaternion_t) {a.m_r - b.m_r, a.m_i - b.m_i, a.m_j - b.m_j, a.m_k - b.m_k};
}

quaternion_t quaternion_mul(quaternion_t a, quaternion_t b) {
    return (quaternion_t) {
        a.m_r * b.m_r - a.m_i * b.m_i - a.m_j * b.m_j - a.m_k * b.m_k, 
        a.m_r * b.m_i + a.m_i * b.m_r + a.m_j * b.m_k - a.m_k * b.m_j,
        a.m_r * b.m_j - a.m_i * b.m_k + a.m_j * b.m_r + a.m_k * b.m_i,
        a.m_r * b.m_k + a.m_i * b.m_j - a.m_j * b.m_i + a.m_k * b.m_r
    };
}

quaternion_t quaternion_div(quaternion_t a, quaternion_t b) {
    quaternion_muleq(&a, quaternion_conj(b));
    quaternion_muleq(&b, quaternion_conj(b));

    a.m_r /= b.m_r;
    a.m_i /= b.m_r;

    return a;
}

// --------EQ-----------

void quaternion_addeq(quaternion_t* a, quaternion_t b) {
    a->m_r += b.m_r;
    a->m_i += b.m_i;
    a->m_j += b.m_j;
    a->m_k += b.m_k;
}

void quaternion_subeq(quaternion_t* a, quaternion_t b) {
    a->m_r -= b.m_r;
    a->m_i -= b.m_i;
    a->m_j -= b.m_j;
    a->m_k -= b.m_k;
}
void quaternion_muleq(quaternion_t* a, quaternion_t b) {
    quaternion_t c = *a;

    a->m_r = c.m_r * b.m_r - c.m_i * b.m_i - c.m_j * b.m_j - c.m_k * b.m_k; 
    a->m_i = c.m_r * b.m_i + c.m_i * b.m_r + c.m_j * b.m_k - c.m_k * b.m_j;
    a->m_j = c.m_r * b.m_j - c.m_i * b.m_k + c.m_j * b.m_r + c.m_k * b.m_i;
    a->m_k = c.m_r * b.m_k + c.m_i * b.m_j - c.m_j * b.m_i + c.m_k * b.m_r;
}

void quaternion_diveq(quaternion_t* a, quaternion_t b) {
    quaternion_muleq(a, quaternion_conj(b));
    quaternion_muleq(&b, quaternion_conj(b));

    a->m_r /= b.m_r;
    a->m_i /= b.m_r;
}

// -------MORE COMPLEX--------

quaternion_t quaternion_exp(quaternion_t a) {
    vec_sclr_t e = exp(a.m_r);

    return (quaternion_t) {e * cos(a.m_i), -e * sin(a.m_i)};
}

quaternion_t quaternion_pow(quaternion_t base, quaternion_t exp) {
    return quaternion_exp(quaternion_mul(quaternion_log(base), exp));
}

quaternion_t quaternion_sqrt(quaternion_t a) {
    return quaternion_pow(a, (quaternion_t) {0.5, 0});
}

quaternion_t quaternion_log(quaternion_t a) {
    return (quaternion_t) {log(quaternion_len(a)), atan(a.m_i / a.m_r)};
}

// --------COMPLEX SPECIFIC-------

quaternion_t quaternion_conj(quaternion_t a) {
    a.m_i *= -1; 
    return a;
}

vec_sclr_t quaternion_len_sq(quaternion_t a) {
    return a.m_r * a.m_r + a.m_i * a.m_i;
}

vec_sclr_t quaternion_len(quaternion_t a) {
    return sqrt(quaternion_len_sq(a));
}

