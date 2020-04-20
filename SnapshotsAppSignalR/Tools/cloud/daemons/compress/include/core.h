#ifndef SKF_CLOUD_CORE_H
#define SKF_CLOUD_CORE_H

#include <iostream>
#include <zmq.hpp>

#include "timer.h"
#include "logs.h"
#include "compression.h"
namespace Engine {
	class Core {
	public:
		Core() : _context(1)
		{
			sleep(1);
			init();
		};

		~Core() {};
		void	run();
		bool	compress(void *buff, size_t f_size);
	private:
		void	init();
		void	load_yaml();

		zmq::context_t			_context;
		vector<zmq::socket_t *>	_ipc_subscriptions;
		vector<zmq::socket_t *>	_tcp_publications;
		Compression _compress;
	};
};
#endif //SKF_CLOUD_CORE_H
