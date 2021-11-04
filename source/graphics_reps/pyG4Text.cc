#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4Text.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4Text(py::module &m)
{
   py::class_<G4Text, G4VMarker> g4Text(m, "G4Text");

   py::enum_<G4Text::Layout>(g4Text, "Layout")
      .value("left", G4Text::left)
      .value("centre", G4Text::centre)
      .value("right", G4Text::right)
      .export_values();

   g4Text.def(py::init<const G4String &>(), py::arg("text"))
      .def(py::init<const G4String &, const G4Point3D &>(), py::arg("text"), py::arg("position"))
      .def(py::init<const G4VMarker &>())

      .def("GetText", &G4Text::GetText)
      .def("GetLayout", &G4Text::GetLayout)

      .def("GetXOffset", &G4Text::GetXOffset)
      .def("GetYOffset", &G4Text::GetYOffset)

      .def("SetText", &G4Text::SetText)
      .def("SetLayout", &G4Text::SetLayout)
      .def("SetOffset", &G4Text::SetOffset, py::arg("dx"), py::arg("dy"))

      .def(
         "__str__",
         [](const G4Text &self) {
            std::stringstream ss;
            ss << self;
            return ss.str();
         },
         py::is_operator());
}
