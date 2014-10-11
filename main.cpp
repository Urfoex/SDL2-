#include <iostream>
#include <SDL.h>
#include <tuple>
#include <utility>
#include <memory>
#include <vector>
#include <stdexcept>
#include <cstdint>

namespace SDL{

    template<typename T> class Vector2D;
    template<typename T> class Vector4D;
    typedef Vector4D<uint8_t> Color;
    typedef SDL_Rect Rect;
    typedef SDL_Point Point;
    class Application;
    class Renderer;
    class Texture;
    class Window;
    class Error;

    class Error : public std::runtime_error{
        public:
            static std::string Get(){ return SDL_GetError(); }
            Error():runtime_error(Get()){}
            virtual ~Error(){}
    };

    template<typename T>
        class Vector2D{
            public:
                union { T x; T w; };
                union { T y; T h; };
        };

    template<typename T>
        class Vector4D{
            public:
                union { T x; T r; };
                union { T y; T g; };
                union { T z; T b; };
                union { T w; T a; };
        };

    class Application{
        public:
            Application():Application(INIT::EVERYTHING){}

            Application(uint32_t flags){
                if(SDL_Init(flags) != 0)
                    throw Error();
            }

            ~Application(){ SDL_Quit(); }

            void InitSubSystem(uint32_t flags){
                if(SDL_InitSubSystem(flags) != 0)
                    throw Error();
            }

            void QuitSubSystem(uint32_t flags){ SDL_QuitSubSystem(flags); }
            auto WasInit(uint32_t flags){ return SDL_WasInit(flags); }

            enum INIT{
                TIMER          = SDL_INIT_TIMER,
                AUDIO          = SDL_INIT_AUDIO,
                VIDEO          = SDL_INIT_VIDEO,
                JOYSTICK       = SDL_INIT_JOYSTICK,
                HAPTIC         = SDL_INIT_HAPTIC,
                GAMECONTROLLER = SDL_INIT_GAMECONTROLLER,
                EVENTS         = SDL_INIT_EVENTS,
                NOPARACHUTE    = SDL_INIT_NOPARACHUTE,
                EVERYTHING     = SDL_INIT_EVERYTHING
            };
    };

    class Window{
        public:
            Window(){/*STUB*/}
            Window(SDL_Window* window):m_window(window){}
            Window(SDL_Window* window, SDL_Renderer* renderer):m_window(window){
                m_renderer = std::make_shared<Renderer>(renderer);
            }
            Window(std::string title, Rect dimension, uint32_t flags){
                ///
                /// \brief Create a window with the specified position, dimensions, and flags.
                ///
                /// \param title The title of the window, in UTF-8 encoding.
                /// \param x     The x position of the window, ::SDL_WINDOWPOS_CENTERED, or
                ///              ::SDL_WINDOWPOS_UNDEFINED.
                /// \param y     The y position of the window, ::SDL_WINDOWPOS_CENTERED, or
                ///              ::SDL_WINDOWPOS_UNDEFINED.
                /// \param w     The width of the window.
                /// \param h     The height of the window.
                /// \param flags The flags for the window, a mask of any of the following:
                ///              ::SDL_WINDOW_FULLSCREEN,    ::SDL_WINDOW_OPENGL,
                ///              ::SDL_WINDOW_HIDDEN,        ::SDL_WINDOW_BORDERLESS,
                ///              ::SDL_WINDOW_RESIZABLE,     ::SDL_WINDOW_MAXIMIZED,
                ///              ::SDL_WINDOW_MINIMIZED,     ::SDL_WINDOW_INPUT_GRABBED,
                ///              ::SDL_WINDOW_ALLOW_HIGHDPI.
                ///
                /// \return The id of the window created, or zero if window creation failed.
                ///
                /// \sa SDL_DestroyWindow()
                ///
                m_window = SDL_CreateWindow(title.c_str(), dimension.x, dimension.y, dimension.w, dimension.h, flags); 
                if(m_window == nullptr)
                    throw Error();
            }

            ~Window(){ SDL_DestroyWindow(m_window); }

            static auto CreateWindowAndRenderer(int width, int height, uint32_t window_flags){
                SDL_Renderer* renderer = nullptr;
                SDL_Window* sdlWindow = nullptr;
                if(SDL_CreateWindowAndRenderer(width, height, window_flags, &sdlWindow, &renderer) != 0)
                    throw Error();
                else{
                    auto window = std::make_shared<Window>(sdlWindow, renderer);
                    return std::make_pair(window, window->GetRenderer());
                }
            }

            auto CreateRenderer(int index, uint32_t flags){
                auto* sdlRenderer = SDL_CreateRenderer(m_window, index, flags);
                if(sdlRenderer == nullptr)
                    throw Error();
                else{
                    m_renderer = std::make_shared<Renderer>(sdlRenderer);
                    return m_renderer;
                }
            }

            std::shared_ptr<Renderer> GetRenderer(){return m_renderer;}


