#ifndef SDL2PP_ERROR
#define SDL2PP_ERROR

#include <stdexcept>

namespace SDL{
	class Error : public std::runtime_error{
		public:
			static std::string Get();
			Error();
			virtual ~Error();
	};
}

#endif
