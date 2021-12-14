#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4UIcommandTree.hh>
#include <G4UImanager.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4UImanager(py::module &m)
{
   py::class_<G4UImanager, py::nodelete>(m, "G4UImanager", "UI manager class")
      .def_static("GetUIpointer", &G4UImanager::GetUIpointer, py::return_value_policy::reference)

      .def("GetCurrentValues", &G4UImanager::GetCurrentValues)
      .def("ExecuteMacroFile", &G4UImanager::ExecuteMacroFile)
      .def(
         "ApplyCommand", [](G4UImanager &self, const char *command) { self.ApplyCommand(command); },
         py::call_guard<py::gil_scoped_release>())

      .def(
         "ApplyCommand", [](G4UImanager &self, const G4String &command) { self.ApplyCommand(command); },
         py::call_guard<py::gil_scoped_release>())

      .def("CreateHTML", &G4UImanager::CreateHTML, py::arg("dir") = "/")
      .def("SetMacroSearchPath", &G4UImanager::SetMacroSearchPath)
      .def("GetMacroSearchPath", &G4UImanager::GetMacroSearchPath)

      .def("SetPauseAtBeginOfEvent", &G4UImanager::SetPauseAtBeginOfEvent)
      .def("GetPauseAtBeginOfEvent", &G4UImanager::GetPauseAtBeginOfEvent)
      .def("SetPauseAtEndOfEvent", &G4UImanager::SetPauseAtEndOfEvent)
      .def("GetPauseAtEndOfEvent", &G4UImanager::GetPauseAtEndOfEvent)
      .def("SetVerboseLevel", &G4UImanager::SetVerboseLevel)
      .def("GetVerboseLevel", &G4UImanager::GetVerboseLevel)

      .def("GetTree", &G4UImanager::GetTree, py::return_value_policy::reference);
}