        private:
            SDL_Window* m_window = nullptr;
            std::shared_ptr<Renderer> m_renderer;



//// extern DECLSPEC int SDLCALL SDL_GetNumVideoDrivers(void);
//// 
//// /**
////  *  \brief Get the name of a built in video driver.
////  *
////  *  \note The video drivers are presented in the order in which they are
////  *        normally checked during initialization.
////  *
////  *  \sa SDL_GetNumVideoDrivers()
////  */
//// extern DECLSPEC const char *SDLCALL SDL_GetVideoDriver(int index);
//// 
//// /**
////  *  \brief Initialize the video subsystem, optionally specifying a video driver.
////  *
////  *  \param driver_name Initialize a specific driver by name, or NULL for the
////  *                     default video driver.
////  *
////  *  \return 0 on success, -1 on error
////  *
////  *  This function initializes the video subsystem; setting up a connection
////  *  to the window manager, etc, and determines the available display modes
////  *  and pixel formats, but does not initialize a window or graphics mode.
////  *
////  *  \sa SDL_VideoQuit()
////  */
//// extern DECLSPEC int SDLCALL SDL_VideoInit(const char *driver_name);
//// 
//// /**
////  *  \brief Shuts down the video subsystem.
////  *
////  *  This function closes all windows, and restores the original video mode.
////  *
////  *  \sa SDL_VideoInit()
////  */
//// extern DECLSPEC void SDLCALL SDL_VideoQuit(void);
//// 
//// /**
////  *  \brief Returns the name of the currently initialized video driver.
////  *
////  *  \return The name of the current video driver or NULL if no driver
////  *          has been initialized
////  *
////  *  \sa SDL_GetNumVideoDrivers()
////  *  \sa SDL_GetVideoDriver()
////  */
//// extern DECLSPEC const char *SDLCALL SDL_GetCurrentVideoDriver(void);
//// 
//// /**
////  *  \brief Returns the number of available video displays.
////  *
////  *  \sa SDL_GetDisplayBounds()
////  */
//// extern DECLSPEC int SDLCALL SDL_GetNumVideoDisplays(void);
//// 
//// /**
////  *  \brief Get the name of a display in UTF-8 encoding
////  *
////  *  \return The name of a display, or NULL for an invalid display index.
////  *
////  *  \sa SDL_GetNumVideoDisplays()
////  */
//// extern DECLSPEC const char * SDLCALL SDL_GetDisplayName(int displayIndex);
//// 
//// /**
////  *  \brief Get the desktop area represented by a display, with the primary
////  *         display located at 0,0
////  *
////  *  \return 0 on success, or -1 if the index is out of range.
////  *
////  *  \sa SDL_GetNumVideoDisplays()
////  */
//// extern DECLSPEC int SDLCALL SDL_GetDisplayBounds(int displayIndex, SDL_Rect * rect);
//// 
//// /**
////  *  \brief Returns the number of available display modes.
////  *
////  *  \sa SDL_GetDisplayMode()
////  */
//// extern DECLSPEC int SDLCALL SDL_GetNumDisplayModes(int displayIndex);
//// 
//// /**
////  *  \brief Fill in information about a specific display mode.
////  *
////  *  \note The display modes are sorted in this priority:
////  *        \li bits per pixel -> more colors to fewer colors
////  *        \li width -> largest to smallest
////  *        \li height -> largest to smallest
////  *        \li refresh rate -> highest to lowest
////  *
////  *  \sa SDL_GetNumDisplayModes()
////  */
//// extern DECLSPEC int SDLCALL SDL_GetDisplayMode(int displayIndex, int modeIndex,
////                                                SDL_DisplayMode * mode);
//// 
//// /**
////  *  \brief Fill in information about the desktop display mode.
////  */
//// extern DECLSPEC int SDLCALL SDL_GetDesktopDisplayMode(int displayIndex, SDL_DisplayMode * mode);
//// 
//// /**
////  *  \brief Fill in information about the current display mode.
////  */
//// extern DECLSPEC int SDLCALL SDL_GetCurrentDisplayMode(int displayIndex, SDL_DisplayMode * mode);
//// 
//// 
//// /**
////  *  \brief Get the closest match to the requested display mode.
////  *
////  *  \param displayIndex The index of display from which mode should be queried.
////  *  \param mode The desired display mode
////  *  \param closest A pointer to a display mode to be filled in with the closest
////  *                 match of the available display modes.
////  *
////  *  \return The passed in value \c closest, or NULL if no matching video mode
////  *          was available.
////  *
////  *  The available display modes are scanned, and \c closest is filled in with the
////  *  closest mode matching the requested mode and returned.  The mode format and
////  *  refresh_rate default to the desktop mode if they are 0.  The modes are
////  *  scanned with size being first priority, format being second priority, and
////  *  finally checking the refresh_rate.  If all the available modes are too
////  *  small, then NULL is returned.
////  *
////  *  \sa SDL_GetNumDisplayModes()
////  *  \sa SDL_GetDisplayMode()
////  */
//// extern DECLSPEC SDL_DisplayMode * SDLCALL SDL_GetClosestDisplayMode(int displayIndex, const SDL_DisplayMode * mode, SDL_DisplayMode * closest);
//// 
//// /**
////  *  \brief Get the display index associated with a window.
////  *
////  *  \return the display index of the display containing the center of the
////  *          window, or -1 on error.
////  */
//// extern DECLSPEC int SDLCALL SDL_GetWindowDisplayIndex(SDL_Window * window);
//// 
//// /**
////  *  \brief Set the display mode used when a fullscreen window is visible.
////  *
////  *  By default the window's dimensions and the desktop format and refresh rate
////  *  are used.
////  *
////  *  \param window The window for which the display mode should be set.
////  *  \param mode The mode to use, or NULL for the default mode.
////  *
////  *  \return 0 on success, or -1 if setting the display mode failed.
////  *
////  *  \sa SDL_GetWindowDisplayMode()
////  *  \sa SDL_SetWindowFullscreen()
////  */
//// extern DECLSPEC int SDLCALL SDL_SetWindowDisplayMode(SDL_Window * window,
////                                                      const SDL_DisplayMode
////                                                          * mode);
//// 
//// /**
////  *  \brief Fill in information about the display mode used when a fullscreen
////  *         window is visible.
////  *
////  *  \sa SDL_SetWindowDisplayMode()
////  *  \sa SDL_SetWindowFullscreen()
////  */
//// extern DECLSPEC int SDLCALL SDL_GetWindowDisplayMode(SDL_Window * window,
////                                                      SDL_DisplayMode * mode);
//// 
//// /**
////  *  \brief Get the pixel format associated with the window.
////  */
//// extern DECLSPEC Uint32 SDLCALL SDL_GetWindowPixelFormat(SDL_Window * window);
//// 
//// /**
////  *  \brief Create an SDL window from an existing native window.
////  *
////  *  \param data A pointer to driver-dependent window creation data
////  *
////  *  \return The id of the window created, or zero if window creation failed.
////  *
////  *  \sa SDL_DestroyWindow()
////  */
//// extern DECLSPEC SDL_Window * SDLCALL SDL_CreateWindowFrom(const void *data);
//// 
//// /**
////  *  \brief Get the numeric ID of a window, for logging purposes.
////  */
//// extern DECLSPEC Uint32 SDLCALL SDL_GetWindowID(SDL_Window * window);
//// 
//// /**
////  *  \brief Get a window from a stored ID, or NULL if it doesn't exist.
////  */
//// extern DECLSPEC SDL_Window * SDLCALL SDL_GetWindowFromID(Uint32 id);
//// 
//// /**
////  *  \brief Get the window flags.
////  */
//// extern DECLSPEC Uint32 SDLCALL SDL_GetWindowFlags(SDL_Window * window);
//// 
//// /**
////  *  \brief Set the title of a window, in UTF-8 format.
////  *
////  *  \sa SDL_GetWindowTitle()
////  */
//// extern DECLSPEC void SDLCALL SDL_SetWindowTitle(SDL_Window * window,
////                                                 const char *title);
//// 
//// /**
////  *  \brief Get the title of a window, in UTF-8 format.
////  *
////  *  \sa SDL_SetWindowTitle()
////  */
//// extern DECLSPEC const char *SDLCALL SDL_GetWindowTitle(SDL_Window * window);
//// 
//// /**
////  *  \brief Set the icon for a window.
////  *
////  *  \param window The window for which the icon should be set.
////  *  \param icon The icon for the window.
////  */
//// extern DECLSPEC void SDLCALL SDL_SetWindowIcon(SDL_Window * window,
////                                                SDL_Surface * icon);
//// 
//// /**
////  *  \brief Associate an arbitrary named pointer with a window.
////  *
////  *  \param window   The window to associate with the pointer.
////  *  \param name     The name of the pointer.
////  *  \param userdata The associated pointer.
////  *
////  *  \return The previous value associated with 'name'
////  *
////  *  \note The name is case-sensitive.
////  *
////  *  \sa SDL_GetWindowData()
////  */
//// extern DECLSPEC void* SDLCALL SDL_SetWindowData(SDL_Window * window,
////                                                 const char *name,
////                                                 void *userdata);
//// 
//// /**
////  *  \brief Retrieve the data pointer associated with a window.
////  *
////  *  \param window   The window to query.
////  *  \param name     The name of the pointer.
////  *
////  *  \return The value associated with 'name'
////  *
////  *  \sa SDL_SetWindowData()
////  */
//// extern DECLSPEC void *SDLCALL SDL_GetWindowData(SDL_Window * window,
////                                                 const char *name);
//// 
//// /**
////  *  \brief Set the position of a window.
////  *
////  *  \param window   The window to reposition.
////  *  \param x        The x coordinate of the window, ::SDL_WINDOWPOS_CENTERED, or
////                     ::SDL_WINDOWPOS_UNDEFINED.
////  *  \param y        The y coordinate of the window, ::SDL_WINDOWPOS_CENTERED, or
////                     ::SDL_WINDOWPOS_UNDEFINED.
////  *
////  *  \note The window coordinate origin is the upper left of the display.
////  *
////  *  \sa SDL_GetWindowPosition()
////  */
//// extern DECLSPEC void SDLCALL SDL_SetWindowPosition(SDL_Window * window,
////                                                    int x, int y);
//// 
//// /**
////  *  \brief Get the position of a window.
////  *
////  *  \param window   The window to query.
////  *  \param x        Pointer to variable for storing the x position, may be NULL
////  *  \param y        Pointer to variable for storing the y position, may be NULL
////  *
////  *  \sa SDL_SetWindowPosition()
////  */
//// extern DECLSPEC void SDLCALL SDL_GetWindowPosition(SDL_Window * window,
////                                                    int *x, int *y);
//// 
//// /**
////  *  \brief Set the size of a window's client area.
////  *
////  *  \param window   The window to resize.
////  *  \param w        The width of the window, must be >0
////  *  \param h        The height of the window, must be >0
////  *
////  *  \note You can't change the size of a fullscreen window, it automatically
////  *        matches the size of the display mode.
////  *
////  *  \sa SDL_GetWindowSize()
////  */
//// extern DECLSPEC void SDLCALL SDL_SetWindowSize(SDL_Window * window, int w,
////                                                int h);
//// 
//// /**
////  *  \brief Get the size of a window's client area.
////  *
////  *  \param window   The window to query.
////  *  \param w        Pointer to variable for storing the width, may be NULL
////  *  \param h        Pointer to variable for storing the height, may be NULL
////  *
////  *  \sa SDL_SetWindowSize()
////  */
//// extern DECLSPEC void SDLCALL SDL_GetWindowSize(SDL_Window * window, int *w,
////                                                int *h);
//// 
//// /**
////  *  \brief Set the minimum size of a window's client area.
////  *
////  *  \param window    The window to set a new minimum size.
////  *  \param min_w     The minimum width of the window, must be >0
////  *  \param min_h     The minimum height of the window, must be >0
////  *
////  *  \note You can't change the minimum size of a fullscreen window, it
////  *        automatically matches the size of the display mode.
////  *
////  *  \sa SDL_GetWindowMinimumSize()
////  *  \sa SDL_SetWindowMaximumSize()
////  */
//// extern DECLSPEC void SDLCALL SDL_SetWindowMinimumSize(SDL_Window * window,
////                                                       int min_w, int min_h);
//// 
//// /**
////  *  \brief Get the minimum size of a window's client area.
////  *
////  *  \param window   The window to query.
////  *  \param w        Pointer to variable for storing the minimum width, may be NULL
////  *  \param h        Pointer to variable for storing the minimum height, may be NULL
////  *
////  *  \sa SDL_GetWindowMaximumSize()
////  *  \sa SDL_SetWindowMinimumSize()
////  */
//// extern DECLSPEC void SDLCALL SDL_GetWindowMinimumSize(SDL_Window * window,
////                                                       int *w, int *h);
//// 
//// /**
////  *  \brief Set the maximum size of a window's client area.
////  *
////  *  \param window    The window to set a new maximum size.
////  *  \param max_w     The maximum width of the window, must be >0
////  *  \param max_h     The maximum height of the window, must be >0
////  *
////  *  \note You can't change the maximum size of a fullscreen window, it
////  *        automatically matches the size of the display mode.
////  *
////  *  \sa SDL_GetWindowMaximumSize()
////  *  \sa SDL_SetWindowMinimumSize()
////  */
//// extern DECLSPEC void SDLCALL SDL_SetWindowMaximumSize(SDL_Window * window,
////                                                       int max_w, int max_h);
//// 
//// /**
////  *  \brief Get the maximum size of a window's client area.
////  *
////  *  \param window   The window to query.
////  *  \param w        Pointer to variable for storing the maximum width, may be NULL
////  *  \param h        Pointer to variable for storing the maximum height, may be NULL
////  *
////  *  \sa SDL_GetWindowMinimumSize()
////  *  \sa SDL_SetWindowMaximumSize()
////  */
//// extern DECLSPEC void SDLCALL SDL_GetWindowMaximumSize(SDL_Window * window,
////                                                       int *w, int *h);
//// 
//// /**
////  *  \brief Set the border state of a window.
////  *
////  *  This will add or remove the window's SDL_WINDOW_BORDERLESS flag and
////  *  add or remove the border from the actual window. This is a no-op if the
////  *  window's border already matches the requested state.
////  *
////  *  \param window The window of which to change the border state.
////  *  \param bordered SDL_FALSE to remove border, SDL_TRUE to add border.
////  *
////  *  \note You can't change the border state of a fullscreen window.
////  *
////  *  \sa SDL_GetWindowFlags()
////  */
//// extern DECLSPEC void SDLCALL SDL_SetWindowBordered(SDL_Window * window,
////                                                    SDL_bool bordered);
//// 
//// /**
////  *  \brief Show a window.
////  *
////  *  \sa SDL_HideWindow()
////  */
//// extern DECLSPEC void SDLCALL SDL_ShowWindow(SDL_Window * window);
//// 
//// /**
////  *  \brief Hide a window.
////  *
////  *  \sa SDL_ShowWindow()
////  */
//// extern DECLSPEC void SDLCALL SDL_HideWindow(SDL_Window * window);
//// 
//// /**
////  *  \brief Raise a window above other windows and set the input focus.
////  */
//// extern DECLSPEC void SDLCALL SDL_RaiseWindow(SDL_Window * window);
//// 
//// /**
////  *  \brief Make a window as large as possible.
////  *
////  *  \sa SDL_RestoreWindow()
////  */
//// extern DECLSPEC void SDLCALL SDL_MaximizeWindow(SDL_Window * window);
//// 
//// /**
////  *  \brief Minimize a window to an iconic representation.
////  *
////  *  \sa SDL_RestoreWindow()
////  */
//// extern DECLSPEC void SDLCALL SDL_MinimizeWindow(SDL_Window * window);
//// 
//// /**
////  *  \brief Restore the size and position of a minimized or maximized window.
////  *
////  *  \sa SDL_MaximizeWindow()
////  *  \sa SDL_MinimizeWindow()
////  */
//// extern DECLSPEC void SDLCALL SDL_RestoreWindow(SDL_Window * window);
//// 
//// /**
////  *  \brief Set a window's fullscreen state.
////  *
////  *  \return 0 on success, or -1 if setting the display mode failed.
////  *
////  *  \sa SDL_SetWindowDisplayMode()
////  *  \sa SDL_GetWindowDisplayMode()
////  */
//// extern DECLSPEC int SDLCALL SDL_SetWindowFullscreen(SDL_Window * window,
////                                                     Uint32 flags);
//// 
//// /**
////  *  \brief Get the SDL surface associated with the window.
////  *
////  *  \return The window's framebuffer surface, or NULL on error.
////  *
////  *  A new surface will be created with the optimal format for the window,
////  *  if necessary. This surface will be freed when the window is destroyed.
////  *
////  *  \note You may not combine this with 3D or the rendering API on this window.
////  *
////  *  \sa SDL_UpdateWindowSurface()
////  *  \sa SDL_UpdateWindowSurfaceRects()
////  */
//// extern DECLSPEC SDL_Surface * SDLCALL SDL_GetWindowSurface(SDL_Window * window);
//// 
//// /**
////  *  \brief Copy the window surface to the screen.
////  *
////  *  \return 0 on success, or -1 on error.
////  *
////  *  \sa SDL_GetWindowSurface()
////  *  \sa SDL_UpdateWindowSurfaceRects()
////  */
//// extern DECLSPEC int SDLCALL SDL_UpdateWindowSurface(SDL_Window * window);
//// 
//// /**
////  *  \brief Copy a number of rectangles on the window surface to the screen.
////  *
////  *  \return 0 on success, or -1 on error.
////  *
////  *  \sa SDL_GetWindowSurface()
////  *  \sa SDL_UpdateWindowSurfaceRect()
////  */
//// extern DECLSPEC int SDLCALL SDL_UpdateWindowSurfaceRects(SDL_Window * window,
////                                                          const SDL_Rect * rects,
////                                                          int numrects);
//// 
//// /**
////  *  \brief Set a window's input grab mode.
////  *
////  *  \param window The window for which the input grab mode should be set.
////  *  \param grabbed This is SDL_TRUE to grab input, and SDL_FALSE to release input.
////  *
////  *  \sa SDL_GetWindowGrab()
////  */
//// extern DECLSPEC void SDLCALL SDL_SetWindowGrab(SDL_Window * window,
////                                                SDL_bool grabbed);
//// 
//// /**
////  *  \brief Get a window's input grab mode.
////  *
////  *  \return This returns SDL_TRUE if input is grabbed, and SDL_FALSE otherwise.
////  *
////  *  \sa SDL_SetWindowGrab()
////  */
//// extern DECLSPEC SDL_bool SDLCALL SDL_GetWindowGrab(SDL_Window * window);
//// 
//// /**
////  *  \brief Set the brightness (gamma correction) for a window.
////  *
////  *  \return 0 on success, or -1 if setting the brightness isn't supported.
////  *
////  *  \sa SDL_GetWindowBrightness()
////  *  \sa SDL_SetWindowGammaRamp()
////  */
//// extern DECLSPEC int SDLCALL SDL_SetWindowBrightness(SDL_Window * window, float brightness);
//// 
//// /**
////  *  \brief Get the brightness (gamma correction) for a window.
////  *
////  *  \return The last brightness value passed to SDL_SetWindowBrightness()
////  *
////  *  \sa SDL_SetWindowBrightness()
////  */
//// extern DECLSPEC float SDLCALL SDL_GetWindowBrightness(SDL_Window * window);
//// 
//// /**
////  *  \brief Set the gamma ramp for a window.
////  *
////  *  \param window The window for which the gamma ramp should be set.
////  *  \param red The translation table for the red channel, or NULL.
////  *  \param green The translation table for the green channel, or NULL.
////  *  \param blue The translation table for the blue channel, or NULL.
////  *
////  *  \return 0 on success, or -1 if gamma ramps are unsupported.
////  *
////  *  Set the gamma translation table for the red, green, and blue channels
////  *  of the video hardware.  Each table is an array of 256 16-bit quantities,
////  *  representing a mapping between the input and output for that channel.
////  *  The input is the index into the array, and the output is the 16-bit
////  *  gamma value at that index, scaled to the output color precision.
////  *
////  *  \sa SDL_GetWindowGammaRamp()
////  */
//// extern DECLSPEC int SDLCALL SDL_SetWindowGammaRamp(SDL_Window * window,
////                                                    const Uint16 * red,
////                                                    const Uint16 * green,
////                                                    const Uint16 * blue);
//// 
//// /**
////  *  \brief Get the gamma ramp for a window.
////  *
////  *  \param window The window from which the gamma ramp should be queried.
////  *  \param red   A pointer to a 256 element array of 16-bit quantities to hold
////  *               the translation table for the red channel, or NULL.
////  *  \param green A pointer to a 256 element array of 16-bit quantities to hold
////  *               the translation table for the green channel, or NULL.
////  *  \param blue  A pointer to a 256 element array of 16-bit quantities to hold
////  *               the translation table for the blue channel, or NULL.
////  *
////  *  \return 0 on success, or -1 if gamma ramps are unsupported.
////  *
////  *  \sa SDL_SetWindowGammaRamp()
////  */
//// extern DECLSPEC int SDLCALL SDL_GetWindowGammaRamp(SDL_Window * window,
////                                                    Uint16 * red,
////                                                    Uint16 * green,
////                                                    Uint16 * blue);
//// 
//// /**
////  *  \brief Returns whether the screensaver is currently enabled (default on).
////  *
////  *  \sa SDL_EnableScreenSaver()
////  *  \sa SDL_DisableScreenSaver()
////  */
//// extern DECLSPEC SDL_bool SDLCALL SDL_IsScreenSaverEnabled(void);
//// 
//// /**
////  *  \brief Allow the screen to be blanked by a screensaver
////  *
////  *  \sa SDL_IsScreenSaverEnabled()
////  *  \sa SDL_DisableScreenSaver()
////  */
//// extern DECLSPEC void SDLCALL SDL_EnableScreenSaver(void);
//// 
//// /**
////  *  \brief Prevent the screen from being blanked by a screensaver
////  *
////  *  \sa SDL_IsScreenSaverEnabled()
////  *  \sa SDL_EnableScreenSaver()
////  */
//// extern DECLSPEC void SDLCALL SDL_DisableScreenSaver(void);
//// 
//// 
//// /**
////  *  \name OpenGL support functions
////  */
//// /* @{ */
//// 
//// /**
////  *  \brief Dynamically load an OpenGL library.
////  *
////  *  \param path The platform dependent OpenGL library name, or NULL to open the
////  *              default OpenGL library.
////  *
////  *  \return 0 on success, or -1 if the library couldn't be loaded.
////  *
////  *  This should be done after initializing the video driver, but before
////  *  creating any OpenGL windows.  If no OpenGL library is loaded, the default
////  *  library will be loaded upon creation of the first OpenGL window.
////  *
////  *  \note If you do this, you need to retrieve all of the GL functions used in
////  *        your program from the dynamic library using SDL_GL_GetProcAddress().
////  *
////  *  \sa SDL_GL_GetProcAddress()
////  *  \sa SDL_GL_UnloadLibrary()
////  */
//// extern DECLSPEC int SDLCALL SDL_GL_LoadLibrary(const char *path);
//// 
//// /**
////  *  \brief Get the address of an OpenGL function.
////  */
//// extern DECLSPEC void *SDLCALL SDL_GL_GetProcAddress(const char *proc);
//// 
//// /**
////  *  \brief Unload the OpenGL library previously loaded by SDL_GL_LoadLibrary().
////  *
////  *  \sa SDL_GL_LoadLibrary()
////  */
//// extern DECLSPEC void SDLCALL SDL_GL_UnloadLibrary(void);
//// 
//// /**
////  *  \brief Return true if an OpenGL extension is supported for the current
////  *         context.
////  */
//// extern DECLSPEC SDL_bool SDLCALL SDL_GL_ExtensionSupported(const char
////                                                            *extension);
//// 
//// /**
////  *  \brief Reset all previously set OpenGL context attributes to their default values
////  */
//// extern DECLSPEC void SDLCALL SDL_GL_ResetAttributes(void);
//// 
//// /**
////  *  \brief Set an OpenGL window attribute before window creation.
////  */
//// extern DECLSPEC int SDLCALL SDL_GL_SetAttribute(SDL_GLattr attr, int value);
//// 
//// /**
////  *  \brief Get the actual value for an attribute from the current context.
////  */
//// extern DECLSPEC int SDLCALL SDL_GL_GetAttribute(SDL_GLattr attr, int *value);
//// 
//// /**
////  *  \brief Create an OpenGL context for use with an OpenGL window, and make it
////  *         current.
////  *
////  *  \sa SDL_GL_DeleteContext()
////  */
//// extern DECLSPEC SDL_GLContext SDLCALL SDL_GL_CreateContext(SDL_Window *
////                                                            window);
//// 
//// /**
////  *  \brief Set up an OpenGL context for rendering into an OpenGL window.
////  *
////  *  \note The context must have been created with a compatible window.
////  */
//// extern DECLSPEC int SDLCALL SDL_GL_MakeCurrent(SDL_Window * window,
////                                                SDL_GLContext context);
//// 
//// /**
////  *  \brief Get the currently active OpenGL window.
////  */
//// extern DECLSPEC SDL_Window* SDLCALL SDL_GL_GetCurrentWindow(void);
//// 
//// /**
////  *  \brief Get the currently active OpenGL context.
////  */
//// extern DECLSPEC SDL_GLContext SDLCALL SDL_GL_GetCurrentContext(void);
//// 
//// /**
////  *  \brief Get the size of a window's underlying drawable (for use with glViewport).
////  *
////  *  \param window   Window from which the drawable size should be queried
////  *  \param w        Pointer to variable for storing the width, may be NULL
////  *  \param h        Pointer to variable for storing the height, may be NULL
////  *
////  * This may differ from SDL_GetWindowSize if we're rendering to a high-DPI
////  * drawable, i.e. the window was created with SDL_WINDOW_ALLOW_HIGHDPI on a
////  * platform with high-DPI support (Apple calls this "Retina"), and not disabled
////  * by the SDL_HINT_VIDEO_HIGHDPI_DISABLED hint.
////  *
////  *  \sa SDL_GetWindowSize()
////  *  \sa SDL_CreateWindow()
////  */
//// extern DECLSPEC void SDLCALL SDL_GL_GetDrawableSize(SDL_Window * window, int *w,
////                                                     int *h);
//// 
//// /**
////  *  \brief Set the swap interval for the current OpenGL context.
////  *
////  *  \param interval 0 for immediate updates, 1 for updates synchronized with the
////  *                  vertical retrace. If the system supports it, you may
////  *                  specify -1 to allow late swaps to happen immediately
////  *                  instead of waiting for the next retrace.
////  *
////  *  \return 0 on success, or -1 if setting the swap interval is not supported.
////  *
////  *  \sa SDL_GL_GetSwapInterval()
////  */
//// extern DECLSPEC int SDLCALL SDL_GL_SetSwapInterval(int interval);
//// 
//// /**
////  *  \brief Get the swap interval for the current OpenGL context.
////  *
////  *  \return 0 if there is no vertical retrace synchronization, 1 if the buffer
////  *          swap is synchronized with the vertical retrace, and -1 if late
////  *          swaps happen immediately instead of waiting for the next retrace.
////  *          If the system can't determine the swap interval, or there isn't a
////  *          valid current context, this will return 0 as a safe default.
////  *
////  *  \sa SDL_GL_SetSwapInterval()
////  */
//// extern DECLSPEC int SDLCALL SDL_GL_GetSwapInterval(void);
//// 
//// /**
////  * \brief Swap the OpenGL buffers for a window, if double-buffering is
////  *        supported.
////  */
//// extern DECLSPEC void SDLCALL SDL_GL_SwapWindow(SDL_Window * window);
//// 
//// /**
////  *  \brief Delete an OpenGL context.
////  *
////  *  \sa SDL_GL_CreateContext()
////  */
//// extern DECLSPEC void SDLCALL SDL_GL_DeleteContext(SDL_GLContext context);

    };

