-- -*- lua -*-
local pkgVersion      = "4.2"
local pkgName         = "gcc"
local pkgNameVer      = pathJoin(pkgName,pkgVersion)
local modulepath_root = os.getenv("MODULEPATH_ROOT")
family("compiler")

prepend_path('MODULEPATH',     pathJoin(modulepath_root,"E_Compiler",pkgNameVer))
