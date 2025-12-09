#include <math.h>

#include "Quaternion.h"


// ----------BASIC-----------

quaternion_t quaternion_add(quaternion_t a, quaternion_t b) {
    return (quaternion_t) {a.e[0] + b.e[0], a.e[1] + b.e[1], a.e[2] + b.e[2], a.e[3] + b.e[3]};
}

quaternion_t quaternion_sub(quaternion_t a, quaternion_t b) {	
    return (quaternion_t) {a.e[0] - b.e[0], a.e[1] - b.e[1], a.e[2] - b.e[2], a.e[3] - b.e[3]};
}

quaternion_t quaternion_mul(quaternion_t a, quaternion_t b) {
    return (quaternion_t) {
        a.e[0] * b.e[0] - a.e[1] * b.e[1] - a.e[2] * b.e[2] - a.e[3] * b.e[3], 
        a.e[0] * b.e[1] + a.e[1] * b.e[0] + a.e[2] * b.e[3] - a.e[3] * b.e[2],
        a.e[0] * b.e[2] - a.e[1] * b.e[3] + a.e[2] * b.e[0] + a.e[3] * b.e[1],
        a.e[0] * b.e[3] + a.e[1] * b.e[2] - a.e[2] * b.e[1] + a.e[3] * b.e[0]
    };
}

quaternion_t quaternion_div(quaternion_t a, quaternion_t b) {
    quaternion_muleq(&a, quaternion_conj(b));
    quaternion_muleq(&b, quaternion_conj(b));

    a.e[0] /= b.e[0];
    a.e[1] /= b.e[0];

    return a;
}

// --------EQ-----------

void quaternion_addeq(quaternion_t* a, quaternion_t b) {
    a->e[0] += b.e[0];
    a->e[1] += b.e[1];
    a->e[2] += b.e[2];
    a->e[3] += b.e[3];
}

void quaternion_subeq(quaternion_t* a, quaternion_t b) {
    a->e[0] -= b.e[0];
    a->e[1] -= b.e[1];
    a->e[2] -= b.e[2];
    a->e[3] -= b.e[3];
}
void quaternion_muleq(quaternion_t* a, quaternion_t b) {
    quaternion_t c = *a;

    a->e[0] = c.e[0] * b.e[0] - c.e[1] * b.e[1] - c.e[2] * b.e[2] - c.e[3] * b.e[3]; 
    a->e[1] = c.e[0] * b.e[1] + c.e[1] * b.e[0] + c.e[2] * b.e[3] - c.e[3] * b.e[2];
    a->e[2] = c.e[0] * b.e[2] - c.e[1] * b.e[3] + c.e[2] * b.e[0] + c.e[3] * b.e[1];
    a->e[3] = c.e[0] * b.e[3] + c.e[1] * b.e[2] - c.e[2] * b.e[1] + c.e[3] * b.e[0];
}

void quaternion_diveq(quaternion_t* a, quaternion_t b) {
    quaternion_muleq(a, quaternion_conj(b));
    quaternion_muleq(&b, quaternion_conj(b));

    a->e[0] /= b.e[0];
    a->e[1] /= b.e[0];
}

// -------MORE COMPLEX--------

quaternion_t quaternion_exp(quaternion_t a) {
    vec_sclr_t e = exp(a.e[0]);

    vec_sclr_t cos_i;
    
    quaternion_t prod = {e, 0, 0, 0};
    quaternion_t b = {0, 0, 0, 0};

    for (ui32 i = 1; i < Q_DIM; i++) {
        cos_i = cos(a.e[i]);

        b.e[i - 1] = 0;
        b.e[i] = sin(a.e[i]);
        b.e[0] = cos_i;

        quaternion_muleq(&prod, b);
    }

    return prod;
}

quaternion_t quaternion_qpow(quaternion_t base, quaternion_t exp) {
    return quaternion_exp(quaternion_mul(quaternion_log(base), exp));
}

quaternion_t quaternion_upow(quaternion_t base, ui32 exp) {
    quaternion_t a = {1, 0, 0, 0};

    for (ui32 i = 0; i < exp; i++) {
        quaternion_muleq(&a, base);
    }

    return a;
}

quaternion_t quaternion_sqrt(quaternion_t a) {
    return quaternion_qpow(a, (quaternion_t) {0.5, 0, 0, 0});
}

quaternion_t quaternion_log(quaternion_t a) {
    quaternion_t out;
    out.e[0] = log(quaternion_len(a));

    for (ui8 i = 1; i < Q_DIM; i++) {
        out.e[i] = atan(a.e[i] / a.e[0]);
    }

    return out;
}

// -------- \sum^{2^n}_{i = 1} a_i e_i SPECIFIC-------

quaternion_t quaternion_conj(quaternion_t a) {
    for (ui8 i = 1; i < Q_DIM; i++) {
        a.e[i] *= -1;
    }

    return a;
}

vec_sclr_t quaternion_lensq(quaternion_t a) {
    vec_sclr_t sum = 0;

    for (ui8 i = 0; i < Q_DIM; i++) {
         sum += a.e[i] * a.e[i];
    }

    return sum;
}

vec_sclr_t quaternion_len(quaternion_t a) {
    return sqrt(quaternion_lensq(a));
}

ui8 quaternion_eq(quaternion_t a, quaternion_t b) {
    ui8 out = 1;

    for (ui8 i = 0; i < Q_DIM; i++) {
        out &= a.e[i] == b.e[i];
    }

    return out;
}

void quaternion_print(quaternion_t a) {
    printf("%f + %fi + %fj + %fk\n", a.e[0], a.e[1], a.e[2], a.e[3]);
}

