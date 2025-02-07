#include "Game.h"
#include <android_native_app_glue.h>
//call from android_native_app_glue.c
void android_main(android_app* state) {
  Game game;
  state->userData = &game;
  game.init(state);
  game.run();

  //state->onAppCmd = engine_handle_cmd;
}