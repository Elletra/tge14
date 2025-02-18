//-----------------------------------------------------------------------------
// Torque Game Engine
// Copyright (C) GarageGames.com, Inc.
//-----------------------------------------------------------------------------

#ifndef _CONSOLE_H_
#define _CONSOLE_H_

#ifndef _PLATFORM_H_
#include "platform/platform.h"
#endif
#ifndef _BITSET_H_
#include "core/bitSet.h"
#endif
#include <stdarg.h>

class SimObject;
struct EnumTable;
class Namespace;

/// Indicates that warnings about undefined script variables should be displayed.
///
/// @note This is set and controlled by script.
extern bool gWarnUndefinedScriptVariables;

enum StringTableConstants
{
   StringTagPrefixByte = 0x01 ///< Magic value prefixed to tagged strings.
};

/// Represents an entry in the log.
struct ConsoleLogEntry
{
   /// This field indicates the severity of the log entry.
   ///
   /// Log entries are filtered and displayed differently based on
   /// their severity. Errors are highlighted red, while normal entries
   /// are displayed as normal text. Often times, the engine will be
   /// configured to hide all log entries except warnings or errors,
   /// or to perform a special notification when it encounters an error.
   enum Level
   {
      Normal = 0,
      Warning,
      Error,
      NUM_CLASS
   } mLevel;

   /// Used to associate a log entry with a module.
   ///
   /// Log entries can come from different sources; for instance,
   /// the scripting engine, or the network code. This allows the
   /// logging system to be aware of where different log entries
   /// originated from.
   enum Type
   {
      General = 0,
      Assert,
      Script,
      GUI,
      Network,
      NUM_TYPE
   } mType;

   /// Indicates the actual log entry.
   ///
   /// This contains a description of the event being logged.
   /// For instance, "unable to access file", or "player connected
   /// successfully", or nearly anything else you might imagine.
   ///
   /// Typically, the description should contain a concise, descriptive
   /// string describing whatever is being logged. Whenever possible,
   /// include useful details like the name of the file being accessed,
   /// or the id of the player or GuiControl, so that if a log needs
   /// to be used to locate a bug, it can be done as painlessly as
   /// possible.
   const char *mString;
};

/// Scripting engine representation of an enum.
///
/// This data structure is used by the scripting engine
/// to expose enumerations to the scripting language. It
/// acts to relate named constants to integer values, just
/// like an enum in C++.
struct EnumTable
{
   /// Number of enumerated items in the table.
   S32 size;

   /// This represents a specific item in the enumeration.
   struct Enums
   {
      S32 index;        ///< Index label maps to.
      const char *label;///< Label for this index.
   };

   Enums *table;

   /// Constructor.
   ///
   /// This sets up the EnumTable with predefined data.
   ///
   /// @param sSize  Size of the table.
   /// @param sTable Pointer to table of Enums.
   ///
   /// @see gLiquidTypeTable
   /// @see gAlignTable
   EnumTable(S32 sSize, Enums *sTable)
      { size = sSize; table = sTable; }
};

typedef const char *StringTableEntry;

/// @defgroup console_callbacks Scripting Engine Callbacks
///
/// The scripting engine makes heavy use of callbacks to represent
/// function exposed to the scripting language. StringCallback,
/// IntCallback, FloatCallback, VoidCallback, and BoolCallback all
/// represent exposed script functions returning different types.
///
/// ConsumerCallback is used with the function Con::addConsumer; functions
/// registered with Con::addConsumer are called whenever something is outputted
/// to the console. For instance, the TelnetConsole registers itself with the
/// console so it can echo the console over the network.
///
/// @note Callbacks to the scripting language - for instance, onExit(), which is
///       a script function called when the engine is shutting down - are handled
///       using Con::executef() and kin.
/// @{

///
typedef const char * (*StringCallback)(SimObject *obj, S32 argc, const char *argv[]);
typedef S32             (*IntCallback)(SimObject *obj, S32 argc, const char *argv[]);
typedef F32           (*FloatCallback)(SimObject *obj, S32 argc, const char *argv[]);
typedef void           (*VoidCallback)(SimObject *obj, S32 argc, const char *argv[]); // We have it return a value so things don't break..
typedef bool           (*BoolCallback)(SimObject *obj, S32 argc, const char *argv[]);

