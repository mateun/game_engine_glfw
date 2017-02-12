#ifdef _WIN32
#ifdef RENDERLIB_EXPORTS
#define RENDERLIB_API __declspec( dllexport )
#else
#define RENDERLIB_API __declspec( dllexport )
#endif
#endif

