add_executable(Sandbox
    src/main.cpp
    src/GameLayer.cpp
)

target_link_libraries(Sandbox
PRIVATE
    NebulaEngine
)