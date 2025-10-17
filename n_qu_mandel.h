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
    
    f64 r_max = 100;
    f64 i_max = 100;

    ui32 counter = 0;

    const f64 dd = 1e-3;
        
    for (ui32 y = 0; y < h; y++) {
        //printf("\r%f", ((f64) (t - t_0) * h + y) / ((f64) h * (t_1 - t_0)));
        //fflush(stdout);
        //
        f64 depth = -1;
        for (ui32 x = data->id * w / n; x < (data->id + 1) * w / n; x++) {
            ui32 i_0 = 1;

            cam3_calc_ray(&cam, x, y);

            if (pow(vec3_dot(cam.m_ray, cam.m_x), 2) < vec3_dot(cam.m_ray, cam.m_ray) * (vec3_dot(cam.m_x, cam.m_x) - 1.8 * 1.8)) {
                //data->buffer->m_buffer[y * w + x] = (vec3_t) {1, 0, 0};
                continue;
            }

            for (depth = -1; depth <= 1; depth += dd * 10) {
                span.m_x = vec3_mul(cam.m_n, depth);

                vec3_t hit = vec3_add(cam.m_x, vec3_mul(cam.m_ray, span3_hit(span, cam.m_x, cam.m_ray)));

                quaternion_t c = {hit.m_vector[1], hit.m_vector[2], hit.m_vector[0], 0};
                quaternion_muleq(&c, quaternion_exp((quaternion_t) {0, 0, t, 0}));
                
                //quaternion_t ex = {0, 0, 0, t};
                //quaternion_muleq(&c, quaternion_exp(ex));
                quaternion_t z = c;

                ui32 i;

                for (i = 1; i < i_max && quaternion_lensq(z) < r_max * r_max; i++) {
                    //z = quaternion_qpow(z, (quaternion_t) {t, 0, 0, 0});
                    z = quaternion_qpow(z, (quaternion_t) {t + 2, 0, 0, 0});
                    quaternion_addeq(&z, c);
                }

                if (depth >= 1) {
                    depth = -1;
                    break; 
                }

                if (i > i_max * 0.8) {
                    if (i > i_0) {
                        depth -= dd * 11;
                        i_0 = i;
                        continue;
                    }
                    
                    data->buffer->m_buffer[y * w + x] = vec4_add(vec4_mul((vec4_t) {-0.548, 0.427, 0.705, 0}, (depth + 1) / 2), (vec4_t) {0.611, 0.243, 0, 1});
                    //depth -= dd;
                    break;
                }


            }
        }

    }

}

#endif
