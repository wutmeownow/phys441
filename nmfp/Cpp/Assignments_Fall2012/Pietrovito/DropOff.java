
public class DropOff {
	public static void main(String[] args) {
		
		double x = 1;
		double f = x*x;
		double fPrime = 2*x;
		double h;
		double deltaH;
		
		for(int i=0; i<20; i++) {
			h = Math.pow(10,  -i);
			deltaH = fPrime - (x*x + 2*x*h + h*h - f)/h;
			if(deltaH<0) {
				deltaH *= -1;
			}
			System.out.println(deltaH);
		}
	}
}
