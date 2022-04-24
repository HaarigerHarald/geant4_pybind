#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4StackingMessenger.hh>
#include <G4StackManager.hh>
#include <G4UIcmdWithoutParameter.hh>
#include <G4UIcmdWithAnInteger.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4StackingMessenger : public G4StackingMessenger, public py::trampoline_self_life_support {
public:
   using G4StackingMessenger::G4StackingMessenger;

   void SetNewValue(G4UIcommand *command, G4String newValues) override
   {
      PYBIND11_OVERRIDE(void, G4StackingMessenger, SetNewValue, command, newValues);
   }

   G4String GetCurrentValue(G4UIcommand *command) override
   {
      PYBIND11_OVERRIDE(G4String, G4StackingMessenger, GetCurrentValue, command);
   }
};

void export_G4StackingMessenger(py::module &m)
{
   py::class_<G4StackingMessenger, PyG4StackingMessenger, G4UImessenger>(m, "G4StackingMessenger")

      .def("__copy__", [](const PyG4StackingMessenger &self) { return new PyG4StackingMessenger(self); })
      .def("__deepcopy__", [](const PyG4StackingMessenger &self, py::dict) { return new PyG4StackingMessenger(self); })
      .def("__copy__", [](const G4StackingMessenger &self) { return new G4StackingMessenger(self); })
      .def("__deepcopy__", [](const G4StackingMessenger &self, py::dict) { return new G4StackingMessenger(self); })
      .def(py::init<G4StackManager *>(), py::arg("fCont"))
      .def("SetNewValue", &G4StackingMessenger::SetNewValue, py::arg("command"), py::arg("newValues"));
}
