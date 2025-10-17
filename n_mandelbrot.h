#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "Vectors.h"
#include "Buffer.h"
#include "Span.h"
#include "Camera.h"

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


i32 run() {
    const ui32 w = 400, h = 3600 / 16;
    
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
    
    f64 t_0, t_1, fps;
    t_0 = 20;
    t_1 = 100;
    fps = 10;
    
    f64 t;

    f64 r_max = 100;
    f64 i_max = 100;

    for (ui32 frame = t_0 * fps; frame < t_1 * fps; frame++) {
        for (ui32 y = 0; y < h; y++) {
            printf("%f\n", ((f64) frame * h + y) / ((f64) h * (t_1 - t_0) * fps));
            for (ui32 x = 0; x < w; x++) {
                t = ((f64) (frame)) / fps;

                cam3_calc_ray(&cam, x, y);

                vec3_t hit = vec3_add(cam.m_x, vec3_mul(cam.m_ray, span3_hit(span, cam.m_x, cam.m_ray)));

                complex_t c = {hit.m_vector[1], hit.m_vector[2]}; 
                complex_t z = c;

                ui32 i;
                    
                for (i = 1; i < i_max && complex_lensq(z) < r_max * r_max; i++) {
                    z = complex_cpow(z, (complex_t) {t, 0});
                    complex_addeq(&z, c);
                }
                
                buffer.m_buffer[y * w + x] = vec3_add(vec3_mul((vec3_t) {1, 1, 1}, i / i_max), (vec3_t) {0, 0, 0});
            }
        }

        buffer3_save_png_frame(&buffer, "out", frame, 8);
    }

    return 0;
}

#endif
