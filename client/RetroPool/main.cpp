
#include "Application.hpp"
#include "RendererManager.hpp"

int main()
{

    RendererManager RenderManager;
    Application game;

    game.GameInit();
    game.GameLoop();

    return 0;
}