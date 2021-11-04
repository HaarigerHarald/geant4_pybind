#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4MonopoleEq.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4MonopoleEq : public G4MonopoleEq, public py::trampoline_self_life_support {
public:
   using G4MonopoleEq::G4MonopoleEq;

   void SetChargeMomentumMass(G4ChargeState particleCharge, G4double MomentumXc, G4double mass) override
   {
      PYBIND11_OVERRIDE(void, G4MonopoleEq, SetChargeMomentumMass, particleCharge, MomentumXc, mass);
   }

   void EvaluateRhsGivenB(const G4double *y, const G4double *Field, G4double *dydx) const override
   {
      PYBIND11_OVERRIDE(void, G4MonopoleEq, EvaluateRhsGivenB, y, Field, dydx);
   }
};

void export_G4MonopoleEq(py::module &m)
{
   py::class_<G4MonopoleEq, PyG4MonopoleEq, G4EquationOfMotion>(m, "G4MonopoleEq")

      .def(py::init<G4ElectroMagneticField *>(), py::arg("emField"))
      .def("__copy__", [](const PyG4MonopoleEq &self) { return PyG4MonopoleEq(self); })
      .def("__deepcopy__", [](const PyG4MonopoleEq &self, py::dict) { return PyG4MonopoleEq(self); })
      .def("SetChargeMomentumMass", &G4MonopoleEq::SetChargeMomentumMass, py::arg("particleCharge"),
           py::arg("MomentumXc"), py::arg("mass"))

      .def("EvaluateRhsGivenB", &G4MonopoleEq::EvaluateRhsGivenB, py::arg("y"), py::arg("Field"), py::arg("dydx"));
}
