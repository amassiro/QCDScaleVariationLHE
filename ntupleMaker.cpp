// to compile:
//   c++ -o ntupleMaker.exe `root-config --glibs --cflags` `lhapdf-config --cppflags  --ldflags` -lm ntupleMaker.cpp
//
// to use:
//   ./ntupleMaker.exe fileLHE    outputFileRoot
//

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <functional>
#include <assert.h>


#include "LHEF.h"


#include "LHAPDF/LHAPDF.h"



#include "TNtuple.h"
#include "TFile.h"
#include "TLorentzVector.h"
#include "Math/Vector3D.h"
#include "Math/Vector4D.h"


struct ptsort: public std::binary_function<TLorentzVector, TLorentzVector, bool> {
 bool operator () (const TLorentzVector & x, const TLorentzVector & y) {
  return  (x.Perp () < y.Perp () ) ;
 }
} ;

TLorentzVector buildP (const LHEF::HEPEUP & event, int iPart) {
 TLorentzVector dummy ;
 dummy.SetPxPyPzE (
   event.PUP.at (iPart).at (0), // px
   event.PUP.at (iPart).at (1), // py
   event.PUP.at (iPart).at (2), // pz
   event.PUP.at (iPart).at (3) // E
   ) ;
 return dummy ;
}


std::vector <std::string> transform (std::string inUglyList) {
 std::vector <std::string> list_comments;
 std::string s = inUglyList;
 std::string delimiter = "#";
 size_t pos = 0;
 std::string token;
 while ((pos = s.find(delimiter)) != std::string::npos) {
  token = s.substr(0, pos);
  if (pos != 0) list_comments.push_back(token);   //---- !=0 to remove first empty line
  s.erase(0, pos + delimiter.length());
 }
 list_comments.push_back(s); //---- last one!
 return list_comments;
}




