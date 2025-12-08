#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4VTouchable.hh>
#include <G4VPhysicalVolume.hh>
#include <G4VSolid.hh>
#include <G4NavigationHistory.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4VTouchable(py::module &m)
{
   py::class_<G4VTouchable>(m, "G4VTouchable")

      .def(py::init<>())
      .def("__copy__", [](const G4VTouchable &self) { return G4VTouchable(self); })
      .def("__deepcopy__", [](const G4VTouchable &self, py::dict) { return G4VTouchable(self); })
      .def("GetTranslation", &G4VTouchable::GetTranslation, py::arg("depth") = 0)
      .def("GetRotation", &G4VTouchable::GetRotation, py::arg("depth") = 0, py::return_value_policy::reference)
      .def("GetVolume", &G4VTouchable::GetVolume, py::arg("depth") = 0, py::return_value_policy::reference)
      .def("GetSolid", &G4VTouchable::GetSolid, py::arg("depth") = 0, py::return_value_policy::reference)
      .def("GetReplicaNumber", &G4VTouchable::GetReplicaNumber, py::arg("depth") = 0)
      .def("GetCopyNumber", &G4VTouchable::GetCopyNumber, py::arg("depth") = 0)
      .def("GetHistoryDepth", &G4VTouchable::GetHistoryDepth)
      .def("MoveUpHistory", &G4VTouchable::MoveUpHistory, py::arg("num_levels") = 1)
      .def("UpdateYourself", &G4VTouchable::UpdateYourself, py::arg("pPhysVol"),
           py::arg("history") = static_cast<const G4NavigationHistory *>(nullptr))

      .def("GetHistory", &G4VTouchable::GetHistory, py::return_value_policy::reference);
}
