#pragma once
#include "MetalView.h"

#import <UIKit/UIKit.h>
#include <Metal/Metal.h>

@interface MetalViewController : UIViewController
@property(nonatomic, strong) MetalView *metalView;
@property(nonatomic, strong) UIWindow *window;
@end
@implementation MetalViewController {
}

- (void)viewDidLoad {

    // MetalView 생성 및 추가
    _metalView = [[MetalView alloc]init];
    self.view = _metalView;

    if (self.view.hidden) {
        NSLog(@"View is hidden");
        self.view.hidden = NO;
    }
    if (self.view.alpha == 0) {
        NSLog(@"View is transparent");
        self.view.alpha = 1.0;
    }
    // 타이머로 렌더링 호출
   
    [NSTimer scheduledTimerWithTimeInterval:(1.0 / 60.0)
                                     target:self
                                   selector:@selector(renderLoop)
                                   userInfo:nil
                                    repeats:YES];
}

- (void)renderLoop {
    [_metalView render];
}
@end

