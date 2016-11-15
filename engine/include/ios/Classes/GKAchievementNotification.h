//
//  GKAchievementNotification.h
//
//  Created by Benjamin Borowski on 9/30/10.
//  Copyright 2010 Typeoneerror Studios. All rights reserved.
//

#import <UIKit/UIKit.h>

#define kGKAchievementAnimeTime 0.4
#define kGKAchievementDisplayTime 1.75

@class GKAchievementNotification;

#pragma mark -

/**
 * The handler delegate responds to hiding and showing
 * of the game center notifications.
 */
@protocol GKAchievementHandlerDelegate <NSObject>

@optional

/**
 * Called on delegate when notification is hidden.
 * @param nofification  The notification view that was hidden.
 */
- (void)didHideAchievementNotification:(GKAchievementNotification *)notification;

/**
 * Called on delegate when notification is shown.
 * @param nofification  The notification view that was shown.
 */
- (void)didShowAchievementNotification:(GKAchievementNotification *)notification;

/**
 * Called on delegate when notification is about to be hidden.
 * @param nofification  The notification view that will be hidden.
 */
- (void)willHideAchievementNotification:(GKAchievementNotification *)notification;

/**
 * Called on delegate when notification is about to be shown.
 * @param nofification  The notification view that will be shown.
 */
- (void)willShowAchievementNotification:(GKAchievementNotification *)notification;

@end

#pragma mark -

/**
 * The GKAchievementNotification is a view for showing the achievement earned.
 */
@interface GKAchievementNotification : UIView
{
    GKAchievementDescription  *_achievement;  /**< Description of achievement earned. */

    NSString *_message;  /**< Optional custom achievement message. */
    NSString *_title;    /**< Optional custom achievement title. */

    UIImageView  *_background;  /**< Stretchable background view. */
    UIImageView  *_logo;        /**< Logo that is displayed on the left. */

    UILabel      *_textLabel;    /**< Text label used to display achievement title. */
    UILabel      *_detailLabel;  /**< Text label used to display achievement description. */

    id<GKAchievementHandlerDelegate> _handlerDelegate;  /**< Reference to nofification handler. */
}

/** Description of achievement earned. */
@property (nonatomic, retain) GKAchievementDescription *achievement;
/** Optional custom achievement message. */
@property (nonatomic, retain) NSString *message;
/** Optional custom achievement title. */
@property (nonatomic, retain) NSString *title;

/** Stretchable background view. */
@property (nonatomic, retain) UIImageView *background;
/** Logo that is displayed on the left. */
@property (nonatomic, retain) UIImageView *logo;
/** Text label used to display achievement title. */
@property (nonatomic, retain) UILabel *textLabel;
/** Text label used to display achievement description. */
@property (nonatomic, retain) UILabel *detailLabel;
/** Reference to nofification handler. */
@property (nonatomic, retain) id<GKAchievementHandlerDelegate> handlerDelegate;

#pragma mark -

/**
 * Create a notification with an achievement description.
 * @param achievement  Achievement description to notify user of earning.
 * @return a GKAchievementNoficiation view.
 */
- (id)initWithAchievementDescription:(GKAchievementDescription *)achievement;

/**
 * Create a notification with a custom title and description.
 * @param title    Title to display in notification.
 * @param message  Descriotion to display in notification.
 * @return a GKAchievementNoficiation view.
 */
- (id)initWithTitle:(NSString *)title andMessage:(NSString *)message;

/**
 * Создать уведомление с кастомным заголовком и без описания
 * @param title Заголовок уведомления
 */
- (id)initWithTitle:(NSString *)title;

/**
 * Show the notification.
 */
- (void)animateIn;

/**
 * Hide the notificaiton.
 */
- (void)animateOut;

/**
 * Change the logo that appears on the left.
 * @param image  The image to display.
 */
- (void)setImage:(UIImage *)image;

/**
 * Прямоугольник сообщения в позиции снаружи
 */
- (CGRect)frameOut;

/**
 * Рассчитать все позиции на основании размера экрана
 * @param frame размеры главного UIView
 */
+ (void)calcPositionsWithFrame:(CGRect)frame;
@end
