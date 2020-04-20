#include <cstdlib>
#include <cstring>
#include <signal.h>

#include "core.h"
#include "conf_loader.h"

using namespace std;

static volatile int g_keep_running = 1;
/** @brief Catches catch ctrl-c set keep runing to false
 */
static void	int_handler(int dummy)
{
	(void) dummy;
	g_keep_running = 0;
}


/**
 * init function for the compression core
 * This part allows to subscribe to the different channels of data
 */
void		Engine::Core::init()
{
	int				i = 0;
	std::string		ipc_path;
	std::string 	tcp_path;
	ConfLoader::Ipc	loader;

	loader.run();
	for (auto &name : loader.get_ipc_names()) {
		_ipc_subscriptions.emplace_back(new zmq::socket_t (_context, ZMQ_SUB));
		_ipc_subscriptions[i]->connect("ipc://" + name);
		std::cout << "ipc://" + name << std::endl;
		_ipc_subscriptions[i]->setsockopt(ZMQ_SUBSCRIBE,  "", 0);
		_tcp_publications.emplace_back(new zmq::socket_t (_context, ZMQ_PUB));
		//_ipc_subscriptions[i]->bind("tcp://*:5556");
		i++;
	}
}

bool		Engine::Core::compress(void *buff, size_t f_size)
{
	t_compressed	data;

	data = _compress.zstd(buff, f_size, 1);
	Logs::engine_log(string(to_string(f_size) + " > " + to_string(data.buf_size) + "\n").c_str(), 0);
	free(data.buf);
	return true;
}

void		Engine::Core::run()
{
	zmq::message_t	update;

	while (g_keep_running) {
		for (auto & subscription : _ipc_subscriptions) {
            subscription->recv(&update, ZMQ_DONTWAIT);
			if (update.size() > 0) {
				compress(update.data(), update.size());
		    }
        }
	}
	exit(0);
}

int main()
{
	Engine::Core		engine;
	signal(SIGINT, int_handler);

	Logs::engine_log(string("engine pid: " + to_string(getpid()) + "\n").c_str(), 0);
	try {
			engine.run();
	}
	catch (std::exception &e) {
		std::cerr << "Exception: " << e.what() << "@n" << endl;
	}
	return 0;
}
