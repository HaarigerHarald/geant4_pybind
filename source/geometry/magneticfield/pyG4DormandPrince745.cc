#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4DormandPrince745.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4DormandPrince745 : public G4DormandPrince745, public py::trampoline_self_life_support {
public:
   using G4DormandPrince745::G4DormandPrince745;

   void Stepper(const G4double *yInput, const G4double *dydx, G4double hstep, G4double *yOutput,
                G4double *yError) override
   {
      PYBIND11_OVERRIDE(void, G4DormandPrince745, Stepper, yInput, dydx, hstep, yOutput, yError);
   }

   G4double DistChord() const override { PYBIND11_OVERRIDE(G4double, G4DormandPrince745, DistChord, ); }

   G4int IntegratorOrder() const override { PYBIND11_OVERRIDE(G4int, G4DormandPrince745, IntegratorOrder, ); }
};

void export_G4DormandPrince745(py::module &m)
{
   py::class_<G4DormandPrince745, PyG4DormandPrince745, G4MagIntegratorStepper>(m, "G4DormandPrince745")

      .def(py::init<G4EquationOfMotion *, G4int>(), py::arg("equation"), py::arg("numberOfVariables") = 6)
      .def("Stepper",
           py::overload_cast<const G4double *, const G4double *, G4double, G4double *, G4double *>(
              &G4DormandPrince745::Stepper),
           py::arg("yInput"), py::arg("dydx"), py::arg("hstep"), py::arg("yOutput"), py::arg("yError"))

      .def("Stepper",
           py::overload_cast<const G4double *, const G4double *, G4double, G4double *, G4double *, G4double *>(
              &G4DormandPrince745::Stepper),
           py::arg("yInput"), py::arg("dydx"), py::arg("hstep"), py::arg("yOutput"), py::arg("yError"),
           py::arg("dydxOutput"))

      .def("SetupInterpolation", &G4DormandPrince745::SetupInterpolation)
      .def("Interpolate", &G4DormandPrince745::Interpolate, py::arg("tau"), py::arg("yOut"))
      .def("DistChord", &G4DormandPrince745::DistChord)
      .def("IntegratorOrder", &G4DormandPrince745::IntegratorOrder)
      .def("StepperType", &G4DormandPrince745::StepperType)
      .def("StepperDescription", &G4DormandPrince745::StepperDescription)
      .def("GetYOut", &G4DormandPrince745::GetYOut)
      .def("Interpolate4thOrder", &G4DormandPrince745::Interpolate4thOrder, py::arg("yOut"), py::arg("tau"))
      .def("SetupInterpolation5thOrder", &G4DormandPrince745::SetupInterpolation5thOrder)
      .def("Interpolate5thOrder", &G4DormandPrince745::Interpolate5thOrder, py::arg("yOut"), py::arg("tau"))
      .def("GetSpecificEquation", &G4DormandPrince745::GetSpecificEquation, py::return_value_policy::reference);
}
