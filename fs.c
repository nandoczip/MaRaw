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

#include "pt.h"

int main() {
    buffer4_t buffer;
    buffer4_init(&buffer);


    
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
        }
        if (argv[1][0] == 't') {
            w = 400;
            h = 3600 / 16;
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

