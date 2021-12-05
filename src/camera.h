
#ifndef _LIBCAMERA_INC
#define _LIBCAMERA_INC
#include "defs.h"

// Opaque C types for libcamera classes
typedef struct CameraManager CameraManager;
typedef struct CameraList CameraList;
typedef struct Camera Camera;
typedef struct StreamList StreamList;
typedef struct CameraConfiguration CameraConfiguration;

#ifdef __cplusplus
extern "C" {
#endif
    // Camera Manager methods
    CameraManager* NewCameraManager();
    void DestroyCameraManager(CameraManager* manager);
    int CameraManagerStart(CameraManager* manager);
    void CameraManagerStop(CameraManager* manager);
    const char* CameraManagerVersion(CameraManager* manager, char* str, int len);

    // Return list of cameras
    CameraList* NewCameraList(CameraManager* manager);
    void DestroyCameraList(CameraList* cameras);
    Camera* CameraListNext(CameraList* cameras);

    // Camera methods
    const char* CameraId(Camera* camera, char* str, int len);
    int CameraAcquire(Camera* camera);
    int CameraRelease(Camera* camera);
    LocationEnum CameraLocation(Camera* camera);
    const char* CameraModel(Camera* camera, char* str, int len);

    // Return list of configurations for a stream
    CameraConfiguration* NewConfiguration(Camera* camera, StreamRoleEnum role[]);
    void DestroyConfiguration(CameraConfiguration* config);

    // Return list of streams for a camera
    StreamList* NewStreamList(Camera* camera);
    void DestroyStreamList(StreamList* streams);

#ifdef __cplusplus
}
#endif
#endif
