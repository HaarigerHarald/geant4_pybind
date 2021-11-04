#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4Mag_SpinEqRhs.hh>
#include <G4MagneticField.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4Mag_SpinEqRhs : public G4Mag_SpinEqRhs, public py::trampoline_self_life_support {
public:
   using G4Mag_SpinEqRhs::G4Mag_SpinEqRhs;

   void SetChargeMomentumMass(G4ChargeState particleCharge, G4double MomentumXc, G4double mass) override
   {
      PYBIND11_OVERRIDE(void, G4Mag_SpinEqRhs, SetChargeMomentumMass, particleCharge, MomentumXc, mass);
   }

   void EvaluateRhsGivenB(const G4double *y, const G4double *B, G4double *dydx) const override
   {
      PYBIND11_OVERRIDE(void, G4Mag_SpinEqRhs, EvaluateRhsGivenB, y, B, dydx);
   }
};

void export_G4Mag_SpinEqRhs(py::module &m)
{
   py::class_<G4Mag_SpinEqRhs, PyG4Mag_SpinEqRhs, G4Mag_EqRhs>(m, "G4Mag_SpinEqRhs")

      .def(py::init<G4MagneticField *>(), py::arg("MagField"))
      .def("__copy__", [](const PyG4Mag_SpinEqRhs &self) { return PyG4Mag_SpinEqRhs(self); })
      .def("__deepcopy__", [](const PyG4Mag_SpinEqRhs &self, py::dict) { return PyG4Mag_SpinEqRhs(self); })
      .def("SetChargeMomentumMass", &G4Mag_SpinEqRhs::SetChargeMomentumMass, py::arg("particleCharge"),
           py::arg("MomentumXc"), py::arg("mass"))

      .def("EvaluateRhsGivenB", &G4Mag_SpinEqRhs::EvaluateRhsGivenB, py::arg("y"), py::arg("B"), py::arg("dydx"))
      .def("SetAnomaly", &G4Mag_SpinEqRhs::SetAnomaly, py::arg("a"))
      .def("GetAnomaly", &G4Mag_SpinEqRhs::GetAnomaly);
}
