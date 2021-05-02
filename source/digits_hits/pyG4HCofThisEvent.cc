#include <pybind11/pybind11.h>

#include <G4HCofThisEvent.hh>

#include "holder.hh"
#include "typecast.hh"

namespace py = pybind11;

void export_G4HCofThisEvent(py::module &m)
{
   py::class_<G4HCofThisEvent, std::unique_ptr<G4HCofThisEvent>>(m, "G4HCofThisEvent")
      .def(py::init<>())
      .def(py::init<G4int>())
      .def(py::init<const G4HCofThisEvent &>())
      .def("AddHitsCollection",
           [](G4HCofThisEvent &self, G4int HCID, G4VHitsCollection *aHC) {
              owntrans_ptr<G4VHitsCollection>::remove(aHC);
              //TRAMPOLINE_REF_INCREASE(G4VHitsCollection, aHC);
              self.AddHitsCollection(HCID, aHC);
           })

      .def("GetHC", &G4HCofThisEvent::GetHC, py::return_value_policy::reference_internal)
      .def("GetNumberOfCollections", &G4HCofThisEvent::GetNumberOfCollections)
      .def("GetCapacity", &G4HCofThisEvent::GetCapacity);
}
