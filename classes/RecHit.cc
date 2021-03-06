#include <iostream>
#include "RecHit.hh"

RecHit::RecHit(RecHit& r){
    _thickness = r._thickness;
    _layer = r._layer;
    _puOffset = r._puOffset;
    _mom = r._mom;
    _pos = r._pos;

};

RecHit::RecHit(TLorentzVector p4, TLorentzVector pos, int layer){
   _mom = p4;
   _pos = pos;
   _layer = layer;
}


RecHit::RecHit(TLorentzVector p4, TLorentzVector pos, int layer, float thickness){
   _mom = p4;
   _pos = pos;
   _layer = layer;
   _thickness = thickness;
}

void RecHit::setP4(TLorentzVector p4){
   _mom = p4;
}

void RecHit::setThickness(float thickness){
   _thickness = thickness;
}

void RecHit::setPuOffset(float puOffset){
   _puOffset = puOffset;
}

bool RecHit::isAboveThreshold(RecHitCalibration rc, float ecut){
   float sigmaNoise = 1.;
   int thickIndex = -1;
   if( _layer <= 40 ){ // EE + FH
       if(_thickness>99. && _thickness<101.) thickIndex=0;
       else if(_thickness>199. && _thickness<201.) thickIndex=1;
       else if(_thickness>299. && _thickness<301.) thickIndex=2;
       else std::cout<< "ERROR - silicon thickness has a nonsensical value"<<std::endl;
   }
   
   // returns threshold for EE, FH, BH (in case of BH thickIndex does not play a role)
   sigmaNoise = 0.001 * (rc.sigmaNoiseMeV(_layer, thickIndex));

   //this checks if rechit energy is above the threshold of ecut (times the sigma noise for the sensor, if that option is set)
   return _mom.E() >= ecut*sigmaNoise; 
   //return (_mom.E() >= ecut*sigmaNoise && _mom.E() >= 0.05); 
}

bool RecHit::isAbovePuNoise(){
   _mom *= (_mom.E() - _puOffset)/_mom.E();
   return _mom.E() > 0; 
}

float RecHit::eta() {return _mom.Eta();}
float RecHit::phi() {return _mom.Phi();}
float RecHit::pt() {return _mom.Pt();}
float RecHit::energy() {return _mom.E();}
float RecHit::x() {return _pos.X();}
float RecHit::y() {return _pos.Y();}
float RecHit::z() {return _pos.Z();}
float RecHit::px() {return _mom.Px();}
float RecHit::py() {return _mom.Py();}
float RecHit::pz() {return _mom.Pz();}
float RecHit::thickness() {return _thickness;}
int   RecHit::layer() {return _layer;}
TLorentzVector RecHit::p4() {return _mom;}
TLorentzVector RecHit::pos() {return _pos;}

