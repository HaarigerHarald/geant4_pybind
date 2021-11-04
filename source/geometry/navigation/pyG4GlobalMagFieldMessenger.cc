#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4GlobalMagFieldMessenger.hh>
#include <G4UniformMagField.hh>
#include <G4UIcmdWith3VectorAndUnit.hh>
#include <G4UIcmdWithAnInteger.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4GlobalMagFieldMessenger : public G4GlobalMagFieldMessenger, public py::trampoline_self_life_support {
public:
   using G4GlobalMagFieldMessenger::G4GlobalMagFieldMessenger;

   void SetNewValue(G4UIcommand *arg0, G4String arg1) override
   {
      PYBIND11_OVERRIDE(void, G4GlobalMagFieldMessenger, SetNewValue, arg0, arg1);
   }

   G4String GetCurrentValue(G4UIcommand *command) override
   {
      PYBIND11_OVERRIDE(G4String, G4GlobalMagFieldMessenger, GetCurrentValue, command);
   }
};

void export_G4GlobalMagFieldMessenger(py::module &m)
{
   py::class_<G4GlobalMagFieldMessenger, PyG4GlobalMagFieldMessenger, G4UImessenger>(m, "G4GlobalMagFieldMessenger")

      .def(py::init<const G4ThreeVector &>(), py::arg("value") = G4ThreeVector())
      .def("__copy__", [](const PyG4GlobalMagFieldMessenger &self) { return PyG4GlobalMagFieldMessenger(self); })
      .def("__deepcopy__",
           [](const PyG4GlobalMagFieldMessenger &self, py::dict) { return PyG4GlobalMagFieldMessenger(self); })

      .def("SetNewValue", &G4GlobalMagFieldMessenger::SetNewValue)
      .def("SetFieldValue", &G4GlobalMagFieldMessenger::SetFieldValue, py::arg("value"))
      .def("GetFieldValue", &G4GlobalMagFieldMessenger::GetFieldValue)
      .def("SetVerboseLevel", &G4GlobalMagFieldMessenger::SetVerboseLevel, py::arg("verboseLevel"))
      .def("GetVerboseLevel", &G4GlobalMagFieldMessenger::GetVerboseLevel);
}
