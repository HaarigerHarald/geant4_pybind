#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4ChargeState.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4ChargeState(py::module &m)
{
   py::class_<G4ChargeState>(m, "G4ChargeState")

      .def(py::init<G4double, G4double, G4double, G4double, G4double>(), py::arg("charge"),
           py::arg("magnetic_dipole_moment"), py::arg("pdgSpin"), py::arg("electric_dipole_moment") = 0.,
           py::arg("magnetic_charge") = 0.)

      .def("__copy__", [](const G4ChargeState &self) { return G4ChargeState(self); })
      .def("__deepcopy__", [](const G4ChargeState &self, py::dict) { return G4ChargeState(self); })
      .def("SetChargeSpinMoments", &G4ChargeState::SetChargeSpinMoments, py::arg("charge"), py::arg("pdgSpin"),
           py::arg("magnetic_dipole_moment") = DBL_MAX, py::arg("electric_dipole_moment") = DBL_MAX,
           py::arg("magnetic_charge") = DBL_MAX)

      .def("SetCharge", &G4ChargeState::SetCharge, py::arg("charge"))
      .def("GetCharge", &G4ChargeState::GetCharge)
      .def("SetPDGSpin", &G4ChargeState::SetPDGSpin, py::arg("spin"))
      .def("GetPDGSpin", &G4ChargeState::GetPDGSpin)
      .def("SetMagneticDipoleMoment", &G4ChargeState::SetMagneticDipoleMoment, py::arg("moment"))
      .def("GetMagneticDipoleMoment", &G4ChargeState::GetMagneticDipoleMoment)
      .def("SetElectricDipoleMoment", &G4ChargeState::SetElectricDipoleMoment, py::arg("moment"))
      .def("ElectricDipoleMoment", &G4ChargeState::ElectricDipoleMoment)
      .def("SetMagneticCharge", &G4ChargeState::SetMagneticCharge, py::arg("charge"))
      .def("MagneticCharge", &G4ChargeState::MagneticCharge)
      .def("SetChargeMdm", &G4ChargeState::SetChargeMdm, py::arg("charge"), py::arg("mag_dipole_moment"))
      .def("SetChargeMdmSpin", &G4ChargeState::SetChargeMdmSpin, py::arg("charge"), py::arg("magnetic_dipole_moment"),
           py::arg("pdgSpin"))

      .def("SetChargeSpin", &G4ChargeState::SetChargeSpin, py::arg("charge"), py::arg("pdgSpin"))
      .def("SetChargeDipoleMoments", &G4ChargeState::SetChargeDipoleMoments, py::arg("charge"),
           py::arg("magnetic_dipole_moment"), py::arg("electric_dipole_moment"))

      .def("SetChargesAndMoments", &G4ChargeState::SetChargesAndMoments, py::arg("charge"),
           py::arg("magnetic_dipole_moment"), py::arg("electric_dipole_moment"), py::arg("magnetic_charge"))

      .def("SetSpin", &G4ChargeState::SetSpin, py::arg("spin"))
      .def("GetSpin", &G4ChargeState::GetSpin);
}
