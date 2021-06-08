#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4UIcommandTree.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4UIcommandTree(py::module &m)
{
   py::class_<G4UIcommandTree>(m, "G4UIcommandTree", "UI command tree")

      .def(py::init<const char *>())

      .def("FindPath", &G4UIcommandTree::FindPath, py::return_value_policy::reference)
      .def("List", &G4UIcommandTree::List)
      .def("ListCurrent", &G4UIcommandTree::ListCurrent)
      .def("ListCurrentWithNum", &G4UIcommandTree::ListCurrentWithNum)
      .def("CreateHTML", &G4UIcommandTree::CreateHTML)
      .def("GetGuidance", &G4UIcommandTree::GetGuidance, py::return_value_policy::reference)
      .def("GetPathName", &G4UIcommandTree::GetPathName)

      .def("GetTreeEntry", &G4UIcommandTree::GetTreeEntry)
      .def("GetCommandEntry", &G4UIcommandTree::GetCommandEntry)
      .def("GetTree", py::overload_cast<G4int>(&G4UIcommandTree::GetTree), py::return_value_policy::reference)
      .def("GetTree", py::overload_cast<const char *>(&G4UIcommandTree::GetTree), py::return_value_policy::reference)
      .def("GetCommand", &G4UIcommandTree::GetCommand, py::return_value_policy::reference)

      .def("GetTitle", &G4UIcommandTree::GetTitle);
}
