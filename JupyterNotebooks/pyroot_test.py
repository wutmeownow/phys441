import os

os.system("echo $ROOTSYS")
os.system("echo $PYTHONPATH")

from ROOT import TCanvas

c1 = TCanvas( 'c1', 'Random Number Generator', 0, 0, 1200, 1000 )
c1.SetGridx()
c1.SetGridy()
c1.GetFrame().SetFillColor( 21 )
c1.GetFrame().SetBorderMode(-1 )
c1.GetFrame().SetBorderSize( 5 )
c1.Divide(2,1)

