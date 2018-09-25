#ifndef _TERRALIB_<%= appnameUpper %>_CONFIG_H
#define _TERRALIB_<%= appnameUpper %>_CONFIG_H

/*!
  \def TE<%= appnameUpper %>EXPORT

  \brief You can use this macro in order to export/import classes and functions from this module.

  \note If you want to compile TerraLib as DLL in Windows, remember to insert TE<%= appnameUpper %>DLL into the project's list of defines.

  \note If you want to compile TerraLib as an Static Library under Windows, remember to insert the TE<%= appnameUpper %>STATIC flag into the project list of defines.
 */
#ifdef WIN32

  #ifdef _MSC_VER
    #pragma warning( disable : 4251 )
    #pragma warning( disable : 4275 )
  #endif

  #ifdef TE<%= appnameUpper %>STATIC
    #define TE<%= appnameUpper %>EXPORT                          // Don't need to export/import... it is a static library
  #elif TE<%= appnameUpper %>DLL
    #define TE<%= appnameUpper %>EXPORT  __declspec(dllexport)   // export DLL information
  #else
    #define TE<%= appnameUpper %>EXPORT  __declspec(dllimport)   // import DLL information
  #endif
#else
  #define TE<%= appnameUpper %>EXPORT
#endif
#endif // _TERRALIB_<%= appnameUpper %>_CONFIG_H