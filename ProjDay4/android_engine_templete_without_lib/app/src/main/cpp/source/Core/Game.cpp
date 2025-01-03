#include "Core/Game.h"

#include "Window/OWindow.h"

#include <EGL/egl.h>
#include <GLES/gl.h>
#include <android/choreographer.h>
#include <android/log.h>
#include <android/set_abort_message.h>
#include <android_native_app_glue.h>
#include <jni.h>

#include <cassert>
#include <cerrno>
#include <cstdlib>
#include <cstring>
#include <initializer_list>
#include <memory>


/**
 * Process the next main command.
 */

android_app* state;

Game::Game()
{

}
Game::~Game()
{

}
void Game::onCreate()
{
}

void Game::onUpdate()
{
	m_graphicsEngine->clear(Vec4(0.0f, 0.5f, 0.8f, 1.0f));
	m_window->Present(false);
}

void Game::onQuit()
{
}
void engine_handle_cmd(android_app* app, int32_t cmd) {
    Game* game = (Game*) app->userData;
    switch (cmd) {
        case APP_CMD_INIT_WINDOW:
            if (app->window != nullptr) {
                ANativeWindow* nativeWindow = app->window;
                game->m_graphicsEngine = std::make_unique<GraphicEngine>(nativeWindow);
                game->m_isInit = true;
                // Store `window` or use it directly
            }
            break;

        case APP_CMD_TERM_WINDOW:
            // Clean up resources tied to the native window
            break;

        default:
            break;
    }
}
void Game::init(void* app)
{
    state = (android_app*)app;
    state->onAppCmd = engine_handle_cmd;
    m_window = std::make_unique<OWindow>();

}
void Game::run()
{
	onCreate();

	while (m_isRunning) {
		// Our input, sensor, and update/render logic is all driven by callbacks, so
		// we don't need to use the non-blocking poll.
		android_poll_source* source = nullptr;
		auto result = ALooper_pollOnce(-1, nullptr, nullptr,
									reinterpret_cast<void**>(&source));
		if (result == ALOOPER_POLL_ERROR) {
		//fatal("ALooper_pollOnce returned an error");
		}

		if (source != nullptr) {
			source->process(state, source);
		}
        if(m_isInit)onUpdate();
    }

	onQuit();

}

void Game::quit()
{
	m_isRunning = false;
}


