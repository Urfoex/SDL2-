#include <iostream>
#include <SDL.h>
#include <tuple>
#include <utility>
#include <memory>

namespace SDL{

class Point;
class Renderer;
class Texture;
class Window;

template<typename T>
class Vector2D{
    public:
        //Point(){}
        union {
            T x;
            T w;
        };
        union {
            T y;
            T h;
        };
};

class Window{
    public:
        Window(){/*STUB*/}
        Window(SDL_Window*){/*STUB*/}
        Window(SDL_Window*, SDL_Renderer*){/*STUB*/}

        static auto CreateWindowAndRenderer(int width, int height, Uint32 window_flags){
            SDL_Renderer* renderer = nullptr;
            SDL_Window* sdlWindow = nullptr;
            if(SDL_CreateWindowAndRenderer(width, height, window_flags, &sdlWindow, &renderer) != 0)
                throw SDL_GetError();
            else{
                auto window = std::make_shared<Window>(sdlWindow, renderer);
                return std::make_pair(window, window->GetRenderer());
            }
        }

        auto CreateRenderer(int index, Uint32 flags){
            auto* sdlRenderer = SDL_CreateRenderer(m_window, index, flags);
            if(sdlRenderer == nullptr)
                throw SDL_GetError();
            else{
                m_renderer = std::make_shared<Renderer>(sdlRenderer);
                return m_renderer;
            }
        }

        std::shared_ptr<Renderer> GetRenderer(){return m_renderer;}


    private:
        SDL_Window* m_window = nullptr;
        std::shared_ptr<Renderer> m_renderer;

};

class Texture{
    public:
        Texture(){/*STUB*/}
        Texture(SDL_Texture*){/*STUB*/}

    private:
        SDL_Texture* m_texture = nullptr;
// extern DECLSPEC int SDL_QueryTexture(SDL_Texture * texture,
//                                              Uint32 * format, int *access,
//                                              int *w, int *h);
// 
// extern DECLSPEC int SDL_SetTextureColorMod(SDL_Texture * texture,
//                                                    Uint8 r, Uint8 g, Uint8 b);
// 
// 
// extern DECLSPEC int SDL_GetTextureColorMod(SDL_Texture * texture,
//                                                    Uint8 * r, Uint8 * g,
//                                                    Uint8 * b);
// 
// extern DECLSPEC int SDL_SetTextureAlphaMod(SDL_Texture * texture,
//                                                    Uint8 alpha);
// 
// extern DECLSPEC int SDL_GetTextureAlphaMod(SDL_Texture * texture,
//                                                    Uint8 * alpha);
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
//                                                  const Uint8 *Yplane, int Ypitch,
//                                                  const Uint8 *Uplane, int Upitch,
//                                                  const Uint8 *Vplane, int Vpitch);
// 
// extern DECLSPEC int SDL_LockTexture(SDL_Texture * texture,
//                                             const SDL_Rect * rect,
//                                             void **pixels, int *pitch);
// 
// extern DECLSPEC void SDL_UnlockTexture(SDL_Texture * texture);
// 
};

class Renderer{
    public:
        Renderer(){/*STUB*/}
        Renderer(SDL_Renderer*){/*STUB*/}

        static auto GetNumRenderDrivers(){
            auto numRenderDrivers = SDL_GetNumRenderDrivers();
            if(numRenderDrivers >= 1)
                return numRenderDrivers;
            else
                throw SDL_GetError();
        }

        static auto GetRenderDriverInfo(int index){
            SDL_RendererInfo info;
            if( SDL_GetRenderDriverInfo(index, &info) != 0)
                throw SDL_GetError();
            else
                return info;
        }

        auto GetRendererInfo(){
            SDL_RendererInfo info;
            if(SDL_GetRendererInfo(m_renderer, &info) != 0)
                throw SDL_GetError();
            else
                return info;
        }

        auto GetRendererOutputSize(){
            Vector2D<int> wh;
            if(SDL_GetRendererOutputSize(m_renderer, &(wh.w), &(wh.h)) != 0)
                throw SDL_GetError();
            else
                return wh;
        }

        auto CreateTexture(Uint32 format, int access, int w, int h){
            auto* sdlTexture = SDL_CreateTexture(m_renderer, format, access, w, h);
            if( sdlTexture == nullptr)
                throw SDL_GetError();
            else
                return std::make_shared<Texture>(sdlTexture);
        }

        auto RenderTargetSupported(){return SDL_RenderTargetSupported(m_renderer);}



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
// extern DECLSPEC int SDL_SetRenderDrawColor(SDL_Renderer * renderer,
//                                            Uint8 r, Uint8 g, Uint8 b,
//                                            Uint8 a);
// 
// extern DECLSPEC int SDL_GetRenderDrawColor(SDL_Renderer * renderer,
//                                            Uint8 * r, Uint8 * g, Uint8 * b,
//                                            Uint8 * a);
// 
// extern DECLSPEC int SDL_SetRenderDrawBlendMode(SDL_Renderer * renderer,
//                                                        SDL_BlendMode blendMode);
// 
// extern DECLSPEC int SDL_GetRenderDrawBlendMode(SDL_Renderer * renderer,
//                                                        SDL_BlendMode *blendMode);
// 
// extern DECLSPEC int SDL_RenderClear(SDL_Renderer * renderer);
// 
// extern DECLSPEC int SDL_RenderDrawPoint(SDL_Renderer * renderer,
//                                                 int x, int y);
// 
// extern DECLSPEC int SDL_RenderDrawPoints(SDL_Renderer * renderer,
//                                                  const SDL_Point * points,
//                                                  int count);
// 
// extern DECLSPEC int SDL_RenderDrawLine(SDL_Renderer * renderer,
//                                                int x1, int y1, int x2, int y2);
// 
// extern DECLSPEC int SDL_RenderDrawLines(SDL_Renderer * renderer,
//                                                 const SDL_Point * points,
//                                                 int count);
// 
// extern DECLSPEC int SDL_RenderDrawRect(SDL_Renderer * renderer,
//                                                const SDL_Rect * rect);
// 
// extern DECLSPEC int SDL_RenderDrawRects(SDL_Renderer * renderer,
//                                                 const SDL_Rect * rects,
//                                                 int count);
// 
// extern DECLSPEC int SDL_RenderFillRect(SDL_Renderer * renderer,
//                                                const SDL_Rect * rect);
// 
// extern DECLSPEC int SDL_RenderFillRects(SDL_Renderer * renderer,
//                                                 const SDL_Rect * rects,
//                                                 int count);
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
//                                                  Uint32 format,
//                                                  void *pixels, int pitch);
// 
// extern DECLSPEC void SDL_RenderPresent(SDL_Renderer * renderer);
// 
// extern DECLSPEC void SDL_DestroyTexture(SDL_Texture * texture);
// 
// extern DECLSPEC void SDL_DestroyRenderer(SDL_Renderer * renderer);
// 
// 
// extern DECLSPEC int SDL_GL_BindTexture(SDL_Texture *texture, float *texw, float *texh);
// 
// extern DECLSPEC int SDL_GL_UnbindTexture(SDL_Texture *texture);
    
};
}

int main(int argc, char** argv){

    return 0;
}
