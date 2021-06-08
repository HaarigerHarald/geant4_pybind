#ifdef G4_HAS_RAYTRACERX

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4RayTracerX.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4RayTracerX()
{
   py::class_<G4RayTracerX, G4VGraphicsSystem>(m, "G4RayTracerX", "RayTracerX visualization module").def(py::init<>());
}

#endif // G4_HAS_RAYTRACERX
