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


    /WWTo2L2Nu_CT10_8TeV-mcatnlo/Summer12_DR53X-PU_S10_START53_V7A-v1/AODSIM
    /WWTo2L2Nu_scaledown_CT10_8TeV-mcatnlo/Summer12_DR53X-PU_S10_START53_V7A-v1/AODSIM
    /WWTo2L2Nu_scaleup_CT10_8TeV-mcatnlo/Summer12_DR53X-PU_S10_START53_V7A-v1/AODSIM


    ls /data/amassiro/CMSSWLHE/WWTo2L2Nu_scaledown_CT10_8TeV-mcatnlo/ --color=none  | awk '{print "./ntupleMaker.exe   /data/amassiro/CMSSWLHE/WWTo2L2Nu_scaledown_CT10_8TeV-mcatnlo/"$1"   "$1".root"}'
    ls /data/amassiro/CMSSWLHE/WWTo2L2Nu_scaleup_CT10_8TeV-mcatnlo/ --color=none  | awk '{print "./ntupleMaker.exe     /data/amassiro/CMSSWLHE/WWTo2L2Nu_scaleup_CT10_8TeV-mcatnlo/"$1"   "$1".root"}'
    ls /data/amassiro/CMSSWLHE/WWTo2L2Nu_CT10_8TeV-mcatnlo/ --color=none  | awk '{print "./ntupleMaker.exe   /data/amassiro/CMSSWLHE/WWTo2L2Nu_CT10_8TeV-mcatnlo/"$1"   "$1".root"}'

    hadd down.root WWTo2L2Nu_downScale_CT10_8TeV_mcatnlo_herwig6_*_fix.lhe.root
    hadd up.root WWTo2L2Nu_upScale_CT10_8TeV_mcatnlo_herwig6_*_fix.lhe.root
    hadd cen.root WWTo2L2Nu_centScale_CT10_8TeV_mcatnlo_herwig6_*_fix.lhe.root


Calculate cross section/efficiency scale



