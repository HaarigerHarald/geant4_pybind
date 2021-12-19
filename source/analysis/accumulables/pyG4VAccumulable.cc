#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4VAccumulable.hh>
#include <G4AccumulableManager.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4VAccumulable : public G4VAccumulable, public py::trampoline_self_life_support {
public:
   using G4VAccumulable::G4VAccumulable;

   void Merge(const G4VAccumulable &other) override { PYBIND11_OVERRIDE_PURE(void, G4VAccumulable, Merge, other); }

   void Reset() override { PYBIND11_OVERRIDE_PURE(void, G4VAccumulable, Reset, ); }
};

void export_G4VAccumulable(py::module &m)
{
   py::class_<G4VAccumulable, PyG4VAccumulable>(m, "G4VAccumulable")

      .def(py::init<const G4String &>(), py::arg("name") = "")
      .def("__copy__", [](const PyG4VAccumulable &self) { return new PyG4VAccumulable(self); })
      .def("__deepcopy__", [](const PyG4VAccumulable &self, py::dict) { return new PyG4VAccumulable(self); })
      .def("GetName", &G4VAccumulable::GetName)
      .def("Merge", &G4VAccumulable::Merge, py::arg("other"))
      .def("Reset", &G4VAccumulable::Reset);
}