typedef void (*ConsumerCallback)(ConsoleLogEntry::Level level, const char *consoleLine);
/// @}

/// @defgroup console_types Scripting Engine Type Functions
///
/// @see Con::registerType
/// @{
typedef const char* (*GetDataFunction)(void *dptr, EnumTable *tbl, BitSet32 flag);
typedef void        (*SetDataFunction)(void *dptr, S32 argc, const char **argv, EnumTable *tbl, BitSet32 flag);
/// @}

/// This namespace contains the core of the console functionality.
///
/// @section con_intro Introduction
///
/// The console is a key part of Torque's architecture. It allows direct run-time control
/// of many aspects of the engine.
///
/// @nosubgrouping
namespace Con
{
   /// Various configuration constants.
   enum Constants 
   {
      /// This is the version number associated with DSO files.
      ///
      /// If you make any changes to the way the scripting language works
      /// (such as DSO format changes, adding/removing op-codes) that would
      /// break compatibility, then you should increment this.
      ///
      /// If you make a really major change, increment it to the next multiple
      /// of ten.
      ///
      /// 12/29/04 - BJG - 33->34 Removed some opcodes, part of namespace upgrade.
      /// 12/30/04 - BJG - 34->35 Reordered some things, further general shuffling.
      /// 11/03/05 - BJG - 35->36 Integrated new debugger code.
      DSOVersion = 36,

      MaxLineLength = 512,  ///< Maximum length of a line of console input.
      MaxDataTypes = 256    ///< Maximum number of registered data types.
   };

   /// @name Control Functions
   ///
   /// The console must be initialized and shutdown appropriately during the
   /// lifetime of the app. These functions are used to manage this behavior.
   ///
   /// @note Torque deals with this aspect of console management, so you don't need
   ///       to call these functions in normal usage of the engine.
   /// @{

   /// Initializes the console.
   ///
   /// This performs the following steps:
   ///   - Calls Namespace::init() to initialize the scripting namespace hierarchy.
   ///   - Calls ConsoleConstructor::setup() to initialize globally defined console
   ///     methods and functions.
   ///   - Registers some basic global script variables.
   ///   - Calls AbstractClassRep::init() to initialize Torque's class database.
   ///   - Registers some basic global script functions that couldn't usefully
   ///     be defined anywhere else.
   void init();

   /// Shuts down the console.
   ///
   /// This performs the following steps:
   ///   - Closes the console log file.
   ///   - Calls Namespace::shutdown() to shut down the scripting namespace hierarchy.
   void shutdown();

   /// Is the console active at this time?
   bool isActive();

   /// @}

   /// @name Console Consumers
   ///
   /// The console distributes its output through Torque by using
   /// consumers. Every time a new line is printed to the console,
   /// all the ConsumerCallbacks registered using addConsumer are
   /// called, in order.
   ///
   /// @note The GuiConsole control, which provides the on-screen
   ///       in-game console, uses a different technique to render
   ///       the console. It calls getLockLog() to lock the Vector
   ///       of on-screen console entries, then it renders them as
   ///       needed. While the Vector is locked, the console will
   ///       not change the Vector. When the GuiConsole control is
   ///       done with the console entries, it calls unlockLog()
   ///       to tell the console that it is again safe to modify
   ///       the Vector.
   ///
   /// @see TelnetConsole
   /// @see TelnetDebugger
   /// @see WinConsole
   /// @see MacCarbConsole
   /// @see StdConsole
   /// @see ConsoleLogger
   ///
   /// @{
   void addConsumer(ConsumerCallback cb);
   void removeConsumer(ConsumerCallback cb);
   /// @}

   /// @name Miscellaneous
   /// @{

   /// Remove color marking information from a string.
   ///
   /// @note It does this in-place, so be careful! It may
   ///       potentially blast data if you're not careful.
   ///       When in doubt, make a copy of the string first.
   void stripColorChars(char* line);

