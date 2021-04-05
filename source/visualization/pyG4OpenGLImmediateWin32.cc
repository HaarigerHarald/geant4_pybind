#ifdef G4_HAS_OPENGLWIN

#include <pybind11/pybind11.h>

#include <G4OpenGLImmediateWin32.hh>

#include "holder.hh"
#include "typecast.hh"

namespace py = pybind11;

void export_G4OpenGLImmediateWin32(py::module &m)
{
   py::class_<G4OpenGLImmediateWin32, G4VGraphicsSystem, owntrans_ptr<G4OpenGLImmediateWin32>>(
      m, "G4OpenGLImmediateWin32", "OpenGL(Immediate Win32) visualization module")
      .def(py::init<>());
   // TODO
}

#endif // G4_HAS_OPENGLWIN
