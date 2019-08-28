
public class ComputerLimit {
	
	public static void main(String[] args){
		double changeInH;
		double h = 1;
		
		while(h > 0.00000000000000000001){
			changeInH = 2*1 - (Math.pow(1+h,2) - 1)/h;
			if(changeInH < 0){
				changeInH = changeInH * -1;
			}
			System.out.println("Limit at " +h+ " is " +changeInH);
			h = h/10;
			
		}
		
		
		
	}

}
