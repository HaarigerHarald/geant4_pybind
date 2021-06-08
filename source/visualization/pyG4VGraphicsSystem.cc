#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4VGraphicsSystem.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4VGraphicsSystem(py::module &m)
{
   py::class_<G4VGraphicsSystem> graphicsSystem(m, "G4VGraphicsSystem", "base class of graphics system");

   py::enum_<G4VGraphicsSystem::Functionality>(graphicsSystem, "Functionality")
      .value("noFunctionality", G4VGraphicsSystem::noFunctionality)
      .value("nonEuclidian", G4VGraphicsSystem::nonEuclidian)
      .value("twoD", G4VGraphicsSystem::twoD)
      .value("twoDStore", G4VGraphicsSystem::twoDStore)
      .value("threeD", G4VGraphicsSystem::threeD)
      .value("threeDInteractive", G4VGraphicsSystem::threeDInteractive)
      .value("virtualReality", G4VGraphicsSystem::virtualReality)
      .value("fileWriter", G4VGraphicsSystem::fileWriter)
      .export_values();

   graphicsSystem
      //.def(py::init<const G4String &, G4VGraphicsSystem::Functionality>())
      //.def(py::init<const G4String &, const G4String &, G4VGraphicsSystem::Functionality>())
      //.def(py::init<const G4String &, const G4String &, const G4String &, G4VGraphicsSystem::Functionality>())
      .def("GetName", &G4VGraphicsSystem::GetName)
      .def("GetNickname", &G4VGraphicsSystem::GetNickname)
      .def("GetNicknames", &G4VGraphicsSystem::GetNicknames)
      .def("GetDescription", &G4VGraphicsSystem::GetDescription)
      .def("GetFunctionality", &G4VGraphicsSystem::GetFunctionality)
      .def("IsUISessionCompatible", &G4VGraphicsSystem::IsUISessionCompatible)
      .def("AddNickname", &G4VGraphicsSystem::AddNickname);
}
