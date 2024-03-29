//-----------------------------------------------------------------------------
// Torque Game Engine
// Copyright (C) GarageGames.com, Inc.
//-----------------------------------------------------------------------------

#include "platformWin32/platformWin32.h"
#include "console/console.h"

#include "al/altypes.h"
#include "al/alctypes.h"
#define INITGUID
#include "al/eaxtypes.h"


// Define the OpenAL and Extension Stub functions
#define AL_FUNCTION(fn_return, fn_name, fn_args, fn_value) fn_return stub_##fn_name fn_args{ fn_value }
#include "al/al_func.h"
#include "al/alc_func.h"
#include "al/eax_func.h"
#undef AL_FUNCTION


// Declare the OpenAL and Extension Function pointers
// And initialize them to the stub functions
#define AL_FUNCTION(fn_return,fn_name,fn_args, fn_value) fn_return (*fn_name)fn_args = stub_##fn_name;
#include "al/al_func.h"
#include "al/alc_func.h"
#include "al/eax_func.h"
#undef AL_FUNCTION


/*!   Get a function address from the OpenAL DLL and bind it to the
*     function pointer
*/
static bool bindFunction( void *&fnAddress, const char *name )
{
   // JMQ: MinGW gcc 3.2 needs the cast to void*
   fnAddress = (void*)(GetProcAddress( winState.hinstOpenAL, name ));
   if( !fnAddress )
      Con::errorf(ConsoleLogEntry::General, " Missing OpenAL function '%s'", name);
   return (fnAddress != NULL);
}

/*!   Get a function address for an OpenAL extension function and bind it
*     to it's function pointer
*/
static bool bindExtensionFunction( void *&fnAddress, const char *name )
{
   fnAddress = alGetProcAddress( (ALubyte*)name );
   if( !fnAddress )
      Con::errorf(ConsoleLogEntry::General, " Missing OpenAL Extension function '%s'", name);
   return (fnAddress != NULL);
}

/*!   Bind the functions in the OpenAL DLL to the al interface functions
*/
static bool bindOpenALFunctions()
{
   bool result = true;
   #define AL_FUNCTION(fn_return, fn_name, fn_args, fn_value) result &= bindFunction( *(void**)&fn_name, #fn_name);
   #include "al/al_func.h"
   #include "al/alc_func.h"
   #undef AL_FUNCTION
   return result;
}

/*!   Bind the stub functions to the al interface functions
*/
static void unbindOpenALFunctions()
{
   #define AL_FUNCTION(fn_return, fn_name, fn_args, fn_value) fn_name = stub_##fn_name;
   #include "al/al_func.h"
   #include "al/alc_func.h"
   #include "al/eax_func.h"
   #undef AL_FUNCTION
}

/*!   Bind the EAX Extension functions to the EAX interface functions
*/
static bool bindEAXFunctions()
{
   bool result = true;
   #define AL_FUNCTION(fn_return, fn_name, fn_args, fn_value) result &= bindExtensionFunction( *(void**)&fn_name, #fn_name);
   #include "al/eax_func.h"
   #undef AL_FUNCTION
   return result;
}



namespace Audio
{

/*!   Shutdown and Unload the OpenAL DLL
*/
void OpenALDLLShutdown()
{
   if (winState.hinstOpenAL)
      FreeLibrary(winState.hinstOpenAL);
   winState.hinstOpenAL = NULL;

   unbindOpenALFunctions();
}

/*!   Dynamically Loads the OpenAL DLL if present and binds all the functions.
*     If there is no DLL or an unexpected error occurs binding functions the
*     stub functions are automatically bound.
*/
bool OpenALDLLInit()
{
   OpenALDLLShutdown();

   winState.hinstOpenAL = LoadLibrary( dT("OpenAl32.dll") );
   if(winState.hinstOpenAL != NULL)
   {
      // if the DLL loaded bind the OpenAL function pointers
      if(bindOpenALFunctions())
      {
         // if EAX is available bind it's function pointers
         //if (alIsExtensionPresent((ALubyte*)"EAX" ))
            bindEAXFunctions();
         return(true);
      }

      // an error occured, shutdown
      OpenALDLLShutdown();
   }
   return(false);
}

} // end namespace Audio
