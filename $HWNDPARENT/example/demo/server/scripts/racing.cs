//-----------------------------------------------------------------------------
// Torque Game Engine 
// Copyright (C) GarageGames.com, Inc.
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//  Functions that implement game-play
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------

package RacingGame {

//-----------------------------------------------------------------------------

function GameConnection::onClientEnterGame(%this)
{
   commandToClient(%this, 'SyncClock', $Sim::Time - $Game::StartTime);
   commandToClient(%this, 'SetGameGUI',"RacingGUI");

   // Create a new camera object.
   %this.camera = new Camera() {
      dataBlock = Observer;
   };
   MissionCleanup.add( %this.camera );
   %this.camera.scopeToClient(%this);

   // Spawn the player
   %this.score = 0;
   %this.spawnPlayer();
}

//-----------------------------------------------------------------------------

function GameConnection::createPlayer(%this, %spawnPoint)
{
   if (%this.player > 0)  {
      // The client should not have a player currently
      // assigned.  Assigning a new one could result in 
      // a player ghost.
      error( "Attempting to create an angus ghost!" );
   }

   %player = new WheeledVehicle() {
      dataBlock = DefaultCar;
      client = %this;
   };

   MissionCleanup.add(%player);

   // Car setup...
   %player.setTransform(%spawnPoint);
   %player.setShapeName(%this.name);
   
   // Update the camera to start with the car
   %this.camera.setTransform(%player.getEyeTransform());

   // Give the client control of the car
   %this.player = %player;
   %this.setControlObject(%player);
}


//-----------------------------------------------------------------------------

function serverCmdSuicide(%client)
{
   if (isObject(%client.player)) {
      %client.player.delete();
      %client.player = 0;
   }
   %client.spawnPlayer();
}

};