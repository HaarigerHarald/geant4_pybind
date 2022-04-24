#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4VSDFilter.hh>
#include <G4Step.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4VSDFilter : public G4VSDFilter, public py::trampoline_self_life_support {
public:
   using G4VSDFilter::G4VSDFilter;

   G4bool Accept(const G4Step *step) const override { PYBIND11_OVERRIDE_PURE(G4bool, G4VSDFilter, Accept, step); }
};

void export_G4VSDFilter(py::module &m)
{
   // TODO
   py::class_<G4VSDFilter, PyG4VSDFilter, py::nodelete>(m, "G4VSDFilter")

      .def(py::init<G4String>(), py::arg("name"))
      .def("Accept", &G4VSDFilter::Accept)
      .def("GetName", &G4VSDFilter::GetName);
}
