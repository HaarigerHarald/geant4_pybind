#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4LogicalVolumeStore.hh>
#include <G4AutoLock.hh>
#include <G4GeomSplitter.hh>
#include <G4ProductionCuts.hh>
#include <G4Material.hh>
#include <G4VUserRegionInformation.hh>
#include <G4MaterialCutsCouple.hh>
#include <G4UserLimits.hh>
#include <G4FieldManager.hh>
#include <G4FastSimulationManager.hh>
#include <G4UserSteppingAction.hh>
#include <G4VPVParameterisation.hh>
#include <G4VSensitiveDetector.hh>
#include <G4VSolid.hh>
#include <G4SmartVoxelHeader.hh>
#include <G4VisAttributes.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4LogicalVolumeStore(py::module &m)
{
   py::class_<G4LogicalVolumeStore, py::nodelete>(m, "G4LogicalVolumeStore")

      .def_static("Register", &G4LogicalVolumeStore::Register, py::arg("pVolume"))
      .def_static("DeRegister", &G4LogicalVolumeStore::DeRegister, py::arg("pVolume"))
      .def_static("GetInstance", &G4LogicalVolumeStore::GetInstance, py::return_value_policy::reference)
      .def_static("SetNotifier", &G4LogicalVolumeStore::SetNotifier, py::arg("pNotifier"))
      .def_static("Clean", &G4LogicalVolumeStore::Clean)
      .def("GetVolume", &G4LogicalVolumeStore::GetVolume, py::arg("name"), py::arg("verbose") = true,
           py::return_value_policy::reference);
}
