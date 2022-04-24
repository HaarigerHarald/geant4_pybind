#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4AdjointPosOnPhysVolGenerator.hh>
#include <G4GeomSplitter.hh>
#include <G4LogicalVolume.hh>
#include <G4VPVParameterisation.hh>
#include <G4VSolid.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4AdjointPosOnPhysVolGenerator(py::module &m)
{
   py::class_<G4AdjointPosOnPhysVolGenerator, py::nodelete>(m, "G4AdjointPosOnPhysVolGenerator")

      .def(
         "__copy__",
         [](const G4AdjointPosOnPhysVolGenerator &self) { return new G4AdjointPosOnPhysVolGenerator(self); },
         py::return_value_policy::reference)

      .def(
         "__deepcopy__",
         [](const G4AdjointPosOnPhysVolGenerator &self, py::dict) { return new G4AdjointPosOnPhysVolGenerator(self); },
         py::return_value_policy::reference)

      .def("ComputeAreaOfExtSurface", py::overload_cast<>(&G4AdjointPosOnPhysVolGenerator::ComputeAreaOfExtSurface))
      .def("ComputeAreaOfExtSurface",
           py::overload_cast<G4int>(&G4AdjointPosOnPhysVolGenerator::ComputeAreaOfExtSurface), py::arg("NStat"))

      .def("ComputeAreaOfExtSurface",
           py::overload_cast<G4double>(&G4AdjointPosOnPhysVolGenerator::ComputeAreaOfExtSurface), py::arg("epsilon"))

      .def("ComputeAreaOfExtSurface",
           py::overload_cast<G4VSolid *>(&G4AdjointPosOnPhysVolGenerator::ComputeAreaOfExtSurface), py::arg("aSolid"))

      .def("ComputeAreaOfExtSurface",
           py::overload_cast<G4VSolid *, G4int>(&G4AdjointPosOnPhysVolGenerator::ComputeAreaOfExtSurface),
           py::arg("aSolid"), py::arg("NStat"))

      .def("ComputeAreaOfExtSurface",
           py::overload_cast<G4VSolid *, G4double>(&G4AdjointPosOnPhysVolGenerator::ComputeAreaOfExtSurface),
           py::arg("aSolid"), py::arg("epsilon"))

      .def("DefinePhysicalVolume", &G4AdjointPosOnPhysVolGenerator::DefinePhysicalVolume, py::arg("aName"),
           py::return_value_policy::reference)

      .def("DefinePhysicalVolume1", &G4AdjointPosOnPhysVolGenerator::DefinePhysicalVolume1, py::arg("aName"))
      .def("GenerateAPositionOnTheExtSurfaceOfASolid",
           &G4AdjointPosOnPhysVolGenerator::GenerateAPositionOnTheExtSurfaceOfASolid, py::arg("aSolid"), py::arg("p"),
           py::arg("direction"))

      .def("GenerateAPositionOnTheExtSurfaceOfThePhysicalVolume",
           py::overload_cast<G4ThreeVector &, G4ThreeVector &>(
              &G4AdjointPosOnPhysVolGenerator::GenerateAPositionOnTheExtSurfaceOfThePhysicalVolume),
           py::arg("p"), py::arg("direction"))

      .def(
         "GenerateAPositionOnTheExtSurfaceOfThePhysicalVolume",
         [](G4AdjointPosOnPhysVolGenerator &self, G4ThreeVector &p, G4ThreeVector &direction,
            G4double &costh_to_normal) {
            self.GenerateAPositionOnTheExtSurfaceOfThePhysicalVolume(p, direction, costh_to_normal);
            return costh_to_normal;
         },
         py::arg("p"), py::arg("direction"), py::arg("costh_to_normal"))

      .def("GenerateAPositionOnTheExtSurfaceOfTheSolid",
           &G4AdjointPosOnPhysVolGenerator::GenerateAPositionOnTheExtSurfaceOfTheSolid, py::arg("p"),
           py::arg("direction"))

      .def("GetAreaOfExtSurfaceOfThePhysicalVolume",
           &G4AdjointPosOnPhysVolGenerator::GetAreaOfExtSurfaceOfThePhysicalVolume)

      .def("GetCosThDirComparedToNormal", &G4AdjointPosOnPhysVolGenerator::GetCosThDirComparedToNormal)
      .def_static("GetInstance", &G4AdjointPosOnPhysVolGenerator::GetInstance, py::return_value_policy::reference)
      .def("SetSolid", &G4AdjointPosOnPhysVolGenerator::SetSolid, py::arg("aSolid"));
}
