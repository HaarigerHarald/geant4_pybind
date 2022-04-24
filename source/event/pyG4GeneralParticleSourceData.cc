#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4GeneralParticleSourceData.hh>
#include <G4Event.hh>
#include <G4ProcessManager.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4GeneralParticleSourceData(py::module &m)
{
   py::class_<G4GeneralParticleSourceData, py::nodelete>(m, "G4GeneralParticleSourceData")

      .def("AddASource", &G4GeneralParticleSourceData::AddASource, py::arg("intensity"))
      .def("ClearSources", &G4GeneralParticleSourceData::ClearSources)
      .def("DeleteASource", &G4GeneralParticleSourceData::DeleteASource, py::arg("idx"))
      .def("GetCurrentSource", py::overload_cast<G4int>(&G4GeneralParticleSourceData::GetCurrentSource), py::arg("idx"),
           py::return_value_policy::reference)

      .def("GetCurrentSource", py::overload_cast<>(&G4GeneralParticleSourceData::GetCurrentSource, py::const_),
           py::return_value_policy::reference)

      .def("GetCurrentSourceIdx", &G4GeneralParticleSourceData::GetCurrentSourceIdx)
      .def("GetFlatSampling", &G4GeneralParticleSourceData::GetFlatSampling)
      .def("GetIntensity", &G4GeneralParticleSourceData::GetIntensity, py::arg("idx"))
      .def("GetIntensityVectorSize", &G4GeneralParticleSourceData::GetIntensityVectorSize)
      .def("GetMultipleVertex", &G4GeneralParticleSourceData::GetMultipleVertex)
      .def("GetSourceProbability", &G4GeneralParticleSourceData::GetSourceProbability, py::arg("idx"))
      .def("GetSourceVectorSize", &G4GeneralParticleSourceData::GetSourceVectorSize)
      .def_static("Instance", &G4GeneralParticleSourceData::Instance, py::return_value_policy::reference)
      .def("IntensityNormalise", &G4GeneralParticleSourceData::IntensityNormalise)
      .def("Lock", &G4GeneralParticleSourceData::Lock)
      .def("Normalised", &G4GeneralParticleSourceData::Normalised)
      .def("SetCurrentSourceIntensity", &G4GeneralParticleSourceData::SetCurrentSourceIntensity)
      .def("SetFlatSampling", &G4GeneralParticleSourceData::SetFlatSampling, py::arg("fSamp"))
      .def("SetMultipleVertex", &G4GeneralParticleSourceData::SetMultipleVertex, py::arg("flag"))
      .def("SetVerbosityAllSources", &G4GeneralParticleSourceData::SetVerbosityAllSources, py::arg("vl"))
      .def("Unlock", &G4GeneralParticleSourceData::Unlock);
}
