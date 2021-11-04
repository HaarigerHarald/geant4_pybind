#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4DormandPrinceRK78.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4DormandPrinceRK78 : public G4DormandPrinceRK78, public py::trampoline_self_life_support {
public:
   using G4DormandPrinceRK78::G4DormandPrinceRK78;

   void Stepper(const G4double *y, const G4double *dydx, G4double h, G4double *yout, G4double *yerr) override
   {
      PYBIND11_OVERRIDE(void, G4DormandPrinceRK78, Stepper, y, dydx, h, yout, yerr);
   }

   G4double DistChord() const override { PYBIND11_OVERRIDE(G4double, G4DormandPrinceRK78, DistChord, ); }

   G4int IntegratorOrder() const override { PYBIND11_OVERRIDE(G4int, G4DormandPrinceRK78, IntegratorOrder, ); }
};

void export_G4DormandPrinceRK78(py::module &m)
{
   py::class_<G4DormandPrinceRK78, PyG4DormandPrinceRK78, G4MagIntegratorStepper>(m, "G4DormandPrinceRK78")

      .def(py::init<G4EquationOfMotion *, G4int, G4bool>(), py::arg("EqRhs"), py::arg("numberOfVariables") = 6,
           py::arg("primary") = true)

      .def("Stepper", &G4DormandPrinceRK78::Stepper, py::arg("y"), py::arg("dydx"), py::arg("h"), py::arg("yout"),
           py::arg("yerr"))

      .def("DistChord", &G4DormandPrinceRK78::DistChord)
      .def("IntegratorOrder", &G4DormandPrinceRK78::IntegratorOrder);
}
