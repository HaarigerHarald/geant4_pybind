#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4VSDFilter.hh>
#include <G4Step.hh>

#include "holder.hh"
#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class TRAMPOLINE_NAME(G4VSDFilter) : public G4VSDFilter {
public:
   TRAMPOLINE_NAME(G4VSDFilter)(G4String name) : G4VSDFilter(name)
   {
      py::handle handle = py::cast(static_cast<const G4VSDFilter *>(this), py::return_value_policy::reference);
      if (handle) handle.inc_ref();
   }

   G4bool Accept(const G4Step *step) const override { PYBIND11_OVERRIDE_PURE(G4bool, G4VSDFilter, Accept, step); }

   TRAMPOLINE_DESTRUCTOR(G4VSDFilter);
};

void export_G4VSDFilter(py::module &m)
{
   py::class_<G4VSDFilter, TRAMPOLINE_NAME(G4VSDFilter), std::unique_ptr<G4VSDFilter, py::nodelete>>(m, "G4VSDFilter")

      .def(py::init<G4String>(), py::arg("name"))
      .def("Accept", &G4VSDFilter::Accept)
      .def("GetName", &G4VSDFilter::GetName);
}
