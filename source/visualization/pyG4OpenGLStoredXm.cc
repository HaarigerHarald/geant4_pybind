#ifdef G4_HAS_OPENGLXM

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4OpenGLStoredXm.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4OpenGLStoredXm(py::module &m)
{
   py::class_<G4OpenGLStoredXm, G4VGraphicsSystem>(m, "G4OpenGLStoredXm", "OpenGL(Stored XM) visualization module")
      .def(py::init<>());
}

#endif // G4_HAS_OPENGLXM
