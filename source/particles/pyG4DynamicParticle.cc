#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4DynamicParticle.hh>
#include <G4PrimaryParticle.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4DynamicParticle(py::module &m)
{
   py::class_<G4DynamicParticle>(m, "G4DynamicParticle", "dynamic particle")
      .def(py::init<>())
      .def(py::init<const G4ParticleDefinition *, const G4ThreeVector &>())
      .def(py::init<const G4ParticleDefinition *, const G4LorentzVector &>())
      .def(py::init<const G4ParticleDefinition *, G4double, const G4ThreeVector &>())
      .def(py::init<const G4ParticleDefinition *, const G4ThreeVector &, G4double, G4double>())
      .def(py::init<const G4DynamicParticle &>())

      .def("GetMomentumDirection", &G4DynamicParticle::GetMomentumDirection)
      .def("GetMomentum", &G4DynamicParticle::GetMomentum)
      //.def("Get4Momentum",       &G4DynamicParticle::Get4Momentum,TODO
      // return_value_policy<return_by_value>())
      .def("GetTotalMomentum", &G4DynamicParticle::GetTotalMomentum)
      .def("GetTotalEnergy", &G4DynamicParticle::GetTotalEnergy)
      .def("GetKineticEnergy", &G4DynamicParticle::GetKineticEnergy)
      .def("GetProperTime", &G4DynamicParticle::GetProperTime)
      .def("GetPolarization", &G4DynamicParticle::GetPolarization)
      .def("GetMass", &G4DynamicParticle::GetMass)
      .def("GetCharge", &G4DynamicParticle::GetCharge)
      //.def("GetElectronOccupancy", &G4DynamicParticle::GetElectronOccupancy, TODO
      // py::return_value_policy::reference_internal)
      .def("GetTotalOccupancy", &G4DynamicParticle::GetTotalOccupancy)
      .def("GetOccupancy", &G4DynamicParticle::GetOccupancy)
      .def("GetDefinition", &G4DynamicParticle::GetDefinition, py::return_value_policy::reference_internal)
      .def("GetPreAssignedDecayProperTime", &G4DynamicParticle::GetPreAssignedDecayProperTime)
      .def("DumpInfo", &G4DynamicParticle::DumpInfo)
      .def("SetVerboseLevel", &G4DynamicParticle::SetVerboseLevel)
      .def("GetVerboseLevel", &G4DynamicParticle::GetVerboseLevel)
      .def("GetPrimaryParticle", &G4DynamicParticle::GetPrimaryParticle, py::return_value_policy::reference_internal)
      .def("GetPDGcode", &G4DynamicParticle::GetPDGcode);
}
