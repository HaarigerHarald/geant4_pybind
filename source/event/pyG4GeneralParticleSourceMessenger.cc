#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4GeneralParticleSourceMessenger.hh>
#include <G4ParticleTable.hh>
#include <G4UIcmdWithoutParameter.hh>
#include <G4UIcmdWithAString.hh>
#include <G4UIcmdWithADoubleAndUnit.hh>
#include <G4UIcmdWith3Vector.hh>
#include <G4UIcmdWith3VectorAndUnit.hh>
#include <G4UIcmdWithAnInteger.hh>
#include <G4UIcmdWithADouble.hh>
#include <G4UIcmdWithABool.hh>
#include <G4SingleParticleSource.hh>
#include <G4GeneralParticleSource.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4GeneralParticleSourceMessenger(py::module &m)
{
   py::class_<G4GeneralParticleSourceMessenger, G4UImessenger, py::nodelete>(m, "G4GeneralParticleSourceMessenger")

      .def(
         "__copy__",
         [](const G4GeneralParticleSourceMessenger &self) { return new G4GeneralParticleSourceMessenger(self); },
         py::return_value_policy::reference)

      .def(
         "__deepcopy__",
         [](const G4GeneralParticleSourceMessenger &self, py::dict) {
            return new G4GeneralParticleSourceMessenger(self);
         },
         py::return_value_policy::reference)

      .def_static("Destroy", &G4GeneralParticleSourceMessenger::Destroy)
      .def("GetCurrentValue", &G4GeneralParticleSourceMessenger::GetCurrentValue, py::arg("command"))
      .def_static("GetInstance", &G4GeneralParticleSourceMessenger::GetInstance, py::return_value_policy::reference)
      .def("SetNewValue", &G4GeneralParticleSourceMessenger::SetNewValue, py::arg("command"), py::arg("newValues"))
      .def("SetParticleGun", &G4GeneralParticleSourceMessenger::SetParticleGun, py::arg("fpg"));
}
