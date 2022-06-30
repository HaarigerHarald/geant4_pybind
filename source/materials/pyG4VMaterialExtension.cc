#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4VMaterialExtension.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4VMaterialExtension : public G4VMaterialExtension, public py::trampoline_self_life_support {
public:
   using G4VMaterialExtension::G4VMaterialExtension;

   void Print() const override { PYBIND11_OVERRIDE_PURE(void, G4VMaterialExtension, Print, ); }
};

void export_G4VMaterialExtension(py::module &m)
{
   py::class_<G4VMaterialExtension, PyG4VMaterialExtension>(m, "G4VMaterialExtension")

      .def("__copy__", [](const PyG4VMaterialExtension &self) { return new PyG4VMaterialExtension(self); })
      .def("__deepcopy__",
           [](const PyG4VMaterialExtension &self, py::dict) { return new PyG4VMaterialExtension(self); })

      .def(py::init<const G4String &>(), py::arg("name"))
      .def("GetHash", &G4VMaterialExtension::GetHash)
      .def("GetName", &G4VMaterialExtension::GetName)
      .def("Print", &G4VMaterialExtension::Print);
}
