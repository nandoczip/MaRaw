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

#ifndef RENDER_FILE
#define RENDER_FILE 1

void vec3_printf(vec3_t a) {
    printf("(%f, %f, %f)\n", a.m_vector[0], a.m_vector[1], a.m_vector[2]);
}

f64 defined_integral(f64 (*f) (f64, f64, f64), f64 x_0, f64 x_1, f64 dx, f64 a, f64 b) {
    f64 sum = 0;

    for (f64 x = x_0; x < x_1; x += dx) {
        sum += f(x, a, b) * dx;
    }

    return sum;
}


i32 run() {
    const ui32 w = 4000, h = 36000 / 16;
    
    cam3_t cam;
    cam.m_w = w;
    cam.m_h = h;
    cam.m_fstop = 0.5;
    cam.m_x = (vec3_t) {-10.0, 0, 0};
    cam.m_n = (vec3_t) {1, 0, 0};

    span3_t span;
    span.m_n = cam.m_n;

    buffer3_t buffer;
    buffer3_init(&buffer);

    buffer3_resize(&buffer, w, h);
    
    vec3_t light = {-1, -1, -1};

    f64 max_v = 0, min_v = 10000;

    for (ui32 y = 0; y < h; y++) {
        printf("%f\n", ((f64) y) / ((f64) h));
        for (ui32 x = 0; x < w; x++) {
            cam3_calc_ray(&cam, x, y);

            vec3_normeq(&cam.m_ray);
            
            //printf("%f\n", vec3_len(cam.m_ray));

            f64 a, b, c;
            a = cam.m_ray.m_vector[0] * cam.m_ray.m_vector[0] + cam.m_ray.m_vector[1] * cam.m_ray.m_vector[1]; 
            b = 2 * cam.m_ray.m_vector[0] * cam.m_x.m_vector[0] + 2 * cam.m_ray.m_vector[1] * cam.m_x.m_vector[1] - cam.m_ray.m_vector[2];
            c = cam.m_x.m_vector[0] * cam.m_x.m_vector[0] + cam.m_x.m_vector[1] * cam.m_x.m_vector[1] - cam.m_x.m_vector[2];
            
            if (b * b < 4 * a * c || a == 0) {
                buffer.m_buffer[y * w + x] = (vec3_t) {0, 0, 0};
                continue;
            }

            f64 lambda = (-b + sqrt(b * b - 4 * a * c)) / (2 * a);

            vec3_t hit = vec3_add(vec3_mul(cam.m_ray, lambda), cam.m_x); 
            vec3_t n = {-2 * hit.m_vector[0], -2 * hit.m_vector[1], 1};
            f64 v = vec3_dot(vec3_norm(n), vec3_norm(light));
            buffer.m_buffer[y * w + x] = (vec3_t) {
                v,
                v,
                v
            };
        }
    }

    buffer3_save_png(&buffer, "out/0.png", 8);

    return 0;
}

#endif
