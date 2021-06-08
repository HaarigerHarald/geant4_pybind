#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4SDManager.hh>
#include <G4MultiFunctionalDetector.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4SDManager(py::module &m)
{
   py::class_<G4SDManager, py::nodelete>(m, "G4SDManager")
      .def_static("GetSDMpointer", &G4SDManager::GetSDMpointer, py::return_value_policy::reference)
      .def_static("GetSDMpointerIfExist", &G4SDManager::GetSDMpointerIfExist, py::return_value_policy::reference)

      .def("AddNewDetector",
           [](G4SDManager &self, py::disown_ptr<G4MultiFunctionalDetector> aMD) { self.AddNewDetector(aMD); })

      .def("AddNewDetector",
           [](G4SDManager &self, py::disown_ptr<G4VSensitiveDetector> aSD) { self.AddNewDetector(aSD); })

      .def("Activate", &G4SDManager::Activate)
      .def("GetCollectionID", py::overload_cast<G4String>(&G4SDManager::GetCollectionID))
      .def("GetCollectionID", py::overload_cast<G4VHitsCollection *>(&G4SDManager::GetCollectionID))

      .def("FindSensitiveDetector", &G4SDManager::FindSensitiveDetector, py::arg("dName"), py::arg("warning") = true,
           py::return_value_policy::reference)

      .def("TerminateCurrentEvent", &G4SDManager::PrepareNewEvent, py::return_value_policy::reference)
      .def("TerminateCurrentEvent", &G4SDManager::TerminateCurrentEvent)
      .def("AddNewCollection", &G4SDManager::AddNewCollection)

      .def("SetVerboseLevel", &G4SDManager::SetVerboseLevel)
      .def("GetTreeTop", &G4SDManager::GetTreeTop, py::return_value_policy::reference)
      .def("ListTree", &G4SDManager::ListTree)
      .def("GetHCtable", &G4SDManager::GetHCtable, py::return_value_policy::reference)

      .def("RegisterSDFilter", &G4SDManager::RegisterSDFilter) // TODO pass ownership
      .def("DeRegisterSDFilter", &G4SDManager::DeRegisterSDFilter);
}
