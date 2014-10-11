#include "renderer.h"
#include "error.h"
#include "texture.h"
#include <SDL.h>
#include <memory>

namespace SDL{
	Renderer::Renderer(){
		/*STUB*/
	}

	Renderer::~Renderer(){
		if(m_renderer != nullptr) DestroyRenderer(); 
	}

	Renderer::Renderer(SDL_Renderer* renderer):m_renderer(renderer){

	}


	void Renderer::DestroyRenderer(){
		SDL_DestroyRenderer(m_renderer);
		m_renderer = nullptr;
	}


	auto Renderer::GetNumRenderDrivers(){
		auto numRenderDrivers = SDL_GetNumRenderDrivers();
		if(numRenderDrivers >= 1)
			return numRenderDrivers;
		else
			throw Error();
	}

	auto Renderer::GetRenderDriverInfo(int index){
		SDL_RendererInfo info;
		if( SDL_GetRenderDriverInfo(index, &info) != 0)
			throw Error();
		else
			return info;
	}

	auto Renderer::GetRendererInfo(){
		SDL_RendererInfo info;
		if(SDL_GetRendererInfo(m_renderer, &info) != 0)
			throw Error();
		else
			return info;
	}

	auto Renderer::GetRendererOutputSize(){
		glm::ivec2 wh;
		if(SDL_GetRendererOutputSize(m_renderer, &(wh.x), &(wh.y)) != 0)
			throw Error();
		else
			return wh;
	}

	auto Renderer::CreateTexture(uint32_t format, int access, int w, int h){
		auto* sdlTexture = SDL_CreateTexture(m_renderer, format, access, w, h);
		if( sdlTexture == nullptr)
			throw Error();
		else
			return std::make_shared<Texture>(sdlTexture);
	}

	auto Renderer::RenderTargetSupported(){
		return SDL_RenderTargetSupported(m_renderer);
	}


	void Renderer::RenderClear(){
		if(SDL_RenderClear(m_renderer) != 0)
			throw Error();
	}

	void Renderer::RenderDrawPoint(glm::ivec2 p){
		RenderDrawPoint(p.x, p.y);
	}

	void Renderer::RenderDrawPoint(glm::ivec2& p){
		RenderDrawPoint(p.x, p.y);
	}

	void Renderer::RenderDrawPoint(Point p){
		RenderDrawPoint(p.x, p.y);
	}

	void Renderer::RenderDrawPoint(Point& p){
		RenderDrawPoint(p.x, p.y);
	}


	void Renderer::RenderDrawPoint(int x, int y){
		if(SDL_RenderDrawPoint(m_renderer, x, y) != 0)
			throw Error();
	}

	void Renderer::RenderDrawPoints(std::vector<Point>& points){
		if(SDL_RenderDrawPoints(m_renderer, points.data(), points.size()) != 0)
			throw Error();
	}

	void Renderer::RenderDrawLine(glm::ivec2 p1, glm::ivec2 p2){
		RenderDrawLine(p1.x, p1.y, p2.x, p2.y);
	}
	
	void Renderer::RenderDrawLine(glm::ivec2& p1, glm::ivec2& p2){
		RenderDrawLine(p1.x, p1.y, p2.x, p2.y);
	}

	void Renderer::RenderDrawLine(Point p1, Point p2){
		RenderDrawLine(p1.x, p1.y, p2.x, p2.y);
	}
	
	void Renderer::RenderDrawLine(Point& p1, Point& p2){
		RenderDrawLine(p1.x, p1.y, p2.x, p2.y);
	}

	void Renderer::RenderDrawLine(int x1, int y1, int x2, int y2){
		if(SDL_RenderDrawLine(m_renderer, x1, y1, x2, y2) != 0)
			throw Error();
	}

	void Renderer::RenderDrawLines(std::vector<Point>& points){
		if(SDL_RenderDrawLines(m_renderer, points.data(), points.size()) != 0)
			throw Error();
	}

	void Renderer::RenderDrawRect(Rect& rect){
		if(SDL_RenderDrawRect(m_renderer, &rect) != 0)
			throw Error();
	}

	void Renderer::RenderDrawRects(std::vector<Rect>& rects){
		if(SDL_RenderDrawRects(m_renderer, rects.data(), rects.size()) != 0)
			throw Error();
	}

