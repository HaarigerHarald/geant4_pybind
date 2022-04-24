#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4ParticleGunMessenger.hh>
#include <G4ParticleGun.hh>
#include <G4ParticleTable.hh>
#include <G4UIcmdWithoutParameter.hh>
#include <G4UIcmdWithAString.hh>
#include <G4UIcmdWithADoubleAndUnit.hh>
#include <G4UIcmdWith3Vector.hh>
#include <G4UIcmdWith3VectorAndUnit.hh>
#include <G4UIcmdWithAnInteger.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4ParticleGunMessenger : public G4ParticleGunMessenger, public py::trampoline_self_life_support {
public:
   using G4ParticleGunMessenger::G4ParticleGunMessenger;

   G4String GetCurrentValue(G4UIcommand *command) override
   {
      PYBIND11_OVERRIDE(G4String, G4ParticleGunMessenger, GetCurrentValue, command);
   }

   void SetNewValue(G4UIcommand *command, G4String newValues) override
   {
      PYBIND11_OVERRIDE(void, G4ParticleGunMessenger, SetNewValue, command, newValues);
   }
};

void export_G4ParticleGunMessenger(py::module &m)
{
   py::class_<G4ParticleGunMessenger, PyG4ParticleGunMessenger, G4UImessenger>(m, "G4ParticleGunMessenger")

      .def("__copy__", [](const PyG4ParticleGunMessenger &self) { return new PyG4ParticleGunMessenger(self); })
      .def("__deepcopy__",
           [](const PyG4ParticleGunMessenger &self, py::dict) { return new PyG4ParticleGunMessenger(self); })

      .def("__copy__", [](const G4ParticleGunMessenger &self) { return new G4ParticleGunMessenger(self); })
      .def("__deepcopy__",
           [](const G4ParticleGunMessenger &self, py::dict) { return new G4ParticleGunMessenger(self); })

      .def(py::init<G4ParticleGun *>(), py::arg("fPtclGun"))
      .def("GetCurrentValue", &G4ParticleGunMessenger::GetCurrentValue, py::arg("command"))
      .def("SetNewValue", &G4ParticleGunMessenger::SetNewValue, py::arg("command"), py::arg("newValues"));
}
