#ifdef G4_HAS_OPENGLX

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4OpenGLImmediateX.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4OpenGLImmediateX(py::module &m)
{
   py::class_<G4OpenGLImmediateX, G4VGraphicsSystem>(m, "G4OpenGLImmediateX",
                                                     "OpenGL(Immediate X) visualization module")
      .def(py::init<>());
   // TODO
}

#endif // G4_HAS_OPENGLX
