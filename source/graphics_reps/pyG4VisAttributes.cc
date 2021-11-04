#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/operators.h>

#include <G4AttDef.hh>
#include <G4AttValue.hh>
#include <G4VisAttributes.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4VisAttributes(py::module &m)
{
   py::class_<G4VisAttributes> visAttributes(m, "G4VisAttributes", "visualization attributes");

   py::enum_<G4VisAttributes::LineStyle>(visAttributes, "LineStyle")
      .value("unbroken", G4VisAttributes::unbroken)
      .value("dashed", G4VisAttributes::dashed)
      .value("dotted", G4VisAttributes::dotted)
      .export_values();

   py::enum_<G4VisAttributes::ForcedDrawingStyle>(visAttributes, "ForcedDrawingStyle")
      .value("wireframe", G4VisAttributes::wireframe)
      .value("solid", G4VisAttributes::solid)
      .export_values();

   visAttributes.def(py::init<>())
      .def(py::init<G4bool>())
      .def(py::init<const G4Colour &>())
      .def(py::init<G4bool, const G4Colour &>())

      .def_static("GetInvisible", &G4VisAttributes::GetInvisible, py::return_value_policy::reference)
      .def("IsVisible", &G4VisAttributes::IsVisible)
      .def("IsDaughtersInvisible", &G4VisAttributes::IsDaughtersInvisible)

      .def("GetColour", &G4VisAttributes::GetColour, py::return_value_policy::reference_internal)
      .def("GetColor", &G4VisAttributes::GetColor, py::return_value_policy::reference_internal)

      .def("GetLineStyle", &G4VisAttributes::GetLineStyle)
      .def("GetLineWidth", &G4VisAttributes::GetLineWidth)
      .def("IsForceDrawingStyle", &G4VisAttributes::IsForceDrawingStyle)
      .def("GetForcedDrawingStyle", &G4VisAttributes::GetForcedDrawingStyle)
      .def("IsForceAuxEdgeVisible", &G4VisAttributes::IsForceAuxEdgeVisible)
      .def("SetVisibility", &G4VisAttributes::SetVisibility)
      .def("SetDaughtersInvisible", &G4VisAttributes::SetDaughtersInvisible)
      .def("SetColor", py::overload_cast<double, double, double, double>(&G4VisAttributes::SetColor))
      .def("SetColour", py::overload_cast<double, double, double, double>(&G4VisAttributes::SetColour))
      .def("SetColor", py::overload_cast<const G4Color &>(&G4VisAttributes::SetColor))
      .def("SetColour", py::overload_cast<const G4Colour &>(&G4VisAttributes::SetColour))
      .def("SetLineStyle", &G4VisAttributes::SetLineStyle)
      .def("SetLineWidth", &G4VisAttributes::SetLineWidth)
      .def("SetForceWireframe", &G4VisAttributes::SetForceWireframe)
      .def("SetForceSolid", &G4VisAttributes::SetForceSolid)
      .def("SetForceAuxEdgeVisible", &G4VisAttributes::SetForceAuxEdgeVisible)
      .def("SetAttValues", &G4VisAttributes::SetAttValues)
      .def("SetAttDefs", &G4VisAttributes::SetAttDefs)

      .def(
         "__str__",
         [](const G4VisAttributes &self) {
            std::stringstream ss;
            ss << std::setprecision(std::numeric_limits<G4double>::digits10 + 1) << self;
            return ss.str();
         },
         py::is_operator())

      .def(py::self == py::self)
      .def(py::self != py::self);
}
