#include "engine.hpp"
#include "../application/application.hpp"
#include "../application/opengl/opengl-application.hpp"
#include "utils/log.hpp"
#include "utils/sdl-wrapper.hpp"
#include <SDL_image.h>
#include <stdexcept>
#include <string>

using ast::Engine;

struct Engine::Internal
{
    const std::string classLogTag;

    Internal() : classLogTag("ast::Engine::") {}

    void run()
    {
        static const std::string logTag{classLogTag + "run"};

        ast::log(logTag, "Starting engine ...");
        SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
        ast::log(logTag, "SDL2 initialized successfully ...");

        if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG)
        {
            throw std::runtime_error(logTag + " Could not initialize SDL2_image ...");
        }
        ast::log(logTag, "SDL2_image initialized successfully with PNG support ...");

        resolveApplication()->startApplication();
    }

    std::unique_ptr<ast::Application> resolveApplication()
    {
        static const std::string logTag{classLogTag + "resolveApplication"};

        try
        {
            ast::log(logTag, "Creating OpenGL application ...");
            return std::make_unique<ast::OpenGLApplication>();
        }
        catch (const std::exception& error)
        {
            ast::log(logTag, "OpenGL application failed to initialize.", error);
        }

        throw std::runtime_error(logTag + " No applications can run in the current environment");
    }

    ~Internal()
    {
        SDL_Quit();
    }
};

Engine::Engine() : internal(ast::make_internal_ptr<Internal>()) {}

void Engine::run()
{
    internal->run();
}