   /// Convert from a relative script path to an absolute script path.
   ///
   /// This is used in (among other places) the exec() script function, which
   /// takes a parameter indicating a script file and executes it. Script paths
   /// can be one of:
   ///      - <b>Absolute:</b> <i>fps/foo/bar.cs</i> Paths of this sort are passed
   ///        through.
   ///      - <b>Mod-relative:</b> <i>~/foo/bar.cs</i> Paths of this sort have their
   ///        replaced with the name of the current mod.
   ///      - <b>File-relative:</b> <i>./baz/blip.cs</i> Paths of this sort are
   ///        calculated relative to the path of the current scripting file.
   ///
   /// @note This function determines paths relative to the currently executing
   ///       CodeBlock. Calling it outside of script execution will result in
   ///       it directly copying src to filename, since it won't know to what the
   ///       path is relative!
   ///
   /// @param  filename    Pointer to string buffer to fill with absolute path.
   /// @param  size        Size of buffer pointed to by filename.
   /// @param  src         Original, possibly relative script path.
   bool expandScriptFilename(char *filename, U32 size, const char *src);

   /// Returns true if fn is a global scripting function.
   ///
   /// This looks in the global namespace. It also checks to see if fn
   /// is in the StringTable; if not, it returns false.
   bool isFunction(const char *fn);

   /// This is the basis for tab completion in the console.
   ///
   /// @note This is an internally used function. You probably don't
   ///       care much about how this works.
   ///
   /// This function does some basic parsing to try to ascertain the namespace in which
   /// we are attempting to do tab completion, then bumps control off to the appropriate
   /// tabComplete function, either in SimObject or Namespace.
   ///
   /// @param  inputBuffer     Pointer to buffer containing starting data, or last result.
   /// @param  cursorPos       Location of cursor in this buffer. This is used to indicate
   ///                         what part of the string should be kept and what part should
   ///                         be advanced to the next match if any.
   /// @param  maxResultLength Maximum amount of result data to put into inputBuffer. This
   ///                         is capped by MaxCompletionBufferSize.
   /// @param  forwardTab      Should we go forward to next match or backwards to previous
   ///                         match? True indicates forward.
   U32 tabComplete(char* inputBuffer, U32 cursorPos, U32 maxResultLength, bool forwardTab);

   /// @}


   /// @name Variable Management
   /// @{

   /// Add a console variable that references the value of a variable in C++ code.
   ///
   /// If a value is assigned to the console variable the C++ variable is updated,
   /// and vice-versa.
   ///
   /// @param name    Global console variable name to create
   /// @param type    The type of the C++ variable; see the ConsoleDynamicTypes enum for a complete list.
   /// @param pointer Pointer to the variable.
   /// @see ConsoleDynamicTypes
   bool addVariable(const char *name, S32 type, void *pointer);

   /// Remove a console variable.
   ///
   /// @param name   Global console variable name to remove
   /// @return       true if variable existed before removal.
   bool removeVariable(const char *name);

   /// Assign a string value to a locally scoped console variable
   ///
   /// @note The context of the variable is determined by gEvalState; that is,
   ///       by the currently executing code.
   ///
   /// @param name   Local console variable name to set
   /// @param value  String value to assign to name
   void setLocalVariable(const char *name, const char *value);

   /// Retrieve the string value to a locally scoped console variable
   ///
   /// @note The context of the variable is determined by gEvalState; that is,
   ///       by the currently executing code.
   ///
   /// @param name   Local console variable name to get
   const char* getLocalVariable(const char* name);

   /// @}

   /// @name Global Variable Accessors
   /// @{
   /// Assign a string value to a global console variable
   /// @param name   Global console variable name to set
   /// @param value  String value to assign to this variable.
   void setVariable(const char *name, const char *value);

   /// Retrieve the string value of a global console variable
   /// @param name   Global Console variable name to query
   /// @return       The string value of the variable or "" if the variable does not exist.
   const char* getVariable(const char* name);

   /// Same as setVariable(), but for bools.
   void setBoolVariable (const char* name,bool var);

