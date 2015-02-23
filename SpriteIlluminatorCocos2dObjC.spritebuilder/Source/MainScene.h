@interface MainScene : CCNode

@property (nonatomic, assign) CCSprite *pointLightCursor;
@property (nonatomic, assign) CCSprite *directionalLightCursor;
@property (nonatomic, assign) CCLightNode *lightNode;

@property (nonatomic, assign) CCParticleSystem *fireEmitter;
@property (nonatomic, assign) CCParticleSystem *snowEmitter;

@property (nonatomic, assign) CCNodeColor *background;

@property (nonatomic, assign) CCSprite *characterSprite;
@property (nonatomic, assign) CCSprite *characterWithoutLighting;

@end