	void Renderer::RenderFillRect(Rect& rect){
		if(SDL_RenderFillRect(m_renderer, &rect) != 0)
			throw Error();
	}

	void Renderer::RenderFillRects(std::vector<Rect>& rects){
		if(SDL_RenderFillRects(m_renderer, rects.data(), rects.size()) != 0)
			throw Error();
	}

	void Renderer::RenderPresent(){
		SDL_RenderPresent(m_renderer);
	}
	
	void Renderer::SetRenderDrawColor(glm::i8vec4 color){
		SetRenderDrawColor(color.r, color.g, color.b, color.a);
	}
	
	void Renderer::SetRenderDrawColor(glm::i8vec4& color){
		SetRenderDrawColor(color.r, color.g, color.b, color.a);
	}
	
	void Renderer::SetRenderDrawColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a){
		if(SDL_SetRenderDrawColor(m_renderer, r, g, b, a) != 0)
			throw Error();
	}



	// static SDL_Renderer * SDL_CreateSoftwareRenderer(SDL_Surface * surface);
	// 
	// 
	// extern DECLSPEC SDL_Texture * SDL_CreateTextureFromSurface(SDL_Renderer * renderer, SDL_Surface * surface);
	// 
	// extern DECLSPEC int SDL_SetRenderTarget(SDL_Renderer *renderer,
	//                                                 SDL_Texture *texture);
	// 
	// extern DECLSPEC SDL_Texture * SDL_GetRenderTarget(SDL_Renderer *renderer);
	// 
	// extern DECLSPEC int SDL_RenderSetLogicalSize(SDL_Renderer * renderer, int w, int h);
	// 
	// extern DECLSPEC void SDL_RenderGetLogicalSize(SDL_Renderer * renderer, int *w, int *h);
	// 
	// extern DECLSPEC int SDL_RenderSetViewport(SDL_Renderer * renderer,
	//                                                   const SDL_Rect * rect);
	// 
	// extern DECLSPEC void SDL_RenderGetViewport(SDL_Renderer * renderer,
	//                                                    SDL_Rect * rect);
	// 
	// extern DECLSPEC int SDL_RenderSetClipRect(SDL_Renderer * renderer,
	//                                                   const SDL_Rect * rect);
	// 
	// extern DECLSPEC void SDL_RenderGetClipRect(SDL_Renderer * renderer,
	//                                                    SDL_Rect * rect);
	// 
	// extern DECLSPEC int SDL_RenderSetScale(SDL_Renderer * renderer,
	//                                                float scaleX, float scaleY);
	// 
	// extern DECLSPEC void SDL_RenderGetScale(SDL_Renderer * renderer,
	//                                                float *scaleX, float *scaleY);
	// 
	// extern DECLSPEC int SDL_GetRenderDrawColor(SDL_Renderer * renderer,
	//                                            uint8_t * r, uint8_t * g, uint8_t * b,
	//                                            uint8_t * a);
	// 
	// extern DECLSPEC int SDL_SetRenderDrawBlendMode(SDL_Renderer * renderer,
	//                                                        SDL_BlendMode blendMode);
	// 
	// extern DECLSPEC int SDL_GetRenderDrawBlendMode(SDL_Renderer * renderer,
	//                                                        SDL_BlendMode *blendMode);
	// 

	// extern DECLSPEC int SDL_RenderCopy(SDL_Renderer * renderer,
	//                                            SDL_Texture * texture,
	//                                            const SDL_Rect * srcrect,
	//                                            const SDL_Rect * dstrect);
	// 
	// extern DECLSPEC int SDL_RenderCopyEx(SDL_Renderer * renderer,
	//                                            SDL_Texture * texture,
	//                                            const SDL_Rect * srcrect,
	//                                            const SDL_Rect * dstrect,
	//                                            const double angle,
	//                                            const SDL_Point *center,
	//                                            const SDL_RendererFlip flip);
	// 
	// extern DECLSPEC int SDL_RenderReadPixels(SDL_Renderer * renderer,
	//                                                  const SDL_Rect * rect,
	//                                                  uint32_t format,
	//                                                  void *pixels, int pitch);
	// 


}