   /// Same as getVariable(), but for bools.
   ///
   /// @param  name  Name of the variable.
   /// @param  def   Default value to supply if no matching variable is found.
   bool getBoolVariable (const char* name,bool def = false);

   /// Same as setVariable(), but for ints.
   void setIntVariable  (const char* name,S32 var);

   /// Same as getVariable(), but for ints.
   ///
   /// @param  name  Name of the variable.
   /// @param  def   Default value to supply if no matching variable is found.
   S32  getIntVariable  (const char* name,S32 def = 0);

   /// Same as setVariable(), but for floats.
   void setFloatVariable(const char* name,F32 var);

   /// Same as getVariable(), but for floats.
   ///
   /// @param  name  Name of the variable.
   /// @param  def   Default value to supply if no matching variable is found.
   F32  getFloatVariable(const char* name,F32 def = .0f);

   /// @}

   /// @name Global Function Registration
   /// @{

   /// Register a C++ function with the console making it a global function callable from the scripting engine.
   ///
   /// @param name      Name of the new function.
   /// @param cb        Pointer to the function implementing the scripting call; a console callback function returning a specific type value.
   /// @param usage     Documentation for this function. @ref console_autodoc
   /// @param minArgs   Minimum number of arguments this function accepts
   /// @param maxArgs   Maximum number of arguments this function accepts
   void addCommand(const char *name, StringCallback cb, const char *usage, S32 minArgs, S32 maxArgs);

   void addCommand(const char *name, IntCallback    cb,    const char *usage, S32 minArgs, S32 maxArgs); ///< @copydoc addCommand(const char *, StringCallback, const char *, S32, S32)
   void addCommand(const char *name, FloatCallback  cb,  const char *usage, S32 minArgs, S32 maxArgs); ///< @copydoc addCommand(const char *, StringCallback, const char *, S32, S32)
   void addCommand(const char *name, VoidCallback   cb,   const char *usage, S32 minArgs, S32 maxArgs); ///< @copydoc addCommand(const char *, StringCallback, const char *, S32, S32)
   void addCommand(const char *name, BoolCallback   cb,   const char *usage, S32 minArgs, S32 maxArgs); ///< @copydoc addCommand(const char *, StringCallback, const char *, S32, S32)
   /// @}

   /// @name Namespace Function Registration
   /// @{

   /// Register a C++ function with the console making it callable
   /// as a method of the given namespace from the scripting engine.
   ///
   /// @param nameSpace Name of the namespace to associate the new function with; this is usually the name of a class.
   /// @param name      Name of the new function.
   /// @param cb        Pointer to the function implementing the scripting call; a console callback function returning a specific type value.
   /// @param usage     Documentation for this function. @ref console_autodoc
   /// @param minArgs   Minimum number of arguments this function accepts
   /// @param maxArgs   Maximum number of arguments this function accepts
   void addCommand(const char *nameSpace, const char *name,StringCallback cb, const char *usage, S32 minArgs, S32 maxArgs);
   void addCommand(const char *nameSpace, const char *name,IntCallback cb,    const char *usage, S32 minArgs, S32 maxArgs); ///< @copydoc addCommand(const char*, const char *, StringCallback, const char *, S32, S32)
   void addCommand(const char *nameSpace, const char *name,FloatCallback cb,  const char *usage, S32 minArgs, S32 maxArgs); ///< @copydoc addCommand(const char*, const char *, StringCallback, const char *, S32, S32)
   void addCommand(const char *nameSpace, const char *name,VoidCallback cb,   const char *usage, S32 minArgs, S32 maxArgs); ///< @copydoc addCommand(const char*, const char *, StringCallback, const char *, S32, S32)
   void addCommand(const char *nameSpace, const char *name,BoolCallback cb,   const char *usage, S32 minArgs, S32 maxArgs); ///< @copydoc addCommand(const char*, const char *, StringCallback, const char *, S32, S32)
   /// @}

