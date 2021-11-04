#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4BulirschStoer.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4BulirschStoer(py::module &m)
{
   py::class_<G4BulirschStoer> mG4BulirschStoer(m, "G4BulirschStoer");

   py::enum_<G4BulirschStoer::step_result>(mG4BulirschStoer, "step_result")
      .value("success", G4BulirschStoer::step_result::success)
      .value("fail", G4BulirschStoer::step_result::fail);

   mG4BulirschStoer
      .def(py::init<G4EquationOfMotion *, G4int, G4double, G4double>(), py::arg("equation"), py::arg("nvar"),
           py::arg("eps_rel"), py::arg("max_dt") = DBL_MAX)

      .def("__copy__", [](const G4BulirschStoer &self) { return G4BulirschStoer(self); })
      .def("__deepcopy__", [](const G4BulirschStoer &self, py::dict) { return G4BulirschStoer(self); })
      .def("set_max_dt", &G4BulirschStoer::set_max_dt, py::arg("max_dt"))
      .def("set_max_relative_error", &G4BulirschStoer::set_max_relative_error, py::arg("eps_rel"))
      .def("try_step", &G4BulirschStoer::try_step, py::arg("in"), py::arg("dxdt"), py::arg("t"), py::arg("out"),
           py::arg("dt"))

      .def("reset", &G4BulirschStoer::reset)
      .def("SetEquationOfMotion", &G4BulirschStoer::SetEquationOfMotion, py::arg("equation"))
      .def("GetEquationOfMotion", &G4BulirschStoer::GetEquationOfMotion, py::return_value_policy::reference)
      .def("GetNumberOfVariables", &G4BulirschStoer::GetNumberOfVariables);
}
