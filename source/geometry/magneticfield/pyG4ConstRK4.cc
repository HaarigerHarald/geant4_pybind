#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4ConstRK4.hh>
#include <G4MagneticField.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4ConstRK4 : public G4ConstRK4, public py::trampoline_self_life_support {
public:
   using G4ConstRK4::G4ConstRK4;

   void Stepper(const G4double *y, const G4double *dydx, G4double h, G4double *yout, G4double *yerr) override
   {
      PYBIND11_OVERRIDE(void, G4ConstRK4, Stepper, y, dydx, h, yout, yerr);
   }

   void DumbStepper(const G4double *yIn, const G4double *dydx, G4double h, G4double *yOut) override
   {
      PYBIND11_OVERRIDE(void, G4ConstRK4, DumbStepper, yIn, dydx, h, yOut);
   }

   G4double DistChord() const override { PYBIND11_OVERRIDE(G4double, G4ConstRK4, DistChord, ); }

   G4int IntegratorOrder() const override { PYBIND11_OVERRIDE(G4int, G4ConstRK4, IntegratorOrder, ); }
};

void export_G4ConstRK4(py::module &m)
{
   py::class_<G4ConstRK4, PyG4ConstRK4, G4MagErrorStepper>(m, "G4ConstRK4")

      .def(py::init<G4Mag_EqRhs *, G4int>(), py::arg("EquationMotion"), py::arg("numberOfStateVariables") = 8)
      .def("Stepper", &G4ConstRK4::Stepper, py::arg("y"), py::arg("dydx"), py::arg("h"), py::arg("yout"),
           py::arg("yerr"))

      .def("DumbStepper", &G4ConstRK4::DumbStepper, py::arg("yIn"), py::arg("dydx"), py::arg("h"), py::arg("yOut"))
      .def("DistChord", &G4ConstRK4::DistChord)
      .def("RightHandSideConst", &G4ConstRK4::RightHandSideConst, py::arg("y"), py::arg("dydx"))
      .def("GetConstField", &G4ConstRK4::GetConstField, py::arg("y"), py::arg("Field"))
      .def("IntegratorOrder", &G4ConstRK4::IntegratorOrder);
}
