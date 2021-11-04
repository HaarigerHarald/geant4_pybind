#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/operators.h>

#include <G4SmartVoxelHeader.hh>
#include <G4LogicalVolume.hh>
#include <G4VoxelLimits.hh>
#include <G4VPhysicalVolume.hh>

#include <limits>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4SmartVoxelHeader(py::module &m)
{
   py::class_<G4SmartVoxelHeader>(m, "G4SmartVoxelHeader")

      .def(py::init<G4LogicalVolume *, G4int>(), py::arg("pVolume"), py::arg("pSlice") = 0)
      .def(py::init<G4LogicalVolume *, const G4VoxelLimits &, const G4VolumeNosVector *, G4int>(), py::arg("pVolume"),
           py::arg("pLimits"), py::arg("pCandidates"), py::arg("pSlice") = 0)

      .def("__copy__", [](const G4SmartVoxelHeader &self) { return G4SmartVoxelHeader(self); })
      .def("__deepcopy__", [](const G4SmartVoxelHeader &self, py::dict) { return G4SmartVoxelHeader(self); })
      .def("GetMaxEquivalentSliceNo", &G4SmartVoxelHeader::GetMaxEquivalentSliceNo)
      .def("SetMaxEquivalentSliceNo", &G4SmartVoxelHeader::SetMaxEquivalentSliceNo, py::arg("pMax"))
      .def("GetMinEquivalentSliceNo", &G4SmartVoxelHeader::GetMinEquivalentSliceNo)
      .def("SetMinEquivalentSliceNo", &G4SmartVoxelHeader::SetMinEquivalentSliceNo, py::arg("pMin"))
      .def("GetAxis", &G4SmartVoxelHeader::GetAxis)
      .def("GetParamAxis", &G4SmartVoxelHeader::GetParamAxis)
      .def("GetMaxExtent", &G4SmartVoxelHeader::GetMaxExtent)
      .def("GetMinExtent", &G4SmartVoxelHeader::GetMinExtent)
      .def("GetNoSlices", &G4SmartVoxelHeader::GetNoSlices)
      .def("GetSlice", &G4SmartVoxelHeader::GetSlice, py::arg("n"), py::return_value_policy::reference)
      .def("AllSlicesEqual", &G4SmartVoxelHeader::AllSlicesEqual)
      .def(py::self == py::self)
      .def(
         "__str__",
         [](const G4SmartVoxelHeader &self) {
            std::stringstream ss;
            ss << std::setprecision(std::numeric_limits<G4double>::digits10 + 1) << self;
            return ss.str();
         },
         py::is_operator());
}
