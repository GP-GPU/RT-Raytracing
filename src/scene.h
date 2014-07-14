#ifndef SCENE_H_
#define SCENE_H_

#include <vector>

#include "shapes/shape.h"
#include "util/vector.h"

struct cl_shape;
class Camera;
class Device;
class Ray;

class Scene {
public:
	Scene(Device* device);
	virtual ~Scene();

	void setCamera(Camera* cam);
	void render(unsigned char* buffer);
	const Vector trace(const Ray& ray);
private:
	Camera* _cam;
	Device* _device;
	std::vector<shape> _shapes;
};

#endif /* SCENE_H_ */
