#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4FieldManager.hh>
#include <G4PropagatorInField.hh>
#include <G4TransportationManager.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4TransportationManager(py::module &m)
{
   py::class_<G4TransportationManager, std::unique_ptr<G4TransportationManager, py::nodelete>>(
      m, "G4TransportationManager", "manager class for transportation")

      .def_static("GetTransportationManager", &G4TransportationManager::GetTransportationManager,
                  py::return_value_policy::reference)

      .def("GetNavigatorForTracking", &G4TransportationManager::GetNavigatorForTracking,
           py::return_value_policy::reference)

      .def("GetPropagatorInField", &G4TransportationManager::GetPropagatorInField, py::return_value_policy::reference)
      .def("GetFieldManager", &G4TransportationManager::GetFieldManager, py::return_value_policy::reference)
      .def("SetNavigatorForTracking", &G4TransportationManager::SetNavigatorForTracking)
      .def("SetPropagatorInField", &G4TransportationManager::SetPropagatorInField)
      .def("SetFieldManager", &G4TransportationManager::SetFieldManager);
}
