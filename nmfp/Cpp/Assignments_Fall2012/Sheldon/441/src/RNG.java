import org.math.plot.*;

import java.util.Random;

import javax.swing.JFrame;
public class RNG {
	
	public static Random rand = new Random(10);
	
	public static double rand_g(long seed){
		double random = Math.sqrt(-2 * Math.log(1 - rand.nextDouble())) * Math.cos(6.283185307 * rand.nextDouble());
		return random;
	}
	public static double rand_u(long seed){
		final double a = 16807;
		final double m = 21473647;
		double ph = a * seed;
		seed = (long) (ph % m);
		double random = seed / m;
		return random;
	}
	public static void main(String[] args){
		long seed = 123456;
		long seed_g = 123;
		double g_dist[] = new double[1000];
		double u_dist[] = new double[1000];
		for(int i = 0; i < 1000; i++){
			g_dist[i] = rand_g(seed);
			u_dist[i] = rand_u(seed_g);
			seed_g = (long) rand_u(seed_g);
		}
		
		Plot2DPanel gplot = new Plot2DPanel();
		gplot.addHistogramPlot("Gaussian", g_dist, 100);
		
		Plot2DPanel uplot = new Plot2DPanel();
		uplot.addHistogramPlot("Uniform", u_dist, 100);
		
		JFrame gframe = new JFrame("Gaussian");
		gframe.setSize(600,600);
		gframe.setContentPane(gplot);
		gframe.setVisible(true);
		
		JFrame uframe = new JFrame("Uniform");
		uframe.setSize(600,600);
		uframe.setContentPane(uplot);
		uframe.setVisible(true);
		
	}
}
