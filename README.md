QCDScaleVariationLHE
====================

QCD scale variation studies


* WW

calculate cross section

 >=0 jet

 >=1 jet

with scale up/down sample

    mc@nlo sample available


Working here:

    cmsneu
    /home/amassiro/Generation/QCDScaleVariationLHE

Dump sensitive information into a root file

    c++ -o ntupleMaker.exe `root-config --glibs --cflags` `lhapdf-config --cppflags  --ldflags` -lm ntupleMaker.cpp
    ./ntupleMaker.exe   blabla.lhe    blabla.root

NB: in the current implementation lhapdf are not needed, but who knows!





