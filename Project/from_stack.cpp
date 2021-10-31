#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <CL/opencl.h>
#include <SFML/Graphics.hpp>

#define DATA_SIZE 8192

int main(int argc, char* argv[])
{
    sf::Image img;
    img.create(DATA_SIZE, DATA_SIZE);

    cl_int err;

    size_t global; // globális probléma tér
    size_t local; // lokális probléma tér

    cl_platform_id platform;
    err = clGetPlatformIDs(1, &platform, NULL);
    // Get first available platform
    if (err != CL_SUCCESS) {
        std::cerr << "Error, failed to find platform.\n";
        std::cin.get();
        return EXIT_FAILURE;
    }

    cl_device_id device_id;
    err = clGetDeviceIDs(platform,
        CL_DEVICE_TYPE_GPU,
        1,
        &device_id,
        NULL);
    if (err != CL_SUCCESS) {
        std::cerr << "Error, failed to create device group.\n";
        std::cin.get();
        return EXIT_FAILURE;
    }

    cl_context context;
    context = clCreateContext(0,
        1,
        &device_id,
        NULL,
        NULL,
        &err);
    if (!context) {
        std::cerr << "Error, failed to create a compute context.\n";
        std::cin.get();
        return EXIT_FAILURE;
    }

    cl_command_queue commands;
    commands = clCreateCommandQueue(context,
        device_id,
        0,
        &err);
    if (!commands) {
        std::cerr << "Error, failed to create command queue.\n";
        std::cin.get();
        return EXIT_FAILURE;
    }

    const char* KernelSource = "__kernel void sqr(__global float* input,\n"
        "const int row,\n"
        "__global float* output){\n"
        "int i = get_global_id(0);\n"
        "float c_re = input[i];\n"
        "float c_im = 1.5 - row*3.0/8192.;\n"
        "int count = 0;\n"
        "float x = 0., y = 0.;\n"
        "while(x*x + y*y < 2. && count < 255 ){\n"
        "float x_new = x*x - y*y + c_re;\n"
        "y = 2*x*y + c_im;\n"
        "x = x_new;\n"
        "count++;\n"
        "}\n"
        "output[i] = count;\n"
        "}\n";

    cl_program program;
    program = clCreateProgramWithSource(context,
        1,
        &KernelSource,
        NULL,
        &err);

    err = clBuildProgram(program,
        0,
        NULL,
        NULL,
        NULL,
        NULL);
    if (err != CL_SUCCESS) {
        size_t len;
        char buffer[2048];
        std::cerr << "Failed to build executable.\n";
        clGetProgramBuildInfo(program, device_id,
            CL_PROGRAM_BUILD_LOG,
            sizeof(buffer), buffer, &len);
        std::cerr << buffer << std::endl;
        std::cin.get();
        exit(1);
    }

    cl_kernel kernel;
    kernel = clCreateKernel(program, "sqr", &err);
    if (!kernel || err != CL_SUCCESS) {
        std::cerr << "Error, failed to create compute kernel.\n";
        std::cin.get();
        exit(1);
    }

    float* data = new float[DATA_SIZE];
    float* results = new float[DATA_SIZE];
    int row;
    cl_mem input;
    cl_mem output;

    for (int s = 0; s < DATA_SIZE; s++) {

        row = s;
        unsigned int count = DATA_SIZE;
        for (int i = 0; i < count; i++) {
            data[i] = -1.5 + 3.*i / (float)count;
        }

        input = clCreateBuffer(context,
            CL_MEM_READ_ONLY, sizeof(float)*count,
            NULL,
            NULL);

        output = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
            sizeof(float)*count,
            NULL,
            NULL);

        if (!input || !output) {
            std::cerr << "Error, failed to allocate device memory.\n";
            std::cin.get();
            exit(1);
        }

        err = clEnqueueWriteBuffer(commands,
            input,
            CL_TRUE,
            0,
            sizeof(float)*count,
            data,
            0,
            NULL,
            NULL);

        if (err != CL_SUCCESS) {
            std::cerr << "Error, failed to write to source array.\n";
            std::cin.get();
            exit(1);
        }

        err = 0;
        err = clSetKernelArg(kernel,
            0,
            sizeof(cl_mem),
            &input);
        err |= clSetKernelArg(kernel,
            1,
            sizeof(int),
            &row);
        err |= clSetKernelArg(kernel,
            2,
            sizeof(cl_mem),
            &output);
        if (err != CL_SUCCESS) {
            std::cerr << "Error, failed to set kernel args.\n";
            std::cin.get();
            exit(1);
        }

        err = clGetKernelWorkGroupInfo(kernel,
            device_id,
            CL_KERNEL_WORK_GROUP_SIZE,
            sizeof(local),
            &local,
            NULL);

        if (err != CL_SUCCESS) {
            std::cerr << "Error, failed to retrieve kernel workgroup info.\n";
            std::cin.get();
            exit(1);
        }

        global = count;
        err = clEnqueueNDRangeKernel(commands,
            kernel,
            1,
            NULL,
            &global,
            &local,
            0,
            NULL,
            NULL);

        if (err) {
            std::cerr << "Error: failed to execute kernel.\n";
            std::cin.get();
            exit(1);
        }

        clFinish(commands);
        err = clEnqueueReadBuffer(commands,
            output,
            CL_TRUE,
            0,
            sizeof(float)*count,
            results,
            0,
            NULL,
            NULL);

        if (err != CL_SUCCESS) {
            std::cerr << "Failed to read output array.\n";
            std::cin.get();
            exit(1);
        }

        // Set the pixels in the img after the calculation
        for (int i = 0; i < count; i++) {
            img.setPixel(i, s, sf::Color::Color(0, (int)results[i], 0));
        }
    }
    // Cleanup.
    delete[] data;
    delete[] results;

    clReleaseMemObject(input);
    clReleaseMemObject(output);
    clReleaseProgram(program);
    clReleaseKernel(kernel);
    clReleaseCommandQueue(commands);
    clReleaseContext(context);


    // Save the image to a bitmap
    img.saveToFile("mandelbrot.bmp");
    return 0;
}