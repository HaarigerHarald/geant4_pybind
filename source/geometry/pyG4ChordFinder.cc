#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4ChordFinder.hh>
#include <G4MagneticField.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4ChordFinder(py::module &m)
{
   py::class_<G4ChordFinder>(m, "G4ChordFinder", "chord finder class")

      .def(py::init<G4MagneticField *>())
      .def(py::init<G4MagneticField *, G4double>())
      .def(py::init<G4MagneticField *, G4double, G4MagIntegratorStepper *>())

      .def("GetDeltaChord", &G4ChordFinder::GetDeltaChord)
      .def("SetDeltaChord", &G4ChordFinder::SetDeltaChord)

      .def("SetVerbose", &G4ChordFinder::SetVerbose, py::arg("newValue") = 1);
}
