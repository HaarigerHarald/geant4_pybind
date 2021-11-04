#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4RK547FEq3.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4RK547FEq3 : public G4RK547FEq3, public py::trampoline_self_life_support {
public:
   using G4RK547FEq3::G4RK547FEq3;

   void Stepper(const G4double *yInput, const G4double *dydx, G4double hstep, G4double *yOutput,
                G4double *yError) override
   {
      PYBIND11_OVERRIDE(void, G4RK547FEq3, Stepper, yInput, dydx, hstep, yOutput, yError);
   }

   G4double DistChord() const override { PYBIND11_OVERRIDE(G4double, G4RK547FEq3, DistChord, ); }

   G4int IntegratorOrder() const override { PYBIND11_OVERRIDE(G4int, G4RK547FEq3, IntegratorOrder, ); }
};

void export_G4RK547FEq3(py::module &m)
{
   py::class_<G4RK547FEq3, PyG4RK547FEq3, G4MagIntegratorStepper>(m, "G4RK547FEq3")

      .def(py::init<G4EquationOfMotion *, G4int>(), py::arg("EqRhs"), py::arg("integrationVariables") = 6)

      .def(
         "Stepper",
         py::overload_cast<const G4double *, const G4double *, G4double, G4double *, G4double *>(&G4RK547FEq3::Stepper),
         py::arg("yInput"), py::arg("dydx"), py::arg("hstep"), py::arg("yOutput"), py::arg("yError"))

      .def("Stepper",
           py::overload_cast<const G4double *, const G4double *, G4double, G4double *, G4double *, G4double *>(
              &G4RK547FEq3::Stepper),
           py::arg("yInput"), py::arg("dydx"), py::arg("hstep"), py::arg("yOutput"), py::arg("yError"),
           py::arg("dydxOutput"))

      .def("DistChord", &G4RK547FEq3::DistChord)
      .def("IntegratorOrder", &G4RK547FEq3::IntegratorOrder);
}
