#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <FTFP_BERT.hh>
#include <FTFP_BERT_ATL.hh>
#include <FTFP_BERT_HP.hh>
#include <FTFP_BERT_TRV.hh>
#include <FTFP_INCLXX.hh>
#include <FTFP_INCLXX_HP.hh>
#include <FTF_BIC.hh>
#include <LBE.hh>
#include <NuBeam.hh>
#include <QBBC.hh>
#include <QGSP_BERT.hh>
#include <QGSP_BERT_HP.hh>
#include <QGSP_BIC.hh>
#include <QGSP_BIC_AllHP.hh>
#include <QGSP_BIC_HP.hh>
#include <QGSP_FTFP_BERT.hh>
#include <QGSP_INCLXX.hh>
#include <QGSP_INCLXX_HP.hh>
#include <QGS_BIC.hh>
#include <Shielding.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

// macro for adding physics lists
#define ADD_PHYSICS_LIST(plname) \
   py::class_<plname, G4VModularPhysicsList>(m, #plname, #plname " physics list").def(py::init<>());

void export_PhysicsLists(py::module &m)
{
   ADD_PHYSICS_LIST(FTFP_BERT);
   ADD_PHYSICS_LIST(FTFP_BERT_ATL);
   ADD_PHYSICS_LIST(FTFP_BERT_HP);
   ADD_PHYSICS_LIST(FTFP_BERT_TRV);
   ADD_PHYSICS_LIST(FTFP_INCLXX);
   ADD_PHYSICS_LIST(FTFP_INCLXX_HP);
   ADD_PHYSICS_LIST(FTF_BIC);
   ADD_PHYSICS_LIST(LBE);
   ADD_PHYSICS_LIST(NuBeam);
   ADD_PHYSICS_LIST(QBBC);
   ADD_PHYSICS_LIST(QGSP_BERT);
   ADD_PHYSICS_LIST(QGSP_BERT_HP);
   ADD_PHYSICS_LIST(QGSP_BIC);
   ADD_PHYSICS_LIST(QGSP_BIC_AllHP);
   ADD_PHYSICS_LIST(QGSP_BIC_HP);
   ADD_PHYSICS_LIST(QGSP_FTFP_BERT);
   ADD_PHYSICS_LIST(QGSP_INCLXX);
   ADD_PHYSICS_LIST(QGSP_INCLXX_HP);
   ADD_PHYSICS_LIST(QGS_BIC);
   ADD_PHYSICS_LIST(Shielding);
}
