#include <pybind11/pybind11.h>

#include <G4TrackingManager.hh>

#include "typecast.hh"

namespace py = pybind11;

void export_G4TrackingManager(py::module &m)
{
   py::class_<G4TrackingManager, std::unique_ptr<G4TrackingManager>>(m, "G4TrackingManager", "tracking manager class")
      .def(py::init<>())

      // TODO
      .def("GetStoreTrajectory", &G4TrackingManager::GetStoreTrajectory)
      .def("SetStoreTrajectory", &G4TrackingManager::SetStoreTrajectory)
      .def("SetVerboseLevel", &G4TrackingManager::SetVerboseLevel)
      .def("GetVerboseLevel", &G4TrackingManager::GetVerboseLevel)
      .def("SetUserTrackInformation", &G4TrackingManager::SetUserTrackInformation);
}
