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

    root -l Calculate.cxx

Calculate as a function of pt threshold

    root -l CalculatePtThreshold.cxx


# POWHEG

Compile:

    first check "ReweightingStuff" README

    export PATH=/home/amassiro/Generation/MINLO/install-fastjet-3.0.6/bin/:$PATH
    export PATH=/home/amassiro/Generation/lhapdf/install-lhapdf-5.9.1/bin/:$PATH
    export LD_LIBRARY_PATH=/home/amassiro/Generation/MINLO/install-fastjet-3.0.6/lib/:$LD_LIBRARY_PATH
    export LD_LIBRARY_PATH=/home/amassiro/Generation/lhapdf/install-lhapdf-5.9.1/lib/:$LD_LIBRARY_PATH
    export LHAPATH=/home/amassiro/Generation/lhapdf/install-lhapdf-5.9.1/share/lhapdf/PDFsets

    make

Generation:

     cd /home/amassiro/Generation/MINLO/POWHEG-BOX/WW/testAM_05_05/
     ../pwhg_main

and do the same for all factorization/renormalization scale folders.

To clean a folder:

    ls | grep -v powheg.input | awk '{print "rm "$1}'

Alternatively reweight one powheg production:

 * in the first production do:

    storeinfo_rwgt 1    ! to save in generation for reweight (0 after)
    pdfreweight 1       ! (default 0) write extra pdf infos on LHEF

 * then, after changing the renorm and fact scale (do a loop over different combinations):

    storeinfo_rwgt 0    ! to save in generation for reweight (0 after)
    pdfreweight 0       ! (default 0) write extra pdf infos on LHEF
    compute_rwgt 1      ! to reweight after



Calculate with POWHEG (with matrix 2x/0.5x in fact and renorm same)

    ./ntupleMaker.exe   /home/amassiro/Generation/MINLO/POWHEG-BOX/WW/testAM_09_09/pwgevents.lhe      f0505.root
    ./ntupleMaker.exe   /home/amassiro/Generation/MINLO/POWHEG-BOX/WW/testAM_05_10/pwgevents.lhe      f0510.root
    ./ntupleMaker.exe   /home/amassiro/Generation/MINLO/POWHEG-BOX/WW/testAM_10_05/pwgevents.lhe      f1005.root
    ./ntupleMaker.exe   /home/amassiro/Generation/MINLO/POWHEG-BOX/WW/testAM_10_10/pwgevents.lhe      f1010.root
    ./ntupleMaker.exe   /home/amassiro/Generation/MINLO/POWHEG-BOX/WW/testAM_10_20/pwgevents.lhe      f1020.root
    ./ntupleMaker.exe   /home/amassiro/Generation/MINLO/POWHEG-BOX/WW/testAM_20_10/pwgevents.lhe      f2010.root
    ./ntupleMaker.exe   /home/amassiro/Generation/MINLO/POWHEG-BOX/WW/testAM_20_20/pwgevents.lhe      f2020.root

    root -l CalculatePOWHEG.cxx



Where:

    /home/amassiro/Generation/MINLO/POWHEG-BOX/WW/testAM_10_10_withDump_and_scales

with

    withdamp 1

done:

    11
    22
    12
    21
    10
    01
    00











