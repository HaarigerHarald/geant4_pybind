#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/operators.h>

#include <G4StatAnalysis.hh>

#include <limits>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4StatAnalysis(py::module &m)
{
   py::class_<G4StatAnalysis>(m, "G4StatAnalysis")
      .def(py::init<>())

      .def("GetMean", &G4StatAnalysis::GetMean)
      .def("GetSum", &G4StatAnalysis::GetSum)
      .def("GetSumSquared", &G4StatAnalysis::GetSumSquared)
      .def("GetSum1", &G4StatAnalysis::GetSum1)
      .def("GetSum2", &G4StatAnalysis::GetSum2)
      .def("GetHits", &G4StatAnalysis::GetHits)
      .def("GetNumNonZero", &G4StatAnalysis::GetNumNonZero)
      .def("GetNumZero", &G4StatAnalysis::GetNumZero)

      .def("SetSum", &G4StatAnalysis::SetSum)
      .def("SetSumSquared", &G4StatAnalysis::SetSumSquared)
      .def("SetSum1", &G4StatAnalysis::SetSum1)
      .def("SetSum2", &G4StatAnalysis::SetSum2)
      .def("SetHits", &G4StatAnalysis::SetHits)
      .def("SetZero", &G4StatAnalysis::SetZero)

      .def("GetFOM", &G4StatAnalysis::GetFOM)
      .def("GetRelativeError", &G4StatAnalysis::GetRelativeError)
      .def("GetStdDev", &G4StatAnalysis::GetStdDev)
      .def("GetVariance", &G4StatAnalysis::GetVariance)
      .def("GetCoeffVariation", &G4StatAnalysis::GetCoeffVariation)
      .def("GetEfficiency", &G4StatAnalysis::GetEfficiency)
      .def("GetR2Int", &G4StatAnalysis::GetR2Int)
      .def("GetR2Eff", &G4StatAnalysis::GetR2Eff)

      .def(
         "__call__", [](const G4StatAnalysis &self) { return self.operator G4double(); }, py::is_operator())

      .def("Reset", &G4StatAnalysis::Reset)
      .def("Add", &G4StatAnalysis::Add, py::arg("_val"), py::arg("_weight") = 1.0)
      .def("Rescale", &G4StatAnalysis::Rescale, py::arg("factor"))

      .def(py::self += G4double())
      .def(py::self /= G4double())
      .def(py::self += py::self)
      .def(py::self -= py::self)

      .def(
         "PrintInfo",
         [](const G4StatAnalysis &self, py::object file, std::string &tab) {
            std::stringstream ss;
            ss.precision(std::numeric_limits<G4double>::digits10 + 1);
            self.PrintInfo(ss, tab);
            py::print(ss, file = file);
         },
         py::arg("file"), py::arg("tab") = "")

      .def("GetCpuTime", &G4StatAnalysis::GetCpuTime)
      .def_static("GetCpuClock", &G4StatAnalysis::GetCpuClock)
      .def_static("ResetCpuClock", &G4StatAnalysis::ResetCpuClock)

      .def(py::self + py::self)
      .def(py::self - py::self)

      .def(
         "__str__",
         [](const G4StatAnalysis &self) {
            std::stringstream ss;
            ss << std::setprecision(std::numeric_limits<G4double>::digits10 + 1) << self;
            return ss.str();
         },
         py::is_operator());

   // py::implicitly_convertible<G4StatAnalysis, G4double>();
}
