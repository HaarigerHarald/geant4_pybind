
file(GLOB SOURCE 
  analysis/*.cc
  digits_hits/*.cc
  event/*.cc
  geometry/*.cc
  global/*.cc
  graphics_reps/*.cc
  intercoms/*.cc
  interface/*.cc
  materials/*.cc
  particles/*.cc
  persistency/*.cc
  physics_lists/*.cc
  processes/*.cc
  run/*.cc
  track/*.cc
  tracking/*.cc
  visualization/*.cc
)

include_directories(.)

if(Geant4_gdml_FOUND)
  add_definitions(-DG4_HAS_GDML)
endif()

if(Geant4_ui_tcsh_FOUND)
  add_definitions(-DG4_HAS_TCSH)
endif()

if(Geant4_vis_opengl_x11_FOUND)
  add_definitions(-DG4_HAS_OPENGLX)
endif()

if(Geant4_vis_raytracer_x11_FOUND)
  add_definitions(-DG4_HAS_RAYTRACERX)
endif()

if(Geant4_motif_FOUND)
  add_definitions(-DG4_HAS_OPENGLXM)
endif()

if(Geant4_vis_opengl_win32_FOUND)
  add_definitions(-DG4_HAS_OPENGLWIN)
endif()

if(Geant4_qt_FOUND)
  add_definitions(-DG4_HAS_QT)
endif()

add_definitions(-DPYBIND11_USE_SMART_HOLDER_AS_DEFAULT)

pybind11_add_module(geant4_pybind
  ${SOURCE}
  geant4_pybind.cc
)

target_link_libraries(geant4_pybind PRIVATE ${Geant4_LIBRARIES})
