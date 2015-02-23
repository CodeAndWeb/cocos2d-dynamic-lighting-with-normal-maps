# Dynamic Lighting Demo for Cocos2D with Normal Maps

This demo uses the same normal mapped sprite in different dynamic light scenarios.
The light source can be dragged do light the sprite from different angles.

<div>
<div style="width:300px; float:left">
<img src="images/normal-mapped-sprite-directional-light-1.png" style="width:100%" alt="Normal Mapped Sprite with 2D Dynamic Lighting, Directional Light"/>
<div style="text-align:center">Summer (Directional Light)</div>
</div>
<div style="width:300px; float:left">
<img src="images/normal-mapped-sprite-directional-light-2.png" style="width:100%" alt="Normal Mapped Sprite with 2D Dynamic Lighting, Directional Light and some Particles"/>
<div style="text-align:center">Winter (Directional Light + Particles)</div>
</div>
<div style="clear:both"/>
</div>

<div>
<div style="width:300px; float:left">
<img src="images/normal-mapped-sprite-point-light-1.png" style="width:100%" alt="Normal Mapped Sprite with 2D Dynamic Lighting, Point Light Source"/>
<div style="text-align:center">Simple Point Light</div>
</div>
<div style="width:300px; float:left">
<img src="images/normal-mapped-sprite-point-light-2.png" style="width:100%" alt="Normal Mapped Sprite with 2D Dynamic Lighting, Point Light, Fire Particle Emitter"/>
<div style="text-align:center">Campfire (Point Light + Particles)</div>
</div>
<div style="clear:both"/>
</div>


All light effects are calculated in real time using Cocos2D's lighting system.

## Normal Maps

A normal mapped sprite consists of 2 files:

<div>
<div style="width:200px; float:left">
<img src="images/character-with-si-logo.png" style="width:100%" alt="Normal Mapped Sprite: Sprite's Texture"/>
<div style="text-align:center">Sprite's Texture</div>
</div>
<div style="width:200px; float:left">
<img src="images/character-with-si-logo_n.png" style="width:100%" alt="Normal Mapped Sprite: Sprite's Normal Map"/>
<div style="text-align:center">Sprite's Normal map</div>
</div>
<div style="clear:both"/>
</div>

Generating a Normal Map for the sprite is easy using a [Normal Map Generator](https://www.codeandweb.com/normal-map-generator).
