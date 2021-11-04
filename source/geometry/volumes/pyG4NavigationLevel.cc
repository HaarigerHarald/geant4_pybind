#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4NavigationLevel.hh>
#include <G4AutoLock.hh>
#include <G4GeomSplitter.hh>
#include <G4LogicalVolume.hh>
#include <G4VPVParameterisation.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4NavigationLevel(py::module &m)
{
   py::class_<G4NavigationLevel>(m, "G4NavigationLevel")

      .def(py::init<G4VPhysicalVolume *, const G4AffineTransform &, EVolume, G4int>(), py::arg("newPtrPhysVol"),
           py::arg("newT"), py::arg("newVolTp"), py::arg("newRepNo") = -1)

      .def(py::init<G4VPhysicalVolume *, const G4AffineTransform &, const G4AffineTransform &, EVolume, G4int>(),
           py::arg("newPtrPhysVol"), py::arg("levelAbove"), py::arg("relativeCurrent"), py::arg("newVolTp"),
           py::arg("newRepNo") = -1)

      .def(py::init<>())
      .def("__copy__", [](const G4NavigationLevel &self) { return G4NavigationLevel(self); })
      .def("__deepcopy__", [](const G4NavigationLevel &self, py::dict) { return G4NavigationLevel(self); })
      .def("GetPhysicalVolume", &G4NavigationLevel::GetPhysicalVolume, py::return_value_policy::reference)
      .def("GetTransform", &G4NavigationLevel::GetTransform)
      .def("GetVolumeType", &G4NavigationLevel::GetVolumeType)
      .def("GetReplicaNo", &G4NavigationLevel::GetReplicaNo)
      .def("GetPtrTransform", &G4NavigationLevel::GetPtrTransform, py::return_value_policy::reference);
}
