#ifdef G4_HAS_OPENGLXM

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4OpenGLImmediateXm.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4OpenGLImmediateXm(py::module &m)
{
   py::class_<G4OpenGLImmediateXm, G4VGraphicsSystem>(m, "G4OpenGLImmediateXm",
                                                      "OpenGL(Immediate XM) visualization module")
      .def(py::init<>());
   // TODO
}

#endif