    class Texture{
        public:
            Texture(){/*STUB*/}
            Texture(SDL_Texture*){/*STUB*/}
            ~Texture(){ if(m_texture != nullptr) DestroyTexture(); }

            void DestroyTexture(){
                SDL_DestroyTexture(m_texture);
                m_texture = nullptr;
            }


        private:
            SDL_Texture* m_texture = nullptr;
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
    };

    class Renderer{
        public:
            Renderer(){/*STUB*/}
            ~Renderer(){ if(m_renderer != nullptr) DestroyRenderer(); }
            Renderer(SDL_Renderer* renderer):m_renderer(renderer){}

            void DestroyRenderer(){
                SDL_DestroyRenderer(m_renderer);
                m_renderer = nullptr;
            }


            static auto GetNumRenderDrivers(){
                auto numRenderDrivers = SDL_GetNumRenderDrivers();
                if(numRenderDrivers >= 1)
                    return numRenderDrivers;
                else
                    throw Error();
            }

            static auto GetRenderDriverInfo(int index){
                SDL_RendererInfo info;
                if( SDL_GetRenderDriverInfo(index, &info) != 0)
                    throw Error();
                else
                    return info;
            }

            auto GetRendererInfo(){
                SDL_RendererInfo info;
                if(SDL_GetRendererInfo(m_renderer, &info) != 0)
                    throw Error();
                else
                    return info;
            }

