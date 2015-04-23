#ifndef ZS4_RING
#define ZS4_RING

#include <zs4string.h>

class zs4ring
{
public:
	zs4string buffer;
	inline zs4ring(void){
		reset();
	}
	virtual inline ~zs4ring(void){

	}

	inline virtual size_t readChar(char * c){
		if (!readable())
			return 0;

		*c = buffer.str[read_index];

		read_index = ((read_index + 1) % buffer.bufsize);

		return 1;
	}
	inline virtual size_t readBlock(void * block, size_t size){
		if (readable() < size)
			return 0;

		char * ptr = (char*)block;

		for (size_t i = 0; i < size; i++)
			readChar(&ptr[i]);

		return size;
	}
	inline virtual size_t writeChar(char c){
		if (!writeable())
			return 0;

		buffer.str[write_index] = c;

		write_index = ((write_index + 1) % buffer.bufsize);

		return 1;
	}
	inline virtual size_t writeBlock(const void * block, size_t size){
		if (writeable() < size)
			return 0;

		char * ptr = (char*)block;

		for (size_t i = 0; i < size; i++)
			writeChar(ptr[i]);

		return size;
	}
	inline virtual size_t readable(void){
		if (write_index == read_index)
			return 0;

		if (write_index > read_index)
			return (write_index - read_index);

		return (write_index + buffer.bufsize - read_index);
	}
	inline virtual size_t writeable(void){
		return ((buffer.bufsize - 1) - readable());
	}
	inline virtual void reset(void){
		read_index = write_index = 0;
	}
	inline virtual zs4error close(void){
		buffer.stream_state = buffer.CLOSED;
		reset();
		return zs4FAILURE;
	}

	inline void operator = (zs4string&buf){ buffer = buf; }

private:
	size_t read_index;
	size_t write_index;
};

#endif
