import Foundation

class MainScene: CCNode
{
    var  pointLightCursor:CCSprite!
    var  directionalLightCursor:CCSprite!
    var  lightNode:CCLightNode!
    var  fireEmitter:CCParticleSystem!
    var  snowEmitter:CCParticleSystem!
    var  background:CCNodeColor!
    var  characterSprite:CCSprite!
    var  characterWithoutLighting:CCSprite!
    
    var nextFlicker:CCTime
    
    override init()
    {
        nextFlicker = 0.1
        super.init()
        self.userInteractionEnabled = true
    }
    
    override func onEnter()
    {
        noLightClicked()
        super.onEnter()
    }
    
    override func touchBegan(touch: CCTouch, withEvent event: CCTouchEvent)
    {
        // touch moved only works with touchBegan present
    }
    
    override func touchMoved(touch: CCTouch!, withEvent event: CCTouchEvent!)
    {
        var touchLocation = touch.locationInNode(self)
        
        // calculate angle for the directional light
        var vector = ccpSub(touchLocation, characterSprite.position)
        var angle = Float(Double(ccpToAngle(vector)) * 180.0 / M_PI)
        lightNode.rotation = 90 - angle
        directionalLightCursor.rotation = 180 - angle
        
        // set positions for light and emitters
        pointLightCursor.position = touchLocation
        lightNode.position = touchLocation
        fireEmitter.position = touchLocation
    }
    
    func showFire(show:Bool)
    {
        if (show)
        {
            fireEmitter.resetSystem()
        }
        else
        {
            fireEmitter.stopSystem()
        }
        fireEmitter.visible = show
    }
    
    func showSnow(show:Bool)
    {
        if (show)
        {
            snowEmitter.resetSystem()
        }
        else
        {
            snowEmitter.stopSystem()
        }
        snowEmitter.visible = show
    }
    
    func pointLightClicked()
    {
        // black background
        background.color = CCColor(red: 0.0, green: 0.0, blue: 0.0)
        
        // white point light with gray ambient light
        lightNode.color = CCColor(red: 1.0, green: 1.0, blue: 1.0)
        lightNode.ambientColor = CCColor(red: 0.5, green: 0.5, blue: 0.5)
        lightNode.type = CCLightType.Point
        lightNode.position  = ccp(400, 260)
        pointLightCursor.position = lightNode.position
        
        pointLightCursor.visible = true
        directionalLightCursor.visible = false
        characterWithoutLighting.visible = false
        characterSprite.visible = true
        
        showFire(false)
        showSnow(false)
    }
    
    func fireClicked()
    {
        // black background
        background.color = CCColor(red: 0.0, green: 0.0, blue: 0.0)
        
        // orange light
        // dark blue ambient light
        // animated in update:
        lightNode.color = CCColor(red: 1.0, green: 0.5, blue: 0.5)
        lightNode.ambientColor = CCColor(red: 0.4, green: 0.4, blue: 0.8)
        lightNode.type = CCLightType.Point
        lightNode.position = ccp(400, 60)
        fireEmitter.position = lightNode.position
        
        pointLightCursor.visible = false
        directionalLightCursor.visible = false
        
        characterWithoutLighting.visible = false
        characterSprite.visible = true
        
        showFire(true)
        showSnow(false)
    }
    
    func summerClicked()
    {
        // green background
        background.color = CCColor(red: 0.6, green: 0.8, blue: 0.6)
        
        // bright light with a touch of warm yello
        lightNode.color = CCColor(red: 1.0, green: 1.0, blue: 0.8)
        lightNode.ambientColor = CCColor(red: 0.8, green: 0.8, blue: 0.8)
        lightNode.type = CCLightType.Directional
        lightNode.depth = 1.0
        lightNode.rotation = 0
        
        pointLightCursor.visible = false
        directionalLightCursor.visible = true
        characterWithoutLighting.visible = false
        characterSprite.visible = true
        
        showFire(false)
        showSnow(false)
    }
    
    func winterClicked()
    {
        // cold blue background
        background.color = CCColor(red: 0.5, green: 0.7, blue: 1.0)
        
        // bright light, with some icy blue
        lightNode.color = CCColor(red: 0.7, green: 0.9, blue: 1.0)
        lightNode.ambientColor = CCColor(red: 0.6, green: 0.7, blue: 1.0)
        lightNode.type = CCLightType.Directional
        lightNode.depth = 1.0
        lightNode.rotation = 0;
        
        pointLightCursor.visible = false
        directionalLightCursor.visible = true
        characterWithoutLighting.visible = false
        characterSprite.visible = true
        
        showFire(false)
        showSnow(true)
    }
    
    func noLightClicked()
    {
        // dark blue background, no light set on this sprite
        background.color = CCColor(red: 0.1, green: 0.1, blue: 0.3)
        
        characterWithoutLighting.visible = true
        characterSprite.visible = false
        pointLightCursor.visible = false
        directionalLightCursor.visible = false
        
        showFire(false)
        showSnow(false)
    }
    
    override func update(delta: CCTime)
    {
        if(fireEmitter.visible)
        {
            nextFlicker -= delta
            if(nextFlicker < 0)
            {
                nextFlicker = 0.1
                // choose random position for light node
                // close to fire emmitter
                lightNode.position = ccpAdd(fireEmitter.position, CGPoint(x: rand() % 30 - 15, y:rand() % 30 - 15))
            }
        }
    }
}
