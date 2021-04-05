#include <pybind11/pybind11.h>

#include <G4RayTracer.hh>

#include "holder.hh"
#include "typecast.hh"

namespace py = pybind11;

void export_G4RayTracer(py::module &m)
{
   py::class_<G4RayTracer, G4VGraphicsSystem, owntrans_ptr<G4RayTracer>>(m, "G4RayTracer",
                                                                         "RayTracer visualization module")
      .def(py::init<>());
}
