#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4RayTracer.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4RayTracer(py::module &m)
{
   py::class_<G4RayTracer, G4VGraphicsSystem>(m, "G4RayTracer", "RayTracer visualization module").def(py::init<>());
}
