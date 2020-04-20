#include "compression.h"

Engine::t_compressed	Engine::Compression::zstd(const void *buf, const size_t buf_size, int compression_level)
{
	int const				c_buf_size = ZSTD_compressBound(buf_size);
	Engine::t_compressed	compressed;

	if ((compressed.buf = malloc(c_buf_size)) == NULL) {
		compressed.buf_size = -1;
		return compressed;
	}
	compressed.buf_size = ZSTD_compress(compressed.buf, c_buf_size, buf, buf_size, compression_level);
	return compressed;
}