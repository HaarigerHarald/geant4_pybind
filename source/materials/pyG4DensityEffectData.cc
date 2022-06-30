#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4DensityEffectData.hh>
#include <G4DensityEffectCalculator.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4DensityEffectData(py::module &m)
{
   py::class_<G4DensityEffectData>(m, "G4DensityEffectData")

      .def(py::init<>())
      .def("DumpData", &G4DensityEffectData::DumpData)
      .def("GetAdensity", &G4DensityEffectData::GetAdensity, py::arg("idx"))
      .def("GetAdjustmentFactor", &G4DensityEffectData::GetAdjustmentFactor, py::arg("idx"))
      .def("GetCdensity", &G4DensityEffectData::GetCdensity, py::arg("idx"))
      .def("GetDelta0density", &G4DensityEffectData::GetDelta0density, py::arg("idx"))
      .def("GetElementIndex", &G4DensityEffectData::GetElementIndex, py::arg("Z"), py::arg("mState"))
      .def("GetErrorDensity", &G4DensityEffectData::GetErrorDensity, py::arg("idx"))
      .def("GetIndex", &G4DensityEffectData::GetIndex, py::arg("matName"))
      .def("GetMdensity", &G4DensityEffectData::GetMdensity, py::arg("idx"))
      .def("GetMeanIonisationPotential", &G4DensityEffectData::GetMeanIonisationPotential, py::arg("idx"))
      .def("GetPlasmaEnergy", &G4DensityEffectData::GetPlasmaEnergy, py::arg("idx"))
      .def("GetX0density", &G4DensityEffectData::GetX0density, py::arg("idx"))
      .def("GetX1density", &G4DensityEffectData::GetX1density, py::arg("idx"))
      .def("PrintData", &G4DensityEffectData::PrintData, py::arg("matName"));
}
