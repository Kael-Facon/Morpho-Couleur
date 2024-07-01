cmake_minimum_required(VERSION 3.22)
project(morpho_couleur)

set(CMAKE_CXX_STANDARD 17)

add_executable(morpho_couleur main.cpp
        # Frontend
        src/frontend/imgui/imconfig.h
        src/frontend/imgui/imgui.cpp
        src/frontend/imgui/imgui.h
        src/frontend/imgui/imgui_demo.cpp
        src/frontend/imgui/imgui_draw.cpp
        src/frontend/imgui/imgui_internal.h
        src/frontend/imgui/imgui_tables.cpp
        src/frontend/imgui/imgui_widgets.cpp
        src/frontend/imgui/imstb_rectpack.h
        src/frontend/imgui/imstb_textedit.h
        src/frontend/imgui/imstb_truetype.h
        src/frontend/imgui/imgui_impl_glfw.cpp
        src/frontend/imgui/imgui_impl_opengl3.cpp
        src/frontend/imgui/imgui_impl_glfw.h
        src/frontend/imgui/imgui_impl_opengl3.h
        src/frontend/imgui/imgui_impl_opengl3_loader.h
        src/frontend/app.cpp
        src/frontend/app.hh
        src/frontend/env.hh
        src/frontend/env.cpp

        # Backend
        ## utils
        src/backend/utils/vector3.hh
        src/backend/utils/vector3.cpp
        src/backend/utils/color.hh
        src/backend/utils/color.cpp
        src/backend/utils/color_hsv.hh
        src/backend/utils/utils.hh

        ## image
        src/backend/image/image.hh
        src/backend/image/image.cpp

        ## intersection
        src/backend/intersection/intersection.hh
        src/backend/intersection/intersection.cpp
        src/backend/intersection/intersection.cpp

        ## shapes
        src/backend/shapes/shape.hh
        src/backend/shapes/disk.hh
        src/backend/shapes/square.hh
        src/backend/shapes/diamond.hh

        ## morpho
        src/backend/morpho/method.hh
        src/backend/morpho/method.cpp
)

find_package(OpenGL REQUIRED)
target_link_libraries(morpho_couleur PUBLIC OpenGL::GL)

find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(morpho_couleur PUBLIC glfw)