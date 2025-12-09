cmake_minimum_required(VERSION 3.6)
project(Engine)

set(C_STANDARD 11)

add_executable(
	Engine 
    main.c
    #src/Window.c
    src/Complex.c
    #src/Matrix.c
    #src/Sphere.c
    #src/Hitable.c
    src/Quaternion.c
    #src/Span.c
    #src/Vectors.c
    #src/Rgb.c
	)

include_directories(header)

add_subdirectory(libs/libpng)
#add_subdirectory(libs/LibRaw)

#target_link_libraries(Engine SDL2main SDL2)
target_link_libraries(Engine png_static)
#target_link_libraries(Engine libraw::libraw)
target_link_libraries(Engine m)


install(TARGETS Engine DESTINATION bin)
