#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4FieldManagerStore.hh>
#include <G4Field.hh>
#include <G4MagneticField.hh>
#include <G4ChordFinder.hh>
#include <G4Track.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4FieldManagerStore(py::module &m)
{
   py::class_<G4FieldManagerStore, py::nodelete>(m, "G4FieldManagerStore")

      .def("__copy__", [](const G4FieldManagerStore &self) { return G4FieldManagerStore(self); })
      .def("__deepcopy__", [](const G4FieldManagerStore &self, py::dict) { return G4FieldManagerStore(self); })
      .def_static("Register", &G4FieldManagerStore::Register, py::arg("pVolume"))
      .def_static("DeRegister", &G4FieldManagerStore::DeRegister, py::arg("pVolume"))
      .def_static("GetInstance", &G4FieldManagerStore::GetInstance, py::return_value_policy::reference)
      .def_static("GetInstanceIfExist", &G4FieldManagerStore::GetInstanceIfExist, py::return_value_policy::reference)
      .def_static("Clean", &G4FieldManagerStore::Clean)
      .def("ClearAllChordFindersState", &G4FieldManagerStore::ClearAllChordFindersState);
}
