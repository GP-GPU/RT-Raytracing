#include <ctime>

#include "scene.h"

#include "devices/device.h"
#include "util/camera.h"
#include "util/ray.h"

Scene::Scene(Device* device) : _cam(nullptr), _device(device) {
	// Initialize shapes here.
	_shapes.push_back(shape { { Vector(0,0,-3).gpu_type(), .2 }, SPHERE });
}

Scene::~Scene() {
	// TODO Auto-generated destructor stub
}

void Scene::setCamera(Camera* cam) {
	this->_cam = cam;
}

void Scene::render(unsigned char* buffer) {
	Vector up = _cam->up();
	Vector right = _cam->right();
	Vector pos = _cam->pos();
	Vector dir = _cam->dir();


	std::clock_t c_start = std::clock();

	float4* gpuraydirs;
	_device->produceray(_cam, gpuraydirs);
	_device->traceray(_cam, gpuraydirs, _shapes, buffer);

	std::clock_t c_end = std::clock();
	//printf("Test duration (regular): %f ms\n", 1000.0 * (c_end - c_start) / CLOCKS_PER_SEC);

	delete gpuraydirs;
}