   /// @name Special Purpose Registration
   ///
   /// These are special-purpose functions that exist to allow commands to be grouped, so
   /// that when we generate console docs, they can be more meaningfully presented.
   ///
   /// @ref console_autodoc "Click here for more information about console docs and grouping."
   ///
   /// @{

   void markCommandGroup (const char * nsName, const char *name, const char* usage=NULL);
   void beginCommandGroup(const char * nsName, const char *name, const char* usage);
   void endCommandGroup  (const char * nsName, const char *name);

   /// @deprecated
   void addOverload      (const char * nsName, const char *name, const char *altUsage);

   /// @}

   /// @name Console Output
   ///
   /// These functions process the formatted string and pass it to all the ConsumerCallbacks that are
   /// currently registered. The console log file and the console window callbacks are installed by default.
   ///
   /// @see addConsumer()
   /// @see removeConsumer()
   /// @{

   /// @param _format   A stdlib printf style formatted out put string
   /// @param ...       Variables to be written
   void printf(const char *_format, ...);

   /// @note The console window colors warning text as LIGHT GRAY.
   /// @param _format   A stdlib printf style formatted out put string
   /// @param ...       Variables to be written
   void warnf(const char *_format, ...);

   /// @note The console window colors warning text as RED.
   /// @param _format   A stdlib printf style formatted out put string
   /// @param ...       Variables to be written
   void errorf(const char *_format, ...);

   /// @note The console window colors warning text as LIGHT GRAY.
   /// @param type      Allows you to associate the warning message with an internal module.
   /// @param _format   A stdlib printf style formatted out put string
   /// @param ...       Variables to be written
   /// @see Con::warnf()
   void warnf(ConsoleLogEntry::Type type, const char *_format, ...);

   /// @note The console window colors warning text as RED.
   /// @param type      Allows you to associate the warning message with an internal module.
   /// @param _format   A stdlib printf style formatted out put string
   /// @param ...       Variables to be written
   /// @see Con::errorf()
   void errorf(ConsoleLogEntry::Type type, const char *_format, ...);

   /// @}

   /// Returns true when called from the main thread, false otherwise
   bool isMainThread();


   /// @name Console Execution
   ///
   /// These are functions relating to the execution of script code.
   ///
   /// @{

   /// Call a script function from C/C++ code.
   ///
   /// @param argc      Number of elements in the argv parameter
   /// @param argv      A character string array containing the name of the function
   ///                  to call followed by the arguments to that function.
   /// @code
   /// // Call a Torque script function called mAbs, having one parameter.
   /// char* argv[] = {"abs", "-9"};
   /// char* result = execute(2, argv);
   /// @endcode
   const char *execute(S32 argc, const char* argv[]);

   /// @see execute(S32 argc, const char* argv[])
   const char *executef(S32 argc, ...);

   /// Call a Torque Script member function of a SimObject from C/C++ code.
   /// @param object    Object on which to execute the method call.
   /// @param argc      Number of elements in the argv parameter (must be >2, see argv)
   /// @param argv      A character string array containing the name of the member function
   ///                  to call followed by an empty parameter (gets filled with object ID)
   ///                  followed by arguments to that function.
   /// @code
   /// // Call the method setMode() on an object, passing it one parameter.
   ///
   /// char* argv[] = {"setMode", "", "2"};
   /// char* result = execute(mysimobject, 3, argv);
   /// @endcode
   const char *execute(SimObject *object, S32 argc, const char *argv[]);

   /// @see execute(SimObject *, S32 argc, const char *argv[])
   const char *executef(SimObject *, S32 argc, ...);

   /// Evaluate an arbitrary chunk of code.
   ///
   /// @param  string   Buffer containing code to execute.
   /// @param  echo     Should we echo the string to the console?
   /// @param  fileName Indicate what file this code is coming from; used in error reporting and such.
   const char *evaluate(const char* string, bool echo = false, const char *fileName = NULL);

   /// Evaluate an arbitrary line of script.
   ///
   /// This wraps dVsprintf(), so you can substitute parameters into the code being executed.
   const char *evaluatef(const char* string, ...);

   /// @}

