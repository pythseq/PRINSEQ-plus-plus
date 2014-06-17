//
//  SequenceData.h
//  PrinSeq
//
//  Created by Jeffrey Sadural on 6/17/14.
//  Copyright (c) 2014 Jeffrey Sadural. All rights reserved.
//

#ifndef __PrinSeq__SequenceData__
#define __PrinSeq__SequenceData__

#include <iostream>
using namespace std;

class SequenceData{
public:
    
    SequenceData();
    SequenceData(string label,string sequence);
    SequenceData(string label,string sequence, bool amino);
    
    void SetSeqClass(string label,string sequence);
    void SetID(string sequenceID);
    void SetDNA(string sequence);
    void SetSeqLength(int sequenceLength);
    void SetAmino(bool amino);
    
    string GetID();
    string GetDNASeq();
    int GetSeqLength();
    bool GetAmino();
    
    void TrimSeqLeft(int trimValue);
    void TrimSeqRight(int trimValue);
    
private:
    string sequenceID;
    string sequence;
    int sequenceLength;
    bool amino;
    
    
};
#endif /* defined(__PrinSeq__SequenceData__) */
