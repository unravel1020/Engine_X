#include <iostream>

#include "GameLayer.hpp"
#include "nebula/Application.hpp"
#include "nebula/core/Log.hpp"

int main()
{
    std::cout << "Initializing logger...\n";

    nebula::Log::Init();

    std::cout << "main begin\n";

    nebula::Application app;

    std::cout << "application created\n";

    app.PushLayer(new GameLayer());

    std::cout << "layer pushed\n";

    app.Run();

    std::cout << "run finished\n";

    return 0;
}