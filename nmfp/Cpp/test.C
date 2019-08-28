{
   int i; 
   TGraph gr[4]; 
   gObjectTable->Print();
   Float_t a[4][4]=
     {450,1050,1431,1983,1,2,3,4,5,6,7,8,9,10,11,12}; 
   Float_t b[4][4]= 
     {1576,3420,4854,6635,117,262,402,528,21,53,71,93,4,18,24,28};   
   TCanvas *c1=new TCanvas("c1","",1); 
   c1->Divide(2,2); 
   for(i=1;i<5;i++) 
   {
	  c1->cd(i); 
    	  gr[i-1]=new TGraph(4,a[i-1],b[i-1]); 
          gr[i-1]->Draw("AL*"); 
   } 
   gObjectTable->Print();
}
