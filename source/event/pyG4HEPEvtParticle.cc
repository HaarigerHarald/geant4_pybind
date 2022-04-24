#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/operators.h>

#include <G4HEPEvtParticle.hh>
#include <G4ParticleDefinition.hh>
#include <G4VUserPrimaryParticleInformation.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4HEPEvtParticle(py::module &m)
{
   py::class_<G4HEPEvtParticle>(m, "G4HEPEvtParticle")

      .def("__copy__", [](const G4HEPEvtParticle &self) { return new G4HEPEvtParticle(self); })
      .def("__deepcopy__", [](const G4HEPEvtParticle &self, py::dict) { return new G4HEPEvtParticle(self); })
      .def(py::init<>())
      .def(py::init<G4PrimaryParticle *, G4int, G4int, G4int>(), py::arg("pp"), py::arg("isthep"), py::arg("jdahep1"),
           py::arg("jdahep2"))

      .def("Done", &G4HEPEvtParticle::Done)
      .def("GetISTHEP", &G4HEPEvtParticle::GetISTHEP)
      .def("GetJDAHEP1", &G4HEPEvtParticle::GetJDAHEP1)
      .def("GetJDAHEP2", &G4HEPEvtParticle::GetJDAHEP2)
      .def("GetTheParticle", &G4HEPEvtParticle::GetTheParticle, py::return_value_policy::reference)
      .def(py::self != py::self)
      .def(py::self == py::self);
}
