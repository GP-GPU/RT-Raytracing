#ifndef PRODUCERAY_H_
#define PRODUCERAY_H_

#include "opencl.h"

class Camera;

class ProduceRay : public OpenCL {
public:
	ProduceRay();
	virtual ~ProduceRay();
	int perform(Camera* cam, cl_float4*& raydirs);
private:
	cl::Kernel kernel;
};

#endif /* PRODUCERAY_H_ */
