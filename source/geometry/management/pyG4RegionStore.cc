#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4RegionStore.hh>
#include <G4Region.hh>
#include <G4VPhysicalVolume.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4RegionStore(py::module &m)
{
   py::class_<G4RegionStore, py::nodelete>(m, "G4RegionStore")

      .def_static("Register", &G4RegionStore::Register, py::arg("pRegion"))
      .def_static("DeRegister", &G4RegionStore::DeRegister, py::arg("pRegion"))
      .def_static("GetInstance", &G4RegionStore::GetInstance, py::return_value_policy::reference)
      .def_static("SetNotifier", &G4RegionStore::SetNotifier, py::arg("pNotifier"))
      .def_static("Clean", &G4RegionStore::Clean)
      .def("IsModified", &G4RegionStore::IsModified)
      .def("ResetRegionModified", &G4RegionStore::ResetRegionModified)
      .def("UpdateMaterialList", &G4RegionStore::UpdateMaterialList,
           py::arg("currentWorld") = static_cast<G4VPhysicalVolume *>(0))

      .def("GetRegion", &G4RegionStore::GetRegion, py::arg("name"), py::arg("verbose") = true,
           py::return_value_policy::reference)

      .def("FindOrCreateRegion", &G4RegionStore::FindOrCreateRegion, py::arg("name"),
           py::return_value_policy::reference)

      .def("SetWorldVolume", &G4RegionStore::SetWorldVolume);
}
