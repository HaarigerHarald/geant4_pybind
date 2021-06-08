#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4Element.hh>
#include <G4Material.hh>
#include <G4VCrossSectionHandler.hh>
#include <G4VDataSetAlgorithm.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4VCrossSectionHandler(py::module &m)
{
   py::class_<G4VCrossSectionHandler>(m, "G4VCrossSectionHandler", "cross section handler")

      //  .def("Initialise", &G4VCrossSectionHandler::Initialise,
      //       py::arg("interpolation") = static_cast<G4VDataSetAlgorithm *>(nullptr), py::arg("minE") = 250 *
      //       CLHEP::eV, py::arg("maxE") = 100 * CLHEP::GeV, py::arg("numberOfBins") = 200, py::arg("unitE") =
      //       CLHEP::MeV, py::arg("unitData") = CLHEP::barn, py::arg("minZ") = 1, py::arg("maxZ") = 99)

      .def("SelectRandomElement", &G4VCrossSectionHandler::SelectRandomElement, py::return_value_policy::reference)
      .def("SelectRandomShell", &G4VCrossSectionHandler::SelectRandomShell)
      .def("FindValue", py::overload_cast<G4int, G4double>(&G4VCrossSectionHandler::FindValue, py::const_))
      .def("FindValue", py::overload_cast<G4int, G4double, G4int>(&G4VCrossSectionHandler::FindValue, py::const_))
      .def("ValueForMaterial", &G4VCrossSectionHandler::ValueForMaterial)
      .def("LoadData", &G4VCrossSectionHandler::LoadData)
      .def("LoadShellData", &G4VCrossSectionHandler::LoadShellData)
      .def("PrintData", &G4VCrossSectionHandler::PrintData)
      .def("Clear", &G4VCrossSectionHandler::Clear);
}