            auto GetRendererOutputSize(){
                Vector2D<int> wh;
                if(SDL_GetRendererOutputSize(m_renderer, &(wh.w), &(wh.h)) != 0)
                    throw Error();
                else
                    return wh;
            }

            auto CreateTexture(uint32_t format, int access, int w, int h){
                auto* sdlTexture = SDL_CreateTexture(m_renderer, format, access, w, h);
                if( sdlTexture == nullptr)
                    throw Error();
                else
                    return std::make_shared<Texture>(sdlTexture);
            }

            auto RenderTargetSupported(){return SDL_RenderTargetSupported(m_renderer);}


            void RenderClear(){
                if(SDL_RenderClear(m_renderer) != 0)
                    throw Error();
            }

            void RenderDrawPoint(Vector2D<int> p){RenderDrawPoint(p.x, p.y);}
            void RenderDrawPoint(Vector2D<int>& p){RenderDrawPoint(p.x, p.y);}
            void RenderDrawPoint(Point p){RenderDrawPoint(p.x, p.y);}
            void RenderDrawPoint(Point& p){RenderDrawPoint(p.x, p.y);}

            void RenderDrawPoint(int x, int y){
                if(SDL_RenderDrawPoint(m_renderer, x, y) != 0)
                    throw Error();
            }

