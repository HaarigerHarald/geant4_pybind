#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4VUserEventInformation.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4VUserEventInformation : public G4VUserEventInformation, public py::trampoline_self_life_support {
public:
   using G4VUserEventInformation::G4VUserEventInformation;

   void Print() const override { PYBIND11_OVERRIDE_PURE(void, G4VUserEventInformation, Print, ); }
};

void export_G4VUserEventInformation(py::module &m)
{
   py::class_<G4VUserEventInformation, PyG4VUserEventInformation>(m, "G4VUserEventInformation")

      .def(py::init<>())
      .def("__copy__", [](const PyG4VUserEventInformation &self) { return new PyG4VUserEventInformation(self); })
      .def("__deepcopy__",
           [](const PyG4VUserEventInformation &self, py::dict) { return new PyG4VUserEventInformation(self); })

      .def("Print", &G4VUserEventInformation::Print);
}
