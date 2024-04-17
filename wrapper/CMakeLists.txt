cmake_minimum_required(VERSION 3.12)
project(pybintest_simple)

set(PYTHONPATH=/eos/user/o/oponcet/code/analysis/data/software/venvs/venv_columnar_dev_3cbb5aff/lib/python3.9/site-packages)
set(Python_VIRTUALENV FIRST)
#set(LIBRARY_PATH=$LIBRARY_PATH:/afs/cern.ch/user/o/oponcet/private/analysis/HCPToTauTau/modules/extern/TauAnalysis/ClassicSVfit/lib)
#set(PYTHONPATH=$PYTHONPATH:/afs/cern.ch/user/o/oponcet/private/analysis/HCPToTauTau/modules/extern/TauAnalysis/ClassicSVfit/lib)


include_directories(/afs/cern.ch/user/o/oponcet/private/analysis/HCPToTauTau/modules/extern)

# Find the pybind11 package
add_subdirectory(pybind11)

# Create the module
pybind11_add_module(pybind_wrapper MODULE pybind_wrapper.cpp)


# Find the ROOT package
find_package(ROOT REQUIRED)

# Include the necessary directories
include_directories(${ROOT_INCLUDE_DIRS})

# Find the ClassicSVfit package
#find_package(ClassicSVfit REQUIRED PATHS=/afs/cern.ch/user/o/oponcet/private/analysis/HCPToTauTau/modules/extern/)

# Include the necessary directories
#include_directories(/afs/cern.ch/user/o/oponcet/private/analysis/HCPToTauTau/modules/extern/ClassicSVfit/interface)


target_link_libraries(pybind_wrapper PUBLIC /afs/cern.ch/user/o/oponcet/private/analysis/HCPToTauTau/modules/extern/TauAnalysis/ClassicSVfit/lib/libTauAnalysis_ClassicSVfit.so)



