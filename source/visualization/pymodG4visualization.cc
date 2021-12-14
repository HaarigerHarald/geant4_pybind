#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4VisManager(py::module &);
void export_G4VisExecutive(py::module &);
void export_G4VGraphicsSystem(py::module &);
void export_G4VRML1File(py::module &);
void export_G4VRML2File(py::module &);
void export_G4DAWNFILE(py::module &);
void export_G4HepRep(py::module &);
void export_G4HepRepFile(py::module &);
void export_G4ASCIITree(py::module &);
void export_G4RayTracer(py::module &);

#ifdef G4_HAS_OPENGLX
void export_G4OpenGLStoredX(py::module &);
void export_G4OpenGLImmediateX(py::module &);
#endif

#ifdef G4_HAS_OPENGLXM
void export_G4OpenGLStoredXm(py::module &);
void export_G4OpenGLImmediateXm(py::module &);
#endif

#ifdef G4_HAS_RAYTRACERX
void export_G4RayTracerX(py::module &);
#endif

#ifdef G4_HAS_OPENGLWIN
void export_G4OpenGLImmediateWin32(py::module &);
#endif

#ifdef G4_HAS_QT
void export_G4OpenGLImmediateQt(py::module &);
#endif

void export_modG4visualization(py::module &m)
{
   export_G4VisManager(m);
   export_G4VisExecutive(m);
   export_G4VGraphicsSystem(m);
   export_G4VRML2File(m);
   export_G4DAWNFILE(m);
   export_G4HepRepFile(m);
   export_G4ASCIITree(m);
   export_G4RayTracer(m);

#ifdef G4_HAS_OPENGLX
   export_G4OpenGLStoredX(m);
   export_G4OpenGLImmediateX(m);
#endif

#ifdef G4_HAS_OPENGLXM
   export_G4OpenGLStoredXm(m);
   export_G4OpenGLImmediateXm(m);
#endif

#ifdef G4_HAS_RAYTRACERX
   export_G4RayTracerX(m);
#endif

#ifdef G4_HAS_OPENGLWIN
   export_G4OpenGLImmediateWin32(m);
#endif

#ifdef G4_HAS_QT
   export_G4OpenGLImmediateQt(m);
#endif
}
