#ifndef SHARED_H_
#define SHARED_H_

#define CLAY_NULL (intptr_t) 0

#ifdef RENDERER_RAYLIB
#  define LOG(args...)  TraceLog(LOG_INFO   , args)
#  define WARN(args...) TraceLog(LOG_WARNING, args)
#  define ERR(args...)  TraceLog(LOG_ERROR  , args)
#endif

#ifdef RENDERER_SDL2
#  define LOG(args...)  SDL_Log(args)
#  define WARN(args...) SDL_LogWarn(0, args)
#  define ERR(args...)  SDL_LogError(0, args)
#endif

#define ARRAY_LEN(arr) sizeof(arr) / sizeof(arr[0])

#endif // SHARED_H_
