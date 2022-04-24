#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4StackedTrack.hh>
#include <G4VTrajectory.hh>
#include <G4Track.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4StackedTrack(py::module &m)
{
   py::class_<G4StackedTrack>(m, "G4StackedTrack")

      .def(py::init<>())
      .def(py::init<G4Track *, G4VTrajectory *>(), py::arg("aTrack"),
           py::arg("aTraj") = static_cast<G4VTrajectory *>(nullptr))

      .def("__copy__", [](const G4StackedTrack &self) { return new G4StackedTrack(self); })
      .def("__deepcopy__", [](const G4StackedTrack &self, py::dict) { return new G4StackedTrack(self); })
      .def("GetTrack", &G4StackedTrack::GetTrack, py::return_value_policy::reference)
      .def("GetTrajectory", &G4StackedTrack::GetTrajectory, py::return_value_policy::reference);
}
