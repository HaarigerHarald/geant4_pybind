#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4BoundingEnvelope.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4BoundingEnvelope(py::module &m)
{
   py::class_<G4BoundingEnvelope>(m, "G4BoundingEnvelope")

      .def(py::init<const G4ThreeVector &, const G4ThreeVector &>(), py::arg("pMin"), py::arg("pMax"))
      .def(py::init<
              const std::vector<const std::vector<G4ThreeVector, std::allocator<G4ThreeVector>> *,
                                std::allocator<const std::vector<G4ThreeVector, std::allocator<G4ThreeVector>> *>> &>(),
           py::arg("polygons"))

      .def(py::init<
              const G4ThreeVector &, const G4ThreeVector &,
              const std::vector<const std::vector<G4ThreeVector, std::allocator<G4ThreeVector>> *,
                                std::allocator<const std::vector<G4ThreeVector, std::allocator<G4ThreeVector>> *>> &>(),
           py::arg("pMin"), py::arg("pMax"), py::arg("polygons"))

      .def("__copy__", [](const G4BoundingEnvelope &self) { return G4BoundingEnvelope(self); })
      .def("__deepcopy__", [](const G4BoundingEnvelope &self, py::dict) { return G4BoundingEnvelope(self); })
      .def("BoundingBoxVsVoxelLimits", &G4BoundingEnvelope::BoundingBoxVsVoxelLimits, py::arg("pAxis"),
           py::arg("pVoxelLimits"), py::arg("pTransform3D"), py::arg("pMin"), py::arg("pMax"))

      .def("CalculateExtent", &G4BoundingEnvelope::CalculateExtent, py::arg("pAxis"), py::arg("pVoxelLimits"),
           py::arg("pTransform3D"), py::arg("pMin"), py::arg("pMax"));
}
