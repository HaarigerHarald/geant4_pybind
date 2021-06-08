#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4ChordFinder.hh>
#include <G4Field.hh>
#include <G4FieldManager.hh>
#include <G4MagneticField.hh>
#include <G4Track.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4FieldManager(py::module &m)
{
   py::class_<G4FieldManager>(m, "G4FieldManager", "field manager class")

      .def(py::init<>())
      .def(py::init<G4Field *>())
      .def(py::init<G4Field *, G4ChordFinder *>())
      .def(py::init<G4Field *, G4ChordFinder *, G4bool>())
      .def(py::init<G4MagneticField *>())

      .def("SetDetectorField", &G4FieldManager::SetDetectorField, py::arg("detectorField"), py::arg("failMode") = 0)
      .def("GetDetectorField", &G4FieldManager::GetDetectorField, py::return_value_policy::reference_internal)
      .def("DoesFieldExist", &G4FieldManager::DoesFieldExist)
      .def("CreateChordFinder", &G4FieldManager::CreateChordFinder)
      .def("SetChordFinder", &G4FieldManager::SetChordFinder)
      .def("GetChordFinder", py::overload_cast<>(&G4FieldManager::GetChordFinder),
           py::return_value_policy::reference_internal)

      .def("GetChordFinder", py::overload_cast<>(&G4FieldManager::GetChordFinder, py::const_),
           py::return_value_policy::reference_internal)

      .def("ConfigureForTrack", &G4FieldManager::ConfigureForTrack)
      .def("GetDeltaIntersection", &G4FieldManager::GetDeltaIntersection)
      .def("GetDeltaOneStep", &G4FieldManager::GetDeltaOneStep)
      .def("SetAccuraciesWithDeltaOneStep", &G4FieldManager::SetAccuraciesWithDeltaOneStep)
      .def("SetDeltaOneStep", &G4FieldManager::SetDeltaOneStep)
      .def("SetDeltaIntersection", &G4FieldManager::SetDeltaIntersection)
      .def("GetMinimumEpsilonStep", &G4FieldManager::GetMinimumEpsilonStep)
      .def("SetMinimumEpsilonStep", &G4FieldManager::SetMinimumEpsilonStep)
      .def("GetMaximumEpsilonStep", &G4FieldManager::GetMaximumEpsilonStep)
      .def("SetMaximumEpsilonStep", &G4FieldManager::SetMaximumEpsilonStep)
      .def("DoesFieldChangeEnergy", &G4FieldManager::DoesFieldChangeEnergy)
      .def("SetFieldChangesEnergy", &G4FieldManager::SetFieldChangesEnergy);
}
