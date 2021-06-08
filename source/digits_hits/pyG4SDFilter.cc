#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4SDChargedFilter.hh>
#include <G4SDKineticEnergyFilter.hh>
#include <G4SDNeutralFilter.hh>
#include <G4SDParticleFilter.hh>
#include <G4SDParticleWithEnergyFilter.hh>

#include <G4Step.hh>
#include <G4ParticleDefinition.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4SDFilter(py::module &m)
{
   py::class_<G4SDChargedFilter, G4VSDFilter, py::nodelete>(m, "G4SDChargedFilter")

      .def(py::init<G4String>(), py::arg("name"))
      .def("Accept", &G4SDChargedFilter::Accept);

   py::class_<G4SDKineticEnergyFilter, G4VSDFilter, py::nodelete>(m, "G4SDKineticEnergyFilter")

      .def(py::init<G4String, G4double, G4double>(), py::arg("name"), py::arg("elow") = 0.0, py::arg("ehigh") = DBL_MAX)

      .def("Accept", &G4SDKineticEnergyFilter::Accept)
      .def("SetKineticEnergy", &G4SDKineticEnergyFilter::SetKineticEnergy, py::arg("elow"), py::arg("ehigh"))
      .def("show", &G4SDKineticEnergyFilter::show);

   py::class_<G4SDNeutralFilter, G4VSDFilter, py::nodelete>(m, "G4SDNeutralFilter")

      .def(py::init<G4String>(), py::arg("name"))
      .def("Accept", &G4SDNeutralFilter::Accept);

   py::class_<G4SDParticleFilter, G4VSDFilter, py::nodelete>(m, "G4SDParticleFilter")

      .def(py::init<G4String>(), py::arg("name"))
      .def(py::init<G4String, const G4String &>(), py::arg("name"), py::arg("particleName"))
      .def(py::init<G4String, const std::vector<G4String> &>(), py::arg("name"), py::arg("particleNames"))
      .def(py::init<G4String, const std::vector<G4ParticleDefinition *> &>(), py::arg("name"), py::arg("particleDef"))

      .def("Accept", &G4SDParticleFilter::Accept)
      .def("add", &G4SDParticleFilter::add, py::arg("particleName"))
      .def("addIon", &G4SDParticleFilter::addIon, py::arg("Z"), py::arg("A"))
      .def("show", &G4SDParticleFilter::show);

   py::class_<G4SDParticleWithEnergyFilter, G4VSDFilter, py::nodelete>(m, "G4SDParticleWithEnergyFilter")

      .def(py::init<G4String, G4double, G4double>(), py::arg("name"), py::arg("elow") = 0.0, py::arg("ehigh") = DBL_MAX)

      .def("Accept", &G4SDParticleWithEnergyFilter::Accept)
      .def("SetKineticEnergy", &G4SDParticleWithEnergyFilter::SetKineticEnergy, py::arg("elow"), py::arg("ehigh"))
      .def("add", &G4SDParticleWithEnergyFilter::add, py::arg("particleName"))
      .def("show", &G4SDParticleWithEnergyFilter::show);
}
