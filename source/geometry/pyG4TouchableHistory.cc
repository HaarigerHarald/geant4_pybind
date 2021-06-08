#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4TouchableHistory.hh>
#include <G4VSolid.hh>
#include <G4VPhysicalVolume.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4TouchableHistory(py::module &m)
{
   py::class_<G4TouchableHistory, G4VTouchable>(m, "G4TouchableHistory", "touchable history class")
      .def(py::init<>())
      .def(py::init<const G4NavigationHistory &>())

      .def("GetVolume", &G4TouchableHistory::GetVolume, py::arg("depth") = 0, py::return_value_policy::reference)
      .def("GetSolid", &G4TouchableHistory::GetSolid, py::arg("depth") = 0, py::return_value_policy::reference)
      .def("GetTranslation", &G4TouchableHistory::GetTranslation, py::arg("depth") = 0)
      .def("GetRotation", &G4TouchableHistory::GetRotation, py::arg("depth") = 0, py::return_value_policy::reference)

      .def("GetReplicaNumber", &G4TouchableHistory::GetReplicaNumber, py::arg("depth") = 0)
      .def("GetHistoryDepth", &G4TouchableHistory::GetHistoryDepth)
      .def("MoveUpHistory", &G4TouchableHistory::MoveUpHistory, py::arg("num_levels") = 1)

      // .def("UpdateYourself", &G4TouchableHistory::UpdateYourself, py::arg("pPhysVol"),
      //      py::arg("history") = static_cast<const G4NavigationHistory *>(nullptr), py::keep_alive<1, 2>())

      .def("GetHistory", &G4TouchableHistory::GetHistory, py::return_value_policy::reference_internal);
}