            void RenderDrawPoints(std::vector<Point>& points){
                if(SDL_RenderDrawPoints(m_renderer, points.data(), points.size()) != 0)
                    throw Error();
            }

            void RenderDrawLine(Vector2D<int> p1, Vector2D<int> p2){RenderDrawLine(p1.x, p1.y, p2.x, p2.y);}
            void RenderDrawLine(Vector2D<int>& p1, Vector2D<int>& p2){RenderDrawLine(p1.x, p1.y, p2.x, p2.y);}
            void RenderDrawLine(Point p1, Point p2){RenderDrawLine(p1.x, p1.y, p2.x, p2.y);}
            void RenderDrawLine(Point& p1, Point& p2){RenderDrawLine(p1.x, p1.y, p2.x, p2.y);}

            void RenderDrawLine(int x1, int y1, int x2, int y2){
                if(SDL_RenderDrawLine(m_renderer, x1, y1, x2, y2) != 0)
                    throw Error();
            }

            void RenderDrawLines(std::vector<Point>& points){
                if(SDL_RenderDrawLines(m_renderer, points.data(), points.size()) != 0)
                    throw Error();
            }

            void RenderDrawRect(Rect& rect){
                if(SDL_RenderDrawRect(m_renderer, &rect) != 0)
                    throw Error();
            }

