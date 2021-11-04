#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4EqEMFieldWithSpin.hh>
#include <G4ElectroMagneticField.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4EqEMFieldWithSpin : public G4EqEMFieldWithSpin, public py::trampoline_self_life_support {
public:
   using G4EqEMFieldWithSpin::G4EqEMFieldWithSpin;

   void SetChargeMomentumMass(G4ChargeState particleCharge, G4double MomentumXc, G4double mass) override
   {
      PYBIND11_OVERRIDE(void, G4EqEMFieldWithSpin, SetChargeMomentumMass, particleCharge, MomentumXc, mass);
   }

   void EvaluateRhsGivenB(const G4double *y, const G4double *Field, G4double *dydx) const override
   {
      PYBIND11_OVERRIDE(void, G4EqEMFieldWithSpin, EvaluateRhsGivenB, y, Field, dydx);
   }
};

void export_G4EqEMFieldWithSpin(py::module &m)
{
   py::class_<G4EqEMFieldWithSpin, PyG4EqEMFieldWithSpin, G4EquationOfMotion>(m, "G4EqEMFieldWithSpin")

      .def(py::init<G4ElectroMagneticField *>(), py::arg("emField"))
      .def("__copy__", [](const PyG4EqEMFieldWithSpin &self) { return PyG4EqEMFieldWithSpin(self); })
      .def("__deepcopy__", [](const PyG4EqEMFieldWithSpin &self, py::dict) { return PyG4EqEMFieldWithSpin(self); })
      .def("SetChargeMomentumMass", &G4EqEMFieldWithSpin::SetChargeMomentumMass, py::arg("particleCharge"),
           py::arg("MomentumXc"), py::arg("mass"))

      .def("EvaluateRhsGivenB", &G4EqEMFieldWithSpin::EvaluateRhsGivenB, py::arg("y"), py::arg("Field"),
           py::arg("dydx"))

      .def("SetAnomaly", &G4EqEMFieldWithSpin::SetAnomaly, py::arg("a"))
      .def("GetAnomaly", &G4EqEMFieldWithSpin::GetAnomaly);
}
