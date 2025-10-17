#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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

vec_sclr_t lp_vec3_dist_pot(vec3_t v, vec_sclr_t p) {
    vec_sclr_t sum = 0;
    vec_sclr_t b;

    for (ui32 i = 0; i < 3; i++) {
        *((long*) &b) = *((long*) &v.m_vector[i]) & ~(1l << 63);
        sum += pow(b, p);
    }

    return sum;
}

i32 run(ui32 w, ui32 h) {
    
    cam3_t cam;
    cam.m_w = w;
    cam.m_h = h;
    cam.m_fstop = 5;
    cam.m_x = (vec3_t) {-10.0, 0, 0};
    cam.m_n = (vec3_t) {1, 0, 0};

    span3_t span;
    span.m_n = cam.m_n;
    span.m_x = (vec3_t) {0, 0, 0};

    buffer3_t buffer;
    buffer3_init(&buffer);

    buffer3_resize(&buffer, w, h);
    
    vec3_t light = {-1, -1, -1};

    vec_sclr_t p = 2, r = 100;
    
    f64 t_0, t_1, t, fps;
    t_0 = 0;
    t_1 = 10;
    fps = 24;
    
    f64 r_max = 100;
    f64 i_max = 100;

    ui32 counter = 0;

    const f64 dd = 1e-3;

    for (ui32 frame = t_0 * fps; frame < t_1 * fps; frame++) {
        t = frame / fps;

        p = sin(t) * 154;

        memset(buffer.m_buffer, 0, sizeof(vec3_t) * w * h);

        for (ui32 y = 0; y < h; y++) {
            printf("%f\n", ((f64) (frame - t_0 * fps) * h + y) / ((f64) h * (t_1 - t_0) * fps));
            for (ui32 x = 0; x < w; x++) {
                vec3_t a = {x, y, 0};
                vec3_t m = {w / 2, h / 2, 0};
                vec3_subeq(&a, m); 

                if (lp_vec3_dist_pot(a, p) < pow(r, p)) {
                    buffer.m_buffer[x + y * w] = (vec3_t) {1, 0, 0};
                }
            }

        }

        buffer3_save_png_frame(&buffer, "out", frame, 8);
    }

    return 0;
}

#endif
