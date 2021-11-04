#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4Mag_EqRhs.hh>
#include <G4MagneticField.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4Mag_EqRhs : public G4Mag_EqRhs, public py::trampoline_self_life_support {
public:
   using G4Mag_EqRhs::G4Mag_EqRhs;

   void EvaluateRhsGivenB(const G4double *y, const G4double *B, G4double *dydx) const override
   {
      PYBIND11_OVERRIDE_PURE(void, G4Mag_EqRhs, EvaluateRhsGivenB, y, B, dydx);
   }

   void SetChargeMomentumMass(G4ChargeState particleCharge, G4double MomentumXc, G4double mass) override
   {
      PYBIND11_OVERRIDE(void, G4Mag_EqRhs, SetChargeMomentumMass, particleCharge, MomentumXc, mass);
   }
};

void export_G4Mag_EqRhs(py::module &m)
{
   py::class_<G4Mag_EqRhs, PyG4Mag_EqRhs, G4EquationOfMotion>(m, "G4Mag_EqRhs")

      .def(py::init<G4MagneticField *>(), py::arg("magField"))
      .def("__copy__", [](const PyG4Mag_EqRhs &self) { return PyG4Mag_EqRhs(self); })
      .def("__deepcopy__", [](const PyG4Mag_EqRhs &self, py::dict) { return PyG4Mag_EqRhs(self); })
      .def("EvaluateRhsGivenB", &G4Mag_EqRhs::EvaluateRhsGivenB, py::arg("y"), py::arg("B"), py::arg("dydx"))
      .def("FCof", &G4Mag_EqRhs::FCof)
      .def("SetChargeMomentumMass", &G4Mag_EqRhs::SetChargeMomentumMass, py::arg("particleCharge"),
           py::arg("MomentumXc"), py::arg("mass"));
}
