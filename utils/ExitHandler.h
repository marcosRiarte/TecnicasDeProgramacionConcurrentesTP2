#ifndef EXITHANDLER_H
#define EXITHANDLER_H

#include "EventHandler.h"


namespace utils {
	class ExitHandler : public EventHandler {
		public:
			static const int SIG_EXIT = SIGINT;


			bool exitRecibido;
			
			
			ExitHandler() : exitRecivido(false) { }


			virtual int handleSignal(int signum) {
				this->exitRecibido = true;
				return 0;
			}
	};

}

#endif
