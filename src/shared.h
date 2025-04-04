#ifndef SHARED_H_
#define SHARED_H_

#define CLAY_NULL (intptr_t) 0

#ifdef RENDERER_RAYLIB
#  define LOG(args...) TraceLog(LOG_INFO, args)
#  define ERR(args...) TraceLog(LOG_ERROR, args)
#endif

#ifdef RENDERER_SDL2
#  define LOG(args...) SDL_Log(args)
#  define ERR(args...) SDL_Log(args)
#endif

#endif // SHARED_H_
