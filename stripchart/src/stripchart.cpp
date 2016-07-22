//============================================================================
// Name        : stripchart.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
	#include <unistd.h>
	#include <iostream>
#include <TCanvas.h>
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TObjArray.h>
#include <TApplication.h>
#include <TTimeStamp.h>
#include <TSystem.h>
#include <TRoot.h>
#include <TF1.h>
using namespace std;


	int main(Int_t argc,char **argv) {
	TApplication *TheApp = new TApplication("theApp",&argc,argv);  // problem with the two commandline args getting in conflict


	// this programs plots a signal over time
	//


	// Create time stamp



	// Let's see what we get a starting point
    TDatime dtime;
    gStyle->SetTimeOffset(dtime.Convert());
	TCanvas *c1 = new TCanvas("c1","Time on axis",10,10,1000,500);
	c1->SetFillColor(42);
	c1->SetFrameFillColor(33);
	c1->SetGrid();
	c1->cd();

	Float_t bintime = 1;
	//one bin = 1 second. change it to set the time scale
	TH1F *ht = new TH1F("ht","The Noisy Signal",10,0,10*bintime);
	Float_t signal = 1000;
	ht->SetMaximum(signal);
	ht->SetMinimum(-signal);
	ht->SetStats(0);
	ht->SetLineColor(2);
	ht->GetXaxis()->SetTimeDisplay(1);
	ht->GetYaxis()->SetNdivisions(520);
	ht->Draw();
	TF1 *f1 = new TF1("f1","gaus",-5,5);
	TCanvas *c2 = new TCanvas();
			c2->cd();
	f1->Draw();

	for (Int_t i=1;i<20000;i++) {
	// wait for 1 second
	//sleep(1);
	//cout<<"tick \n";
	//======= Build a signal : noisy damped sine ======
	//Float_t noise = f1->GetRandom();
		Float_t noise = i/10;
	cout<<noise<<"\n";
	if (i > 700)
	noise += signal*sin((i-700.)*6.28/30)*exp((700.-i)/300.);
	ht->SetBinContent(i,noise);
	ht->GetXaxis()->SetRange(i-50,i+50);
/*	if(i==50){
	c1->Clear();
	ht->Draw();
	c1->Update();
	}
	else{ */
	c1->Modified();
	c1->Update();
	//}
	gSystem->ProcessEvents();
	//canvas can be edited during the loop
	}




TheApp->Run();
TheApp->Terminate();


return 1;
}
