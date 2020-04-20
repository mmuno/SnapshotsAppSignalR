#ifndef SKF_CLOUD_COMPRESSION_H
#define SKF_CLOUD_COMPRESSION_H

#include <cstdlib>
#include <cstring>

#include <zstd.h>

namespace Engine {
	typedef struct	s_compressed {
		void		*buf;
		int			buf_size;
	}t_compressed;

	class Compression {
	public:
		Compression() {};
		~Compression() {};

		t_compressed	zstd(const void *buf, const size_t buf_size, int compression_level);
	private:
	};
}

#endif //SKF_CLOUD_COMPRESSION_H
