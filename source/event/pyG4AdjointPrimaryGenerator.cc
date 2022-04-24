#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4AdjointPrimaryGenerator.hh>
#include <G4AdjointPosOnPhysVolGenerator.hh>
#include <G4Event.hh>
#include <G4SingleParticleSource.hh>
#include <G4ParticleDefinition.hh>
#include <G4Navigator.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4AdjointPrimaryGenerator(py::module &m)
{
   py::class_<G4AdjointPrimaryGenerator>(m, "G4AdjointPrimaryGenerator")

      .def(py::init<>())
      .def("ComputeAccumulatedDepthVectorAlongBackRay",
           &G4AdjointPrimaryGenerator::ComputeAccumulatedDepthVectorAlongBackRay, py::arg("glob_pos"),
           py::arg("direction"), py::arg("ekin"), py::arg("aPDef"))

      .def("GenerateAdjointPrimaryVertex", &G4AdjointPrimaryGenerator::GenerateAdjointPrimaryVertex, py::arg("anEvt"),
           py::arg("adj_part"), py::arg("E1"), py::arg("E2"))

      .def("GenerateFwdPrimaryVertex", &G4AdjointPrimaryGenerator::GenerateFwdPrimaryVertex, py::arg("anEvt"),
           py::arg("adj_part"), py::arg("E1"), py::arg("E2"))

      .def(
         "SampleDistanceAlongBackRayAndComputeWeightCorrection",
         [](G4AdjointPrimaryGenerator &self, G4double &weight_corr) {
            return std::make_tuple(self.SampleDistanceAlongBackRayAndComputeWeightCorrection(weight_corr), weight_corr);
         },
         py::arg("weight_corr"))

      .def("SetAdjointPrimarySourceOnAnExtSurfaceOfAVolume",
           &G4AdjointPrimaryGenerator::SetAdjointPrimarySourceOnAnExtSurfaceOfAVolume, py::arg("v_name"))

      .def("SetSphericalAdjointPrimarySource", &G4AdjointPrimaryGenerator::SetSphericalAdjointPrimarySource,
           py::arg("radius"), py::arg("pos"))

      ;
}
