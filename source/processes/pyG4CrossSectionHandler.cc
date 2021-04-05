#include <pybind11/pybind11.h>

#include <G4CrossSectionHandler.hh>

#include "OpaqueTypes.hh"
#include "typecast.hh"

namespace py = pybind11;

void export_G4CrossSectionHandler(py::module &m)
{
   py::class_<G4CrossSectionHandler, G4VCrossSectionHandler, std::unique_ptr<G4CrossSectionHandler>>(
      m, "G4CrossSectionHandler", "cross section handler")
      .def(py::init<>());
}
