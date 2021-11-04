#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4Mag_UsualEqRhs.hh>
#include <G4MagneticField.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4Mag_UsualEqRhs : public G4Mag_UsualEqRhs, public py::trampoline_self_life_support {
public:
   using G4Mag_UsualEqRhs::G4Mag_UsualEqRhs;

   void EvaluateRhsGivenB(const G4double *y, const G4double *B, G4double *dydx) const override
   {
      PYBIND11_OVERRIDE(void, G4Mag_UsualEqRhs, EvaluateRhsGivenB, y, B, dydx);
   }

   void SetChargeMomentumMass(G4ChargeState particleCharge, G4double MomentumXc, G4double mass) override
   {
      PYBIND11_OVERRIDE(void, G4Mag_UsualEqRhs, SetChargeMomentumMass, particleCharge, MomentumXc, mass);
   }
};

void export_G4Mag_UsualEqRhs(py::module &m)
{
   py::class_<G4Mag_UsualEqRhs, PyG4Mag_UsualEqRhs, G4Mag_EqRhs>(m, "G4Mag_UsualEqRhs")

      .def(py::init<G4MagneticField *>(), py::arg("MagField"))
      .def("__copy__", [](const PyG4Mag_UsualEqRhs &self) { return PyG4Mag_UsualEqRhs(self); })
      .def("__deepcopy__", [](const PyG4Mag_UsualEqRhs &self, py::dict) { return PyG4Mag_UsualEqRhs(self); })
      .def("EvaluateRhsGivenB", &G4Mag_UsualEqRhs::EvaluateRhsGivenB, py::arg("y"), py::arg("B"), py::arg("dydx"))
      .def("SetChargeMomentumMass", &G4Mag_UsualEqRhs::SetChargeMomentumMass, py::arg("particleCharge"),
           py::arg("MomentumXc"), py::arg("mass"));
}
