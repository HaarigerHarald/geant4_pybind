#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4AccumulableManager.hh>
#include <G4AnalysisManagerState.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4AccumulableManager(py::module &m)
{
   py::class_<G4AccumulableManager, py::nodelete>(m, "G4AccumulableManager")

      .def(
         "__copy__", [](const G4AccumulableManager &self) { return new G4AccumulableManager(self); },
         py::return_value_policy::reference)
      .def(
         "__deepcopy__", [](const G4AccumulableManager &self, py::dict) { return new G4AccumulableManager(self); },
         py::return_value_policy::reference)

      .def("Begin", &G4AccumulableManager::Begin)
      .def("BeginConst", &G4AccumulableManager::BeginConst)
      .def("End", &G4AccumulableManager::End)
      .def("EndConst", &G4AccumulableManager::EndConst)
      .def("GetAccumulable",
           py::overload_cast<const G4String &, G4bool>(&G4AccumulableManager::GetAccumulable<G4double>, py::const_),
           py::arg("name"), py::arg("warn") = true, py::return_value_policy::reference)

      .def("GetAccumulable",
           py::overload_cast<G4int, G4bool>(&G4AccumulableManager::GetAccumulable<G4double>, py::const_), py::arg("id"),
           py::arg("warn") = true, py::return_value_policy::reference)

      .def("GetNofAccumulables", &G4AccumulableManager::GetNofAccumulables)

      .def_static("Instance", &G4AccumulableManager::Instance, py::return_value_policy::reference)

      .def("Merge", &G4AccumulableManager::Merge, py::call_guard<py::gil_scoped_release>())
      .def("RegisterAccumulable", &G4AccumulableManager::RegisterAccumulable<G4double>, py::arg("accumulable"))
      .def("Reset", &G4AccumulableManager::Reset, py::call_guard<py::gil_scoped_release>());
}
