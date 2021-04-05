#ifdef G4_HAS_OPENGLXM

#include <pybind11/pybind11.h>

#include <G4OpenGLImmediateXm.hh>

#include "holder.hh"
#include "typecast.hh"

namespace py = pybind11;

void export_G4OpenGLImmediateXm(py::module &m)
{
   py::class_<G4OpenGLImmediateXm, G4VGraphicsSystem, owntrans_ptr<G4OpenGLImmediateXm>>(
      m, "G4OpenGLImmediateXm", "OpenGL(Immediate XM) visualization module")
      .def(py::init<>());
   // TODO
}

#endif
