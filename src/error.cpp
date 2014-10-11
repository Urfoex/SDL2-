#include "error.h"
#include <SDL_error.h>

namespace SDL{
	std::string Error::Get(){
		return SDL_GetError(); 
	}

	Error::Error():runtime_error(Get()){

	}

	Error::~Error(){

	}

}
