#ifndef SDL2PP_RENDERER
#define SDL2PP_RENDERER

#include <cstdint>
#include <vector>
#include <glm/glm.hpp>
#include "point.h"
#include "rect.h"

class SDL_Renderer;

namespace SDL{

	class Renderer{
		public:
			Renderer();
			~Renderer();
			Renderer(SDL_Renderer* renderer);

			void DestroyRenderer();


			static auto GetNumRenderDrivers();

			static auto GetRenderDriverInfo(int index);

			auto GetRendererInfo();

			auto GetRendererOutputSize();

			auto CreateTexture(uint32_t format, int access, int w, int h);

			auto RenderTargetSupported();

			void RenderClear();

			void RenderDrawPoint(glm::ivec2 p);
			void RenderDrawPoint(glm::ivec2& p);
			void RenderDrawPoint(Point p);
			void RenderDrawPoint(Point& p);

			void RenderDrawPoint(int x, int y);

			void RenderDrawPoints(std::vector<Point>& points);

			void RenderDrawLine(glm::ivec2 p1, glm::ivec2 p2);
			void RenderDrawLine(glm::ivec2& p1, glm::ivec2& p2);
			void RenderDrawLine(Point p1, Point p2);
			void RenderDrawLine(Point& p1, Point& p2);

			void RenderDrawLine(int x1, int y1, int x2, int y2);

			void RenderDrawLines(std::vector<Point>& points);

			void RenderDrawRect(Rect& rect);

			void RenderDrawRects(std::vector<Rect>& rects);

			void RenderFillRect(Rect& rect);

			void RenderFillRects(std::vector<Rect>& rects);
			void RenderPresent();
			void SetRenderDrawColor(glm::i8vec4 color);
			void SetRenderDrawColor(glm::i8vec4& color);
			void SetRenderDrawColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a);


		private:
			SDL_Renderer* m_renderer = nullptr;



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



	};

}

#endif
