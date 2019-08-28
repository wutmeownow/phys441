import java.io.*;
import java.util.Scanner;
import org.math.plot.*;

import javax.swing.JFrame;
public class FinalHistogram {

	public static void main(String[] args) throws FileNotFoundException{
		Scanner fileScan = new Scanner(new File("vmagF.txt"));
		double hist[] = new double[15200];
		for( int i = 0; i < hist.length; i++){
			hist[i] = fileScan.nextDouble();
		}
		
		Plot2DPanel plot = new Plot2DPanel();
		plot.addHistogramPlot("Frequency of Collisions", hist, 1000);
		
		JFrame frame = new JFrame("Frequency of Collisions");
		frame.setSize(600,600);
		frame.setContentPane(plot);
		frame.setVisible(true);
	}
}