   /// @name Console Function Implementation Helpers
   ///
   /// The functions Con::getIntArg, Con::getFloatArg and Con::getArgBuffer(size) are used to
   /// allocate on the console stack string variables that will be passed into the next console
   //  function called.  This allows the console to avoid copying some data.
   ///
   /// getReturnBuffer lets you allocate stack space to return data in.
   /// @{

   ///
   char *getReturnBuffer(U32 bufferSize);

   char *getArgBuffer(U32 bufferSize);
   char *getFloatArg(F64 arg);
   char *getIntArg  (S32 arg);
   /// @}

   /// @name Namespaces
   /// @{

   Namespace *lookupNamespace(const char *nsName);
   bool linkNamespaces(const char *parentName, const char *childName);

   /// @note This should only be called from consoleObject.h
   bool classLinkNamespaces(Namespace *parent, Namespace *child);
   /// @}

   /// @name Logging
   /// @{

   void getLockLog(ConsoleLogEntry * &log, U32 &size);
   void unlockLog(void);
   void setLogMode(S32 mode);

   /// @}

   /// @name Dynamic Type System
   /// @{

   ///
/*   void registerType( const char *typeName, S32 type, S32 size, GetDataFunction gdf, SetDataFunction sdf, bool isDatablockType = false );
   void registerType( const char* typeName, S32 type, S32 size, bool isDatablockType = false );
   void registerTypeGet( S32 type, GetDataFunction gdf );
   void registerTypeSet( S32 type, SetDataFunction sdf );

   const char *getTypeName(S32 type);
   bool isDatablockType( S32 type ); */

   void setData(S32 type, void *dptr, S32 index, S32 argc, const char **argv, EnumTable *tbl = NULL, BitSet32 flag = 0);
   const char *getData(S32 type, void *dptr, S32 index, EnumTable *tbl = NULL, BitSet32 flag = 0);
   /// @}
};

extern void expandEscape(char *dest, const char *src);
extern bool collapseEscape(char *buf);
extern S32 HashPointer(StringTableEntry ptr);

/// This is the backend for the ConsoleMethod()/ConsoleFunction() macros.
///
/// See the group ConsoleConstructor Innards for specifics on how this works.
///
/// @see @ref console_autodoc
/// @nosubgrouping
class ConsoleConstructor
{
public:
   /// @name Entry Type Fields
   ///
   /// One of these is set based on the type of entry we want
   /// inserted in the console.
   ///
   /// @ref console_autodoc
   /// @{
   StringCallback sc;   ///< A function/method that returns a string.
   IntCallback ic;      ///< A function/method that returns an int.
   FloatCallback fc;    ///< A function/method that returns a float.
   VoidCallback vc;     ///< A function/method that returns nothing.
   BoolCallback bc;     ///< A function/method that returns a bool.
   bool group;          ///< Indicates that this is a group marker.
   bool overload;       ///< Indicates that this is an overload marker.
                        ///  @deprecated Unused.
   /// @}

   /// Minimum/maximum number of arguments for the function.
   S32 mina, maxa;
   const char *usage;         ///< Usage string.
   const char *funcName;      ///< Function name.
   const char *className;     ///< Class name.

