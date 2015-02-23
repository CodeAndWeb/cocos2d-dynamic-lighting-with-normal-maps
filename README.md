# Dynamic Lighting Demo for Cocos2D with Normal Maps

This demo uses the same normal mapped sprite in different dynamic light scenarios.
The light source can be dragged do light the sprite from different angles.

#### Summer scene

* Bright yellow directional light
* Bright ambient light

![Normal Mapped Sprite with 2D Dynamic Lighting, Directional Light](images/normal-mapped-sprite-directional-light-1.png)

#### Winter scene

* Bright light blue directional light
* Bright light blue ambient light
* Snow particles (no light effect, just for the fun)

![Normal Mapped Sprite with 2D Dynamic Lighting, Directional Light and some Particles](images/normal-mapped-sprite-directional-light-2.png)

#### Point light scene

* White point light (restricted radius)
* Dark gray ambient light

![Normal Mapped Sprite with 2D Dynamic Lighting, Point Light Source](images/normal-mapped-sprite-point-light-1.png)

#### Camp fire scene

* Orange point light (restricted radius)
* Dark blue ambient light
* Fire particles (no light effect, just for the fun)
* Animated ligth source position (flickering)

![Normal Mapped Sprite with 2D Dynamic Lighting, Point Light, Fire Particle Emitter](images/normal-mapped-sprite-point-light-2.png)


All light effects are calculated in real time using Cocos2D's lighting system.


## Normal Maps

A normal mapped sprite consists of 2 files:

![Normal Mapped Sprite: Sprite's Texture](images/character-with-si-logo.png)
![Normal Mapped Sprite: Sprite's Normal Map](images/character-with-si-logo_n.png)

Generating a Normal Map for the sprite is easy using a [Normal Map Generator](https://www.codeandweb.com/normal-map-generator).

