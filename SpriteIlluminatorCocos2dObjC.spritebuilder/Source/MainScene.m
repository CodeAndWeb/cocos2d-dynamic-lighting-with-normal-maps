/**
 * SpriteIlluminator Demo for Cocos2D
 *
 * Written by Andreas Loew / CodeAndWeb GmbH
 * 
 * This demo shows different 2d dynamic lighting scenarios with a single sprite.
 * The sprite's normal map was created using SpriteIlluminator
 * https://www.codeandweb.com/spriteilluminator
 *
 */
#import "MainScene.h"

@implementation MainScene
{
    CCTime nextFlicker;
}

- (id)init
{
    if (self = [super init])
    {
        self.userInteractionEnabled = TRUE;
        nextFlicker = 0.1;
    }

    return self;
}

-(void) onEnter
{
    // start with default screen
    [self noLightClicked];
    [super onEnter];
}

-(void)touchBegan:(CCTouch *)touch withEvent:(CCTouchEvent *)event
{
    // touch moved only works with touchBegan present
}

- (void)touchMoved:(CCTouch *)touch withEvent:(CCTouchEvent *)event
{
    CGPoint touchLocation = [touch locationInNode:self];
    
    // calculate angle for the directional light
    CGPoint vector = ccpSub(touchLocation,_characterSprite.position);
    float angle = ccpToAngle(vector) * 180.0f /  M_PI;
    _lightNode.rotation = 90-angle;
    _directionalLightCursor.rotation = 180-angle;

    // set positions for light and emitters
    _pointLightCursor.position = _lightNode.position = _fireEmitter.position = touchLocation;
}

-(void) showFire:(BOOL)show
{
    if(show)
    {
        [_fireEmitter resetSystem];
    }
    else
    {
        [_fireEmitter stopSystem];
    }
    
    [_fireEmitter setVisible: show];
}


-(void) showSnow:(BOOL)show
{
    if(show)
    {
        [_snowEmitter resetSystem];
    }
    else
    {
        [_snowEmitter stopSystem];
    }
    [_snowEmitter setVisible: show];
}


-(void) pointLightClicked
{
    // black background
    _background.color = [CCColor colorWithRed:0.0f green:0.0f blue:0.0f];

    // white point light with gray ambient light
    _lightNode.color = [CCColor colorWithRed:1.0f green:1.0f blue:1.0f];
    _lightNode.ambientColor = [CCColor colorWithRed:0.5f green:0.5f blue:0.5f];
    _lightNode.type = CCLightPoint;
    _lightNode.position =_pointLightCursor.position = ccp(400,260);
    
    _pointLightCursor.visible = TRUE;
    _directionalLightCursor.visible = FALSE;
    _characterWithoutLighting.visible = FALSE;
    _characterSprite.visible = TRUE;
    
    [self showFire:NO];
    [self showSnow:NO];
}

-(void) fireClicked
{
    // black background
    _background.color = [CCColor colorWithRed:0.0f green:0.0f blue:0.0f];

    // orange light
    // dark blue ambient light
    // animated in update:
    _lightNode.color = [CCColor colorWithRed:1.0f green:0.5f blue:0.5f];
    _lightNode.ambientColor = [CCColor colorWithRed:0.4f green:0.4f blue:0.8f];
    _lightNode.type = CCLightPoint;
    _lightNode.position = _fireEmitter.position = ccp(400,60);
    
    _pointLightCursor.visible = FALSE;
    _directionalLightCursor.visible = FALSE;
    _characterWithoutLighting.visible = FALSE;
    _characterSprite.visible = TRUE;

    [self showFire:YES];
    [self showSnow:NO];
}

-(void) summerClicked
{
    // green background
    _background.color = [CCColor colorWithRed:0.6f green:0.8f blue:0.6f];

    // bright light with a touch of warm yello
    _lightNode.color = [CCColor colorWithRed:1.0f green:1.0f blue:0.8f];
    _lightNode.ambientColor = [CCColor colorWithRed:0.8f green:0.8f blue:0.8f];
    _lightNode.type = CCLightDirectional;
    _lightNode.depth = 1.0;
    _lightNode.rotation = 0;
    
    _pointLightCursor.visible = FALSE;
    _directionalLightCursor.visible = TRUE;
    _characterWithoutLighting.visible = FALSE;
    _characterSprite.visible = TRUE;

    [self showFire:NO];
    [self showSnow:NO];
}

-(void) winterClicked
{
    // cold blue background
    _background.color = [CCColor colorWithRed:0.5f green:0.7f blue:1.0f];

    // bright light, with some icy blue
    _lightNode.color = [CCColor colorWithRed:0.7f green:0.9f blue:1.0f];
    _lightNode.ambientColor = [CCColor colorWithRed:0.6f green:0.7f blue:1.0f];
    _lightNode.type = CCLightDirectional;
    _lightNode.depth = 1.0;
    _lightNode.rotation = 0;
    
    _pointLightCursor.visible = FALSE;
    _directionalLightCursor.visible = TRUE;
    _characterWithoutLighting.visible = FALSE;
    _characterSprite.visible = TRUE;
    
    [self showFire:NO];
    [self showSnow:YES];
}

-(void) noLightClicked
{
    // dark blue background, no light set on this sprite
    _background.color = [CCColor colorWithRed:0.1f green:0.1f blue:0.3f];

    _characterWithoutLighting.visible = TRUE;
    _characterSprite.visible = FALSE;
    _pointLightCursor.visible = FALSE;
    _directionalLightCursor.visible = FALSE;

    [self showFire:NO];
    [self showSnow:NO];
}

-(void) update:(CCTime)delta
{
    if(_fireEmitter.visible)
    {
        nextFlicker -= delta;
        if(nextFlicker < 0)
        {
            nextFlicker = 0.1;
            // choose random position for light node
            // close to fire emmitter
            _lightNode.position = ccpAdd(_fireEmitter.position, ccp(rand() % 30 - 15, rand() % 30 - 15));
        }
    }
}

@end
