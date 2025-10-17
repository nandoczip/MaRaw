#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#include <time.h>

#include "Vectors.h"
#include "Buffer.h"
#include "Span.h"
#include "Camera.h"

#include "Quaternion.h"
#include "Complex.h"
#include "type_shortage.h"

#ifndef VEC3
#define VEC3 1
USE_VEC(3);
#endif

#ifndef VEC4
#define VEC4 1
USE_VEC(4);
#endif

#ifndef BUFFER3
#define BUFFER3 1
USE_BUFFER(3);
#endif

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


const ui32 n = 4;


typedef struct Thread_data {
    pthread_t ip;
    ui32 id;
    ui32 w;
    ui32 h;
    f64 t;
    buffer3_t* buffer;
} thread_data_t;


void* th_run(void* _data) {
    thread_data_t* data = (thread_data_t*) _data;

    ui32 w = data->w;
    ui32 h = data->h;
    f64 t = data->t;

    cam3_t cam;
    cam.m_w = w;
    cam.m_h = h;
    cam.m_fstop = 5;
    cam.m_x = (vec3_t) {-10.0, 0, 0};
    cam.m_n = (vec3_t) {1, 0, 0};

    span3_t span;
    span.m_n = cam.m_n;
    span.m_x = (vec3_t) {0, 0, 0};

    
    vec3_t light = {-1, -1, -1};
    
    
    f64 r_max = 100;
    f64 i_max = 100;

    ui32 counter = 0;

    const f64 dd = 1e-1;
        
    for (ui32 y = 0; y < h; y++) {
        //printf("\r%f", ((f64) (t - t_0) * h + y) / ((f64) h * (t_1 - t_0)));
        //fflush(stdout);
        for (ui32 x = data->id * w / n; x < (data->id + 1) * w / n; x++) {
            ui32 i_0 = 1;

            cam3_calc_ray(&cam, x, y);

            if (pow(vec3_dot(cam.m_ray, cam.m_x), 2) < vec3_dot(cam.m_ray, cam.m_ray) * (vec3_dot(cam.m_x, cam.m_x) - 1.8 * 1.8)) {
                //buffer.m_buffer[y * w + x] = (vec3_t) {1, 0, 0};
                continue;
            }

            for (f64 depth = -1; depth <= 1; depth += dd) {
                span.m_x = vec3_mul(cam.m_n, depth);

                vec3_t hit = vec3_add(cam.m_x, vec3_mul(cam.m_ray, span3_hit(span, cam.m_x, cam.m_ray)));

                quaternion_t c = {hit.m_vector[1], hit.m_vector[2], hit.m_vector[0], 0};
                quaternion_muleq(&c, quaternion_exp((quaternion_t) {0, 0, 0, t}));
                
                //quaternion_t ex = {0, 0, 0, t};
                //quaternion_muleq(&c, quaternion_exp(ex));
                quaternion_t z = c;

                ui32 i;

                for (i = 1; i < i_max && quaternion_lensq(z) < r_max * r_max; i++) {
                    //z = quaternion_qpow(z, (quaternion_t) {t, 0, 0, 0});
                    z = quaternion_upow(z, 2);
                    quaternion_addeq(&z, c);
                }

                if (depth >= 1) {
                    break; 
                }

                if (i > i_max * 0.8) {
                    /*if (i > i_0) {
                        depth -= dd * 11;
                        continue;
                    }*/
                    
                    data->buffer->m_buffer[y * w + x] = vec3_add(vec3_mul((vec3_t) {-0.548, 0.427, 0.705}, (depth + 1) / 2), (vec3_t) {0.611, 0.243, 0});
                    break;
                }

                //i_0 = i;

            }
        }

    }

}

i32 run(ui32 w, ui32 h) {
    thread_data_t datas[n];

    buffer3_t buffer;
    buffer3_init(&buffer);
    buffer3_resize(&buffer, w, h);

    f64 t_0, t_1, t, fps;
    t_0 = 0;
    t_1 = 1;
    fps = 1;
    
    printf("Start\n");
    time_t time_0;
    time(&time_0);

    for (ui32 frame = t_0 * fps; frame < t_1 * fps; frame++) {
        t = frame / fps;
        memset(buffer.m_buffer, 0, sizeof(vec3_t) * w * h);
        
        for (ui32 i = 0; i < n; i++) {
            datas[i].id = i;
            datas[i].w = w;
            datas[i].h = h;
            datas[i].t = t;
            datas[i].buffer = &buffer;

            pthread_create(&datas[i].ip, NULL, th_run, &datas[i]); 
        }

        for (ui32 i = 0; i < n; i++) {
            pthread_join(datas[i].ip, NULL); 
        }

        printf("\r");
        buffer3_save_png_frame(&buffer, "out", frame, 8);
        fflush(stdout);
    } 

    printf("%lf\n", difftime(time(NULL), time_0));
    
    return 0;
}


put_pixel(ui32 x, ui32 y) {
    asm {
        mov ah,0x02
        mov bh,0x00
        mov dh,y
        mov dl,x

        int 10h
    }
}

#endif
