#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4ExceptionSeverity.hh>
#include <G4StateManager.hh>
#include <G4ios.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4Exception(py::module &m)
{
   m.def("G4Exception", [](const char *originOfException, const char *exceptionCode, G4ExceptionSeverity severity,
                           const char *description) {
      G4VExceptionHandler *exceptionHandler = G4StateManager::GetStateManager()->GetExceptionHandler();
      G4bool               toBeAborted      = true;
      if (exceptionHandler) {
         toBeAborted = exceptionHandler->Notify(originOfException, exceptionCode, severity, description);
      } else {
         G4String           e_banner = "\n!!!!! - !!!!! - !!!!! - !!!!! - !!!!! - !!!!!\n";
         G4String           w_banner = "\nwwwww - wwwww - wwwww - wwwww - wwwww - wwwww\n";
         std::ostringstream message;
         message << "\n*** ExceptionHandler is not defined ***\n"
                 << "*** G4Exception : " << exceptionCode << G4endl << "      issued by : " << originOfException
                 << G4endl << description << G4endl;
         switch (severity) {
         case FatalException: G4cerr << e_banner << message.str() << "*** Fatal Exception ***" << e_banner; break;
         case FatalErrorInArgument:
            G4cerr << e_banner << message.str() << "*** Fatal Error In Argument ***" << e_banner;
            break;
         case RunMustBeAborted: G4cerr << e_banner << message.str() << "*** Run Must Be Aborted ***" << e_banner; break;
         case EventMustBeAborted:
            G4cerr << e_banner << message.str() << "*** Event Must Be Aborted ***" << e_banner;
            break;
         default:
            G4cout << w_banner << message.str() << "*** This is just a warning message. ***" << w_banner;
            toBeAborted = false;
            break;
         }
      }

      if (toBeAborted) {
         if (G4StateManager::GetStateManager()->SetNewState(G4State_Abort)) {
            G4cerr << G4endl << "*** G4Exception: Aborting execution ***" << G4endl;
            PyErr_SetString(PyExc_RuntimeError, description);
            PyErr_Print();
         } else {
            G4cerr << G4endl << "*** G4Exception: Abortion suppressed ***" << G4endl
                   << "*** No guarantee for further execution ***" << G4endl;
         }
      }
   });
}
