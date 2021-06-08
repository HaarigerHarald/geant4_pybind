#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4ParticleDefinition.hh>
#include <G4PrimaryParticle.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4PrimaryParticle(py::module &m)
{
   py::class_<G4PrimaryParticle>(m, "G4PrimaryParticle", "primary particle")
      .def(py::init<>())
      .def(py::init<G4int>())
      .def(py::init<G4int, G4double, G4double, G4double>())
      .def(py::init<G4int, G4double, G4double, G4double, G4double>())
      .def(py::init<const G4ParticleDefinition *>())
      .def(py::init<const G4ParticleDefinition *, G4double, G4double, G4double>())
      .def(py::init<const G4ParticleDefinition *, G4double, G4double, G4double, G4double>())

      .def_property_readonly("Px", &G4PrimaryParticle::GetPx)
      .def_property_readonly("Py", &G4PrimaryParticle::GetPy)
      .def_property_readonly("Pz", &G4PrimaryParticle::GetPz)

      .def("Print", &G4PrimaryParticle::Print)
      .def("GetPDGcode", &G4PrimaryParticle::GetPDGcode)
      .def("GetG4code", &G4PrimaryParticle::GetG4code, py::return_value_policy::reference_internal)
      .def("GetMomentum", &G4PrimaryParticle::GetMomentum)
      .def("GetPx", &G4PrimaryParticle::GetPx)
      .def("GetPy", &G4PrimaryParticle::GetPy)
      .def("GetPz", &G4PrimaryParticle::GetPz)
      .def("Set4Momentum", &G4PrimaryParticle::Set4Momentum)
      .def("SetMomentumDirection", &G4PrimaryParticle::SetMomentumDirection)
      .def("GetNext", &G4PrimaryParticle::GetNext, py::return_value_policy::reference_internal)
      .def("GetDaughter", &G4PrimaryParticle::GetNext, py::return_value_policy::reference_internal)
      .def("GetTrackID", &G4PrimaryParticle::GetTrackID)
      .def("GetMass", &G4PrimaryParticle::GetMass)
      .def("SetMass", &G4PrimaryParticle::SetMass)
      .def("GetCharge", &G4PrimaryParticle::GetCharge)
      .def("SetCharge", &G4PrimaryParticle::SetCharge)
      .def("GetPolarization", &G4PrimaryParticle::GetPolarization)
      .def("GetPolX", &G4PrimaryParticle::GetPolX)
      .def("GetPolY", &G4PrimaryParticle::GetPolY)
      .def("GetPolZ", &G4PrimaryParticle::GetPolZ)
      .def("GetWeight", &G4PrimaryParticle::GetWeight)
      .def("SetWeight", &G4PrimaryParticle::SetWeight)
      .def("GetProperTime", &G4PrimaryParticle::GetProperTime);
}
