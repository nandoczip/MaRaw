#include "Quaternion.h"
#include "Complex.h"

#include "Span.h"
#include "Camera.h"

#ifndef SPAN3
#define SPAN3 1
USE_SPAN(3);
#endif

#ifndef CAM3
#define CAM3 1
USE_CAM(3);
#endif


#ifndef MANDELBROT_FILE
#define MANDELBROT_FILE 1

void* th_run(void* _data) {
    thread_data_t* data = (thread_data_t*) _data;
    ui32 w = data->w;
    ui32 h = data->h;
    
    f64 t = data->t;

    cam3_t cam;
    cam.m_w = w;
    cam.m_h = h;
    cam.m_fstop = 4;
    cam.m_x = (vec3_t) {-10.0, 0, 0};
    cam.m_n = (vec3_t) {1, 0, 0};

    span3_t span;
    span.m_n = cam.m_n;
    span.m_x = (vec3_t) {0, 0, 0};

    vec3_t light = {-1, -1, -1};
    
    ui32 frame = 0;

    f64 r_max = 2;
    f64 i_max = 100;

    for (ui32 y = 0; y < h; y++) {
        for (ui32 x = data->id * w / n; x < (data->id + 1) * w / n; x++) {
            //frame = t * fps;

            cam3_calc_ray(&cam, x, y);

            vec3_t hit = vec3_add(cam.m_x, vec3_mul(cam.m_ray, span3_hit(span, cam.m_x, cam.m_ray)));

            complex_t c = {hit.m_vector[1], hit.m_vector[2]}; 

            complex_t z = complex_add(complex_mul(c, c), c);
            complex_t z_np1 = {0, 0};
            
            ui32 i;

            /*for (i = 2; i < i_max && complex_lensq(complex_sub(z, c)) > 0; i++) {
                complex_muleq(&z, z);
                complex_addeq(&z, c);
            }*/
            
            ui32 m = 10;

            complex_t zs[100];
            zs[1] = c;

            for (i = 2; i < m + 1; i++) {
                zs[i] = complex_mul(zs[i - 1], zs[i - 1]);
                complex_addeq(&zs[i], c);
            }

            vec2_t* zz = (vec2_t*) zs;
            vec2_t as[2] = {vec2_sub(zz[m - 2], zz[m - 1]), vec2_sub(zz[m], zz[m - 1])};
            f64 dot = vec2_dot(as[0], as[1]) / (vec2_len(as[0]) * vec2_len(as[1]));

            //complex_subeq(&z_np1, z_n);
            
            //f64 dot = vec2_dot(*((vec2_t*) &z_np1), *((vec2_t*) &z_n)) / (complex_len(z_np1) * complex_len(z_n)); 
            //f64 cos_phi = vec2_dot(*((vec2_t*) &z_np1), (vec2_t) {1, 0}) / complex_len(z_np1);

            data->buffer->m_buffer[y * w + x] = vec4_add(
                    vec4_mul((vec4_t) {-1, -1, 0, 0}, dot), 
                    (vec4_t) {1, 1, 1, 1}
                );
        }
    }
}

#endif
