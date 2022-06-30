#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4ICRU90StoppingData.hh>
#include <G4DensityEffectData.hh>
#include <G4DensityEffectCalculator.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4ICRU90StoppingData(py::module &m)
{
   py::class_<G4ICRU90StoppingData>(m, "G4ICRU90StoppingData")

      .def(py::init<>())
      .def(
         "GetElectronicDEDXforAlpha",
         py::overload_cast<const G4Material *, G4double>(&G4ICRU90StoppingData::GetElectronicDEDXforAlpha, py::const_),
         py::arg("arg0"), py::arg("scaledKinEnergy"))

      .def("GetElectronicDEDXforAlpha",
           py::overload_cast<G4int, G4double>(&G4ICRU90StoppingData::GetElectronicDEDXforAlpha, py::const_),
           py::arg("idx"), py::arg("scaledKinEnergy"))

      .def(
         "GetElectronicDEDXforProton",
         py::overload_cast<const G4Material *, G4double>(&G4ICRU90StoppingData::GetElectronicDEDXforProton, py::const_),
         py::arg("arg0"), py::arg("kinEnergy"))

      .def("GetElectronicDEDXforProton",
           py::overload_cast<G4int, G4double>(&G4ICRU90StoppingData::GetElectronicDEDXforProton, py::const_),
           py::arg("idx"), py::arg("kinEnergy"))

      .def("GetIndex", py::overload_cast<const G4Material *>(&G4ICRU90StoppingData::GetIndex, py::const_))
      .def("GetIndex", py::overload_cast<const G4String &>(&G4ICRU90StoppingData::GetIndex, py::const_))
      .def("Initialise", &G4ICRU90StoppingData::Initialise)
      .def("IsApplicable", &G4ICRU90StoppingData::IsApplicable);
}
