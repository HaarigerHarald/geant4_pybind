#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4MagIntegratorStepper.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4MagIntegratorStepper : public G4MagIntegratorStepper, public py::trampoline_self_life_support {
public:
   using G4MagIntegratorStepper::G4MagIntegratorStepper;

   void Stepper(const G4double *y, const G4double *dydx, G4double h, G4double *yout, G4double *yerr) override
   {
      PYBIND11_OVERRIDE_PURE(void, G4MagIntegratorStepper, Stepper, y, dydx, h, yout, yerr);
   }

   G4double DistChord() const override { PYBIND11_OVERRIDE_PURE(G4double, G4MagIntegratorStepper, DistChord, ); }

   G4int IntegratorOrder() const override { PYBIND11_OVERRIDE_PURE(G4int, G4MagIntegratorStepper, IntegratorOrder, ); }
};

void export_G4MagIntegratorStepper(py::module &m)
{
   py::class_<G4MagIntegratorStepper, PyG4MagIntegratorStepper>(m, "G4MagIntegratorStepper")

      .def(py::init<G4EquationOfMotion *, G4int, G4int, G4bool>(), py::arg("Equation"),
           py::arg("numIntegrationVariables"), py::arg("numStateVariables") = 12, py::arg("isFSAL") = false)

      .def("Stepper", &G4MagIntegratorStepper::Stepper, py::arg("y"), py::arg("dydx"), py::arg("h"), py::arg("yout"),
           py::arg("yerr"))

      .def("DistChord", &G4MagIntegratorStepper::DistChord)
      .def("NormaliseTangentVector", &G4MagIntegratorStepper::NormaliseTangentVector, py::arg("vec"))
      .def("NormalisePolarizationVector", &G4MagIntegratorStepper::NormalisePolarizationVector, py::arg("vec"))
      .def("RightHandSide",
           py::overload_cast<const G4double *, G4double *>(&G4MagIntegratorStepper::RightHandSide, py::const_),
           py::arg("y"), py::arg("dydx"))

      .def("RightHandSide",
           py::overload_cast<const G4double *, G4double *, G4double *>(&G4MagIntegratorStepper::RightHandSide,
                                                                       py::const_),
           py::arg("y"), py::arg("dydx"), py::arg("field"))

      .def("GetNumberOfVariables", &G4MagIntegratorStepper::GetNumberOfVariables)
      .def("GetNumberOfStateVariables", &G4MagIntegratorStepper::GetNumberOfStateVariables)
      .def("IntegratorOrder", &G4MagIntegratorStepper::IntegratorOrder)
      .def("IntegrationOrder", &G4MagIntegratorStepper::IntegrationOrder)
      .def("GetEquationOfMotion", py::overload_cast<>(&G4MagIntegratorStepper::GetEquationOfMotion),
           py::return_value_policy::reference)

      .def("GetEquationOfMotion", py::overload_cast<>(&G4MagIntegratorStepper::GetEquationOfMotion, py::const_),
           py::return_value_policy::reference)

      .def("SetEquationOfMotion", &G4MagIntegratorStepper::SetEquationOfMotion, py::arg("newEquation"))
      .def("GetfNoRHSCalls", &G4MagIntegratorStepper::GetfNoRHSCalls)
      .def("ResetfNORHSCalls", &G4MagIntegratorStepper::ResetfNORHSCalls)
      .def("IsFSAL", &G4MagIntegratorStepper::IsFSAL);
}
