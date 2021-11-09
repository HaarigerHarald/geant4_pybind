#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4EquationOfMotion.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4EquationOfMotion : public G4EquationOfMotion, public py::trampoline_self_life_support {
public:
   using G4EquationOfMotion::G4EquationOfMotion;

   void EvaluateRhsGivenB(const G4double *y, const G4double *B, G4double *dydx) const override
   {
      PYBIND11_OVERRIDE_PURE(void, G4EquationOfMotion, EvaluateRhsGivenB, y, B, dydx);
   }

   void SetChargeMomentumMass(G4ChargeState particleCharge, G4double MomentumXc, G4double MassXc2) override
   {
      PYBIND11_OVERRIDE_PURE(void, G4EquationOfMotion, SetChargeMomentumMass, particleCharge, MomentumXc, MassXc2);
   }
};

void export_G4EquationOfMotion(py::module &m)
{
   py::class_<G4EquationOfMotion, PyG4EquationOfMotion>(m, "G4EquationOfMotion")

      .def(py::init<G4Field *>(), py::arg("Field"))
      .def("__copy__", [](const PyG4EquationOfMotion &self) { return PyG4EquationOfMotion(self); })
      .def("__deepcopy__", [](const PyG4EquationOfMotion &self, py::dict) { return PyG4EquationOfMotion(self); })
      .def("EvaluateRhsGivenB", &G4EquationOfMotion::EvaluateRhsGivenB, py::arg("y"), py::arg("B"), py::arg("dydx"))
      .def("SetChargeMomentumMass", &G4EquationOfMotion::SetChargeMomentumMass, py::arg("particleCharge"),
           py::arg("MomentumXc"), py::arg("MassXc2"))

      .def("RightHandSide", &G4EquationOfMotion::RightHandSide, py::arg("y"), py::arg("dydx"))
      .def("EvaluateRhsReturnB", &G4EquationOfMotion::EvaluateRhsReturnB, py::arg("y"), py::arg("dydx"),
           py::arg("Field"))

      .def(
         "GetFieldValue",
         [](G4EquationOfMotion &self, const std::vector<G4double> &pyPoint, py::list pyField) {
            if (pyPoint.size() != 4) {
               py::pybind11_fail("\"G4EquationOfMotion::GetFieldValue\" Point must have 4 components");
            } else if (pyField.size() != 6) {
               py::pybind11_fail("\"G4EquationOfMotion::GetFieldValue\" Field must have 6 components");
            } else {
               G4double field[6] = {0};

               self.GetFieldValue(pyPoint.data(), field);

               for (size_t i = 0; i < 6; i++) {
                  pyField[i] = field[i];
               }
            }
         },
         py::arg("Point"), py::arg("Bfield"))

      .def("GetFieldObj", py::overload_cast<>(&G4EquationOfMotion::GetFieldObj, py::const_),
           py::return_value_policy::reference)

      .def("GetFieldObj", py::overload_cast<>(&G4EquationOfMotion::GetFieldObj), py::return_value_policy::reference)
      .def("SetFieldObj", &G4EquationOfMotion::SetFieldObj, py::arg("pField"));
}
