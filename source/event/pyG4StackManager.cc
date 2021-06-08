//#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4StackManager.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4StackManager(py::module &m)
{
   py::class_<G4StackManager>(m, "G4StackManager", "stack management class")
      .def(py::init<>())

      // TODO
      .def("ReClassify", &G4StackManager::ReClassify)
      .def("clear", &G4StackManager::clear)
      .def("ClearUrgentStack", &G4StackManager::ClearUrgentStack)
      .def("ClearWaitingStack", &G4StackManager::ClearWaitingStack, py::arg("i") = 0)
      .def("ClearPostponeStack", &G4StackManager::ClearPostponeStack)
      .def("GetNTotalTrack", &G4StackManager::GetNTotalTrack)
      .def("GetNUrgentTrack", &G4StackManager::GetNUrgentTrack)
      .def("GetNWaitingTrack", &G4StackManager::GetNWaitingTrack, py::arg("i") = 0)
      .def("SetVerboseLevel", &G4StackManager::SetVerboseLevel);
}
