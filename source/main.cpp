#include <eng.h>

#include "Game.h"
int main() {
  Game* game = new Game();
  eng::Engine& engine = eng::Engine::getInstance();
  engine.setApplication(game);

  if (engine.init(1280, 720)) {
    engine.run();
  }
  engine.destroy();
  return 0;
}
