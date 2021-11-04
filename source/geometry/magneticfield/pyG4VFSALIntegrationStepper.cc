#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4VFSALIntegrationStepper.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4VFSALIntegrationStepper : public G4VFSALIntegrationStepper, public py::trampoline_self_life_support {
public:
   using G4VFSALIntegrationStepper::G4VFSALIntegrationStepper;

   void Stepper(const G4double *y, const G4double *dydx, G4double h, G4double *yout, G4double *yerr,
                G4double *lastDydx) override
   {
      PYBIND11_OVERRIDE_PURE(void, G4VFSALIntegrationStepper, Stepper, y, dydx, h, yout, yerr, lastDydx);
   }

   G4double DistChord() const override { PYBIND11_OVERRIDE_PURE(G4double, G4VFSALIntegrationStepper, DistChord, ); }

   G4int IntegratorOrder() const override
   {
      PYBIND11_OVERRIDE_PURE(G4int, G4VFSALIntegrationStepper, IntegratorOrder, );
   }
};

void export_G4VFSALIntegrationStepper(py::module &m)
{
   py::class_<G4VFSALIntegrationStepper, PyG4VFSALIntegrationStepper>(m, "G4VFSALIntegrationStepper")

      .def(py::init<G4EquationOfMotion *, G4int, G4int>(), py::arg("Equation"), py::arg("numIntegrationVariables"),
           py::arg("numStateVariables") = 12)

      .def("Stepper", &G4VFSALIntegrationStepper::Stepper, py::arg("y"), py::arg("dydx"), py::arg("h"), py::arg("yout"),
           py::arg("yerr"), py::arg("lastDydx"))

      .def("DistChord", &G4VFSALIntegrationStepper::DistChord)
      .def("NormaliseTangentVector", &G4VFSALIntegrationStepper::NormaliseTangentVector, py::arg("vec"))
      .def("NormalisePolarizationVector", &G4VFSALIntegrationStepper::NormalisePolarizationVector, py::arg("vec"))
      .def("RightHandSide", &G4VFSALIntegrationStepper::RightHandSide, py::arg("y"), py::arg("dydx"))
      .def("GetNumberOfVariables", &G4VFSALIntegrationStepper::GetNumberOfVariables)
      .def("GetNumberOfStateVariables", &G4VFSALIntegrationStepper::GetNumberOfStateVariables)
      .def("IntegratorOrder", &G4VFSALIntegrationStepper::IntegratorOrder)
      .def("GetEquationOfMotion", &G4VFSALIntegrationStepper::GetEquationOfMotion, py::return_value_policy::reference)
      .def("SetEquationOfMotion", &G4VFSALIntegrationStepper::SetEquationOfMotion, py::arg("newEquation"))
      .def("GetfNoRHSCalls", &G4VFSALIntegrationStepper::GetfNoRHSCalls)
      .def("increasefNORHSCalls", &G4VFSALIntegrationStepper::increasefNORHSCalls)
      .def("ResetfNORHSCalls", &G4VFSALIntegrationStepper::ResetfNORHSCalls);
}