void fillNtuple (std::string fileNameLHE,  TNtuple & ntuple) {
 std::ifstream ifs (fileNameLHE.c_str ()) ;
 LHEF::Reader reader (ifs) ;

 long ieve = 0 ;
 long selected = 0 ;
 double jetsNum = 0. ;

 std::cout << " reading " << fileNameLHE << std::endl;

 // loop over events
 while ( reader.readEvent () ) {
  ieve++;
  if (ieve % 10000 == 0) std::cout << "event " << ieve << "\n" ;

  //----                mu      mu    weight
  std::map < std::pair<float, float>, float > weights;
  std::vector <std::string> comments_LHE = transform (reader.eventComments);

//   std::cout << " comments_LHE.size() = " << comments_LHE.size() << std::endl;
  for (unsigned int iComm = 0; iComm < comments_LHE.size(); iComm++) {
//    std::cout << " i[" << iComm << "] = " << comments_LHE.at(iComm) << std::endl;
  }
  //----                    0 is somethig I don't care:     rwgt            1           3  0.404994932416933         54217137   634096161           0
  //----                    1 is somethig I don't care:     pdf   3 -3 0.21541051E+00 0.32619889E-02 0.21206289E+03 0.12651286E-01 0.93895940E+00
  for (unsigned int iComm = 2; iComm < comments_LHE.size(); iComm++) {
  /// #new weight,renfact,facfact,pdf1,pdf2  0.604844179378303       0.500000000000000        1.00000000000000            11000       11000  lha
   std::stringstream line( comments_LHE.at(iComm) );
   std::string dummy;
   line >> dummy; // new
   line >> dummy; // weight,renfact,facfact,pdf1,pdf2
   float dummy_float_weight;
   line >> dummy_float_weight; // 0.604844179378303
   float dummy_float_mu1;
   line >> dummy_float_mu1; // 0.500000000000000
//    std::cout << " mu1 = " << dummy_float_mu1 << "    ";
   float dummy_float_mu2;
   line >> dummy_float_mu2; // 1.00000000000000
//    std::cout << " mu2 = " << dummy_float_mu2 << std::endl;
   std::pair <float, float> mumu(dummy_float_mu1,dummy_float_mu2);
   weights[mumu] = dummy_float_weight;
  }


  TLorentzVector Higgs;
  int iPartHiggs = -1;
  float mH = 0;

  std::vector<TLorentzVector> v_f_quarks_and_gluons ;
  std::vector<TLorentzVector> v_f_quarks ;
  std::vector<TLorentzVector> v_f_leptons ;
  std::vector<TLorentzVector> v_f_neutrinos ;

  // loop over particles in the event
  // and fill the variables of leptons and quarks
  for (int iPart = 0 ; iPart < reader.hepeup.IDUP.size (); ++iPart) {

   // look for the Higgs
   if (abs (reader.hepeup.IDUP.at (iPart)) == 25) {
    iPartHiggs = iPart;
    Higgs.SetPxPyPzE  (
      reader.hepeup.PUP.at (iPart).at (0), // px
      reader.hepeup.PUP.at (iPart).at (1), // py
      reader.hepeup.PUP.at (iPart).at (2), // pz
      reader.hepeup.PUP.at (iPart).at (3) // E
      );
    mH = Higgs.M();
   }

   // outgoing particles
   if (reader.hepeup.ISTUP.at (iPart) == 1) {
    // quarks
    if (abs (reader.hepeup.IDUP.at (iPart)) < 7) {
     TLorentzVector dummy (
       reader.hepeup.PUP.at (iPart).at (0), // px
       reader.hepeup.PUP.at (iPart).at (1), // py
       reader.hepeup.PUP.at (iPart).at (2), // pz
       reader.hepeup.PUP.at (iPart).at (3) // E
       ) ;
     v_f_quarks.push_back (dummy) ;
     v_f_quarks_and_gluons.push_back (dummy) ;
    } // quarks
    else if (abs (reader.hepeup.IDUP.at (iPart)) == 11 || abs (reader.hepeup.IDUP.at (iPart)) == 13 || abs (reader.hepeup.IDUP.at (iPart)) == 15) {  // e = 11,   mu = 13,   tau = 15
     TLorentzVector dummy (
       reader.hepeup.PUP.at (iPart).at (0), // px
       reader.hepeup.PUP.at (iPart).at (1), // py
       reader.hepeup.PUP.at (iPart).at (2), // pz
       reader.hepeup.PUP.at (iPart).at (3) // E
       ) ;
     v_f_leptons.push_back (dummy) ;
    }
    else if (abs (reader.hepeup.IDUP.at (iPart)) == 12 || abs (reader.hepeup.IDUP.at (iPart)) == 14 || abs (reader.hepeup.IDUP.at (iPart)) == 16) { // ve = 12,   vmu = 14,   vtau = 16
     TLorentzVector dummy
       (
       reader.hepeup.PUP.at (iPart).at (0), // px
       reader.hepeup.PUP.at (iPart).at (1), // py
       reader.hepeup.PUP.at (iPart).at (2), // pz
       reader.hepeup.PUP.at (iPart).at (3) // E
       ) ;
     v_f_neutrinos.push_back (dummy) ;
    }
    else if (abs (reader.hepeup.IDUP.at (iPart)) == 21) { //---- gluons
     TLorentzVector dummy (
       reader.hepeup.PUP.at (iPart).at (0), // px
       reader.hepeup.PUP.at (iPart).at (1), // py
       reader.hepeup.PUP.at (iPart).at (2), // pz
       reader.hepeup.PUP.at (iPart).at (3) // E
                          ) ;
     v_f_quarks_and_gluons.push_back (dummy) ;
    }

   } // outgoing particles
  } // loop over particles in the event

  if (v_f_leptons.size () != 2) {
   std::cout << " what !?!?!?! Not 2 leptons? Are you kidding?" << std::endl;
   continue;
  }


  // sorting in pt
  sort (v_f_quarks_and_gluons.rbegin (), v_f_quarks_and_gluons.rend (), ptsort ()) ;
  sort (v_f_quarks.rbegin (), v_f_quarks.rend (), ptsort ()) ;
  sort (v_f_leptons.rbegin (), v_f_leptons.rend (), ptsort ()) ;

  TLorentzVector diLepton = v_f_leptons.at (0) + v_f_leptons.at (1) ;
  TLorentzVector missingEnergy = v_f_neutrinos.at (0) + v_f_neutrinos.at (1) ;

  TLorentzVector dilepton_plus_dineutrinos = v_f_leptons.at (0) + v_f_leptons.at (1) + v_f_neutrinos.at (0) + v_f_neutrinos.at (1) ;

  // the sum pf the two quarks

  float jetpt1 = -99;
  if (v_f_quarks_and_gluons.size()>0) jetpt1 = v_f_quarks_and_gluons.at (0).Pt ();
  float jetpt2 = -99;
  if (v_f_quarks_and_gluons.size()>1) jetpt2 = v_f_quarks_and_gluons.at (1).Pt ();

  ntuple.Fill (
    jetpt1,
    jetpt2,
//     v_f_leptons.at (0).Pt (),
//     v_f_leptons.at (1).Pt ()
    weights[std::pair<float, float>(0.5, 0.5)],
    weights[std::pair<float, float>(1.0, 0.5)],
    weights[std::pair<float, float>(0.5, 1.0)],
    weights[std::pair<float, float>(1.0, 2.0)],
    weights[std::pair<float, float>(2.0, 1.0)],
    weights[std::pair<float, float>(2.0, 2.0)],
    weights[std::pair<float, float>(1.0, 1.0)]
//     1
    ) ;

 } // loop over events

}



int main (int argc, char **argv) { 
 // Open a stream connected to an event file:
 if (argc < 3) exit (1) ;

 std::cout << " Input  LHE  =" << argv[1] << std::endl;
 std::cout << " Output ROOT =" << argv[2] << std::endl;

 
 const int SUBSET = 0 ;
 const std::string NAME = "cteq6ll" ; //"cteq6l1"

 LHAPDF::initPDFSet (NAME, LHAPDF::LHPDF, SUBSET) ;
 const int NUMBER = LHAPDF::numberPDF () ;

 LHAPDF::initPDF (0) ;


//  TNtuple ntu ("ntu", "ntu", "jetpt1:jetpt2:pt1:pt2");
 TNtuple ntu ("ntu", "ntu", "jetpt1:jetpt2:w00:w10:w01:w12:w21:w22:w11");
 fillNtuple (argv[1], ntu) ;

 TFile output (argv[2], "recreate") ;
 output.cd() ;
 ntu.Write();
 output.Close();

}



