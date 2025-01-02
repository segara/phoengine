#import "ViewController.h"

#import "CppInterface.h"
@interface ViewController ()
{

}
@end
@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    CppInterface*  i = [[CppInterface alloc]init];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
