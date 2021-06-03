#line 1 "C:/Users/s2019112543/source/repos/CudaRuntime2/CudaRuntime2/kernel.cu"
static const struct __si_class_type_info _ZTISt20bad_array_new_length;
#line 19961 "C:\\Users\\s2019112543\\source\\repos\\CudaRuntime2\\CudaRuntime2\\..\\usr\\include\\GL\\glew.h"
extern __declspec( dllimport ) PFNGLBINDBUFFERPROC __glewBindBuffer;
extern __declspec( dllimport ) PFNGLBUFFERDATAPROC __glewBufferData;

extern __declspec( dllimport ) PFNGLDELETEBUFFERSPROC __glewDeleteBuffers;


extern __declspec( dllimport ) PFNGLGENBUFFERSPROC __glewGenBuffers;
extern struct __C7 *__curr_eh_stack_entry;
extern unsigned short __eh_curr_region;
#line 23 "C:/Users/s2019112543/source/repos/CudaRuntime2/CudaRuntime2/kernel.cu"
extern int Width;
extern int Height;
GLuint gl_pbo = 0;
struct cudaGraphicsResource *cuda_pbo = 0;
struct uchar4 *pDevImage = 0;
#line 86 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.16299.0\\ucrt\\corecrt_stdio_config.h"
 /* COMDAT group: _ZZ28__local_stdio_printf_optionsE15_OptionsStorage */ unsigned __int64 _ZZ28__local_stdio_printf_optionsE15_OptionsStorage;
extern void *__dso_handle;
#line 90 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v11.2\\include\\thrust/system/cuda/detail/error.inl"
 /* COMDAT group: _ZZN6thrust6system13cuda_categoryEvE6result */ struct _ZN6thrust6system8cuda_cub6detail19cuda_error_categoryE _ZZN6thrust6system13cuda_categoryEvE6result = {{0}};
 /* COMDAT group: _ZZN6thrust6system13cuda_categoryEvE6result */ unsigned __int64 _ZGVZN6thrust6system13cuda_categoryEvE6result;
#line 42 "C:/Users/s2019112543/source/repos/CudaRuntime2/CudaRuntime2/kernel.cu"
extern int mouseCount;
extern long timeMax;

extern double downGravity[3];
extern double upGravity[3];

extern double ExtForce[3];
struct _ZSt6vectorI8ParticleSaIS0_EE PSystem = {{{{0}}}};
extern int __catch_clause_number;
static const struct __si_class_type_info _ZTIN6thrust6system6detail9bad_allocE;
static const struct __si_class_type_info _ZTISt12length_error;
#line 208 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v11.2\\include\\thrust\\mr\\memory_resource.h"
 /* COMDAT group: _ZZN6thrust2mr19get_global_resourceINS_6system4cuda6detail20cuda_memory_resourceIXadL_Z10cudaMallocEEXadL_Z8cudaFreeEENS_8cuda_cub7pointerIvEEEEEEPT_vE8resource */ _ZN6thrust22device_memory_resourceE _ZZN6thrust2mr19get_global_resourceINS_6system4cuda6detail20cuda_memory_resourceIXadL_Z10cudaMallocEEXadL_Z8cudaFreeEENS_8cuda_cub7pointerIvEEEEEEPT_vE8resource = {{0}};
 /* COMDAT group: _ZZN6thrust2mr19get_global_resourceINS_6system4cuda6detail20cuda_memory_resourceIXadL_Z10cudaMallocEEXadL_Z8cudaFreeEENS_8cuda_cub7pointerIvEEEEEEPT_vE8resource */ unsigned __int64 _ZGVZN6thrust2mr19get_global_resourceINS_6system4cuda6detail20cuda_memory_resourceIXadL_Z10cudaMallocEEXadL_Z8cudaFreeEENS_8cuda_cub7pointerIvEEEEEEPT_vE8resource;
#line 208 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v11.2\\include\\thrust\\mr\\memory_resource.h"
 /* COMDAT group: _ZZN6thrust2mr19get_global_resourceINS_26device_ptr_memory_resourceINS_6system4cuda6detail20cuda_memory_resourceIXadL_Z10cudaMallocEEXadL_Z8cudaFreeEENS_8cuda_cub7pointerIvEEEEEEEEPT_vE8resource */ struct _ZN6thrust26device_ptr_memory_resourceINS_6system4cuda6detail20cuda_memory_resourceIXadL_Z10cudaMallocEEXadL_Z8cudaFreeEENS_8cuda_cub7pointerIvEEEEEE _ZZN6thrust2mr19get_global_resourceINS_26device_ptr_memory_resourceINS_6system4cuda6detail20cuda_memory_resourceIXadL_Z10cudaMallocEEXadL_Z8cudaFreeEENS_8cuda_cub7pointerIvEEEEEEEEPT_vE8resource = {{0}};
 /* COMDAT group: _ZZN6thrust2mr19get_global_resourceINS_26device_ptr_memory_resourceINS_6system4cuda6detail20cuda_memory_resourceIXadL_Z10cudaMallocEEXadL_Z8cudaFreeEENS_8cuda_cub7pointerIvEEEEEEEEPT_vE8resource */ unsigned __int64 _ZGVZN6thrust2mr19get_global_resourceINS_26device_ptr_memory_resourceINS_6system4cuda6detail20cuda_memory_resourceIXadL_Z10cudaMallocEEXadL_Z8cudaFreeEENS_8cuda_cub7pointerIvEEEEEEEEPT_vE8resource;
