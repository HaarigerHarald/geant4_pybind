#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4StateManager.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4StateManager(py::module &m)
{
   py::class_<G4StateManager, py::nodelete>(m, "G4StateManager", "state manager")
      .def_static("GetStateManager", &G4StateManager::GetStateManager, "Get an instance of G4StateManager",
                  py::return_value_policy::reference)

      .def("GetCurrentState", &G4StateManager::GetCurrentState)
      .def("GetPreviousState", &G4StateManager::GetPreviousState)
      .def("GetStateString", &G4StateManager::GetStateString);
}
