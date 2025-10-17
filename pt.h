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


f64 gamma(f64 x) {
    f64 dt = 1e-3;
    f64 sum = 0;

    for (f64 t = 100; t > 0; t -= dt) {
        sum += pow(t, x - 1) * exp(-t) * dt;    
        //printf("%.20lf\t%lf\n", t, sum);
    }

    return sum;
}

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
            f64 psi = gamma(hit.m_vector[1] + 1) / (gamma(hit.m_vector[2] + 1) * gamma(hit.m_vector[1] - hit.m_vector[2] + 1));       

            data->buffer->m_buffer[y * w + x] = vec4_add(
                    vec4_mul((vec4_t) {1, 0, 0, 0}, psi), 
                    (vec4_t) {0, 0, 0, 1}
                );
        }
    }
}


void* th_edit(void* _data) {
    thread_data_t* data = (thread_data_t*) _data;
    ui32 w = data->w;
    ui32 h = data->h;

    f64 t = data->t;
    
    for (ui32 y = 0; y < h; y++) {
        for (ui32 x = data->id * w / n; x < (data->id + 1) * w / n; x++) {
            vec3_diveq((vec3_t*) &(data->buffer->m_buffer[y * w + x]), 2);
            //printf("%lf\n", data->buffer->m_buffer[y * w + x].m_vector[0]);
        }
    }
}

#endif
