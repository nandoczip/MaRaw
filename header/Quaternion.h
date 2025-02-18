#ifndef QUATERNION_H
#define QUATERNION_H 1

typedef double vec_sclr_t;

typedef struct {
	vec_sclr_t m_r, m_i, m_j, m_k;
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
quaternion_t quaternion_pow(quaternion_t base, quaternion_t exp);
quaternion_t quaternion_sqrt(quaternion_t a);
quaternion_t quaternion_log(quaternion_t a);

quaternion_t quaternion_conj(quaternion_t);

vec_sclr_t quaternion_len_sq(quaternion_t a);
vec_sclr_t quaternion_len(quaternion_t a);

#endif
