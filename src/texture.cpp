#include "texture.h"
#include <SDL_render.h>


namespace SDL{

	Texture::Texture(){
		/*STUB*/
	}

	Texture::Texture(SDL_Texture*){
		/*STUB*/
	}

	Texture::~Texture(){
		if(m_texture != nullptr) DestroyTexture(); 
	}


	void Texture::DestroyTexture(){
		SDL_DestroyTexture(m_texture);
		m_texture = nullptr;
	}

	// extern DECLSPEC int SDL_QueryTexture(SDL_Texture * texture,
	//                                              uint32_t * format, int *access,
	//                                              int *w, int *h);
	// 
	// extern DECLSPEC int SDL_SetTextureColorMod(SDL_Texture * texture,
	//                                                    uint8_t r, uint8_t g, uint8_t b);
	// 
	// 
	// extern DECLSPEC int SDL_GetTextureColorMod(SDL_Texture * texture,
	//                                                    uint8_t * r, uint8_t * g,
	//                                                    uint8_t * b);
	// 
	// extern DECLSPEC int SDL_SetTextureAlphaMod(SDL_Texture * texture,
	//                                                    uint8_t alpha);
	// 
	// extern DECLSPEC int SDL_GetTextureAlphaMod(SDL_Texture * texture,
	//                                                    uint8_t * alpha);
	// 
	// extern DECLSPEC int SDL_SetTextureBlendMode(SDL_Texture * texture,
	//                                                     SDL_BlendMode blendMode);
	// 
	// extern DECLSPEC int SDL_GetTextureBlendMode(SDL_Texture * texture,
	//                                                     SDL_BlendMode *blendMode);
	// 
	// extern DECLSPEC int SDL_UpdateTexture(SDL_Texture * texture,
	//                                               const SDL_Rect * rect,
	//                                               const void *pixels, int pitch);
	// 
	// extern DECLSPEC int SDL_UpdateYUVTexture(SDL_Texture * texture,
	//                                                  const SDL_Rect * rect,
	//                                                  const uint8_t *Yplane, int Ypitch,
	//                                                  const uint8_t *Uplane, int Upitch,
	//                                                  const uint8_t *Vplane, int Vpitch);
	// 
	// extern DECLSPEC int SDL_LockTexture(SDL_Texture * texture,
	//                                             const SDL_Rect * rect,
	//                                             void **pixels, int *pitch);
	// 
	// extern DECLSPEC void SDL_UnlockTexture(SDL_Texture * texture);
	// 
	// extern DECLSPEC int SDL_GL_BindTexture(SDL_Texture *texture, float *texw, float *texh);
	// 
	// extern DECLSPEC int SDL_GL_UnbindTexture(SDL_Texture *texture);
}
