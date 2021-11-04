#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4TrialsCounter.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4TrialsCounter(py::module &m)
{
   py::class_<G4TrialsCounter>(m, "G4TrialsCounter")

      .def(py::init<const G4String &, const G4String &, G4bool>(), py::arg("nameStats"), py::arg("description"),
           py::arg("printOnExit") = false)

      .def("__copy__", [](const G4TrialsCounter &self) { return G4TrialsCounter(self); })
      .def("__deepcopy__", [](const G4TrialsCounter &self, py::dict) { return G4TrialsCounter(self); })
      .def("AccumulateCounts", &G4TrialsCounter::AccumulateCounts, py::arg("noTrials"))
      .def("ClearCounts", &G4TrialsCounter::ClearCounts)
      .def("ReturnTotals", &G4TrialsCounter::ReturnTotals, py::arg("calls"), py::arg("maxTrials"), py::arg("numMaxT"))
      .def("PrintStatistics", &G4TrialsCounter::PrintStatistics);
}
