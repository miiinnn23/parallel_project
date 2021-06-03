#define __NV_CUBIN_HANDLE_STORAGE__ static
#if !defined(__CUDA_INCLUDE_COMPILER_INTERNAL_HEADERS__)
#define __CUDA_INCLUDE_COMPILER_INTERNAL_HEADERS__
#endif
#include "crt/host_runtime.h"
#include "kernel.fatbin.c"
typedef __int64 _ZN6thrust15iterator_traitsIPK8ParticleE15difference_typeE;
typedef __int64 _ZN6thrust6detail20iterator_traits_implINS0_15normal_iteratorINS_10device_ptrIK8ParticleEEEEvE15difference_typeE;
typedef thrust::cuda_cub::__parallel_for::ParallelForAgent< ::thrust::cuda_cub::__transform::unary_transform_f< ::thrust::detail::normal_iterator< ::thrust::device_ptr<const     ::Particle> > ,  ::thrust::device_ptr<    ::Particle> ,  ::thrust::cuda_cub::__transform::no_stencil_tag,  ::thrust::identity<    ::Particle> ,  ::thrust::cuda_cub::__transform::always_true_predicate> , long long>  _ZN6thrust8cuda_cub14__parallel_for16ParallelForAgentINS0_11__transform17unary_transform_fINS_6detail15normal_iteratorINS_10device_ptrIK8ParticleEEEENS7_IS8_EENS3_14no_stencil_tagENS_8identityIS8_EENS3_21always_true_predicateEEExEE;
typedef thrust::cuda_cub::__parallel_for::ParallelForAgent< ::thrust::cuda_cub::__transform::unary_transform_f<const     ::Particle *,  ::thrust::device_ptr<    ::Particle> ,  ::thrust::cuda_cub::__transform::no_stencil_tag,  ::thrust::identity<    ::Particle> ,  ::thrust::cuda_cub::__transform::always_true_predicate> , long long>  _ZN6thrust8cuda_cub14__parallel_for16ParallelForAgentINS0_11__transform17unary_transform_fIPK8ParticleNS_10device_ptrIS5_EENS3_14no_stencil_tagENS_8identityIS5_EENS3_21always_true_predicateEEExEE;
typedef thrust::cuda_cub::__transform::unary_transform_f< ::thrust::detail::normal_iterator< ::thrust::device_ptr<const     ::Particle> > ,  ::thrust::device_ptr<    ::Particle> ,  ::thrust::cuda_cub::__transform::no_stencil_tag,  ::thrust::identity<    ::Particle> ,  ::thrust::cuda_cub::__transform::always_true_predicate>  _ZN6thrust8cuda_cub11__transform17unary_transform_fINS_6detail15normal_iteratorINS_10device_ptrIK8ParticleEEEENS5_IS6_EENS1_14no_stencil_tagENS_8identityIS6_EENS1_21always_true_predicateEEE;
typedef thrust::cuda_cub::__transform::unary_transform_f<const     ::Particle *,  ::thrust::device_ptr<    ::Particle> ,  ::thrust::cuda_cub::__transform::no_stencil_tag,  ::thrust::identity<    ::Particle> ,  ::thrust::cuda_cub::__transform::always_true_predicate>  _ZN6thrust8cuda_cub11__transform17unary_transform_fIPK8ParticleNS_10device_ptrIS3_EENS1_14no_stencil_tagENS_8identityIS3_EENS1_21always_true_predicateEEE;
typedef thrust::device_vector<    ::Particle,  ::thrust::device_allocator<    ::Particle> >  _ZN6thrust13device_vectorI8ParticleNS_16device_allocatorIS1_EEEE;
extern void __device_stub__Z8myKernelP8ParticlediN6thrust13device_vectorIS_NS1_16device_allocatorIS_EEEE(struct Particle *, double, int,  _ZN6thrust13device_vectorI8ParticleNS_16device_allocatorIS1_EEEE&);
extern void __device_stub__Z20beforePushBackKernelP8Particled(struct Particle *, double);
static void __device_stub__ZN6thrust8cuda_cub4core13_kernel_agentINS0_14__parallel_for16ParallelForAgentINS0_11__transform17unary_transform_fINS_6detail15normal_iteratorINS_10device_ptrIK8ParticleEEEENS9_ISA_EENS5_14no_stencil_tagENS_8identityISA_EENS5_21always_true_predicateEEExEESJ_xEEvT0_T1_( _ZN6thrust8cuda_cub11__transform17unary_transform_fINS_6detail15normal_iteratorINS_10device_ptrIK8ParticleEEEENS5_IS6_EENS1_14no_stencil_tagENS_8identityIS6_EENS1_21always_true_predicateEEE&, _ZN6thrust6detail20iterator_traits_implINS0_15normal_iteratorINS_10device_ptrIK8ParticleEEEEvE15difference_typeE);
static void __device_stub__ZN6thrust8cuda_cub4core13_kernel_agentINS0_14__parallel_for16ParallelForAgentINS0_11__transform17unary_transform_fIPK8ParticleNS_10device_ptrIS7_EENS5_14no_stencil_tagENS_8identityIS7_EENS5_21always_true_predicateEEExEESG_xEEvT0_T1_( _ZN6thrust8cuda_cub11__transform17unary_transform_fIPK8ParticleNS_10device_ptrIS3_EENS1_14no_stencil_tagENS_8identityIS3_EENS1_21always_true_predicateEEE&, _ZN6thrust15iterator_traitsIPK8ParticleE15difference_typeE);
static void __device_stub__ZN3cub11EmptyKernelIvEEvv(void);
static void __nv_cudaEntityRegisterCallback(void **);
static void __sti____cudaRegisterAll(void);
#pragma section(".CRT$XCU",read)
__declspec(allocate(".CRT$XCU"))static void (*__dummy_static_init__sti____cudaRegisterAll[])(void) = {__sti____cudaRegisterAll};
void __device_stub__Z8myKernelP8ParticlediN6thrust13device_vectorIS_NS1_16device_allocatorIS_EEEE(
struct Particle *__par0, 
double __par1, 
int __par2, 
 _ZN6thrust13device_vectorI8ParticleNS_16device_allocatorIS1_EEEE&__par3)
{
__cudaLaunchPrologue(4);
__cudaSetupArgSimple(__par0, 0Ui64);
__cudaSetupArgSimple(__par1, 8Ui64);
__cudaSetupArgSimple(__par2, 16Ui64);
__cudaSetupArg(__par3, 24Ui64);
__cudaLaunch(((char *)((void ( *)(struct Particle *, double, int,  _ZN6thrust13device_vectorI8ParticleNS_16device_allocatorIS1_EEEE))myKernel)));
}
void myKernel( struct Particle *__cuda_0,double __cuda_1,int __cuda_2, _ZN6thrust13device_vectorI8ParticleNS_16device_allocatorIS1_EEEE __cuda_3)
{__device_stub__Z8myKernelP8ParticlediN6thrust13device_vectorIS_NS1_16device_allocatorIS_EEEE( __cuda_0,__cuda_1,__cuda_2,__cuda_3);
}
#line 1 "x64/Debug/kernel.cudafe1.stub.c"
void __device_stub__Z20beforePushBackKernelP8Particled(
struct Particle *__par0, 
double __par1)
{
__cudaLaunchPrologue(2);
__cudaSetupArgSimple(__par0, 0Ui64);
__cudaSetupArgSimple(__par1, 8Ui64);
__cudaLaunch(((char *)((void ( *)(struct Particle *, double))beforePushBackKernel)));
}
void beforePushBackKernel( struct Particle *__cuda_0,double __cuda_1)
{__device_stub__Z20beforePushBackKernelP8Particled( __cuda_0,__cuda_1);
}
#line 1 "x64/Debug/kernel.cudafe1.stub.c"
static void __device_stub__ZN6thrust8cuda_cub4core13_kernel_agentINS0_14__parallel_for16ParallelForAgentINS0_11__transform17unary_transform_fINS_6detail15normal_iteratorINS_10device_ptrIK8ParticleEEEENS9_ISA_EENS5_14no_stencil_tagENS_8identityISA_EENS5_21always_true_predicateEEExEESJ_xEEvT0_T1_(
 _ZN6thrust8cuda_cub11__transform17unary_transform_fINS_6detail15normal_iteratorINS_10device_ptrIK8ParticleEEEENS5_IS6_EENS1_14no_stencil_tagENS_8identityIS6_EENS1_21always_true_predicateEEE&__par0, 
_ZN6thrust6detail20iterator_traits_implINS0_15normal_iteratorINS_10device_ptrIK8ParticleEEEEvE15difference_typeE __par1)
{
__cudaLaunchPrologue(2);
__cudaSetupArg(__par0, 0Ui64);
__cudaSetupArgSimple(__par1, 24Ui64);
__cudaLaunch(((char *)((void ( *)( _ZN6thrust8cuda_cub11__transform17unary_transform_fINS_6detail15normal_iteratorINS_10device_ptrIK8ParticleEEEENS5_IS6_EENS1_14no_stencil_tagENS_8identityIS6_EENS1_21always_true_predicateEEE, _ZN6thrust6detail20iterator_traits_implINS0_15normal_iteratorINS_10device_ptrIK8ParticleEEEEvE15difference_typeE))thrust::cuda_cub::core::_kernel_agent< ::thrust::cuda_cub::__parallel_for::ParallelForAgent< ::thrust::cuda_cub::__transform::unary_transform_f< ::thrust::detail::normal_iterator< ::thrust::device_ptr<const     ::Particle> > ,  ::thrust::device_ptr<    ::Particle> ,  ::thrust::cuda_cub::__transform::no_stencil_tag,  ::thrust::identity<    ::Particle> ,  ::thrust::cuda_cub::__transform::always_true_predicate> , long long> ,  ::thrust::cuda_cub::__transform::unary_transform_f< ::thrust::detail::normal_iterator< ::thrust::device_ptr<const     ::Particle> > ,  ::thrust::device_ptr<    ::Particle> ,  ::thrust::cuda_cub::__transform::no_stencil_tag,  ::thrust::identity<    ::Particle> ,  ::thrust::cuda_cub::__transform::always_true_predicate> , long long> )));
}namespace thrust{
namespace cuda_cub{
namespace core{

template<> __specialization_static void __wrapper__device_stub__kernel_agent< ::thrust::cuda_cub::__parallel_for::ParallelForAgent< ::thrust::cuda_cub::__transform::unary_transform_f< ::thrust::detail::normal_iterator< ::thrust::device_ptr<const     ::Particle> > ,  ::thrust::device_ptr<    ::Particle> ,  ::thrust::cuda_cub::__transform::no_stencil_tag,  ::thrust::identity<    ::Particle> ,  ::thrust::cuda_cub::__transform::always_true_predicate> , long long> , ::thrust::cuda_cub::__transform::unary_transform_f< ::thrust::detail::normal_iterator< ::thrust::device_ptr<const     ::Particle> > ,  ::thrust::device_ptr<    ::Particle> ,  ::thrust::cuda_cub::__transform::no_stencil_tag,  ::thrust::identity<    ::Particle> ,  ::thrust::cuda_cub::__transform::always_true_predicate> ,__int64>(  _ZN6thrust8cuda_cub11__transform17unary_transform_fINS_6detail15normal_iteratorINS_10device_ptrIK8ParticleEEEENS5_IS6_EENS1_14no_stencil_tagENS_8identityIS6_EENS1_21always_true_predicateEEE &__cuda_0,_ZN6thrust6detail20iterator_traits_implINS0_15normal_iteratorINS_10device_ptrIK8ParticleEEEEvE15difference_typeE &__cuda_1){__device_stub__ZN6thrust8cuda_cub4core13_kernel_agentINS0_14__parallel_for16ParallelForAgentINS0_11__transform17unary_transform_fINS_6detail15normal_iteratorINS_10device_ptrIK8ParticleEEEENS9_ISA_EENS5_14no_stencil_tagENS_8identityISA_EENS5_21always_true_predicateEEExEESJ_xEEvT0_T1_( ( _ZN6thrust8cuda_cub11__transform17unary_transform_fINS_6detail15normal_iteratorINS_10device_ptrIK8ParticleEEEENS5_IS6_EENS1_14no_stencil_tagENS_8identityIS6_EENS1_21always_true_predicateEEE &)__cuda_0,(_ZN6thrust6detail20iterator_traits_implINS0_15normal_iteratorINS_10device_ptrIK8ParticleEEEEvE15difference_typeE &)__cuda_1);}}}}
static void __device_stub__ZN6thrust8cuda_cub4core13_kernel_agentINS0_14__parallel_for16ParallelForAgentINS0_11__transform17unary_transform_fIPK8ParticleNS_10device_ptrIS7_EENS5_14no_stencil_tagENS_8identityIS7_EENS5_21always_true_predicateEEExEESG_xEEvT0_T1_(
 _ZN6thrust8cuda_cub11__transform17unary_transform_fIPK8ParticleNS_10device_ptrIS3_EENS1_14no_stencil_tagENS_8identityIS3_EENS1_21always_true_predicateEEE&__par0, 
_ZN6thrust15iterator_traitsIPK8ParticleE15difference_typeE __par1)
{
__cudaLaunchPrologue(2);
__cudaSetupArg(__par0, 0Ui64);
__cudaSetupArgSimple(__par1, 24Ui64);
__cudaLaunch(((char *)((void ( *)( _ZN6thrust8cuda_cub11__transform17unary_transform_fIPK8ParticleNS_10device_ptrIS3_EENS1_14no_stencil_tagENS_8identityIS3_EENS1_21always_true_predicateEEE, _ZN6thrust15iterator_traitsIPK8ParticleE15difference_typeE))thrust::cuda_cub::core::_kernel_agent< ::thrust::cuda_cub::__parallel_for::ParallelForAgent< ::thrust::cuda_cub::__transform::unary_transform_f<const     ::Particle *,  ::thrust::device_ptr<    ::Particle> ,  ::thrust::cuda_cub::__transform::no_stencil_tag,  ::thrust::identity<    ::Particle> ,  ::thrust::cuda_cub::__transform::always_true_predicate> , long long> ,  ::thrust::cuda_cub::__transform::unary_transform_f<const     ::Particle *,  ::thrust::device_ptr<    ::Particle> ,  ::thrust::cuda_cub::__transform::no_stencil_tag,  ::thrust::identity<    ::Particle> ,  ::thrust::cuda_cub::__transform::always_true_predicate> , long long> )));
}namespace thrust{
namespace cuda_cub{
namespace core{

template<> __specialization_static void __wrapper__device_stub__kernel_agent< ::thrust::cuda_cub::__parallel_for::ParallelForAgent< ::thrust::cuda_cub::__transform::unary_transform_f<const     ::Particle *,  ::thrust::device_ptr<    ::Particle> ,  ::thrust::cuda_cub::__transform::no_stencil_tag,  ::thrust::identity<    ::Particle> ,  ::thrust::cuda_cub::__transform::always_true_predicate> , long long> , ::thrust::cuda_cub::__transform::unary_transform_f<const     ::Particle *,  ::thrust::device_ptr<    ::Particle> ,  ::thrust::cuda_cub::__transform::no_stencil_tag,  ::thrust::identity<    ::Particle> ,  ::thrust::cuda_cub::__transform::always_true_predicate> ,__int64>(  _ZN6thrust8cuda_cub11__transform17unary_transform_fIPK8ParticleNS_10device_ptrIS3_EENS1_14no_stencil_tagENS_8identityIS3_EENS1_21always_true_predicateEEE &__cuda_0,_ZN6thrust15iterator_traitsIPK8ParticleE15difference_typeE &__cuda_1){__device_stub__ZN6thrust8cuda_cub4core13_kernel_agentINS0_14__parallel_for16ParallelForAgentINS0_11__transform17unary_transform_fIPK8ParticleNS_10device_ptrIS7_EENS5_14no_stencil_tagENS_8identityIS7_EENS5_21always_true_predicateEEExEESG_xEEvT0_T1_( ( _ZN6thrust8cuda_cub11__transform17unary_transform_fIPK8ParticleNS_10device_ptrIS3_EENS1_14no_stencil_tagENS_8identityIS3_EENS1_21always_true_predicateEEE &)__cuda_0,(_ZN6thrust15iterator_traitsIPK8ParticleE15difference_typeE &)__cuda_1);}}}}
static void __device_stub__ZN3cub11EmptyKernelIvEEvv(void)
{
__cudaLaunchPrologue(1);
__cudaLaunch(((char *)((void ( *)(void))cub::EmptyKernel<void> )));
}namespace cub{

template<> __specialization_static void __wrapper__device_stub_EmptyKernel<void>(void){__device_stub__ZN3cub11EmptyKernelIvEEvv();}}
static void __nv_cudaEntityRegisterCallback(
void **__T268)
{
__nv_dummy_param_ref(__T268);
__nv_save_fatbinhandle_for_managed_rt(__T268);
__cudaRegisterEntry(__T268, ((void ( *)(void))cub::EmptyKernel<void> ), _ZN3cub11EmptyKernelIvEEvv, (-1));
__cudaRegisterEntry(__T268, ((void ( *)( _ZN6thrust8cuda_cub11__transform17unary_transform_fIPK8ParticleNS_10device_ptrIS3_EENS1_14no_stencil_tagENS_8identityIS3_EENS1_21always_true_predicateEEE, _ZN6thrust15iterator_traitsIPK8ParticleE15difference_typeE))thrust::cuda_cub::core::_kernel_agent< ::thrust::cuda_cub::__parallel_for::ParallelForAgent< ::thrust::cuda_cub::__transform::unary_transform_f<const     ::Particle *,  ::thrust::device_ptr<    ::Particle> ,  ::thrust::cuda_cub::__transform::no_stencil_tag,  ::thrust::identity<    ::Particle> ,  ::thrust::cuda_cub::__transform::always_true_predicate> , long long> ,  ::thrust::cuda_cub::__transform::unary_transform_f<const     ::Particle *,  ::thrust::device_ptr<    ::Particle> ,  ::thrust::cuda_cub::__transform::no_stencil_tag,  ::thrust::identity<    ::Particle> ,  ::thrust::cuda_cub::__transform::always_true_predicate> , long long> ), _ZN6thrust8cuda_cub4core13_kernel_agentINS0_14__parallel_for16ParallelForAgentINS0_11__transform17unary_transform_fIPK8ParticleNS_10device_ptrIS7_EENS5_14no_stencil_tagENS_8identityIS7_EENS5_21always_true_predicateEEExEESG_xEEvT0_T1_, ( ::thrust::cuda_cub::__parallel_for::PtxPolicy<(int)256, (int)2> ::BLOCK_THREADS));
__cudaRegisterEntry(__T268, ((void ( *)( _ZN6thrust8cuda_cub11__transform17unary_transform_fINS_6detail15normal_iteratorINS_10device_ptrIK8ParticleEEEENS5_IS6_EENS1_14no_stencil_tagENS_8identityIS6_EENS1_21always_true_predicateEEE, _ZN6thrust6detail20iterator_traits_implINS0_15normal_iteratorINS_10device_ptrIK8ParticleEEEEvE15difference_typeE))thrust::cuda_cub::core::_kernel_agent< ::thrust::cuda_cub::__parallel_for::ParallelForAgent< ::thrust::cuda_cub::__transform::unary_transform_f< ::thrust::detail::normal_iterator< ::thrust::device_ptr<const     ::Particle> > ,  ::thrust::device_ptr<    ::Particle> ,  ::thrust::cuda_cub::__transform::no_stencil_tag,  ::thrust::identity<    ::Particle> ,  ::thrust::cuda_cub::__transform::always_true_predicate> , long long> ,  ::thrust::cuda_cub::__transform::unary_transform_f< ::thrust::detail::normal_iterator< ::thrust::device_ptr<const     ::Particle> > ,  ::thrust::device_ptr<    ::Particle> ,  ::thrust::cuda_cub::__transform::no_stencil_tag,  ::thrust::identity<    ::Particle> ,  ::thrust::cuda_cub::__transform::always_true_predicate> , long long> ), _ZN6thrust8cuda_cub4core13_kernel_agentINS0_14__parallel_for16ParallelForAgentINS0_11__transform17unary_transform_fINS_6detail15normal_iteratorINS_10device_ptrIK8ParticleEEEENS9_ISA_EENS5_14no_stencil_tagENS_8identityISA_EENS5_21always_true_predicateEEExEESJ_xEEvT0_T1_, ( ::thrust::cuda_cub::__parallel_for::PtxPolicy<(int)256, (int)2> ::BLOCK_THREADS));
__cudaRegisterEntry(__T268, ((void ( *)(struct Particle *, double))beforePushBackKernel), _Z20beforePushBackKernelP8Particled, (-1));
__cudaRegisterEntry(__T268, ((void ( *)(struct Particle *, double, int,  _ZN6thrust13device_vectorI8ParticleNS_16device_allocatorIS1_EEEE))myKernel), _Z8myKernelP8ParticlediN6thrust13device_vectorIS_NS1_16device_allocatorIS_EEEE, (-1));
__cudaRegisterVariable(__T268, __shadow_var(_ZN33_INTERNAL_14_kernel_cpp1_ii_Width6thrust6system6detail10sequential3seqE,::thrust::system::detail::sequential::seq), 0, 1Ui64, 0, 0);
__cudaRegisterVariable(__T268, __shadow_var(_ZN33_INTERNAL_14_kernel_cpp1_ii_Width6thrust6system3cpp3parE,::thrust::system::cpp::par), 0, 1Ui64, 0, 0);
__cudaRegisterVariable(__T268, __shadow_var(_ZN33_INTERNAL_14_kernel_cpp1_ii_Width6thrust8cuda_cub3parE,::thrust::cuda_cub::par), 0, 1Ui64, 0, 0);
__cudaRegisterVariable(__T268, __shadow_var(_ZN33_INTERNAL_14_kernel_cpp1_ii_Width6thrust12placeholders2_1E,::thrust::placeholders::_1), 0, 1Ui64, 0, 0);
__cudaRegisterVariable(__T268, __shadow_var(_ZN33_INTERNAL_14_kernel_cpp1_ii_Width6thrust12placeholders2_2E,::thrust::placeholders::_2), 0, 1Ui64, 0, 0);
__cudaRegisterVariable(__T268, __shadow_var(_ZN33_INTERNAL_14_kernel_cpp1_ii_Width6thrust12placeholders2_3E,::thrust::placeholders::_3), 0, 1Ui64, 0, 0);
__cudaRegisterVariable(__T268, __shadow_var(_ZN33_INTERNAL_14_kernel_cpp1_ii_Width6thrust12placeholders2_4E,::thrust::placeholders::_4), 0, 1Ui64, 0, 0);
__cudaRegisterVariable(__T268, __shadow_var(_ZN33_INTERNAL_14_kernel_cpp1_ii_Width6thrust12placeholders2_5E,::thrust::placeholders::_5), 0, 1Ui64, 0, 0);
__cudaRegisterVariable(__T268, __shadow_var(_ZN33_INTERNAL_14_kernel_cpp1_ii_Width6thrust12placeholders2_6E,::thrust::placeholders::_6), 0, 1Ui64, 0, 0);
__cudaRegisterVariable(__T268, __shadow_var(_ZN33_INTERNAL_14_kernel_cpp1_ii_Width6thrust12placeholders2_7E,::thrust::placeholders::_7), 0, 1Ui64, 0, 0);
__cudaRegisterVariable(__T268, __shadow_var(_ZN33_INTERNAL_14_kernel_cpp1_ii_Width6thrust12placeholders2_8E,::thrust::placeholders::_8), 0, 1Ui64, 0, 0);
__cudaRegisterVariable(__T268, __shadow_var(_ZN33_INTERNAL_14_kernel_cpp1_ii_Width6thrust12placeholders2_9E,::thrust::placeholders::_9), 0, 1Ui64, 0, 0);
__cudaRegisterVariable(__T268, __shadow_var(_ZN33_INTERNAL_14_kernel_cpp1_ii_Width6thrust12placeholders3_10E,::thrust::placeholders::_10), 0, 1Ui64, 0, 0);
__cudaRegisterVariable(__T268, __shadow_var(_ZN33_INTERNAL_14_kernel_cpp1_ii_Width6thrust3seqE,::thrust::seq), 0, 1Ui64, 0, 0);
__cudaRegisterVariable(__T268, __shadow_var(_ZN33_INTERNAL_14_kernel_cpp1_ii_Width6thrust6deviceE,::thrust::device), 0, 1Ui64, 0, 0);
}
static void __sti____cudaRegisterAll(void)
{
__cudaRegisterBinary(__nv_cudaEntityRegisterCallback);
}
