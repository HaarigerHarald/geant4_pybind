#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4VUserTaskQueue(py::module &);
void export_G4RunManagerFactory(py::module &);
void export_G4TaskRunManager(py::module &);

void export_modG4tasking(py::module &m)
{
   export_G4VUserTaskQueue(m);
   export_G4TaskRunManager(m);
   export_G4RunManagerFactory(m);
}
