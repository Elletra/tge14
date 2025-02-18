// MAIN.CS
//
// This script is the first to execute when the exporter program starts.
//
// COPYRIGHT (C) 2004 BY
// DAVID WYAND.
// AJAX, ONTARIO
// CANADA
//
// PORTIONS COPYRIGHT (C) BY GarageGames.com, Inc.
//
// This software is furnished under a license and may be
// used  and copied only in accordance with the terms of
// such license and with  the  inclusion  of  the  above
// copyright  notice.  This software or any other copies
// thereof  may  not  be  provided  or  otherwise   made
// available  to  any  other  person.   No  title to and
// ownership of the software is hereby transferred.
//
// Revision History:
// November 18, 2003	David Wyand		Created file from original TGE main.cs
//

//*** Globals
$baseMods   = "tstpro/common";
$userMods   = "tstpro/exporter";
$displayHelp = false;


//************************************************************************************
//*** Support functions used to manage the mod string
//************************************************************************************

function pushFront(%list, %token, %delim)
{
   if (%list !$= "")
      return %token @ %delim @ %list;
   return %token;
}

function pushBack(%list, %token, %delim)
{
   if (%list !$= "")
      return %list @ %delim @ %token;
   return %token;
}

function popFront(%list, %delim)
{
   return nextToken(%list, unused, %delim);
}


//************************************************************************************
//*** Process command line arguments
//************************************************************************************

for ($i = 1; $i < $Game::argc ; $i++)
{
   $arg = $Game::argv[$i];
   $nextArg = $Game::argv[$i+1];
   $hasNextArg = $Game::argc - $i > 1;
   $logModeSpecified = false;
   
   switch$ ($arg)
   {
      //--------------------
      case "-log":
         $argUsed[$i]++;
         if ($hasNextArg)
         {
            // Turn on console logging
            if ($nextArg != 0)
            {
               // Dump existing console to logfile first.
               $nextArg += 4;
            }
            setLogMode($nextArg);
            $logModeSpecified = true;
            $argUsed[$i+1]++;
            $i++;
         }
         else
            error("Error: Missing Command Line argument. Usage: -log <Mode: 0,1,2>");

      //--------------------
      case "-mod":
         $argUsed[$i]++;
         if ($hasNextArg)
         {
            // Append the mod to the end of the current list
            $userMods = strreplace($userMods, $nextArg, "");
            $userMods = pushFront($userMods, $nextArg, ";");
            $argUsed[$i+1]++;
            $i++;
         }
         else
            error("Error: Missing Command Line argument. Usage: -mod <mod_name>");
            
      //--------------------
      case "-game":
         $argUsed[$i]++;
         if ($hasNextArg)
         {
            // Remove all mods, start over with game
            $userMods = $nextArg;
            $argUsed[$i+1]++;
            $i++;
         }
         else
            error("Error: Missing Command Line argument. Usage: -game <game_name>");
            
      //--------------------
      case "-show":
         // A useful shortcut for -mod show
         $userMods = strreplace($userMods, "show", "");
         $userMods = pushFront($userMods, "show", ";");
         $argUsed[$i]++;

      //--------------------
      case "-console":
         enableWinConsole(true);
         $argUsed[$i]++;

      //--------------------
      case "-jSave":
         $argUsed[$i]++;
         if ($hasNextArg)
         {
            echo("Saving event log to journal: " @ $nextArg);
            saveJournal($nextArg);
            $argUsed[$i+1]++;
            $i++;
         }
         else
            error("Error: Missing Command Line argument. Usage: -jSave <journal_name>");

      //--------------------
      case "-jPlay":
         $argUsed[$i]++;
         if ($hasNextArg)
         {
            playJournal($nextArg,false);
            $argUsed[$i+1]++;
            $i++;
         }
         else
            error("Error: Missing Command Line argument. Usage: -jPlay <journal_name>");

      //--------------------
      case "-jDebug":
         $argUsed[$i]++;
         if ($hasNextArg)
         {
            playJournal($nextArg,true);
            $argUsed[$i+1]++;
            $i++;
         }
         else
            error("Error: Missing Command Line argument. Usage: -jDebug <journal_name>");

      //-------------------
      case "-help":
         $displayHelp = true;
         $argUsed[$i]++;
   }
}


//************************************************************************************
//*** The displayHelp, onStart, onExit and parseArgs function are overriden
//*** by mod packages to get hooked into initialization and cleanup. 
//************************************************************************************

function onStart()
{
   // Default startup function.  Invoked at the end of this file.
}

function onExit()
{
   // OnExit is called directly from C++ code, whereas onStart is
   // invoked at the end of this file.
}

function parseArgs()
{
   // Here for mod override, the arguments have already
   // been parsed.
}   

package Help {
   function onExit() {
      // Override onExit when displaying help
   }
};

function displayHelp() {
   activatePackage(Help);

      // Notes on logmode: console logging is written to console.log.
      // -log 0 disables console logging.
      // -log 1 appends to existing logfile; it also closes the file
      // (flushing the write buffer) after every write.
      // -log 2 overwrites any existing logfile; it also only closes
      // the logfile when the application shuts down.  (default)

   error(
      "Torque Demo command line options:\n"@
      "  -log <logmode>         Logging behavior; see main.cs comments for details\n"@
      "  -game <game_name>      Reset list of mods to only contain <game_name>\n"@
      "  -mod <mod_name>        Add <mod_name> to list of mods\n"@
      "  -console               Open a separate console\n"@
      "  -show <shape>          Launch the TS show tool\n"@
      "  -jSave  <file_name>    Record a journal\n"@
      "  -jPlay  <file_name>    Play back a journal\n"@
      "  -jDebug <file_name>    Play back a journal and issue an int3 at the end\n"@
      "  -help                  Display this help message\n"
   );
}


//************************************************************************************

//*** Default to a new logfile each session.
if (!$logModeSpecified) {
   setLogMode(6);
}

//*** Set the mod path which dictates which directories will be visible
//*** to the scripts and the resource engine.
$modPath = pushback($userMods, $baseMods, ";");
setModPaths($modPath);

//*** Get the first mod on the list, which will be the last to be applied... this
//*** does not modify the list.
nextToken($modPath, currentMod, ";");

//*** Execute startup scripts for each mod, starting at base and working up
echo("--------- ROOT MAIN.CS: Loading MODS ---------");
function loadMods(%modPath)
{
   %modPath = nextToken(%modPath, token, ";");
   if (%modPath !$= "")
      loadMods(%modPath);

   //*** Execute the MOD's main.cs here
   exec(%token @ "/main.cs");
}
loadMods($modPath);
echo("--------- ROOT MAIN.CS: Loading MODS Complete ---------");

//*** Parse the command line arguments
echo("--------- ROOT MAIN.CS: Parsing Arguments ---------");
parseArgs();

//** Either display the help message or startup the app.
if ($displayHelp) {
   enableWinConsole(true);
   displayHelp();
   quit();
}
else {
   echo("--------- ROOT MAIN.CS: Starting up ---------");
   onStart();
   echo("--------- ROOT MAIN.CS: Engine initialized ---------");
}

//*** Display an error message for unused arguments
for ($i = 1; $i < $Game::argc; $i++)  {
   if (!$argUsed[$i])
      error("Error: Unknown command line argument: " @ $Game::argv[$i]);
}
