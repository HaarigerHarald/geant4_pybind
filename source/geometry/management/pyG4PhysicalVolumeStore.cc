#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4PhysicalVolumeStore.hh>
#include <G4AutoLock.hh>
#include <G4GeomSplitter.hh>
#include <G4LogicalVolume.hh>
#include <G4VPVParameterisation.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4PhysicalVolumeStore(py::module &m)
{
   py::class_<G4PhysicalVolumeStore, py::nodelete>(m, "G4PhysicalVolumeStore")

      .def_static("Register", &G4PhysicalVolumeStore::Register, py::arg("pSolid"))
      .def_static("DeRegister", &G4PhysicalVolumeStore::DeRegister, py::arg("pSolid"))
      .def_static("GetInstance", &G4PhysicalVolumeStore::GetInstance, py::return_value_policy::reference)
      .def_static("SetNotifier", &G4PhysicalVolumeStore::SetNotifier, py::arg("pNotifier"))
      .def_static("Clean", &G4PhysicalVolumeStore::Clean)
      .def("GetVolume", &G4PhysicalVolumeStore::GetVolume, py::arg("name"), py::arg("verbose") = true,
           py::return_value_policy::reference);
}