static const struct __class_type_info _ZTISt9exception;
extern  /* COMDAT group: _ZTSSt9exception */ const char _ZTSSt9exception[13];
static const struct __si_class_type_info _ZTISt9bad_alloc;
extern  /* COMDAT group: _ZTSSt9bad_alloc */ const char _ZTSSt9bad_alloc[13];
extern  /* COMDAT group: _ZTSSt20bad_array_new_length */ const char _ZTSSt20bad_array_new_length[25];
static const struct __si_class_type_info _ZTISt11logic_error;
extern  /* COMDAT group: _ZTSSt11logic_error */ const char _ZTSSt11logic_error[16];
extern  /* COMDAT group: _ZTSSt12length_error */ const char _ZTSSt12length_error[17];
extern  /* COMDAT group: _ZTSN6thrust6system6detail9bad_allocE */ const char _ZTSN6thrust6system6detail9bad_allocE[34];
#line 115 "C:\\Program Files (x86)\\Microsoft Visual Studio\\2019\\Community\\VC\\Tools\\MSVC\\14.24.28314\\include\\xlocnum"
extern __declspec( dllimport ) struct _ZNSt6locale2idE _ZNSt8numpunctIcE2idE;
#line 115 "C:\\Program Files (x86)\\Microsoft Visual Studio\\2019\\Community\\VC\\Tools\\MSVC\\14.24.28314\\include\\xlocnum"
extern __declspec( dllimport ) struct _ZNSt6locale2idE _ZNSt8numpunctIwE2idE;
static const struct __si_class_type_info _ZTISt20bad_array_new_length = {{{(_ZTVN10__cxxabiv120__si_class_type_infoE + 2),_ZTSSt20bad_array_new_length}},((const struct __class_type_info *)(&_ZTISt9bad_alloc.base))};
#line 23 "C:/Users/s2019112543/source/repos/CudaRuntime2/CudaRuntime2/kernel.cu"
int Width = 800;
int Height = 600;
#line 42 "C:/Users/s2019112543/source/repos/CudaRuntime2/CudaRuntime2/kernel.cu"
int mouseCount = 0;
long timeMax = 0L;

double downGravity[3] = {(0.0),(-9.800000000000000711),(0.0)};
double upGravity[3] = {(0.0),(-1.199999999999999956),(0.0)};

double ExtForce[3] = {(0.0),(0.0),(0.0)};
static const struct __si_class_type_info _ZTIN6thrust6system6detail9bad_allocE = {{{(_ZTVN10__cxxabiv120__si_class_type_infoE + 2),_ZTSN6thrust6system6detail9bad_allocE}},((const struct __class_type_info *)(&_ZTISt9bad_alloc.base))};
static const struct __si_class_type_info _ZTISt12length_error = {{{(_ZTVN10__cxxabiv120__si_class_type_infoE + 2),_ZTSSt12length_error}},((const struct __class_type_info *)(&_ZTISt11logic_error.base))};
static const struct __class_type_info _ZTISt9exception = {{(_ZTVN10__cxxabiv117__class_type_infoE + 2),_ZTSSt9exception}};
 /* COMDAT group: _ZTSSt9exception */ const char _ZTSSt9exception[13] = "St9exception";
static const struct __si_class_type_info _ZTISt9bad_alloc = {{{(_ZTVN10__cxxabiv120__si_class_type_infoE + 2),_ZTSSt9bad_alloc}},(&_ZTISt9exception)};
 /* COMDAT group: _ZTSSt9bad_alloc */ const char _ZTSSt9bad_alloc[13] = "St9bad_alloc";
 /* COMDAT group: _ZTSSt20bad_array_new_length */ const char _ZTSSt20bad_array_new_length[25] = "St20bad_array_new_length";
static const struct __si_class_type_info _ZTISt11logic_error = {{{(_ZTVN10__cxxabiv120__si_class_type_infoE + 2),_ZTSSt11logic_error}},(&_ZTISt9exception)};
 /* COMDAT group: _ZTSSt11logic_error */ const char _ZTSSt11logic_error[16] = "St11logic_error";
 /* COMDAT group: _ZTSSt12length_error */ const char _ZTSSt12length_error[17] = "St12length_error";
 /* COMDAT group: _ZTSN6thrust6system6detail9bad_allocE */ const char _ZTSN6thrust6system6detail9bad_allocE[34] = "N6thrust6system6detail9bad_allocE";
