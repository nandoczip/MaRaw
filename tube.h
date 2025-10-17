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

f64 abs_f64(f64 a) {
    *((i64*) &a) &= ~(1l << 63);

    return a;
}

void vec3_printf(vec3_t a) {
    printf("(%f, %f, %f)\n", a.m_vector[0], a.m_vector[1], a.m_vector[2]);
}

void vec2_printf(vec2_t a) {
    printf("(%f, %f)\n", a.m_vector[0], a.m_vector[1]);
}

f64 defined_integral(f64 (*f) (f64, f64, f64), f64 x_0, f64 x_1, f64 dx, f64 a, f64 b) {
    f64 sum = 0;

    for (f64 x = x_0; x < x_1; x += dx) {
        sum += f(x, a, b) * dx;
    }

    return sum;
}

//f64 n_m_aprox(f64 (*f)(f64), f64 x_0, f64 h, f64 epsilon, f64 a, f64 b, f64 c) {
f64 n_m_approx(f64 (*func)(f64, vec3_t, vec3_t), f64 x_0, f64 h, f64 epsilon, vec3_t a, vec3_t b) {
    f64 x;
    ui32 i;
    
    for (i = 0, x = x_0; i < 10000 && abs_f64(func(x, a, b)) > epsilon; i++, x -= func(x, a, b) * h / (func(x + h, a, b) - func(x, a, b)));

    return x;
}

/*f64 n_m(f64 (*func)(vec3_t (*)(f64), vec3_t (*)(f64), f64, vec3_t, vec3_t), f64 (*func_p)(f64), f64 x_0, f64 h, f64 epsilon, f64 a, f64 b, f64 c) {
    f64 x;
    
    for (x = x_0; abs_f64(f(x)) > epsilon; x -= func(x) / func_p(x));

    return x;
}*/

vec3_t g(f64 lambda) {
    return (vec3_t) {
        lambda * lambda,
        4 * lambda,
        lambda * lambda * lambda
    };
}

vec3_t g_p(f64 lambda) {
    return (vec3_t) {
        2 * lambda,
        4,
        3 * lambda * lambda
    };    
}

f64 out(f64 my, vec3_t a, vec3_t b) {
    f64 lambda = vec3_dot(b, vec3_sub(g(my), a)) / vec3_lensq(b);

    return -2 * vec3_dot(vec3_sub(vec3_add(a, vec3_mul(b, lambda)), g(my)), g_p(my)); 
}

f64 out_p(f64 my, vec3_t a, vec3_t b) {
    const f64 h = 1e-10;
    return (out(my + h, a, b) - out(my, a, b)) / h;
}

vec2_t n_mm(f64 (*func)(vec2_t), f64 (*func_p)(vec2_t), vec2_t x_0, f64 epsilon) {
    vec2_t x;
    
    for (x = x_0; abs_f64(func(x)) > epsilon; vec2_subeq(&x, vec2_mul((vec2_t) {1, 1}, func(x) / func_p(x)))) {vec2_printf(x);}

    return x;
}

f64 ff(f64 x) {
    return x * x;
}

i32 run() {
    const ui32 w = 400, h = 3600 / 16;
    
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
    
    f64 t_0, t_1, fps;
    t_0 = 1;
    t_1 = 2;
    fps = 1;
    
    ui32 frame;

    
    for (f64 t = t_0; t < t_1; t += 1 / fps) {
        for (ui32 y = 0; y < h; y++) {
            printf("%f\n", ((f64) y) / ((f64) h));
            for (ui32 x = 0; x < w; x++) {
                frame = t * fps;
                cam.m_x.m_vector[2] = -10 + t;
                cam3_calc_ray(&cam, x, y);
                
                f64 min_d = INFINITY;

                for (ui8 x_0_i = -100; x_0_i < 200; x_0_i += 100) {
                    f64 my = n_m_approx(out, x_0_i, 1e-10, 1e-6, cam.m_x, cam.m_ray);
                    //printf("h");
                    f64 lambda = vec3_dot(vec3_sub(g(my), cam.m_x), cam.m_ray) / vec3_lensq(cam.m_ray);

                    f64 d = vec3_lensq(vec3_sub(vec3_add(vec3_mul(cam.m_ray, lambda), cam.m_x), g(my)));

                    if (d < min_d) {
                        min_d = d;
                    }
                }
                const f64 r = 1;

                if (min_d > r * r) {
                    buffer.m_buffer[y * h + x] = (vec3_t) {
                        0,
                        0,
                        0
                    };
                }

                else {
                    buffer.m_buffer[y * h + x] = (vec3_t) {
                        1,
                        0,
                        0
                    };
                }
            }
        }
        
        buffer3_save_png_frame(&buffer, "out", frame, 8);
    }

    /*
    f64 x_n = 2;

    for (f64 t = t_0; t < t_1; t += 1 / fps) {
        frame = t * fps;
        const f64 x_0 = -10;
        const f64 x_1 = 10;
        const f64 dx = (x_1 - x_0) / (100 * w);

        const f64 y_0 = -10; //ff(x_0);
        const f64 y_1 = 10; //ff(x_1);

        cam3_calc_ray(&cam, 0, 0);
        f64 eta = 1e-6;

        memset(buffer.m_buffer, 0, w * h * sizeof(vec3_t));

        x_n -= out(x_n, cam.m_x, cam.m_ray) / out_p(x_n, cam.m_x, cam.m_ray);

        for (f64 x = x_0; x < x_1; x += dx) {

            f64 yy[2];
            yy[0] = out(x, cam.m_x, cam.m_ray);
            yy[1] = out_p(x_n, cam.m_x, cam.m_ray) * (x - x_n) + out(x_n, cam.m_x, cam.m_ray);

            i32 pos_x, pos_y, pos_0;

            for (ui8 i = 0; i < 2; i++) {
                f64 y = yy[i];

                pos_x = w * (x - x_0) / (x_1 - x_0);
                pos_y = h * (1 - (y - y_0) / (y_1 - y_0));
                pos_0 = h * (1 + y_0 / (y_1 - y_0));


                if (pos_y < h && pos_y >= 0) {
                    buffer.m_buffer[pos_y * w + pos_x] = (vec3_t) {
                        1,
                        0,
                        0
                    };
                }
            }

            buffer.m_buffer[w * pos_0 + pos_x] = (vec3_t) {
                1, 1, 1
            };
        }

        for (ui32 y = 0; y < h; y++) {
            buffer.m_buffer[w * y + ((ui32) (w * (x_0 / (x_0 - x_1))))] = (vec3_t) {1, 1, 1};
        }
        printf("%f: ", x_n);
        buffer3_save_png_frame(&buffer, "out", frame, 8);
    }
    */

    //printf("%f\n", n_m(g, 5, 1e-10, 1e-15)); 
    
    //vec2_printf(n_mm(f, f_p, (vec2_t) {2, 4}, 0));

    //buffer3_save_png(&buffer, "out/0.png", 8);

    return 0;
}

#endif
