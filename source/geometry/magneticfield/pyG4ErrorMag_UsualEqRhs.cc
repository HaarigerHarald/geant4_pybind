#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4ErrorMag_UsualEqRhs.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4ErrorMag_UsualEqRhs : public G4ErrorMag_UsualEqRhs, public py::trampoline_self_life_support {
public:
   using G4ErrorMag_UsualEqRhs::G4ErrorMag_UsualEqRhs;

   void EvaluateRhsGivenB(const G4double *y, const G4double *B, G4double *dydx) const override
   {
      PYBIND11_OVERRIDE(void, G4ErrorMag_UsualEqRhs, EvaluateRhsGivenB, y, B, dydx);
   }

   void SetChargeMomentumMass(G4ChargeState particleCharge, G4double MomentumXc, G4double mass) override
   {
      PYBIND11_OVERRIDE(void, G4ErrorMag_UsualEqRhs, SetChargeMomentumMass, particleCharge, MomentumXc, mass);
   }
};

void export_G4ErrorMag_UsualEqRhs(py::module &m)
{
   py::class_<G4ErrorMag_UsualEqRhs, PyG4ErrorMag_UsualEqRhs, G4Mag_UsualEqRhs>(m, "G4ErrorMag_UsualEqRhs")

      .def(py::init<G4MagneticField *>(), py::arg("MagField"))
      .def("__copy__", [](const PyG4ErrorMag_UsualEqRhs &self) { return PyG4ErrorMag_UsualEqRhs(self); })
      .def("__deepcopy__", [](const PyG4ErrorMag_UsualEqRhs &self, py::dict) { return PyG4ErrorMag_UsualEqRhs(self); })
      .def("EvaluateRhsGivenB", &G4ErrorMag_UsualEqRhs::EvaluateRhsGivenB, py::arg("y"), py::arg("B"), py::arg("dydx"));
}
