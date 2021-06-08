#ifdef G4_HAS_QT

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4OpenGLImmediateQt.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4OpenGLImmediateQt(py::module &m)
{
   py::class_<G4OpenGLImmediateQt, G4VGraphicsSystem>(m, "G4OpenGLImmediateQt", "OpenGL(Qt) visualization module")

      .def(py::init<>());
   // TODO
}

#endif // G4_HAS_QT
