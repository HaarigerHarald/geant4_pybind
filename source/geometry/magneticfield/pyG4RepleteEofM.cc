#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4RepleteEofM.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4RepleteEofM : public G4RepleteEofM, public py::trampoline_self_life_support {
public:
   using G4RepleteEofM::G4RepleteEofM;

   void SetChargeMomentumMass(G4ChargeState particleCharge, G4double MomentumXc, G4double mass) override
   {
      PYBIND11_OVERRIDE(void, G4RepleteEofM, SetChargeMomentumMass, particleCharge, MomentumXc, mass);
   }

   void EvaluateRhsGivenB(const G4double *y, const G4double *Field, G4double *dydx) const override
   {
      PYBIND11_OVERRIDE(void, G4RepleteEofM, EvaluateRhsGivenB, y, Field, dydx);
   }
};

void export_G4RepleteEofM(py::module &m)
{
   py::class_<G4RepleteEofM, PyG4RepleteEofM, G4EquationOfMotion>(m, "G4RepleteEofM")

      .def(py::init<G4Field *, G4int>(), py::arg("arg0"), py::arg("nvar") = 8)
      .def("__copy__", [](const PyG4RepleteEofM &self) { return PyG4RepleteEofM(self); })
      .def("__deepcopy__", [](const PyG4RepleteEofM &self, py::dict) { return PyG4RepleteEofM(self); })
      .def("SetChargeMomentumMass", &G4RepleteEofM::SetChargeMomentumMass, py::arg("particleCharge"),
           py::arg("MomentumXc"), py::arg("mass"))

      .def("EvaluateRhsGivenB", &G4RepleteEofM::EvaluateRhsGivenB, py::arg("y"), py::arg("Field"), py::arg("dydx"))
      .def("SetAnomaly", &G4RepleteEofM::SetAnomaly, py::arg("a"))
      .def("GetAnomaly", &G4RepleteEofM::GetAnomaly)
      .def("SetBField", &G4RepleteEofM::SetBField)
      .def("SetEField", &G4RepleteEofM::SetEField)
      .def("SetgradB", &G4RepleteEofM::SetgradB)
      .def("SetSpin", &G4RepleteEofM::SetSpin);
}
