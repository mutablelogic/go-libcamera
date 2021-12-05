#include <libcamera/libcamera.h>
#include <stdlib.h>
#include <string.h>
#include "defs.h"

#define MAX_CAMERAS 100 // Upward bound of the number of cameras supported by CameraList

using namespace libcamera;

// CameraManager
extern "C" {
    CameraManager* NewCameraManager() {
        CameraManager* manager = new CameraManager();
        return manager;
    }
    void DestroyCameraManager(CameraManager* manager) {
        delete manager;
    }
    int CameraManagerStart(CameraManager* manager) {
        return manager->start();
    }
    void CameraManagerStop(CameraManager* manager) {
        manager->stop();
    }
    const char* CameraManagerVersion(CameraManager* manager, char* str, int len) {
        if(str != NULL && len > 0) {
            strncpy(str, manager->version().c_str(), len);
        }
        return str;
    }
}

// CameraList
extern "C" {
    typedef struct  {
        Camera** arr;
        unsigned int n;
        unsigned int i;
    } CameraList;
    
    CameraList* NewCameraList(CameraManager* manager) {
        CameraList* cameras = (CameraList* )malloc(sizeof(CameraList));
        cameras->arr = (Camera** )malloc(sizeof(Camera*) * MAX_CAMERAS);
        if(cameras == NULL || cameras->arr == NULL) {
            free(cameras);
            return NULL;
        }
        cameras->n = 0;
        cameras->i = 0;
        for (auto const &camera : manager->cameras()) {
            if(cameras->n < MAX_CAMERAS) {
                cameras->arr[cameras->n++] = camera.get();
            }
        }
        return cameras;
    }
    void DestroyCameraList(CameraList* cameras) {
        free(cameras->arr);
        free(cameras);
    }
    Camera* CameraListNext(CameraList* cameras) {
        if(cameras->i >= cameras->n) {
            cameras->i = 0;
            return NULL;
        }
        return cameras->arr[cameras->i++];
    }
}

// Camera
extern "C" {
    const char* CameraId(Camera* camera, char* str, int len) {
        if(str != NULL && len > 0) {
            strncpy(str,camera->id().c_str(),len);
        }
        return str;
    }
    int CameraAcquire(Camera* camera) {
        return camera->acquire();
    }
    int CameraRelease(Camera* camera) {
        return camera->release();
    }
    LocationEnum CameraLocation(Camera* camera) {
        const ControlList &props = camera->properties();
    	switch (props.get(properties::Location)) {
    	case properties::CameraLocationFront:
            return CameraLocationFront;
    	case properties::CameraLocationBack:
            return CameraLocationBack;
    	default:
            return CameraLocationExternal;
    	}
    }
    const char* CameraModel(Camera* camera, char* str, int len) {
        const ControlList &props = camera->properties();
        if(str != NULL && len > 0 && props.contains(properties::Model)) {
            strncpy(str,props.get(properties::Model).c_str(),len);
            return str;
        }
        return NULL;
    }
}

// CameraConfiguration
extern "C" {
    CameraConfiguration* NewConfiguration(Camera* camera, StreamRoleEnum role[]) {
        // TODO
        return NULL;
    }
    void DestroyConfiguration(CameraConfiguration* config) {
        // TODO
    }
}
