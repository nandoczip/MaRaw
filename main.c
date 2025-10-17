#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#include <time.h>

#include "Vectors.h"
#include "Buffer.h"

#include "type_shortage.h"

#ifndef VEC3
#define VEC3 1
USE_VEC(3);
#endif

#ifndef VEC4
#define VEC4 1
USE_VEC(4);
#endif

#ifndef BUFFER4
#define BUFFER4 1
USE_BUFFER(4);
#endif


typedef struct Thread_data {
    pthread_t thread;
    ui32 id;
    ui32 w;
    ui32 h;
    f64 t;
    buffer4_t* buffer;
} thread_data_t;

ui32 n = 0;
ui8 mode = 0; // 0 := "render", 1 := "edit"

#include "pt.h"

int run(ui32 w, ui32 h) {
    char b[100];

    buffer4_t buffer;
    buffer4_init(&buffer);

    switch (mode) {
        case 1:
            buffer4_load_raw(&buffer, "out/0.raw");
            w = buffer.m_w;
            h = buffer.m_h;
            break;
        case 0:
            buffer4_resize(&buffer, w, h);
            break;
    }

    pthread_t threads[n];
    thread_data_t datas[n];
    
    time_t time_0;
    f64 dtime;

    f64 t_0, t_1, dt, t, fps;
    
    t_0 = 0;
    t_1 = 1;
    fps = 90;

    dt = 1 / fps;
    
    time(&time_0);

    for (ui32 frame = t_0 * fps; frame < t_1 * fps; frame++) {
        t = frame * dt;

        for (ui32 i = 0; i < n; i++) {
            datas[i].thread = threads[i];
            datas[i].id = i;
            datas[i].w = w;
            datas[i].h = h;
            datas[i].t = t;
            datas[i].buffer = &buffer;
            
            switch (mode) {
                case 0:
                    pthread_create(&threads[i], NULL, th_run, &datas[i]);
                    break;
                case 1:
                    pthread_create(&threads[i], NULL, th_edit, &datas[i]);
                    break;
            }
        }

        for (ui32 i = 0; i < n; i++) {
            pthread_join(threads[i], NULL);
        }
        
        dtime = difftime(time(NULL), time_0);
        
        printf("\r");

        for (ui32 i = 0; i < 100; i++) {
            printf(" ");    
        }

        printf("\r");
        switch (mode) {
            case 0:
                buffer4_save_raw(&buffer, "out/0.raw");
                break;
            case 1:
                buffer4_save_png_frame(&buffer, "out", frame, 8);
                break;
        }
        printf("Total time: %lfs\tRemaining time: %lfmin", dtime, (dtime * (t_1 - t_0) / (t + dt - t_0)) / 60); 
        fflush(stdout);
    }
    
    printf("\n");

    return 0;
}

int main(int argc, char* argv[]) {
    ui32 w = 0, h = 0;  
    ui32* sizes[3] = {&w, &h, &n};
    
    if (argc == 1) {
        w = 400;
        h = 3600 / 16;
    }

    else if (argc == 2) {
        if (argv[1][0] == 'f') {
            w = 4000 / 2;
            h = 36000 / 16 / 2;
            n = 4;
        }
        else if (argv[1][0] == 't') {
            w = 400;
            h = 3600 / 16;
            n = 4;
        }
        else if (argv[1][0] == 'e') {
            mode = 1;
            w = 1;
            h = 1;
            n = 4;
        }
    }

    else if (argc >= 3) {
        for (ui32 i = 0; i < argc - 1; i++) {
            for (ui32 j = 0; argv[i + 1][j] != 0; j++) {
                *(sizes[i]) *= 10;
                *(sizes[i]) += argv[i + 1][j] - 48;
            }
        }
    }

    printf("%u\t%u\t%u\t%d\n", w, h, n, argc);

    return run(w, h);
}

