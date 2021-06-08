#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4HCofThisEvent.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4HCofThisEvent(py::module &m)
{
   py::class_<G4HCofThisEvent>(m, "G4HCofThisEvent")
      .def(py::init<>())
      .def(py::init<G4int>())
      .def(py::init<const G4HCofThisEvent &>())
      .def("AddHitsCollection", [](G4HCofThisEvent &self, G4int HCID,
                                   py::disown_ptr<G4VHitsCollection> aHC) { self.AddHitsCollection(HCID, aHC); })

      .def("GetHC", &G4HCofThisEvent::GetHC, py::return_value_policy::reference_internal)
      .def("GetNumberOfCollections", &G4HCofThisEvent::GetNumberOfCollections)
      .def("GetCapacity", &G4HCofThisEvent::GetCapacity);
}
