#include "shapes/shape.h"
#include "shapes/sphere.h"
#include "util/ray.h"
#include "scene.h"

Scene::Scene() {
	// Initialize shapes here.
	_shapes.push_back(new Sphere(Vector(0,0,-3), .2));
}

Scene::~Scene() {
	// TODO Auto-generated destructor stub
}

void Scene::render(Vector*& buffer, int width, int height) {
	Camera cam;
	Vector up = cam.up();
	Vector right = cam.right();
	Vector pos = cam.pos();
	Vector dir = cam.dir();

	float invwidth = 1.f / width;
	float invheight = 1.f / height;

	Vector *pixel = buffer;
	for (int yi = 0; yi < height; yi++) {
		for (int xi = 0; xi < width; xi++, pixel++) {
			float x = (xi + .5) * invwidth - 0.5;
			float y = (yi + .5) * invheight - 0.5;

			Vector imageproj = x * right + y * up + pos + dir;
			Vector raydir = (imageproj - pos).normalize();
			Ray ray(pos, raydir);

			*pixel = this->trace(ray);
		}
	}
}

const Vector Scene::trace(const Ray ray) {
	for(Shape* shape : _shapes) {
		Vector hit, normal;
		if (shape->intersect(ray, hit, normal)) {
			std::cout << "hit: " << hit << std::endl;
			return Vector(1,0,0);
		}
	}
	std::cout << "miss: " << ray.dir() << std::endl;
	return Vector(0,0,0);
}