   /// @name ConsoleConstructer Innards
   ///
   /// The ConsoleConstructor class is used as the backend for the ConsoleFunction() and
   /// ConsoleMethod() macros. The way it works takes advantage of several properties of
   /// C++.
   ///
   /// The ConsoleFunction()/ConsoleMethod() macros wrap the declaration of a ConsoleConstructor.
   ///
   /// @code
   ///      // The definition of a ConsoleFunction using the macro
   ///      ConsoleFunction(ExpandFilename, const char*, 2, 2, "(string filename)")
   ///      {
   ///         argc;
   ///         char* ret = Con::getReturnBuffer( 1024 );
   ///         Con::expandScriptFilename(ret, 1024, argv[1]);
   ///         return ret;
   ///      }
   ///
   ///      // Resulting code
   ///      static const char* cExpandFilename(SimObject *, S32, const char **argv);
   ///      static ConsoleConstructor
   ///            gExpandFilenameobj(NULL,"ExpandFilename", cExpandFilename,
   ///            "(string filename)", 2, 2);
   ///      static const char* cExpandFilename(SimObject *, S32 argc, const char **argv)
   ///      {
   ///         argc;
   ///         char* ret = Con::getReturnBuffer( 1024 );
   ///         Con::expandScriptFilename(ret, 1024, argv[1]);
   ///         return ret;
   ///      }
   ///
   ///      // A similar thing happens when you do a ConsoleMethod.
   /// @endcode
   ///
   /// As you can see, several global items are defined when you use the ConsoleFunction method.
   /// The macro constructs the name of these items from the parameters you passed it. Your
   /// implementation of the console function is is placed in a function with a name based on
   /// the actual name of the console funnction. In addition, a ConsoleConstructor is declared.
   ///
   /// Because it is defined as a global, the constructor for the ConsoleConstructor is called
   /// before execution of main() is started. The constructor is called once for each global
   /// ConsoleConstructor variable, in the order in which they were defined (this property only holds true
   /// within file scope).
   ///
   /// We have ConsoleConstructor create a linked list at constructor time, by storing a static
   /// pointer to the head of the list, and keeping a pointer to the next item in each instance
   /// of ConsoleConstructor. init() is a helper function in this process, automatically filling
   /// in commonly used fields and updating first and next as needed. In this way, a list of
   /// items to add to the console is assemble in memory, ready for use, before we start
   /// execution of the program proper.
   ///
   /// In Con::init(), ConsoleConstructor::setup() is called to process this prepared list. Each
   /// item in the list is iterated over, and the appropriate Con namespace functions (usually
   /// Con::addCommand) are invoked to register the ConsoleFunctions and ConsoleMethods in
   /// the appropriate namespaces.
   ///
   /// @see Namespace
   /// @see Con
   /// @{

   ConsoleConstructor *next;
   static ConsoleConstructor *first;

   void init(const char *cName, const char *fName, const char *usg, S32 minArgs, S32 maxArgs);
   static void setup();
   /// @}

   /// @name Basic Console Constructors
   /// @{

   ConsoleConstructor(const char *className, const char *funcName, StringCallback sfunc, const char* usage,  S32 minArgs, S32 maxArgs);
   ConsoleConstructor(const char *className, const char *funcName, IntCallback    ifunc, const char* usage,  S32 minArgs, S32 maxArgs);
   ConsoleConstructor(const char *className, const char *funcName, FloatCallback  ffunc, const char* usage,  S32 minArgs, S32 maxArgs);
   ConsoleConstructor(const char *className, const char *funcName, VoidCallback   vfunc, const char* usage,  S32 minArgs, S32 maxArgs);
   ConsoleConstructor(const char *className, const char *funcName, BoolCallback   bfunc, const char* usage,  S32 minArgs, S32 maxArgs);
   /// @}

   /// @name Magic Console Constructors
   ///
   /// These perform various pieces of "magic" related to consoleDoc functionality.
   /// @ref console_autodoc
   /// @{

   /// Indicates a group marker. (A doxygen illusion)
   ///
   /// @see Con::markCommandGroup
   /// @ref console_autodoc
   ConsoleConstructor(const char *className, const char *groupName, const char* usage);

   /// @}
};

/// @name Global Console Definition Macros
///
/// @note If TORQUE_DEBUG is defined, then we gather documentation information, and
///       do some extra sanity checks.
///
/// @see ConsoleConstructor
/// @ref console_autodoc
/// @{

// O hackery of hackeries
#define conmethod_return_const              return (const
#define conmethod_return_S32                return (S32
#define conmethod_return_F32                return (F32
#define conmethod_nullify(val)
#define conmethod_return_void               conmethod_nullify(void
#define conmethod_return_bool               return (bool

#if !defined(TORQUE_SHIPPING)

// Console function macros
#  define ConsoleFunctionGroupBegin(groupName, usage) \
      static ConsoleConstructor gConsoleFunctionGroup##groupName##__GroupBegin(NULL,#groupName,usage);

