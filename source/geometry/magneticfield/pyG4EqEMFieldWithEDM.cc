#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4EqEMFieldWithEDM.hh>
#include <G4ElectroMagneticField.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4EqEMFieldWithEDM : public G4EqEMFieldWithEDM, public py::trampoline_self_life_support {
public:
   using G4EqEMFieldWithEDM::G4EqEMFieldWithEDM;

   void SetChargeMomentumMass(G4ChargeState particleCharge, G4double MomentumXc, G4double mass) override
   {
      PYBIND11_OVERRIDE(void, G4EqEMFieldWithEDM, SetChargeMomentumMass, particleCharge, MomentumXc, mass);
   }

   void EvaluateRhsGivenB(const G4double *y, const G4double *Field, G4double *dydx) const override
   {
      PYBIND11_OVERRIDE(void, G4EqEMFieldWithEDM, EvaluateRhsGivenB, y, Field, dydx);
   }
};

void export_G4EqEMFieldWithEDM(py::module &m)
{
   py::class_<G4EqEMFieldWithEDM, PyG4EqEMFieldWithEDM, G4EquationOfMotion>(m, "G4EqEMFieldWithEDM")

      .def(py::init<G4ElectroMagneticField *>(), py::arg("emField"))
      .def("__copy__", [](const PyG4EqEMFieldWithEDM &self) { return PyG4EqEMFieldWithEDM(self); })
      .def("__deepcopy__", [](const PyG4EqEMFieldWithEDM &self, py::dict) { return PyG4EqEMFieldWithEDM(self); })
      .def("SetChargeMomentumMass", &G4EqEMFieldWithEDM::SetChargeMomentumMass, py::arg("particleCharge"),
           py::arg("MomentumXc"), py::arg("mass"))

      .def("EvaluateRhsGivenB", &G4EqEMFieldWithEDM::EvaluateRhsGivenB, py::arg("y"), py::arg("Field"), py::arg("dydx"))
      .def("SetAnomaly", &G4EqEMFieldWithEDM::SetAnomaly, py::arg("a"))
      .def("GetAnomaly", &G4EqEMFieldWithEDM::GetAnomaly)
      .def("SetEta", &G4EqEMFieldWithEDM::SetEta, py::arg("n"))
      .def("GetEta", &G4EqEMFieldWithEDM::GetEta);
}
