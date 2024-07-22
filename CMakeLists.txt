cmake_minimum_required(VERSION 3.0.0)

set (PROJECT_NAME Raytracer)
project(${PROJECT_NAME} 
        VERSION 0.1.0
        LANGUAGES CXX)

set ( CMAKE_CXX_STANDARD 20 )

CONFIGURE_FILE(assets/objects.xml objects.xml COPYONLY)
CONFIGURE_FILE(assets/mesh/box_stack.obj box_stack.obj COPYONLY)
CONFIGURE_FILE(assets/mesh/bed.obj bed.obj COPYONLY)
CONFIGURE_FILE(assets/mesh/chair.obj chair.obj COPYONLY)
CONFIGURE_FILE(assets/mesh/cube.obj cube.obj COPYONLY)
CONFIGURE_FILE(assets/mesh/monkey.obj monkey.obj COPYONLY)
CONFIGURE_FILE(assets/mesh/sphere.obj sphere.obj COPYONLY)
CONFIGURE_FILE(assets/mesh/stool.obj stool.obj COPYONLY)
CONFIGURE_FILE(assets/mesh/table.obj table.obj COPYONLY)
CONFIGURE_FILE(assets/mesh/tree.obj tree.obj COPYONLY)

set ( HDR 
        src/3rdParty/tinyxml2/tinyxml2.h
        src/3rdParty/ObjLoader/OBJ_Loader.h
        src/engine/camera.h
        src/engine/config.h
        src/engine/hittable.h
        src/engine/sphere.h
        src/engine/triangle.h
        src/engine/material.h
        src/engine/emissive.h
        src/engine/lambertian.h
        src/engine/metal.h
        src/engine/sun.h
        src/engine/mesh.h
        src/engine/hittable_list.h
        src/engine/world.h
        src/engine/factories/factory_methods.h
        src/util/vec3.h
        src/util/ray.h
        src/defs.h
    )

set ( SRC 
        src/3rdParty/tinyxml2/tinyxml2.cpp
        src/engine/camera.cpp
        src/engine/config.cpp
        src/engine/shpere.cpp
        src/engine/triangle.cpp
        src/engine/lambertian.cpp
        src/engine/metal.cpp
        src/engine/emissive.cpp
        src/engine/sun.cpp
        src/engine/mesh.cpp
        src/engine/hittable_list.cpp
        src/engine/world.cpp
        src/engine/factories/factory_methods.cpp
        src/util/vec3.cpp
        src/main.cpp
    )

# Add library subdirectories
add_subdirectory(src/3rdParty/glm-master ${CMAKE_BINARY_DIR}/glm)

# Executable
add_executable(${PROJECT_NAME}
                ${HDR} 
                ${SRC} 
            )

# Link static libraries
target_link_libraries(${PROJECT_NAME}
                        glm
					)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
