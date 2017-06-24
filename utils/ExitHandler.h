#ifndef EXITHANDLER_H
#define EXITHANDLER_H

#include "EventHandler.h"


namespace utils {
	class ExitHandler : public EventHandler {
		public:
			static const int SIG_EXIT = SIGINT;


			bool exitRecibido;
			
			
			ExitHandler() : exitRecibido(false) { }


			virtual int handleSignal(int) {
				this->exitRecibido = true;
				return 0;
			}
	};

}

#endif
