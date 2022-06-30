#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4IonisParamElm.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4IonisParamElm(py::module &m)
{
   py::class_<G4IonisParamElm>(m, "G4IonisParamElm")

      .def(py::init<G4double>(), py::arg("Z"))
      .def("GetAlow", &G4IonisParamElm::GetAlow)
      .def("GetBlow", &G4IonisParamElm::GetBlow)
      .def("GetClow", &G4IonisParamElm::GetClow)
      .def("GetFermiVelocity", &G4IonisParamElm::GetFermiVelocity)
      .def("GetLFactor", &G4IonisParamElm::GetLFactor)
      .def("GetMeanExcitationEnergy", &G4IonisParamElm::GetMeanExcitationEnergy)
      .def("GetShellCorrectionVector", &G4IonisParamElm::GetShellCorrectionVector, py::return_value_policy::reference)
      .def("GetTau0", &G4IonisParamElm::GetTau0)
      .def("GetTaul", &G4IonisParamElm::GetTaul)
      .def("GetZ", &G4IonisParamElm::GetZ)
      .def("GetZ3", &G4IonisParamElm::GetZ3)
      .def("GetZZ3", &G4IonisParamElm::GetZZ3)
      .def("GetlogZ3", &G4IonisParamElm::GetlogZ3);
}
