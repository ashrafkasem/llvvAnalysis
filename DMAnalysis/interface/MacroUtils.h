#ifndef MacroUtils_h
#define MacroUtils_h

#include<iostream>
#include<vector>
#include <ext/hash_map>

#include "TGraph.h"
#include "TH1.h"
#include "TF1.h"

#include "Math/LorentzVector.h"
#include "DataFormats/Math/interface/deltaR.h"

typedef ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > LorentzVector;
typedef std::vector<LorentzVector> LorentzVectorCollection;


LorentzVector min(const LorentzVector& a, const LorentzVector& b);
double weightVBF(std::string SampleName, double m_gen, double mass);
double weightNarrowResonnance(std::string SampleName, double m_gen, double mass, double Cprime, double BRnew, TGraph* hLineShapeNominal, TF1 *decayProbPdf=0);

typedef std::vector<TGraph *> PuShifter_t;
enum PuShifterTypes {PUDOWN,PUUP};
PuShifter_t getPUshifters(std::vector< float > &Lumi_distr, float puUnc);

// CODE FOR DUPLICATE EVENTS CHECKING
namespace __gnu_cxx{
        template<> struct hash< std::string >{
                size_t operator()( const std::string& x ) const{ return hash< const char* >()( x.c_str() );  }
        };
}

class DuplicatesChecker{
   private :
  typedef __gnu_cxx::hash_map<std::string, bool > RunEventHashMap;
      RunEventHashMap map;
   public :
        DuplicatesChecker(){}
        ~DuplicatesChecker(){}
        void Clear(){map.clear();}
        bool isDuplicate(unsigned int Run, unsigned int Lumi, unsigned int Event){
           char tmp[255];sprintf(tmp,"%i_%i_%i",Run,Lumi,Event);
           RunEventHashMap::iterator it = map.find(tmp);
           if(it==map.end()){
              map[tmp] = true;
              return false;
           }
           return true;
        }
        bool isDuplicate(unsigned int Run, unsigned int Lumi, unsigned int Event,unsigned int cat){
	  char tmp[255];sprintf(tmp,"%i_%i_%i_%i",Run,Lumi,Event,cat);
	  RunEventHashMap::iterator it = map.find(tmp);
	  if(it==map.end()){
	    map[tmp] = true;
	    return false;
	  }
	  return true;
        }
};

//
std::string toLatexRounded(double value, double error, double systError=-1);

//
std::pair<TH1 *,TH1 *> generateHistoEnvelope(TH1 *h,bool debug=false);

#endif
