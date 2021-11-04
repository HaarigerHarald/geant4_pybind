#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4GeometryMessenger.hh>
#include <G4UIcmdWithoutParameter.hh>
#include <G4UIcmdWithABool.hh>
#include <G4UIcmdWithAnInteger.hh>
#include <G4UIcmdWithADoubleAndUnit.hh>
#include <G4TransportationManager.hh>
#include <G4GeomTestVolume.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4GeometryMessenger : public G4GeometryMessenger, public py::trampoline_self_life_support {
public:
   using G4GeometryMessenger::G4GeometryMessenger;

   void SetNewValue(G4UIcommand *command, G4String newValues) override
   {
      PYBIND11_OVERRIDE(void, G4GeometryMessenger, SetNewValue, command, newValues);
   }

   G4String GetCurrentValue(G4UIcommand *command) override
   {
      PYBIND11_OVERRIDE(G4String, G4GeometryMessenger, GetCurrentValue, command);
   }
};

void export_G4GeometryMessenger(py::module &m)
{
   py::class_<G4GeometryMessenger, PyG4GeometryMessenger, G4UImessenger>(m, "G4GeometryMessenger")

      .def(py::init<G4TransportationManager *>(), py::arg("tman"))
      .def("__copy__", [](const PyG4GeometryMessenger &self) { return PyG4GeometryMessenger(self); })
      .def("__deepcopy__", [](const PyG4GeometryMessenger &self, py::dict) { return PyG4GeometryMessenger(self); })
      .def("SetNewValue", &G4GeometryMessenger::SetNewValue, py::arg("command"), py::arg("newValues"))
      .def("GetCurrentValue", &G4GeometryMessenger::GetCurrentValue, py::arg("command"));
}
