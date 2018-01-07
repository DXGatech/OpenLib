//EGL configuration establishment for OPENGL ES rendering
//function: takes native window as the parameter and create a render surface

//the mininum and maximum version numbers that a user expects to use
int majorVersionNum;
int minorVersionNum;

EGLNativeWindow native_window;

//the variables used to locate an appropriate surface
int red_size;
int green_size;
int blue_size;
int depth_size;

//egl seeks for appropriate configurations for surfaces according to the following array
const EGLint config_attr[] = {
  EGL_RENDER_TYPE, EGL_OPENGL_ES3_BIT_KHR, //the render surface configuration; we choose opengl es 3
  EGL_RED_SIZE, red_size, //number of red bits in the ideal color buffer
  EGL_GREEN_SIZE, green_size, //number of green bits
  EGL_BLUE_SIZE, blue_size, //number of blue bits
  EGL_DEPTH_SIZE, depth_size, //this name is self-explanatory
  EGL_NONE //fill the last criteria with an empty value
}

//egl configures the rendering context, which stores informations such as primitive values, with the following options
const EGLint context_attr[] = {
  EGL_CONTEXT_CLIENT_VERSION, 3, //opengl es 3
  EGL_NONE //fill the last criteria with an empty value
}

//egl fills the following variables with the information of the preferable configurations provided by the user
EGLConfig config;
EGLint config_number;

//Code piece 1: setting up EGL rendering surface
EGLDisplay display = eglGetDisplay(EGL_DEFAULT_DISPLAY) //each system may have a different index for its default rendering surface, so the constant
if(display == EGL_NO_DISPLAY) return EGL_FALSE;

if(!eglInitialize(display, &minorVersionNum, &majorVersionNum)) return EGL_FALSE;

if(!eglChooseConfig(display, config_attr, &config, 1, &config_number)) return EGL_FALSE;

//create the surface for rendering. The fourth argument specifies EGL_RENDER_BUFFER, with EGL_BACK_BUFFER as its default value
//opengl es 3 does not support single-buffered windows, thus EGL_SINGLE_BUFFER, the other option for EGL_RENDER_BUFFER, is not recommended here
EGLSurface window = eglCreateWindowSurface(display, config, native_window, NULL);
if(window == EGL_NO_SURFACE) return EGL_FALSE;

//EGL_NO_CONTEXT specifies whether the information stored within the context should not be shared with the other contexts
EGLContext rendering_context = eglCreateContext(display, config, EGL_NO_CONTEXT, context_attr);
if(context == EGL_NO_CONTEXT) return EGL_FALSE;
//associate the rendering context with the surface and window
if(!eglMakeCurrent(display, window, window, context)) return EGL_FALSE;

return EGL_TRUE;
