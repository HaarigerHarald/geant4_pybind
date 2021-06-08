#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4CrossSectionHandler.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4CrossSectionHandler(py::module &m)
{
   py::class_<G4CrossSectionHandler, G4VCrossSectionHandler>(m, "G4CrossSectionHandler", "cross section handler")
      .def(py::init<>());
}
