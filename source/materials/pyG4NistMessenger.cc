#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4NistMessenger.hh>
#include <G4NistManager.hh>
#include <G4UIcmdWithAnInteger.hh>
#include <G4UIcmdWithAString.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4NistMessenger : public G4NistMessenger, public py::trampoline_self_life_support {
public:
   using G4NistMessenger::G4NistMessenger;

   G4String GetCurrentValue(G4UIcommand *command) override
   {
      PYBIND11_OVERRIDE(G4String, G4NistMessenger, GetCurrentValue, command);
   }
};

void export_G4NistMessenger(py::module &m)
{
   py::class_<G4NistMessenger, PyG4NistMessenger, G4UImessenger>(m, "G4NistMessenger")

      .def("__copy__", [](const PyG4NistMessenger &self) { return new PyG4NistMessenger(self); })
      .def("__deepcopy__", [](const PyG4NistMessenger &self, py::dict) { return new PyG4NistMessenger(self); })
      .def("__copy__", [](const G4NistMessenger &self) { return new G4NistMessenger(self); })
      .def("__deepcopy__", [](const G4NistMessenger &self, py::dict) { return new G4NistMessenger(self); })
      .def(py::init<G4NistManager *>())
      .def("SetNewValue", &G4NistMessenger::SetNewValue);
}
