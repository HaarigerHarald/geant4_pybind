#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4ModifiedMidpoint.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4ModifiedMidpoint(py::module &m)
{
   py::class_<G4ModifiedMidpoint>(m, "G4ModifiedMidpoint")

      .def(py::init<G4EquationOfMotion *, G4int, G4int>(), py::arg("equation"), py::arg("nvar") = 6,
           py::arg("steps") = 2)

      .def("__copy__", [](const G4ModifiedMidpoint &self) { return G4ModifiedMidpoint(self); })
      .def("__deepcopy__", [](const G4ModifiedMidpoint &self, py::dict) { return G4ModifiedMidpoint(self); })
      .def("DoStep",
           py::overload_cast<const G4double *, const G4double *, G4double *, G4double>(&G4ModifiedMidpoint::DoStep,
                                                                                       py::const_),
           py::arg("yIn"), py::arg("dydxIn"), py::arg("yOut"), py::arg("hstep"))

      //  .def("DoStep",
      //       py::overload_cast<const G4double *, const G4double *, G4double *, G4double, G4double *,
      //                         G4double(*)[G4FieldTrack::ncompSVEC]>(&G4ModifiedMidpoint::DoStep, py::const_),
      //       py::arg("yIn"), py::arg("dydxIn"), py::arg("yOut"), py::arg("hstep"), py::arg("yMid"), py::arg("derivs"))

      .def("SetSteps", &G4ModifiedMidpoint::SetSteps, py::arg("steps"))
      .def("GetSteps", &G4ModifiedMidpoint::GetSteps)
      .def("SetEquationOfMotion", &G4ModifiedMidpoint::SetEquationOfMotion, py::arg("equation"))
      .def("GetEquationOfMotion", &G4ModifiedMidpoint::GetEquationOfMotion, py::return_value_policy::reference)
      .def("GetNumberOfVariables", &G4ModifiedMidpoint::GetNumberOfVariables);
}
