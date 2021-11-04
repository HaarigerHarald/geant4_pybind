#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4SmartVoxelStat.hh>
#include <G4LogicalVolume.hh>
#include <G4SmartVoxelHeader.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4SmartVoxelStat(py::module &m)
{
   py::class_<G4SmartVoxelStat>(m, "G4SmartVoxelStat")

      .def(py::init<const G4LogicalVolume *, const G4SmartVoxelHeader *, G4double, G4double>(), py::arg("theVolume"),
           py::arg("theVoxel"), py::arg("theSysTime"), py::arg("theUserTime"))

      .def("__copy__", [](const G4SmartVoxelStat &self) { return G4SmartVoxelStat(self); })
      .def("__deepcopy__", [](const G4SmartVoxelStat &self, py::dict) { return G4SmartVoxelStat(self); })
      .def("GetVolume", &G4SmartVoxelStat::GetVolume, py::return_value_policy::reference)
      .def("GetVoxel", &G4SmartVoxelStat::GetVoxel, py::return_value_policy::reference)
      .def("GetSysTime", &G4SmartVoxelStat::GetSysTime)
      .def("GetUserTime", &G4SmartVoxelStat::GetUserTime)
      .def("GetTotalTime", &G4SmartVoxelStat::GetTotalTime)
      .def("GetNumberHeads", &G4SmartVoxelStat::GetNumberHeads)
      .def("GetNumberNodes", &G4SmartVoxelStat::GetNumberNodes)
      .def("GetNumberPointers", &G4SmartVoxelStat::GetNumberPointers)
      .def("GetMemoryUse", &G4SmartVoxelStat::GetMemoryUse);
}
