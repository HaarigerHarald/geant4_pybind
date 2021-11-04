#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4NavigationHistory.hh>
#include <G4AutoLock.hh>
#include <G4GeomSplitter.hh>
#include <G4LogicalVolume.hh>
#include <G4VPVParameterisation.hh>

#include <limits>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4NavigationHistory(py::module &m)
{
   py::class_<G4NavigationHistory>(m, "G4NavigationHistory")

      .def(py::init<>())
      .def("__copy__", [](const G4NavigationHistory &self) { return G4NavigationHistory(self); })
      .def("__deepcopy__", [](const G4NavigationHistory &self, py::dict) { return G4NavigationHistory(self); })
      .def("Reset", &G4NavigationHistory::Reset)
      .def("Clear", &G4NavigationHistory::Clear)
      .def("SetFirstEntry", &G4NavigationHistory::SetFirstEntry, py::arg("pVol"))
      .def("GetTopTransform", &G4NavigationHistory::GetTopTransform)
      .def("GetPtrTopTransform", &G4NavigationHistory::GetPtrTopTransform, py::return_value_policy::reference)
      .def("GetTopReplicaNo", &G4NavigationHistory::GetTopReplicaNo)
      .def("GetTopVolumeType", &G4NavigationHistory::GetTopVolumeType)
      .def("GetTopVolume", &G4NavigationHistory::GetTopVolume, py::return_value_policy::reference)
      .def("GetDepth", &G4NavigationHistory::GetDepth)
      .def("GetMaxDepth", &G4NavigationHistory::GetMaxDepth)
      .def("GetTransform", &G4NavigationHistory::GetTransform, py::arg("n"))
      .def("GetReplicaNo", &G4NavigationHistory::GetReplicaNo, py::arg("n"))
      .def("GetVolumeType", &G4NavigationHistory::GetVolumeType, py::arg("n"))
      .def("GetVolume", &G4NavigationHistory::GetVolume, py::arg("n"), py::return_value_policy::reference)
      .def("NewLevel", &G4NavigationHistory::NewLevel, py::arg("pNewMother"), py::arg("vType") = kNormal,
           py::arg("nReplica") = -1)

      .def("BackLevel", py::overload_cast<>(&G4NavigationHistory::BackLevel))
      .def("BackLevel", py::overload_cast<G4int>(&G4NavigationHistory::BackLevel), py::arg("n"))
      .def(
         "__str__",
         [](const G4NavigationHistory &self) {
            std::stringstream ss;
            ss << std::setprecision(std::numeric_limits<G4double>::digits10 + 1) << self;
            return ss.str();
         },
         py::is_operator());
}
