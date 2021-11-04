#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4EqGravityField.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4EqGravityField : public G4EqGravityField, public py::trampoline_self_life_support {
public:
   using G4EqGravityField::G4EqGravityField;

   void SetChargeMomentumMass(G4ChargeState particleCharge, G4double MomentumXc, G4double mass) override
   {
      PYBIND11_OVERRIDE(void, G4EqGravityField, SetChargeMomentumMass, particleCharge, MomentumXc, mass);
   }

   void EvaluateRhsGivenB(const G4double *y, const G4double *Field, G4double *dydx) const override
   {
      PYBIND11_OVERRIDE(void, G4EqGravityField, EvaluateRhsGivenB, y, Field, dydx);
   }
};

void export_G4EqGravityField(py::module &m)
{
   py::class_<G4EqGravityField, PyG4EqGravityField, G4EquationOfMotion>(m, "G4EqGravityField")

      .def(py::init<G4UniformGravityField *>(), py::arg("gField"))
      .def("__copy__", [](const PyG4EqGravityField &self) { return PyG4EqGravityField(self); })
      .def("__deepcopy__", [](const PyG4EqGravityField &self, py::dict) { return PyG4EqGravityField(self); })
      .def("SetChargeMomentumMass", &G4EqGravityField::SetChargeMomentumMass, py::arg("particleCharge"),
           py::arg("MomentumXc"), py::arg("mass"))

      .def("EvaluateRhsGivenB", &G4EqGravityField::EvaluateRhsGivenB, py::arg("y"), py::arg("Field"), py::arg("dydx"));
}