            void RenderDrawRects(std::vector<Rect>& rects){
                if(SDL_RenderDrawRects(m_renderer, rects.data(), rects.size()) != 0)
                    throw Error();
            }

            void RenderFillRect(Rect& rect){
                if(SDL_RenderFillRect(m_renderer, &rect) != 0)
                    throw Error();
            }

            void RenderFillRects(std::vector<Rect>& rects){
                if(SDL_RenderFillRects(m_renderer, rects.data(), rects.size()) != 0)
                    throw Error();
            }
            void RenderPresent(){SDL_RenderPresent(m_renderer);}
            void SetRenderDrawColor(Color color){SetRenderDrawColor(color.r, color.g, color.b, color.a);}
            void SetRenderDrawColor(Color& color){SetRenderDrawColor(color.r, color.g, color.b, color.a);}
            void SetRenderDrawColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a){
                if(SDL_SetRenderDrawColor(m_renderer, r, g, b, a) != 0)
                    throw Error();
            }


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

int main(int argc, char** argv){
    try{
        SDL::Application app{SDL::Application::INIT::EVERYTHING};
        SDL::Window window("SDL::Test", SDL::Rect{SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 320, 240}, SDL_WINDOW_OPENGL | SDL_WINDOW_BORDERLESS);
        auto renderer = window.CreateRenderer(-1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE | SDL_RENDERER_PRESENTVSYNC);

        auto running = true;
        SDL_Event event;
        uint8_t r = 0, g = 0, b = 0;
        while(running){
            renderer->SetRenderDrawColor(SDL::Color{r++, g, b, 255});
            {
                g += r%255;
                b += b%255;
            }
            renderer->RenderClear();

            while(SDL_PollEvent(&event)){
                switch(event.type){
                    case SDL_QUIT:
                        running = false;
                        break;
                    case SDL_KEYDOWN:
                        switch(event.key.keysym.sym){
                            case SDLK_ESCAPE:
                                running = false;
                                break;
                        }
                        break;
                }
            }

            renderer->RenderPresent();
        }

    }catch(SDL::Error& e){
        std::cerr << "Exception: " << e.what() << std::endl;
    }
    return 0;
}
