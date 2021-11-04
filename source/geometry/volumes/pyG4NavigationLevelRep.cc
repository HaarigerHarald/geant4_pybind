#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4NavigationLevelRep.hh>
#include <G4AutoLock.hh>
#include <G4GeomSplitter.hh>
#include <G4LogicalVolume.hh>
#include <G4VPVParameterisation.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4NavigationLevelRep(py::module &m)
{
   py::class_<G4NavigationLevelRep>(m, "G4NavigationLevelRep")

      .def(py::init<G4VPhysicalVolume *, const G4AffineTransform &, EVolume, G4int>(), py::arg("newPtrPhysVol"),
           py::arg("newT"), py::arg("newVolTp"), py::arg("newRepNo") = -1)

      .def(py::init<G4VPhysicalVolume *, const G4AffineTransform &, const G4AffineTransform &, EVolume, G4int>(),
           py::arg("newPtrPhysVol"), py::arg("levelAbove"), py::arg("relativeCurrent"), py::arg("newVolTp"),
           py::arg("newRepNo") = -1)

      .def(py::init<>())
      .def(py::init<G4NavigationLevelRep &>())
      .def("GetPhysicalVolume", &G4NavigationLevelRep::GetPhysicalVolume, py::return_value_policy::reference)
      .def("GetTransformPtr", &G4NavigationLevelRep::GetTransformPtr, py::return_value_policy::reference)
      .def("GetTransform", &G4NavigationLevelRep::GetTransform)
      .def("GetVolumeType", &G4NavigationLevelRep::GetVolumeType)
      .def("GetReplicaNo", &G4NavigationLevelRep::GetReplicaNo)
      .def("AddAReference", &G4NavigationLevelRep::AddAReference)
      .def("RemoveAReference", &G4NavigationLevelRep::RemoveAReference);
}
