#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4NystromRK4.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4NystromRK4 : public G4NystromRK4, public py::trampoline_self_life_support {
public:
   using G4NystromRK4::G4NystromRK4;

   void Stepper(const G4double *y, const G4double *dydx, G4double hstep, G4double *yOut, G4double *yError) override
   {
      PYBIND11_OVERRIDE(void, G4NystromRK4, Stepper, y, dydx, hstep, yOut, yError);
   }

   G4int IntegratorOrder() const override { PYBIND11_OVERRIDE(G4int, G4NystromRK4, IntegratorOrder, ); }

   G4double DistChord() const override { PYBIND11_OVERRIDE(G4double, G4NystromRK4, DistChord, ); }
};

void export_G4NystromRK4(py::module &m)
{
   py::class_<G4NystromRK4, PyG4NystromRK4, G4MagIntegratorStepper>(m, "G4NystromRK4")

      .def(py::init<G4Mag_EqRhs *, G4double>(), py::arg("EquationMotion"), py::arg("distanceConstField") = 0.)
      .def("Stepper", &G4NystromRK4::Stepper, py::arg("y"), py::arg("dydx"), py::arg("hstep"), py::arg("yOut"),
           py::arg("yError"))

      .def("SetDistanceForConstantField", &G4NystromRK4::SetDistanceForConstantField, py::arg("length"))
      .def("GetDistanceForConstantField", &G4NystromRK4::GetDistanceForConstantField)
      .def("IntegratorOrder", &G4NystromRK4::IntegratorOrder)
      .def("DistChord", &G4NystromRK4::DistChord);
}
