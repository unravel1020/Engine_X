add_library(NebulaEngine STATIC
    src/app/Application.cpp
    src/logger/Log.cpp
    src/core/LayerStack.cpp
    src/platform/Window.cpp
    src/core/Input.cpp
    src/platform/OpenGLContext.cpp
    src/renderer/Buffer.cpp
    src/renderer/Shader.cpp
    src/renderer/VertexArray.cpp
    src/renderer/RenderCommand.cpp
    src/renderer/OpenGL/OpenGLRenderAPI.cpp
    src/renderer/Renderer.cpp
    src/renderer/OrthographicCamera.cpp
)

target_include_directories(NebulaEngine PUBLIC
    include
)

find_package(spdlog CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glad CONFIG REQUIRED)

target_link_libraries(NebulaEngine PUBLIC
    spdlog::spdlog
    glfw
    glm::glm
    OpenGL::GL
    glad::glad
)

target_compile_features(NebulaEngine PUBLIC cxx_std_20)