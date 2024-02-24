#ifndef BUFFER_HPP
#define BUFFER_HPP

struct Buffer {
    unsigned int id;
};

Buffer CreateBufferf(unsigned int type, float *data, int data_length);
Buffer CreateBufferu(unsigned int type, unsigned int *data, int data_length);

#endif