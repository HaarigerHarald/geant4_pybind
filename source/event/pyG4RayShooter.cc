#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4RayShooter.hh>
#include <G4ProcessManager.hh>
#include <G4VTrackingManager.hh>
#include <G4DecayTable.hh>
#include <G4ParticleTable.hh>
#include <G4ParticlePropertyTable.hh>
#include <G4VUserPrimaryParticleInformation.hh>
#include <G4VUserPrimaryVertexInformation.hh>
#include <G4Event.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4RayShooter(py::module &m)
{
   py::class_<G4RayShooter>(m, "G4RayShooter")

      .def("__copy__", [](const G4RayShooter &self) { return new G4RayShooter(self); })
      .def("__deepcopy__", [](const G4RayShooter &self, py::dict) { return new G4RayShooter(self); })
      .def(py::init<>())
      .def("Shoot", &G4RayShooter::Shoot, py::arg("evt"), py::arg("vtx"), py::arg("direc"));
}
