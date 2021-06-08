#ifdef G4_HAS_OPENGLX

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4OpenGLStoredX.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4OpenGLStoredX(py::module &m)
{
   py::class_<G4OpenGLStoredX, G4VGraphicsSystem>(m, "G4OpenGLStoredX", "OpenGL(Stored X) visualization module")
      .def(py::init<>());
}

#endif // G4_HAS_OPENGLX
