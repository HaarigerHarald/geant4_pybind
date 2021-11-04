#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4EqMagElectricField.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4EqMagElectricField : public G4EqMagElectricField, public py::trampoline_self_life_support {
public:
   using G4EqMagElectricField::G4EqMagElectricField;

   void SetChargeMomentumMass(G4ChargeState particleCharge, G4double MomentumXc, G4double mass) override
   {
      PYBIND11_OVERRIDE(void, G4EqMagElectricField, SetChargeMomentumMass, particleCharge, MomentumXc, mass);
   }

   void EvaluateRhsGivenB(const G4double *y, const G4double *Field, G4double *dydx) const override
   {
      PYBIND11_OVERRIDE(void, G4EqMagElectricField, EvaluateRhsGivenB, y, Field, dydx);
   }
};

void export_G4EqMagElectricField(py::module &m)
{
   py::class_<G4EqMagElectricField, PyG4EqMagElectricField, G4EquationOfMotion>(m, "G4EqMagElectricField")

      .def(py::init<G4ElectroMagneticField *>(), py::arg("emField"))
      .def("__copy__", [](const PyG4EqMagElectricField &self) { return PyG4EqMagElectricField(self); })
      .def("__deepcopy__", [](const PyG4EqMagElectricField &self, py::dict) { return PyG4EqMagElectricField(self); })
      .def("SetChargeMomentumMass", &G4EqMagElectricField::SetChargeMomentumMass, py::arg("particleCharge"),
           py::arg("MomentumXc"), py::arg("mass"))

      .def("EvaluateRhsGivenB", &G4EqMagElectricField::EvaluateRhsGivenB, py::arg("y"), py::arg("Field"),
           py::arg("dydx"));
}
