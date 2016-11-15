#ifdef __OBJC__

#import <UIKit/UIKit.h>

@class EAGLView;
@class MainViewController;

@interface AppDelegate : NSObject <UIApplicationDelegate> {
    UIWindow *window;
    EAGLView *glView;
    MainViewController *viewController;
}

+ (AppDelegate*) GetInstance;
+ (UIViewController*) GetRootViewController;
+ (UIView*) GetRootView;

@property (nonatomic, retain) IBOutlet UIWindow *window;
@property (nonatomic, retain) IBOutlet EAGLView *glView;
@property (nonatomic, retain) IBOutlet MainViewController *viewController;

@end

#endif

#ifdef __cplusplus

namespace GUI
{
class Widget;
}

// Ввод текста
void ShowKeyboard();
void ShowNumericKeyboard();
void HideKeyboard();
bool IsKeyboardActive();
bool IsKeyboardVisible();
std::string GetInputText(); // Возвращает текст в textField
void SetInputText(const std::string &text); // Устанавливает текст в textField
void SetInputWidget(GUI::Widget *w);
GUI::Widget* GetInputWidget();

void ResetAnimationFrameInterval();

#endif
