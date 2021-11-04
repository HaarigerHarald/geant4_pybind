#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4FieldTrack.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4FieldTrack(py::module &m)
{
   py::class_<G4FieldTrack>(m, "G4FieldTrack")

      .def(py::init<const G4ThreeVector &, G4double, const G4ThreeVector &, G4double, G4double, G4double,
                    const G4ThreeVector &, G4double, G4double, G4double>(),
           py::arg("pPosition"), py::arg("LaboratoryTimeOfFlight"), py::arg("pMomentumDirection"),
           py::arg("kineticEnergy"), py::arg("restMass_c2"), py::arg("charge"), py::arg("polarization"),
           py::arg("magnetic_dipole_moment") = 0., py::arg("curve_length") = 0., py::arg("PDGspin") = -1.)

      .def(py::init<char>())
      .def(py::init<const G4ThreeVector &, const G4ThreeVector &, G4double, G4double, const G4double, G4double,
                    G4double, G4double, const G4ThreeVector *, G4double>(),
           py::arg("pPosition"), py::arg("pMomentumDirection"), py::arg("curve_length"), py::arg("kineticEnergy"),
           py::arg("restMass_c2"), py::arg("velocity"), py::arg("LaboratoryTimeOfFlight") = 0.,
           py::arg("ProperTimeOfFlight") = 0., py::arg("pPolarization") = static_cast<const G4ThreeVector *>(nullptr),
           py::arg("PDGspin") = -1.)

      .def("__copy__", [](const G4FieldTrack &self) { return G4FieldTrack(self); })
      .def("__deepcopy__", [](const G4FieldTrack &self, py::dict) { return G4FieldTrack(self); })
      .def("UpdateState", &G4FieldTrack::UpdateState, py::arg("pPosition"), py::arg("LaboratoryTimeOfFlight"),
           py::arg("pMomentumDirection"), py::arg("kineticEnergy"))

      .def("UpdateFourMomentum", &G4FieldTrack::UpdateFourMomentum, py::arg("kineticEnergy"),
           py::arg("momentumDirection"))

      .def("SetChargeAndMoments", &G4FieldTrack::SetChargeAndMoments, py::arg("charge"),
           py::arg("magnetic_dipole_moment") = DBL_MAX, py::arg("electric_dipole_moment") = DBL_MAX,
           py::arg("magnetic_charge") = DBL_MAX)

      .def("SetPDGSpin", &G4FieldTrack::SetPDGSpin, py::arg("pdgSpin"))
      .def("GetPDGSpin", &G4FieldTrack::GetPDGSpin)
      .def("GetMomentum", &G4FieldTrack::GetMomentum)
      .def("GetPosition", &G4FieldTrack::GetPosition)
      .def("GetMomentumDir", &G4FieldTrack::GetMomentumDir)
      .def("GetMomentumDirection", &G4FieldTrack::GetMomentumDirection)
      .def("GetCurveLength", &G4FieldTrack::GetCurveLength)
      .def("GetPolarization", &G4FieldTrack::GetPolarization)
      .def("SetPolarization", &G4FieldTrack::SetPolarization, py::arg("vecPol"))
      .def("GetChargeState", &G4FieldTrack::GetChargeState, py::return_value_policy::reference)
      .def("GetLabTimeOfFlight", &G4FieldTrack::GetLabTimeOfFlight)
      .def("GetProperTimeOfFlight", &G4FieldTrack::GetProperTimeOfFlight)
      .def("GetKineticEnergy", &G4FieldTrack::GetKineticEnergy)
      .def("GetCharge", &G4FieldTrack::GetCharge)
      .def("GetRestMass", &G4FieldTrack::GetRestMass)
      .def("SetPosition", &G4FieldTrack::SetPosition, py::arg("nPos"))
      .def("SetMomentum", &G4FieldTrack::SetMomentum, py::arg("nMomDir"))
      .def("SetMomentumDir", &G4FieldTrack::SetMomentumDir, py::arg("nMomDir"))
      .def("SetRestMass", &G4FieldTrack::SetRestMass, py::arg("Mass_c2"))
      .def("SetCurveLength", &G4FieldTrack::SetCurveLength, py::arg("nCurve_s"))
      .def("SetKineticEnergy", &G4FieldTrack::SetKineticEnergy, py::arg("nEnergy"))
      .def("SetLabTimeOfFlight", &G4FieldTrack::SetLabTimeOfFlight, py::arg("tofLab"))
      .def("SetProperTimeOfFlight", &G4FieldTrack::SetProperTimeOfFlight, py::arg("tofProper"))
      .def("DumpToArray", &G4FieldTrack::DumpToArray, py::arg("valArr"))
      .def("LoadFromArray", &G4FieldTrack::LoadFromArray, py::arg("valArr"), py::arg("noVarsIntegrated"))
      .def("InitialiseSpin", &G4FieldTrack::InitialiseSpin, py::arg("vecPolarization"))
      .def("GetSpin", &G4FieldTrack::GetSpin)
      .def("SetSpin", &G4FieldTrack::SetSpin, py::arg("vSpin"));
}
