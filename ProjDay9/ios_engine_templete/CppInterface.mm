#import "CppInterface.h"
#include "Game.h"
@interface CppInterface ()
{
    Game* game;
}
@end

@implementation CppInterface

-(instancetype)init
{
    self = [super init];
    if (self) {
        game = new Game();
        game->init();
        game->run();
    }
    return self;
}

@end
