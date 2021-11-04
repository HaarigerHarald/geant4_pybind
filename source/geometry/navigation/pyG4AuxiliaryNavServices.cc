#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4AuxiliaryNavServices.hh>
#include <G4VoxelLimits.hh>
#include <G4VPVParameterisation.hh>
#include <G4VPhysicalVolume.hh>
#include <G4VGraphicsScene.hh>
#include <G4Polyhedron.hh>
#include <G4VisExtent.hh>
#include <G4DisplacedSolid.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4AuxiliaryNavServices(py::module &m)
{
   py::class_<G4AuxiliaryNavServices>(m, "G4AuxiliaryNavServices")

      .def(py::init<>())
      .def("__copy__", [](const G4AuxiliaryNavServices &self) { return G4AuxiliaryNavServices(self); })
      .def("__deepcopy__", [](const G4AuxiliaryNavServices &self, py::dict) { return G4AuxiliaryNavServices(self); })
      .def_static("CheckPointOnSurface", &G4AuxiliaryNavServices::CheckPointOnSurface, py::arg("sampleSolid"),
                  py::arg("localPoint"), py::arg("globalDirection"), py::arg("sampleTransform"),
                  py::arg("locatedOnEdge"))

      .def_static("CheckPointExiting", &G4AuxiliaryNavServices::CheckPointExiting, py::arg("sampleSolid"),
                  py::arg("localPoint"), py::arg("globalDirection"), py::arg("sampleTransform"))

      .def_static("ReportTolerances", &G4AuxiliaryNavServices::ReportTolerances);
}
