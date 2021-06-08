#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4EmCalculator.hh>
#include <G4Region.hh>
#include <G4Material.hh>
#include <G4Element.hh>
#include <G4ParticleDefinition.hh>
#include <G4MaterialCutsCouple.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4EmCalculator(py::module &m)
{
   py::class_<G4EmCalculator>(m, "G4EmCalculator", "Provide access to dE/dx and cross section")
      .def(py::init<>())

      .def("GetDEDX",
           py::overload_cast<G4double, const G4ParticleDefinition *, const G4Material *, const G4Region *>(
              &G4EmCalculator::GetDEDX),
           py::arg("kinEnergy"), py::arg("particle"), py::arg("material"),
           py::arg("region") = static_cast<const G4Region *>(nullptr))

      .def("GetDEDX",
           py::overload_cast<G4double, const G4String &, const G4String &, const G4String &>(&G4EmCalculator::GetDEDX),
           py::arg("kinEnergy"), py::arg("particle"), py::arg("material"), py::arg("region") = "world")

      .def("GetRange",
           py::overload_cast<G4double, const G4ParticleDefinition *, const G4Material *, const G4Region *>(
              &G4EmCalculator::GetRange),
           py::arg("kinEnergy"), py::arg("particle"), py::arg("material"),
           py::arg("region") = static_cast<const G4Region *>(nullptr))

      .def("GetRange",
           py::overload_cast<G4double, const G4String &, const G4String &, const G4String &>(&G4EmCalculator::GetRange),
           py::arg("kinEnergy"), py::arg("particle"), py::arg("material"), py::arg("region") = "world")

      .def("GetKinEnergy",
           py::overload_cast<G4double, const G4ParticleDefinition *, const G4Material *, const G4Region *>(
              &G4EmCalculator::GetKinEnergy),
           py::arg("kinEnergy"), py::arg("particle"), py::arg("material"),
           py::arg("region") = static_cast<const G4Region *>(nullptr))

      .def("GetKinEnergy",
           py::overload_cast<G4double, const G4String &, const G4String &, const G4String &>(
              &G4EmCalculator::GetKinEnergy),
           py::arg("kinEnergy"), py::arg("particle"), py::arg("material"), py::arg("region") = "world")

      .def("GetCrossSectionPerVolume",
           py::overload_cast<G4double, const G4ParticleDefinition *, const G4String &, const G4Material *,
                             const G4Region *>(&G4EmCalculator::GetCrossSectionPerVolume),
           py::arg("kinEnergy"), py::arg("particle"), py::arg("processName"), py::arg("material"),
           py::arg("region") = static_cast<const G4Region *>(nullptr))

      .def("GetCrossSectionPerVolume",
           py::overload_cast<G4double, const G4String &, const G4String &, const G4String &, const G4String &>(
              &G4EmCalculator::GetCrossSectionPerVolume),
           py::arg("kinEnergy"), py::arg("particle"), py::arg("processName"), py::arg("material"),
           py::arg("region") = "world")

      .def("GetMeanFreePath",
           py::overload_cast<G4double, const G4ParticleDefinition *, const G4String &, const G4Material *,
                             const G4Region *>(&G4EmCalculator::GetMeanFreePath),
           py::arg("kinEnergy"), py::arg("particle"), py::arg("processName"), py::arg("material"),
           py::arg("region") = static_cast<const G4Region *>(nullptr))

      .def("GetMeanFreePath",
           py::overload_cast<G4double, const G4String &, const G4String &, const G4String &, const G4String &>(
              &G4EmCalculator::GetMeanFreePath),
           py::arg("kinEnergy"), py::arg("particle"), py::arg("processName"), py::arg("material"),
           py::arg("region") = "world")

      .def("PrintDEDXTable", &G4EmCalculator::PrintDEDXTable)
      .def("PrintRangeTable", &G4EmCalculator::PrintRangeTable)
      .def("PrintInverseRangeTable", &G4EmCalculator::PrintInverseRangeTable)

      .def("ComputeDEDX",
           py::overload_cast<G4double, const G4ParticleDefinition *, const G4String &, const G4Material *, G4double>(
              &G4EmCalculator::ComputeDEDX),
           py::arg("kinEnergy"), py::arg("particle"), py::arg("processName"), py::arg("material"),
           py::arg("cut") = DBL_MAX)

      .def("ComputeDEDX",
           py::overload_cast<G4double, const G4String &, const G4String &, const G4String &, G4double>(
              &G4EmCalculator::ComputeDEDX),
           py::arg("kinEnergy"), py::arg("particle"), py::arg("processName"), py::arg("material"),
           py::arg("cut") = DBL_MAX)

      .def("ComputeNuclearDEDX", py::overload_cast<G4double, const G4ParticleDefinition *, const G4Material *>(
                                    &G4EmCalculator::ComputeNuclearDEDX))

      .def("ComputeNuclearDEDX",
           py::overload_cast<G4double, const G4String &, const G4String &>(&G4EmCalculator::ComputeNuclearDEDX))

      .def("ComputeElectronicDEDX",
           py::overload_cast<G4double, const G4ParticleDefinition *, const G4Material *, G4double>(
              &G4EmCalculator::ComputeElectronicDEDX),
           py::arg("kinEnergy"), py::arg("particle"), py::arg("material"), py::arg("cut") = DBL_MAX)

      .def("ComputeElectronicDEDX",
           py::overload_cast<G4double, const G4String &, const G4String &, G4double>(
              &G4EmCalculator::ComputeElectronicDEDX),
           py::arg("kinEnergy"), py::arg("particle"), py::arg("material"), py::arg("cut") = DBL_MAX)

      .def("ComputeTotalDEDX",
           py::overload_cast<G4double, const G4ParticleDefinition *, const G4Material *, G4double>(
              &G4EmCalculator::ComputeTotalDEDX),
           py::arg("kinEnergy"), py::arg("particle"), py::arg("material"), py::arg("cut") = DBL_MAX)

      .def("ComputeTotalDEDX",
           py::overload_cast<G4double, const G4String &, const G4String &, G4double>(&G4EmCalculator::ComputeTotalDEDX),
           py::arg("kinEnergy"), py::arg("particle"), py::arg("material"), py::arg("cut") = DBL_MAX)

      .def("ComputeCrossSectionPerVolume",
           py::overload_cast<G4double, const G4ParticleDefinition *, const G4String &, const G4Material *, G4double>(
              &G4EmCalculator::ComputeCrossSectionPerVolume),
           py::arg("kinEnergy"), py::arg("particle"), py::arg("processName"), py::arg("material"), py::arg("cut") = 0.0)

      .def("ComputeCrossSectionPerVolume",
           py::overload_cast<G4double, const G4String &, const G4String &, const G4String &, G4double>(
              &G4EmCalculator::ComputeCrossSectionPerVolume),
           py::arg("kinEnergy"), py::arg("particle"), py::arg("processName"), py::arg("material"), py::arg("cut") = 0.0)

      .def("ComputeCrossSectionPerAtom",
           py::overload_cast<G4double, const G4ParticleDefinition *, const G4String &, G4double, G4double, G4double>(
              &G4EmCalculator::ComputeCrossSectionPerAtom),
           py::arg("kinEnergy"), py::arg("particle"), py::arg("processName"), py::arg("Z"), py::arg("A"),
           py::arg("cut") = 0.0)

      .def("ComputeCrossSectionPerAtom",
           py::overload_cast<G4double, const G4String &, const G4String &, const G4Element *, G4double>(
              &G4EmCalculator::ComputeCrossSectionPerAtom),
           py::arg("kinEnergy"), py::arg("particle"), py::arg("processName"), py::arg("elm"), py::arg("cut") = 0.0)

      .def("ComputeEnergyCutFromRangeCut",
           py::overload_cast<G4double, const G4ParticleDefinition *, const G4Material *>(
              &G4EmCalculator::ComputeEnergyCutFromRangeCut))

      .def("ComputeEnergyCutFromRangeCut", py::overload_cast<G4double, const G4String &, const G4String &>(
                                              &G4EmCalculator::ComputeEnergyCutFromRangeCut))

      .def("ComputeMeanFreePath",
           py::overload_cast<G4double, const G4ParticleDefinition *, const G4String &, const G4Material *, G4double>(
              &G4EmCalculator::ComputeMeanFreePath),
           py::arg("kinEnergy"), py::arg("particle"), py::arg("processName"), py::arg("material"), py::arg("cut") = 0.0)

      .def("ComputeMeanFreePath",
           py::overload_cast<G4double, const G4String &, const G4String &, const G4String &, G4double>(
              &G4EmCalculator::ComputeMeanFreePath),
           py::arg("kinEnergy"), py::arg("particle"), py::arg("processName"), py::arg("material"), py::arg("cut") = 0.0)

      .def("FindParticle", &G4EmCalculator::FindParticle, py::return_value_policy::reference)
      .def("FindMaterial", &G4EmCalculator::FindMaterial, py::return_value_policy::reference)
      .def("FindRegion", &G4EmCalculator::FindRegion, py::return_value_policy::reference)
      .def("FindCouple", &G4EmCalculator::FindCouple, py::arg("material"),
           py::arg("region") = static_cast<const G4Region *>(nullptr), py::return_value_policy::reference)

      .def("SetVerbose", &G4EmCalculator::SetVerbose);
}
