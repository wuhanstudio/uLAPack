    
from building import *
import rtconfig

# get current directory
cwd     = GetCurrentDir()
# The set of source files associated with this SConscript file.

src     = Glob('src/*.c')

# Examples
if GetDepend('ULAPACK_USING_LU'):
    src    += Glob('examples/u_lu.c')

if GetDepend('ULAPACK_USING_SVD'):
    src    += Glob('examples/u_svd.c')

if GetDepend('ULAPACK_USING_PCA'):
    src    += Glob('examples/u_pca.c')

if GetDepend('ULAPACK_USING_POLYFIT'):
    src    += Glob('examples/u_polyfit.c')

path    = [cwd + '/']
path   += [cwd + '/src']

LOCAL_CCFLAGS = ''

group = DefineGroup('ulapack', src, depend = ['PKG_USING_ULAPACK'], CPPPATH = path, LOCAL_CCFLAGS = LOCAL_CCFLAGS)

Return('group')
