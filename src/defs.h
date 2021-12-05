
#ifndef _LIBCAMERA_DEFS
#define _LIBCAMERA_DEFS

typedef enum {
    CameraLocationFront = 0,
    CameraLocationBack = 1,
    CameraLocationExternal = 2
} LocationEnum;

typedef enum {
     Raw, 
     StillCapture,
     VideoRecording,
     Viewfinder
} StreamRoleEnum;

typedef enum { 
    Valid, 
    Adjusted, 
    Invalid 
} StatusEnum;

#endif
