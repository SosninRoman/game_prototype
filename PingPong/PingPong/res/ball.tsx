<?xml version="1.0" encoding="UTF-8"?>
<tileset name="ball" tilewidth="32" tileheight="32" tilecount="8" columns="8">
 <image source="ball.png" width="256" height="32"/>
 <tile id="0">
  <objectgroup draworder="index" name="ball_animation"/>
  <animation>
   <frame tileid="0" duration="100"/>
   <frame tileid="1" duration="100"/>
   <frame tileid="2" duration="100"/>
   <frame tileid="3" duration="100"/>
   <frame tileid="4" duration="100"/>
   <frame tileid="5" duration="100"/>
   <frame tileid="6" duration="100"/>
   <frame tileid="7" duration="100"/>
  </animation>
 </tile>
 <tile id="1">
  <objectgroup draworder="index" name="ball_animation_back"/>
  <animation>
   <frame tileid="7" duration="100"/>
   <frame tileid="6" duration="100"/>
   <frame tileid="5" duration="100"/>
   <frame tileid="4" duration="100"/>
   <frame tileid="3" duration="100"/>
   <frame tileid="2" duration="100"/>
   <frame tileid="1" duration="100"/>
   <frame tileid="0" duration="100"/>
  </animation>
 </tile>
</tileset>
