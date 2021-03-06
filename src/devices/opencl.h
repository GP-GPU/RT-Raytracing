#ifndef OPENCL_H_
#define OPENCL_H_

#ifdef __APPLE__
  #include <OpenCL/opencl.h>
//  #include "../kernel/kernel.cl.h"
#else
  #include <CL/cl.h>
#endif /* __APPLE__ */

#include <vector>

#include "devices/device.h"

#define SAFE( call) {                                                     \
	cl_int err = call;                                                    \
	if( CL_SUCCESS != err) {                                              \
		fprintf(stderr, "OpenCL error in file '%s' in line %i: %d.\n",   \
				__FILE__, __LINE__, err);                                 \
				exit(EXIT_FAILURE);                                       \
	}                                                                     \
}
#define SAFE_REF( call) {                                                 \
	cl_int err; call;                                                     \
	if( CL_SUCCESS != err) {                                              \
		fprintf(stderr, "OpenCL error in file '%s' in line %i: %d.\n",   \
				__FILE__, __LINE__, err);                                 \
				exit(EXIT_FAILURE);                                       \
	}                                                                     \
}
#define SAFE_BUILD( call) {                                                   \
	cl_int err = call;                                                        \
	if( CL_SUCCESS != err) {                                                  \
		char buffer[2048];                                                    \
		clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, sizeof(buffer), buffer, 0); \
		fprintf(stderr, "OpenCL error in file '%s' in line %i: %d.\n"         \
				"Build log:\n%s\n",                                           \
				__FILE__, __LINE__, err, buffer);                             \
				exit(EXIT_FAILURE);                                           \
	}                                                                         \
}

class OpenCL : public Device {
public:
	OpenCL();
	virtual ~OpenCL();

	void set_best_device();
	int init();
	int load_kernels(std::vector<std::string> kernel_path);

	virtual device_mem malloc(size_t size, void* host_ptr, mem_flags perm);
	virtual void read(device_mem mem, size_t size, void* data_read);
	virtual void write(device_mem mem, size_t size, void* data_write);
	virtual int enqueue_kernel_range(kernel_key id, uint8_t num_args, void** arg_values,
					size_t* arg_sizes, uint8_t dim, size_t* work_size);

#ifdef __APPLE__
	dispatch_queue_t	dp_queue;
#else
	cl_command_queue 	commands;
#endif /* __APPLE__ */
	cl_context		context;
protected:
	cl_device_id		device;
	std::vector<cl_kernel>	kernels;
};

#endif /* OPENCL_H_ */
