#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4EvManMessenger.hh>
#include <G4EventManager.hh>
#include <G4UIcmdWithoutParameter.hh>
#include <G4UIcmdWithAnInteger.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4EvManMessenger : public G4EvManMessenger, public py::trampoline_self_life_support {
public:
   using G4EvManMessenger::G4EvManMessenger;

   G4String GetCurrentValue(G4UIcommand *command) override
   {
      PYBIND11_OVERRIDE(G4String, G4EvManMessenger, GetCurrentValue, command);
   }

   void SetNewValue(G4UIcommand *command, G4String newValues) override
   {
      PYBIND11_OVERRIDE(void, G4EvManMessenger, SetNewValue, command, newValues);
   }
};

void export_G4EvManMessenger(py::module &m)
{
   py::class_<G4EvManMessenger, PyG4EvManMessenger, G4UImessenger>(m, "G4EvManMessenger")

      .def("__copy__", [](const PyG4EvManMessenger &self) { return new PyG4EvManMessenger(self); })
      .def("__deepcopy__", [](const PyG4EvManMessenger &self, py::dict) { return new PyG4EvManMessenger(self); })
      .def("__copy__", [](const G4EvManMessenger &self) { return new G4EvManMessenger(self); })
      .def("__deepcopy__", [](const G4EvManMessenger &self, py::dict) { return new G4EvManMessenger(self); })
      .def(py::init<G4EventManager *>(), py::arg("fEvMan"))
      .def("GetCurrentValue", &G4EvManMessenger::GetCurrentValue, py::arg("command"))
      .def("SetNewValue", &G4EvManMessenger::SetNewValue, py::arg("command"), py::arg("newValues"));
}
