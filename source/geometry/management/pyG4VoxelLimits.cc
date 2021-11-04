#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4VoxelLimits.hh>

#include <limits>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4VoxelLimits(py::module &m)
{
   py::class_<G4VoxelLimits>(m, "G4VoxelLimits")

      .def(py::init<>())
      .def("__copy__", [](const G4VoxelLimits &self) { return G4VoxelLimits(self); })
      .def("__deepcopy__", [](const G4VoxelLimits &self, py::dict) { return G4VoxelLimits(self); })
      .def("AddLimit", &G4VoxelLimits::AddLimit, py::arg("pAxis"), py::arg("pMin"), py::arg("pMax"))
      .def("GetMaxXExtent", &G4VoxelLimits::GetMaxXExtent)
      .def("GetMaxYExtent", &G4VoxelLimits::GetMaxYExtent)
      .def("GetMaxZExtent", &G4VoxelLimits::GetMaxZExtent)
      .def("GetMinXExtent", &G4VoxelLimits::GetMinXExtent)
      .def("GetMinYExtent", &G4VoxelLimits::GetMinYExtent)
      .def("GetMinZExtent", &G4VoxelLimits::GetMinZExtent)
      .def("GetMaxExtent", &G4VoxelLimits::GetMaxExtent, py::arg("pAxis"))
      .def("GetMinExtent", &G4VoxelLimits::GetMinExtent, py::arg("pAxis"))
      .def("IsXLimited", &G4VoxelLimits::IsXLimited)
      .def("IsYLimited", &G4VoxelLimits::IsYLimited)
      .def("IsZLimited", &G4VoxelLimits::IsZLimited)
      .def("IsLimited", py::overload_cast<>(&G4VoxelLimits::IsLimited, py::const_))
      .def("IsLimited", py::overload_cast<const EAxis>(&G4VoxelLimits::IsLimited, py::const_), py::arg("pAxis"))
      .def("ClipToLimits", &G4VoxelLimits::ClipToLimits, py::arg("pStart"), py::arg("pEnd"))
      .def("Inside", &G4VoxelLimits::Inside, py::arg("pVec"))
      .def("OutCode", &G4VoxelLimits::OutCode, py::arg("pVec"))
      .def(
         "__str__",
         [](const G4VoxelLimits &self) {
            std::stringstream ss;
            ss << std::setprecision(std::numeric_limits<G4double>::digits10 + 1) << self;
            return ss.str();
         },
         py::is_operator());
}
