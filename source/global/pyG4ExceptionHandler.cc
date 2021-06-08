#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4StateManager.hh>
#include <G4VExceptionHandler.hh>
#include <G4ios.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4ExceptionHandler : public G4VExceptionHandler {
public:
   PyG4ExceptionHandler() : G4VExceptionHandler()
   {
      G4StateManager *sm = G4StateManager::GetStateManager();
      sm->SetExceptionHandler(this);
   }
   ~PyG4ExceptionHandler() {}

   G4bool Notify(const char *originOfException, const char *exceptionCode, G4ExceptionSeverity severity,
                 const char *description)
   {

      std::ostringstream message;
      message << "*** G4Exception : " << exceptionCode << G4endl << "      issued by : " << originOfException << G4endl
              << description << G4endl;

      switch (severity) {
      case FatalException:
         PyErr_SetString(PyExc_AssertionError, "*** Fatal Exception ***");
         PyErr_Print();
         G4cerr << message.str() << G4endl;
         break;

      case FatalErrorInArgument:
         PyErr_SetString(PyExc_ValueError, "*** Fatal Error In Argument ***");
         PyErr_Print();
         G4cerr << message.str() << G4endl;
         break;

      case RunMustBeAborted:
         PyErr_SetString(PyExc_RuntimeError, "*** Run Must Be Aborted ***");
         PyErr_Print();
         G4cerr << message.str() << G4endl;
         break;

      case EventMustBeAborted:
         PyErr_SetString(PyExc_RuntimeError, "*** Event Must Be Aborted ***");
         PyErr_Print();
         G4cerr << message.str() << G4endl;
         break;

      default:
         PyErr_Warn(PyExc_RuntimeWarning, "*** This is just a warning message. ***");
         G4cerr << message.str() << G4endl;
         break;
      }

      // anyway, no abort.
      return false;
   }
};

void export_G4ExceptionHandler(py::module &m)
{
   py::class_<PyG4ExceptionHandler>(m, "G4ExceptionHandler", "exception handler").def(py::init<>());
}
