#pragma once
#include <memory>
#import <UIKit/UIKit.h>
#include <Metal/Metal.h>
#include <functional>
@interface DisplayLink : NSObject
{
    std::function<void()> callback; // 멤버 변수로 관리
}
@property (nonatomic, strong) CADisplayLink *displayLink;
@end
@implementation DisplayLink {
}
- (instancetype)init
{
    self = [super init];
    // CADisplayLink 설정
       self.displayLink = [CADisplayLink displayLinkWithTarget:self selector:@selector(gameLoop)];
       [self.displayLink addToRunLoop:[NSRunLoop mainRunLoop] forMode:NSDefaultRunLoopMode];
    return self;
}
- (void)gameLoop {
    if (callback) {
           callback();
       }
}
- (void)start:(std::function<void()> )cb {
   callback = cb;
}
@end
