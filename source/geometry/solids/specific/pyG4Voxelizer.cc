#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/operators.h>

#include <G4Voxelizer.hh>
#include <G4AffineTransform.hh>
#include <G4VoxelLimits.hh>
#include <G4VPVParameterisation.hh>
#include <G4VPhysicalVolume.hh>
#include <G4VGraphicsScene.hh>
#include <G4VisExtent.hh>
#include <G4DisplacedSolid.hh>
#include <G4VisAttributes.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4Voxelizer(py::module &m)
{
   py::class_<G4VoxelBox>(m, "G4VoxelBox")

      .def("__copy__", [](const G4VoxelBox &self) { return G4VoxelBox(self); })
      .def("__deepcopy__", [](const G4VoxelBox &self, py::dict) { return G4VoxelBox(self); })
      .def(py::init<>())
      .def_readwrite("hlen", &G4VoxelBox::hlen)
      .def_readwrite("pos", &G4VoxelBox::pos);

   py::class_<G4VoxelInfo>(m, "G4VoxelInfo")

      .def(py::init<>())
      .def("__copy__", [](const G4VoxelInfo &self) { return G4VoxelInfo(self); })
      .def("__deepcopy__", [](const G4VoxelInfo &self, py::dict) { return G4VoxelInfo(self); })
      .def_readwrite("count", &G4VoxelInfo::count)
      .def_readwrite("previous", &G4VoxelInfo::previous)
      .def_readwrite("next", &G4VoxelInfo::next);

   py::class_<G4Voxelizer>(m, "G4Voxelizer")

      .def(py::init<>())
      .def("__copy__", [](const G4Voxelizer &self) { return G4Voxelizer(self); })
      .def("__deepcopy__", [](const G4Voxelizer &self, py::dict) { return G4Voxelizer(self); })
      //.def_static("BinarySearch", &G4Voxelizer::BinarySearch, py::arg("vec"), py::arg("value"))
      .def("Voxelize",
           py::overload_cast<std::vector<G4VSolid *, std::allocator<G4VSolid *>> &,
                             std::vector<HepGeom::Transform3D, std::allocator<HepGeom::Transform3D>> &>(
              &G4Voxelizer::Voxelize),
           py::arg("solids"), py::arg("transforms"))

      .def("Voxelize", py::overload_cast<std::vector<G4VFacet *, std::allocator<G4VFacet *>> &>(&G4Voxelizer::Voxelize),
           py::arg("facets"))

      .def("DisplayVoxelLimits", &G4Voxelizer::DisplayVoxelLimits)
      .def("DisplayBoundaries", py::overload_cast<>(&G4Voxelizer::DisplayBoundaries))
      .def("DisplayListNodes", &G4Voxelizer::DisplayListNodes)
      .def("GetCandidatesVoxel", &G4Voxelizer::GetCandidatesVoxel, py::arg("voxels"))
      .def("GetCandidatesVoxelArray",
           py::overload_cast<const G4ThreeVector &, std::vector<int, std::allocator<int>> &, G4SurfBits *>(
              &G4Voxelizer::GetCandidatesVoxelArray, py::const_),
           py::arg("point"), py::arg("list"), py::arg("crossed") = static_cast<G4SurfBits *>(nullptr))

      .def("GetCandidatesVoxelArray",
           py::overload_cast<const std::vector<int, std::allocator<int>> &, const G4SurfBits *,
                             std::vector<int, std::allocator<int>> &, G4SurfBits *>(
              &G4Voxelizer::GetCandidatesVoxelArray, py::const_),
           py::arg("voxels"), py::arg("bitmasks"), py::arg("list"),
           py::arg("crossed") = static_cast<G4SurfBits *>(nullptr))

      .def("GetCandidatesVoxelArray",
           py::overload_cast<const std::vector<int, std::allocator<int>> &, std::vector<int, std::allocator<int>> &,
                             G4SurfBits *>(&G4Voxelizer::GetCandidatesVoxelArray, py::const_),
           py::arg("voxels"), py::arg("list"), py::arg("crossed") = static_cast<G4SurfBits *>(nullptr))

      .def("GetBoxes", &G4Voxelizer::GetBoxes)
      .def("GetBoundary", &G4Voxelizer::GetBoundary, py::arg("index"))
      .def("UpdateCurrentVoxel", &G4Voxelizer::UpdateCurrentVoxel, py::arg("point"), py::arg("direction"),
           py::arg("curVoxel"))

      .def("GetVoxel", &G4Voxelizer::GetVoxel, py::arg("curVoxel"), py::arg("point"))
      .def("GetBitsPerSlice", &G4Voxelizer::GetBitsPerSlice)
      .def("Contains", &G4Voxelizer::Contains, py::arg("point"))
      .def("DistanceToNext", &G4Voxelizer::DistanceToNext, py::arg("point"), py::arg("direction"), py::arg("curVoxel"))

      .def("DistanceToFirst", &G4Voxelizer::DistanceToFirst, py::arg("point"), py::arg("direction"))
      .def("DistanceToBoundingBox", &G4Voxelizer::DistanceToBoundingBox, py::arg("point"))
      .def("GetVoxelsIndex", py::overload_cast<G4int, G4int, G4int>(&G4Voxelizer::GetVoxelsIndex, py::const_),
           py::arg("x"), py::arg("y"), py::arg("z"))

      .def("GetVoxelsIndex",
           py::overload_cast<const std::vector<int, std::allocator<int>> &>(&G4Voxelizer::GetVoxelsIndex, py::const_),
           py::arg("voxels"))

      .def("GetPointVoxel", &G4Voxelizer::GetPointVoxel, py::arg("p"), py::arg("voxels"))
      .def("GetPointIndex", &G4Voxelizer::GetPointIndex, py::arg("p"))
      .def("Empty", &G4Voxelizer::Empty)
      .def("IsEmpty", &G4Voxelizer::IsEmpty, py::arg("index"))
      .def("SetMaxVoxels", py::overload_cast<G4int>(&G4Voxelizer::SetMaxVoxels), py::arg("max"))
      .def("SetMaxVoxels", py::overload_cast<const G4ThreeVector &>(&G4Voxelizer::SetMaxVoxels),
           py::arg("reductionRatio"))

      .def("GetMaxVoxels", &G4Voxelizer::GetMaxVoxels, py::arg("ratioOfReduction"))
      .def("AllocatedMemory", &G4Voxelizer::AllocatedMemory)
      .def("GetCountOfVoxels", &G4Voxelizer::GetCountOfVoxels)
      .def("CountVoxels", &G4Voxelizer::CountVoxels, py::arg("boundaries"))
      .def("GetCandidates", &G4Voxelizer::GetCandidates, py::arg("curVoxel"))
      .def("GetVoxelBoxesSize", &G4Voxelizer::GetVoxelBoxesSize)
      .def("GetVoxelBox", &G4Voxelizer::GetVoxelBox, py::arg("i"))
      .def("GetVoxelBoxCandidates", &G4Voxelizer::GetVoxelBoxCandidates, py::arg("i"))
      .def("GetTotalCandidates", &G4Voxelizer::GetTotalCandidates)
      .def_static("MinDistanceToBox", &G4Voxelizer::MinDistanceToBox, py::arg("aPoint"), py::arg("f"))
      .def_static("SetDefaultVoxelsCount", &G4Voxelizer::SetDefaultVoxelsCount, py::arg("count"))
      .def_static("GetDefaultVoxelsCount", &G4Voxelizer::GetDefaultVoxelsCount);
}
