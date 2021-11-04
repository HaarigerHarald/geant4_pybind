#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4VUserRegionInformation.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4VUserRegionInformation : public G4VUserRegionInformation, public py::trampoline_self_life_support {
public:
   using G4VUserRegionInformation::G4VUserRegionInformation;

   void Print() const override { PYBIND11_OVERRIDE_PURE(void, G4VUserRegionInformation, Print, ); }
};

void export_G4VUserRegionInformation(py::module &m)
{
   py::class_<G4VUserRegionInformation, PyG4VUserRegionInformation>(m, "G4VUserRegionInformation")

      .def(py::init<>())
      .def("__copy__", [](const PyG4VUserRegionInformation &self) { return PyG4VUserRegionInformation(self); })
      .def("__deepcopy__",
           [](const PyG4VUserRegionInformation &self, py::dict) { return PyG4VUserRegionInformation(self); })

      .def("Print", &G4VUserRegionInformation::Print);
}
