help([==[

Description
===========
Intel Math Kernel Library is a library of highly optimized,
 extensively threaded math routines for science, engineering, and financial
 applications that require maximum performance. Core math functions include
 BLAS, LAPACK, ScaLAPACK, Sparse Solvers, Fast Fourier Transforms, Vector Math, and more.


More information
================
 - Homepage: http://software.intel.com/en-us/intel-mkl/
]==])

whatis([==[Description: Intel Math Kernel Library is a library of highly optimized,
 extensively threaded math routines for science, engineering, and financial
 applications that require maximum performance. Core math functions include
 BLAS, LAPACK, ScaLAPACK, Sparse Solvers, Fast Fourier Transforms, Vector Math, and more.]==])
whatis([==[Homepage: http://software.intel.com/en-us/intel-mkl/]==])

local root = "/cvmfs/soft.computecanada.ca/easybuild/software/2017/Core/imkl/2018.3.222"

conflict("imkl")

prepend_path("CPATH", pathJoin(root, "mkl/include"))
prepend_path("CPATH", pathJoin(root, "mkl/include/fftw"))
prepend_path("LIBRARY_PATH", pathJoin(root, "lib/intel64"))
prepend_path("LIBRARY_PATH", pathJoin(root, "mkl/lib/intel64"))
prepend_path("PATH", pathJoin(root, "bin"))
prepend_path("PATH", pathJoin(root, "mkl/bin"))
setenv("EBROOTIMKL", root)
setenv("EBVERSIONIMKL", "2018.3.222")
setenv("EBDEVELIMKL", pathJoin(root, "easybuild/Core-imkl-2018.3.222-easybuild-devel"))

setenv("MKL_EXAMPLES", "/cvmfs/soft.computecanada.ca/easybuild/software/2017/Core/imkl/2018.3.222/mkl/examples/")
prepend_path("NLSPATH", pathJoin(root, "idb/intel64/locale/%l_%t/%N"))
setenv("MKLROOT", "/cvmfs/soft.computecanada.ca/easybuild/software/2017/Core/imkl/2018.3.222/mkl")
-- Built with EasyBuild version 3.6.2-r1ed7dac97acd22d6301e534c78048f7fcedaa585