#  define ConsoleFunction(name,returnType,minArgs,maxArgs,usage1)                         \
      static returnType c##name(SimObject *, S32, const char **argv);                     \
      static ConsoleConstructor g##name##obj(NULL,#name,c##name,usage1,minArgs,maxArgs);  \
      static returnType c##name(SimObject *, S32 argc, const char **argv)

#  define ConsoleFunctionGroupEnd(groupName) \
      static ConsoleConstructor gConsoleFunctionGroup##groupName##__GroupEnd(NULL,#groupName,NULL);

// Console method macros
#  define ConsoleMethodGroupBegin(className, groupName, usage) \
      static ConsoleConstructor className##groupName##__GroupBegin(#className,#groupName,usage);

#  define ConsoleMethod(className,name,returnType,minArgs,maxArgs,usage1)                             \
      static inline returnType c##className##name(className *, S32, const char **argv);               \
      static returnType c##className##name##caster(SimObject *object, S32 argc, const char **argv) {  \
         AssertFatal( dynamic_cast<className*>( object ), "Object passed to " #name " is not a " #className "!" ); \
         conmethod_return_##returnType ) c##className##name(static_cast<className*>(object),argc,argv);              \
      };                                                                                              \
      static ConsoleConstructor className##name##obj(#className,#name,c##className##name##caster,usage1,minArgs,maxArgs); \
      static inline returnType c##className##name(className *object, S32 argc, const char **argv)

#  define ConsoleStaticMethod(className,name,returnType,minArgs,maxArgs,usage1)                       \
      static inline returnType c##className##name(S32, const char **);                                \
      static returnType c##className##name##caster(SimObject *object, S32 argc, const char **argv) {  \
         conmethod_return_##returnType ) c##className##name(argc,argv);                                \
      };                                                                                              \
      static ConsoleConstructor                                                                       \
         className##name##obj(#className,#name,c##className##name##caster,usage1,minArgs,maxArgs);    \
      static inline returnType c##className##name(S32 argc, const char **argv)

#  define ConsoleMethodGroupEnd(className, groupName) \
      static ConsoleConstructor className##groupName##__GroupEnd(#className,#groupName,NULL);

#else

// These do nothing if we don't want doc information.
#  define ConsoleFunctionGroupBegin(groupName, usage)
#  define ConsoleFunctionGroupEnd(groupName)
#  define ConsoleMethodGroupBegin(className, groupName, usage)
#  define ConsoleMethodGroupEnd(className, groupName)

// These are identical to what's above, we just want to null out the usage strings.
#  define ConsoleFunction(name,returnType,minArgs,maxArgs,usage1)                   \
      static returnType c##name(SimObject *, S32, const char **);                   \
      static ConsoleConstructor g##name##obj(NULL,#name,c##name,"",minArgs,maxArgs);\
      static returnType c##name(SimObject *, S32 argc, const char **argv)

#  define ConsoleMethod(className,name,returnType,minArgs,maxArgs,usage1)                             \
      static inline returnType c##className##name(className *, S32, const char **argv);               \
      static returnType c##className##name##caster(SimObject *object, S32 argc, const char **argv) {  \
         conmethod_return_##returnType ) c##className##name(static_cast<className*>(object),argc,argv);              \
      };                                                                                              \
      static ConsoleConstructor                                                                       \
         className##name##obj(#className,#name,c##className##name##caster,"",minArgs,maxArgs);        \
      static inline returnType c##className##name(className *object, S32 argc, const char **argv)

#  define ConsoleStaticMethod(className,name,returnType,minArgs,maxArgs,usage1)                       \
      static inline returnType c##className##name(S32, const char **);                                \
      static returnType c##className##name##caster(SimObject *object, S32 argc, const char **argv) {  \
         conmethod_return_##returnType ) c##className##name(argc,argv);                                                        \
      };                                                                                              \
      static ConsoleConstructor                                                                       \
         className##name##obj(#className,#name,c##className##name##caster,"",minArgs,maxArgs);        \
      static inline returnType c##className##name(S32 argc, const char **argv)


#endif

/// @}

#endif
