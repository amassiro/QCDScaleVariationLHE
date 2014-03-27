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



# 1M events generation

Where:

    /home/amassiro/Generation/MINLO/POWHEG-BOX/WW/testAM_1M_events

with

    withdamp 1


Configuration powheg.input here:

    Configuration

While scaling up/down do:

    cp Configuration/powheg.input.POINT   powheg.input
    mv pwgevents-rwgt.lhe pwgevents.lhe
    ../pwhg_main


with weights:

    ./ntupleMaker.exe   /home/amassiro/Generation/MINLO/POWHEG-BOX/WW/testAM_10_10_withDump_and_scales/pwgevents.lhe      test.root
    ./ntupleMaker.exe   /tmp/amassiro//pwgevents.lhe      fAll.root
    ./ntupleMaker.exe   /home/amassiro/Generation/MINLO/POWHEG-BOX/WW/testAM_1M_events/pwgevents-rwgt.lhe     fAll.root

    root -l CalculatePOWHEGOneSample.cxx




Plot
=======

    r99t DrawDistribution.cxx\(\"jetpt1\",200,-200,200,\"jetpt1\ [GeV]\"\)
    r99t DrawDistribution.cxx\(\"jetpt1\",200,0,200,\"jetpt1\ [GeV]\"\)
    r99t DrawDistribution.cxx\(\"jeteta1\",100,-5,5,\"jeteta1\"\)




PDF reweight
=======

First generate events with

    storeinfo_rwgt 1

and

    pdfreweight 1


then, once generated change input file 

    lhans1 XXX
    lhans2 XXX

with the new pdf (lhapdf numbering from http://lhapdf.hepforge.org/pdfsets)

after having commented

    #storeinfo_rwgt 1

and adding

    compute_rwgt 1


Now:

    11062
    11063
    11064
    11065
    11066
    11067
    11068
    11069
    11070
    11071
    11072
    11073
    11074




# WW aMC@NLO

Where:

    /home/amassiro/Generation/QCDScaleVariationLHE/

LHE inputs:

    /data/amassiro/CMSSWLHE/WWaMCatNLO/140310_WW0j_deacy_2l2n.lhe

Transform the weight to "#" style:

    sed 's:<wgt:#wgt:' < /data/amassiro/CMSSWLHE/WWaMCatNLO/140310_WW0j_deacy_2l2n.lhe > new.lhe ; cat new.lhe | grep -v "<rwgt>" | grep -v "</rwgt>" | grep -v "<initrwgt>" | grep -v "</initrwgt>" > two.lhe ; rm new.lhe; mv two.lhe /data/amassiro/CMSSWLHE/WWaMCatNLO/140310_WW0j_deacy_2l2n.modified.lhe



Coding:

    <weight id='1001'> muR=0.10000E+01 muF=0.10000E+01 </weight>
    <weight id='1002'> muR=0.10000E+01 muF=0.20000E+01 </weight>
    <weight id='1003'> muR=0.10000E+01 muF=0.50000E+00 </weight>
    <weight id='1004'> muR=0.20000E+01 muF=0.10000E+01 </weight>
    <weight id='1005'> muR=0.20000E+01 muF=0.20000E+01 </weight>
    <weight id='1006'> muR=0.20000E+01 muF=0.50000E+00 </weight>
    <weight id='1007'> muR=0.50000E+00 muF=0.10000E+01 </weight>
    <weight id='1008'> muR=0.50000E+00 muF=0.20000E+01 </weight>
    <weight id='1009'> muR=0.50000E+00 muF=0.50000E+00 </weight>

Typical event:

    <wgt id='1001'>  +2.8460099e+00 </wgt>
    <wgt id='1002'>  +2.1632896e+00 </wgt>
    <wgt id='1003'>  +3.5138639e+00 </wgt>

How it's going to be:


    #new weight,renfact,facfact,pdf1,pdf2  0.663394213531429       0.500000000000000        1.00000000000000            11000       11000  lha
    #new weight,renfact,facfact,pdf1,pdf2  0.652068114333561        1.00000000000000       0.500000000000000            11000       11000  lha
    #new weight,renfact,facfact,pdf1,pdf2  0.719963513969510       0.500000000000000       0.500000000000000            11000       11000  lha
    #new bla                               0.555108255272325        1.00000000000000        2.00000000000000            11000       11000  lha


How it really appears:

    #wgt id='1001'>  +2.8460099e+00 </wgt>
    #wgt id='1002'>  +2.0005984e+00 </wgt>
    #wgt id='1003'>  +3.8051671e+00 </wgt>




Create ntuple:

    ./ntupleMaker.exe  tmp.lhe    fAll_amcatnlo.root  1
    ./ntupleMaker.exe  /data/amassiro/CMSSWLHE/WWaMCatNLO/140310_WW0j_deacy_2l2n.modified.lhe    fAll_amcatnlo.root  1



