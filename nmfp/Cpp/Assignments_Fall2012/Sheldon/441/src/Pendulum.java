import java.util.Scanner;

import javax.swing.JFrame;

import org.math.plot.Plot2DPanel;
public class Pendulum {

	public static void main(String[] args){
		Scanner input = new Scanner(System.in);
		
		double theta_initial = 0;
		System.out.println("1 for Euler, 2 for Verlet");
		int method = input.nextInt();
		System.out.println("Enter the initial angle: ");
		theta_initial = input.nextDouble();
		double theta = theta_initial * Math.PI / 180;
		double omega = 0;
		
		double g_l = 1;
		double tau = 0;
		double t = 0;
		double tprev = 0;
		int turn = 0;
		System.out.println("Enter a time step: ");
		tau = input.nextDouble();
		
		double a = -g_l * Math.sin(theta);
		double theta_prev = theta - omega * tau * tau * a;
		int nstep = 0;
		
		System.out.println("Enter a number of time steps: ");
		nstep = input.nextInt();
		double t_plot[] = new double[nstep + 1];
		double th_plot[] = new double[nstep + 1];
		double period[] = new double[nstep + 1];
		
		for(int i = 1; i <= nstep; i++){
			t_plot[i] = t;
			th_plot[i] = theta * 180 / Math.PI;
			t += tau;
			if( method == 1){
				theta_prev = theta;
				theta += tau * omega;
				omega += tau * a;
			}
			else{
				double theta_new = 2 * theta - theta_prev + tau * tau * a;
				theta_prev = theta;
				theta = theta_new;
			}
			
			if(theta * theta_prev < 0){
				System.out.println("Turning point at t = " +t);
				if(turn == 0){
					tprev = t;
				}
				else{
					period[turn] = 2 * (t - tprev);
					tprev = t;
				}
				turn++;
			}
		
		}
		int nPeriod = turn - 1;
		double avgperiod = 0;
		
		for(int i = 1; i <= nPeriod; i++){
			avgperiod += period[i];
		}
		
		avgperiod /= nPeriod;
		
		double pError = 0;
		
		for(int i = 1; i <= nPeriod; i++){
			pError += (period[i] - avgperiod) * (period[i] - avgperiod);
		}
		pError = Math.sqrt(pError / (nPeriod * (nPeriod - 1)));
		System.out.println("Average Period = " +avgperiod+ " +/- " +pError);
		
		Plot2DPanel plot = new Plot2DPanel();
		plot.addScatterPlot("Pendulum", t_plot, th_plot);
		
		JFrame frame = new JFrame("Pendulum");
		frame.setSize(600, 600);
		frame.setContentPane(plot);
		frame.setVisible(true);
		
	}
}
