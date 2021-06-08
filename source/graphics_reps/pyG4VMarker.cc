#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/operators.h>

#include <G4VMarker.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4VMarker : public G4VMarker {

public:
   using G4VMarker::G4VMarker;

   const G4String &GetInfo() const override { PYBIND11_OVERRIDE(const G4String &, G4VMarker, GetInfo, ); }

   void SetInfo(const G4String &info) override { PYBIND11_OVERRIDE(void, G4VMarker, SetInfo, info); }
};

void export_G4VMarker(py::module &m)
{
   py::class_<G4VMarker, PyG4VMarker> marker(m, "G4VMarker");

   py::enum_<G4VMarker::FillStyle>(marker, "FillStyle")
      .value("noFill", G4VMarker::noFill)
      .value("hashed", G4VMarker::hashed)
      .value("filled", G4VMarker::filled)
      .export_values();

   py::enum_<G4VMarker::SizeType>(marker, "SizeType")
      .value("none", G4VMarker::none)
      .value("world", G4VMarker::world)
      .value("screen", G4VMarker::screen)
      .export_values();

   marker.def(py::init<>())
      .def(py::init([](const G4VMarker &other) { return new G4VMarker(other); }))
      .def(py::init<const G4Point3D &>())
      .def(py::self != py::self)

      .def("GetPosition", &G4VMarker::GetPosition)
      .def("GetSizeType", &G4VMarker::GetSizeType)
      .def("GetWorldSize", &G4VMarker::GetWorldSize)
      .def("GetWorldDiameter", &G4VMarker::GetWorldDiameter)
      .def("GetWorldRadius", &G4VMarker::GetWorldRadius)
      .def("GetScreenSize", &G4VMarker::GetScreenSize)
      .def("GetScreenDiameter", &G4VMarker::GetScreenDiameter)
      .def("GetScreenRadius", &G4VMarker::GetScreenRadius)
      .def("GetFillStyle", &G4VMarker::GetFillStyle)

      .def("SetPosition", &G4VMarker::SetPosition)
      .def("SetSize", &G4VMarker::SetSize)
      .def("SetDiameter", &G4VMarker::SetDiameter)
      .def("SetRadius", &G4VMarker::SetRadius)
      .def("SetWorldSize", &G4VMarker::SetWorldSize)
      .def("SetWorldDiameter", &G4VMarker::SetWorldDiameter)
      .def("SetWorldRadius", &G4VMarker::SetWorldRadius)
      .def("SetScreenSize", &G4VMarker::SetScreenSize)
      .def("SetScreenDiameter", &G4VMarker::SetScreenDiameter)
      .def("SetScreenRadius", &G4VMarker::SetScreenRadius)
      .def("SetFillStyle", &G4VMarker::SetFillStyle)
      .def("GetInfo", &G4VMarker::GetInfo)
      .def("SetInfo", &G4VMarker::SetInfo);
}
