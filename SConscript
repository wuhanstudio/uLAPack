    
from building import *
import rtconfig

# get current directory
cwd     = GetCurrentDir()
# The set of source files associated with this SConscript file.

src     = Glob('src/*.c')

# Examples
if GetDepend('ULAPACK_USE_STATIC_ALLOC'):

    if GetDepend('ULAPACK_USING_LU'):
        src    += Glob('examples/u_lu_static.c')

    if GetDepend('ULAPACK_USING_SVD'):
        src    += Glob('examples/u_svd_static.c')

    if GetDepend('ULAPACK_USING_PCA'):
        src    += Glob('examples/u_pca_static.c')

    if GetDepend('ULAPACK_USING_POLYFIT'):
        src    += Glob('examples/u_polyfit_static.c')

elif GetDepend('ULAPACK_USE_DYNAMIC_ALLOC'):

    if GetDepend('ULAPACK_USING_LU'):
        src    += Glob('examples/u_lu_dynamic.c')

    if GetDepend('ULAPACK_USING_SVD'):
        src    += Glob('examples/u_svd_dynamic.c')

    if GetDepend('ULAPACK_USING_PCA'):
        src    += Glob('examples/u_pca_dynamic.c')

    if GetDepend('ULAPACK_USING_POLYFIT'):
        src    += Glob('examples/u_polyfit_dynamic.c')

    pass
path    = [cwd + '/']
path   += [cwd + '/src']

LOCAL_CCFLAGS = ''

group = DefineGroup('ulapack', src, depend = ['PKG_USING_ULAPACK'], CPPPATH = path, LOCAL_CCFLAGS = LOCAL_CCFLAGS)

Return('group')
