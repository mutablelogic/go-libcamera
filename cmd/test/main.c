#include <camera.h>
#include <stdio.h>

#define MAX_STR_LENGTH 100

int main() {
	char str[MAX_STR_LENGTH+1];
	CameraManager* cm = NewCameraManager();
	int ret = CameraManagerStart(cm);
	if(ret < 0) {
		printf("Error starting camera manager\n");
		goto END;
	}

	// Print version of libcamera
	printf("ver=%s\n", CameraManagerVersion(cm, str, sizeof(str)));

	// Enumerate all cameras
	CameraList* list = NewCameraList(cm);
	Camera* camera = CameraListNext(list);
	while(camera) {
		printf("  camera %s\n",CameraId(camera, str, sizeof(str)));
		printf("    model %s\n",CameraModel(camera, str, sizeof(str)));
		printf("    location %d\n",CameraLocation(camera));

		// Acquire camera
		if(CameraAcquire(camera) != 0) {
			printf("    unable to aquire\n");
			continue;
		}

		// Release camera
		if(CameraRelease(camera) != 0) {
			printf("    unable to release\n");
		}

		camera = CameraListNext(list);
	}

	// Destroy list of cameras
	DestroyCameraList(list);

	// Stop camera manager
	CameraManagerStop(cm);

END:
	DestroyCameraManager(cm);
	return 0;
}
